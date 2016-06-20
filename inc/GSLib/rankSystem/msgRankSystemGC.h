//////////////////////////////////////////////////////////////////////
//	created:	2014/10/23
//	filename: 	GSLib\chatSystem\msgChatSystemGC.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_RANKSYSTEM_MSGRANKSYSTEMGC_H__
#define __GSLIB_RANKSYSTEM_MSGRANKSYSTEMGC_H__

#include <GSLib/rankSystem/msgNumIDRankSystem.h>
#include <BSLib/utility/baseDef.h>
#include <GSLib/rankSystem/rankSystemError.h>
#include <GSLib/rankSystem/GM/rankData.h>
#include <GSLib/rankSystem/cmmhdr.h>

namespace GSLib
{

namespace RankSystem
{

const BSLib::uint32 MsgIDRankSystemCN2GCAckGetRankList = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_RANKSYSTEM, EMSGNUMID_RANKSYSTEM_CN2GC_ACK_GET_RANK_LIST);
class CMsgRankSystemCN2GCAckGetRankList: public GFLib::CMessage
{
public:
	CMsgRankSystemCN2GCAckGetRankList() 
	:GFLib::CMessage(MsgIDRankSystemCN2GCAckGetRankList)
	{
		;
	}
protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{	
		stream << m_id;
		stream << m_type;

		BSLib::uint32 size = m_list.size();
		stream << size;
		std::vector<SRankCell>::const_iterator it = m_list.begin();
		for(; it != m_list.end(); ++it)
		{
			(*it)._serializeTo(stream);
		}

		return true;
	}

public:
	BSLib::uint32 m_id;		// 排行榜id
	BSLib::uint32 m_type;	// 1: 获取排行榜列表, 2:获取自己的位置
	std::vector<SRankCell> m_list;
};

}//RankSystem

}//GSLib

#endif//__GSLIB_RANKSYSTEM_MSGRANKSYSTEMGC_H__
