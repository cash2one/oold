//////////////////////////////////////////////////////////////////////
//	created:	2014/09/10
//	filename: 	GSLib\petSystem\GM\msgPetSystemGM.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PETSYSTEM_GM_MSGPETSYSTEMGM_H__
#define __GSLIB_PETSYSTEM_GM_MSGPETSYSTEMGM_H__

#include <GSLib/petSystem/msgNumIDPetSystem.h>

namespace GSLib
{

namespace PetSystem
{

//////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDPetSystemGC2GMReqExpandHotSpring = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GC2GM_REQ_EXPANDHOTSPRING);
class CMsgPetSystemGC2GMReqExpandHotSpring: public GFLib::CMessage
{
public:
    CMsgPetSystemGC2GMReqExpandHotSpring() : GFLib::CMessage(MsgIDPetSystemGC2GMReqExpandHotSpring)
    {
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        return true;
    }
};


const BSLib::uint32 MsgIDPetSystemGC2GMReqInitRolePetData = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GC2GM_REQ_INIT_ROLEPETDATA);
class CMsgPetSystemGC2GMReqInitRolePetData: public GFLib::CMessage
{
public:
    CMsgPetSystemGC2GMReqInitRolePetData() : GFLib::CMessage(MsgIDPetSystemGC2GMReqInitRolePetData)
    {
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        return true;
    }
};

const BSLib::uint32 MsgIDPetSystemGC2GMReqPetSitDown = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_SITDOWN);
class CMsgPetSystemGC2GMReqPetSitDown: public GFLib::CMessage
{
public:
    CMsgPetSystemGC2GMReqPetSitDown() : GFLib::CMessage(MsgIDPetSystemGC2GMReqPetSitDown)
    {
        m_petID = 0;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_petID;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_petID;
        return true;
    }

public:
    BSLib::uint32 m_petID;
};


const BSLib::uint32 MsgIDPetSystemGC2GMReqPetStandUp = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_STANDUP);
class CMsgPetSystemGC2GMReqPetStandUp: public GFLib::CMessage
{
public:
    CMsgPetSystemGC2GMReqPetStandUp() : GFLib::CMessage(MsgIDPetSystemGC2GMReqPetStandUp)
    {
        m_petID = 0;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_petID;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_petID;
        return true;
    }

public:
    BSLib::uint32 m_petID;
};

const BSLib::uint32 MsgIDPetSystemGC2GMReqGetPetData = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GC2GM_REQ_GET_PETDATA);
class CMsgPetSystemGC2GMReqGetPetData: public GFLib::CMessage
{
public:
    CMsgPetSystemGC2GMReqGetPetData() : GFLib::CMessage(MsgIDPetSystemGC2GMReqGetPetData)
    {
        m_petID = 0;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_petID;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_petID;
        return true;
    }

public:
    BSLib::uint32 m_petID;
};

const BSLib::uint32 MsgIDPetSystemGC2GMReqPetEnterPool = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_ENTERPOOL);
class CMsgPetSystemGC2GMReqPetEnterPool: public GFLib::CMessage
{
public:
    CMsgPetSystemGC2GMReqPetEnterPool() : GFLib::CMessage(MsgIDPetSystemGC2GMReqPetEnterPool)
    {
        m_petID = 0;
        m_hotSpringType = 0;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_petID;
        stream << m_hotSpringType;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_petID;
        stream >> m_hotSpringType;
        return true;
    }

public:
    BSLib::uint32 m_petID;
    BSLib::uint32 m_hotSpringType;
};

const BSLib::uint32 MsgIDPetSystemGC2GMReqPetQuitPool = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_QUITPOOL);
class CMsgPetSystemGC2GMReqPetQuitPool: public GFLib::CMessage
{
public:
    CMsgPetSystemGC2GMReqPetQuitPool() : GFLib::CMessage(MsgIDPetSystemGC2GMReqPetQuitPool)
    {
        m_petID = 0;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_petID;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_petID;
        return true;
    }

public:
    BSLib::uint32 m_petID;
};

const BSLib::uint32 MsgIDPetSystemGC2GMReqPetFastQuitPool = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_FAST_QUITPOOL);
class CMsgPetSystemGC2GMReqPetFastQuitPool: public GFLib::CMessage
{
public:
    CMsgPetSystemGC2GMReqPetFastQuitPool() : GFLib::CMessage(MsgIDPetSystemGC2GMReqPetFastQuitPool)
    {
        m_petID = 0;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_petID;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_petID;
        return true;
    }

public:
    BSLib::uint32 m_petID;
};

