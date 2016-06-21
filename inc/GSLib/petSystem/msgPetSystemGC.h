#ifndef __GSLIB_PETSYSTEM_MSGPETSYSTEMGC_H__
#define __GSLIB_PETSYSTEM_MSGPETSYSTEMGC_H__

#include <GSLib/petSystem/msgNumIDPetSystem.h>


namespace GSLib
{

namespace PetSystem
{
//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDPetSystemGM2GCAckExpandHotSpring= GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GM2GC_ACK_EXPANDHOTSPRING);
class CMsgPetSystemGM2GCAckExpandHotSpring: public GFLib::CMessage
{
public:
    CMsgPetSystemGM2GCAckExpandHotSpring() : GFLib::CMessage(MsgIDPetSystemGM2GCAckExpandHotSpring)
    {
        m_retCode = EEXPANDHOTSPRING_RESULT_FAIL;
        m_stream.reset();
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_stream;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::Utility::CStream m_stream;
};

const BSLib::uint32 MsgIDPetSystemGM2GCAckInitPetData= GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GM2GC_ACK_INIT_ROLEPETDATA);
class CMsgPetSystemGM2GCAckInitPetData: public GFLib::CMessage
{
public:
	CMsgPetSystemGM2GCAckInitPetData() : GFLib::CMessage(MsgIDPetSystemGM2GCAckInitPetData)
	{
        m_retCode = EGET_INITROLEPETDATA_RESULT_FAIL;
		m_stream.reset();
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
        stream << m_retCode;
		stream << m_stream;
		return true;
	}

public:
    BSLib::uint32 m_retCode;
	BSLib::Utility::CStream m_stream;

};

const BSLib::uint32 MsgIDPetSystemGM2GCAckPetSitDown= GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_SITDOWN);
class CMsgPetSystemGM2GCAckPetSitDown: public GFLib::CMessage
{
public:
    CMsgPetSystemGM2GCAckPetSitDown() : GFLib::CMessage(MsgIDPetSystemGM2GCAckPetSitDown)
    {
        m_retCode = EPETSITDOWN_RESULT_FAIL;
        m_stream.reset();
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_stream;
        return true;
    }
public:
    BSLib::uint32 m_retCode;
    BSLib::Utility::CStream m_stream;
};

const BSLib::uint32 MsgIDPetSystemGM2GCAckPetStandUp= GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_STANDUP);
class CMsgPetSystemGM2GCAckPetStandUp: public GFLib::CMessage
{
public:
    CMsgPetSystemGM2GCAckPetStandUp() : GFLib::CMessage(MsgIDPetSystemGM2GCAckPetStandUp)
    {
        m_retCode = EPETSTANDUP_RESULT_FAIL;
        m_stream.reset();
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_stream;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::Utility::CStream m_stream;
};

const BSLib::uint32 MsgIDPetSystemGM2GCAckGetPetData= GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GM2GC_ACK_GET_PETDATA);
class CMsgPetSystemGM2GCAckGetPetData: public GFLib::CMessage
{
public:
    CMsgPetSystemGM2GCAckGetPetData() : GFLib::CMessage(MsgIDPetSystemGM2GCAckGetPetData)
    {
        m_retCode = EGETPETDATA_RESULT_FAIL;
        m_stream.reset();
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_stream;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::Utility::CStream m_stream;

};

const BSLib::uint32 MsgIDPetSystemGM2GCAckPetEnterPool= GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_ENTERPOOL);
class CMsgPetSystemGM2GCAckPetEnterPool: public GFLib::CMessage
{
public:
    CMsgPetSystemGM2GCAckPetEnterPool() : GFLib::CMessage(MsgIDPetSystemGM2GCAckPetEnterPool)
    {
        m_retCode = EPETENTERPOOL_RESULT_FAIL;
        m_stream.reset();
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_stream;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::Utility::CStream m_stream;
};

const BSLib::uint32 MsgIDPetSystemGM2GCAckPetQuitPool= GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_QUITPOOL);
class CMsgPetSystemGM2GCAckPetQuitPool: public GFLib::CMessage
{
public:
    CMsgPetSystemGM2GCAckPetQuitPool() : GFLib::CMessage(MsgIDPetSystemGM2GCAckPetQuitPool)
    {
        m_retCode = EPETQUITPOOL_RESULT_FAIL;
        m_stream.reset();
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_stream;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::Utility::CStream m_stream;
};


const BSLib::uint32 MsgIDPetSystemGM2GCAckPetFastQuitPool= GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_FAST_QUITPOOL);
class CMsgPetSystemGM2GCAckPetFastQuitPool: public GFLib::CMessage
{
public:
    CMsgPetSystemGM2GCAckPetFastQuitPool() : GFLib::CMessage(MsgIDPetSystemGM2GCAckPetFastQuitPool)
    {
        m_retCode = EPET_FASTQUITPOOL_RESULT_FAIL;
        m_stream.reset();
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_stream;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::Utility::CStream m_stream;
};

const BSLib::uint32 MsgIDPetSystemGM2GCNtfActiveHotSpringTask = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GM2GC_NTF_ACTIVE_SPRINGTASK);
class CMsgPetSystemGM2GCNtfActivePetTask: public GFLib::CMessage
{
public:
    CMsgPetSystemGM2GCNtfActivePetTask() : GFLib::CMessage(MsgIDPetSystemGM2GCNtfActiveHotSpringTask)
    {
        m_petID = 0;
        m_hotSpringTaskStatus = 0;
        m_hotSpringTaskType = 0;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_petID;
        stream << m_hotSpringTaskStatus;
        stream << m_hotSpringTaskType;
        return true;
    }

public:
    BSLib::uint32 m_petID;
    BSLib::uint32 m_hotSpringTaskStatus;
    BSLib::uint32 m_hotSpringTaskType;
};

