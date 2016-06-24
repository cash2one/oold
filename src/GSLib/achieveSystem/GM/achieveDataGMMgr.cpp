
#include <GSLib/achieveSystem/msgAchieveSystemGC.h>
#include <GSLib/achieveSystem/msgAchieveSystem.h>
#include <GSLib/tracer.h>
#include <BSLib/utility/file/dirInfo.h>
#include <BSLib/utility/table.h>
#include <GSLib/achieveSystem/GM/achieveDataGMMgr.h>
namespace GSLib
{

namespace AchieveSystem
{	

namespace GM
{

BSLIB_SINGLETON_DEFINE(CAchieveConfigDataGMMgr);

CAchieveConfigDataGMMgr::CAchieveConfigDataGMMgr()
{

}

CAchieveConfigDataGMMgr::~CAchieveConfigDataGMMgr()
{
}

void CAchieveConfigDataGMMgr::init()
{
	;
}

void CAchieveConfigDataGMMgr::final()
{
}

bool CAchieveConfigDataGMMgr::loadGameConfig(const std::string& a_configPath)
{
    BSLib::Utility::CStringA configPath = a_configPath;
    configPath += "\\achieve\\";

    std::string fileName = configPath + "t_achieve_config.xml";
	BSLib::Utility::CDirInfo::standardization(fileName);
    BSLib::Utility::CStringA path(fileName);

    BSLib::Utility::CTableSheet tableSheet;
    if (!tableSheet.loadXmlFile(path)) {
        BSLIB_LOG_ERROR(ETT_GSLIB_ACHIEVESYSTEM, "[LOADCONFIG_ERROR]loadXmlFile[%s]", path.c_str());
        return false;
    }
    try {
        BSLIB_LOG_INFO(ETT_GSLIB_ACHIEVESYSTEM, "[LOADCONFIG][%s]", path.c_str());
        BSLib::Utility::CTable& table = tableSheet["item"];
        for (BSLib::uint32 i=0; i < table.getRowCount(); ++i) {
            if (!loadRow(table[i])){
                return false;
            }
        }
    } catch (...){
        BSLIB_LOG_ERROR(ETT_GSLIB_ACHIEVESYSTEM, "[LOADCONFIG_ERROR][Exception][%s]", path.c_str());
        return false;
    }
    return true;
}

bool CAchieveConfigDataGMMgr::loadRow(BSLib::Utility::CTableRow& a_tableRow)
{
    SAchieveConfig *item = new SAchieveConfig();
    if(item == NULL){
        BSLIB_LOG_ERROR(ETT_GSLIB_ACHIEVESYSTEM, "[LOADCONFIG_ERROR][item == NULL]");
        return false;
    }
    item->loadData(a_tableRow);
    m_achieveConfigDataHashMap.setValue(item->m_achieveID,item);
    CAchieveConfigList *list = getAchieveConfigList(item->m_subTypeID);
    if(list != NULL){
          return list->addAchieveItem(item);
    }

    list = new CAchieveConfigList((EAchieveType)item->m_typeID,item->m_subTypeID);
    if(list == NULL){
        BSLIB_SAFE_DELETE(item); 
    }
    m_achieveConfigHashMap.setValue(item->m_subTypeID,list);
    return list->addAchieveItem(item);
}

CAchieveConfigList* CAchieveConfigDataGMMgr::getAchieveConfigList(BSLib::uint32 a_achieveSubID)
{
    CAchieveConfigList *acheiveList = NULL;
    m_achieveConfigHashMap.getValue(a_achieveSubID,acheiveList);
    return acheiveList;
}

bool CAchieveConfigDataGMMgr::getAchieveFinishList(BSLib::uint32 a_achieveSubID,BSLib::uint32 a_value,std::list<SAchieveConfig*>& a_achieveList)
{
    CAchieveConfigList* list = getAchieveConfigList(a_achieveSubID);
    if (list == NULL){
        return false;
    }

    return list->getAchieveFinishList(a_value,a_achieveList);
}

bool CAchieveConfigDataGMMgr::getCurAchieveListByType(EAchieveType a_achieveType,std::list<SAchieveConfig*>& a_achieveList)
{
    BSLib::Utility::CHashMap<BSLib::uint32, CAchieveConfigList*>::iterator it = m_achieveConfigHashMap.begin();
    for(;it != m_achieveConfigHashMap.end();++it){
        CAchieveConfigList *achieveList = it->second;
        if(achieveList == NULL){
            continue;
        }
        if(achieveList->getAchieveType() == a_achieveType){
            achieveList->getCurAchieveList(a_achieveList);
        }
    }
    return true;
}

bool CAchieveConfigDataGMMgr::getCurAchieveListBySubID(BSLib::uint32 a_achieveSubID,std::list<SAchieveConfig*>& a_achieveList)
{
    CAchieveConfigList* list = getAchieveConfigList(a_achieveSubID);
    if (list == NULL){
        return false;
    }
    return list->getCurAchieveList(a_achieveList);
}

EAchieveType CAchieveConfigDataGMMgr::getCurAchieveTypeBySubID(BSLib::uint32 a_achieveSubID)
{
    CAchieveConfigList* list = getAchieveConfigList(a_achieveSubID);
    if (list == NULL){
        return ACHIEVE_INVALID;
    }
    return list->getAchieveType();
}

bool CAchieveConfigDataGMMgr::getCurAchieveSubIDByParam1(EAchieveType a_achieveType,BSLib::uint32 a_param1,BSLib::uint32& a_achieveSubType)
{
    std::list<SAchieveConfig*> achieveList;
    if(!getCurAchieveListByType(a_achieveType,achieveList)){
        return false;
    }

    std::list<SAchieveConfig*>::iterator it = achieveList.begin();
    for(;it != achieveList.end();++it){
        SAchieveConfig *achieveConfig = *it;
        if(achieveConfig == NULL){
            continue;
        }
        if( achieveConfig->param1 == a_param1){
            a_achieveSubType = achieveConfig->m_subTypeID;
            return true;
        } 
    }
    return false;
}

bool CAchieveConfigDataGMMgr::getCurAchieve(BSLib::uint32 a_achieveSubID,BSLib::uint32 a_value,SAchieveConfig& a_achieveList)
{
    CAchieveConfigList* list = getAchieveConfigList(a_achieveSubID);
    if (list == NULL){
        return false;
    }

    return list->getCurAchieve(a_value,a_achieveList);
}

EAchieveType CAchieveConfigDataGMMgr::getAchieveTypeID(BSLib::uint32 a_achieveSubID)
{
    CAchieveConfigList *achieveList = getAchieveConfigList(a_achieveSubID);
    if(achieveList == NULL){
        return ACHIEVE_INVALID;
    }
    
    return achieveList->getAchieveType();
}

SAchieveConfig* CAchieveConfigDataGMMgr::getAchieveByAchieveID(AchieveID a_achieveID)
{
   SAchieveConfig* achieve = NULL;
   m_achieveConfigDataHashMap.getValue(a_achieveID,achieve);
   return achieve;
}
}//GM

}//AchieveSystem

}//GSLib

