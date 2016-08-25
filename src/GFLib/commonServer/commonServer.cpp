#include <BSLib/utility/file/fileInfo.h>
#include <BSLib/utility/file/dirInfo.h>
#include <BSLib/utility/fileTracer.h>
#include <BSLib/utility/cmdExecMgr.h>
#include <BSLib/database/dbMgr.h>
#include <GFLib/commonServer/message/msgSystemChannel.h>
#include <GFLib/commonServer/message/msgLocalServer.h>
#include <GFLib/commonServer/commonServer.h>
#include <GFLib/commonServer/serverTypeMgr.h>
#include <GFLib/commonServer/tracer.h>
#include <GFLib/commonServer/stubMgr.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <GFLib/commonServer/sysChannelMgr.h>


namespace GFLib
{

namespace CommonServer
{

#define  GFLIB_COMMAND_LOGSIZE_MAX (1024 * 1024 * 1024)

struct SAcceptorIPAndPort
{
	BSLib::Network::ENetType m_netType;
	BSLib::Network::CSockAddr m_listenerAddr;
	void* m_tempData;
};

#ifdef WIN32

	BOOL WINAPI CtrlHandler(DWORD ctrlType)
	{
		ICommonServer::getCommonServer()->terminate();

		while (ICommonServer::getCommonServer()->isValid()) {
			BSLib::Utility::CThread::msleep(10);
		}
		return TRUE;
	}

#endif

BSLib::Utility::CFileTracer g_fileTracer;

//////////////////////////////////////////////////////////////////////////
ICommonServer::ICommonServer()
: m_serverID(INVALID_SERVERID)
, m_needPing(false)
{
	//CClientMgr::singleton().setClientCreator(this);
}

ICommonServer::~ICommonServer()
{
	for (BSLib::uint32 i=0; i<m_acceptorIPAndPorts.size(); ++i) {
		SAcceptorIPAndPort* acceptorIPAndPort = m_acceptorIPAndPorts[i];
		if (acceptorIPAndPort == NULL) {
			continue;
		}
		BSLIB_SAFE_DELETE(acceptorIPAndPort);
	}
	m_acceptorIPAndPorts.clear();
}

const std::string& ICommonServer::getServerTypeName()
{
	return CServerTypeMgr::singleton().getTextServerType(ICommonServer_getServerType());
}

bool ICommonServer::_IThread_init()
{
	if (!_loadInitConfigFile()){
		return false;
	}
	const std::string& serverName = getServerTypeName();

	std::string serverKey = BSLib::Framework::CSysConfig::singleton().getValueStr(serverName, "ServerKey");
	if (serverKey.empty()) {
		BSLIB_LOG_TRACE(ETT_GFLIB_COMMON, "获取ServerKey失败");
		return false;
	}
	_setKey(serverKey);

	_setOutConsole();
	_setOutTrace();

	BSLIB_LOG_INFO(ETT_GFLIB_COMMON, "********************************************************");
#ifdef _DEBUG

	BSLIB_LOG_INFO(ETT_GFLIB_COMMON, "%s Debug Version[%s]", serverName.c_str(), ICommonServer_getServerVersion().c_str());

#else

	BSLIB_LOG_INFO(ETT_GFLIB_COMMON, "%s Release Version[%s]", serverName.c_str(), ICommonServer_getServerVersion().c_str());

#endif
	BSLIB_LOG_INFO(ETT_GFLIB_COMMON, "********************************************************");

#ifdef _DEBUG

	BSLib::Framework::CSysConfig::singleton().showAll();
	BSLIB_LOG_DEBUG(ETT_GFLIB_COMMON, "********************************************************");

#endif

	if (!_loadNetConfigFile()) {
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "加载网络配置文件失败");
		return false;
	}

	if (!ICommonServer_initServer()) {
		return false;
	}

