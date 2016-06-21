#ifndef __GSLIB_ACTIVITYSYSTEM_MSGACTIVITYSYSTEMGC_H__
#define __GSLIB_ACTIVITYSYSTEM_MSGACTIVITYSYSTEMGC_H__

#include <GSLib/activitySystem/msgNumIDActivitySystem.h>
#include <GSLib/activitySystem/GM/activitySystemError.h>
#include <GSLib/activitySystem/GM/activityData.h>

namespace GSLib
{

namespace ActivitySystem
{	
const BSLib::uint32 MsgIDActivitySystemGM2GCAckGetAttendenceData = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_ACTIVITYSYSTEM, EMSGNUMID_ACTIVITYSYSTEM_GM2GC_ACK_GET_ATTENDENCE_DATA);
class CMsgActivitySystemGM2GCAckGetAttendenceData: public GFLib::CMessage
{
public:
	CMsgActivitySystemGM2GCAckGetAttendenceData() 
	:GFLib::CMessage(MsgIDActivitySystemGM2GCAckGetAttendenceData)
	,m_result(GM::EGET_ATTENDENCE_DATA_RESULT_FAIL)
	,m_startTime(0)
	,m_endTime(0)
	,m_attendenceCount(0)
	,m_attendenceAttrMap(NULL)
	{
	}
protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << (BSLib::int8)m_result;
		stream << m_startTime;
		stream << m_endTime;
		stream << m_attendenceCount;
		BSLib::uint16 count = m_attendenceAttrMap == NULL ? 0 : (BSLib::uint16)m_attendenceAttrMap->size();
		stream << count;
		for (BSLib::Utility::CHashMap<BSLib::uint32, GM::CAttendenceAttr*>::const_iterator itr = m_attendenceAttrMap->begin(); itr != m_attendenceAttrMap->end(); ++itr) {
			if (itr->second != NULL) {
				itr->second->serializeTo(stream);
			}
		}
		return true;
	}
public:
	GM::EGetAttendenceDataResult m_result;
	BSLib::int32 m_startTime;
	BSLib::int32 m_endTime;
	BSLib::int32 m_attendenceCount;
	const BSLib::Utility::CHashMap<BSLib::uint32, GM::CAttendenceAttr*> * m_attendenceAttrMap;
};               

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDActivitySystemGM2GCAckSignIn = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_ACTIVITYSYSTEM, EMSGNUMID_ACTIVITYSYSTEM_GM2GC_ACK_SIGN_IN);
class CMsgActivitySystemGM2GCAckSignIn: public GFLib::CMessage
{
public:
	CMsgActivitySystemGM2GCAckSignIn() 
	:GFLib::CMessage(MsgIDActivitySystemGM2GCAckSignIn)
	,m_result(GM::EATTENDENCE_SIGN_IN_RESULT_SUCCESS)
	,m_signInTime(0)
	{
	}
protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << (BSLib::int8)m_result;
		stream << m_signInTime;
		return true;
	}
public:
	GM::EAttendenceSignInResult m_result;
	BSLib::int32 m_signInTime;
};               

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDActivitySystemGM2GCAckDrawCard = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_ACTIVITYSYSTEM, EMSGNUMID_ACTIVITYSYSTEM_GM2GC_ACK_DRAW_CARD);
class CMsgActivitySystemGM2GCAckDrawCard: public GFLib::CMessage
{
public:
	CMsgActivitySystemGM2GCAckDrawCard() 
	:GFLib::CMessage(MsgIDActivitySystemGM2GCAckDrawCard)
	,m_result(GM::EDRAW_CARD_RESULT_FAIL)
	,m_nextFreeGoldDrawCardRemaindTime(0)
	,m_nextFreeDiamondDrawCardRemainTime(0)
	,m_curFreeGoldDrawCardRemaindCount(0)
	{
	}
protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << (BSLib::int8)m_result;
		if (m_result == GM::EDRAW_CARD_RESULT_SUCCESS) {
			stream << m_nextFreeGoldDrawCardRemaindTime;
			stream << m_nextFreeDiamondDrawCardRemainTime;
			stream << m_curFreeGoldDrawCardRemaindCount;
			BSLib::uint16 count = m_vecRolledItem.size();
			stream << count;
			for (BSLib::uint16 i = 0; i < count; ++i) {
				m_vecRolledItem[i].serialzeTo(stream);	
			}
		}
		return true;
	}
public:
	GM::EDrawCardResult m_result;
	BSLib::int32 m_nextFreeGoldDrawCardRemaindTime;
	BSLib::int32 m_nextFreeDiamondDrawCardRemainTime;
	BSLib::uint32 m_curFreeGoldDrawCardRemaindCount;
	std::vector<GM::CRolledItem> m_vecRolledItem;
};               

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDActivitySystemGM2GCAckGetDrawCardInfo = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_ACTIVITYSYSTEM, EMSGNUMID_ACTIVITYSYSTEM_GM2GC_ACK_GET_DRAW_CARD_INFO);
class CMsgActivitySystemGM2GCAckGetDrawCardInfo: public GFLib::CMessage
{
public:
	CMsgActivitySystemGM2GCAckGetDrawCardInfo() 
	:GFLib::CMessage(MsgIDActivitySystemGM2GCAckGetDrawCardInfo)
	,m_nextFreeGoldDrawCardRemaindTime(0)
	,m_nextFreeDiamondDrawCardRemainTime(0)
	,m_curFreeGoldDrawCardRemaindCount(0)
	{
	}
protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_nextFreeGoldDrawCardRemaindTime;
		stream << m_nextFreeDiamondDrawCardRemainTime;
		stream << m_curFreeGoldDrawCardRemaindCount;
		return true;
	}
public:
	BSLib::int32 m_nextFreeGoldDrawCardRemaindTime;
	BSLib::int32 m_nextFreeDiamondDrawCardRemainTime;
	BSLib::uint32 m_curFreeGoldDrawCardRemaindCount;
};               




}

}//GSLib

#endif

