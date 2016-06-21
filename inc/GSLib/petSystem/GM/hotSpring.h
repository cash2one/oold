#ifndef __GSLIB_PETSYSTEM_GM_HOTSPRING_H__
#define __GSLIB_PETSYSTEM_GM_HOTSPRING_H__

#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/petSystem/baseDef.h>
namespace GSLib
{

namespace PetSystem
{

namespace GM
{
class CHotSpring
{
public:
    CHotSpring();
    ~CHotSpring();

public:
    bool final();

public:
    BSLib::uint32 getLevel() const;
    BSLib::uint32 getMaxPetCount() const;
    BSLib::uint32 getInPoolPetCount() const;
	BSLib::uint32 getHelpPetCount() const;
    
    bool isPetSitDown(BSLib::uint32 a_petID) const;
    bool isPetInPool(BSLib::uint32 a_petID) const;
    bool isPoolFull() const;

    EPetStatus getPetStatus(BSLib::uint32 a_petID) const;

public:
	BSLib::uint32 getMaxSitDownPlace() const;

    void setLevel(BSLib::uint32 a_level);
    void setMaxPetCount(BSLib::uint32 a_maxPetCount);

    bool updatePetStatus(BSLib::uint32 a_petID,EPetStatus a_petStatus);
    //bool setPetStatus(BSLib::uint32 a_petID,EPetStatus a_oldStatus,EPetStatus a_petStatus);
    bool sitDown(BSLib::uint32 a_petID);
    void standUp(BSLib::uint32 a_petID);

    bool quitPool(BSLib::uint32 a_petID);
    bool enterPool(BSLib::uint32 a_petID);

    bool serializeTo(BSLib::Utility::CStream& stream) const;
    bool serializeFrom(BSLib::Utility::CStream& stream);

private:
    BSLib::uint32 m_level;
    BSLib::uint32 m_maxPetCount;
	std::vector<BSLib::uint32> m_helperList;
    BSLib::uint32 m_inPoolPetCount;
    std::vector<BSLib::uint32> m_inPoolPetIDArray;
};

}//GM

}//PetSystem

}//GSLib
#endif// __GSLIB_PETSYSTEM_GM_HOTSPRING_H__

