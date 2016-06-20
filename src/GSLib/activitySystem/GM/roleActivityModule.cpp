//////////////////////////////////////////////////////////////////////
//	created:	2014/12/5
//	filename: 	GSLib\activitySystem\GM\roleActivityModule.cpp
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/activitySystem/GM/roleActivityModule.h>
#include <GSLib/activitySystem/msgActivitySystem.h>
#include <GSLib/prizeSystem/GM/rolePrizeModule.h>
#include <BSLib/utility/tracer.h>
#include <GSLib/tracer.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/playerSystem/GM/playerGM.h>
#include <GSLib/activitySystem/DB/tableActivityDB.h>
#include <GSLib/activitySystem/GM/activitySystemGM.h>
#include <GSLib/playerSystem/GM/playerGM.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/dbTableID.h>
#include <GSLib/activitySystem/DB/tableActivityDB.h>
#include <BSLib/utility/dateTime.h>
#include <GSLib/activitySystem/GM/activitySystemError.h>
#include <GSLib/activitySystem/GM/activitySystemDataMgr.h>
#include <BSLib/utility/dateTime.h>
#include <GSLib/petSystem/GM/petModule.h>
#include <BSLib/utility/random.h>


namespace GSLib
{

namespace ActivitySystem
{

namespace GM
{

CRoleActivityModule::CRoleActivityModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType)
: GSLib::PlayerSystem::GM::CRoleModuleGM(a_roleGM, a_moduleType)
{
}

CRoleActivityModule::~CRoleActivityModule()
{
	;
}

void CRoleActivityModule::preInit(bool isFirst)
{	

}

void CRoleActivityModule::postInit(bool isFirst)
{

}

void CRoleActivityModule::initToClient()
{	
}

void CRoleActivityModule::final()
{
	;
}

void CRoleActivityModule::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDActivitySystemGC2GMReqGetAttendenceData, &BSLib::Framework::CreateCMessage<CMsgActivitySystemGC2GMReqGetAttendenceData>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDActivitySystemGC2GMReqGetAttendenceData, &CRoleActivityModule::_onMsgActivitySystemGC2GMReqGetAttendenceData, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDActivitySystemGC2GMReqSignIn, &BSLib::Framework::CreateCMessage<CMsgActivitySystemGC2GMReqSignIn>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDActivitySystemGC2GMReqSignIn, &CRoleActivityModule::_onMsgActivitySystemGC2GMReqSignIn, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDActivitySystemGC2GMReqDrawCard, &BSLib::Framework::CreateCMessage<CMsgActivitySystemGC2GMReqDrawCard>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDActivitySystemGC2GMReqDrawCard, &CRoleActivityModule::_onMsgActivitySystemGC2GMReqDrawCard, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDActivitySystemGC2GMReqGetDrawCardInfo, &BSLib::Framework::CreateCMessage<CMsgActivitySystemGC2GMReqGetDrawCardInfo>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDActivitySystemGC2GMReqGetDrawCardInfo, &CRoleActivityModule::_onMsgActivitySystemGC2GMReqGetDrawCardInfo, this);
}

void CRoleActivityModule::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	a_msgExecMgr->delMsgExecPtr(MsgIDActivitySystemGC2GMReqGetAttendenceData);
	a_msgExecMgr->delMsgExecPtr(MsgIDActivitySystemGC2GMReqSignIn);
	a_msgExecMgr->delMsgExecPtr(MsgIDActivitySystemGC2GMReqDrawCard);
	a_msgExecMgr->delMsgExecPtr(MsgIDActivitySystemGC2GMReqGetDrawCardInfo);
}

void CRoleActivityModule::onRoleActive()
{
	if (m_roleDrawCardData.getLastDailyFreeGoldDrawCardCountResetTime() < CActivitySystemGM::singleton().getLastDailyFreeGoldDrawCardTimeTime()) {
		m_roleDrawCardData.onDailyFreeGoldDrawCardCountReset();	
		updateDrawCardTable(m_roleDrawCardData);
	}
}

