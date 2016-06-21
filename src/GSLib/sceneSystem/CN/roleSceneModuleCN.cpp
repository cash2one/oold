#include <BSLib/database/dbTableRow.h>
#include <BSLib/utility/random.h>
#include <GSLib/sceneSystem/sceneSystemDefine.h>
#include <GSLib/sceneSystem/CN/roleSceneModuleCN.h>
#include <GSLib/playerSystem/CN/roleCN.h>
#include <GSLib/sceneSystem/msgSceneSystem.h>
#include <GSLib/rankSystem/CN/rankSystemCN.h>
#include <GSLib/rankSystem/CN/roleRankModuleCN.h>
#include <GSLib/rankSystem/cmmhdr.h>
#include <GSLib/playerSystem/CN/roleBaseInfoCNMgr.h>
#include <GSLib/playerSystem/CN/playerCNMgr.h>
#include <BSLib/utility/random.h>
#include <GSLib//tracer.h>
#include <GSLib/sceneSystem/sceneSystemCommonData.h>
#include <GSLib/sceneSystem/DB/tableSceneDB.h>

namespace GSLib
{

namespace SceneSystem
{

namespace CN
{

CRoleSceneModuleCN::CRoleSceneModuleCN(GSLib::PlayerSystem::CN::CRoleCN* a_roleGM, EModuleType a_moduleType)
:GSLib::PlayerSystem::CN::CRoleModuleCN(a_roleGM, a_moduleType)
{
	;
}

CRoleSceneModuleCN::~CRoleSceneModuleCN()
{
	;
}

void CRoleSceneModuleCN::preInit(bool isFirst)
{
	;
}

void CRoleSceneModuleCN::postInit(bool isFirst)
{
	;
}

void CRoleSceneModuleCN::initToClient()
{
	;
}

void CRoleSceneModuleCN::final()
{
	;
}

void CRoleSceneModuleCN::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSceneSystemGM2CNReqArenaAction, &BSLib::Framework::CreateCMessage<CMsgSceneSystemGM2CNReqArenaAction>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSceneSystemGM2CNReqArenaAction, &CRoleSceneModuleCN::_onMsgSceneSystemGM2CNReqArenaAction, this);
}

void CRoleSceneModuleCN::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	a_msgExecMgr->delMsgExecPtr(MsgIDSceneSystemGM2CNReqArenaAction);

}

void CRoleSceneModuleCN::updateDataToDB()
{	

}

bool CRoleSceneModuleCN::cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
	return true;
}

bool CRoleSceneModuleCN::cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
	switch(a_tableID)
	{
	case EDBTABLEID_ROLE_SCENE_ARENA_CHALLENGE_RECORD:
		{
			m_arenaChallengeRecordTable = a_keyTable;
		}	
		break;
	default:
		break;
	}

	return true; 
}

void CRoleSceneModuleCN::onRoleActive()
{
	//TODO DELETE CODE
	RankSystem::CN::Rank *rank = RankSystem::CN::CRankSystemCN::singleton().getRank(RankSystem::ERANKID_ARENA);
	if (rank != NULL) {
		SRoleKey other(0,0,0);
		SRoleKey self(getRoleCN()->getRoleKey());
		rank->update(self, other);
	}
}

void CRoleSceneModuleCN::onRoleInactive()
{
}

void CRoleSceneModuleCN::_onMsgSceneSystemGM2CNReqArenaAction(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgSceneSystemGM2CNReqArenaAction *msgReq = (CMsgSceneSystemGM2CNReqArenaAction *)a_msg;
	if (msgReq == NULL) {
		return;
	}
	switch (msgReq->m_actionID) 
	{
	case EARENA_ACTION_GET_ARENA_DATA:
		{
			_onGetRoleArenaData();				
		}
		break;
	case EARENA_ACTION_GET_ARENA_CHALLENGABLE_CHALLENGEES:
		{
			_onGetChallengableRoles();
		}
		break;
	case EARENA_ACTION_GET_ARENA_CHALLENGEE_DATA:
		{

		}
		break;
	case EARENA_ACTION_UPDATE_RECORD_TO_CHALLENGEE:
		{
			_onUpdateChallengeeArenaRecord(msgReq->m_challengeeRecord);
		}
		break;
	case EARENA_ACTION_FINISH_ARENA_CHALLENGE:
		{
			_onArenaChallengeFinished(*msgReq);
		}
	default:
		break;
	}
}

