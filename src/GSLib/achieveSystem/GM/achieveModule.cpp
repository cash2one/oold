//////////////////////////////////////////////////////////////////////
//	created:	2014/07/27
//	filename: 	src\GSLib\achieveSystem\GM\roleEquipModule.cpp
//	author:		zhangping
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/tracer.h>
#include <GSLib/achieveSystem/GM/achieveModule.h>
#include <GSLib/achieveSystem/msgAchieveSystem.h>
#include <GSLib/dbSystem/GM/dbSystemGM.h>
#include <GSLib/achieveSystem/DB/tableAchieveDB.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/playerSystem/GM/playerGM.h>
#include <GSLib/achieveSystem/GM/achieveSystemGM.h>
#include <GSLib/achieveSystem/GM/achieveDataGM.h>
#include <GSLib/achieveSystem/GM/achieveDataGMMgr.h>
#include <GSLib/prizeSystem/GM/rolePrizeModule.h>

namespace GSLib
{

namespace AchieveSystem
{	

namespace GM
{

CAchieveModule::CAchieveModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType)
: GSLib::PlayerSystem::GM::CRoleModuleGM(a_roleGM, a_moduleType)
{
}

CAchieveModule::~CAchieveModule()
{
	;
}

void CAchieveModule::preInit(bool isFirst)
{
	if(isFirst)
	{
	}
}

void CAchieveModule::postInit(bool isFirst)
{
    GSLib::PlayerSystem::GM::CRoleGM* roleGM = getRoleGM();
    if (roleGM == NULL) {
        return ;
    }
    roleGM->updateTotalBattleAttr(false);
}

void CAchieveModule::initToClient()
{
}

void CAchieveModule::final()
{
    BSLib::Utility::CHashMap<EAchieveType, CAchieveList* >::iterator it = m_achieveHashMap.begin();
    for(;it != m_achieveHashMap.end(); ++it){
        CAchieveList* achieveList = it->second;
        if(achieveList == NULL){
            continue;
        }
        achieveList->clear();
        BSLIB_SAFE_DELETE(achieveList); 
    }
    m_achieveHashMap.clear();
}

void CAchieveModule::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDAchieveSystemGC2GMReqGetAchieveList, &BSLib::Framework::CreateCMessage<CMsgAchieveSystemGC2GMReqGetAchieveList>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDAchieveSystemGC2GMReqGetAchieveList, &CAchieveModule::_onMsgAchieveSystemGC2GMReqGetAchieveList, this);

    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDAchieveSystemGC2GMReqGetAchievePrize, &BSLib::Framework::CreateCMessage<CMsgAchieveSystemGC2GMReqGetAchievePrize>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDAchieveSystemGC2GMReqGetAchievePrize, &CAchieveModule::_onMsgAchieveSystemGC2GMReqGetAchievePrize, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDAchieveSystemGC2GMReqSaveAchieveData, &BSLib::Framework::CreateCMessage<CMsgAchieveSystemGC2GMReqSaveAchieveData>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDAchieveSystemGC2GMReqSaveAchieveData, &CAchieveModule::_onMsgAchieveSystemGC2GMReqSaveAchieveData, this);
}

void CAchieveModule::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	a_msgExecMgr->delMsgExecPtr(MsgIDAchieveSystemGC2GMReqGetAchieveList);
	a_msgExecMgr->delMsgExecPtr(MsgIDAchieveSystemGC2GMReqGetAchievePrize);
	a_msgExecMgr->delMsgExecPtr(MsgIDAchieveSystemGC2GMReqSaveAchieveData);
}

void CAchieveModule::updateDataToDB()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_ACHIEVESYSTEM, "[updateDataToDB]");
	DB::CAchieveData achieveData;
	_getAchieveDataDB(achieveData);
	if(achieveData.m_achieveList.size() <= 0){
		return;
	}

	BSLib::Utility::CStream a_stream;
	a_stream.reset();
	achieveData.serializeTo(a_stream);
	if (!updateTableData("","",EDBTABLEID_ROLE_ACHIEVE_DATA,a_stream,true)){
		BSLIB_LOG_ERROR(ETT_GSLIB_ACHIEVESYSTEM, "[DBWRITE_ERROR][updateTableData][EDBTABLEID_ROLE_ACHIEVE_DATA]");
	}
}

