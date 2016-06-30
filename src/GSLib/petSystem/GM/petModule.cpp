#include <stdarg.h>
#include <BSLib/utility/random.h>
#include <GSLib/tracer.h>
#include <GSLib/petSystem/GM/petModule.h>
#include <GSLib/petSystem/msgPetSystem.h>
#include <GSLib/dbSystem/GM/dbSystemGM.h>
#include <GSLib/petSystem/GM/petSystemGM.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/playerSystem/GM/playerGM.h>
#include <GSLib/itemSystem/GM/itemGMMgr.h>
#include <GSLib/achieveSystem/GM/achieveModule.h>
#include <GSLib/petSystem/GM/sendItem.h>
#include "petConfigGMMgr.h"
namespace GSLib
{

namespace PetSystem
{	

namespace GM
{

CPetModule::CPetModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType)
: GSLib::PlayerSystem::GM::CRoleModuleGM(a_roleGM, a_moduleType)
, m_uniqueIDByPetID(1, PET_MAX_ID, (BSLib::uint32)INVALID_PETINDEX)
, m_timerHandleHotSpringTask(BSLib::Utility::INVALID_TIMER)
, m_hotSpringTaskTimerStatues(EHotSpringTimerStop)
{
	m_uniqueIDByPetID.setUniqueIDMgr(this);
}

CPetModule::~CPetModule()
{
	;
}

void CPetModule::preInit(bool isFirst)
{
	 if(isFirst)
	 {
         BSLib::uint32 level = 1;
         m_hotSpring.setLevel(level);
         _addHotSpringTaskPassTimeTimer();
		 return;
	 }
}

void CPetModule::postInit(bool isFirst)
{
}

void CPetModule::initToClient()
{
}

void CPetModule::final()
{
	m_hotSpring.final();
    _delHotSpringTaskPassTimeTimer();
    _removeAllPet();
}

void CPetModule::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPetSystemGC2GMReqExpandHotSpring, &BSLib::Framework::CreateCMessage<CMsgPetSystemGC2GMReqExpandHotSpring>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPetSystemGC2GMReqExpandHotSpring, &CPetModule::_onMsgPetSystemGC2GMReqExpandHotSpring, this);
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPetSystemGC2GMReqHotSpringTaskEnd, &BSLib::Framework::CreateCMessage<CMsgPetSystemGC2GMReqHotSpringTaskEnd>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPetSystemGC2GMReqHotSpringTaskEnd, &CPetModule::_onMsgPetSystemGC2GMReqHotSpringTaskEnd, this);
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPetSystemGC2GMReqPetFinishHotSpringTask, &BSLib::Framework::CreateCMessage<CMsgPetSystemGC2GMReqPetFinishHotSpringTask>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPetSystemGC2GMReqPetFinishHotSpringTask, &CPetModule::_onMsgPetSystemGC2GMReqFinishPetTask, this);
    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPetSystemGC2GMReqSendPetGift, &BSLib::Framework::CreateCMessage<CMsgPetSystemGC2GMReqSendPetGift>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPetSystemGC2GMReqSendPetGift, &CPetModule::_onMsgPetSystemGC2GMReqSendPetGift, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPetSystemGC2GMReqGetPetUnlockData, &BSLib::Framework::CreateCMessage<CMsgPetSystemGC2GMReqGetPetUnlockData>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPetSystemGC2GMReqGetPetUnlockData, &CPetModule::_onMsgPetSystemGC2GMReqGetPetUnlockData, this);
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPetSystemGC2GMReqUnlockPet, &BSLib::Framework::CreateCMessage<CMsgPetSystemGC2GMReqUnlockPet>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPetSystemGC2GMReqUnlockPet, &CPetModule::_onMsgPetSystemGC2GMReqUnlockPet, this);
    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPetSystemGC2GMReqGetPetBaseInforList, &BSLib::Framework::CreateCMessage<CMsgPetSystemGC2GMReqGetPetBaseInforList>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPetSystemGC2GMReqGetPetBaseInforList, &CPetModule::_onMsgPetSystemGC2GMReqGetPetBaseInforList, this);
    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPetSystemGC2GMReqPetGetHotSpringTaskDetail, &BSLib::Framework::CreateCMessage<CMsgPetSystemGC2GMReqPetGetHotSpringTaskDetail>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPetSystemGC2GMReqPetGetHotSpringTaskDetail, &CPetModule::_onMsgPetSystemGC2GMReqGetPetTaskDetail, this);

    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPetSystemGC2GMReqInitRolePetData, &BSLib::Framework::CreateCMessage<CMsgPetSystemGC2GMReqInitRolePetData>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPetSystemGC2GMReqInitRolePetData, &CPetModule::_onMsgPetSystemGC2GMReqInitPetData, this);
    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPetSystemGC2GMReqPetSitDown, &BSLib::Framework::CreateCMessage<CMsgPetSystemGC2GMReqPetSitDown>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPetSystemGC2GMReqPetSitDown, &CPetModule::_onMsgPetSystemGC2GMReqPetSitDown, this);
    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPetSystemGC2GMReqPetStandUp, &BSLib::Framework::CreateCMessage<CMsgPetSystemGC2GMReqPetStandUp>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPetSystemGC2GMReqPetStandUp, &CPetModule::_onMsgPetSystemGC2GMReqPetStandUp, this);
    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPetSystemGC2GMReqGetPetData, &BSLib::Framework::CreateCMessage<CMsgPetSystemGC2GMReqGetPetData>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPetSystemGC2GMReqGetPetData, &CPetModule::_onMsgPetSystemGC2GMReqGetPetData, this);

    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPetSystemGC2GMReqPetEnterPool, &BSLib::Framework::CreateCMessage<CMsgPetSystemGC2GMReqPetEnterPool>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPetSystemGC2GMReqPetEnterPool, &CPetModule::_onMsgPetSystemGC2GMReqPetEnterPool, this);
    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPetSystemGC2GMReqPetQuitPool, &BSLib::Framework::CreateCMessage<CMsgPetSystemGC2GMReqPetQuitPool>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPetSystemGC2GMReqPetQuitPool, &CPetModule::_onMsgPetSystemGC2GMReqPetQuitPool, this);
    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDPetSystemGC2GMReqPetFastQuitPool, &BSLib::Framework::CreateCMessage<CMsgPetSystemGC2GMReqPetFastQuitPool>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDPetSystemGC2GMReqPetFastQuitPool, &CPetModule::_onMsgPetSystemGC2GMReqPetFastQuitPool, this);
}

