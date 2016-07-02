#ifndef __SERVER_GAMESERVER_GAMESERVER_H__
#define __SERVER_GAMESERVER_GAMESERVER_H__

#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonServer.h>

class CGameServer : public GFLib::CommonServer::ICommonServer
{
public:
	CGameServer();
	virtual ~CGameServer();

	BSLIB_SINGLETON_DECLARE(CGameServer);

	virtual GFLib::ServerType ICommonServer_getServerType();
	virtual std::string ICommonServer_getServerVersion();

public:
	static int main();

protected:
	virtual bool _IThread_init();
	virtual bool _IThread_callback();
	virtual int _IThread_final();
	virtual bool ICommonServer_initSystem(GFLib::CommonServer::CCommonSystemMgr* commanSystemMgr);

	virtual bool ICommonServer_loadGameConfig(const std::string& a_configPath);
	virtual void ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	virtual void ICommonServer_cbServerEnter(GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonServer_cbServerLeave(GFLib::SServerID& a_serverID, const std::string& a_key);

	virtual GFLib::CommonServer::CCommonClientPtr _ICommonServer_cbCreateClient(GFLib::SServerID& a_serverID, const std::string& a_serverKey);
	virtual BSLib::Network::CNetStubPtr _INetServer_cbNewTcpStub(BSLib::Network::CNetConnectionPtr& netConnPtr, void* tempData);

private:
	//BSLib::int64 m_lastMilliseconds;
};

#endif//__SERVER_GAMESERVER_GAMESERVER_H__