void CRoleSceneModuleCN::_onGetRoleArenaData()
{
	RankSystem::CN::Rank *rank = RankSystem::CN::CRankSystemCN::singleton().getRank(RankSystem::ERANKID_ARENA);
	if (rank != NULL) {
		SRoleKey self(getRoleCN()->getRoleKey());
		BSLib::uint32 rankNum = rank->getPlace(self);
		if (rankNum == 0) { // no ranking
			RankSystem::CN::Rank *rank = RankSystem::CN::CRankSystemCN::singleton().getRank(RankSystem::ERANKID_ARENA);
			if (rank != NULL) {
				SRoleKey other(0,0,0);
				SRoleKey self(getRoleCN()->getRoleKey());
				rank->update(self, other);
			}
		}
		CMsgSceneSystemCN2GMAckArenaAction msgAck;
		msgAck.m_actionID = EARENA_ACTION_GET_ARENA_DATA;
		msgAck.m_rank = rankNum;
		_getChallengableRoles(msgAck.m_vecChallengeeData);
		sendMsgToGameServer(msgAck);
	}
}

void CRoleSceneModuleCN::_onGetChallengableRoles()
{
	CMsgSceneSystemCN2GMAckArenaAction msgAck;
	msgAck.m_actionID = EARENA_ACTION_GET_ARENA_CHALLENGABLE_CHALLENGEES;
	_getChallengableRoles(msgAck.m_vecChallengeeData);
	sendMsgToGameServer(msgAck);
}

void CRoleSceneModuleCN::_onUpdateChallengeeArenaRecord(const SceneSystem::CArenaChallengeRecord & a_record)
{
	PlayerSystem::CN::CRoleCN* roleCn = PlayerSystem::CN::CPlayerCNMgr::singleton().getRoleCN(a_record.m_challengeeAccountID, 
																							  a_record.m_challengeeZoneID, a_record.m_challengeeRoleIndex);
	if (roleCn != NULL) {
		CMsgSceneSystemCN2GMAckArenaAction msgAck;
		msgAck.m_actionID = EARENA_ACTION_UPDATE_RECORD_TO_CHALLENGEE;
		msgAck.m_challengerRecord = a_record;
		_getChallengableRoles(msgAck.m_vecChallengeeData);
		sendMsgToGameServer(msgAck);
	}
}