void CPetModule::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	a_msgExecMgr->delMsgExecPtr(MsgIDPetSystemGC2GMReqExpandHotSpring);
	a_msgExecMgr->delMsgExecPtr(MsgIDPetSystemGC2GMReqHotSpringTaskEnd);
	a_msgExecMgr->delMsgExecPtr(MsgIDPetSystemGC2GMReqPetFinishHotSpringTask);
	a_msgExecMgr->delMsgExecPtr(MsgIDPetSystemGC2GMReqSendPetGift);

	a_msgExecMgr->delMsgExecPtr(MsgIDPetSystemGC2GMReqGetPetUnlockData);
	a_msgExecMgr->delMsgExecPtr(MsgIDPetSystemGC2GMReqUnlockPet);
	a_msgExecMgr->delMsgExecPtr(MsgIDPetSystemGC2GMReqGetPetBaseInforList);
	a_msgExecMgr->delMsgExecPtr(MsgIDPetSystemGC2GMReqPetGetHotSpringTaskDetail);

	a_msgExecMgr->delMsgExecPtr(MsgIDPetSystemGC2GMReqInitRolePetData);
	a_msgExecMgr->delMsgExecPtr(MsgIDPetSystemGC2GMReqPetSitDown);
	a_msgExecMgr->delMsgExecPtr(MsgIDPetSystemGC2GMReqPetStandUp);
	a_msgExecMgr->delMsgExecPtr(MsgIDPetSystemGC2GMReqGetPetData);

    a_msgExecMgr->delMsgExecPtr(MsgIDPetSystemGC2GMReqPetEnterPool);
    a_msgExecMgr->delMsgExecPtr(MsgIDPetSystemGC2GMReqPetQuitPool);
    a_msgExecMgr->delMsgExecPtr(MsgIDPetSystemGC2GMReqPetFastQuitPool);
}

void CPetModule::updateDataToDB()
{
	GSLib::PlayerSystem::GM::CRoleGM* roleGM = getRoleGM();
	if (roleGM == NULL) {
		return ;
	}

	DB::CRolePetData petDataList;
    petDataList.m_hotSpringLevel = m_hotSpring.getLevel();

    petDataList.m_accountID = roleGM->getAccountID();
    petDataList.m_zoneID = roleGM->getZoneID();
    petDataList.m_roleIndex = roleGM->getRoleIndex();
	BSLib::Utility::CHashMap<PetID, CPetGM*>::iterator it = m_petHashMap.begin();
	for(;it != m_petHashMap.end();++it){
		CPetGM* pet = it->second;
		if(pet == NULL){
			BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "updateDataToDB[m_petHashMap.size=%d][pet == NULL]",m_petHashMap.size());
			continue;
		}
		DB::CPetDBData petData = pet->getPetDBData();
        petData.m_lastQuitGameTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
		petDataList.m_petList.push_back(petData);
	}

	BSLib::Utility::CStream a_stream;
	a_stream.reset();
	petDataList.serializeTo(a_stream);
	if (!updateTableData("","",EDBTABLEID_ROLE_PET_DATA,a_stream,true)){
		BSLIB_LOG_ERROR(ETT_GSLIB_EQUIPSYSTEM, "更新僚姬信息失败");
	}
}

bool CPetModule::cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
    // 防止数据重复添加
    if(a_sessionID == GSLIB_SESSIONID_CREATE_ROLE_FINISH){
        return true;
    }
    GSLib::PlayerSystem::GM::CRoleGM* role = getRoleGM();
    if (role == NULL) {
        return true;
    }
    BSLib::Database::CDBTableRow* row = a_keyTable->getRow(role->getRoleDBKey());
    if (row == NULL) {
        return true; 
    }
    
    BSLib::Utility::CStream stream;
    row->serializeTo(stream);
    DB::CRolePetData allPetData;
    allPetData.serializeFrom(stream);
    m_hotSpring.setLevel(allPetData.m_hotSpringLevel);
  
    for(std::vector<DB::CPetDBData>::iterator it = allPetData.m_petList.begin();it != allPetData.m_petList.end(); ++it){
        DB::CPetDBData petDBData = *it;
        CPetGM* curPet = _initPetFromDB(petDBData);
        if(NULL == curPet){
            return false;
        }
        _updatePet(curPet->getPetID(),curPet);
        if(curPet->getStatus() != EPetStatusFree){
           m_hotSpring.updatePetStatus(curPet->getPetID(),curPet->getStatus()); 
        }
    }
    _addHotSpringTaskPassTimeTimer();

    return true;
}

bool CPetModule::cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
	return true;
}

void CPetModule::onRoleDelete()
{
    _delHotSpringTaskPassTimeTimer();
    m_hotSpring.final();
}
void CPetModule::onRoleInactive()
{
}

bool CPetModule::updateTableData(const std::string& a_tableIndex, const std::string& a_name, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, bool a_needSave)
{
    PlayerSystem::GM::CRoleGM* role = getRoleGM();
    if (role == NULL){
        BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "获取当前角色失败");
        return false;
    }
	const SRoleKey& roleKey = role->getRoleKey();
	std::string tableKey = roleKey.getDBKey();
	if (!GSLib::PetSystem::GM::CPetSystemGM::singleton().updateTableData(tableKey, a_tableIndex, a_name, a_tableID, a_stream, a_needSave)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "更新表[TableID=%d]失败%s", a_tableID, roleKey.toLogString().c_str());
		return false;
	}
	return true;
}

bool CPetModule::updateTableData(EDBTableID a_tableID, void* a_data, BSLib::uint32 a_dataSize, bool a_needSave)
{
	if (!GSLib::PetSystem::GM::CPetSystemGM::singleton().updateTableData("", "", "", a_tableID, a_data, a_dataSize, a_needSave)) {
        PlayerSystem::GM::CRoleGM* role = getRoleGM();
        if (role == NULL){
            BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "获取当前角色失败");
            return false;
        }
        const SRoleKey& roleKey = role->getRoleKey();
		BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "更新表[TableID=%d]失败%s", a_tableID, roleKey.toLogString().c_str());
		return false;
	}
	return true;
}


bool CPetModule::addPet(PetTPID a_petTPID,bool bSave,const std::string a_reason)
{
    BSLib::uint32 petLevel = 1;
    _addNewPet(a_petTPID, petLevel);
    _outputGameLog("AddPet","[Type=%s][PetTPID=%d][PetLevel=%d]",a_reason.c_str(),a_petTPID, petLevel);

    if(bSave){
       updateDataToDB();
    }

    //_checkPetAchieve();
    return true;
}

bool CPetModule::addPetFriendlyValueByPetTPID(PetTPID a_petTPID,BSLib::uint32 a_friendlyValue)
{
    CPetGM* pet = getPetByTPID(a_petTPID);
    if(pet == NULL){
        return false;
    }
    if (!pet->addFriendlyValue(a_friendlyValue)){
        return false;
    }
    updatePetTotalBattleAttr(true);
    return true;
}

