//////////////////////////////////////////////////////////////////////
//	created:	2014/09/10
//	filename: 	GSLib\prizeSystem\GM\prizeSystemGM.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PRIZESYSTEM_GM_PRIZESYSTEMGM_H__
#define __GSLIB_PRIZESYSTEM_GM_PRIZESYSTEMGM_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>
#include <GSLib/prizeSystem/GM/dateTimer.h>

namespace GSLib
{

namespace PrizeSystem
{

namespace GM
{

class CPrizeSystemGM : public GSLib::DBSystem::CDBCommonSystem
	,CDateTimerCallback
{
public:
	CPrizeSystemGM();
	virtual ~CPrizeSystemGM();

	BSLIB_SINGLETON_DECLARE(CPrizeSystemGM);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_PRIZESYSTEM; }

	void update(BSLib::uint64 a_delayMilliseconds);

public:
	virtual bool _init();
	virtual void _final();
	virtual bool _loadGameConfig(const std::string& a_configPath);
	virtual bool _initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void _cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void _cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);

private:
	virtual void	cb(BSLib::uint32 a_id);
	CDateTimer m_dateTimer;
};

}//GM

}//PrizeSystem

}//GSLib

#endif//__GSLIB_PRIZESYSTEM_GM_PRIZESYSTEMGM_H__
