//////////////////////////////////////////////////////////////////////
//	created:	2014/09/12
//	filename: 	GSLib\skillSystem\GM\skillAttrMgr.cpp
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/skillSystem/GM/skillAttrMgr.h>
#include <GSLib/skillSystem/GM/skillAttr.h>
#include <BSLib/utility/file/dirInfo.h>
#include <BSLib/utility/table.h>
#include <GSLib/tracer.h>
#include <GSLib/skillSystem/GM/skillLevel.h>
#include <BSLib/utility/string.h>
#include <GSLib/playerSystem/GM/roleBagModuleGM.h>
#include <BSLib/utility/convert.h>

namespace GSLib
{

namespace SkillSystem
{

namespace GM
{

CSkillDataMgr::CSkillDataMgr()
{
}

CSkillDataMgr::~CSkillDataMgr()
{
}

BSLIB_SINGLETON_DEFINE(CSkillDataMgr)

bool CSkillDataMgr::init()
{
	return true;
}

void CSkillDataMgr::final()
{
	for (BSLib::Utility::CHashMap<GSLib::SkillTPID, CSkillAttr*> ::iterator itr = m_mapSkillAttrs.begin(); itr != m_mapSkillAttrs.end(); ++itr) {
		if (itr->second != NULL) {
			delete itr->second, itr->second = NULL;
		}
	}

	m_mapSkillAttrs.clear();
}

void CSkillDataMgr::add(CSkillAttr *skillAttr)
{
	if (skillAttr != NULL) {
		if (skillAttr->getTPID() != 0) {
			if (m_mapSkillAttrs.find(skillAttr->getTPID()) == m_mapSkillAttrs.end()) {
				m_mapSkillAttrs.setValue(skillAttr->getTPID(), skillAttr);
		    }
		}
	}
}

bool CSkillDataMgr::loadGameConfig(const std::string& a_configPath)
{
	BSLib::Utility::CStringA configPath = a_configPath;
	configPath += "\\skill";
	BSLib::Utility::CDirInfo::standardization(configPath);

	if (!_loadSkillAttrs(configPath)) {
		return false;
	}

	return true;
}

const CSkillAttr* CSkillDataMgr::getSkillAttr(GSLib::SkillTPID a_TPID) const
{
	BSLib::Utility::CHashMap<GSLib::SkillTPID, CSkillAttr*> ::const_iterator itr = m_mapSkillAttrs.find(a_TPID);
	if (itr != m_mapSkillAttrs.end()) {
		return itr->second;
	}

	return NULL;
}

bool CSkillDataMgr::_loadSkillAttrs(const std::string &a_configPath)
{
	std::string skillAttrPath = a_configPath + "\\t_skill_config.xml";
	BSLib::Utility::CDirInfo::standardization(skillAttrPath);

	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(skillAttrPath)) {
		BSLIB_LOG_INFOR(ETT_GSLIB_SCENESYSTEM, "加载技能配置失败[%s]", skillAttrPath.c_str());
		return false;
	}
	try {
		BSLib::Utility::CTable& table = tableSheet["item"];
		for (BSLib::uint32 i = 0; i < table.getRowCount(); ++i) {
			BSLib::int32 roleTPID = 0;
			table[i]["f_profession"] >> roleTPID;
			if (roleTPID > 0) {
				CSkillAttr *skillAttr = new CSkillAttr;
				skillAttr->m_roleTPID = roleTPID;
				table[i]["f_id"] >> skillAttr->m_skillID;
				table[i]["f_max_level"] >> skillAttr->m_maxSkillLevel;
				table[i]["f_require_level"] >> skillAttr->m_skillLearnRequiredLevel;

				CSkillDataMgr::singleton().add(skillAttr);
			}
		}
	} catch (...){
		BSLIB_LOG_INFOR(ETT_GSLIB_SCENESYSTEM, "加载技能配置文件失败[%s]", skillAttrPath.c_str());
		return false;
	}

	return true;
}

}//GM

}//SKillSystem

}//GSLib