BSLib::uint32 CPetModule::getPetCounts(PetTPID a_petTPID) const
{
    BSLib::uint32 petCounts = 0;
    BSLib::Utility::CHashMap<PetID, CPetGM*>::const_iterator it = m_petHashMap.begin();
    for(;it != m_petHashMap.end();++it){
        CPetGM* data = it->second;
        if(data == NULL){
            continue;
        }
        if(data->getTPID() == a_petTPID){
            petCounts++;
        }
    }
    return petCounts;
}

CPetGM* CPetModule::getPetByTPID(PetTPID a_petTPID) const
{
    CPetGM* pet = NULL;
    BSLib::Utility::CHashMap<PetID, CPetGM*>::const_iterator it = m_petHashMap.begin();
    for(;it != m_petHashMap.end();++it){
        CPetGM* data = it->second;
        if(data == NULL){
            continue;
        }
        if(data->getTPID() == a_petTPID){
           pet = data;
           break;
        }
    }
    return pet;
}

CPetGM* CPetModule::getPet(PetID a_petID) const
{
    CPetGM *rolePet = NULL;
    m_petHashMap.getValue(a_petID,rolePet);
    return rolePet;
}

CPetGM* CPetModule::randomPet() const
{
    BSLib::uint32 petCount = m_petHashMap.size();
    if(petCount<= 0){
        return NULL;
    }
    BSLib::uint32 index = BSLib::Utility::CRandom::randomBetween(1,petCount);
    BSLib::uint32 desIndex = 0;
    BSLib::Utility::CHashMap<PetID, CPetGM*>::const_iterator it = m_petHashMap.begin();
    for(;it != m_petHashMap.end();++it){
        desIndex++;
        if(desIndex == index){
            CPetGM* curPet = it->second;
            return curPet;
        }
        if(desIndex > index){
            return NULL;
        }
    }
    return NULL;
}

bool CPetModule::_removeBagItemCount(BSLib::uint32 a_itemTPID,BSLib::uint32 a_count,std::string a_reason)
{
    GSLib::PlayerSystem::GM::CRoleGM* curRole = getRoleGM();
    if (curRole == NULL) {
        return false;
    }
    GSLib::PlayerSystem::GM::CRoleBagModuleGM * bag = curRole->getRoleBag();
    if(bag == NULL){
        return false;
    }
    bag->removeItemCount(a_itemTPID,ItemSystem::GM::EITEM_TP_IVALID,a_count,a_reason,true);

    return true;
}

bool CPetModule::_removePetUnlockItems(PetTPID a_petTPID)
{
    std::vector<ItemSystem::GM::CPrizeItem> itemArray;
    if(!ItemSystem::GM::CItemGMMgr::singleton().getSynthesisArray(a_petTPID,itemArray)){
        return false;
    }
    for(BSLib::uint32 i=0;i<itemArray.size();i++){
        ItemSystem::GM::CPrizeItem& item = itemArray[i];
        if(!_removeBagItemCount(item.m_itemTPID,item.m_itemCount,"UNLOCK_PET")){
            return false;
        }
    }
    return true;
}

bool CPetModule::_isPetReadyUnlock(PetTPID a_petTPID) const
{
    std::vector<ItemSystem::GM::CPrizeItem> itemArray;
    if(!ItemSystem::GM::CItemGMMgr::singleton().getSynthesisArray(a_petTPID,itemArray)){
        return false;
    }
    for(BSLib::uint32 i=0;i<itemArray.size();i++){
        ItemSystem::GM::CPrizeItem& item = itemArray[i];
        BSLib::uint32 curCount = 0;
        if(!_getBagItemCount(item.m_itemTPID,curCount)){
            return false;
        }
        if(curCount<item.m_itemCount){
            return false;
        }
    }
    return true;
}

const SBattleAttribute& CPetModule::getTotalBattleAttr() const
{
    return m_totalBattleAttr; 
}

bool CPetModule::sendMsgToClientToActivePetTask(PetID a_petID,bool a_notify)
{
    CPetGM* pet = getPet(a_petID);
    if(pet == NULL){
        return false;
    }

    CHotSpringTask* task = pet->activePetTask();
    if(task != NULL){
       EHotSpringTaskType subType = task->getHotSpringTaskSubType();
       EHotSpringTaskStatus status = task->getType();
       BSLIB_LOG_DEBUG(ETT_GSLIB_PETSYSTEM,"%s[sendMsgToClientToActivePetTask][m_petID=%d][TaskID=%d][subType=%d]",getRoleInfor().c_str(),a_petID,task->getTaskID(),subType);
       CMsgPetSystemGM2GCNtfActivePetTask ntf;
       ntf.m_petID = a_petID;
       ntf.m_hotSpringTaskStatus = (BSLib::uint32)status;
       ntf.m_hotSpringTaskType = (BSLib::uint32)subType;
       if(a_notify){
           return sendMsgToClient(ntf);
       }
       return true;
    }
    return false;
}

void CPetModule::updatePetTotalBattleAttr(bool a_notify)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PETSYSTEM, "updatePetTotalBattleAttr[更新伙伴总属性]");
    m_totalBattleAttr.cleanAttr();
    BSLib::Utility::CHashMap<PetID, CPetGM*>::iterator it = m_petHashMap.begin();
    for(;it != m_petHashMap.end();++it){
        CPetGM* curPet = it->second;
        if(curPet == NULL){
            return ;
        }
        SBattleAttribute attr; 
        curPet->getBattleAttr(attr);
        BSLIB_LOG_DEBUG(ETT_GSLIB_PETSYSTEM, "updatePetTotalBattleAttr[添加伙伴属性][petTPID=%d]%s",curPet->getTPID(),attr.toLogString().c_str());
        m_totalBattleAttr.addAttr(attr);
    }

    BSLIB_LOG_DEBUG(ETT_GSLIB_PETSYSTEM, "[伙伴总属性]%s",m_totalBattleAttr.toLogString().c_str());
    GSLib::PlayerSystem::GM::CRoleGM* curRole = getRoleGM();
    if(curRole == NULL){
        return;
    }
    curRole->updateTotalBattleAttr(a_notify);
}

bool CPetModule::checkUniqueID(PetID a_petID)
{
	return m_petHashMap.find(a_petID) != m_petHashMap.end();
}

void CPetModule::_onMsgPetSystemGC2GMReqExpandHotSpring(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgPetSystemGM2GCAckExpandHotSpring ack;
    ack.m_retCode = _expandHotSpring(ack.m_stream);
    sendMsgToClient(ack);
}

