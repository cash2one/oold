#ifndef __SERVER_SUPERSERVER_SUPERSERVER_H__
#define __SERVER_SUPERSERVER_SUPERSERVER_H__

#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonServer.h>
#include <GSLib/masterSystem/msgMasterSystem.h>

class CSuperServer : public GFLib::CommonServer::ICommonServer
{
public:
	CSuperServer();
	virtual ~CSuperServer();

	BSLIB_SINGLETON_DECLARE(CSuperServer);

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

	virtual GFLib::CommonServer::CCommonClientPtr _ICommonServer_cbCreateClient(GFLib::SServerID& a_serverID, const std::string& a_serverKey) override;
	virtual BSLib::Network::CNetStubPtr _INetServer_cbNewTcpStub(BSLib::Network::CNetConnectionPtr& netConnPtr, void* tempData) override;

public:
	std::map<std::string, GFLib::SServerID> m_cnServers;

};

#endif//__SERVER_SUPERSERVER_SUPERSERVER_H__

