//////////////////////////////////////////////////////////////////////
//	created:	2014/10/28
//	filename: 	GSLib\dbTableDef.hpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_DBTABLEDEF_HPP__
#define __GSLIB_DBTABLEDEF_HPP__

#include <GSLib/dbSystem/dbCommonSystem.h>
#include <GSLib/dbTableID.h>
#include <GSLib/equipSystem/DB/tableEquipDB.h>
#include <GSLib/itemSystem/DB/tableItemDB.h>
#include <GSLib/skillSystem/DB/tableSkillDB.h>
#include <GSLib/mailSystem/DB/tableMailDB.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>
#include <GSLib/sceneSystem/DB/tableSceneDB.h>
#include <GSLib/petSystem/DB/tablePetDB.h>
#include <GSLib/prizeSystem/DB/tablePrizeDB.h>
#include <GSLib/taskSystem/DB/tableTaskDB.h>
#include <GSLib/shopSystem/DB/tableShopDB.h>
#include <GSLib/activitySystem/DB/tableActivityDB.h>
#include <GSLib/friendSystem/DB/tableFriendDB.h>
#include <GSLib/rankSystem/DB/tableRankDB.h>
#include <GSLib/achieveSystem/DB/tableAchieveDB.h>
#include <GSLib/dbSystem/LG/dbTableLG.h>

namespace GSLib
{

void relateDBTableIDBySDbColumn(GSLib::DBSystem::CDBCommonSystem& a_dbCommonSystem)
{	
	a_dbCommonSystem.addDbColumn(EDBTABLEID_PLAYER_DATA, "PlayerData", GSLib::PlayerSystem::DB::g_playerDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_DATA, "RoleData", GSLib::PlayerSystem::DB::g_roleDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_VIPGIFT_DATA, "RoleVipGiftData", GSLib::PlayerSystem::DB::g_roleVipGiftDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_BAG_DATA, "RoleBagData", GSLib::PlayerSystem::DB::g_roleBagDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_EQUIP_DATA, "RoleEquipData", GSLib::EquipSystem::DB::g_roleEquipDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_SKILL_DATA, "RoleSkillData", GSLib::SkillSystem::DB::g_roleSkillDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_ITEM_DATA, "RoleItemData", GSLib::ItemSystem::DB::g_roleItemDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBTABLEID_MAIL_OUTPUT_DATA, "MailOutputData", GSLib::MailSystem::DB::g_mailOutputDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_MAIL_CONFIG_DATA, "RoleMailConfigData", GSLib::MailSystem::DB::g_roleMailConfigDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_MAIL_INPUTBOX_DATA, "RoleMailInputBoxData", GSLib::MailSystem::DB::g_roleMailInputDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_SCENE_ARENA_ROLE_DATA, "RoleArenaData", GSLib::SceneSystem::DB::g_roleArenaDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_SCENE_ARENA_CHALLENGE_RECORD, "ArenaChallengeRecordData", GSLib::SceneSystem::DB::g_arenaChallengeRecordColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_PET_DATA, "RolePetData", GSLib::PetSystem::DB::g_petDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBABLEID_ROLE_PRIZE_DATA, "RolePrizeData", GSLib::PrizeSystem::DB::g_rolePrizeDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBABLEID_ROLE_DAILY_TASK_DATA, "RoleDailyTaskData", GSLib::TaskSystem::DB::g_roleDailyTaskColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBABLEID_ROLE_MAIN_TASK_DATA, "RoleMainTaskData", GSLib::TaskSystem::DB::g_roleMainTaskColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_SHOP_DATA, "RoleShopData", GSLib::ShopSystem::DB::g_roleShopDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBABLEID_ROLE_ATTENDENCE_DATA, "RoleAttendenceData", GSLib::ActivitySystem::DB::g_roleAttendenceTableColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_FRIEND_DATA, "RoleFriendData", GSLib::FriendSystem::DB::g_roleFriendDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBTABLEID_FRIEND_PENDING_QUEUE_DATA, "FriendPendingQueueData", GSLib::FriendSystem::DB::g_FriendPendingQueueDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
    a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_NAME_DATA, "RoleNameData", GSLib::PlayerSystem::DB::g_roleNameDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
    a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_STORY_INSTANCE_PROGRESS_DATA, "RoleStoryInstanceProgressData", GSLib::SceneSystem::DB::g_roleStoryInstanceProgressColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
    a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_STAGE_DATA, "RoleInstanceStageData", GSLib::SceneSystem::DB::g_roleInstanceStageDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
    a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_INSTANCE_PRIZE_DATA, "RoleInstancePrizeData", GSLib::SceneSystem::DB::g_roleInstancePrizeDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBTABLEID_RANK_DATA, "RankData", GSLib::RankSystem::DB::g_RankPendingQueueDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_DRAW_CARD_DATA, "RoleDrawCardData", GSLib::ActivitySystem::DB::g_roleDrawCardData, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
    a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_CONTINUOUS_INSTANCE_DATA, "RoleContinuousInstanceData", GSLib::SceneSystem::DB::g_roleContinuousInstanceDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
    a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_CONTINUOUS_INSTANCE_PROGRESS_DATA, "RoleContinuousInstanceProgressData", GSLib::SceneSystem::DB::g_roleContinuousInstanceProgressDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
    a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_CONTINUOUS_STAGE_RESULT_DATA, "RoleContinuousStageResultData", GSLib::SceneSystem::DB::g_roleContinuousStageResultDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_RANK_DATA, "RoleRankData", GSLib::RankSystem::DB::g_roleRankDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_RANK_CN_DATA, "RoleRankCNData", GSLib::RankSystem::DB::g_roleRankCNDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
    a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_ACHIEVE_DATA, "RoleAchieveData", GSLib::AchieveSystem::DB::g_roleAchieveDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
    a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_STAGE_SYSTEM_DATA, "RoleStageSystemData", GSLib::SceneSystem::DB::g_roleStageSystemDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBTABLEID_ACCOUNT_DATA, "AccountData", GSLib::DBSystem::LG::g_accountDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBABLEID_ROLE_PET_TASK_DATA, "RolePetTaskData", GSLib::TaskSystem::DB::g_rolePetTaskColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
	a_dbCommonSystem.addDbColumn(EDBABLEID_ROLE_TASK_SYSTEM_DATA, "RoleTaskSystemData", GSLib::TaskSystem::DB::g_roleTaskSystemDataColumn, GSLib::DBSystem::EDBCNNCTTYPE_LOCAL);
    
// 	a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_DATA, "RoleData", );
// 	a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_SKILL_DATA, "SkillData", );
// 	a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_EQUIP_DATA, "EquipData", );
// 	a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_ITEM_DATA, "ItemData", );
// 	a_dbCommonSystem.addDbColumn(EDBTABLEID_ROLE_BAG_DATA, "RoleBagData", );
}

}//GSLib

#endif// __GSLIB_RELATETABLEIDDEF_HPP__