void CPetModule::_onMsgPetSystemGC2GMReqHotSpringTaskEnd(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgPetSystemGC2GMReqHotSpringTaskEnd* req = (CMsgPetSystemGC2GMReqHotSpringTaskEnd*)a_msg;
    CMsgPetSystemGM2GCAckHotSpringTaskEnd ack;
    EPetHotSprintEnd endStatus = (EPetHotSprintEnd)req->m_endStatus;
    ack.m_retCode = _endPetTask(req->m_petID,endStatus,ack.m_stream);
    sendMsgToClient(ack);
}

void CPetModule::_onMsgPetSystemGC2GMReqFinishPetTask(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgPetSystemGC2GMReqPetFinishHotSpringTask* req = (CMsgPetSystemGC2GMReqPetFinishHotSpringTask*)a_msg;
    CMsgPetSystemGM2GCAckPetFinishHotSpringTask ack;
    ack.m_petID = req->m_petID;
    ack.m_retCode = _finishPetTask(req->m_petID,req->m_answerID);
    sendMsgToClient(ack);
}

void CPetModule::_onMsgPetSystemGC2GMReqSendPetGift(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgPetSystemGC2GMReqSendPetGift* req = (CMsgPetSystemGC2GMReqSendPetGift*)a_msg;
    CMsgPetSystemGM2GCAckSendPetGift ack;
    ack.m_retCode = _sendPetGift(req->m_petID,req->m_stream);
    sendMsgToClient(ack);
}

void CPetModule::_onMsgPetSystemGC2GMReqGetPetUnlockData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgPetSystemGM2GCAckGetPetUnlockData ack;
    ack.m_retCode = _getPetUnlockData(ack.m_stream);
    sendMsgToClient(ack);
}

void CPetModule::_onMsgPetSystemGC2GMReqGetPetBaseInforList(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgPetSystemGC2GMReqGetPetBaseInforList* req = (CMsgPetSystemGC2GMReqGetPetBaseInforList*)a_msg;
    CMsgPetSystemGM2GCAckGetPetBaseInforList ack;
    ack.m_retCode = _getAllPetBaseInfor(ack.m_stream);
    sendMsgToClient(ack);
}

void CPetModule::_onMsgPetSystemGC2GMReqInitPetData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgPetSystemGM2GCAckInitPetData ack;
    ack.m_retCode = _getAllPetData(ack.m_stream);
    sendMsgToClient(ack);
}

void CPetModule::_onMsgPetSystemGC2GMReqGetPetTaskDetail(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgPetSystemGC2GMReqPetGetHotSpringTaskDetail* req = (CMsgPetSystemGC2GMReqPetGetHotSpringTaskDetail*)a_msg;
    CMsgPetSystemGM2GCAckPetGetHotSpringTaskDetail ack;
    ack.m_petID = req->m_petID;
    ack.m_retCode = _getPetTaskDetail(req->m_petID,(EHotSpringTaskType)req->m_taskType,ack.m_stream);
    sendMsgToClient(ack);
}

void CPetModule::_onMsgPetSystemGC2GMReqGetPetData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgPetSystemGC2GMReqGetPetData* req = (CMsgPetSystemGC2GMReqGetPetData*)a_msg;
    CMsgPetSystemGM2GCAckGetPetData ack;
    ack.m_retCode = _getPetData(req->m_petID,ack.m_stream);
    sendMsgToClient(ack);
}

void CPetModule::_onMsgPetSystemGC2GMReqUnlockPet(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgPetSystemGC2GMReqUnlockPet* req = (CMsgPetSystemGC2GMReqUnlockPet*)a_msg;
    CMsgPetSystemGM2GCAckUnlockPet ack;
    ack.m_retCode = _unlockPet(req->m_petTPID,ack.m_stream);
    sendMsgToClient(ack);
}

void CPetModule::_onMsgPetSystemGC2GMReqPetSitDown(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgPetSystemGC2GMReqPetSitDown * req = (CMsgPetSystemGC2GMReqPetSitDown*)a_msg;
    CMsgPetSystemGM2GCAckPetSitDown ack;
    ack.m_retCode = _petSitDown(req->m_petID);
    sendMsgToClient(ack);
}

void CPetModule::_onMsgPetSystemGC2GMReqPetStandUp(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgPetSystemGC2GMReqPetStandUp* req = (CMsgPetSystemGC2GMReqPetStandUp*)a_msg;
    CMsgPetSystemGM2GCAckPetStandUp ack;
    ack.m_retCode = _petStandUp(req->m_petID);
    sendMsgToClient(ack);
}

void CPetModule::_onMsgPetSystemGC2GMReqPetEnterPool(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgPetSystemGC2GMReqPetEnterPool* req = (CMsgPetSystemGC2GMReqPetEnterPool*)a_msg;
    CMsgPetSystemGM2GCAckPetEnterPool ack;
    EHotSpringType type = (EHotSpringType)req->m_hotSpringType;
    ack.m_retCode = _petEnterPool(req->m_petID,type);
    sendMsgToClient(ack);
}

void CPetModule::_onMsgPetSystemGC2GMReqPetQuitPool(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgPetSystemGC2GMReqPetQuitPool* req = (CMsgPetSystemGC2GMReqPetQuitPool*)a_msg;
    CMsgPetSystemGM2GCAckPetQuitPool ack;
    ack.m_retCode = _petQuitPool(req->m_petID,ack.m_stream);
    sendMsgToClient(ack);
}

void CPetModule::_onMsgPetSystemGC2GMReqPetFastQuitPool(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgPetSystemGC2GMReqPetFastQuitPool* req = (CMsgPetSystemGC2GMReqPetFastQuitPool*)a_msg;
    CMsgPetSystemGM2GCAckPetFastQuitPool ack;
    ack.m_retCode = _petFastQuitPool(req->m_petID,ack.m_stream);
    sendMsgToClient(ack);
}

