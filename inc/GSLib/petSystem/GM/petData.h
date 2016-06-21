#ifndef __GSLIB_PETSYSTEM_GM_PETDATA_H__
#define __GSLIB_PETSYSTEM_GM_PETDATA_H__


#include <GSLib/petSystem/DB/tablePetDB.h>

namespace GSLib
{

namespace PetSystem
{

namespace GM
{
struct SPetSkillItem{
	BSLib::uint32 m_skillID;
	BSLib::uint32 m_skillLevel;
};

class CPetData{
public:
    CPetData();
    ~CPetData();
public:
	bool serializeTo(BSLib::Utility::CStream& stream) const;
public:
    DB::CPetDBData m_petData;
    std::list<SPetSkillItem*> m_skillList;

};
}//GM

}//PetSystem

}//GSLib

#endif//__GSLIB_PETSYSTEM_GM_PETDATA_H__

