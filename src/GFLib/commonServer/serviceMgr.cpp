#include <BSLib/utility/file/xmlFile.h>
#include <BSLib/framework/message/msgType.h>
#include <GFLib/commonServer/tracer.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <GFLib/commonServer/message/msgServerLink.h>
#include <GFLib/commonServer/commonClient.h>
#include <GFLib/commonServer/clientMgr.h>
#include <GFLib/commonServer/commonServer.h>

namespace GFLib
{

namespace CommonServer
{

//////////////////////////////////////////////////////////////////////////
bool loadServersNode(ZoneID a_zoneID, BSLib::Utility::CXmlFile& a_xmlFile, BSLib::Utility::HXmlNode a_serversNode, SServiceNetInfo& a_netInfor)
{ 
	BSLib::int32 serverNumber = 0;
	std::string strServerType = "";
	std::string innerIP = "";
	std::string outerIP = "";
	a_xmlFile.getNodeAttrValue(a_serversNode, "number", serverNumber);
	a_xmlFile.getNodeAttrValue(a_serversNode, "type", strServerType);
	a_xmlFile.getNodeAttrValue(a_serversNode, "key", a_netInfor.m_key);
	a_xmlFile.getNodeAttrValue(a_serversNode, "outerip", outerIP);
	a_xmlFile.getNodeAttrValue(a_serversNode, "innerip", innerIP);
	if (strServerType.empty()) {
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "server属性type无效");
		return false;
	}
	if (innerIP.empty() && outerIP.empty()) {
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "server属性inner和outer都为空");
		return false;
	}
	if (serverNumber == 0) {
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "server属性number无效");
		return false;
	}
	std::string serverTypeName = strServerType + "server";
	ServerType serverType = CServerTypeMgr::singleton().getServerTypeByText(serverTypeName);
	if (serverType == SRVTYPE_NULL) {
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "server属性type[%s]不存在", serverTypeName.c_str());
		return false;
	}
	a_netInfor.m_serverID.setServerID(a_zoneID, serverType, serverNumber);
	if (!innerIP.empty()) {
		a_netInfor.m_innerAddr.setIP(innerIP.c_str());
	}
	if (!outerIP.empty()) {
		a_netInfor.m_outerAddr.setIP(outerIP.c_str());
	}
	BSLib::Utility::HXmlNode subNode = a_xmlFile.getChildNode(a_serversNode);
	while (subNode != NULL) {
		std::string subNodeName;
		if (!a_xmlFile.getNodeName(subNode, subNodeName)) {
			return false;
		}
		if (subNodeName == "listener") {
			SServiceNetListenerInfo listenerInfor;
			std::string listenerIP;
			BSLib::int32 listenerPort = 0;
			std::string strNeedOuter = "false";

			a_xmlFile.getNodeAttrValue(subNode, "ip", listenerIP);
			a_xmlFile.getNodeAttrValue(subNode, "port", listenerPort);
			a_xmlFile.getNodeAttrValue(subNode, "flag", listenerInfor.m_flag);
			a_xmlFile.getNodeAttrValue(subNode, "outer", strNeedOuter);

			listenerInfor.m_listenerAddr.setIPAndPort(listenerIP.c_str(), (BSLib::uint16)listenerPort);
			listenerInfor.m_outer = false;
			if (strNeedOuter == "true") {
				listenerInfor.m_outer = true;
				a_netInfor.m_outerAddr.setPort((BSLib::uint16)listenerPort);
			} else {
				a_netInfor.m_innerAddr.setPort((BSLib::uint16)listenerPort);
			}

			a_netInfor.m_listenerAddrList.push_back(listenerInfor);
		} else if (subNodeName == "connect") {
			SServiceNetConnectorInfo connectorInfor;
			std::string strNeedReconnect = "false";
			std::string strNeedTerminateServer = "false";
			std::string strNeedPing = "false";
			a_xmlFile.getNodeAttrValue(subNode, "key", connectorInfor.m_serverKey);
			a_xmlFile.getNodeAttrValue(subNode, "flag", connectorInfor.m_flag);
			a_xmlFile.getNodeAttrValue(subNode, "reconnect", strNeedReconnect);
			a_xmlFile.getNodeAttrValue(subNode, "terminate", strNeedTerminateServer);
			a_xmlFile.getNodeAttrValue(subNode, "ping", strNeedPing);

			connectorInfor.m_reconnect = false;
			if (strNeedReconnect == "true") {
				connectorInfor.m_reconnect = true;
			}
			connectorInfor.m_terminateServer = false;
			if (strNeedTerminateServer == "true") {
				connectorInfor.m_terminateServer = true;
			}
			connectorInfor.m_needPing = false;
			if (strNeedPing == "true") {
				connectorInfor.m_needPing = true;
			}

			a_netInfor.m_connectorAddrList.push_back(connectorInfor);
		}
		subNode = a_xmlFile.getNextNode(subNode);
	}
	return true;
}

