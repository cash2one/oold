#ifndef __GSLIB_ACHIEVESYSTEM_GM_MSGACHIEVESYSTEMGM_H__
#define __GSLIB_ACHIEVESYSTEM_GM_MSGACHIEVESYSTEMGM_H__

#include <GSLib/achieveSystem/msgNumIDAchieveSystem.h>

namespace GSLib
{

namespace AchieveSystem
{
const BSLib::uint32 MsgIDAchieveSystemGC2GMReqGetAchieveList = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_ACHIEVESYSTEM, EMSGNUMID_ACHIEVESYSTEM_GC2GM_REQ_GET_ACHIEVE_LIST);
class CMsgAchieveSystemGC2GMReqGetAchieveList: public GFLib::CMessage
{
public:
    CMsgAchieveSystemGC2GMReqGetAchieveList() : GFLib::CMessage(MsgIDAchieveSystemGC2GMReqGetAchieveList)
    {
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_achieveType;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_achieveType;
        return true;
    }

public:
    BSLib::uint32 m_achieveType;
};

const BSLib::uint32 MsgIDAchieveSystemGC2GMReqGetAchievePrize = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_ACHIEVESYSTEM, EMSGNUMID_ACHIEVESYSTEM_GC2GM_REQ_GET_ACHIEVE_PRIZE);
class CMsgAchieveSystemGC2GMReqGetAchievePrize: public GFLib::CMessage
{
public:
    CMsgAchieveSystemGC2GMReqGetAchievePrize() : GFLib::CMessage(MsgIDAchieveSystemGC2GMReqGetAchievePrize)
    {
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_achieveID;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_achieveID;
        return true;
    }

public:
    BSLib::uint32 m_achieveID;
};

const BSLib::uint32 MsgIDAchieveSystemGC2GMReqSaveAchieveData = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_ACHIEVESYSTEM, EMSGNUMID_ACHIEVESYSTEM_GC2GM_REQ_SAVE_ACHIEVE_DATA);
class CMsgAchieveSystemGC2GMReqSaveAchieveData: public GFLib::CMessage
{
public:
    CMsgAchieveSystemGC2GMReqSaveAchieveData() : GFLib::CMessage(MsgIDAchieveSystemGC2GMReqSaveAchieveData)
    {
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_achieveSubType;
        stream << m_achieveData;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_achieveSubType;
        stream >> m_achieveData;
        return true;
    }

public:
    BSLib::uint32 m_achieveSubType;
    BSLib::uint32 m_achieveData;
};
}//AchieveSystem

}//GSLib

#endif//__GSLIB_ACHIEVESYSTEM_GM_MSGACHIEVESYSTEMGM_H__