void CRoleActivityModule::updateDataToDB()
{

}

bool CRoleActivityModule::cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL) {
		return false;
	}

	if (a_tableID == EDBABLEID_ROLE_ATTENDENCE_DATA) {
		m_roleAttendenceTable = a_keyTable;
		if (a_sessionID == 0) {
			DB::CRoleAttendenceDataDB roleAttendenceDataDB;
			roleAttendenceDataDB.m_accountID = getRoleGM()->getAccountID();
			roleAttendenceDataDB.m_zoneID = getRoleGM()->getZoneID();
			roleAttendenceDataDB.m_roleIndex = getRoleGM()->getRoleIndex();
			BSLib::Database::CDBTableRow* row = a_keyTable->getRow(roleAttendenceDataDB.getDBKey());
			if (row != NULL) {
				BSLib::Utility::CStream stream;
				row->serializeTo(stream);
				roleAttendenceDataDB.serializeFrom(stream);
				m_roleAttendenceData.m_prizeTableID = roleAttendenceDataDB.m_prizeTableID;
				m_roleAttendenceData.m_startTime = (BSLib::int32)roleAttendenceDataDB.m_startTime;
				m_roleAttendenceData.m_lastSignInTime = (BSLib::int32)roleAttendenceDataDB.m_lastSignInTime;
				m_roleAttendenceData.m_endTime = _calcAttendenceEndTime(m_roleAttendenceData.m_startTime) ;
				m_roleAttendenceData.m_attendenceCount = roleAttendenceDataDB.m_attendenceCount;
			}
		}
	} else if (a_tableID == EDBTABLEID_ROLE_DRAW_CARD_DATA) {
		m_roleDrawCardDataTable = a_keyTable;
		if (a_sessionID == 0) {
			DB::CRoleDrawCardDataDB roleDrawCardDataDB;
			roleDrawCardDataDB.m_accountID = getRoleGM()->getAccountID();
			roleDrawCardDataDB.m_zoneID = getRoleGM()->getZoneID();
			roleDrawCardDataDB.m_roleIndex = getRoleGM()->getRoleIndex();
			BSLib::Database::CDBTableRow* row = a_keyTable->getRow(roleDrawCardDataDB.getDBKey());
			if (row != NULL) {
				BSLib::Utility::CStream stream;
				row->serializeTo(stream);
				roleDrawCardDataDB.serializeFrom(stream);
				m_roleDrawCardData.m_curFreeGoldDrawCardCount = roleDrawCardDataDB.m_curFreeGoldDrawCardCount;
				m_roleDrawCardData.m_lastDailyFreeGoldDrawCardCountResetTime = roleDrawCardDataDB.m_lastFreeGoldDrawCardCountResetTime;
				m_roleDrawCardData.m_lastGoldDrawCardTime = roleDrawCardDataDB.m_lastGoldDrawCardTime;
				m_roleDrawCardData.m_lastDiamondDrawCardTime = roleDrawCardDataDB.m_lastDiamondDrawCardTime;
			}
		}
	}

	return true;
}

bool CRoleActivityModule::cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
	return true;
}

void CRoleActivityModule::updateRoleAttendenceTable(CRoleAttendenceData &a_roleAttendenceData)
{
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL) {
		return;
	}
	DB::CRoleAttendenceDataDB roleAttendenceDB;
	roleAttendenceDB.m_accountID = getRoleGM()->getAccountID();
	roleAttendenceDB.m_zoneID = getRoleGM()->getZoneID();
	roleAttendenceDB.m_roleIndex = getRoleGM()->getRoleIndex();
	roleAttendenceDB.m_prizeTableID = a_roleAttendenceData.m_prizeTableID;
	roleAttendenceDB.m_attendenceCount = a_roleAttendenceData.m_attendenceCount;
	roleAttendenceDB.m_startTime = a_roleAttendenceData.m_startTime;
	roleAttendenceDB.m_lastSignInTime = a_roleAttendenceData.m_lastSignInTime;
	BSLib::Utility::CStream stream;
	roleAttendenceDB.serializeTo(stream);
	m_roleAttendenceTable->update(roleAttendenceDB.getDBKey(), stream);
	m_roleAttendenceTable->saveDataToDBServer(roleAttendenceDB.getDBKey(), true);
}

