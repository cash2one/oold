
#ifndef __GSLIB_ACHIEVESYSTEM_GM_ITEMGMMGR_H__
#define __GSLIB_ACHIEVESYSTEM_GM_ITEMGMMGR_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/memory/objectMgr.h>
#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/achieveSystem/GM/achieveDataGM.h>
#include <GSLib/achieveSystem/GM/achieveDataGMMgr.h>
namespace GSLib
{

namespace AchieveSystem
{

namespace GM
{


class CAchieveConfigDataGMMgr
{
public:
	CAchieveConfigDataGMMgr();
	virtual ~CAchieveConfigDataGMMgr();

    BSLIB_SINGLETON_DECLARE(CAchieveConfigDataGMMgr);
	void init();
	void final();

	bool loadGameConfig(const std::string& a_configPath);
    bool loadRow(BSLib::Utility::CTableRow& a_tableRow);

    bool getAchieveFinishList(BSLib::uint32 a_achieveSubID,BSLib::uint32 a_value,std::list<SAchieveConfig*>& a_achieveList);
    bool getCurAchieveSubIDByParam1(EAchieveType a_achieveType,BSLib::uint32 a_param1,BSLib::uint32& a_achieveSubType);
    bool getCurAchieve(BSLib::uint32 a_achieveSubID,BSLib::uint32 a_value,SAchieveConfig& a_achieveList);
    bool getCurAchieveListByType(EAchieveType a_achieveType,std::list<SAchieveConfig*>& a_achieveList);
    bool getCurAchieveListBySubID(BSLib::uint32 a_achieveSubID,std::list<SAchieveConfig*>& a_achieveList);

    EAchieveType getCurAchieveTypeBySubID(BSLib::uint32 a_achieveSubID);
    CAchieveConfigList* getAchieveConfigList(BSLib::uint32 a_achieveSubID);

    SAchieveConfig* getAchieveByAchieveID(AchieveID a_achieveID);
    EAchieveType getAchieveTypeID(BSLib::uint32 a_achieveSubID);

private:
    BSLib::Utility::CHashMap<BSLib::uint32, CAchieveConfigList*> m_achieveConfigHashMap;
    BSLib::Utility::CHashMap<AchieveID, SAchieveConfig*> m_achieveConfigDataHashMap;
};

}//GM

}//AchieveSystem

}//GSLib

#endif//__GSLIB_ACHIEVESYSTEM_GM_ITEMGMMGR_H__