bool loadGlobalNodes(BSLib::Utility::CXmlFile& a_xmlFile, BSLib::Utility::HXmlNode a_globalNode, BSLib::Utility::CHashMap<std::string, SServiceInfo*>& a_hashMapByKeyName)
{
	BSLib::Utility::HXmlNode subNode = a_xmlFile.getChildNode(a_globalNode);
	while (subNode != NULL) {
		std::string subNodeName;
		if (!a_xmlFile.getNodeName(subNode, subNodeName)) {
			return false;
		}
		if (subNodeName == "server") {
			SServiceInfo* serviceInfor = new SServiceInfo;
			if (serviceInfor == NULL) {
				return false;
			}
			if (!loadServersNode(GLOBAL_ZONEID, a_xmlFile, subNode, serviceInfor->m_netInfor)) {
				BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "加载节点[%s]失败", subNodeName.c_str());
				BSLIB_SAFE_DELETE(serviceInfor);
				return false;
			}
			if (a_hashMapByKeyName.find(serviceInfor->m_netInfor.m_key) != a_hashMapByKeyName.end()) {
				BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "加载节点[%s]失败, key[%s]值重复", subNodeName.c_str(), serviceInfor->m_netInfor.m_key.c_str());
				BSLIB_SAFE_DELETE(serviceInfor);
				return false;
			}
			a_hashMapByKeyName.setValue(serviceInfor->m_netInfor.m_key, serviceInfor);
		}
		subNode = a_xmlFile.getNextNode(subNode);
	}
	return true;
}

bool loadZoneNodes(BSLib::Utility::CXmlFile& a_xmlFile, BSLib::Utility::HXmlNode a_zoneNode, BSLib::Utility::CHashMap<std::string, SServiceInfo*>& a_hashMapByKeyName)
{
	BSLib::int32 zoneID = GLOBAL_ZONEID;
	a_xmlFile.getNodeAttrValue(a_zoneNode, "zoneid", zoneID);
	if (zoneID == GLOBAL_ZONEID) {
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "加载zone属性id失败");
		return false;
	}
	BSLib::Utility::HXmlNode subNode = a_xmlFile.getChildNode(a_zoneNode);
	while (subNode != NULL) {
		std::string subNodeName;
		if (!a_xmlFile.getNodeName(subNode, subNodeName)) {
			return false;
		}
		if (subNodeName == "server") {
			SServiceInfo* serviceInfor = new SServiceInfo;
			if (serviceInfor == NULL) {
				return false;
			}
			if (!loadServersNode((ZoneID)zoneID, a_xmlFile, subNode, serviceInfor->m_netInfor)) {
				BSLIB_LOG_TRACE(ETT_GFLIB_COMMON, "加载节点[%s]失败", subNodeName.c_str());
				BSLIB_SAFE_DELETE(serviceInfor);
				return false;
			}
			if (a_hashMapByKeyName.find(serviceInfor->m_netInfor.m_key) != a_hashMapByKeyName.end()) {
				BSLIB_LOG_TRACE(ETT_GFLIB_COMMON, "加载节点[%s]失败, key[%s]值重复", subNodeName.c_str(), serviceInfor->m_netInfor.m_key.c_str());
				BSLIB_SAFE_DELETE(serviceInfor);
				return false;
			}
			a_hashMapByKeyName.setValue(serviceInfor->m_netInfor.m_key, serviceInfor);
		}
		subNode = a_xmlFile.getNextNode(subNode);
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
BSLIB_SINGLETON_DEFINE(CServiceMgr);

CServiceMgr::CServiceMgr()
{
	;
}

CServiceMgr::~CServiceMgr()
{
	;
}

bool CServiceMgr::loadConfig(const std::string& a_configFile)
{
	if (!_loadConfigFile(a_configFile)) {
		return false;
	}
	if (!_initServiceInfor()) {
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "初始文件[%s]失败", a_configFile.c_str());
		return false;
	}
	return true;
}