void CRoleSceneModuleCN::_onArenaChallengeFinished(const CMsgSceneSystemGM2CNReqArenaAction & a_msg)
{
	GSLib::SRoleKey enemyKey(a_msg.m_challengerRecord.m_challengeeAccountID, 
		a_msg.m_challengerRecord.m_challengeeZoneID, a_msg.m_challengerRecord.m_challengeeRoleIndex);
	PlayerSystem::CN::CRoleBaseInfoCN *enemyBaseInfo = 
		PlayerSystem::CN::CRoleBaseInfoCNMgr::singleton().getRoleBaseInfoCNByRoleKey(enemyKey.getDBKey());
	if (enemyBaseInfo == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "挑战结果获取竞技场被挑战者信息失败,该挑战者Account[%d]ZoneID[%d]RoleIndex[%d]可能被删除或不存在", 
			enemyKey.getAccountID(), enemyKey.getZoneID(), enemyKey.getIndex());	
		return;
	}
	RankSystem::CN::Rank *rankMgr = RankSystem::CN::CRankSystemCN::singleton().getRank(RankSystem::ERANKID_ARENA);
	if (rankMgr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "获取竞技场排名管理器失败");	
	}
	SRoleKey self(getRoleCN()->getRoleKey());
	BSLib::uint32 roleRanking = rankMgr->getPlace(self);
	BSLib::uint32 enemyRanking = rankMgr->getPlace(enemyKey);
	CArenaChallengeRecord roleRecord(a_msg.m_challengerRecord);
	CArenaChallengeRecord enemyRecord(a_msg.m_challengeeRecord);
	roleRecord.m_newRank = roleRanking;
	enemyRecord.m_newRank = enemyRanking;
	BSLib::int32 roleChangedRank = 0;
	if (roleRecord.m_isWin && roleRanking > enemyRanking) {
		rankMgr->update(self, enemyKey);
		roleRecord.m_newRank = enemyRanking;
		enemyRecord.m_newRank = roleRanking;
		roleChangedRank = roleRanking - enemyRanking;
	}
	roleRecord.m_changedRank = roleChangedRank;
	enemyRecord.m_changedRank = roleChangedRank * (-1);
	_updateChallengeRecord(roleRecord, self);
	_updateChallengeRecord(enemyRecord, enemyKey);

	CMsgSceneSystemCN2GMAckArenaAction msgAck2Role;	
	msgAck2Role.m_actionID = EARENA_ACTION_FINISH_ARENA_CHALLENGE;
	msgAck2Role.m_challengerRecord = roleRecord;
	sendMsgToGameServer(msgAck2Role);
	PlayerSystem::CN::CRoleCN *enemy = PlayerSystem::CN::CPlayerCNMgr::singleton().getRoleCN(enemyKey);
	if (enemy != NULL && enemy->getPlayerCN() != NULL) {
		CMsgSceneSystemCN2GMAckArenaAction msgAck2Enemy;	
		msgAck2Enemy.m_actionID = EARENA_ACTION_FINISH_ARENA_CHALLENGE;
		msgAck2Enemy.m_challengerRecord = enemyRecord;
		enemy->getPlayerCN()->sendMsgToGameServer(msgAck2Enemy);
	}
}

void CRoleSceneModuleCN::_getChallengableRoles(std::vector<SceneSystem::CArenaChallengeeData> & a_vecChallengees)
{
	RankSystem::CN::Rank *rank = RankSystem::CN::CRankSystemCN::singleton().getRank(RankSystem::ERANKID_ARENA);
	if (rank != NULL) {
		SRoleKey self(getRoleCN()->getRoleKey());
		BSLib::uint32 roleRank = rank->getPlace(self);
		BSLib::uint32 count = 0;
		BSLib::uint32 maxChallengeCount = rank->getSize() < MAX_CHALLENGEE_COUNT ? rank->getSize() - 1 : MAX_CHALLENGEE_COUNT;
		if (roleRank < 7) {
			BSLib::uint32 ranking = 1;
			while (count < maxChallengeCount) {
				if (ranking != roleRank) {
					SRoleKey challengeeKey(0, 0, 0);
					rank->getRole(ranking, challengeeKey);
					if (challengeeKey.getAccountID() > 0) {
						CArenaChallengeeData challengeeData;
						if (_getChallengeeData(challengeeKey, challengeeData)) {
							a_vecChallengees.push_back(challengeeData);
						} else {
							BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "获取竞技场被挑战者信息失败,该挑战者Account[%d]ZoneID[%d]RoleIndex[%d]可能被删除或不存在", 
								challengeeData.m_accountID, challengeeData.m_zoneID, challengeeData.m_roleIndex);	
						}
						++count;
					}
				}
				++ranking;
			}
		} else {
			double param = 0;
			if (roleRank < 21) {
				param = 0.3;
			} else {
				param = 0.7;
			}
			BSLib::uint32 baseRank = _getArenaBaseRank(roleRank);
			for (BSLib::uint32 i = 0; i < maxChallengeCount; ++i) {
				BSLib::uint32 maxNum = 100;
				float factor = (float)BSLib::Utility::CRandom::randomBetween(1, maxNum) / maxNum;
				BSLib::uint32 rollRank = baseRank + (roleRank - baseRank) * i / 5 + (BSLib::int32)(factor  * param *(roleRank - baseRank) / 5);
				SRoleKey challengeeKey(0, 0, 0);
				rank->getRole(rollRank, challengeeKey);
				if (challengeeKey.getAccountID() > 0) {
					CArenaChallengeeData challengeeData;
					if (_getChallengeeData(challengeeKey, challengeeData)) {
						a_vecChallengees.push_back(challengeeData);
					} else {
						BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "获取竞技场被挑战者信息失败,该挑战者Account[%d]ZoneID[%d]RoleIndex[%d]可能被删除或不存在", 
							challengeeKey.getAccountID(), challengeeKey.getZoneID(), challengeeKey.getIndex());	
					}
				}
			}
		}
	}
}

