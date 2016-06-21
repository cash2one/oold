#ifndef __GSLIB_PETSYSTEM_GM_PETTPIDLEVELTASKDATA_H__
#define __GSLIB_PETSYSTEM_GM_PETTPIDLEVELTASKDATA_H__

#include <GFLib/commonServer/commonSystem.h>
#include "GSLib//petSystem/baseDef.h"
#include <BSLib/utility/table.h>
#include <BSLib/utility/random.h>
#include <GSLib/petSystem/GM/hotSpringTask.h>
namespace GSLib
{

namespace PetSystem
{

namespace GM
{
class CPetTPIDTask
{
public: 
    CPetTPIDTask();
    ~CPetTPIDTask();
    bool addTask(BSLib::uint32 a_TaskID);
public:
     std::vector<BSLib::uint32> m_taskIDArray; 
};

}//GM

}//PetSystem

}//GSLib
#endif// __GSLIB_PETSYSTEM_GM_PETTPIDLEVELTASKDATA_H__