	CCommonSystemMgr* commonSystemMgr = &CCommonSystemMgr::singleton();
	if (!ICommonServer_initSystem(commonSystemMgr)) {
		return false;
	}
	std::string gameConfigPath = BSLib::Framework::CSysConfig::singleton().getValueStr("GameConfigPath");
	if (!ICommonServer_loadGameConfig(gameConfigPath)) {
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "加载游戏配置文件失败");
		return false;
	}
	if (!commonSystemMgr->loadGameConfig(gameConfigPath)) {
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "加载系统配置文件失败");
		return false;
	}

	if (!_connectServer()) {
		return false;
	}

	if (!BSLib::Framework::CMainThread::_IThread_init()) {
		return false;
	}

	_changeLogFile();

	BSLib::Framework::CMsgExecMgr* msgExecMgr = _getMsgExecMgr();
	ICommonServer_initServerMsg(msgExecMgr);
	commonSystemMgr->initServerMsg(msgExecMgr);
	
	BSLib::Utility::CCmdExecMgr* cmdExecMgr = _getCmdExecMgr();
	commonSystemMgr->initCommand(cmdExecMgr);

	if (!_openNetServer()) {
		return false;
	}
	if (!BSLib::Network::INetServer::_INetServer_init()) {
		return false;
	}
	BSLib::uint32 sysKey = BSLib::Framework::CSysConfig::singleton().getValueInt("SysKey");
	if (sysKey != 0) {
		if (!CSysChannelMgr::singleton().init(sysKey)) {
			return false;
		}
	}
	BSLib::int32 dbThreadCount = BSLib::Framework::CSysConfig::singleton().getValueInt(serverName, "DBPoolThreadMax");
	BSLib::Database::CDBMgr::singleton().init(dbThreadCount);

	if (!commonSystemMgr->singleton().init(_getTimerServer())) {
		return false;
	}

	if (!commonSystemMgr->singleton().startSystem()) {
		return false;
	}

	std::string needPing = BSLib::Framework::CSysConfig::singleton().getValueStr(serverName, "NeedPing");
	if (needPing == "true") {
		m_needPing = true;
	}

	BSLIB_LOG_INFO(ETT_GFLIB_COMMON, "###### %s 初始化完成 ######", serverName.c_str());
	return true;
}

int ICommonServer::_IThread_final()
{
	const std::string& serverName = getServerTypeName();
	BSLIB_LOG_INFO(ETT_GFLIB_COMMON, "###### %s 退出 ######", serverName.c_str());

	GFLib::CommonServer::CCommonSystemMgr::singleton().final();
	
	BSLib::uint32 sysKey = BSLib::Framework::CSysConfig::singleton().getValueInt("SysKey");
	if (sysKey != 0) {
		BSLIB_LOG_DEBUG(ETT_GFLIB_COMMON, "释放CSysChannelMgr资源", serverName.c_str());
		CSysChannelMgr::singleton().final();
	}

	BSLib::Database::CDBMgr::singleton().final();

	BSLIB_LOG_DEBUG(ETT_GFLIB_COMMON, "释放CClientMgr资源", serverName.c_str());
	CClientMgr::singleton().final();

	BSLIB_LOG_DEBUG(ETT_GFLIB_COMMON, "释放INetServer资源", serverName.c_str());
	BSLib::Network::INetServer::_INetServer_final();

	BSLIB_LOG_DEBUG(ETT_GFLIB_COMMON, "释放CServiceMgr资源", serverName.c_str());
	CServiceMgr::singleton().closeAll();

	BSLIB_LOG_DEBUG(ETT_GFLIB_COMMON, "释放CMainThread资源", serverName.c_str());
	BSLib::Framework::CMainThread::_IThread_final();

	_closeTrace();

	return 0;
}

bool ICommonServer::_IThread_callback()
{
	return BSLib::Framework::CMainThread::_IThread_callback();
}

// void ICommonServer::_update_1000()
// {
// 	BSLib::Network::SNetCollectInfor netCollectInfor;
// 	BSLib::Network::INetServer::getNetInfo(netCollectInfor);
// 
// 	BSLIB_LOG_TRACE(ETT_GFLIB_COMMON, "[ConnectCount=%d][StubCount=%d][OkeyStubCount=%d][VerifyStubCount=%d]"
// 		,netCollectInfor.m_tcpConnectCount
// 		,netCollectInfor.m_tcpStubCount
// 		,netCollectInfor.m_tcpOkayStubCount
// 		,netCollectInfor.m_tcpVerifyStubCount);
// }