bool CServiceMgr::addService(CServicePtr& a_service)
{
	SServerID serverID = a_service->getServerID();

	SServiceInfo* serviceInfor = NULL;
	m_hashMapByServerID.getValue(serverID.getServerID(), serviceInfor);
	if (serviceInfor == NULL) {
		return false;
	}
	
	BSLib::Utility::CMutexFun mutexFun(&m_mutex);

	if (serviceInfor->m_state != 0) {
		BSLIB_LOG_TRACE(ETT_GFLIB_COMMON, "%s(%d.%d.%d)[%s]注册失败,Server资源还没有释放",
			GFLib::CommonServer::CServerTypeMgr::singleton().getTextServerType(serverID.getServerType()).c_str(),
			serverID.getZoneID(),
			serverID.getServerType(),
			serverID.getServerNumber(),
			a_service->getKey().c_str());
		return false;
	}
	if (serviceInfor->m_servicePtr != NULL) {
		BSLIB_LOG_TRACE(ETT_GFLIB_COMMON, "%s(%d.%d.%d)[%s]注册失败,已经存在",
			GFLib::CommonServer::CServerTypeMgr::singleton().getTextServerType(serverID.getServerType()).c_str(),
			serverID.getZoneID(),
			serverID.getServerType(),
			serverID.getServerNumber(),
			a_service->getKey().c_str());
		return false;
	}
	if (serviceInfor->m_netInfor.m_key != a_service->getKey()) {
		BSLIB_LOG_TRACE(ETT_GFLIB_COMMON, "%s(%d.%d.%d)[%s]注册失败,ServerKey不一致",
			GFLib::CommonServer::CServerTypeMgr::singleton().getTextServerType(serverID.getServerType()).c_str(),
			serverID.getZoneID(),
			serverID.getServerType(),
			serverID.getServerNumber(),
			a_service->getKey().c_str());
		return false;
	}
	serviceInfor->m_servicePtr = a_service;
	serviceInfor->m_state = 1;

	BSLIB_LOG_TRACE(ETT_GFLIB_COMMON, "%s(%d.%d.%d)[%s]注册成功",
		GFLib::CommonServer::CServerTypeMgr::singleton().getTextServerType(serverID.getServerType()).c_str(),
		serverID.getZoneID(),
		serverID.getServerType(),
		serverID.getServerNumber(),
		a_service->getKey().c_str());

	return true;
}