void CRoleActivityModule::updateDrawCardTable(CRoleDrawCardData & a_roleDrawCardData)
{
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL) {
		return;
	}
	DB::CRoleDrawCardDataDB roleDrawCardDB;
	roleDrawCardDB.m_accountID = getRoleGM()->getAccountID();
	roleDrawCardDB.m_zoneID = getRoleGM()->getZoneID();
	roleDrawCardDB.m_roleIndex = getRoleGM()->getRoleIndex();
	roleDrawCardDB.m_lastGoldDrawCardTime = a_roleDrawCardData.m_lastGoldDrawCardTime;
	roleDrawCardDB.m_lastDiamondDrawCardTime = a_roleDrawCardData.m_lastDiamondDrawCardTime;
	roleDrawCardDB.m_curFreeGoldDrawCardCount = a_roleDrawCardData.m_curFreeGoldDrawCardCount;
	roleDrawCardDB.m_lastFreeGoldDrawCardCountResetTime = a_roleDrawCardData.m_lastDailyFreeGoldDrawCardCountResetTime;
	BSLib::Utility::CStream stream;
	roleDrawCardDB.serializeTo(stream);
	m_roleDrawCardDataTable->update(roleDrawCardDB.getDBKey(), stream);
	m_roleDrawCardDataTable->saveDataToDBServer(roleDrawCardDB.getDBKey(), true);
}

void CRoleActivityModule::_onMsgActivitySystemGC2GMReqGetAttendenceData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL) {
		return;
	}
	CRoleAttendenceData roleAttendenceData(m_roleAttendenceData);
	const BSLib::Utility::CHashMap<BSLib::uint32, CAttendenceAttr *>* attendenceAttrMap = CActivitySystemDataMgr::singleton().getAttendenceAttrMap(m_roleAttendenceData.m_prizeTableID);
	BSLib::Utility::CDateTime curTime = BSLib::Utility::CDateTime::getCurrentTime();
	BSLib::Utility::CDateTime lastSignInTime((time_t)m_roleAttendenceData.m_lastSignInTime);
	if (m_roleAttendenceData.m_attendenceCount == 0 || m_roleAttendenceData.m_attendenceCount >= MAX_SIGN_IN_DAYS  || curTime.getSeconds() > m_roleAttendenceData.m_endTime) {
		attendenceAttrMap = CActivitySystemDataMgr::singleton().getCurAttendenceAttrMap();
		roleAttendenceData.m_startTime = 0;
		roleAttendenceData.m_endTime = 0;
		roleAttendenceData.m_attendenceCount = 0;
	}
	EGetAttendenceDataResult result = EGET_ATTENDENCE_DATA_RESULT_SUCCESS;
	if (attendenceAttrMap == NULL) {
		result = EGET_ATTENDENCE_DATA_RESULT_PRIZE_TABLE_ERROR;
	}

	CMsgActivitySystemGM2GCAckGetAttendenceData msgAck;
	msgAck.m_result = result;
	msgAck.m_startTime = roleAttendenceData.m_startTime;
	msgAck.m_endTime = roleAttendenceData.m_endTime;
	msgAck.m_attendenceCount = roleAttendenceData.m_attendenceCount;
	msgAck.m_attendenceAttrMap = attendenceAttrMap;
	sendMsgToClient(msgAck);
}