EExpandHotSpringResult CPetModule::_expandHotSpring(BSLib::Utility::CStream& a_stream)
{
    BSLib::uint32 curHotSpringLevel = m_hotSpring.getLevel();
    BSLib::uint32 maxHotSpringLevel = CPetConfigGMMgr::singleton().getHotSpringMaxLevel();
    if(curHotSpringLevel >= maxHotSpringLevel){
        return EEXPANDHOTSPRING_RESULT_LEVEL_LIMIT;
    }
    curHotSpringLevel++;
    BSLib::uint32 needDiamond = CPetConfigGMMgr::singleton().getExpandHotSpringNeedDiamond(curHotSpringLevel);
    GSLib::PlayerSystem::GM::CRoleGM* role = getRoleGM();
    if(role == NULL){
        return EEXPANDHOTSPRING_RESULT_FAIL;
    }
    // TODO:vip功能添加后实现 vip等级条件判断（预留）

    BSLib::uint32 curDiamond = role->getTotalDiamond();
    if(curDiamond < needDiamond){
        BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%s[ExpandHotSpring][EEXPANDHOTSPRING_RESULT_DIAMOND_LIMIT][curDiamond=%d][needDiamond=%d]",getRoleInfor().c_str(),curDiamond,needDiamond);
        return EEXPANDHOTSPRING_RESULT_DIAMOND_LIMIT;
    }
    BSLib::uint32 diamond = needDiamond;
    if(!role->delDiamond(diamond,"EXPAND_HOTSPRING",true)){
        BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%s[ExpandHotSpring][EEXPANDHOTSPRING_RESULT_FAIL][curDiamond=%d][needDiamond=%d]",getRoleInfor().c_str(),curDiamond,needDiamond);
        return EEXPANDHOTSPRING_RESULT_FAIL;
    }

    m_hotSpring.setLevel(curHotSpringLevel);
    m_hotSpring.serializeTo(a_stream);
    updateDataToDB();

    return EEXPANDHOTSPRING_RESULT_SUCCESS;
}

EPetTaskFinishResult CPetModule::_finishPetTask(PetID a_petID,BSLib::uint32 a_answerID)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PETSYSTEM, "_finishPetTask[a_petID=%d][a_answerID=%d]",a_petID,a_answerID);
    PetID petID = a_petID;
    CPetGM* pet = getPet(petID);
    if(pet == NULL){
        return EPETTASKFINISH_RESULT_INVALID_PETID;
    }

    BSLib::uint32 taskID =pet->getCurTaskID();
    CHotSpringTask* task = CPetConfigGMMgr::singleton().getHotSpringTask(taskID); 
    if(task == NULL){
        return EPETTASKFINISH_RESULT_INVALID_TASK;
    }

    EHotSpringTaskType type = task->getHotSpringTaskSubType();
    if(type == EHotSpringTaskTypeGetGift){
        if(a_answerID == 0){
            const BSLib::uint32 itemTPID = task->getItemTPID();
            if(itemTPID != 0){
                BSLib::uint32 curCount = 0;
                if(!_getBagItemCount(itemTPID,curCount)){
                    return EPETTASKFINISH_RESULT_FAIL;
                }
                if(curCount<1){
                    return EPETTASKFINISH_RESULT_ITEM_LIMIT;
                }
                BSLIB_LOG_DEBUG(ETT_GSLIB_PETSYSTEM, "---完成索要任务消耗物品[m_itemTPID=%d][m_itemCount=1]---",itemTPID);
                _removeBagItemCount(itemTPID,1,"HOTSPRING_PETTASK");
            }
        }
    }

    if(!pet->finishPetTask(a_answerID)){
        return EPETTASKFINISH_RESULT_INVALID_TASK;
    }

    updateDataToDB();
    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%s[_finishPetTask][status=%d][m_petID=%d][TaskID=%d][type=%d]",getRoleInfor().c_str(),task->getType(),a_petID,task->getTaskID(),type);
    return EPETTASKFINISH_RESULT_SUCCESS;
}


EHotSpringTaskEndResult CPetModule::_endPetTask(PetID a_petID,EPetHotSprintEnd a_endStatus,BSLib::Utility::CStream& a_stream)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PETSYSTEM, "_endPetTask[a_petID=%d][a_endStatus=%d]",a_petID,a_endStatus);
    CPetGM* pet = getPet(a_petID);
    if(pet == NULL){
        return EHOTSPRINGTASK_END_RESULT_INVALID_PETID;
    }

    if(!pet->endPetTask(a_endStatus,a_stream)){
        return EHOTSPRINGTASK_END_RESULT_FAIL;
    }

    updateDataToDB();

    return EHOTSPRINGTASK_END_RESULT_SUCCESS;
}

ESendPetGiftResult CPetModule::_sendPetGift(PetID a_petID,BSLib::Utility::CStream& a_stream)
{
    BSLib::uint32 petID = a_petID;
    CPetGM *pet = getPet(petID);
    if (NULL == pet){
        return ESENDPET_GIFT_RESULT_INVALID_PETID;
    }

    CSendItem item;
    item.serializeFrom(a_stream);
    const std::vector<ItemSystem::GM::CPrizeItem>& itemArray = item.getItemArray();
    for(BSLib::uint32 i=0;i<itemArray.size();i++){
        const ItemSystem::GM::CPrizeItem& item = itemArray[i];
        BSLib::uint32 curCount = 0;
        if(!_getBagItemCount(item.m_itemTPID,curCount)){
            return ESENDPET_GIFT_RESULT_FAIL;
        }
        if(curCount<item.m_itemCount){
            return ESENDPET_GIFT_RESULT_ITEM_LIMIT;
        }
    }
    BSLib::uint32 totalFriendlyValue = 0;
    for(BSLib::uint32 i=0;i<itemArray.size(); ++i){
        const ItemSystem::GM::CPrizeItem item = itemArray[i];
        if (ItemSystem::GM::CItemGMMgr::singleton().getType(item.m_itemTPID) != ItemSystem::GM::EITEM_TP_PROP_PET_FRIENDLY){
            return ESENDPET_GIFT_RESULT_INVALID_GIFT;
        }
		ItemSystem::GM::CItemDataGM* petItem = ItemSystem::GM::CItemGMMgr::singleton().getItem(pet->getTPID());
		if (petItem == NULL) {
			return ESENDPET_GIFT_RESULT_FAIL;
		}
		bool isFavoriate = petItem->getSpecfunc3() == petItem->getSpecfunc3();
        BSLib::uint32 addFriendlyValue = ItemSystem::GM::CItemGMMgr::singleton().getPetAddFriendlyValue(isFavoriate, item.m_itemTPID);
        addFriendlyValue = addFriendlyValue*item.m_itemCount;
        if(ItemSystem::GM::CItemGMMgr::singleton().isPetLovelyItems(pet->getTPID(),item.m_itemTPID)){
            addFriendlyValue = addFriendlyValue*2;
        }
        totalFriendlyValue += addFriendlyValue;
    }
    pet->addFriendlyValue(totalFriendlyValue);
    _sendGift(itemArray,"HOTSPRING_PETTASK");
    return ESENDPET_GIFT_RESULT_SUCCESS;
}

