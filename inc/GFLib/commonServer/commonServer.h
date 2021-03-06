#ifndef __GFLIB_COMMONSERVER_COMMONSERVER_H__
#define __GFLIB_COMMONSERVER_COMMONSERVER_H__

#include <BSLib/utility/cmdExecMgr.h>
#include <BSLib/network/netServer.h>
#include <BSLib/framework/mainThread.h>
#include <GFLib/commonServer/baseDef.h>
#include <GFLib/commonServer/clientMgr.h>
#include <GFLib/commonServer/commonSystemMgr.h>

namespace GFLib
{

namespace CommonServer
{

struct SAcceptorIPAndPort;

class GFLIB_COMMONSERVER_API ICommonServer 
    : public BSLib::Framework::CMainThread
    , public BSLib::Network::INetServer
{
public:
	ICommonServer();
	virtual ~ICommonServer();

	SServerID getServerID() { return m_serverID; }
	const std::string getServerKey() { return m_key; }

	virtual ServerType ICommonServer_getServerType() = 0;
	virtual std::string ICommonServer_getServerVersion() = 0;
	const std::string& getServerTypeName();

	BSLib::Utility::CCmdExecMgr* getCmdExecMgr() { return _getCmdExecMgr(); }

	bool getNeedPing() { return m_needPing; }

protected:
	virtual bool _IThread_init() override;
	virtual int _IThread_final() override;

	virtual bool _IThread_callback() override;
	//virtual void _update_1000();
	
	//初始化服务器
	//ServerID 和 ServerKey
	virtual bool ICommonServer_initServer();

	virtual bool ICommonServer_initSystem(CCommonSystemMgr* commanSystemMgr);

	//加载游戏配置文件
	virtual bool ICommonServer_loadGameConfig(const std::string& a_configPath);

	//服务器消息初始化
	virtual void ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	virtual void ICommonServer_cbServerEnter(SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonServer_cbServerLeave(SServerID& a_serverID, const std::string& a_key);

	void _setKey(const std::string& a_key) { m_key = a_key; }
	void _setServerID(SServerID a_serverID) { m_serverID = a_serverID; }

	bool _addAcceptorIPAndPort(BSLib::Network::ENetType netType, const BSLib::Network::CSockAddr& acceptorAddr, void* tempData);
	bool _addAcceptorIPAndPort(BSLib::Network::ENetType netType, const std::string& acceptorIP, int acceptorPort, void* tempData);

	BSLib::Utility::CCmdExecMgr* _getCmdExecMgr() { return &m_cmdExecMgr; }

	virtual BSLib::Network::CNetStubMgr* _INetServer_cbNetStubMgr();
	virtual BSLib::Network::CNetStubPtr _INetServer_cbNewTcpStub(BSLib::Network::CNetConnectionPtr& netConnPtr, void* tempData);
	virtual BSLib::Network::CNetStubPtr _INetServer_cbNewUdpStub(BSLib::Network::CNetConnectionPtr& netConnPtr, void* tempData);
	virtual CCommonClientPtr _ICommonServer_cbCreateClient(SServerID& a_serverID, const std::string& a_serverKey);

protected:
	bool _loadInitConfigFile();
	bool _loadNetConfigFile();
	void _setOutConsole();
	void _setOutTrace();
	void _changeLogFile();
	void _closeTrace();

	bool _connectServer();
	bool _openNetServer();

private:
	void _onMsgSysChannelLC2LCReqServerInfo(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework:: SMessage* msg);
	void _onMsgSysChannelLC2LCNtfCommand(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework:: SMessage* msg);
	void _onMsgServerLocalLC2LCNtfServerEnter(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework:: SMessage* msg);
	void _onMsgServerLocalLC2LCNtfServerLeave(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework:: SMessage* msg);
	void _onMsgServerLocalLC2LCNtfCommand(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework:: SMessage* msg);

public:
	static ICommonServer* getCommonServer() { return (ICommonServer*)BSLib::Framework::CMainThread::getMainThread(); }

private:
	std::string m_key;
	SServerID m_serverID;
	std::vector<SAcceptorIPAndPort*> m_acceptorIPAndPorts;
	BSLib::Utility::CCmdExecMgr m_cmdExecMgr;

	bool m_needPing;
};

}//CommonServer

}//GFLib

#endif//__GFLIB_COMMONSERVER_COMMONSERVER_H__




