#ifndef __SERVER_LOGINSERVER_LOGINSERVER_H__
#define __SERVER_LOGINSERVER_LOGINSERVER_H__

#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonServer.h>

class CLoginServer : public GFLib::CommonServer::CCommonServer
{
public:
	CLoginServer();
	virtual ~CLoginServer();

	BSLIB_SINGLETON_DECLARE(CLoginServer);

	virtual GFLib::ServerType getServerType();
	virtual std::string getServerVersion();

public:
	static int main();

protected:
	virtual bool _init();
	virtual int _final();

	virtual bool _initSystem(GFLib::CommonServer::CCommonSystemMgr* commanSystemMgr);

	virtual bool _loadGameConfig(const std::string& a_configPath);
	virtual void _initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	
	virtual void _cbServerEnter(GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void _cbServerLeave(GFLib::SServerID& a_serverID, const std::string& a_key);

	virtual GFLib::CommonServer::CCommonClientPtr _cbCreateClient(GFLib::SServerID& a_serverID, const std::string& a_serverKey);
	virtual BSLib::Network::CNetStubPtr _cbNewTcpStub(BSLib::Network::CNetConnectionPtr& netConnPtr, void* tempData);

private:
	void _onMsgServerLinkGT2LCNtfGateInfor(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg);
};

#endif//__SERVER_LOGINSERVER_LOGINSERVER_H__

