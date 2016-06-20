//////////////////////////////////////////////////////////////////////
//	created:	2014/07/25
//	filename: 	GSLib\achieveSystem\GM\CRoleEquipModule.h
//	author:	     zhangping	
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_ACHIEVESYSTEM_GM_ROLEEQUIPMODULE_H__
#define __GSLIB_ACHIEVESYSTEM_GM_ROLEEQUIPMODULE_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/uniqueID.h>
#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/achieveSystem/baseDef.h>
#include <GSLib/playerSystem/GM/roleModuleGM.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/achieveSystem/msgAchieveSystem.h>
#include <GSLib/achieveSystem/GM/achieveAttributeGM.h>
#include <GSLib/achieveSystem/DB/tableAchieveDB.h>


#ifdef __GNUC__

namespace __gnu_cxx
{
	template< > struct hash< EAchieveType >
	{
		size_t operator()(const EAchieveType& x) const
		{
			return size_t(x);
		}
	};
}

#endif

namespace GSLib
{

namespace AchieveSystem
{

namespace GM
{
//class GSLib::PlayerSystem::GM::CRoleGM;

class CAchieveList{
public:
    CAchieveList(EAchieveType a_achieveType)
    {
        m_achieveType = a_achieveType;
        clear();
    }
public:
    bool getAchieveData(DB::CAchieveData& a_achieveData)
    {
        BSLib::Utility::CHashMap<AchieveID, DB::SAchieveItem*>::iterator it = m_achieveHashMap.begin();
        for(;it != m_achieveHashMap.end();++it){
            DB::SAchieveItem* item = it->second;
            if(item == NULL){
                BSLIB_LOG_ERROR(ETT_GSLIB_ACHIEVESYSTEM, "[GETEQUIP_ERROR]updateDataToDB[m_achieveHashMap.size=%d][achieve == NULL]",m_achieveHashMap.size());
                continue;
            }
            a_achieveData.m_achieveList.push_back(*item);
        }
        return true;
    }

    void clear()
    {
        BSLib::Utility::CHashMap<AchieveID, DB::SAchieveItem*>::iterator it = m_achieveHashMap.begin();
        for(;it != m_achieveHashMap.end();++it){
            DB::SAchieveItem* item = it->second;
            if(item == NULL){
                BSLIB_LOG_ERROR(ETT_GSLIB_ACHIEVESYSTEM, "[GETEQUIP_ERROR]updateDataToDB[m_achieveHashMap.size=%d][achieve == NULL]",m_achieveHashMap.size());
                continue;
            }
            BSLIB_SAFE_DELETE(item); 
        }
        m_achieveHashMap.clear();
        return ;
    }

    bool addAchieveItem(DB::SAchieveItem* a_achieveItem)
    {
        m_achieveHashMap.setValue(a_achieveItem->m_achieveID,a_achieveItem);
        return true;
    }

    DB::SAchieveItem* getAchieveItem(AchieveID a_achieveID)
    {
        DB::SAchieveItem* achieve = NULL;
        m_achieveHashMap.getValue(a_achieveID,achieve);
        return achieve;
    }

    bool getAchieveItemProgress(BSLib::uint32 a_subTypeID,BSLib::uint32& a_achieveProgress)
    {
        DB::SAchieveItem* achieve = NULL;
        BSLib::Utility::CHashMap<AchieveID, DB::SAchieveItem*>::iterator it = m_achieveHashMap.begin();
        for(;it != m_achieveHashMap.end();++it){
            achieve = it->second;
            if(achieve == NULL){
                BSLIB_LOG_ERROR(ETT_GSLIB_ACHIEVESYSTEM, "[GETACHIEVE_ERROR]serializeTo[m_achieveHashMap.size=%d][item == NULL]",m_achieveHashMap.size());
                return false;
            }
            if(achieve->m_achieveSubType == a_subTypeID){
                a_achieveProgress = achieve->m_achieveProgress;
                return true;
            }
        }
        return false;
    }

