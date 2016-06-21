#ifndef __GSLIB_PLAYERSYSTEM_GT_PLAYERSYSTEMGT_H__
#define __GSLIB_PLAYERSYSTEM_GT_PLAYERSYSTEMGT_H__

#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonSystem.h>

namespace GSLib
{

namespace PlayerSystem
{

namespace GT
{

class CPlayerSystemGT : public GFLib::CommonServer::CCommonSystem
{
public:
	CPlayerSystemGT();
	virtual ~CPlayerSystemGT();

	BSLIB_SINGLETON_DECLARE(CPlayerSystemGT);

public:
	virtual bool _init();
	virtual void _final();
	virtual bool _loadGameConfig(const std::string& a_configPath);
	virtual bool _initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void _cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void _cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);
};

}//GT

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_GT_PLAYERSYSTEMGT_H__