EGetPetUnlockDataResult CPetModule::_getPetUnlockData(BSLib::Utility::CStream& a_stream) const
{
    std::vector<ItemTPID> petTPIDArrays;
    if(!ItemSystem::GM::CItemGMMgr::singleton().getPetTPIDArray(petTPIDArrays)){
        return EGETPETUNLOCKDATARESULT_FAIL;
    }
    CPetUnlockData petUnlockData;
    for(BSLib::uint32 i=0;i<petTPIDArrays.size();++i){
        ItemTPID tpid = petTPIDArrays[i];
        CPetGM* pet = getPetByTPID(tpid);
        if(pet == NULL){
            SPetUnlockItem item;
            item.m_petID = 0;
            item.m_petTPID = tpid;
            if(!_isPetReadyUnlock(tpid)){
                item.m_petUnlockStatus = EPetStatusCannotUnlock;
            }
            else{
                item.m_petUnlockStatus = EPetStatusReadyUnlock;
            }
            petUnlockData.addItem(item);
            continue;
        }
        SPetUnlockItem item;
        item.m_petID = pet->getPetID();
        item.m_petTPID = tpid;
        item.m_petUnlockStatus = EPetStatusUnlocked;
        petUnlockData.addItem(item);
    }
    petUnlockData.serializeTo(a_stream);

    return EGETPETUNLOCKDATARESULT_SUCCESS;
}

EGetInitRolePetDataResult CPetModule::_getAllPetData(BSLib::Utility::CStream& a_stream) const
{
    if(!_getPetSystemDetailInfor(a_stream)){
        return EGET_INITROLEPETDATA_RESULT_FAIL;
    }

    return EGET_INITROLEPETDATA_RESULT_SUCCESS;
}

EGetPetBaseInforListResult CPetModule::_getAllPetBaseInfor(BSLib::Utility::CStream& a_stream) const
{
    if(!_getPetBaseInforList(a_stream)){
        return EGET_PETBASEINFORLIST_RESULT_FAIL;
    }

    return EGET_PETBASEINFORLIST_RESULT_SUCCESS;
}

EPetGetHotSpringTaskDetailResult CPetModule::_getPetTaskDetail(PetID a_petID,EHotSpringTaskType a_type,BSLib::Utility::CStream& a_stream) const
{
    CPetGM* pet = getPet(a_petID);
    if (pet == NULL) {
        return EPETGET_HOTSPRING_TASKDETAIL_RESULT_FAIL;
    }
    if(!pet->getPetTaskDetail(a_type,a_stream)){
        return EPETGET_HOTSPRING_TASKDETAIL_RESULT_FAIL;
    }

    return EPETGET_HOTSPRING_TASKDETAIL_RESULT_SUCCESS;
}

EGetPetDataResult CPetModule::_getPetData(PetID a_petID,BSLib::Utility::CStream& a_stream) const
{
    CPetGM *desPet = getPet(a_petID);
    if (NULL == desPet){
        return EGETPETDATA_RESULT_INVALID_PETID;
    }
    if(!desPet->serializeToClient(a_stream)){
        return EGETPETDATA_RESULT_FAIL;
    }

    return EGETPETDATA_RESULT_SUCCESS;
}

EUnlockPetResult CPetModule::_unlockPet(PetTPID a_petTPID,BSLib::Utility::CStream& a_stream)
{
    if(ItemSystem::GM::EMAIN_TP_PET != ItemSystem::GM::CItemGMMgr::singleton().getMainType(a_petTPID)){
        return EUNLOCKPET_RESULT_INVALID_PETTPID;
    }
    CPetGM *pet = getPetByTPID(a_petTPID);
    if (NULL != pet){
        return EUNLOCKPET_RESULT_ALREADY_UNLOCK;
    }
    if(!_isPetReadyUnlock(a_petTPID)){
        return EUNLOCKPET_RESULT_METARIAL_LIMIT;
    }
    if(!addPet(a_petTPID, true)){
        return EUNLOCKPET_RESULT_FAIL;
    }
    if(!_removePetUnlockItems(a_petTPID)){
        return EUNLOCKPET_RESULT_FAIL;
    }
    CPetGM *newPet = getPetByTPID(a_petTPID);
    if (NULL == newPet){
        return EUNLOCKPET_RESULT_FAIL;
    }
	updatePetTotalBattleAttr(true);

    newPet->serializeToClient(a_stream);
    updateDataToDB();

    return EUNLOCKPET_RESULT_SUCCESS;
}

EPetSitDownResult CPetModule::_petSitDown(PetID a_petID)
{
    CPetGM *pet = getPet(a_petID);
    if (NULL == pet){
       return EPETSITDOWN_RESULT_INVALID_PETID;
    }
    if(pet->getStatus() == EPetStatusSit){
       return EPETSITDOWN_RESULT_ALREADY_SITDOWN;
    }
    if(pet->getStatus() == EPetStatusInSpring){
       return EPETSITDOWN_RESULT_ALREADY_INPOOL;
    }
	if (m_hotSpring.getHelpPetCount() >= m_hotSpring.getMaxPetCount()) {
		return EPETSITDOWN_RESULT_NO_SIT_PLACE;
	}

    // 修改温泉数据
    if(!m_hotSpring.updatePetStatus(a_petID,EPetStatusSit)){
        return EPETSITDOWN_RESULT_FAIL;
    }

    // 修改状态
    pet->sitDown();
    updateDataToDB();

    return EPETSITDOWN_RESULT_SUCCESS;
}

EPetStandUpResult CPetModule::_petStandUp(PetID a_petID)
{
    CPetGM *pet = getPet(a_petID);
    if (NULL == pet){
        return EPETSTANDUP_RESULT_INVALID_PETID;
    }
    if(pet->getStatus() != EPetStatusSit){
        return EPETSTANDUP_RESULT_NOT_SITDOWN;
    }
    // 修改温泉数据
    if(!m_hotSpring.updatePetStatus(a_petID,EPetStatusFree)){
        return EPETSTANDUP_RESULT_FAIL;
    }

    // 修改状态
    pet->standUp();
    updateDataToDB();

    return EPETSTANDUP_RESULT_SUCCESS;
}

EPetEnterPoolResult CPetModule::_petEnterPool(PetID a_petID,EHotSpringType a_hotSpringType)
{
    if(m_hotSpring.isPoolFull()){
        return EPETENTERPOOL_ALREADY_FULL;
    }
    CPetGM *pet = getPet(a_petID);
    if (NULL == pet){
        return EPETENTERPOOL_RESULT_INVALID_PETID;
    }
    if(pet->getStatus() == EPetStatusInSpring){
        return EPETENTERPOOL_ALREADY_INPOOL;
    }

    if(pet->getStatus() == EPetStatusSit){
        return EPETENTERPOOL_ALREADY_SITDOWN;
    }

    // 修改温泉数据
    if(!m_hotSpring.updatePetStatus(a_petID,EPetStatusInSpring)){
        return EPETENTERPOOL_RESULT_FAIL;
    }

    // 修改状态
    pet->enterPool(a_hotSpringType);
    updateDataToDB();

    return EPETENTERPOOL_RESULT_SUCCESS;
}

