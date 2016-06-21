#ifndef __GSLIB_ACHIEVESYSTEM_MSGACHIEVESYSTEMGC_H__
#define __GSLIB_ACHIEVESYSTEM_MSGACHIEVESYSTEMGC_H__

#include <GSLib/achieveSystem/msgNumIDAchieveSystem.h>

namespace GSLib
{

namespace AchieveSystem
{
const BSLib::uint32 MsgIDAchieveSystemGM2GCAckGetAchieveList = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_ACHIEVESYSTEM, EMSGNUMID_ACHIEVESYSTEM_GM2GC_ACK_GET_ACHIEVE_LIST);
class CMsgAchieveSystemGM2GCAckGetAchieveList: public GFLib::CMessage
{
public:
    CMsgAchieveSystemGM2GCAckGetAchieveList() : GFLib::CMessage(MsgIDAchieveSystemGM2GCAckGetAchieveList)
    {
        m_retCode = EGETACHIEVELIST_RESULT_FAIL;
        m_achieveType = 0;
        m_achieveCount = 0;
        m_stream.reset();
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_achieveType;
        stream << m_achieveCount;
        stream << m_stream;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::uint32 m_achieveType;
    BSLib::uint32 m_achieveCount;
    BSLib::Utility::CStream m_stream;
};

const BSLib::uint32 MsgIDAchieveSystemGM2GCAckGetAchievePrize = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_ACHIEVESYSTEM, EMSGNUMID_ACHIEVESYSTEM_GM2GC_ACK_GET_ACHIEVE_PRIZE);
class CMsgAchieveSystemGM2GCAckGetAchievePrize: public GFLib::CMessage
{
public:
    CMsgAchieveSystemGM2GCAckGetAchievePrize() : GFLib::CMessage(MsgIDAchieveSystemGM2GCAckGetAchievePrize)
    {
        m_retCode = EGETACHIEVEPRIZE_RESULT_FAIL;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_achieveID;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::uint32 m_achieveID;
};


const BSLib::uint32 MsgIDAchieveSystemGM2GCAckSaveAchieveData = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_ACHIEVESYSTEM, EMSGNUMID_ACHIEVESYSTEM_GM2GC_ACK_SAVE_ACHIEVE_DATA);
class CMsgAchieveSystemGM2GCAckSaveAchieveData: public GFLib::CMessage
{
public:
    CMsgAchieveSystemGM2GCAckSaveAchieveData() : GFLib::CMessage(MsgIDAchieveSystemGM2GCAckSaveAchieveData)
    {
        m_retCode = ESAVEACHIEVEDATA_RESULT_FAIL;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
};

const BSLib::uint32 MsgIDAchieveSystemGM2GCNtfAchieveFinished = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_ACHIEVESYSTEM, EMSGNUMID_ACHIEVESYSTEM_GM2GC_NTF_ACHIEVE_FINISHED);
class CMsgAchieveSystemGM2GCNtfAchieveFinished: public GFLib::CMessage
{
public:
    CMsgAchieveSystemGM2GCNtfAchieveFinished() : GFLib::CMessage(MsgIDAchieveSystemGM2GCNtfAchieveFinished)
    {
        m_achieveID = 0;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_achieveID;
        return true;
    }

public:
    BSLib::uint32 m_achieveID;
};

}//AchieveSystem

}//GSLib

#endif//__GSLIB_ACHIEVESYSTEM_MSGACHIEVESYSTEMGC_H__