bool CServiceMgr::delService(SServerID a_serverID)
{
	SServiceInfo* serviceInfor = NULL;
	m_hashMapByServerID.getValue(a_serverID.getServerID(), serviceInfor);
	if (serviceInfor == NULL) {
		return false;
	}
	
	BSLib::Utility::CMutexFun mutexFun(&m_mutex);

	if (serviceInfor->m_servicePtr == NULL) {
		return false;
	}

	BSLIB_LOG_TRACE(ETT_GFLIB_COMMON, "%s(%d.%d.%d)注销成功",
		CServerTypeMgr::singleton().getTextServerType(a_serverID.getServerType()).c_str(),
		a_serverID.getZoneID(),
		a_serverID.getServerType(),
		a_serverID.getServerNumber());

	serviceInfor->m_servicePtr = NULL;
	serviceInfor->m_state = 2;

	return true;
}

void CServiceMgr::freeService(SServerID a_serverID)
{
	SServiceInfo* serviceInfor = NULL;
	m_hashMapByServerID.getValue(a_serverID.getServerID(), serviceInfor);
	if (serviceInfor == NULL) {
		return ;
	}

	BSLib::Utility::CMutexFun mutexFun(&m_mutex);

	if (serviceInfor->m_state != 2) {
		return ;
	}
	serviceInfor->m_state = 0;
}

void CServiceMgr::closeAll()
{
	BSLib::Utility::CHashMap<std::string, SServiceInfo*>::iterator it_key = m_hashMapByKeyName.begin();
	for (; it_key != m_hashMapByKeyName.end(); ++it_key) {
		if (it_key->second == NULL) {
			continue;
		}
		BSLIB_SAFE_DELETE(it_key->second);
	}
	m_hashMapByKeyName.clear();
	m_hashMapByServerID.clear();
	m_hashMapByServerType.clear();
	m_hashMapByZone.clear();
}

