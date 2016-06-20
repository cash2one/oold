//////////////////////////////////////////////////////////////////////
//	created:	2014/09/12
//	filename: 	GSLib\skillSystem\GM\skillDataMgr.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////

#ifndef		__GSLIB_SKILLSYSTEM_GM_SKILLATTRMGR_H__
#define		__GSLIB_SKILLSYSTEM_GM_SKILLATTRMGR_H__

#include <string>
#include <BSLib/utility/hashMap.h>
#include <GSLib/baseDef.h>
#include <BSLib/utility/singleton.h>

namespace GSLib
{

namespace SkillSystem
{

namespace GM
{

class CSkillAttr;

class CSkillDataMgr
{
public:
	CSkillDataMgr();
	~CSkillDataMgr();
public:
	BSLIB_SINGLETON_DECLARE(CSkillDataMgr);
public:
	bool init();
	void final();
	void add(CSkillAttr *skillAttr);
	bool loadGameConfig(const std::string& a_configPath);
	const CSkillAttr* getSkillAttr(GSLib::SkillTPID a_TPID) const;
private:
	bool _loadSkillAttrs(const std::string &a_configPath);
private:
	BSLib::Utility::CHashMap<GSLib::SkillTPID, CSkillAttr*> m_mapSkillAttrs;
};
}//GM

}//SKillSystem

}//GSLib

#endif
