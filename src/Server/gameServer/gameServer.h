//////////////////////////////////////////////////////////////////////
//	created:	2014/07/09
//	filename:	src\Server\gameServer\gameServer.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __SERVER_GAMESERVER_GAMESERVER_H__
#define __SERVER_GAMESERVER_GAMESERVER_H__

#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonServer.h>

class CGameServer : public GFLib::CommonServer::CCommonServer
{
public:
	CGameServer();
	virtual ~CGameServer();

	BSLIB_SINGLETON_DECLARE(CGameServer);

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

private:
	//BSLib::int64 m_lastMilliseconds;
};

#endif//__SERVER_GAMESERVER_GAMESERVER_H__
