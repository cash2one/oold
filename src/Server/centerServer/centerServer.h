//////////////////////////////////////////////////////////////////////
//	created:	2014/07/17
//	filename: 	src\Server\centerServer\centerServer.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __SERVER_CENTERSERVER_CENTERSERVER_H__
#define __SERVER_CENTERSERVER_CENTERSERVER_H__

#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonServer.h>

class CCenterServer : public GFLib::CommonServer::CCommonServer
{
public:
	CCenterServer();
	virtual ~CCenterServer();

	BSLIB_SINGLETON_DECLARE(CCenterServer);

	virtual GFLib::ServerType getServerType();
	virtual std::string getServerVersion();

public:
	static int main();

protected:
	virtual int _final();

	virtual bool _initSystem(GFLib::CommonServer::CCommonSystemMgr* commanSystemMgr);

	virtual bool _loadGameConfig(const std::string& a_configPath);
	virtual void _initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	virtual void _cbServerEnter(GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void _cbServerLeave(GFLib::SServerID& a_serverID, const std::string& a_key);

	virtual GFLib::CommonServer::CCommonClientPtr _cbCreateClient(GFLib::SServerID& a_serverID, const std::string& a_serverKey);
	virtual BSLib::Network::CNetStubPtr _cbNewTcpStub(BSLib::Network::CNetConnectionPtr& netConnPtr, void* tempData);
};

#endif//__SERVER_CENTERSERVER_CENTERSERVER_H__
