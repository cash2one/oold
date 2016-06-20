//////////////////////////////////////////////////////////////////////
//	created:	2014/07/25
//	filename: 	GSLib\playerSystem\LG\playerSystemLG.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PLAYERSYSTEM_LG_PLAYERSYSTEMLG_H__
#define __GSLIB_PLAYERSYSTEM_LG_PLAYERSYSTEMLG_H__

#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonSystem.h>

namespace GSLib
{

namespace PlayerSystem
{

namespace LG
{

class CPlayerSystemLG : public GFLib::CommonServer::CCommonSystem
{
public:
	CPlayerSystemLG();
	virtual ~CPlayerSystemLG();

	BSLIB_SINGLETON_DECLARE(CPlayerSystemLG);

public:
	virtual bool _init();
	virtual void _final();
	virtual bool _loadGameConfig(const std::string& a_configPath);
	virtual bool _initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void _cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void _cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);
};

}//LG

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_LG_PLAYERSYSTEMLG_H__