void CAchieveModule::_getAchieveDataDB(DB::CAchieveData& a_achieveData)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_ACHIEVESYSTEM, "[getAchieveDataDB]");
    GSLib::PlayerSystem::GM::CRoleGM* roleGM = getRoleGM();
    if (roleGM == NULL) {
        return ;
    }

    a_achieveData.m_accountID = roleGM->getAccountID();
    a_achieveData.m_zoneID = roleGM->getZoneID();
    a_achieveData.m_roleIndex = roleGM->getRoleIndex();
    a_achieveData.m_achieveList.clear();
    BSLib::Utility::CHashMap<EAchieveType, CAchieveList* >::iterator it = m_achieveHashMap.begin();
    for(;it != m_achieveHashMap.end(); ++it){
        CAchieveList* achieveList = it->second;
        if(achieveList == NULL){
            BSLIB_LOG_ERROR(ETT_GSLIB_ACHIEVESYSTEM, "[GETEQUIP_ERROR]updateDataToDB[m_achieveHashMap.size=%d][achieve == NULL]",m_achieveHashMap.size());
            continue;
        }
        achieveList->getAchieveData(a_achieveData);
    }
}

bool CAchieveModule::cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_ACHIEVESYSTEM, "[cbSelectKeyTableData][a_sessionID=%d][a_tableID=%d]",a_sessionID,a_tableID);
    if (a_tableID == EDBTABLEID_ROLE_ACHIEVE_DATA) {
        if (a_sessionID == 0) {
            GSLib::PlayerSystem::GM::CRoleGM* roleGM = getRoleGM();
            if (roleGM == NULL) {
                return true;
            }
            BSLib::Database::CDBTableRow* row  = a_keyTable->getRow(roleGM->getRoleDBKey());
            if (row == NULL) {
                return true;
            }
            BSLib::Utility::CStream stream;
            if (!row->serializeTo(stream)) {
                return true;
            }
            DB::CAchieveData achieveData;
            achieveData.serializeFrom(stream);
            _initAchieveData(achieveData);
        }
    }
	return true;
}

bool CAchieveModule::cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_ACHIEVESYSTEM, "[cbSelectKeyIndexTableData][a_sessionID=%d][a_tableID=%d]",a_sessionID,a_tableID);
// 	GSLib::PlayerSystem::GM::CRoleGM* roleGM = getRoleGM();
// 	if (roleGM == NULL) {
// 		return true;
// 	}
// 	const BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>* tables = a_keyTable->getRows(roleGM->getRoleDBKey());
// 	if (tables == NULL) {
// 		return true;
// 	}
// 
// 	BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::const_iterator it = tables->begin();
// 	for (; it != tables->end(); ++it) {
// 		BSLib::Database::CDBTableRow* row = it->second;
// 		if (row == NULL) {
// 			continue;
// 		}
// 		DB::CAchieveData achieveData;
// 
//         BSLib::Utility::CStream acheiveStream;
//         if (!row->serializeTo(acheiveStream)) {
//             continue;
//         }
//         achieveData.serializeFrom(acheiveStream);
// 
// 		_initAchieveData(achieveData);
// 	}

	return true;
}

void CAchieveModule::cbSelectTableData(BSLib::uint32 a_sessionID, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_ACHIEVESYSTEM, "[cbSelectTableData][a_sessionID=%d][a_tableID=%d]",a_sessionID,a_tableID);

   
}

bool CAchieveModule::updateTableData(const std::string& a_tableIndex, const std::string& a_name, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, bool a_needSave)
{
    PlayerSystem::GM::CRoleGM* role = getRoleGM();
    if (role == NULL){
        BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "获取当前角色失败");
        return false;
    }
    const SRoleKey& roleKey = role->getRoleKey();
	std::string tableKey = roleKey.getDBKey();
	if (!GSLib::AchieveSystem::GM::CAchieveSystemGM::singleton().updateTableData(tableKey, a_tableIndex, a_name, a_tableID, a_stream, a_needSave)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_ACHIEVESYSTEM, "更新表[TableID=%d]失败%s", a_tableID, roleKey.toLogString().c_str());
		return false;
	}
	return true;
}