bool ICommonServer::ICommonServer_initServer()
{
	//const std::string& serverName = getServerTypeName();

	std::string serverKey = getServerKey();
	const SServiceNetInfo* serverInfo = CServiceMgr::singleton().getServerNetInfor(serverKey);
	if (serverInfo == NULL) {
		BSLIB_LOG_TRACE(ETT_GFLIB_COMMON, "ServerKey[%s]获取网络参数失败", serverKey.c_str());
		return false;
	}
	if (ICommonServer_getServerType() != serverInfo->m_serverID.getServerType()) {
		BSLIB_LOG_TRACE(ETT_GFLIB_COMMON, "ServerKey[%s]获取类型参数不一致", serverKey.c_str());
		return false;
	}
	_setServerID(serverInfo->m_serverID);

	BSLIB_LOG_INFO(ETT_GFLIB_COMMON, "设置本地服务 %s(%d.%d.%d) Key[%s]",
		GFLib::CommonServer::CServerTypeMgr::singleton().getTextServerType(getServerID().getServerType()).c_str(),
		getServerID().getZoneID(),
		getServerID().getServerType(),
		getServerID().getServerNumber(),
		getServerKey().c_str());

	for (BSLib::uint32 i=0; i<serverInfo->m_listenerAddrList.size(); ++i) {
		_addAcceptorIPAndPort(BSLib::Network::NETT_TCP, serverInfo->m_listenerAddrList[i].m_listenerAddr, (void*)serverInfo->m_listenerAddrList[i].m_flag);
	}
	return true;
}

bool ICommonServer::ICommonServer_initSystem(CCommonSystemMgr* commanSystemMgr)
{
	return true;
}

bool ICommonServer::ICommonServer_loadGameConfig(const std::string& a_configPath)
{
	return true;
}

void ICommonServer::ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSysChannelLC2LCReqServerInfo, &ICommonServer::_onMsgSysChannelLC2LCReqServerInfo, this);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSysChannelLC2LCNtfCommand, &ICommonServer::_onMsgSysChannelLC2LCNtfCommand, this);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDServerLocalLC2LCNtfServerEnter, &ICommonServer::_onMsgServerLocalLC2LCNtfServerEnter, this);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDServerLocalLC2LCNtfServerLeave, &ICommonServer::_onMsgServerLocalLC2LCNtfServerLeave, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDServerLocalLC2LCNtfCommand, &BSLib::Framework::CreateCMessage<CMsgServerLocalLC2LCNtfCommand>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDServerLocalLC2LCNtfCommand, &ICommonServer::_onMsgServerLocalLC2LCNtfCommand, this);
}


void ICommonServer::ICommonServer_cbServerEnter(SServerID& a_serverID, const std::string& a_key)
{
	BSLIB_LOG_TRACE(ETT_GFLIB_COMMON, "%s(%d.%d.%d)[%s]进入",
		GFLib::CommonServer::CServerTypeMgr::singleton().getTextServerType(a_serverID.getServerType()).c_str(),
		a_serverID.getZoneID(),
		a_serverID.getServerType(),
		a_serverID.getServerNumber(),
		a_key.c_str());

	CCommonSystemMgr::singleton().cbServerEnter(a_serverID, a_key);
}

void ICommonServer::ICommonServer_cbServerLeave(SServerID& a_serverID, const std::string& a_key)
{
	CCommonSystemMgr::singleton().cbServerLeave(a_serverID, a_key);

	BSLIB_LOG_TRACE(ETT_GFLIB_COMMON, "%s(%d.%d.%d)[%s]离开",
		GFLib::CommonServer::CServerTypeMgr::singleton().getTextServerType(a_serverID.getServerType()).c_str(),
		a_serverID.getZoneID(),
		a_serverID.getServerType(),
		a_serverID.getServerNumber(),
		a_key.c_str());
}

bool ICommonServer::_addAcceptorIPAndPort(BSLib::Network::ENetType netType, const BSLib::Network::CSockAddr& acceptorAddr, void* tempData)
{
	SAcceptorIPAndPort* acceptorIPAndPort = new SAcceptorIPAndPort();
	if (acceptorIPAndPort == NULL) {
		return false;
	}
	acceptorIPAndPort->m_netType = netType;
	acceptorIPAndPort->m_listenerAddr = acceptorAddr;
	acceptorIPAndPort->m_tempData = tempData;
	m_acceptorIPAndPorts.push_back(acceptorIPAndPort);
	return true;
}

bool ICommonServer::_addAcceptorIPAndPort(BSLib::Network::ENetType netType, const std::string& acceptorIP, int acceptorPort, void* tempData)
{
	BSLib::Network::CSockAddr acceptorAddr(acceptorIP.c_str(), acceptorPort);

	return _addAcceptorIPAndPort(netType, acceptorAddr, tempData);
}

