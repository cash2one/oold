#include <GSLib/skillSystem/DB/tableSkillDB.h>
#include <GSLib/tracer.h>

namespace GSLib
{

namespace SkillSystem
{

namespace DB
{

bool CRoleSkillData::_serializeTo(BSLib::Utility::CStream& stream) const 
{
	BSLib::uint32 buffSize = m_vecSkill.size() * sizeof(GM::CSkill);
	stream << buffSize; 
	for (BSLib::uint32 i=0; i<m_vecSkill.size(); ++i) {
		stream << m_vecSkill[i];
	}

	buffSize = m_vecSkillPos.size() * sizeof(SkillTPID);
	stream << buffSize;
	for (BSLib::uint32 i = 0; i < m_vecSkillPos.size(); ++i) {
		stream << m_vecSkillPos[i];
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

	BSLib::uint32 skillCount = buffSize / sizeof(GM::CSkill);
	for (BSLib::uint32 i=0; i<skillCount; ++i) {
		GM::CSkill skill = 0;
		stream >> skill;
		m_vecSkill.push_back(skill);
	}

	stream >> buffSize; 
	if (buffSize <= 0) {
		return false;
	}
	if (buffSize > stream.readSize()) {
		return false;
	}
	BSLib::uint32 size = buffSize / sizeof(SkillTPID);
	for (BSLib::uint32 i = 0; i < size; ++i) {
		SkillTPID skillID;
		stream >> skillID;
		m_vecSkillPos.push_back(skillID);
	}

	return true;
}

std::string CRoleSkillData::getDBKey() const
{
	std::string key;
	key.append((char*)&m_accountID, sizeof(m_accountID));
	key.append((char*)&m_zoneID, sizeof(m_zoneID));
	key.append((char*)&m_roleIndex, sizeof(m_roleIndex));
	return key;
}


}//DB

}//SkillSystem

}//GSLib