bool CAchieveModule::updateTableData(EDBTableID a_tableID, void* a_data, BSLib::uint32 a_dataSize, bool a_needSave)
{

	if (!GSLib::AchieveSystem::GM::CAchieveSystemGM::singleton().updateTableData("", "", "", a_tableID, a_data, a_dataSize, a_needSave)) {
        PlayerSystem::GM::CRoleGM* role = getRoleGM();
        if (role == NULL){
            BSLIB_LOG_ERROR(ETT_GSLIB_ACHIEVESYSTEM, "获取当前角色失败");
            return false;
        }
        const SRoleKey& roleKey = role->getRoleKey();
		BSLIB_LOG_ERROR(ETT_GSLIB_ACHIEVESYSTEM, "[DBWRITE_ERROR]更新表[TableID=%d]失败%s", a_tableID, roleKey.toLogString().c_str());
		return false;
	}
	return true;
}

BSLib::uint32 CAchieveModule::_getAchieveDataValue(BSLib::uint32 a_achieveSubID)
{
    // 获取等级相关成就，记录成就进度
    EAchieveType type = CAchieveConfigDataGMMgr::singleton().getAchieveTypeID(a_achieveSubID);

    CAchieveList* achieveList = _getAchieve(type);
    BSLib::uint32 achieveProgress = 0;
    if(achieveList == NULL){
        return achieveProgress;
    }
    
    achieveList->getAchieveItemProgress(a_achieveSubID,achieveProgress);
    return achieveProgress;
}
bool CAchieveModule::_updateAchieveData(BSLib::uint32 a_achieveSubID,BSLib::uint32 a_achieveData)
{
    std::list<SAchieveConfig*> achieveList;
    // 获取等级相关成就，记录成就进度
    CAchieveConfigDataGMMgr::singleton().getCurAchieveListBySubID(a_achieveSubID,achieveList);
    for(std::list<SAchieveConfig*>::iterator it = achieveList.begin(); it != achieveList.end() ; ++it){
        SAchieveConfig* achieve = *it;
        if (achieve == NULL){
            continue;
        }
        DB::SAchieveItem* oldAchieve = _getAchieveByAchieveID(achieve->m_achieveID);
        if(oldAchieve != NULL){
            oldAchieve->m_achieveProgress = a_achieveData;
            if(oldAchieve->m_achieveStatus == EACHIEVE_STATUS_FINISHED){
                continue;
            }
            if(achieve->param1 <= oldAchieve->m_achieveProgress){
                oldAchieve->m_achieveStatus = EACHIEVE_STATUS_FINISHED;
                CMsgAchieveSystemGM2GCNtfAchieveFinished ack;
                ack.m_achieveID = oldAchieve->m_achieveID;
                sendMsgToClient(ack);
            }
            else{
                oldAchieve->m_achieveStatus = ACHIEVE_STATUS_DOING;
            }
        }
        else{
            DB::SAchieveItem item;
            item.m_achieveID = achieve->m_achieveID;
            item.m_achieveSubType = a_achieveSubID;
            item.m_achieveProgress = a_achieveData;
            if(achieve->param1 <= a_achieveData){
                item.m_achieveStatus = EACHIEVE_STATUS_FINISHED;
                CMsgAchieveSystemGM2GCNtfAchieveFinished ack;
                ack.m_achieveID = item.m_achieveID;
                sendMsgToClient(ack);
            }
            else{
                item.m_achieveStatus = ACHIEVE_STATUS_DOING;
            }
            _addAchieve(item);
        }
    }
    return true;
}

