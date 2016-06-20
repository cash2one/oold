//////////////////////////////////////////////////////////////////////
//	created:	2014/09/10
//	filename: 	GSLib\petSystem\msgNumIDPetSystem.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PETSYSTEM_MSGNUMIDPETSYSTEM_H__
#define __GSLIB_PETSYSTEM_MSGNUMIDPETSYSTEM_H__

#include <GFLib/commonServer/message/message.h>
#include <GSLib/funType.h>
#include <GSLib/serverType.h>
#include <GSLib/baseDef.h>

namespace GSLib
{

namespace PetSystem
{

	//////////////////////////////////////////////////////////////////////////
enum EMsgNumIDPetSystem
{
    // ��Ȫ��
    EMSGNUMID_PETSYSTEM_GC2GM_REQ_EXPANDHOTSPRING = 1,
    EMSGNUMID_PETSYSTEM_GM2GC_ACK_EXPANDHOTSPRING = 2,
	// ��ʼ�����
	EMSGNUMID_PETSYSTEM_GM2GC_NTF_ACTIVE_SPRINGTASK = 3,     
	//EMSGNUMID_PETSYSTEM_GM2GC_NTF_HOTSPRINGEGG_FULL = 4,

	// ������ 
	EMSGNUMID_PETSYSTEM_GC2GM_REQ_HOTSPRINGTASK_END = 5,     
	EMSGNUMID_PETSYSTEM_GM2GC_ACK_HOTSPRINGTASK_END = 6,

	// ��Ȫ�������
	EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_FINISHSPRINGTASK = 7,     
	EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_FINISHSPRINGTASK = 8,

	// �����Ӻ��Ѷ� 
	EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_GETPETUNLOCKDATA = 9,     
	EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_GETPETUNLOCKDATA = 10,

	// ��ȴֵ����
	EMSGNUMID_PETSYSTEM_GC2GM_REQ_UNLOCKPET = 11,     
	EMSGNUMID_PETSYSTEM_GM2GC_ACK_UNLOCKPET = 12,

	// ��Ȫ�ϰ������� 
	EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_SENDPET_GIFT = 13,
	EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_SENDPET_GIFT = 14,

    //EMSGNUMID_PETSYSTEM_GM2GC_NTF_UPDATE_HOTSPRING = 15,
    //EMSGNUMID_PETSYSTEM_GM2GC_NTF_ACTIVE_HOTSPRING_BOSSTASK = 16,

    EMSGNUMID_PETSYSTEM_GC2GM_REQ_GET_PET_BASEINFOR_LIST = 17, 
    EMSGNUMID_PETSYSTEM_GM2GC_ACK_GET_PET_BASEINFOR_LIST = 18,

    // ��ȡ��Ȫ��������
    EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_GET_HOTSPRING_TASK_DETAIL = 19,     
    EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_GET_HOTSPRING_TASK_DETAIL = 20,

    EMSGNUMID_PETSYSTEM_GC2GM_REQ_INIT_ROLEPETDATA = 21,
    EMSGNUMID_PETSYSTEM_GM2GC_ACK_INIT_ROLEPETDATA = 22,

    // ����Ԯ��
    EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_SITDOWN = 23,
    EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_SITDOWN = 24,

    // ȡ��Ԯ��
    EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_STANDUP = 25,
    EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_STANDUP = 26,

    // ��ȡ�������
    EMSGNUMID_PETSYSTEM_GC2GM_REQ_GET_PETDATA = 27,
    EMSGNUMID_PETSYSTEM_GM2GC_ACK_GET_PETDATA = 28,

    // ������Ȫ
    EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_ENTERPOOL = 29,
    EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_ENTERPOOL = 30,

    // �뿪��Ȫ
    EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_QUITPOOL = 31,
    EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_QUITPOOL = 32,