bool CServiceMgr::sendMsgToServer(const std::string& a_serverKey, GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
{
	SServiceInfo* serviceInfor = NULL;
	m_hashMapByKeyName.getValue(a_serverKey, serviceInfor);
	if (serviceInfor == NULL) {
		return false;
	}
	
	m_mutex.lock();
	CServicePtr servicePtr = serviceInfor->m_servicePtr ;
	m_mutex.unlock();

	if (servicePtr == NULL) {
		return false;
	}
	return servicePtr->IService_sendMsg(a_msg, a_msgSize);
}

bool CServiceMgr::sendMsgToServer(const std::string& a_serverKey, GFLib::CMessage& a_msg)
{
	SServiceInfo* serviceInfor = NULL;
	m_hashMapByKeyName.getValue(a_serverKey, serviceInfor);
	if (serviceInfor == NULL) {
		return false;
	}

	m_mutex.lock();
	CServicePtr servicePtr = serviceInfor->m_servicePtr ;
	m_mutex.unlock();

	if (servicePtr == NULL) {
		return false;
	}

	return servicePtr->IService_sendMsg(a_msg);
}

bool CServiceMgr::sendMsgToServer(const ServerID& a_serverID, GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
{
	SServiceInfo* serviceInfor = NULL;
	m_hashMapByServerID.getValue(a_serverID, serviceInfor);
	if (serviceInfor == NULL) {
		return false;
	}

	m_mutex.lock();
	CServicePtr servicePtr = serviceInfor->m_servicePtr ;
	m_mutex.unlock();

	if (servicePtr == NULL) {
		return false;
	}

	return servicePtr->IService_sendMsg(a_msg, a_msgSize);
}

bool CServiceMgr::sendMsgToServer(const ServerID& a_serverID, GFLib::CMessage& a_msg)
{
	SServiceInfo* serviceInfor = NULL;
	m_hashMapByServerID.getValue(a_serverID, serviceInfor);
	if (serviceInfor == NULL) {
		return false;
	}

	m_mutex.lock();
	CServicePtr servicePtr = serviceInfor->m_servicePtr ;
	m_mutex.unlock();

	if (servicePtr == NULL) {
		return false;
	}

	return servicePtr->IService_sendMsg(a_msg);
}

bool CServiceMgr::sendMsgToServer(const SServerID& a_serverID, GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
{
	return sendMsgToServer(a_serverID.getServerID(), a_msg, a_msgSize);
}


bool CServiceMgr::sendMsgToServer(const SServerID& a_serverID, GFLib::CMessage& a_msg)
{
	return sendMsgToServer(a_serverID.getServerID(), a_msg);
}

bool CServiceMgr::sendMsgToServer(const SServerID& a_serverID, const SAccountKey& a_accountKey, GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
{
	GFLib::CommonServer::CCommonServer* server = GFLib::CommonServer::CCommonServer::getCommonServer();
	if (server == NULL) {
		return false;
	}

	BSLib::Utility::CStream stream;
	stream.writeReserve(a_msgSize + sizeof(SMsgServerLinkXX2XXNtfTransfer));

	SMsgServerLinkXX2XXNtfTransfer* ntTransfer = (SMsgServerLinkXX2XXNtfTransfer*)stream.writePtr();
	new (static_cast<void*>(ntTransfer)) SMsgServerLinkXX2XXNtfTransfer();
	ntTransfer->m_serverIDFrom = server->getServerID();
	ntTransfer->m_serverIDTo = a_serverID;
	ntTransfer->m_accountKey = a_accountKey;
	ntTransfer->m_msgSize = 0;

	BSLib::uint32 headSize = ntTransfer->getSize();
	ntTransfer->m_msgSize = a_msgSize;

	stream.writeFlip(headSize);

	stream.push((char*)a_msg, a_msgSize);

	return GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_serverID, (GFLib::SMessage*)stream.readPtr(), stream.readSize());
}

bool CServiceMgr::sendMsgToServer(const SServerID& a_serverID, const SAccountKey& a_accountKey, GFLib::CMessage& a_msg)
{
	GFLib::CommonServer::CCommonServer* server = GFLib::CommonServer::CCommonServer::getCommonServer();
	if (server == NULL) {
		return false;
	}

	BSLib::Utility::CStream stream;
	stream.writeReserve(sizeof(SMsgServerLinkXX2XXNtfTransfer));

	SMsgServerLinkXX2XXNtfTransfer* ntTransfer = (SMsgServerLinkXX2XXNtfTransfer*)stream.writePtr();
	new (static_cast<void*>(ntTransfer)) SMsgServerLinkXX2XXNtfTransfer();
	ntTransfer->m_serverIDFrom = server->getServerID();
	ntTransfer->m_serverIDTo = a_serverID;
	ntTransfer->m_accountKey = a_accountKey;
	ntTransfer->m_msgSize = 0;

	BSLib::uint32 headSize = ntTransfer->getSize();
	stream.writeFlip(headSize);

	if (!a_msg.serializeTo(stream)){
		return false;
	}

	ntTransfer = (SMsgServerLinkXX2XXNtfTransfer*)stream.readPtr();
	ntTransfer->m_msgSize = stream.readSize() - headSize;

	return GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_serverID, (GFLib::SMessage*)stream.readPtr(), stream.readSize());
}


bool CServiceMgr::sendMsgToServerType(ServerType a_serverType, GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
{
	BSLib::Utility::CHashMap< ServerType, std::vector< SServiceInfo* > >::iterator it_type;
	it_type = m_hashMapByServerType.find(a_serverType);
	if (it_type == m_hashMapByServerType.end()) {
		return true;
	}
	std::vector<SServiceInfo*>& serviceList = it_type->second;
	for (BSLib::uint32 i=0; i<serviceList.size(); ++i) {
		SServiceInfo* serviceInfor = serviceList[i];
		if (serviceInfor == NULL) {
			continue;
		}

		m_mutex.lock();
		CServicePtr servicePtr = serviceInfor->m_servicePtr ;
		m_mutex.unlock();

		if (servicePtr == NULL) {
			continue;
		}

		servicePtr->IService_sendMsg(a_msg, a_msgSize);
	}
	return true;
}

bool CServiceMgr::sendMsgToServerType(ServerType a_serverType, GFLib::CMessage& a_msg)
{
	BSLib::Utility::CHashMap< ServerType, std::vector< SServiceInfo* > >::iterator it_type;
	it_type = m_hashMapByServerType.find(a_serverType);
	if (it_type == m_hashMapByServerType.end()) {
		return true;
	}
	std::vector<SServiceInfo*>& serviceList = it_type->second;
	for (BSLib::uint32 i=0; i<serviceList.size(); ++i) {
		SServiceInfo* serviceInfor = serviceList[i];
		if (serviceInfor == NULL) {
			continue;
		}
		
		m_mutex.lock();
		CServicePtr servicePtr = serviceInfor->m_servicePtr ;
		m_mutex.unlock();

		if (servicePtr == NULL) {
			continue;
		}

		servicePtr->IService_sendMsg(a_msg);
	}
	return true;
}

SServerID CServiceMgr::getServerID(const std::string& a_serverKey)
{
	SServiceInfo* serviceInfor = NULL;
	m_hashMapByKeyName.getValue(a_serverKey, serviceInfor);
	if (serviceInfor == NULL) {
		return SServerID(0);
	}
	return serviceInfor->m_netInfor.m_serverID;
}

const std::string& CServiceMgr::getServerKey(SServerID a_serverID)
{
	static std::string tmp = "";

	SServiceInfo* serviceInfor = NULL;
	m_hashMapByServerID.getValue(a_serverID.getServerID(), serviceInfor);
	if (serviceInfor == NULL) {
		return tmp;
	}
	return serviceInfor->m_netInfor.m_key;
}

const SServiceNetInfo* CServiceMgr::getServerNetInfor(const std::string& a_serverKey)
{
	SServiceInfo* serviceInfor = NULL;
	m_hashMapByKeyName.getValue(a_serverKey, serviceInfor);
	return &serviceInfor->m_netInfor;
}

void CServiceMgr::traversal(BSLib::Utility::CHashMap<ServerID, SServiceInfo*>::CCallback& cb)
{
	m_hashMapByServerID.traversal(cb);
}

bool CServiceMgr::_loadConfigFile(const std::string& a_configFile)
{
	BSLib::Utility::CXmlFile xmlFile;
	if (!xmlFile.loadFile(a_configFile)) {
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "加载文件[%s]失败", a_configFile.c_str());
		return false;
	}
	BSLib::Utility::HXmlNode rootNode = xmlFile.getRootNode("config");
	if (rootNode == NULL) {
		BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "加载文件[%s]的config节点失败", a_configFile.c_str());
		xmlFile.clear();
		return false;
	}
	BSLib::Utility::HXmlNode node = xmlFile.getChildNode(rootNode);
	while (node != NULL){
		std::string nodeName;
		if (!xmlFile.getNodeName(node, nodeName)) {
			BSLIB_LOG_ERROR(ETT_GFLIB_COMMON, "加载文件[%s]的config字节名称失败", a_configFile.c_str());
			xmlFile.clear();
			return false;
		}
		if (nodeName == "global") {
			if (!loadGlobalNodes(xmlFile, node, m_hashMapByKeyName)) {
				BSLIB_LOG_TRACE(ETT_GFLIB_COMMON, "加载文件[%s]节点[%s]失败", a_configFile.c_str(), nodeName.c_str());
				xmlFile.clear();
				return false;
			}
		} else if (nodeName == "zone") {
			if (!loadZoneNodes(xmlFile, node, m_hashMapByKeyName)) {
				BSLIB_LOG_TRACE(ETT_GFLIB_COMMON, "加载文件[%s]节点[%s]失败", a_configFile.c_str(), nodeName.c_str());
				xmlFile.clear();
				return false;
			}
		}else {
			BSLIB_LOG_TRACE(ETT_GFLIB_COMMON, "加载文件[%s]节点[%s]失败", a_configFile.c_str(), nodeName.c_str());
		}
		node = xmlFile.getNextNode(node);
	}
	xmlFile.clear();
	return true;
}

bool CServiceMgr::_initServiceInfor()
{
	BSLib::Utility::CHashMap<std::string, SServiceInfo*>::iterator it_key = m_hashMapByKeyName.begin();
	for (; it_key != m_hashMapByKeyName.end(); ++it_key) {
		SServiceInfo* seviceInfor = it_key->second;
		if (seviceInfor == NULL) {
			return false;
		}
		if (m_hashMapByServerID.find(seviceInfor->m_netInfor.m_serverID.getServerID()) != m_hashMapByServerID.end()) {
			BSLIB_LOG_TRACE(ETT_GFLIB_COMMON, "服务器[%s]serverID重复", seviceInfor->m_netInfor.m_key.c_str());
			return false;
		}
		m_hashMapByServerID.setValue(seviceInfor->m_netInfor.m_serverID.getServerID(), seviceInfor);
		
		BSLib::Utility::CHashMap< ServerType, std::vector< SServiceInfo* > >::iterator it_type;
		it_type = m_hashMapByServerType.find(seviceInfor->m_netInfor.m_serverID.getServerType());
		if (it_type == m_hashMapByServerType.end()) {
			std::vector<SServiceInfo*> serviceList;
			serviceList.push_back(seviceInfor);
			m_hashMapByServerType.setValue(seviceInfor->m_netInfor.m_serverID.getServerType(), serviceList);
		} else {
			it_type->second.push_back(seviceInfor);
		}

		BSLib::Utility::CHashMap< ZoneID, std::vector< SServiceInfo* > >::iterator it_zone;
		it_zone = m_hashMapByZone.find(seviceInfor->m_netInfor.m_serverID.getZoneID());
		if (it_zone == m_hashMapByZone.end()) {
			std::vector<SServiceInfo*> serviceList;
			serviceList.push_back(seviceInfor);
			m_hashMapByZone.setValue(seviceInfor->m_netInfor.m_serverID.getZoneID(), serviceList);
		} else {
			it_zone->second.push_back(seviceInfor);
		}

		for (BSLib::uint32 i=0; i<seviceInfor->m_netInfor.m_connectorAddrList.size(); ++i) {
			SServiceNetConnectorInfo& connectInfor = seviceInfor->m_netInfor.m_connectorAddrList[i];

			SServiceInfo* connectServiceInfor = NULL;
			m_hashMapByKeyName.getValue(connectInfor.m_serverKey, connectServiceInfor);
			if (connectServiceInfor == NULL) {
				BSLIB_LOG_TRACE(ETT_GFLIB_COMMON, "服务器[%s]链接服务器[%s]不存在", seviceInfor->m_netInfor.m_key.c_str(), connectInfor.m_serverKey.c_str());
				return false;
			}
			BSLib::uint32 netIP = connectServiceInfor->m_netInfor.m_innerAddr.getNetIP();
			BSLib::uint16 port = 0;
			for (BSLib::uint32 j=0; connectServiceInfor->m_netInfor.m_listenerAddrList.size(); ++j) {
				if (connectServiceInfor->m_netInfor.m_listenerAddrList[j].m_flag == connectInfor.m_flag){
					port = connectServiceInfor->m_netInfor.m_listenerAddrList[j].m_listenerAddr.getPort();
					break;
				}
			}
			if (port == 0) {
				BSLIB_LOG_TRACE(ETT_GFLIB_COMMON, "服务器[%s]链接服务器[%s]端口无效", seviceInfor->m_netInfor.m_key.c_str(), connectInfor.m_serverKey.c_str());
				return false;
			}
			connectInfor.m_connectorAddr.setIPAndPort(netIP, port);
		}
	}
	return true;
}

}//CommonServer

}//GFLib


