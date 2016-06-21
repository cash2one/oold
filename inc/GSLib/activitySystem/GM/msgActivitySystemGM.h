#ifndef __GSLIB_ACTIVITYSYSTEM_MSGACTIVITYSYSTEMGM_H__
#define __GSLIB_ACTIVITYSYSTEM_MSGACTIVITYSYSTEMGM_H__

#include <GSLib/activitySystem/msgNumIDActivitySystem.h>
#include <GSLib/activitySystem/msgActivitySystem.h>
#include <GSLib/activitySystem/GM/activitySystemDefine.h>

namespace GSLib
{

namespace ActivitySystem
{	
	const BSLib::uint32 MsgIDActivitySystemGC2GMReqGetAttendenceData = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_ACTIVITYSYSTEM, EMSGNUMID_ACTIVITYSYSTEM_GC2GM_REQ_GET_ATTENDENCE_DATA);
	class CMsgActivitySystemGC2GMReqGetAttendenceData : public GFLib::CMessage
	{
	public:
		CMsgActivitySystemGC2GMReqGetAttendenceData() : GFLib::CMessage(MsgIDActivitySystemGC2GMReqGetAttendenceData)
		{
		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{
			return true;
		}

	};                     

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDActivitySystemGC2GMReqSignIn = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_ACTIVITYSYSTEM, EMSGNUMID_ACTIVITYSYSTEM_GC2GM_REQ_SGIN_IN);
	class CMsgActivitySystemGC2GMReqSignIn : public GFLib::CMessage
	{
	public:
		CMsgActivitySystemGC2GMReqSignIn() : GFLib::CMessage(MsgIDActivitySystemGC2GMReqSignIn)
		{
		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{
			return true;
		}
	};                     

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDActivitySystemGC2GMReqDrawCard = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_ACTIVITYSYSTEM, EMSGNUMID_ACTIVITYSYSTEM_GC2GM_REQ_DRAW_CARD);
	class CMsgActivitySystemGC2GMReqDrawCard : public GFLib::CMessage
	{
	public:
		CMsgActivitySystemGC2GMReqDrawCard() 
		:GFLib::CMessage(MsgIDActivitySystemGC2GMReqDrawCard)
		,m_type(GM::DRAW_CARD_TYPE_GOLD)
		,m_count(0)
		{
		}
	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{
			BSLib::int8 type = 0;
			stream >> type;
			m_type = (GM::EDrawCardType)type;
			stream >> m_count;
			return true;
		}
	public:
		GM::EDrawCardType m_type;
		BSLib::uint16 m_count;
	};                     

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const BSLib::uint32 MsgIDActivitySystemGC2GMReqGetDrawCardInfo = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_ACTIVITYSYSTEM, EMSGNUMID_ACTIVITYSYSTEM_GC2GM_REQ_GET_DRAW_CARD_INFO);
	class CMsgActivitySystemGC2GMReqGetDrawCardInfo : public GFLib::CMessage
	{
	public:
		CMsgActivitySystemGC2GMReqGetDrawCardInfo() : GFLib::CMessage(MsgIDActivitySystemGC2GMReqGetDrawCardInfo)
		{
		}

	protected:
		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{
			return true;
		}

	};                     

}

}//GSLib

#endif