    bool serializeTo(BSLib::Utility::CStream& stream)
    {
        BSLib::Utility::CHashMap<AchieveID, DB::SAchieveItem*>::iterator it = m_achieveHashMap.begin();
        for(;it != m_achieveHashMap.end();++it){
            DB::SAchieveItem* item = it->second;
            if(item == NULL){
                BSLIB_LOG_ERROR(ETT_GSLIB_ACHIEVESYSTEM, "[GETACHIEVE_ERROR]serializeTo[m_achieveHashMap.size=%d][item == NULL]",m_achieveHashMap.size());
                return false;
            }
            stream << item->m_achieveID;
            stream << item->m_achieveSubType;
            stream << item->m_achieveProgress;
            stream << item->m_achieveStatus;
        }
        return true;
    }

    bool serializeFrom(BSLib::Utility::CStream& stream)
    {
        return true;
    }

    EAchieveType getAchieveType(){
        return m_achieveType;
    }

    BSLib::uint32 getAchieveCount(){
        return m_achieveHashMap.size();
    }


private:
    EAchieveType m_achieveType;
    BSLib::Utility::CHashMap<AchieveID, DB::SAchieveItem*> m_achieveHashMap;
};

class CAchieveModule : public GSLib::PlayerSystem::GM::CRoleModuleGM
{
public:
	CAchieveModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType);
	virtual ~CAchieveModule();

public:
	virtual void preInit(bool isFirst);
	virtual void postInit(bool isFirst);
	virtual void initToClient();
	virtual void final();

	virtual void initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual void freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	virtual void updateDataToDB();

	virtual bool cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
	virtual bool cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
	virtual void cbSelectTableData(BSLib::uint32 a_sessionID, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream);
    virtual void onRoleDelete();

    bool updateTableData(const std::string& a_tableIndex, const std::string& a_name, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, bool a_needSave = false);
	bool updateTableData(EDBTableID a_tableID, void* a_data, BSLib::uint32 a_dataSize,  bool a_needSave = false);
    
    void onEventAchieveUpdate(BSLib::Utility::EventID& a_eventID, BSLib::Utility::CStream& a_stream);
private:
    BSLib::uint32 _getLevelSkillCount(BSLib::uint32 a_skillLevel,const std::list<BSLib::uint32>& a_skillLevelList);
    BSLib::uint32 _getAchieveDataValue(BSLib::uint32 a_achieveSubID);

    bool _updateRoleSkillLevelAchieveData(BSLib::uint32 a_achieveSubID,const std::list<BSLib::uint32>& a_skillLevelList);
    bool _updateAchieveData(BSLib::uint32 a_achieveSubID,BSLib::uint32 a_achieveData);
    void _getAchieveDataDB(DB::CAchieveData& a_achieveData);
	void _updateAchieveDataToClient(AchieveID a_achieveID);

private:
    void _onMsgAchieveSystemGC2GMReqGetAchieveList(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgAchieveSystemGC2GMReqGetAchievePrize(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgAchieveSystemGC2GMReqSaveAchieveData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

public:
	bool loadGameConfig(const std::string& a_configPath);

private:
    bool _receiveAchievePrize(AchieveID a_achieveID);
    bool _saveAchieveData(BSLib::uint32 a_achieveSubID,BSLib::uint32 a_achieveData);

    void _initAchieveData(DB::CAchieveData& a_chieveData);
    bool _addAchieve(const DB::SAchieveItem& a_chieveItem);
    CAchieveList* _getAchieve(EAchieveType a_achieveType);
    DB::SAchieveItem* _getAchieveByAchieveID(AchieveID a_achieveID) const;

private:
    BSLib::Utility::CHashMap<EAchieveType, CAchieveList*> m_achieveHashMap;
};

}//GM

}//AchieveSystem

}//GSLib

#endif//__GSLIB_ACHIEVESYSTEM_GM_ROLEEQUIPMODULE_H__
