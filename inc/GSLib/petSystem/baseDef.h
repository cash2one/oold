//////////////////////////////////////////////////////////////////////
//	created:	2014/08/20
//	filename:	GSLib\inc\baseDef.h
//	author:		zhangping
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PETSYSTEM_BASEDEF_H__
#define __GSLIB_PETSYSTEM_BASEDEF_H__

typedef BSLib::uint32 PetID;          // ���ID �ڴ���������
typedef BSLib::uint32 PetTPID;        // ���TPID ��Ʒ�������õ���ƷTPID
typedef BSLib::uint32 PetSkillID;     // ��鼼��ID

typedef BSLib::uint64 PetLevelFriendlyValue; // ���TPID��ȼ����ID
typedef BSLib::uint64 PetFRangeID;    // ����Ѻö�������������ɵ�ID

#define  PET_MAX_ID        65535      // �������

//�ż�ID
#define  INVALID_PETINDEX   0         // ��Ч����
#define  INVALID_PETTPID   -1         // ��ЧTPID
#define  INVALID_PETSKILLID   -1      // ��Ч����ID



// ���״̬
enum EPetStatus
{
    /// <summary>
    /// ��Ч״̬
    /// </summary>
    EPetStatusFree = 0,
    /// <summary>
    /// ���ºȲ�״̬
    /// </summary>
    EPetStatusSit = 1,
    /// <summary>
    /// ����Ȫ״̬
    /// </summary>
    EPetStatusInSpring = 2,
};


/// <summary>
/// ��ս���
/// </summary>
enum EPetHotSprintEnd
{
    /// <summary>
    ///  ʤ��
    /// </summary>
    EPetHotSprintEndWin = 0,
    /// <summary>
    /// ʧ��
    /// </summary>
    EPetHotSprintEndLoss = 1,
};

/// <summary>
/// ������״̬
/// </summary>
enum EPetUnlockStatus
{
    /// <summary>
    /// �Ѿ�����״̬ 
    /// </summary>
    EPetStatusUnlocked = 0,
    /// <summary>
    /// �ɽ���״̬ 
    /// </summary>
    EPetStatusReadyUnlock = 1,
    /// <summary>
    /// ���ɽ���״̬
    /// </summary>
    EPetStatusCannotUnlock = 2,
};

// �����ɫ״̬
enum ETaskUser
{
    /// <summary>
    /// ��Ч״̬
    /// </summary>
    ETaskUserInvalid = 0,
    /// <summary>
    /// ��� 
    /// </summary>
    ETaskUserPet = 1,
    /// <summary>
    /// �ϰ��� 
    /// </summary>
    ETaskUserBoss = 2,
};

/// <summary>
/// ���״̬
/// </summary>
enum EHotSpringType
{
    /// <summary>
    /// ��Ч��Ȫ 
    /// </summary>
    EInvalidHotSpring=0,
    /// <summary>
    /// �������Ȫ
    /// </summary>
    EFiveMiniteHotSpring=1,
    /// <summary>
    /// ��Сʱ��Ȫ
    /// </summary>
    EFourHoursHotSpring=2,
    /// <summary>
    /// ��Сʱ��Ȫ
    /// </summary>
    EEightHoursHotSpring=3,
};

/// <summary>
/// ��Ȫ��������
/// </summary>
enum EHotSpringTaskStatus
{
    /// <summary>
    /// ��Ч����
    /// </summary>
    EHotSpringInvalidTask = 0,
    /// <summary>
    /// �ճ�����
    /// </summary>
    EHotSpringTaskNormal = 1,
    /// <summary>
    /// ��������
    /// </summary>
    EHotSpringMainTask = 2,
    /// <summary>
    /// ֧������
    /// </summary>
    EHotSpringRandomTask = 3,
};

/// <summary>
/// ��������
/// </summary>
enum EHotSpringTaskType
{
    EHotSpringTaskTypeInvalid = 0,
    /// <summary>
    /// ��������
    /// </summary>
    EHotSpringTaskTypeTalk = 1,
    /// <summary>
    /// �ʴ�����
    /// </summary>
    EHotSpringTaskTypeQuestion = 2,
    /// <summary>
    /// ��Ҫ����
    /// </summary>
    EHotSpringTaskTypeGetGift = 3,
    
    /// <summary>
    /// ��������
    /// </summary>
    EHotSpringTaskTypePublishTask = 4,
};

enum EUserType
{
    EUserMe=0,
    EUserYou=1,
};

enum EAnswerType
{
    EAnswerYes=0,
    EAnswerNo=1,
};

enum EHotSpringTimerStatus
{
    EHotSpringTimerStop = 0,
    EHotSpringTimerWork = 1,
};

#ifdef __GNUC__

namespace __gnu_cxx
{
	template< > struct hash< EHotSpringTaskType >
	{
		size_t operator()(const EHotSpringTaskType& x) const
		{
			return (size_t)x;
		}
	};
}

#endif

#endif//__GSLIB_PETSYSTEM_BASEDEF_H__