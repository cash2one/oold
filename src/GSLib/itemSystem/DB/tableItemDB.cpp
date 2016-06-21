/*#include <GSLib/skillSystem/DB/tableSkillDB.h>
#include <GSLib/tracer.h>

namespace GSLib
{

namespace SkillSystem
{

namespace DB
{

bool CRoleSkillData::_serializeTo(BSLib::Utility::CStream& stream) const 
{
	BSLib::uint32 buffSize = m_skillList.size() * sizeof(SkillID);
	stream << buffSize; 
	for (BSLib::uint32 i=0; i<m_skillList.size(); ++i) {
		stream << m_skillList[i];
	}
	return true;
}

bool CRoleSkillData::_serializeFrom(BSLib::Utility::CStream& stream)
{
	BSLib::uint32 buffSize = 0;
	stream >> buffSize;
	if (buffSize <= 0) {
		return true;
	}
	if (buffSize > stream.readSize()) {
		return false;
	}
	SkillID skillID = 0;
	BSLib::uint32 skillCount = buffSize / sizeof(SkillID);
	for (BSLib::uint32 i=0; i<skillCount; ++i) {
		stream >> skillID;
		m_skillList.push_back(skillID);
	}
	return true;
}

}//DB

}//SkillSystem

}//GSLib*/