void CRoleActivityModule::_onMsgActivitySystemGC2GMReqSignIn(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	BSLib::Utility::CDateTime lastSignInTime((time_t)m_roleAttendenceData.m_lastSignInTime);
	BSLib::Utility::CDateTime curTime = BSLib::Utility::CDateTime::getCurrentTime();
	EAttendenceSignInResult result(EATTENDENCE_SIGN_IN_RESULT_SUCCESS);
	if (lastSignInTime.getYear() == curTime.getYear() && lastSignInTime.getMonth() == curTime.getMonth() && lastSignInTime.getDay() == curTime.getDay()) {
		result = EATTENDENCE_SIGN_IN_RESULT_ALREADY_SIGN_IN;
	}

	if (result == EATTENDENCE_SIGN_IN_RESULT_SUCCESS) {
		if (m_roleAttendenceData.m_attendenceCount == 0 || m_roleAttendenceData.m_attendenceCount >= MAX_SIGN_IN_DAYS || curTime.getSeconds() > m_roleAttendenceData.m_endTime) {
			m_roleAttendenceData.m_attendenceCount = 0;
			m_roleAttendenceData.m_startTime = (BSLib::int32)curTime.getSeconds();
			m_roleAttendenceData.m_endTime = _calcAttendenceEndTime(m_roleAttendenceData.m_startTime);
			m_roleAttendenceData.m_prizeTableID = CActivitySystemDataMgr::singleton().getCurAttendencePrizeTable();
		}
		++m_roleAttendenceData.m_attendenceCount;
		m_roleAttendenceData.m_lastSignInTime = (BSLib::int32)curTime.getSeconds();
		const CAttendenceAttr * attendenceAttr = CActivitySystemDataMgr::singleton().getAttendenceAttr(m_roleAttendenceData.m_prizeTableID, m_roleAttendenceData.m_attendenceCount + 1);
		if (attendenceAttr == NULL) {
			BSLIB_LOG_ERROR(ETT_GSLIB_ACTIVITYSYSTEM, "Get attendence table failed AccountID[%lld] ZoneID[%d] RoleIndex[%d] TableID[%d]", getRoleGM()->getAccountID(), getRoleGM()->getZoneID(), 
				getRoleGM()->getRoleIndex(), m_roleAttendenceData.m_prizeTableID);
		} else {
			GSLib::PrizeSystem::GM::CRolePrizeModule * prizeModule = (GSLib::PrizeSystem::GM::CRolePrizeModule * )getRoleGM()->getPlayerModuleGM(EMODULECTYPE_PRIZE);
			if (prizeModule != NULL) {
				std::string senderName = toMailString("系统信息");
				std::string title = toMailString("每日签到奖励(背包满)");
				std::string content = toMailString("恭喜您获得每日签到奖励,奖励如下:");
				prizeModule->prizeRequest(attendenceAttr->m_vecPrizeItems, senderName, title, content, "SignInPrize");//todo
			}
		}
		updateRoleAttendenceTable(m_roleAttendenceData);
	}
	CMsgActivitySystemGM2GCAckSignIn msgAck;
	msgAck.m_result = result;
	if (result == EATTENDENCE_SIGN_IN_RESULT_SUCCESS) {
		msgAck.m_signInTime = m_roleAttendenceData.m_lastSignInTime;
	}
	sendMsgToClient(msgAck);
}

