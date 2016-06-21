#ifndef __SERVER_DATASERVER_DATASERVER_H__
#define __SERVER_DATASERVER_DATASERVER_H__

#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonServer.h>

class CDataServer : public GFLib::CommonServer::CCommonServer
{
public:
	CDataServer();
	virtual ~CDataServer();

	BSLIB_SINGLETON_DECLARE(CDataServer);

	virtual GFLib::ServerType getServerType();
	virtual std::string getServerVersion();

public:
	static int main();

protected:
	virtual int _final();
	virtual bool _initSystem(GFLib::CommonServer::CCommonSystemMgr* commanSystemMgr);

	virtual bool _loadGameConfig(const std::string& a_configPath);
	virtual void _initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual GFLib::CommonServer::CCommonClientPtr _cbCreateClient(GFLib::SServerID& a_serverID, const std::string& a_serverKey);
	virtual BSLib::Network::CNetStubPtr _cbNewTcpStub(BSLib::Network::CNetConnectionPtr& netConnPtr, void* tempData);
};

#endif//__SERVER_DATASERVER_DATASERVER_H__

