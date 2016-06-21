#ifndef __GSLIB_ACHIEVESYSTEM_GM_ITEMATTRIBUTEGM_H__
#define __GSLIB_ACHIEVESYSTEM_GM_ITEMATTRIBUTEGM_H__

#include <GFLib/commonServer/commonSystem.h>
#include "GSLib//achieveSystem/baseDef.h"
namespace GSLib
{

namespace AchieveSystem
{

namespace GM
{       
class CAchieveItem
{
public:
	CAchieveItem(AchieveID a_achieveID, EAchieveType a_type, EAchieveStatus a_status, BSLib::uint32 a_count);
	~CAchieveItem();
public:
	void serializeTo(BSLib::Utility::CStream& stream) const;
public:
	AchieveID m_achieveID;
	EAchieveType m_achieveType;
    EAchieveStatus m_achieveStatus;
    BSLib::uint32 m_achieveProgress;
};

}//GM

}//AchieveSystem

}//GSLib
#endif// __GSLIB_ACHIEVESYSTEM_GM_ITEMATTRIBUTEGM_H__