BSLib::Network::CNetStubMgr* ICommonServer::_INetServer_cbNetStubMgr()
{
	return &CStubMgr::singleton();
}

BSLib::Network::CNetStubPtr ICommonServer::_INetServer_cbNewTcpStub(BSLib::Network::CNetConnectionPtr& netConnPtr, void* tempData)
{
	const BSLib::Network::CSockAddr& localAddr = netConnPtr->getLocalAddr();
	const BSLib::Network::CSockAddr& peerAddr = netConnPtr->getPeerAddr();
	BSLIB_LOG_INFO(ETT_GFLIB_COMMON, "连接[%s:%d]<-------[%s:%d]", localAddr.getIP().c_str(), localAddr.getPort(), peerAddr.getIP().c_str(), peerAddr.getPort());

	return BSLib::Network::CNetStubPtr(NULL);
}

BSLib::Network::CNetStubPtr ICommonServer::_INetServer_cbNewUdpStub(BSLib::Network::CNetConnectionPtr& netConnPtr, void* tempData)
{
	return BSLib::Network::CNetStubPtr(NULL);
}

CCommonClientPtr ICommonServer::_ICommonServer_cbCreateClient(SServerID& a_serverID, const std::string& a_serverKey)
{
	return CCommonClientPtr(NULL);
}

bool ICommonServer::_loadInitConfigFile()
{
	//加载配置文件
	const std::string& serverName = getServerTypeName();

	if (serverName.empty() || serverName =="Unkown"){
		return false;
	}
	std::string workpath = BSLib::Framework::CSysConfig::singleton().getValueStr("WorkPath");
	if (workpath.empty()){
		std::string execFileDir = BSLib::Utility::CDirInfo::getExeDirectory();
		if (execFileDir.empty()){
			workpath = BSLib::Utility::CDirInfo::getCurDirectory();
		} else {
			workpath = BSLib::Utility::CFileInfo::getFullPath(execFileDir);
		}
		if (workpath.empty()){
			return false;
		}
		BSLib::Framework::CSysConfig::singleton().setValue("WorkPath", workpath);
	}
	std::string configPath = workpath + "\\config";
	BSLib::Utility::CDirInfo::standardization(configPath);
	BSLib::Framework::CSysConfig::singleton().setValue("SysConfigPath", configPath);

	std::string configFile = BSLib::Framework::CSysConfig::singleton().getValueStr("SysConfigFile");
	if (configFile.empty()){
		configFile = serverName + ".ini";
		BSLib::Framework::CSysConfig::singleton().setValue("SysConfigFile", configFile);
	}
	std::string configFilePath = configPath + "\\";
	configFilePath += configFile;
	BSLib::Utility::CDirInfo::standardization(configFilePath);
	if (!BSLib::Framework::CSysConfig::singleton().open(configFilePath)){
		return false;
	}
	BSLib::Framework::CSysConfig::singleton().setValue("ConfigFilePath", configFilePath);

	std::string gameConfigPath = workpath;
	std::string gameConfig = BSLib::Framework::CSysConfig::singleton().getValueStr("GameConfigDir");
	if (gameConfig.empty()) {
		BSLib::Framework::CSysConfig::singleton().setValue("GameConfigDir", "config");
		gameConfigPath += "\\config";
	} else {
		gameConfigPath += "\\";
		gameConfigPath += gameConfig;
	}
	BSLib::Utility::CDirInfo::standardization(gameConfigPath);
	BSLib::Framework::CSysConfig::singleton().setValue("GameConfigPath", gameConfigPath);

	return true;
}

bool ICommonServer::_loadNetConfigFile()
{
	std::string workpath = BSLib::Framework::CSysConfig::singleton().getValueStr("WorkPath");
	std::string netConfigFile = BSLib::Framework::CSysConfig::singleton().getValueStr("NetConfigFile");
	if (netConfigFile.empty()){
		netConfigFile = "NetConfig.xml";
		BSLib::Framework::CSysConfig::singleton().setValue("NetConfigFile", netConfigFile);
	}
	std::string netConfigFilePath = workpath + "\\config\\";
	netConfigFilePath += netConfigFile;

	BSLib::Utility::CDirInfo::standardization(netConfigFilePath);

	if (!CServiceMgr::singleton().loadConfig(netConfigFilePath)) {
		return false;
	}

	return true;
}

