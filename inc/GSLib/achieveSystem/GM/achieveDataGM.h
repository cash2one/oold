#ifndef __GSLIB_ACHIEVESYSTEM_GM_ITEMDATAGM_H__
#define __GSLIB_ACHIEVESYSTEM_GM_ITEMDATAGM_H__

#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/achieveSystem/GM/achieveAttributeGM.h>
#include <BSLib/utility/table.h>

namespace GSLib
{

namespace AchieveSystem
{

namespace GM
{
struct SAchieveConfig{
    AchieveID m_achieveID;
    BSLib::uint32 m_typeID;
    BSLib::uint32 m_subTypeID;
    std::string m_prize;
    BSLib::uint32 param1;
    BSLib::uint32 param2;

    SAchieveConfig(){
        m_achieveID = 0;
        m_typeID = 0;
        m_subTypeID = 0;
        param1 = 0;
        param2 = 0;
        m_prize = "";
    };
    bool loadData(BSLib::Utility::CTableRow& a_tableRow){
        a_tableRow["f_id"] >> m_achieveID;
        a_tableRow["f_type"] >> m_typeID;
        a_tableRow["f_subtype"] >> m_subTypeID;
        a_tableRow["f_achieve_prize"] >> m_prize;
        a_tableRow["f_param1"] >> param1;
        a_tableRow["f_param2"] >> param2;

        return true;
    }

    AchieveID getUniqueID() const
    {
        return m_achieveID;
    }
};

class CAchieveConfigList{
public:
    CAchieveConfigList(EAchieveType a_achieveType,BSLib::uint32 a_subType)
    {
        m_achieveType = a_achieveType;
        m_subType = a_subType;
        clear();
    }
public:
    bool getAchieveData(SAchieveConfig& a_achieveData)
    {
        std::map<AchieveID, SAchieveConfig*>::iterator it = m_achieveConfigMap.begin();
        for(;it != m_achieveConfigMap.end();++it){
            SAchieveConfig* item = it->second;
            if(item == NULL){
                continue;
            }
            a_achieveData.m_achieveID = item->m_achieveID;
            a_achieveData.m_prize = item->m_prize;
            a_achieveData.m_subTypeID = item->m_subTypeID;
            a_achieveData.m_typeID = item->m_typeID;
            a_achieveData.param1 = item->param1;
            a_achieveData.param2 = item->param2;
        }
        return true;
    }

    bool getAchieveFinishList(BSLib::uint32 a_value,std::list<SAchieveConfig*>& a_achieveList)
    {
        std::map<AchieveID, SAchieveConfig*>::iterator it = m_achieveConfigMap.begin();
        for(;it != m_achieveConfigMap.end();++it){
            SAchieveConfig* item = it->second;
            if(item == NULL){
                continue;
            }
            if(item->param1 <= a_value){
                a_achieveList.push_back(item);
            }
        }
        return true;
    }

    bool getCurAchieve(BSLib::uint32 a_value,SAchieveConfig& a_achieve)
    {
        SAchieveConfig* desAchieve = NULL;
        std::map<AchieveID, SAchieveConfig*>::iterator it = m_achieveConfigMap.begin();
        for(;it != m_achieveConfigMap.end();++it){
            SAchieveConfig* item = it->second;
            if(item == NULL){
                continue;
            }

            if(item->param1 < a_value){
                continue; 
            }

            if(desAchieve == NULL){
               desAchieve = item; 
            }
            else{

                if(desAchieve->param1 > item->param1){
                    desAchieve = item; 
                }
            }
        }

        if(desAchieve!=NULL){
            a_achieve.m_achieveID = desAchieve->m_achieveID;
            a_achieve.m_subTypeID = desAchieve->m_subTypeID;
            a_achieve.m_typeID = desAchieve->m_typeID;
            a_achieve.m_prize = desAchieve->m_prize;
            a_achieve.param1 = desAchieve->param1;
            a_achieve.param2 = desAchieve->param2;
        }
        return true;
    }

    bool getAchieveByParam1(BSLib::uint32 a_param1,SAchieveConfig& a_achieve)
    {
        SAchieveConfig* desAchieve = NULL;
        std::map<AchieveID, SAchieveConfig*>::iterator it = m_achieveConfigMap.begin();
        for(;it != m_achieveConfigMap.end();++it){
            SAchieveConfig* item = it->second;
            if(item == NULL){
                continue;
            }
            if(a_param1 == item->param1){
                desAchieve = item;
                break;
            }
        }

        if(desAchieve!=NULL){
            a_achieve.m_achieveID = desAchieve->m_achieveID;
            a_achieve.m_subTypeID = desAchieve->m_subTypeID;
            a_achieve.m_typeID = desAchieve->m_typeID;
            a_achieve.m_prize = desAchieve->m_prize;
            a_achieve.param1 = desAchieve->param1;
            a_achieve.param2 = desAchieve->param2;
        }
        return true;
    }

    bool getCurAchieveList(std::list<SAchieveConfig*>& a_achieveList)
    {
        //SAchieveConfig* desAchieve = NULL;
        std::map<AchieveID, SAchieveConfig*>::iterator it = m_achieveConfigMap.begin();
        for(;it != m_achieveConfigMap.end();++it){
            SAchieveConfig* item = it->second;
            if(item == NULL){
                continue;
            }
            a_achieveList.push_back(item);
        }
        return true;
    }

    void clear()
    {
        std::map<AchieveID, SAchieveConfig*>::iterator it = m_achieveConfigMap.begin();
        for(;it != m_achieveConfigMap.end();++it){
            SAchieveConfig* item = it->second;
            if(item == NULL){
                continue;
            }
            BSLIB_SAFE_DELETE(item); 
        }
        m_achieveConfigMap.clear();
        return ;
    }

    bool addAchieveItem(SAchieveConfig* a_achieveItem)
    {
        m_achieveConfigMap.insert(std::pair<AchieveID, SAchieveConfig*>(a_achieveItem->m_achieveID,a_achieveItem));
        return true;
    }

    EAchieveType getAchieveType() const
    {
       return  m_achieveType;
    }

private:
    EAchieveType m_achieveType;
    BSLib::uint32 m_subType;
    std::map<AchieveID, SAchieveConfig*> m_achieveConfigMap;
};
}//GM

}//AchieveSystem

}//GSLib

#endif//__GSLIB_ACHIEVESYSTEM_GM_ACHIEVESYSTEMGM_H__