void CRoleActivityModule::_onMsgActivitySystemGC2GMReqDrawCard(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL) {
		return;
	}
	std::vector<CRolledItem> vecRolledItems;
	CMsgActivitySystemGC2GMReqDrawCard *msgReq = (CMsgActivitySystemGC2GMReqDrawCard  *)a_msg;
	EDrawCardResult result = _canDrawCard(msgReq->m_type, msgReq->m_count);
	if (result == EDRAW_CARD_RESULT_SUCCESS) {
		BSLib::uint32 curTime = (BSLib::uint32)BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
		BSLib::Utility::CRandom::setRandomSeed(curTime);
		if (msgReq->m_count == 1) {
			if (msgReq->m_type == DRAW_CARD_TYPE_GOLD) {
				if (m_roleDrawCardData.isGoldDrawCardFree()) {
					m_roleDrawCardData.m_lastGoldDrawCardTime = (BSLib::int32)BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
					++m_roleDrawCardData.m_curFreeGoldDrawCardCount;
					updateDrawCardTable(m_roleDrawCardData);
				} else {
					getRoleGM()->modifyGold(-DRAW_CARD_COST_GOLD_PER_TIME, "");
				}
			} else if (msgReq->m_type == DRAW_CARD_TYPE_DIAMOND) {
				if (m_roleDrawCardData.isDiamondDrawCardFree()) {
					m_roleDrawCardData.m_lastDiamondDrawCardTime = (BSLib::int32)BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
					updateDrawCardTable(m_roleDrawCardData);
				} else {
					getRoleGM()->modifyRoleResource(PlayerSystem::GM::ATTR_DIAMOND, -DRAW_CARD_COST_DIAMOND_PER_TIME, "");
				}
			}
			CRolledItem rolledItem;
			_drawCard(0, rolledItem);
			vecRolledItems.push_back(rolledItem);
		} else if (msgReq->m_count == 10) {
			if (msgReq->m_type == DRAW_CARD_TYPE_GOLD) {
				BSLib::int32 costGold = msgReq->m_count * DRAW_CARD_COST_GOLD_PER_TIME * 90 / 100;
				getRoleGM()->modifyGold(-costGold, "");
			} else if (msgReq->m_type == DRAW_CARD_TYPE_DIAMOND) {
				BSLib::int32 costDiamond = msgReq->m_count * DRAW_CARD_COST_DIAMOND_PER_TIME * 90 / 100;
				getRoleGM()->modifyGold(-costDiamond, "");
			}
			_drawTenCard(msgReq->m_type, vecRolledItems);
		}
	}
	for (std::vector<CRolledItem>::iterator itr = vecRolledItems.begin(); itr != vecRolledItems.end(); ++itr) {
		_addRolledItem(*itr);
	}
	CMsgActivitySystemGM2GCAckDrawCard msgAck;
	msgAck.m_result = result;
	if (result == EDRAW_CARD_RESULT_SUCCESS){
		BSLib::int32 curTime = (BSLib::int32)BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
		BSLib::int32 nextFreeGoldDrewCardRemainlTime = m_roleDrawCardData.m_lastGoldDrawCardTime + MAX_FREE_GOLD_DRAW_CARD_TIME - curTime ;
		BSLib::int32 nextDiamondDrewCardRemainTime = m_roleDrawCardData.m_lastDiamondDrawCardTime + MAX_FREE_DIAMOND_DRAW_CARD_TIME - curTime;
		msgAck.m_nextFreeGoldDrawCardRemaindTime = nextFreeGoldDrewCardRemainlTime > 0 ? nextFreeGoldDrewCardRemainlTime : 0;
		msgAck.m_nextFreeDiamondDrawCardRemainTime = nextDiamondDrewCardRemainTime > 0 ? nextDiamondDrewCardRemainTime : 0;
		msgAck.m_curFreeGoldDrawCardRemaindCount = 
			m_roleDrawCardData.m_curFreeGoldDrawCardCount >= DAILY_FREE_GOLD_DRAW_CARD_COUNT ? 0 : DAILY_FREE_GOLD_DRAW_CARD_COUNT -  m_roleDrawCardData.m_curFreeGoldDrawCardCount;;
	}
	msgAck.m_vecRolledItem = vecRolledItems;
	sendMsgToClient(msgAck);
}

void CRoleActivityModule::_onMsgActivitySystemGC2GMReqGetDrawCardInfo(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	BSLib::int32 curTime = (BSLib::int32)BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
	BSLib::int32 nextFreeGoldDrewCardRemainlTime = m_roleDrawCardData.m_lastGoldDrawCardTime + MAX_FREE_GOLD_DRAW_CARD_TIME - curTime ;
	BSLib::int32 nextDiamondDrewCardRemainTime = m_roleDrawCardData.m_lastDiamondDrawCardTime + MAX_FREE_DIAMOND_DRAW_CARD_TIME - curTime;
	CMsgActivitySystemGM2GCAckGetDrawCardInfo msgAck;
	msgAck.m_nextFreeGoldDrawCardRemaindTime = nextFreeGoldDrewCardRemainlTime > 0 ? nextFreeGoldDrewCardRemainlTime : 0;
	msgAck.m_nextFreeDiamondDrawCardRemainTime = nextDiamondDrewCardRemainTime > 0 ? nextDiamondDrewCardRemainTime : 0;
	msgAck.m_curFreeGoldDrawCardRemaindCount = 
		m_roleDrawCardData.m_curFreeGoldDrawCardCount >= DAILY_FREE_GOLD_DRAW_CARD_COUNT ? 0 : DAILY_FREE_GOLD_DRAW_CARD_COUNT -  m_roleDrawCardData.m_curFreeGoldDrawCardCount;
	sendMsgToClient(msgAck);
}

