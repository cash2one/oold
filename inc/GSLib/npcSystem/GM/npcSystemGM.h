#ifndef __GSLIB_NPCSYSTEM_GM_SKILLSYSTEMGM_H__
#define __GSLIB_NPCSYSTEM_GM_SKILLSYSTEMGM_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace NPCSystem
{

namespace GM
{

class CNPCSystemGM : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CNPCSystemGM();
	virtual ~CNPCSystemGM();

	BSLIB_SINGLETON_DECLARE(CNPCSystemGM);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_NPCSYSTEM; }

	void update(BSLib::uint64 a_delayMilliseconds);

public:
	virtual bool _init();
	virtual void _final();
	virtual bool _loadGameConfig(const std::string& a_configPath);
	virtual bool _initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void _cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void _cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);

};

}//GM

}//NPCSystem

}//GSLib

#endif//__GSLIB_NPCSYSTEM_GM_SKILLSYSTEMGM_H__

