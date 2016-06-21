#ifndef __GSLIB_LOGINSYSTEM_CN_GAMEINFORMGR_H__
#define __GSLIB_LOGINSYSTEM_CN_GAMEINFORMGR_H__

#include <GFLib/commonServer/serviceMgr.h>
#include <GSLib/loginSystem/msgLoginSystem.h>

namespace GSLib
{

namespace LoginSystem
{

namespace CN
{

struct SGameInfor
{
	GFLib::SServerID m_gameServerID;
	BSLib::uint32 m_onlineCount;
	bool m_isRunning;
};

class CGameInforMgr
{
public:
	CGameInforMgr();
	~CGameInforMgr();

	BSLIB_SINGLETON_DECLARE(CGameInforMgr);

	void init();
	void final();

	void gameServerEnter(const GFLib::SServerID& a_serverID);
	void gameServerLeave(const GFLib::SServerID& a_serverID);

	bool increaseAccountToGameServer(GFLib::SServerID& a_gameServerID);
	void decreaseAccountFromGameServer(GFLib::SServerID& a_gameServerID);

private:
	std::vector<SGameInfor> m_gameOnlineInforHashMap;
};

}//CN

}//LoginSystem

}//GSLib


#endif//__GSLIB_LOGINSYSTEM_CN_GAMEINFORMGR_H__