bool CRoleSceneModuleCN::_getChallengeeData(const SRoleKey &a_roleKey, SceneSystem::CArenaChallengeeData & challengeeData)
{
	PlayerSystem::CN::CRoleBaseInfoCN *roleBaseInfo = PlayerSystem::CN::CRoleBaseInfoCNMgr::singleton().getRoleBaseInfoCNByRoleKey(a_roleKey.getDBKey());
	RankSystem::CN::Rank *rank = RankSystem::CN::CRankSystemCN::singleton().getRank(RankSystem::ERANKID_ARENA);
	if (roleBaseInfo != NULL && rank != NULL) {
		challengeeData.m_accountID = roleBaseInfo->getRoleKey().getAccountID();
		challengeeData.m_zoneID = roleBaseInfo->getRoleKey().getZoneID();
		challengeeData.m_roleIndex = roleBaseInfo->getRoleKey().getIndex();
		challengeeData.m_roleName = roleBaseInfo->getRoleName();
		challengeeData.m_roleTPID = roleBaseInfo->getRoleTPID();
		challengeeData.m_level = roleBaseInfo->getRoleLevel();
		challengeeData.m_combatPower = roleBaseInfo->getCombat();
		SRoleKey roleKey(a_roleKey);
		challengeeData.m_rank = rank->getPlace(roleKey);
		return true;
	}

	return false;
}

BSLib::uint32 CRoleSceneModuleCN::_getArenaBaseRank(BSLib::uint32 a_rank) const
{
	if (a_rank > 0 && a_rank < 7) {
		return 1;
	} else if (a_rank < 21) {
		return 2;
	} else if (a_rank < 51) {
		return 7;
	} else if (a_rank < 101) {
		return 21;
	} else if (a_rank < 401) {
		return 51;
	} else if (a_rank < 801) {
		return 101;
	} else if (a_rank < 1601) {
		return 401;
	} else if (a_rank < 3201) {
		return 801;
	} else if (a_rank < 6401) {
		return 1601;
	} else if (a_rank < 10001) {
		return 3201;
	} else {
		return 6401;
	}
}

void CRoleSceneModuleCN::_updateChallengeRecord(const CArenaChallengeRecord & a_challengeRecord, const SRoleKey & a_roleKey)
{
	if (getRoleCN() == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "updateChallengeRecordToDB:getRoleGM OR getRoleGM()->getPlayerGM() error");
		return;
	}
	DB::CArenaChallgengeRecordDB record;
	record.m_accountID = a_roleKey.getAccountID();
	record.m_zoneID = a_roleKey.getZoneID();
	record.m_roleIndex = a_roleKey.getIndex();
	record.m_recordID = a_challengeRecord.m_recordID;
	record.m_isActive = a_challengeRecord.m_isActive;
	record.m_isWin = a_challengeRecord.m_isWin;
	record.m_challengeTime = a_challengeRecord.m_challengeTime;
	record.m_newRank = a_challengeRecord.m_newRank;
	record.m_changedRank = a_challengeRecord.m_changedRank;
	record.m_challengeeZoneID = a_challengeRecord.m_challengeeZoneID;
	record.m_challengeeAccountID = a_challengeRecord.m_challengeeAccountID;
	record.m_challengeeRoleIndex = a_challengeRecord.m_challengeeRoleIndex;
	record.m_challengeeTPID = a_challengeRecord.m_challengeeTPID;
	record.m_challengeeName = a_challengeRecord.m_challengeeName;
	record.m_isRevenged = a_challengeRecord.m_isRevenged;
	BSLib::Utility::CStream stream;
	record.serializeTo(stream);
	m_arenaChallengeRecordTable->update(record.getDBKey(), stream);
	m_arenaChallengeRecordTable->saveDataToDBServer(record.getDBKey(), record.getIndexKey(), true);
}





}//GM

}//SceneSystem

}//GSLib



