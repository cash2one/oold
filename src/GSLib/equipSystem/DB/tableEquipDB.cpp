#include <GSLib/equipSystem/DB/tableEquipDB.h>
#include <GSLib/tracer.h>
#include <GSLib/equipSystem/baseDef.h>
namespace GSLib
{

namespace EquipSystem
{

namespace DB
{

bool CRoleEquipData::serializeTo(BSLib::Utility::CStream& stream) const 
{
    BSLib::uint32 buffSize = m_roleEquipList.size() * sizeof(SRoleEquipData);
    stream << buffSize; 
	for (BSLib::uint32 i=0; i<m_roleEquipList.size(); ++i) {
		m_roleEquipList[i].serializeTo(stream);
	}
	return true;
}

bool CRoleEquipData::serializeFrom(BSLib::Utility::CStream& stream)
{
    BSLib::uint32 buffSize = 0;
    stream >> buffSize;
    if (buffSize <= 0) {
        return true;
    }
    if (buffSize > stream.readSize()) {
        return false;
    }
    BSLib::uint32 count = buffSize / sizeof(SRoleEquipData);
   for (BSLib::uint32 i=0; i<count; ++i) {
	   SRoleEquipData roleEquipData;
	   roleEquipData.serializeFrom(stream);
       m_roleEquipList.push_back(roleEquipData);
   }

   return true;
}

}//DB

}//EquipSystem

}//GSLib
