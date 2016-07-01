#ifndef __GSLIB_ITEMSYSTEM_GM_ITEMSYSTEMGM_H__
#define __GSLIB_ITEMSYSTEM_GM_ITEMSYSTEMGM_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace ItemSystem
{

namespace GM
{

class CItemSystemGM : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CItemSystemGM();
	virtual ~CItemSystemGM();

	BSLIB_SINGLETON_DECLARE(CItemSystemGM);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_ITEMSYSTEM; }

public:
	virtual bool _init();
	virtual void _final();

	virtual bool ICommonServer_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();

	virtual void ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);

};

}//GM

}//ItemSystem

}//GSLib

#endif//__GSLIB_ITEMSYSTEM_GM_ITEMSYSTEMGM_H__