void CAchieveModule::onEventAchieveUpdate(BSLib::Utility::EventID& a_eventID, BSLib::Utility::CStream& a_stream)
{
     BSLIB_LOG_DEBUG(ETT_GSLIB_ACHIEVESYSTEM, "[_onEventAchieveUpdate][a_eventID=%d]",a_eventID);
     EEventID eventID = (EEventID)a_eventID;
     switch (eventID)
     {
     case EEVENTID_ACHIEVE_ROLELEVEL:     //等级成就
        {
             BSLib::uint32 level = 0;
             BSLib::uint32 subAchieveID = (BSLib::uint32)SUB_ACHIEVE_LEVEL;
             a_stream >> level;
             BSLIB_LOG_DEBUG(ETT_GSLIB_ACHIEVESYSTEM, "[_onEventAchieveUpdate][a_eventID=%d][level=%d]",a_eventID,level);
             _updateAchieveData(subAchieveID,level);
        }
     	break;
     case EEVENTID_ACHIEVE_COMBAT://战斗力成就
        {
            BSLib::uint32 combat = 0;
            BSLib::uint32 subAchieveID = (BSLib::uint32)SUB_ACHIEVE_COMBAT;
            a_stream >> combat;
            BSLIB_LOG_DEBUG(ETT_GSLIB_ACHIEVESYSTEM, "[_onEventAchieveUpdate][a_eventID=%d][combat=%d]",a_eventID,combat);
            _updateAchieveData(subAchieveID,combat);
        }
     	break;
     case EEVENTID_ACHIEVE_KILL_BOSS://击杀BOSS成就
         {
             // TODO: 记录击杀BOSS成就
             BSLib::uint32 bossID= 0;
             BSLib::uint32 subAchieveID = (BSLib::uint32)SUB_ACHIEVE_KILL_BOSS;
             a_stream >> bossID;
             BSLIB_LOG_DEBUG(ETT_GSLIB_ACHIEVESYSTEM, "[_onEventAchieveUpdate][a_eventID=%d][bossID=%d]",a_eventID,bossID);
             if(!CAchieveConfigDataGMMgr::singleton().getCurAchieveSubIDByParam1(ACHIEVE_KILL_BOSS,bossID,subAchieveID)){
                 return;
             }
             _updateAchieveData(subAchieveID,bossID);
         }
         break;
     case EEVENTID_ACHIEVE_PASS_INSTANCE://通关副本成就	
         {
             // TODO: 记录通关副本成就
             BSLib::uint32 stageID= 0;
             BSLib::uint32 subAchieveID = 400;
             a_stream >> stageID;
             BSLIB_LOG_DEBUG(ETT_GSLIB_ACHIEVESYSTEM, "[_onEventAchieveUpdate][a_eventID=%d][stageID=%d]",a_eventID,stageID);
             if(!CAchieveConfigDataGMMgr::singleton().getCurAchieveSubIDByParam1(ACHIEVE_PASS_INSTANCE,stageID,subAchieveID)){
                 return;
             }
             _updateAchieveData(subAchieveID,stageID);
         }
         break;
     case EEVENTID_ACHIEVE_PVP://PVP成就
         {
             // TODO: 记录PVP成就
             BSLib::uint32 winCount = 0;
             BSLib::uint32 subAchieveID = (BSLib::uint32)SUB_ACHIEVE_PVP_WINCOUNT;
             a_stream >> subAchieveID;
             a_stream >> winCount;
             BSLIB_LOG_DEBUG(ETT_GSLIB_ACHIEVESYSTEM, "[_onEventAchieveUpdate][a_eventID=%d][winCount=%d]",a_eventID,winCount);
             _updateAchieveData(subAchieveID,winCount);
         }
         break;
     case EEVENTID_ACHIEVE_DICE://骰子成就
         {
             // TODO: 记录骰子成就
             BSLib::uint32 count = 0;
             BSLib::uint32 subAchieveID = (BSLib::uint32)SUB_ACHIEVE_DICE;
             a_stream >> count;
             BSLib::uint32 oldCount = _getAchieveDataValue(subAchieveID);
             count += oldCount;
             BSLIB_LOG_DEBUG(ETT_GSLIB_ACHIEVESYSTEM, "[_onEventAchieveUpdate][a_eventID=%d][winCount=%d]",a_eventID,count);
             _updateAchieveData(subAchieveID,count);
         }
         break;
     case EEVENTID_ACHIEVE_PASS_STAGE://连续闯关成就
         {
             // TODO: 记录连续闯关成就
             BSLib::uint32 stageLevelCount = 0;
             BSLib::uint32 subAchieveID = (BSLib::uint32)SUB_ACHIEVE_PASS_STAGE;
             a_stream >> stageLevelCount;
             BSLIB_LOG_DEBUG(ETT_GSLIB_ACHIEVESYSTEM, "[_onEventAchieveUpdate][a_eventID=%d][stageLevelCount=%d]",a_eventID,stageLevelCount);
             if(!CAchieveConfigDataGMMgr::singleton().getCurAchieveSubIDByParam1(ACHIEVE_PASS_STAGE,stageLevelCount,subAchieveID)){
                 return;
             }
             _updateAchieveData(subAchieveID,stageLevelCount);
         }
         break;
     case EEVENTID_ACHIEVE_EQUIP://装备成就
         {
             // TODO: 记录装备成就
             BSLib::uint32 achieveData = 0;
             BSLib::uint32 subAchieveID = (BSLib::uint32)SUB_ACHIEVE_EQUIP_COLOR;
             a_stream >> subAchieveID;
             a_stream >> achieveData;
             if (SUB_ACHIEVE_EQUIP_COLOR == subAchieveID){
                 _updateAchieveData(subAchieveID,achieveData);
             }
             else if (801 == subAchieveID){
                 _updateAchieveData(subAchieveID,achieveData);
             }
             else if (802 == subAchieveID){
                 _updateAchieveData(subAchieveID,achieveData);
             }
             else if (803 == subAchieveID){
                 _updateAchieveData(subAchieveID,achieveData);
             }
             else if (804 == subAchieveID){
                 _updateAchieveData(subAchieveID,achieveData);
             }
         }
         break;
     case EEVENTID_ACHIEVE_GEM://宝石成就
         {
             // TODO: 记录宝石成就
         }
         break;
     case EEVENTID_ACHIEVE_SKILL://技能成就
         {
             // TODO: 记录技能成就
             std::list<BSLib::uint32> skillLevelList;
             skillLevelList.clear();
             BSLib::uint32 skillCount = 0;
             BSLib::uint32 skillLevel =0;
             //BSLib::uint32 subAchieveID = (BSLib::uint32)SUB_ACHIEVE_SKILL;
             a_stream >> skillCount;
             for(BSLib::uint32 i=0;i<skillCount; ++i){
                 a_stream >> skillLevel;
                 skillLevelList.push_back(skillLevel);
             }
             // TODO: 更新各个等级数据
             _updateRoleSkillLevelAchieveData(1000,skillLevelList);
             _updateRoleSkillLevelAchieveData(1001,skillLevelList);
             _updateRoleSkillLevelAchieveData(1002,skillLevelList);
             _updateRoleSkillLevelAchieveData(1003,skillLevelList);
             _updateRoleSkillLevelAchieveData(1004,skillLevelList);
         }
         break;
     case EEVENTID_ACHIEVE_PET://僚机成就
         {
             // TODO: 记录僚姬成就
             BSLib::uint32 achieveData = 0;
             BSLib::uint32 subAchieveID = 1100;
             a_stream >> subAchieveID;
             a_stream >> achieveData;
             if (1100 == subAchieveID){
                 _updateAchieveData(subAchieveID,achieveData);
             }
             else if (1101 == subAchieveID){
                 _updateAchieveData(subAchieveID,achieveData);
             }
             else if (1102 == subAchieveID){
                 _updateAchieveData(subAchieveID,achieveData);
             }
         }
         break;
     case EEVENTID_ACHIEVE_CHARGEPAY://充值消费成就
         {
             BSLib::uint32 achieveData = 0;
             BSLib::uint32 subAchieveID = SUB_ACHIEVE_VIPLEVEL;
             a_stream >> subAchieveID;
             if(subAchieveID!=SUB_ACHIEVE_BUY_VIALITY){
                 a_stream >> achieveData;
             }
             
             BSLIB_LOG_DEBUG(ETT_GSLIB_ACHIEVESYSTEM, "[_onEventAchieveUpdate][a_eventID=%d][combat=%d]",a_eventID,achieveData);
             // vip等级成就
             if(subAchieveID == SUB_ACHIEVE_VIPLEVEL){
                 _updateAchieveData(subAchieveID,achieveData);
             }
             else if(subAchieveID == SUB_ACHIEVE_CHARGE){
                 _updateAchieveData(subAchieveID,achieveData);
             }
             else if(subAchieveID == SUB_ACHIEVE_BUY_VIALITY){
                 _updateAchieveData(subAchieveID,achieveData);
             }
         }
         break;
     default:
         {
         }
         break;
     }
}

