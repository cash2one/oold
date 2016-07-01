#ifndef __GSLIB_PLAYERSYSTEM_GT_PLAYERSYSTEMGT_H__
#define __GSLIB_PLAYERSYSTEM_GT_PLAYERSYSTEMGT_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace PlayerSystem
{

namespace GT
{

class CPlayerSystemGT : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CPlayerSystemGT();
	virtual ~CPlayerSystemGT();

	BSLIB_SINGLETON_DECLARE(CPlayerSystemGT);

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

}//GT

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_GT_PLAYERSYSTEMGT_H__

