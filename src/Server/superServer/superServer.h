//////////////////////////////////////////////////////////////////////
//	created:	2014/12/10
//	filename: 	src\Server\superServer\superServer.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __SERVER_SUPERSERVER_SUPERSERVER_H__
#define __SERVER_SUPERSERVER_SUPERSERVER_H__

#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonServer.h>
#include <GSLib/masterSystem/msgMasterSystem.h>

class CSuperServer : public GFLib::CommonServer::CCommonServer
{
public:
	CSuperServer();
	virtual ~CSuperServer();

	BSLIB_SINGLETON_DECLARE(CSuperServer);

	virtual GFLib::ServerType getServerType();
	virtual std::string getServerVersion();
public:
	static int main();

protected:
	virtual bool _init();
	virtual bool _callback();
	virtual int _final();

	virtual bool _initSystem(GFLib::CommonServer::CCommonSystemMgr* commanSystemMgr);

	virtual bool _loadGameConfig(const std::string& a_configPath);
	virtual void _initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	
	virtual void _cbServerEnter(GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void _cbServerLeave(GFLib::SServerID& a_serverID, const std::string& a_key);

	virtual GFLib::CommonServer::CCommonClientPtr _cbCreateClient(GFLib::SServerID& a_serverID, const std::string& a_serverKey);
	virtual BSLib::Network::CNetStubPtr _cbNewTcpStub(BSLib::Network::CNetConnectionPtr& netConnPtr, void* tempData);

public:
	std::map<std::string, GFLib::SServerID> m_cnServers;

};

#endif//__SERVER_SUPERSERVER_SUPERSERVER_H__
