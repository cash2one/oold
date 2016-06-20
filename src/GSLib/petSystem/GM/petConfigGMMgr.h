//////////////////////////////////////////////////////////////////////
//	created:	2014/08/03
//	filename:	GSLib\petSystem\GM\playerGMMgr.h
//	author:	    zhangping	
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////

#ifndef __GSLIB_PETSYSTEM_GM_PETGMMGR_H__
#define __GSLIB_PETSYSTEM_GM_PETGMMGR_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/table.h>
#include <BSLib/utility/memory/objectMgr.h>
#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/petSystem/GM/petGM.h>
#include <GSLib/petSystem/GM/petUnlockItem.h>
#include "petTPIDTask.h"

namespace GSLib
{

namespace PetSystem
{

namespace GM
{

struct SPetInitConfig
{
    BSLib::uint32 m_petTPID;
    BSLib::uint32 m_petLevel;
    SPetInitConfig()
    {
        m_petTPID = 0;
        m_petLevel = 0;
    };

    void loadData(BSLib::Utility::CTableRow& a_tableRow)
    {
        a_tableRow["f_id"] >> m_petTPID;
        a_tableRow["f_level"] >> m_petLevel;
    }
};

class CPetConfigGMMgr
{
public:
	CPetConfigGMMgr();
	virtual ~CPetConfigGMMgr();

    BSLIB_SINGLETON_DECLARE(CPetConfigGMMgr);
	void init();
	void final();
	bool loadGameConfig(const std::string& a_configPath);

    // 伙伴属性
public:
    BSLib::uint32 getPetMaxLevel(ItemTPID a_tpid) const;
    BSLib::uint32 getUpgradeNeedFriendlyValue(ItemTPID a_tpid,BSLib::uint32 a_level) const;
    // 获取伙伴属性
    bool getPetAttr(ItemTPID a_tpid,BSLib::uint32 a_level,SBattleAttribute& a_battleAttr) const;
    bool getUpgradeAttr(ItemTPID a_tpid,SBattleAttribute& a_upgradeAttrs) const;
    BSLib::uint32 getPetLevel(ItemTPID a_tpid,BSLib::uint32 a_level,BSLib::uint32 a_addFriendlyValue,BSLib::uint32& a_leftFriendlyValue) const;

public:
    BSLib::uint32 getFastFinishNeedDiamond(EHotSpringType a_hotSpringType) const;
    BSLib::uint32 getAddFriendlyValueByHotSpringType(EHotSpringType a_hotSpringType) const;
    BSLib::uint32 getHotSpringMaxLevel() const;

    BSLib::uint32 getHotSpringSize(BSLib::uint32 a_level) const;
    BSLib::uint32 getHotSpringMaxSize() const;
    BSLib::uint32 getExpandHotSpringNeedDiamond(BSLib::uint32 a_level) const;

    BSLib::uint32 randomHotSpringTaskTime() const;

    CHotSpringTask* getHotSpringTask(BSLib::uint32 a_taskID) const;
    CHotSpringTask* randomDailyPetTask(PetTPID a_petTPID,BSLib::uint32 a_fLevel,BSLib::uint32 a_friendly,EHotSpringTaskType a_taskType) const;
    CHotSpringTask* randomPetTask(PetTPID a_petTPID,BSLib::uint32 a_fLevel,BSLib::uint32 a_friendly) const;
    CHotSpringTask* getMainPetTask(PetTPID a_petTPID,BSLib::uint32 a_fLevel,BSLib::uint32 a_friendlyValue,BSLib::uint32 a_lastTaskID) const;

private:
    CHotSpringTask* _getRandomPetTask(std::vector<CHotSpringTask*>& a_tasks) const;
    CHotSpringTask* _getNextMainTask(std::map<BSLib::uint32,CHotSpringTask*>& a_tasks,BSLib::uint32 a_lastTaskID) const;

	BSLib::uint64 _makeUInt64Key(BSLib::uint32 a_left,BSLib::uint32 a_right) const;
    bool _addHotSpringTask(CHotSpringTask* a_task);

    CPetTPIDTask* _getDialyHotSpringTask(PetTPID a_petTPID) const;
    CPetTPIDTask* _getMainHotSpringTask(PetTPID a_petTPID) const;
    CPetTPIDTask* _getRandomHotSpringTask(PetTPID a_petTPID) const;

	void _removeHotSpringTaskConfig();
    bool _loadHotSpringTaskConfig(const std::string& a_configPath);

private:
	BSLib::Utility::CUniqueID<BSLib::uint32> m_uniqueIDByPetIndex;

    BSLib::Utility::CHashMap<PetTPID, CPetTPIDTask*> m_petDailyTaskHashMap;               // 日常任务
    BSLib::Utility::CHashMap<PetTPID, CPetTPIDTask*> m_petMainTaskHashMap;                // 主线任务
    BSLib::Utility::CHashMap<PetTPID, CPetTPIDTask*> m_petRandomTaskHashMap;              // 随机任务
    BSLib::Utility::CHashMap<BSLib::uint32, CHotSpringTask*> m_hotSpringTaskHashMap;      // 任务总表
};

}//GM

}//PetSystem

}//GSLib

#endif//__GSLIB_PETSYSTEM_GM_PETGMMGR_H__
