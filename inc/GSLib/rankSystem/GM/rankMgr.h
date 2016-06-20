//////////////////////////////////////////////////////////////////////
//	created:	2014/11/3
//	filename: 	GSLib\rankSystem\GM\rankMgr.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef	__GSLIB_RANKSYSTEM_RANKMGR_H__
#define __GSLIB_RANKSYSTEM_RANKMGR_H__

#include <vector>
#include <BSLib/utility/baseDef.h>
#include <GSLib/baseDef.h>
#include <GSLib/rankSystem/GM/rankData.h>
#include <BSLib/utility/singleton.h>

namespace GSLib
{

namespace RankSystem
{

namespace GM
{

class CRankMgr
{
public:
	BSLIB_SINGLETON_DECLARE(CRankMgr);
public:
	CRankMgr();
	~CRankMgr();
public:
	BSLib::uint32 getRoleArenaRank(BSLib::int16 a_zoneID, GFLib::AccountID a_accountID, BSLib::uint32 a_roleIndex) const;
	const std::vector<CRankData> & getArenaRankData() const;
	void initArenaRankData();
	void onArenaRankChanged(BSLib::uint32 a_pos1, BSLib::uint32 a_pos2);
public:
	std::vector<CRankData> m_vecArenaRankData;
};
}


}//RankSystem

}//GSLib

#endif//__GSLIB_RANKSYSTEM_RANKMGR_H__













