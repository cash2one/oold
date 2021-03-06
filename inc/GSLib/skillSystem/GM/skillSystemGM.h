#ifndef __GSLIB_SKILLSYSTEM_GM_SKILLSYSTEMGM_H__
#define __GSLIB_SKILLSYSTEM_GM_SKILLSYSTEMGM_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace SkillSystem
{

namespace GM
{

class CSkillSystemGM : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CSkillSystemGM();
	virtual ~CSkillSystemGM();

	virtual BSLib::uint16 ICommonSystem_getFuncType() { return GSLib::EFUNCTYPE_SKILLPSYSTEM; }

	BSLIB_SINGLETON_DECLARE(CSkillSystemGM);

public:
	virtual bool _init();
	virtual void _final();
	virtual bool ICommonSystem_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _ICommonSystem_startSystem();
	virtual void ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);

};

}//GM

}//SkillSystem

}//GSLib

#endif//__GSLIB_SKILLSYSTEM_GM_SKILLSYSTEMGM_H__

