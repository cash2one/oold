#ifndef __GFLIB_COMMONSERVER_SERVICEMGR_H__
#define __GFLIB_COMMONSERVER_SERVICEMGR_H__

#include <GFLib/commonServer/service.h>

#define GFLIB_SERVERTYPE_COUNT (BSLIB_UINT8_MAX + 1)

namespace GFLib
{

namespace CommonServer
{

struct SServiceNetListenerInfo
{
	BSLib::Network::CSockAddr m_listenerAddr;
	BSLib::int32 m_flag;
	bool m_outer;
};

struct SServiceNetConnectorInfo
{
	std::string m_serverKey;
	BSLib::Network::CSockAddr m_connectorAddr;
	BSLib::int32 m_flag;
	bool m_reconnect;
	bool m_terminateServer;
	bool m_needPing;
};

struct SServiceNetInfo
{
	SServerID m_serverID;
	std::string m_key;
	BSLib::Network::CSockAddr m_outerAddr;
	BSLib::Network::CSockAddr m_innerAddr;
	std::vector<SServiceNetListenerInfo> m_listenerAddrList;
	std::vector<SServiceNetConnectorInfo> m_connectorAddrList;
};


struct SServiceInfo
{
	SServiceInfo() : m_servicePtr(NULL), m_state(0) {}

	SServiceNetInfo m_netInfor;
	IServicePtr m_servicePtr;
	BSLib::uint8 m_state;
};

class GFLIB_COMMONSERVER_API CServiceMgr
{
public:
	CServiceMgr();
	virtual ~CServiceMgr();

	BSLIB_SINGLETON_DECLARE(CServiceMgr);

	bool loadConfig(const std::string& a_configFile);

	bool addService(IServicePtr& a_service);
	bool delService(SServerID a_serverID);
	void freeService(SServerID a_serverID);

	void closeAll();

	bool sendMsgToServer(const std::string& a_serverKey, GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize);
	bool sendMsgToServer(const std::string& a_serverKey, GFLib::CMessage& a_msg);
	bool sendMsgToServer(const ServerID& a_serverID, GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize);
	bool sendMsgToServer(const ServerID& a_serverID, GFLib::CMessage& a_msg);

	bool sendMsgToServer(const SServerID& a_serverID, GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize);
	bool sendMsgToServer(const SServerID& a_serverID, GFLib::CMessage& a_msg);

	bool sendMsgToServer(const SServerID& a_serverID, const SAccountKey& a_accountKey, GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize);
	bool sendMsgToServer(const SServerID& a_serverID, const SAccountKey& a_accountKey, GFLib::CMessage& a_msg);

	bool sendMsgToServerType(ServerType a_serverType, GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize);
	bool sendMsgToServerType(ServerType a_serverType, GFLib::CMessage& a_msg);

	SServerID getServerID(const std::string& a_serverKey);
	const std::string& getServerKey(SServerID a_serverID);

	const SServiceNetInfo* getServerNetInfor(const std::string& a_serverKey);

	void traversal(BSLib::Utility::CHashMap<ServerID, SServiceInfo*>::CCallback& cb);

protected:
	bool _loadConfigFile(const std::string& a_configFile);
	bool _initServiceInfor();

private:
	BSLib::Utility::CHashMap<std::string, SServiceInfo*> m_hashMapByKeyName;
	BSLib::Utility::CHashMap<ServerID, SServiceInfo*> m_hashMapByServerID;
	BSLib::Utility::CHashMap<ServerType, std::vector< SServiceInfo* > > m_hashMapByServerType;
	BSLib::Utility::CHashMap<ZoneID, std::vector< SServiceInfo*> > m_hashMapByZone;
	BSLib::Utility::CMutex m_mutex;
};

}//CommonServer

}//GFLib

#endif//__GFLIB_COMMONSERVER_SERVICEMGR_H__




