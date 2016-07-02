#ifndef __GSLIB_PETSYSTEM_GM_PETSYSTEMGM_H__
#define __GSLIB_PETSYSTEM_GM_PETSYSTEMGM_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace PetSystem
{

namespace GM
{

class CPetSystemGM : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CPetSystemGM();
	virtual ~CPetSystemGM();

	BSLIB_SINGLETON_DECLARE(CPetSystemGM);

	virtual BSLib::uint16 ICommonSystem_getFuncType() { return GSLib::EFUNCTYPE_PETSYSTEM; }

	void update(BSLib::uint64 a_delayMilliseconds);

public:
	virtual bool _init();
	virtual void _final();
	virtual bool ICommonSystem_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _ICommonSystem_startSystem();
	virtual void ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);

    BSLib::Utility::CTimerServer* getTimerServer();

};

}//GM

}//PetSystem

}//GSLib

#endif//__GSLIB_PETSYSTEM_GM_PETSYSTEMGM_H__

