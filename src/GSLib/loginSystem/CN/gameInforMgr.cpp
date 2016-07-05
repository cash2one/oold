#include "CN/gameInforMgr.h"

#define GAME_ACCOUNT_MAX (20000)

namespace GSLib
{

namespace LoginSystem
{

namespace CN
{

class CGameServiceMgrCallback : public BSLib::Utility::CHashMap<GFLib::ServerID, GFLib::CommonServer::SServiceInfo*>::CCallback
{
public:
	CGameServiceMgrCallback(std::vector<SGameInfor>* gameOnlineInforHashMap)
		: m_gameOnlineInforHashMap(gameOnlineInforHashMap)
	{
		;
	}
	virtual bool exec(const GFLib::ServerID& _key, GFLib::CommonServer::SServiceInfo*& _value)
	{
		GFLib::SServerID serverID(_key);

		if (serverID.getZoneID() == 0) {
			return true;
		}
		if (serverID.getServerType() != SRVTYPE_GAMESERVER) {
			return true;
		}

		SGameInfor gameInfor;
		gameInfor.m_gameServerID = serverID;
		gameInfor.m_isRunning = false;
		gameInfor.m_onlineCount = 0;

		m_gameOnlineInforHashMap->push_back(gameInfor);
		return true;
	}

private:
	std::vector<SGameInfor>* m_gameOnlineInforHashMap;
};

//////////////////////////////////////////////////////////////////////////
BSLIB_SINGLETON_DEFINE(CGameInforMgr);

CGameInforMgr::CGameInforMgr()
{
	;
}

CGameInforMgr::~CGameInforMgr()
{
	;
}

void CGameInforMgr::init()
{
	CGameServiceMgrCallback serviceMgrCb(&m_gameOnlineInforHashMap);

	GFLib::CommonServer::CServiceMgr::singleton().traversal(serviceMgrCb);
}

void CGameInforMgr::final()
{
	m_gameOnlineInforHashMap.clear();
}

void CGameInforMgr::gameServerEnter(const GFLib::SServerID& a_serverID)
{
	std::vector<SGameInfor>::iterator it = m_gameOnlineInforHashMap.begin();
	for (; it != m_gameOnlineInforHashMap.end(); ++it) {
		SGameInfor& gameInfor = *it;
		if (gameInfor.m_gameServerID == a_serverID) {
			gameInfor.m_isRunning = true;
			return;
		}
	}
}

void CGameInforMgr::gameServerLeave(const GFLib::SServerID& a_serverID)
{
	std::vector<SGameInfor>::iterator it = m_gameOnlineInforHashMap.begin();
	for (; it != m_gameOnlineInforHashMap.end(); ++it) {
		SGameInfor& gameInfor = *it;
		if (gameInfor.m_gameServerID == a_serverID) {
			gameInfor.m_isRunning = false;
			gameInfor.m_onlineCount = 0;
			return;
		}
	}
}

bool CGameInforMgr::increaseAccountToGameServer(GFLib::SServerID& a_gameServerID)
{
	a_gameServerID.setServerID(GFLib::INVALID_SERVERID);

	std::vector<SGameInfor>::iterator it = m_gameOnlineInforHashMap.begin();
	for (; it != m_gameOnlineInforHashMap.end(); ++it) {
		SGameInfor& gameInfor = *it;
		if (!gameInfor.m_isRunning) {
			continue;
		}
		if (gameInfor.m_onlineCount  < GAME_ACCOUNT_MAX){
			a_gameServerID = gameInfor.m_gameServerID;
			gameInfor.m_onlineCount += 1;
		}
	}
	return a_gameServerID.isValid();
}

void CGameInforMgr::decreaseAccountFromGameServer(GFLib::SServerID& a_gameServerID)
{
	std::vector<SGameInfor>::iterator it = m_gameOnlineInforHashMap.begin();
	for (; it != m_gameOnlineInforHashMap.end(); ++it) {
		SGameInfor& gameInfor = *it;
		if (!gameInfor.m_isRunning) {
			continue;
		}
		if (gameInfor.m_gameServerID != a_gameServerID) {
			continue;
		}
		if (gameInfor.m_onlineCount >= 0) {
			gameInfor.m_onlineCount -= 1;
		}
		return ;
	}
}

}//CN

}//LoginSystem

}//GSLib