void CRoleActivityModule::onDailyFreeGoldDrawCardCountResetCallback()
{
	m_roleDrawCardData.onDailyFreeGoldDrawCardCountReset();	
	updateDrawCardTable(m_roleDrawCardData);
}

BSLib::int32 CRoleActivityModule::_calcAttendenceEndTime(BSLib::int32 a_startTime) const
{
	BSLib::Utility::CDateTime startTime((time_t)a_startTime);
	BSLib::int32 timeDelta = startTime.getHour() * 3600 + startTime.getMinute() * 60 + startTime.getSecond();
	BSLib::int32 endTime = (BSLib::int32)startTime.getSeconds() - timeDelta + MAX_SIGN_IN_PERIOD * 24 * 3600;
	return endTime;
}

EDrawCardResult CRoleActivityModule::_canDrawCard(EDrawCardType type, BSLib::uint16 count)
{
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL) {
		return EDRAW_CARD_RESULT_FAIL;
	}
	if (type < DRAW_CARD_TYPE_GOLD || type > DRAW_CARD_TYPE_DIAMOND) {
		return EDRAW_CARD_RESULT_ERROR_TYPE;
	}
	if (count != 1 && count != 10) {
		return EDRAW_CARD_RESULT_ERROR_COUNT;
	}
	if (type == DRAW_CARD_TYPE_GOLD) {
		if (!m_roleDrawCardData.isGoldDrawCardFree()) {
			BSLib::uint32 costGold = (count == 1 ? DRAW_CARD_COST_GOLD_PER_TIME : count  * DRAW_CARD_COST_GOLD_PER_TIME * 90 / 100);
			if (getRoleGM()->getGold() < costGold) {
				return EDRAW_CARD_RESULT_NOT_ENOUGH_GOLD;
			}
		}
	} else if (type == DRAW_CARD_TYPE_DIAMOND) {
		if (!m_roleDrawCardData.isDiamondDrawCardFree()) {
			BSLib::uint32 costDiamond = (count == 1 ? DRAW_CARD_COST_DIAMOND_PER_TIME : count  * DRAW_CARD_COST_DIAMOND_PER_TIME * 90 / 100);
			if (getRoleGM()->getTotalDiamond() < costDiamond) {
				return EDRAW_CARD_RESULT_NOT_ENOUGH_DIAMOND;
			}
		}
	}
	return EDRAW_CARD_RESULT_SUCCESS;		
}

bool CRoleActivityModule::_genRollMap(BSLib::int32 a_level, CDrawItemPool& a_drawItemPool)
{
	if (getRoleGM() == NULL) {
		return false;
	}
	PetSystem::GM::CPetModule *petModule = (PetSystem::GM::CPetModule *)getRoleGM()->getPlayerModuleGM(EMODULECTYPE_PET);
	if (petModule == NULL ) {
		return false;
	}
	const BSLib::Utility::CHashMap<BSLib::uint32, CPetCardInfo> & petCardInfoMap = CActivitySystemDataMgr::singleton().getPetCardInfoMap(a_level);
	for (BSLib::Utility::CHashMap<BSLib::uint32, CPetCardInfo>::const_iterator itr = petCardInfoMap.begin(); itr != petCardInfoMap.end(); ++itr) {
		CDrawWeightItem drawItem;
		if (petModule->getPetCounts(itr->second.m_petTPID) <= 0) {
			drawItem.m_isPet = true;
			drawItem.m_count = 1;
			drawItem.m_TPID = itr->second.m_petTPID;
			drawItem.m_weight = itr->second.m_petWeight;
		} else {
			drawItem.m_isPet = false;
			drawItem.m_TPID = itr->second.m_petPieceTPID;
			drawItem.m_count = itr->second.m_petPieceCount;
			drawItem.m_weight = itr->second.m_petPieceWeight;
		}
		a_drawItemPool.m_vecDrawItem.push_back(drawItem);
		a_drawItemPool.m_totalWeight += drawItem.m_weight;
	}
	return true;
}

