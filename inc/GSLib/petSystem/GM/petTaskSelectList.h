//////////////////////////////////////////////////////////////////////
//	created:	2015/03/05
//	filename: 	GSLib\petSystem\GM\petTaskSelectList.h
//	author:		zhangping
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PETSYSTEM_GM_HOTSPRINGTASK_SELECTLIST_H__
#define __GSLIB_PETSYSTEM_GM_HOTSPRINGTASK_SELECTLIST_H__

#include <GFLib/commonServer/commonSystem.h>
#include "GSLib//petSystem/baseDef.h"
namespace GSLib
{

namespace PetSystem
{

namespace GM
{
class CPetTaskSelectList
{
public:
    CPetTaskSelectList();
    ~CPetTaskSelectList();

    void setTaskList(std::vector<EHotSpringTaskType>& a_taskTypeArray);
    void setPetID(BSLib::uint32 a_petID);
    void setSelectCount(BSLib::uint32 a_selectCount){m_selectCount = a_selectCount;}
    
    bool SerializeFrom(BSLib::Utility::CStream& stream);
    bool SerializeTo(BSLib::Utility::CStream& stream) const;

    PetID getPetID() const;
    BSLib::uint32 getSelectCount() const;

private:
    BSLib::uint32 m_petID;
    BSLib::uint32 m_selectCount;
    std::vector<EHotSpringTaskType> m_taskTypeArray;
};
}//GM

}//PetSystem

}//GSLib
#endif// __GSLIB_PETSYSTEM_GM_HOTSPRINGTASK_SELECTLIST_H__
