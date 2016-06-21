#include <GSLib/rankSystem/GM/rankMgr.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/playerSystem/GM/playerGMMgr.h>

namespace GSLib
{

namespace RankSystem
{

namespace GM
{

CRankMgr::CRankMgr()
{
}

CRankMgr::~CRankMgr()
{

}

BSLIB_SINGLETON_DEFINE(CRankMgr)

BSLib::uint32 CRankMgr::getRoleArenaRank(BSLib::int16 a_zoneID, GFLib::AccountID a_accountID, BSLib::uint32 a_roleIndex) const
{
	for (std::vector<CRankData>::size_type i = 0; i < m_vecArenaRankData.size(); ++i) {
		if (m_vecArenaRankData[i].m_zoneID == a_zoneID && m_vecArenaRankData[i].m_accountID == a_accountID && m_vecArenaRankData[i].m_roleIndex == a_roleIndex) {
			return m_vecArenaRankData[i].m_rank;
		}
	}

	return 10001;
}

const std::vector<CRankData> & CRankMgr::getArenaRankData() const
{
	return m_vecArenaRankData;
}

void CRankMgr::initArenaRankData()
{
	std::list<GSLib::PlayerSystem::GM::CRoleGM*> listRoleGM;
	GSLib::PlayerSystem::GM::CPlayerGMMgr::singleton().getAllRoleGM(listRoleGM);
	for (std::list<GSLib::PlayerSystem::GM::CRoleGM*>::iterator itr = listRoleGM.begin(); itr != listRoleGM.end(); ++itr) {
		GSLib::PlayerSystem::GM::CRoleGM *role = *itr;
		bool isInList = false;
		if (role != NULL) {
			for (std::vector<CRankData>::iterator itr = m_vecArenaRankData.begin(); itr != m_vecArenaRankData.end(); ++itr) {
				if (role->getZoneID() == itr->m_zoneID && role->getAccountID() == itr->m_accountID && role->getRoleIndex() == (BSLib::int32)itr->m_roleIndex) {
					isInList = true;
					break;
				}
			}
			if (isInList) {
				continue;
			}
			CRankData rankData;
			rankData.m_zoneID = role->getPlayerGM()->getZoneID();
			rankData.m_accountID = role->getPlayerGM()->getAccountID();
			rankData.m_roleIndex = role->getRoleIndex();
			rankData.m_roleName = role->getName();
			rankData.m_roleTPID = role->getTPID();
			rankData.m_level = role->getLevel();
			rankData.m_rank = (BSLib::uint32)m_vecArenaRankData.size() + 1;
			rankData.m_combatPower = role->getCombat();

			m_vecArenaRankData.push_back(rankData);
		}
	}
}

void CRankMgr::onArenaRankChanged(BSLib::uint32 a_pos1, BSLib::uint32 a_pos2)
{
	if (a_pos1 == a_pos2) {
		return;
	}
	if (a_pos1 >= m_vecArenaRankData.size() || a_pos2 >= m_vecArenaRankData.size()) {
		return;
	}

	CRankData rankData = m_vecArenaRankData[a_pos1];
	m_vecArenaRankData[a_pos1] = m_vecArenaRankData[a_pos2];
	m_vecArenaRankData[a_pos2]= rankData;
	m_vecArenaRankData[a_pos1].m_rank = a_pos1 + 1;
	m_vecArenaRankData[a_pos2].m_rank = a_pos2 + 1;
}


}//GM

}//RankSystem

}//GSLib