BSLib::uint32 CAchieveModule::_getLevelSkillCount(BSLib::uint32 a_skillLevel,const std::list<BSLib::uint32>& a_skillLevelList)
{
    BSLib::uint32 count = 0;
     std::list<BSLib::uint32> skillLevelList = a_skillLevelList;
     std::list<BSLib::uint32>::iterator it = skillLevelList.begin();
     for(;it != skillLevelList.end();++it){
         BSLib::uint32 level = *it;
         if(level >= a_skillLevel){
             count++;
         }
     }
     return count;
}

bool CAchieveModule::_updateRoleSkillLevelAchieveData(BSLib::uint32 a_achieveSubID,const std::list<BSLib::uint32>& a_skillLevelList)
{
    std::list<SAchieveConfig*> achieveList;
    // 获取等级相关成就，记录成就进度
    CAchieveConfigDataGMMgr::singleton().getCurAchieveListBySubID(a_achieveSubID,achieveList);
    for(std::list<SAchieveConfig*>::iterator it = achieveList.begin(); it != achieveList.end() ; ++it){
        SAchieveConfig* achieve = *it;
        if (achieve == NULL){
            continue;
        }
        BSLib::uint32 skillCount = _getLevelSkillCount(achieve->param2,a_skillLevelList);

        DB::SAchieveItem* oldAchieve = _getAchieveByAchieveID(achieve->m_achieveID);
        if(oldAchieve != NULL){
            oldAchieve->m_achieveProgress = skillCount;
            if(oldAchieve->m_achieveStatus == EACHIEVE_STATUS_FINISHED){
                continue;
            }
            if(achieve->param1 <= oldAchieve->m_achieveProgress){
                oldAchieve->m_achieveStatus = EACHIEVE_STATUS_FINISHED;
                CMsgAchieveSystemGM2GCNtfAchieveFinished ack;
                ack.m_achieveID = oldAchieve->m_achieveID;
                sendMsgToClient(ack);
            }
            else{
                oldAchieve->m_achieveStatus = ACHIEVE_STATUS_DOING;
            }
        }
        else{
            DB::SAchieveItem item;
            item.m_achieveID = achieve->m_achieveID;
            item.m_achieveSubType = a_achieveSubID;
            item.m_achieveProgress = skillCount;
            if(achieve->param1 <= skillCount){
                item.m_achieveStatus = EACHIEVE_STATUS_FINISHED;
                CMsgAchieveSystemGM2GCNtfAchieveFinished ack;
                ack.m_achieveID = item.m_achieveID;
                sendMsgToClient(ack);
            }
            else{
                item.m_achieveStatus = ACHIEVE_STATUS_DOING;

            }
            _addAchieve(item);
        }
    }
    return true;
}