void ICommonServer::_setOutConsole()
{
	const std::string& serverName = getServerTypeName();
	//设置控制台输出
	bool isOutConsole = false;
	std::string outConsole = BSLib::Framework::CSysConfig::singleton().getValueStr(serverName, "OutConsole");
	if (outConsole == "true") {
		isOutConsole = true;
	} else {
		BSLib::Framework::CSysConfig::singleton().setValue(serverName, "OutConsole", "false");
	}
	std::string outConsoleLevel = BSLib::Framework::CSysConfig::singleton().getValueStr(serverName, "OutConsoleLevel");
	if (outConsoleLevel.empty()) {
		outConsoleLevel = "infor";
		BSLib::Framework::CSysConfig::singleton().setValue(serverName, "OutConsoleLevel", outConsoleLevel);
	}

#ifdef WIN32

	if (isOutConsole) {
		::SetConsoleCtrlHandler(CtrlHandler, TRUE);
	}

#else

	if (!isOutConsole) {
		daemon(1, 1);
	}

#endif

	g_fileTracer.setOutConsole(isOutConsole, outConsoleLevel.c_str());
	BSLib::Utility::CTracer::setSysTracer(&g_fileTracer);
}

void ICommonServer::_setOutTrace()
{
	const std::string& serverName = getServerTypeName();
	std::string workpath = BSLib::Framework::CSysConfig::singleton().getValueStr("WorkPath");

	// 设置日志输出文件
	std::string logFilePath = workpath + "\\log\\";
	logFilePath += serverName;
	BSLib::Utility::CDirInfo::standardization(logFilePath);
	if (!BSLib::Utility::CDirInfo::isExist(logFilePath)) {
		BSLib::Utility::CDirInfo::makeDir(logFilePath);
	}
	BSLib::Framework::CSysConfig::singleton().setValue(serverName, "LogPath", logFilePath);
	std::string logFile = BSLib::Framework::CSysConfig::singleton().getValueStr(serverName, "LogFile");
	if (logFile.empty()){
		logFile = serverName + ".log";
		BSLib::Framework::CSysConfig::singleton().setValue(serverName, "LogFile", logFile);
	}
	logFilePath += "\\";
	logFilePath += logFile;
	BSLib::Utility::CDirInfo::standardization(logFilePath);
	g_fileTracer.setOutFile(logFilePath.c_str(), GFLIB_COMMAND_LOGSIZE_MAX);
	BSLib::Framework::CSysConfig::singleton().setValue("LogFilePath", logFilePath);

	// 设置日志等级
	std::string logLevel = BSLib::Framework::CSysConfig::singleton().getValueStr(serverName, "LogLevel");
	if (logLevel.empty()) {
		logLevel = "infor";
		BSLib::Framework::CSysConfig::singleton().setValue(serverName, "LogLevel", logLevel);
	}
	g_fileTracer.setTypeON(BSLib::ETT_ALL);
	g_fileTracer.setLevel(BSLib::ETT_ALL, logLevel.c_str());

	g_fileTracer.setTypeName(ETT_GFLIB_COMMON, "GFCOMMON");
}

void ICommonServer::_changeLogFile()
{
	const std::string& serverName = getServerTypeName();

	std::string logFilePath = BSLib::Framework::CSysConfig::singleton().getValueStr(serverName, "LogPath");
	if (!logFilePath.empty()) {
		std::string serverKey = getServerKey();
		if (!serverKey.empty()) {
			logFilePath += "\\";
			logFilePath += serverKey;
			BSLib::Utility::CDirInfo::standardization(logFilePath);
			if (!BSLib::Utility::CDirInfo::isExist(logFilePath)) {
				BSLib::Utility::CDirInfo::makeDir(logFilePath);
			}
			std::string logFile = BSLib::Framework::CSysConfig::singleton().getValueStr(serverName, "LogFile");
			logFilePath += "\\";
			logFilePath += logFile;
			BSLib::Utility::CDirInfo::standardization(logFilePath);

			BSLIB_LOG_INFO(ETT_GFLIB_COMMON, "转移日志[%s]", logFilePath.c_str());

			BSLib::Utility::CStringA logType = BSLib::Framework::CSysConfig::singleton().getValueStr(serverName, "LogType");
			logType.toLower();
			if (logType == "hour") {
				g_fileTracer.setOutFile(logFilePath.c_str(), BSLib::Utility::ELFST_HOUR);
			} else if (logType == "day") {
				g_fileTracer.setOutFile(logFilePath.c_str(), BSLib::Utility::ELFST_DAY);
			} else if (logType == "size") {
				//BSLib::uint32 logSize = 1024 * 1024 * 1024;
				g_fileTracer.setOutFile(logFilePath.c_str(), GFLIB_COMMAND_LOGSIZE_MAX);
			} else {
				g_fileTracer.setOutFile(logFilePath.c_str(), BSLib::Utility::ELFST_HOUR);
			}
			
		}
	}
}