EPetQuitPoolResult CPetModule::_petQuitPool(PetID a_petID,BSLib::Utility::CStream& a_stream)
{
    CPetGM *pet = getPet(a_petID);
    if (NULL == pet){
        return EPETQUITPOOL_RESULT_INVALID_PETID;
    }
    if(pet->getStatus() != EPetStatusInSpring){
        return EPETQUITPOOL_RESULT_NOT_INPOOL;
    }
    // 修改温泉数据
    if(!m_hotSpring.updatePetStatus(a_petID,EPetStatusFree)){
        return EPETQUITPOOL_RESULT_FAIL;
    }

    // 修改状态
    pet->quitPool(false);
    if(!pet->serializeToClient(a_stream)){
       return EPETQUITPOOL_RESULT_FAIL;
    }
    updateDataToDB();

    return EPETQUITPOOL_RESULT_SUCCESS;
}

EPetFastQuitPoolResult CPetModule::_petFastQuitPool(PetID a_petID,BSLib::Utility::CStream& a_stream)
{
    CPetGM *pet = getPet(a_petID);
    if (NULL == pet){
        return EPET_FASTQUITPOOL_RESULT_INVALID_PETID;
    }
    if(pet->getStatus() != EPetStatusInSpring){
        return EPET_FASTQUITPOOL_RESULT_NOT_INPOOL;
    }

    GSLib::PlayerSystem::GM::CRoleGM* role = getRoleGM();
    if(role == NULL){
        return EPET_FASTQUITPOOL_RESULT_FAIL;
    }
    BSLib::uint32 needDiamond = pet->getFastFinishNeedDiamond();
    BSLib::uint32 curDiamond = role->getTotalDiamond();
    if(curDiamond < needDiamond){
        BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sFastQuitPool[ERESETATTR_RESULT_DIAMOND_LIMIT][m_petID=%d][curDiamond=%d][needDiamond=%d]",getRoleInfor().c_str(),a_petID,curDiamond,needDiamond);
        return EPET_FASTQUITPOOL_RESULT_DIAMOND_LIMIT;
    }
    BSLib::uint32 diamond = needDiamond;
    if(!role->delDiamond(diamond,"PET_FAST_QUITPOOL",true)){
        BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM,"%sResetAttr[ERESETATTR_RESULT_FAIL][m_petID=%d][curDiamond=%d][needDiamond=%d]",getRoleInfor().c_str(),a_petID,curDiamond,needDiamond);
        return EPET_FASTQUITPOOL_RESULT_FAIL;
    }
    // 修改温泉数据
    if(!m_hotSpring.updatePetStatus(a_petID,EPetStatusFree)){
        return EPET_FASTQUITPOOL_RESULT_FAIL;
    }

    // 修改状态
    pet->quitPool(true);
    if(!pet->serializeToClient(a_stream)){
        return EPET_FASTQUITPOOL_RESULT_FAIL;
    }
    updateDataToDB();

    return EPET_FASTQUITPOOL_RESULT_SUCCESS;
}

CPetGM*  CPetModule::_addNewPet(const PetTPID a_petTPID,const BSLib::uint32 a_petFriendlyLevel)
{
    DB::CPetDBData petData;
    petData.m_petID = m_uniqueIDByPetID.allocateID();
    if (!m_uniqueIDByPetID.isValidID(petData.m_petID)) {
        BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "[ID分配失败]");
        return NULL;
    }
    petData.m_petTPID = a_petTPID;
    petData.m_friendlyLevel = a_petFriendlyLevel;
    petData.m_friendlyValue = 0;
    petData.m_hotSpringTaskPassTime = 0;
    petData.m_hotSpringTaskMaxTime = 0;
	CPetGM* pet = new CPetGM(petData,this);
	if (pet == NULL){
		BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "_addNewPet[a_petID=%d][a_petTPID=%d]",petData.m_petID,a_petTPID);
		return NULL;
	}

    pet->init(true);
    _updatePet(petData.m_petID,pet);
	return pet;
}

CPetGM* CPetModule::_initPetFromDB(DB::CPetDBData& petData)
{
	CPetGM* newPet = new CPetGM(petData,this);
	if (newPet == NULL){
		BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "_initPetData[a_petID=%d][a_petTPID=%d]",petData.m_petID,petData.m_petTPID);
		return NULL;
	}
	newPet->init();
	return newPet;
}

bool CPetModule::_getBagItemCount(BSLib::uint32 a_metarialID,BSLib::uint32& a_metarialCount) const
{
    GSLib::PlayerSystem::GM::CRoleGM* curRole = getRoleGM();
    if (curRole == NULL) {
        return false;
    }
    GSLib::PlayerSystem::GM::CRoleBagModuleGM * bag = curRole->getRoleBag();
    if(bag == NULL){
        return false;
    }
    a_metarialCount = bag->getItemCount(a_metarialID);

    return true;
}

bool CPetModule::_getPetSystemDetailInfor(BSLib::Utility::CStream& stream) const
{
    stream.reset();
    m_hotSpring.serializeTo(stream);
    BSLib::Utility::CHashMap<PetID, CPetGM*>::const_iterator it = m_petHashMap.begin();
    BSLib::uint32 count = (BSLib::uint32)m_petHashMap.size();
    stream << count;
    for(;it != m_petHashMap.end();++it){
        CPetGM* curPet = it->second;
        if(curPet == NULL){
            BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "_serializeTo[m_petHashMap.size=%d][pet == NULL]",m_petHashMap.size());
            return false;
        }
        curPet->serializeToClient(stream);
    }
    return true;
}

bool CPetModule::_getPetBaseInforList(BSLib::Utility::CStream& stream) const
{
    stream.reset();
    BSLib::Utility::CHashMap<PetID, CPetGM*>::const_iterator it = m_petHashMap.begin();
    BSLib::uint32 count = (BSLib::uint32)m_petHashMap.size();
    stream << count;
    for(;it != m_petHashMap.end();++it){
        CPetGM* curPet = it->second;
        if(curPet == NULL){
            return false;
        }
        curPet->getBaseInfor(stream);
    }
    return true;
}

void CPetModule::_updatePet(PetID a_petID,CPetGM* a_pet)
{
    m_petHashMap.setValue(a_petID,a_pet);
}

