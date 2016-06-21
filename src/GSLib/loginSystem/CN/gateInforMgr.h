#ifndef __GSLIB_LOGINSYSTEM_CN_GATEINFORMGR_H__
#define __GSLIB_LOGINSYSTEM_CN_GATEINFORMGR_H__

#include <GFLib/commonServer/serviceMgr.h>
#include <GSLib/loginSystem/msgLoginSystem.h>

namespace GSLib
{

namespace LoginSystem
{

namespace CN
{

struct SGateInfor
{
	GFLib::SServerID m_gateServerID;
	BSLib::Network::CSockAddr m_connectAddr;
	BSLib::uint32 m_onlineCount;
	BSLib::uint32 m_waitCount;
	bool m_isRunning;
};

class CGateInforMgr
{
public:
	CGateInforMgr();
	~CGateInforMgr();

	BSLIB_SINGLETON_DECLARE(CGateInforMgr);

	void init();
	void final();

	void gateServerEnter(const GFLib::SServerID& a_serverID);
	void gateServerLeave(const GFLib::SServerID& a_serverID);

	BSLib::Network::CSockAddr& getGateConnectAddr(GFLib::SServerID& a_gateServerID);

	bool increaseAccountToGateServer(GFLib::SServerID& a_gateServerID);

	void increaseOnlineAccountFromGateServer(GFLib::SServerID& a_gateServerID);
	void increaseWaitAccountFromGateServer(GFLib::SServerID& a_gateServerID);
	void decreaseOnlineAccountFromGateServer(GFLib::SServerID& a_gateServerID);
	void decreaseWaitAccountFromGateServer(GFLib::SServerID& a_gateServerID);

private:
	std::vector<SGateInfor> m_gateOnlineInforHashMap;

};

}//CN

}//LoginSystem

}//GSLib


#endif//__GSLIB_LOGINSYSTEM_CN_GATEINFORMGR_H__
