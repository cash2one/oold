#ifndef __GSLIB_PLAYERSYSTEM_LG_PLAYERSYSTEMLG_H__
#define __GSLIB_PLAYERSYSTEM_LG_PLAYERSYSTEMLG_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace PlayerSystem
{

namespace LG
{

class CPlayerSystemLG : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CPlayerSystemLG();
	virtual ~CPlayerSystemLG();

	BSLIB_SINGLETON_DECLARE(CPlayerSystemLG);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_PLAYERSYSTEM; }

public:
	virtual bool _init();
	virtual void _final();
	virtual bool ICommonServer_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);
};

}//LG

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_LG_PLAYERSYSTEMLG_H__