void CAchieveModule::onRoleDelete()
{
}

void CAchieveModule::_updateAchieveDataToClient(AchieveID a_achieveID)
{
}

void CAchieveModule::_onMsgAchieveSystemGC2GMReqGetAchieveList(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgAchieveSystemGC2GMReqGetAchieveList* req = (CMsgAchieveSystemGC2GMReqGetAchieveList*)a_msg;
	BSLIB_LOG_DEBUG(ETT_GSLIB_ACHIEVESYSTEM, "[req][GetAchieveList][m_achieveType=%d]", req->m_achieveType);
 	CMsgAchieveSystemGM2GCAckGetAchieveList ack;
    ack.m_achieveType = req->m_achieveType;
    CAchieveList *list = _getAchieve((EAchieveType)req->m_achieveType);
    if(list == NULL){
        ack.m_retCode = EGETACHIEVELIST_RESULT_SUCCESS;
        ack.m_achieveCount = 0;
        sendMsgToClient(ack);
        return;
    }

    if(!list->serializeTo(ack.m_stream)){
        ack.m_retCode = EGETACHIEVELIST_RESULT_FAIL;
        ack.m_achieveCount = 0;
        sendMsgToClient(ack);
        return;
    }
    ack.m_retCode = EGETACHIEVELIST_RESULT_SUCCESS;
    ack.m_achieveCount = list->getAchieveCount();
	sendMsgToClient(ack);
}

