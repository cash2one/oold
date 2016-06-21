#ifndef __GSLIB_RANKSYSTEM_MSGRANKSYSTEMGM_H__
#define __GSLIB_RANKSYSTEM_MSGRANKSYSTEMGM_H__

#include <GSLib/rankSystem/msgNumIDRankSystem.h>

namespace GSLib
{

namespace RankSystem
{
	const BSLib::uint32 MsgIDRankSystemCN2GMNtfPlace = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_RANKSYSTEM, EMSGNUMID_RANKSYSTEM_CN2GM_NTF_PLACE);
	class CMsgRankSystemCN2GMNtfPlace: public GFLib::CMessage
	{
	public:
		CMsgRankSystemCN2GMNtfPlace() 
			:GFLib::CMessage(MsgIDRankSystemCN2GMNtfPlace)
		{
			;
		}
	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{	
			stream << m_id;
			stream << m_place;
			return true;
		}

		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{
			stream >> m_id;
			stream >> m_place;
			return true;
		}

	public:
		BSLib::uint32 m_id;		// ≈≈––∞Òid
		BSLib::uint32 m_place;	// Œª÷√
	};

}//RankSystem

}//GSLib

#endif//__GSLIB_RANKSYSTEM_MSGRANKSYSTEMGM_H__