void ICommonServer::_closeTrace()
{
	BSLib::Utility::CTracer::setSysTracer(NULL);
	g_fileTracer.close();
}

bool ICommonServer::_connectServer()
{
	std::string serverKey = getServerKey();
	const SServiceNetInfo* serverInfo = CServiceMgr::singleton().getServerNetInfor(serverKey);
	if (serverInfo == NULL) {
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "ServerKey[%s]获取网络参数失败", serverKey.c_str());
		return false;
	}

	for (BSLib::uint32 i=0; i<serverInfo->m_connectorAddrList.size(); ++i) {
		std::string connectServerKey = serverInfo->m_connectorAddrList[i].m_serverKey;
		SServerID serverID = CServiceMgr::singleton().getServerID(connectServerKey);
		if (!serverID.isValid()) {
			BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "ServerKey[%s]链接[%s]失败,ServerID无效", serverKey.c_str(), connectServerKey.c_str());
			return false;
		}
		
		CCommonClientPtr commonClientPtr = _ICommonServer_cbCreateClient(serverID, connectServerKey);
		if (commonClientPtr == NULL) {
			BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "ServerKey[%s]链接[%s]失败", serverKey.c_str(), connectServerKey.c_str());
			return false;
		}
		commonClientPtr->setServerIPAndPort(serverInfo->m_connectorAddrList[i].m_connectorAddr.getIP(), serverInfo->m_connectorAddrList[i].m_connectorAddr.getPort());
		commonClientPtr->setNeedReconnect(serverInfo->m_connectorAddrList[i].m_reconnect);
		commonClientPtr->setNeedTerminateServer(serverInfo->m_connectorAddrList[i].m_terminateServer);
		commonClientPtr->setNeedPing(serverInfo->m_connectorAddrList[i].m_needPing);
		
		CClientMgr::singleton().addCommonClient(serverID, commonClientPtr);
		commonClientPtr->start();
	}
	return true;
}

bool ICommonServer::_openNetServer()
{
	const std::string& serverName = getServerTypeName();
	bool needOpenTcp = false;
	bool needOpenUdp = false;
	for (BSLib::uint32 i=0; i<m_acceptorIPAndPorts.size(); ++i) {
		SAcceptorIPAndPort* acceptorIPAndPort = m_acceptorIPAndPorts[i];
		if (acceptorIPAndPort == NULL) {
			continue;
		}
		if (acceptorIPAndPort->m_netType == BSLib::Network::NETT_TCP) {
			if (!BSLib::Network::INetServer::_addTcpAccpetor(acceptorIPAndPort->m_listenerAddr, acceptorIPAndPort->m_tempData)) {
				BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "%s 开启监听端口 TCP[%s:%d] 失败", serverName.c_str(), acceptorIPAndPort->m_listenerAddr.getIP().c_str(), acceptorIPAndPort->m_listenerAddr.getPort());
				return false;
			}
			needOpenTcp = true;
			BSLIB_LOG_INFO(ETT_GFLIB_COMMON, "%s 开启监听端口 TCP[%s:%d] 成功", serverName.c_str(), acceptorIPAndPort->m_listenerAddr.getIP().c_str(), acceptorIPAndPort->m_listenerAddr.getPort());
		} else if (acceptorIPAndPort->m_netType == BSLib::Network::NETT_UDP) {
			if (!BSLib::Network::INetServer::_addUdpAccpetor(acceptorIPAndPort->m_listenerAddr, acceptorIPAndPort->m_tempData)) {
				BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "%s 开启监听端口 UDP[%s:%d] 失败", serverName.c_str(), acceptorIPAndPort->m_listenerAddr.getIP().c_str(), acceptorIPAndPort->m_listenerAddr.getPort());
				return false;
			}
			needOpenUdp = true;
			BSLIB_LOG_INFO(ETT_GFLIB_COMMON, "%s 开启监听端口 UDP[%s:%d] 成功", serverName.c_str(), acceptorIPAndPort->m_listenerAddr.getIP().c_str(), acceptorIPAndPort->m_listenerAddr.getPort());
		}
		BSLIB_SAFE_DELETE(acceptorIPAndPort);
	}
	m_acceptorIPAndPorts.clear();
	
	BSLib::uint32 maxStub, minThread, maxStubPerThd;
	if (needOpenTcp) {
		maxStub = BSLib::Framework::CSysConfig::singleton().getValueInt(serverName, "TcpMaxConnect");
		if (maxStub == 0) {
			maxStub = 4096;
		}
		minThread = BSLib::Framework::CSysConfig::singleton().getValueInt(serverName, "TcpMinThreads");
		if (minThread == 0) {
			minThread = 2;
		}
		maxStubPerThd = BSLib::Framework::CSysConfig::singleton().getValueInt(serverName, "TcpMaxConnectPerThread");
		if (maxStubPerThd == 0) {
			maxStubPerThd = 512;
		}
		if (!BSLib::Network::INetServer::_setTcpStubPool(maxStub, minThread, maxStubPerThd)) {
			BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "%s 开启TCP Stub Pool失败", serverName.c_str());
			return false;
		}
	}
	if (needOpenUdp) {
		maxStub = BSLib::Framework::CSysConfig::singleton().getValueInt(serverName, "UdpMaxConnect");
		if (maxStub == 0) {
			maxStub = 4096;
		}
		minThread = BSLib::Framework::CSysConfig::singleton().getValueInt(serverName, "UdpMinThreads");
		if (minThread == 0) {
			minThread = 2;
		}
		maxStubPerThd = BSLib::Framework::CSysConfig::singleton().getValueInt(serverName, "UdpMaxConnectPerThread");
		if (maxStubPerThd == 0) {
			maxStubPerThd = 512;
		}
		if (!BSLib::Network::INetServer::_setUdpStubPool(maxStub, minThread, maxStubPerThd)) {
			BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "%s 开启UDP Stub Pool失败", serverName.c_str());
			return false;
		}
	}
	return true;
}