void CAchieveModule::_onMsgAchieveSystemGC2GMReqGetAchievePrize(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgAchieveSystemGC2GMReqGetAchievePrize* req = (CMsgAchieveSystemGC2GMReqGetAchievePrize*)a_msg;
    BSLIB_LOG_DEBUG(ETT_GSLIB_ACHIEVESYSTEM, "[req][GetAchievePrize][m_achieveID=%d]", req->m_achieveID);
    CMsgAchieveSystemGM2GCAckGetAchievePrize ack;
    ack.m_achieveID = req->m_achieveID;
    if(!_receiveAchievePrize(req->m_achieveID)){
        ack.m_retCode = EGETACHIEVEPRIZE_RESULT_FAIL;
        sendMsgToClient(ack);
        return;
    }
    ack.m_retCode = EGETACHIEVEPRIZE_RESULT_SUCCESS;
    sendMsgToClient(ack);
}

void CAchieveModule::_onMsgAchieveSystemGC2GMReqSaveAchieveData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgAchieveSystemGC2GMReqSaveAchieveData* req = (CMsgAchieveSystemGC2GMReqSaveAchieveData*)a_msg;
    BSLIB_LOG_DEBUG(ETT_GSLIB_ACHIEVESYSTEM, "[req][SaveAchieveData][m_achieveType=%d][m_achieveData=%d]", req->m_achieveSubType,req->m_achieveData);
    SAchieveConfig achieve;
    CMsgAchieveSystemGM2GCAckSaveAchieveData ack;
    if(!_saveAchieveData(req->m_achieveSubType,req->m_achieveData)){
        ack.m_retCode = ESAVEACHIEVEDATA_RESULT_FAIL;
        sendMsgToClient(ack);
        return;
    }
    ack.m_retCode = ESAVEACHIEVEDATA_RESULT_SUCCESS;
    sendMsgToClient(ack);
}

bool CAchieveModule::_receiveAchievePrize(AchieveID a_achieveID)
{
    SAchieveConfig* achieveConfig = CAchieveConfigDataGMMgr::singleton().getAchieveByAchieveID(a_achieveID);
    if ( achieveConfig == NULL){
        BSLIB_LOG_WARN(ETT_GSLIB_ACHIEVESYSTEM, "[_receiveAchievePrize][achieveID=%d][无效成就ID]",a_achieveID);
        return false;
    }
    DB::SAchieveItem*item = _getAchieveByAchieveID(a_achieveID);
    if (item == NULL) {
        BSLIB_LOG_WARN(ETT_GSLIB_ACHIEVESYSTEM, "[_receiveAchievePrize][achieveID=%d][成就未完成]",a_achieveID);
        return false;
    }
    if (item->m_achieveStatus != EACHIEVE_STATUS_FINISHED){
        BSLIB_LOG_WARN(ETT_GSLIB_ACHIEVESYSTEM, "[_receiveAchievePrize][achieveID=%d][achieveStatus=%d][当前状态不可领取]",a_achieveID,item->m_achieveStatus);
        return false;
    }
    std::string prize = achieveConfig->m_prize;
    GSLib::PlayerSystem::GM::CRoleGM* role = getRoleGM();
    if (role == NULL){
        BSLIB_LOG_ERROR(ETT_GSLIB_ACHIEVESYSTEM, "[_receiveAchievePrize][achieveID=%d][获取角色失败]",a_achieveID);
        return false;
    }
    PrizeSystem::GM::CRolePrizeModule *prizeModue = (PrizeSystem::GM::CRolePrizeModule *)role->getPlayerModuleGM(EMODULECTYPE_PRIZE);
    if (prizeModue == NULL) {
        BSLIB_LOG_ERROR(ETT_GSLIB_ACHIEVESYSTEM, "[_receiveAchievePrize][achieveID=%d][获取奖励模块失败]",a_achieveID);
        return false;
    }
    if (!prizeModue->prizeRequest(prize,true,"成就发奖")){
        return false;
    }
    item->m_achieveStatus = ACHIEVE_STATUS_PRIZED;
    return true;
}