    // �����뿪��Ȫ
    EMSGNUMID_PETSYSTEM_GC2GM_REQ_PET_FAST_QUITPOOL = 33,
    EMSGNUMID_PETSYSTEM_GM2GC_ACK_PET_FAST_QUITPOOL = 34,
};

/// <summary>
/// ��Ȫ���� 
/// </summary>
enum EExpandHotSpringResult
{
    EEXPANDHOTSPRING_RESULT_SUCCESS = 0,
    EEXPANDHOTSPRING_RESULT_FAIL = 1,
    EEXPANDHOTSPRING_RESULT_LEVEL_LIMIT = 2,   // �ﵽ��Ȫ�ȼ�����
    EEXPANDHOTSPRING_RESULT_DIAMOND_LIMIT = 3, // ��ʯ����
    EEXPANDHOTSPRING_RESULT_VIPLEVEL_LIMIT = 4, // VIP�ȼ�����(Ԥ��)
};

/// <summary>
/// ������� 
/// </summary>
enum EHotSpringTaskEndResult
{
    EHOTSPRINGTASK_END_RESULT_SUCCESS = 0,
    EHOTSPRINGTASK_END_RESULT_FAIL = 1,
    EHOTSPRINGTASK_END_RESULT_INVALID_PETID = 2, // ��Ч�Ļ��ID
    EHOTSPRINGTASK_END_RESULT_INVALID_TASK = 3, // ��ǰ������Ч
};

/// <summary>
/// ������� 
/// </summary>
enum EPetTaskFinishResult
{
    EPETTASKFINISH_RESULT_SUCCESS = 0,
    EPETTASKFINISH_RESULT_FAIL = 1,
    EPETTASKFINISH_RESULT_INVALID_PETID = 2, // ��Ч�Ļ��ID
    EPETTASKFINISH_RESULT_INVALID_TASK = 3, // ��ǰ������Ч
    EPETTASKFINISH_RESULT_ITEM_LIMIT = 4, // ��������򲻴��ڸ���Ʒ
};

/// <summary>
/// ������� 
/// </summary>
enum ESendPetGiftResult
{
    ESENDPET_GIFT_RESULT_SUCCESS = 0,
    ESENDPET_GIFT_RESULT_FAIL = 1,
    ESENDPET_GIFT_RESULT_INVALID_PETID = 2, // ��Ч�Ļ��ID
    ESENDPET_GIFT_RESULT_INVALID_GIFT = 3,  // ������Ч������
    ESENDPET_GIFT_RESULT_ITEM_LIMIT = 4,  // ��������򲻴��ڸ���Ʒ
};

/// <summary>
/// �鿴���������� 
/// </summary>
enum EGetPetUnlockDataResult
{
    EGETPETUNLOCKDATARESULT_SUCCESS = 0,
    EGETPETUNLOCKDATARESULT_FAIL = 1,
};

/// <summary>
///  �������
/// </summary>
enum EUnlockPetResult
{
    EUNLOCKPET_RESULT_SUCCESS = 0,
    EUNLOCKPET_RESULT_FAIL = 1,
    EUNLOCKPET_RESULT_INVALID_PETTPID = 2, // ��Ч�Ļ��TPID
    EUNLOCKPET_RESULT_METARIAL_LIMIT = 3,  // ���ϳɲ��ϲ���
    EUNLOCKPET_RESULT_ALREADY_UNLOCK = 4,  // ����ѽ���
};

/// <summary>
/// ������� 
/// </summary>
enum EPetGetHotSpringTaskDetailResult
{
    EPETGET_HOTSPRING_TASKDETAIL_RESULT_SUCCESS = 0,
    EPETGET_HOTSPRING_TASKDETAIL_RESULT_FAIL = 1,
};

enum EGetInitRolePetDataResult
{
    EGET_INITROLEPETDATA_RESULT_SUCCESS = 0,
    EGET_INITROLEPETDATA_RESULT_FAIL = 1,
};

/// <summary>
/// Ԯ��
/// </summary>
enum EPetSitDownResult
{
    EPETSITDOWN_RESULT_SUCCESS = 0,
    EPETSITDOWN_RESULT_FAIL = 1,
    EPETSITDOWN_RESULT_INVALID_PETID = 2,		// ��鲻����
    EPETSITDOWN_RESULT_ALREADY_SITDOWN = 3,		// ����Ѿ����£��Ѿ���Ԯ��״̬��
    EPETSITDOWN_RESULT_ALREADY_INPOOL = 4,		// ���������Ȫ�����ɽ���Ԯ��״̬��
    EPETSITDOWN_RESULT_NO_SIT_PLACE,			// �Ѵﵽ��������
};

/// <summary>
/// ȡ��Ԯ��
/// </summary>
enum EPetStandUpResult
{
    EPETSTANDUP_RESULT_SUCCESS = 0,
    EPETSTANDUP_RESULT_FAIL = 1,
    EPETSTANDUP_RESULT_INVALID_PETID = 2,   // ��鲻����
    EPETSTANDUP_RESULT_NOT_SITDOWN = 3,     // ��鲻��Ԯ��״̬
};

/// <summary>
/// ��ȡ������� 
/// </summary>
enum EGetPetDataResult
{
    EGETPETDATA_RESULT_SUCCESS = 0,
    EGETPETDATA_RESULT_FAIL = 1,
    EGETPETDATA_RESULT_INVALID_PETID = 2,   // ��鲻����
};

/// <summary>
/// ������Ȫ
/// </summary>
enum EPetEnterPoolResult
{
    EPETENTERPOOL_RESULT_SUCCESS = 0,
    EPETENTERPOOL_RESULT_FAIL = 1,
    EPETENTERPOOL_RESULT_INVALID_PETID = 2,   // ��鲻����
    EPETENTERPOOL_ALREADY_INPOOL = 3,         // ���������Ȫ��
    EPETENTERPOOL_ALREADY_SITDOWN = 4,        // �����Ԯ�������ɽ�����Ȫ��
    EPETENTERPOOL_ALREADY_FULL = 5,           // ��Ȫ����
};

/// <summary>
/// �뿪��Ȫ
/// </summary>
enum EPetQuitPoolResult
{
    EPETQUITPOOL_RESULT_SUCCESS = 0,
    EPETQUITPOOL_RESULT_FAIL = 1,
    EPETQUITPOOL_RESULT_INVALID_PETID = 2, // ��鲻����
    EPETQUITPOOL_RESULT_NOT_INPOOL = 3,    // ��鲻��Ȫ��
};

/// <summary>
/// �����뿪��Ȫ
/// </summary>
enum EPetFastQuitPoolResult
{
    EPET_FASTQUITPOOL_RESULT_SUCCESS = 0,
    EPET_FASTQUITPOOL_RESULT_FAIL = 1,
    EPET_FASTQUITPOOL_RESULT_INVALID_PETID = 2,      // ��鲻����
    EPET_FASTQUITPOOL_RESULT_NOT_INPOOL = 3,         // ��鲻��Ȫ��
    EPET_FASTQUITPOOL_RESULT_DIAMOND_LIMIT = 4,      // ��ʯ����
};

/// <summary>
/// ��ȡ��������Ϣ�б� 
/// </summary>
enum EGetPetBaseInforListResult
{
    EGET_PETBASEINFORLIST_RESULT_SUCCESS = 0,
    EGET_PETBASEINFORLIST_RESULT_FAIL = 1,
};

}//PetSystem

}//GSLib

#endif//__GSLIB_PETSYSTEM_MSGNUMIDPETSYSTEM_H__