void ICommonServer::_onMsgSysChannelLC2LCReqServerInfo(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework:: SMessage* msg)
{
	if (msgLabel->getLabelType() != BSLib::Framework::ELABELTYPE_SYS) {
		return ;
	}
	BSLib::Framework::SSysMsgLabel* sysMsgLabel = (BSLib::Framework::SSysMsgLabel*)msgLabel;
	
	SMsgSysChannelLC2LCResServerInfo resServerInfor;
	resServerInfor.m_localServerID = getServerID();
	resServerInfor.setLocalKeyName(getServerKey());

	CSysChannelMgr::singleton().sendMsg(sysMsgLabel->m_sysMsgIDFrome, &resServerInfor, sizeof(resServerInfor));
}

void ICommonServer::_onMsgSysChannelLC2LCNtfCommand(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework:: SMessage* msg)
{
	SMsgSysChannelLC2LCNtfCommand* command = (SMsgSysChannelLC2LCNtfCommand*)msg;

	BSLIB_LOG_INFO(ETT_GFLIB_COMMON, "收到通道命令[%s]", command->m_command);

	m_cmdExecMgr.parseCommand(command->m_command, msgLabel);
}

void ICommonServer::_onMsgServerLocalLC2LCNtfServerEnter(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework:: SMessage* msg)
{
	SMsgServerLocalLC2LCNtfServerEnter* serverEnter = (SMsgServerLocalLC2LCNtfServerEnter*)msg;
	ICommonServer_cbServerEnter(serverEnter->m_enterServerID, serverEnter->m_enterServerKey);
}

void ICommonServer::_onMsgServerLocalLC2LCNtfServerLeave(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework:: SMessage* msg)
{
	SMsgServerLocalLC2LCNtfServerLeave* serverLeave = (SMsgServerLocalLC2LCNtfServerLeave*)msg;
	ICommonServer_cbServerLeave(serverLeave->m_leaveServerID, serverLeave->m_leaveServerKey);
	CServiceMgr::singleton().freeService(serverLeave->m_leaveServerID);
}

void ICommonServer::_onMsgServerLocalLC2LCNtfCommand(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework:: SMessage* msg)
{
	CMsgServerLocalLC2LCNtfCommand* command = (CMsgServerLocalLC2LCNtfCommand*)msg;

	m_cmdExecMgr.parseCommand(command->m_command, msgLabel);
}


}//CommonServer

}//GFLib



