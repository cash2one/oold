//////////////////////////////////////////////////////////////////////
//	created:	2014/09/09
//	filename: 	GSLib\ACHIEVESYSTEM\GM\ACHIEVESYSTEMGM.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_ACHIEVESYSTEM_GM_ACHIEVESYSTEMGM_H__
#define __GSLIB_ACHIEVESYSTEM_GM_ACHIEVESYSTEMGM_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace AchieveSystem
{

namespace GM
{

class CAchieveSystemGM : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CAchieveSystemGM();
	virtual ~CAchieveSystemGM();

	BSLIB_SINGLETON_DECLARE(CAchieveSystemGM);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_ACHIEVESYSTEM; }

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

}//AchieveSystem

}//GSLib

#endif//__GSLIB_ACHIEVESYSTEM_GM_ACHIEVESYSTEMGM_H__