void CPetModule::_checkPetAchieve()
{
    BSLib::uint32 achieve_1100_count = 0;
    BSLib::uint32 achieve_1101_count = 0;
    BSLib::uint32 achieve_1102_count = 0;
    BSLib::Utility::CHashMap<PetID, CPetGM*>::iterator it = m_petHashMap.begin();
    for(;it != m_petHashMap.end();++it){
        CPetGM* curPet = it->second;
        if(curPet == NULL){
            BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "_serializeTo[m_petHashMap.size=%d][pet == NULL]",m_petHashMap.size());
            return ;
        }
        BSLib::uint32 quality = curPet->getFriendlyLevel();
        if (quality == 1){
            achieve_1100_count++;
        }
        else if(quality == 2){
            achieve_1101_count++;
        }
         
        BSLib::uint32 starLevel = curPet->getFriendlyLevel();
        if(starLevel == 5){
            achieve_1102_count++;
        }
    }

    if (achieve_1100_count != 0){
        BSLib::Utility::CStream stream;
        stream.reset();
        PlayerSystem::GM::CRoleGM* role = getRoleGM();
        if (role == NULL){
            BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "获取当前角色失败");
            return;
        }
        const SRoleKey& roleKey = role->getRoleKey();
        roleKey.serializeTo(stream);
        BSLib::uint32 subID =  SUB_ACHIEVE_PET_COLOR_PURPLE; 
        BSLib::uint32 level = achieve_1100_count; 
        stream << subID;
        stream << level;
        //GFLib::CommonServer::CEventMgr::singleton().sendEvent(EEVENTID_ACHIEVE_PET,stream);
    }
    if (achieve_1101_count != 0){
        BSLib::Utility::CStream stream;
        stream.reset();
        PlayerSystem::GM::CRoleGM* role = getRoleGM();
        if (role == NULL){
            BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "获取当前角色失败");
            return;
        }
        const SRoleKey& roleKey = role->getRoleKey();
        roleKey.serializeTo(stream);
        BSLib::uint32 subID =  SUB_ACHIEVE_PET_COLOR_YELLOW; 
        BSLib::uint32 level = achieve_1101_count; 
        stream << subID;
        stream << level;
        //GFLib::CommonServer::CEventMgr::singleton().sendEvent(EEVENTID_ACHIEVE_PET,stream);
    }
    if (achieve_1102_count != 0){
        BSLib::Utility::CStream stream;
        stream.reset();
        PlayerSystem::GM::CRoleGM* role = getRoleGM();
        if (role == NULL){
            BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "获取当前角色失败");
            return;
        }
        const SRoleKey& roleKey = role->getRoleKey();
        roleKey.serializeTo(stream);
        BSLib::uint32 subID =  SUB_ACHIEVE_PET_COLOR_STARLEVEL; 
        BSLib::uint32 level = achieve_1102_count; 
        stream << subID;
        stream << level;
        //GFLib::CommonServer::CEventMgr::singleton().sendEvent(EEVENTID_ACHIEVE_PET,stream);
    }
}

bool CPetModule::_addHotSpringTaskPassTimeTimer()
{
    BSLib::Utility::CTimerServer* timer = CPetSystemGM::singleton().getTimerServer(); 
    if (timer == NULL) {
        return false;
    }
	if (m_timerHandleHotSpringTask != BSLib::Utility::INVALID_TIMER) {
		timer->delTimer(m_timerHandleHotSpringTask);
		//m_timerHandleHotSpringTask = BSLib::Utility::INVALID_TIMER;
	}
    m_timerHandleHotSpringTask =  timer->addTimer(&CPetModule::_cbTimerAddPetHotSpringTaskPassTimeCallBack,this,(BSLib::uint64)0,NULL,1000,0,-1);
    if (m_timerHandleHotSpringTask == BSLib::Utility::INVALID_TIMER) {
        return false;
    }
    m_hotSpringTaskTimerStatues = EHotSpringTimerWork;

    return true;
}

bool CPetModule::_delHotSpringTaskPassTimeTimer()
{
    BSLib::Utility::CTimerServer* timer = CPetSystemGM::singleton().getTimerServer(); 
    if (timer == NULL) {
        return false;
    }
    timer->delTimer(m_timerHandleHotSpringTask);

    return true;
}

bool CPetModule::_cbTimerAddPetHotSpringTaskPassTimeCallBack(BSLib::uint64 id, void* a_para)
{	
    if(m_hotSpringTaskTimerStatues == EHotSpringTimerStop){
        return true;
    }

    if ((m_hotSpring.getInPoolPetCount() <= 0) && (m_hotSpring.getHelpPetCount() == 0)){
        return true;
    }

    BSLib::Utility::CHashMap<PetID, CPetGM*>::iterator it = m_petHashMap.begin();
    for(;it != m_petHashMap.end();++it){
        CPetGM* curPet = it->second;
        if(curPet == NULL){
            BSLIB_LOG_ERROR(ETT_GSLIB_PETSYSTEM, "_serializeTo[m_petHashMap.size=%d][pet == NULL]",m_petHashMap.size());
            return true;
        }
        if (EPetStatusFree != curPet->getStatus()){
            curPet->addPassTime(1);
        }
    }
    return true;
}

void CPetModule::_sendGift(const std::vector<ItemSystem::GM::CPrizeItem>& a_gifts,const std::string& a_reason)
{
    const std::vector<ItemSystem::GM::CPrizeItem>& itemArray = a_gifts;
    for(BSLib::uint32 i=0;i<itemArray.size(); ++i){
        ItemSystem::GM::CPrizeItem item = itemArray[i];
        _removeBagItemCount(item.m_itemTPID,item.m_itemCount,a_reason);
    }
}

void CPetModule::_outputGameLog(const std::string& a_gameLable, const char* a_format, ...)
{
    GSLib::PlayerSystem::GM::CRoleGM* roleGM = getRoleGM();
    if (roleGM == NULL) {
        return ;
    }
    std::string strFormat;

    va_list args;
    va_start(args, a_format);

    BSLib::Utility::stringFormat(strFormat, a_format, args);

    va_end(args);

    roleGM->outputGameLog(a_gameLable,"%s",strFormat.c_str());

}

std::string CPetModule::getRoleInfor() const
{
    GSLib::PlayerSystem::GM::CRoleGM* roleGM = getRoleGM();
    if (roleGM == NULL) {
        return "";
    }
    return roleGM->getRoleLogString();
}

void CPetModule::_removeAllPet()
{
    BSLib::Utility::CHashMap<PetID, CPetGM*>::iterator it = m_petHashMap.begin();
    for (; it != m_petHashMap.end(); ++it) {
        CPetGM* data =  it->second;
        if (data == NULL) {
            continue;
        }
        data->final();
        BSLIB_SAFE_DELETE(data);
    }
    m_petHashMap.clear();
}

BSLib::uint32 CPetModule::getPetCount() const
{
	return (BSLib::uint32)m_petHashMap.size();
}

}//GM

}//PetSystem

}//GSLib