bool CAchieveModule::_saveAchieveData(BSLib::uint32 a_achieveSubID,BSLib::uint32 a_achieveData)
{
    SAchieveConfig achieve;
    CAchieveConfigDataGMMgr::singleton().getCurAchieve(a_achieveSubID,a_achieveData,achieve);
    DB::SAchieveItem* oldAchieve = _getAchieveByAchieveID(achieve.m_achieveID);
    if(oldAchieve != NULL){
        oldAchieve->m_achieveProgress +=1;
        if(achieve.param1 <= oldAchieve->m_achieveProgress){
            oldAchieve->m_achieveStatus = EACHIEVE_STATUS_FINISHED;
        }
        else{
            oldAchieve->m_achieveStatus = ACHIEVE_STATUS_DOING;
        }
        return true; 
    }
    else{
        DB::SAchieveItem item;
        item.m_achieveID = achieve.m_achieveID;
        item.m_achieveSubType = a_achieveSubID;
        item.m_achieveProgress = a_achieveData;
        if(achieve.param1 == 1){
            item.m_achieveStatus = EACHIEVE_STATUS_FINISHED;
        }
        else{
            item.m_achieveStatus = ACHIEVE_STATUS_DOING;
        }
        return _addAchieve(item);
    }
}

void CAchieveModule::_initAchieveData(DB::CAchieveData& a_chieveData)
{
    for (BSLib::uint32 i=0; i<a_chieveData.m_achieveList.size();++i) {
       _addAchieve(a_chieveData.m_achieveList[i]);
    }
}

bool CAchieveModule::_addAchieve(const DB::SAchieveItem& a_chieveItem)
{
    EAchieveType type = CAchieveConfigDataGMMgr::singleton().getAchieveTypeID(a_chieveItem.m_achieveSubType);
    DB::SAchieveItem *item = new DB::SAchieveItem();
    if(item == NULL){
       return false; 
    }
    item->m_achieveID = a_chieveItem.m_achieveID;
    item->m_achieveStatus = a_chieveItem.m_achieveStatus;
    item->m_achieveProgress = a_chieveItem.m_achieveProgress;
    item->m_achieveSubType = a_chieveItem.m_achieveSubType;

    CAchieveList* achieveList = _getAchieve(type);
    if(achieveList != NULL){
         return achieveList->addAchieveItem(item);
    }

    achieveList = new CAchieveList(type);
    if(achieveList == NULL){
        BSLIB_SAFE_DELETE(item); 
    }

    achieveList->addAchieveItem(item);
    m_achieveHashMap.setValue(achieveList->getAchieveType(),achieveList);
    return true;
}

CAchieveList* CAchieveModule::_getAchieve(EAchieveType a_achieveType)
{
	CAchieveList* achieve = NULL;
    m_achieveHashMap.getValue(a_achieveType,achieve);
	return achieve;
}

DB::SAchieveItem* CAchieveModule::_getAchieveByAchieveID(AchieveID a_achieveID) const
{
    SAchieveConfig*  config = CAchieveConfigDataGMMgr::singleton().getAchieveByAchieveID(a_achieveID);
    if(config == NULL){
        return NULL;
    }

    //DB::SAchieveItem *item = new DB::SAchieveItem();
    CAchieveList* achieve = NULL;
    m_achieveHashMap.getValue((EAchieveType)config->m_typeID,achieve);
    if(achieve == NULL){
        return NULL;
    }

    return achieve->getAchieveItem(a_achieveID);
}

}//GM

}//AchieveSystem

}//GSLib