const BSLib::uint32 MsgIDPetSystemGM2GCAckHotSpringTaskEnd= GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GM2GC_ACK_HOTSPRINGTASK_END);
class CMsgPetSystemGM2GCAckHotSpringTaskEnd: public GFLib::CMessage
{
public:
	CMsgPetSystemGM2GCAckHotSpringTaskEnd() : GFLib::CMessage(MsgIDPetSystemGM2GCAckHotSpringTaskEnd)
	{
		m_retCode = EHOTSPRINGTASK_END_RESULT_FAIL;
        m_stream.reset();
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_stream;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::Utility::CStream m_stream;
};

const BSLib::uint32 MsgIDPetSystemGM2GCAckPetFinishHotSpringTask= GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_FINISHSPRINGTASK);
class CMsgPetSystemGM2GCAckPetFinishHotSpringTask: public GFLib::CMessage
{
public:
	CMsgPetSystemGM2GCAckPetFinishHotSpringTask() : GFLib::CMessage(MsgIDPetSystemGM2GCAckPetFinishHotSpringTask)
	{
		m_retCode = EPETTASKFINISH_RESULT_FAIL;
		m_petID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_retCode;
		stream << m_petID;
		return true;
	}

public:
	BSLib::uint32 m_retCode;
    BSLib::uint32 m_petID;
};

const BSLib::uint32 MsgIDPetSystemGM2GCAckSendPetGift= GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_SENDPET_GIFT);
class CMsgPetSystemGM2GCAckSendPetGift: public GFLib::CMessage
{
public:
    CMsgPetSystemGM2GCAckSendPetGift() : GFLib::CMessage(MsgIDPetSystemGM2GCAckSendPetGift)
    {
        m_retCode = ESENDPET_GIFT_RESULT_FAIL;
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

const BSLib::uint32 MsgIDPetSystemGM2GCAckGetPetUnlockData = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_GETPETUNLOCKDATA);
class CMsgPetSystemGM2GCAckGetPetUnlockData: public GFLib::CMessage
{
public:
	CMsgPetSystemGM2GCAckGetPetUnlockData() : GFLib::CMessage(MsgIDPetSystemGM2GCAckGetPetUnlockData)
	{
		m_retCode = EGETPETUNLOCKDATARESULT_FAIL;
        m_stream.reset();
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_stream;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::Utility::CStream m_stream;
};

const BSLib::uint32 MsgIDPetSystemGM2GCAckPetColdValueClean = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GM2GC_ACK_UNLOCKPET);
class CMsgPetSystemGM2GCAckUnlockPet: public GFLib::CMessage
{
public:
	CMsgPetSystemGM2GCAckUnlockPet() : GFLib::CMessage(MsgIDPetSystemGM2GCAckPetColdValueClean)
	{
		m_retCode = EUNLOCKPET_RESULT_FAIL;
        m_stream.reset();
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_stream;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::Utility::CStream m_stream;
};


const BSLib::uint32 MsgIDPetSystemGM2GCAckGetPetBaseInforList = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GM2GC_ACK_GET_PET_BASEINFOR_LIST);
class CMsgPetSystemGM2GCAckGetPetBaseInforList: public GFLib::CMessage
{
public:
    CMsgPetSystemGM2GCAckGetPetBaseInforList() : GFLib::CMessage(MsgIDPetSystemGM2GCAckGetPetBaseInforList)
    {
        m_retCode = EGET_PETBASEINFORLIST_RESULT_FAIL;
        m_stream.reset();
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_stream;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::Utility::CStream m_stream;
};

const BSLib::uint32 MsgIDPetSystemGM2GCAckPetGetHotSpringTaskDetail = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PETSYSTEM, EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_GET_HOTSPRING_TASK_DETAIL);
class CMsgPetSystemGM2GCAckPetGetHotSpringTaskDetail: public GFLib::CMessage
{
public:
    CMsgPetSystemGM2GCAckPetGetHotSpringTaskDetail() : GFLib::CMessage(MsgIDPetSystemGM2GCAckPetGetHotSpringTaskDetail)
    {
        m_retCode = EPETGET_HOTSPRING_TASKDETAIL_RESULT_FAIL;
        m_petID=0;
        m_stream.reset();
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
		if (m_retCode == 0) {
	        stream << m_petID;
	        stream << m_stream;
		}
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::uint32 m_petID;
    BSLib::Utility::CStream m_stream;
};



}//PetSystem

}//GSLib

#endif//__GSLIB_PETSYSTEM_MSGPETSYSTEMGC_H__

