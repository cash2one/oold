//////////////////////////////////////////////////////////////////////
//	created:	2014/07/25
//	filename: 	GSLib\playerSystem\CN\playerSystemCN.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PLAYERSYSTEM_CN_PLAYERSYSTEMCN_H__
#define __GSLIB_PLAYERSYSTEM_CN_PLAYERSYSTEMCN_H__

#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonSystem.h>

namespace GSLib
{

namespace PlayerSystem
{
namespace CN
{

class CPlayerSystemCN : public GFLib::CommonServer::CCommonSystem
{
public:
	CPlayerSystemCN();
	virtual ~CPlayerSystemCN();

	BSLIB_SINGLETON_DECLARE(CPlayerSystemCN);

protected:
	virtual bool _init();
	virtual void _final();
	virtual bool _loadGameConfig(const std::string& a_configPath);
	virtual bool _initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void _cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void _cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);
};

}//CN

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_CN_PLAYERSYSTEMCN_H__
