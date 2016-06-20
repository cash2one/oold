//////////////////////////////////////////////////////////////////////
//	created:	2014/09/29
//	filename: 	GSLib\sceneSystem\GM\sceneDefine.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef		__GSLIB_SCENESYSTEM_GM_SCENEDEFINE_H__
#define		__GSLIB_SCENESYSTEM_GM_SCENEDEFINE_H__



namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

	const BSLib::uint32 C_DAILY_ARENA_CHALLENGE_TIMES = 10;				//ÿ����ս����
	const BSLib::uint32 C_MAX_DAILY_ARENA_TICKET_PURCHASE_COUNT = 4;	//ÿ�տɹ�����Ʊ����
	const BSLib::uint32 C_MAX_ARENA_TICKETS_PER_PURCHASE = 5;			//ÿ�ι�����Ʊ��
	const BSLib::uint32 C_MAX_AREN_WIN_LIGHT_POWER_PRIZE = 100;			//������ʤ����100������
	const BSLib::uint32 C_MAX_AREN_LOSE_LIGHT_POWER_PRIZE = 20;			//������ʤ����20������
	const BSLib::uint32 C_ERASE_CHALLENGE_COLD_DOWN_DIAMOND_COST = 20;	//ȥ��CD��������ʯ��

	const BSLib::uint32 C_GET_ARENA_INFO_INTERVAL = 5;					
	const BSLib::uint32 C_ARENA_SCENE_ID = 1;
	const BSLib::uint32 C_STAGE_LEVEL_REQUIRE_STAR = 3;

	const BSLib::uint32 C_REVIVE_COUNT = 3;
	const BSLib::uint32 C_MAX_GREED_LAND_ENTRANCE_TICKETS = 10;
	const BSLib::uint32 C_GREED_LAND_TICKETSUPDATE_SECONDS = 2* 60;
	const BSLib::uint32 C_CHALLENGE_COOL_DWON_INTERVAL = 600;
	const BSLib::uint32 C_MAX_CHALLENGE_RECORD_COUNT = 50;

enum ESceneType
{
	ESCENE_TYPE_NONE = 0,
	ESCENE_TYPE_CITY,				//����
	ESCENE_TYPE_STAGE,				//����ؿ� ��Ӣ���� 
	ESCENE_TYPE_ARENA,				//������
	ESCENE_TYPE_CONTINUOUS_STAGE,	//��������
	ESCENE_TYPE_RANDOM_STAGE,		//����ؿ�
	ESCENE_TYPE_RANDOM_GOLD_STAGE,	//��Ҹ���
	ESCENE_TYPE_RANDOM_EXP_STAGE,	//���鸱��

	ESCENE_TYPE_MAX,
};

enum ESceneState
{
	ESCENE_NONE,
	ESCENE_BEGIN,
	ESCENE_END,
};

enum EInstanceType
{
	EINSTANCE_TYPE_NONE = 0,			//��
	EINSTANCE_TYPE_STORY,				//��ͨ���鸱��
	EINSTANCE_TYPE_ADVANCE,				//��Ӣ����
	EINSTANCE_TYPE_ACTIVITY,			//�����
	EINSTANCE_TYPE_CONTINUOUS_STAGE,	//��������
	EINSTANCE_TYPE_RANDOM_STAGE,		//����ؿ�
	EINSTANCE_TYPE_RANDOM_EXP_STAGE,	//���鸱��
	EINSTANCE_TYPE_RANDOM_GOLD_STAGE,	//��Ҹ���

	EINSTANCE_TYPE_MAX,					//
};

enum EMonsterDropType
{
	None,
	CertainlyDropMonster,
	RandomDropMonster,
	Boss,
	Elite,
};

enum EChallengeType
{
	ECHALLENGE_TYPE_RANKING_ROLE = 0,
	ECHALLENGE_TYPE_REVENGE,
};




} // GSLib

} // SceneSystem

} // GSLib






#endif