const BSLib::uint32 MsgIDPetSystemGC2GMReqHotSpringTaskEnd= GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GC2GM_REQ_HOTSPRINGTASK_END);
class CMsgPetSystemGC2GMReqHotSpringTaskEnd: public GFLib::CMessage
{
public:
	CMsgPetSystemGC2GMReqHotSpringTaskEnd() : GFLib::CMessage(MsgIDPetSystemGC2GMReqHotSpringTaskEnd)
	{
		m_petID = 0;
		m_endStatus = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_petID;
		stream << m_endStatus;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_petID;
		stream >> m_endStatus;
		return true;
	}

public:
	BSLib::uint32 m_petID;
	BSLib::uint32 m_endStatus;
};

const BSLib::uint32 MsgIDPetSystemGC2GMReqPetFinishHotSpringTask = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_FINISHSPRINGTASK);
class CMsgPetSystemGC2GMReqPetFinishHotSpringTask: public GFLib::CMessage
{
public:
	CMsgPetSystemGC2GMReqPetFinishHotSpringTask() : GFLib::CMessage(MsgIDPetSystemGC2GMReqPetFinishHotSpringTask)
    {
        m_petID = 0;
        m_answerID = 0;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_petID;
        stream << m_answerID;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_petID;
        stream >> m_answerID;
        return true;
    }
public:
    BSLib::uint32 m_petID;
    BSLib::uint32 m_answerID;
};

const BSLib::uint32 MsgIDPetSystemGC2GMReqSendPetGift = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_SENDPET_GIFT);
class CMsgPetSystemGC2GMReqSendPetGift: public GFLib::CMessage
{
public:
    CMsgPetSystemGC2GMReqSendPetGift() : GFLib::CMessage(MsgIDPetSystemGC2GMReqSendPetGift)
    {
        m_petID = 0;
        m_stream.reset();
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_petID;
        stream << m_stream;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_petID;
        stream >> m_stream;
        return true;
    }
public:
    BSLib::uint32 m_petID;
    BSLib::Utility::CStream m_stream;
};

const BSLib::uint32 MsgIDPetSystemGC2GMReqGetPetUnlockData = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_GETPETUNLOCKDATA);
class CMsgPetSystemGC2GMReqGetPetUnlockData: public GFLib::CMessage
{
public:
	CMsgPetSystemGC2GMReqGetPetUnlockData() : GFLib::CMessage(MsgIDPetSystemGC2GMReqGetPetUnlockData)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		return true;
	}
};

const BSLib::uint32 MsgIDPetSystemGC2GMReqUnlockPet = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GC2GM_REQ_UNLOCKPET);
class CMsgPetSystemGC2GMReqUnlockPet: public GFLib::CMessage
{
public:
	CMsgPetSystemGC2GMReqUnlockPet() : GFLib::CMessage(MsgIDPetSystemGC2GMReqUnlockPet)
	{
        m_petTPID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_petTPID;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_petTPID;
		return true;
	}

public:
   BSLib::uint32 m_petTPID;
};

const BSLib::uint32 MsgIDPetSystemGC2GMReqGetPetBaseInforList = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GC2GM_REQ_GET_PET_BASEINFOR_LIST);
class CMsgPetSystemGC2GMReqGetPetBaseInforList: public GFLib::CMessage
{
public:
    CMsgPetSystemGC2GMReqGetPetBaseInforList() : GFLib::CMessage(MsgIDPetSystemGC2GMReqGetPetBaseInforList)
    {
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        return true;
    }
};

const BSLib::uint32 MsgIDPetSystemGC2GMReqPetGetHotSpringTaskDetail = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_GET_HOTSPRING_TASK_DETAIL);
class CMsgPetSystemGC2GMReqPetGetHotSpringTaskDetail: public GFLib::CMessage
{
public:
    CMsgPetSystemGC2GMReqPetGetHotSpringTaskDetail() : GFLib::CMessage(MsgIDPetSystemGC2GMReqPetGetHotSpringTaskDetail)
    {
        m_petID = 0;
        m_taskType = 0;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_petID;
        stream << m_taskType;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_petID;
        stream >> m_taskType;
        return true;
    }

public:
    BSLib::uint32 m_petID;
    BSLib::uint32 m_taskType;
};

}//PetSystem

}//GSLib

#endif//__GSLIB_PETSYSTEM_GM_MSGPETSYSTEMGM_H__
