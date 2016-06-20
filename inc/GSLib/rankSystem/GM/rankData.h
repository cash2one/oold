//////////////////////////////////////////////////////////////////////
//	created:	2014/11/3
//	filename: 	GSLib\rankSystem\GM\rankData.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_RANKSYSTEM_RANKDATA_H__
#define __GSLIB_RANKSYSTEM_RANKDATA_H__

#include <BSLib/utility/baseDef.h>
#include <GSLib/baseDef.h>

namespace GSLib
{

namespace RankSystem
{
namespace GM
{

class CRankData
{
public:
	CRankData();
	~CRankData();
public:
	void serializeTo(BSLib::Utility::CStream & a_stream) const;
public:
	BSLib::uint16 m_zoneID;
	GFLib::AccountID m_accountID;
	BSLib::uint32 m_roleIndex;
	BSLib::uint32 m_roleTPID;
	std::string m_roleName;
	BSLib::uint32 m_rank;
	BSLib::uint32 m_level;
	BSLib::uint32 m_combatPower;
};

}



}//RankSystem

}//GSLib

#endif//__GSLIB_RANKSYSTEM_RANKDATA_H__
