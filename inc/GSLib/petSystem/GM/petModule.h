#ifndef __GSLIB_PETSYSTEM_GM_PETMODULE_H__
#define __GSLIB_PETSYSTEM_GM_PETMODULE_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/uniqueID.h>
#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/petSystem/baseDef.h>
#include <GSLib/petSystem/GM/petGM.h>
#include <GSLib/playerSystem/GM/roleModuleGM.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/petSystem/msgPetSystem.h>
#include <GSLib/taskSystem/GM/roleTaskModule.h>
#include <GSLib/petSystem/GM/hotSpring.h>

namespace GSLib
{

namespace PetSystem
{

namespace GM
{

class CPetModule : public GSLib::PlayerSystem::GM::CRoleModuleGM,BSLib::Utility::CUniqueIDMgr<PetID>
{
public:
	CPetModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType);
	virtual ~CPetModule();

	virtual void preInit(bool isFirst);
	virtual void postInit(bool isFirst);
	virtual void initToClient();
	virtual void final();

	virtual void initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual void freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	virtual void updateDataToDB();
	virtual bool cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
	virtual bool cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
    
    virtual void onRoleDelete();
    virtual void onRoleInactive();

	bool updateTableData(const std::string& a_tableIndex, const std::string& a_name, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, bool a_needSave = false);
	bool updateTableData(EDBTableID a_tableID, void* a_data, BSLib::uint32 a_dataSize,  bool a_needSave = false);

	bool loadGameConfig(const std::string& a_configPath);

public:
    bool addPet(PetTPID a_petTPID,bool bSave = false,const std::string a_reason="");
    bool addPetFriendlyValueByPetTPID(PetTPID a_petTPID,BSLib::uint32 a_friendlyValue);

    BSLib::uint32 getPetCounts(PetTPID a_petTPID) const;
    CPetGM* getPetByTPID(PetTPID a_petTPID) const;
    CPetGM* getPet(PetID a_petID) const;
	CPetGM* randomPet() const;
	BSLib::uint32 getPetCount() const;

    const SBattleAttribute& getTotalBattleAttr() const;
    bool sendMsgToClientToActivePetTask(PetID a_petID,bool a_notify = true);
    void updatePetTotalBattleAttr(bool a_notify);

private:
	virtual bool checkUniqueID(PetID a_petID);

    void _onMsgPetSystemGC2GMReqExpandHotSpring(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgPetSystemGC2GMReqHotSpringTaskEnd(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgPetSystemGC2GMReqFinishPetTask(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgPetSystemGC2GMReqSendPetGift(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

    void _onMsgPetSystemGC2GMReqGetPetUnlockData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgPetSystemGC2GMReqGetPetBaseInforList(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgPetSystemGC2GMReqInitPetData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgPetSystemGC2GMReqGetPetTaskDetail(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgPetSystemGC2GMReqGetPetData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

    void _onMsgPetSystemGC2GMReqUnlockPet(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgPetSystemGC2GMReqPetSitDown(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgPetSystemGC2GMReqPetStandUp(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

    void _onMsgPetSystemGC2GMReqPetEnterPool(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgPetSystemGC2GMReqPetQuitPool(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgPetSystemGC2GMReqPetFastQuitPool(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
 
private:
    EExpandHotSpringResult _expandHotSpring(BSLib::Utility::CStream& a_stream);
    EPetTaskFinishResult _finishPetTask(PetID a_petID,BSLib::uint32 a_answerID);
    EHotSpringTaskEndResult _endPetTask(PetID a_petID,EPetHotSprintEnd a_endStatus,BSLib::Utility::CStream& stream);
    ESendPetGiftResult _sendPetGift(PetID a_petID,BSLib::Utility::CStream& a_stream);

    EGetPetUnlockDataResult _getPetUnlockData(BSLib::Utility::CStream& a_stream) const;
    EGetInitRolePetDataResult _getAllPetData(BSLib::Utility::CStream& a_stream) const;
    EGetPetBaseInforListResult _getAllPetBaseInfor(BSLib::Utility::CStream& a_stream) const;
    EPetGetHotSpringTaskDetailResult _getPetTaskDetail(PetID a_petID,EHotSpringTaskType a_type,BSLib::Utility::CStream& a_stream) const;
    EGetPetDataResult _getPetData(PetID a_petID,BSLib::Utility::CStream& a_stream) const;

    EUnlockPetResult _unlockPet(PetTPID a_petTPID,BSLib::Utility::CStream& a_stream);
    EPetSitDownResult _petSitDown(PetID a_petID);
    EPetStandUpResult _petStandUp(PetID a_petID);

    EPetEnterPoolResult _petEnterPool(PetID a_petID,EHotSpringType a_hotSpringType);
    EPetQuitPoolResult _petQuitPool(PetID a_petID,BSLib::Utility::CStream& a_stream);
    EPetFastQuitPoolResult _petFastQuitPool(PetID a_petID,BSLib::Utility::CStream& a_stream);

private:
    CPetGM* _addNewPet(const PetTPID a_petTPID,const BSLib::uint32 a_petFriendlyLevel);
	CPetGM* _initPetFromDB(DB::CPetDBData& petData);

private:
    bool _removeBagItemCount(BSLib::uint32 a_itemTPID,BSLib::uint32 a_count,std::string a_reason);
    bool _removePetUnlockItems(PetTPID a_petTPID);

    bool _isPetReadyUnlock(PetTPID a_petTPID) const;
    bool _getBagItemCount(BSLib::uint32 a_metarialID,BSLib::uint32& a_metarialCount) const;
	bool _getPetSystemDetailInfor(BSLib::Utility::CStream& stream) const;
    bool _getPetBaseInforList(BSLib::Utility::CStream& a_stream) const;

private:
    void _updatePet(PetID a_petID,CPetGM* a_pet);
    void _checkPetAchieve();

    bool _addHotSpringTaskPassTimeTimer();
    bool _delHotSpringTaskPassTimeTimer();
    bool _cbTimerAddPetHotSpringTaskPassTimeCallBack(BSLib::uint64, void* a_para);

private:
    void _sendGift(const std::vector<ItemSystem::GM::CPrizeItem>& a_gifts,const std::string& a_reason);

private:
    void _outputGameLog(const std::string& a_gameLable, const char* a_format, ...);
    std::string getRoleInfor() const;

    void _removeAllPet();

private:
	BSLib::Utility::CHashMap<PetID, CPetGM*> m_petHashMap;
	BSLib::Utility::CUniqueID<PetID> m_uniqueIDByPetID;

    SBattleAttribute m_totalBattleAttr;
    CHotSpring m_hotSpring;

    BSLib::Utility::TimerHandle m_timerHandleHotSpringTask;
    EHotSpringTimerStatus m_hotSpringTaskTimerStatues;
};

}//GM

}//PetSystem

}//GSLib

#endif//__GSLIB_PETSYSTEM_GM_PETMODULE_H__