void CRoleActivityModule::_rollCard(const CDrawItemPool& a_drawItemPool, CRolledItem & a_rolledItem)
{
	BSLib::uint32 roll = BSLib::Utility::CRandom::randomBetween(0, a_drawItemPool.m_totalWeight);
	BSLib::uint32 weight = 0;
	for (std::vector<CDrawWeightItem>::const_iterator itr = a_drawItemPool.m_vecDrawItem.begin(); itr != a_drawItemPool.m_vecDrawItem.end(); ++itr) {
		weight += itr->m_weight;
		if (roll <= weight) {
			a_rolledItem.m_isPet = itr->m_isPet;
			a_rolledItem.m_TPID = itr->m_TPID;
			a_rolledItem.m_count = itr->m_count;
			break;
		}
	}
}

void CRoleActivityModule::_drawCard(BSLib::int32 a_level, CRolledItem & a_rolledItem)
{
	if (getRoleGM() == NULL) {
		return;
	}
	CDrawItemPool pool;
	if (!_genRollMap(a_level, pool)) {
		return;
	}
	_rollCard(pool, a_rolledItem);
}

void CRoleActivityModule::_drawTenCard(EDrawCardType a_type, std::vector<CRolledItem> & a_vecRolledItem)
{
	BSLib::int32 totalDrawCount = 10;

	if (a_type == DRAW_CARD_TYPE_DIAMOND) {
		--totalDrawCount;
		CRolledItem rolledItem;
		_drawCard(1, rolledItem);
		a_vecRolledItem.push_back(rolledItem);
	} 
	CDrawItemPool pool;
	if (!_genRollMap(0, pool)) {
		return;
	}
	for (BSLib::int32 i = 0; i < totalDrawCount; ++i) {
		CRolledItem rolledItem;
		_rollCard(pool, rolledItem);
		a_vecRolledItem.push_back(rolledItem);
	}
}

void CRoleActivityModule::_addRolledItem(const CRolledItem & a_rolledItem)
{
	if (a_rolledItem.m_isPet) {
		PetSystem::GM::CPetModule *petModule = (PetSystem::GM::CPetModule *)getRoleGM()->getPlayerModuleGM(EMODULECTYPE_PET);
		if (petModule != NULL) {
			petModule->addPet(a_rolledItem.m_TPID, true);
			//bool b = petModule->addPet(a_rolledItem.m_TPID, true);
			//int a = 1;
		}
	} else {
		PrizeSystem::GM::CRolePrizeModule * prizeModule = (PrizeSystem::GM::CRolePrizeModule *)getRoleGM()->getPlayerModuleGM(EMODULECTYPE_PRIZE);
		if (prizeModule != NULL) {
			ItemSystem::GM::CPrizeItem item;
			item.m_itemTPID = a_rolledItem.m_TPID;
			item.m_itemCount = a_rolledItem.m_count;
			item.m_itemType = ItemSystem::GM::EITEM_TP_VIR_PET_MATERIAL;
			std::vector<ItemSystem::GM::CPrizeItem> vecPrizeItem;
			vecPrizeItem.push_back(item);
			std::string sender = toMailString("系统信息");
			std::string title = toMailString("抽卡奖励(背包满)");
			std::string conent = toMailString("恭喜您获得抽卡奖励,背包奖励如下:");
			prizeModule->prizeRequest(vecPrizeItem, sender, title, conent, "RollCards");//todo
		}

	}
}



}//GM

}

}//GSLib
