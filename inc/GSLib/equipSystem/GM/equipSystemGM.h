//////////////////////////////////////////////////////////////////////
//	created:	2014/07/25
//	filename: 	GSLib\equipSystem\GM\equipSystemGM.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_EQUIPSYSTEM_GM_EQUIPSYSTEMGM_H__
#define __GSLIB_EQUIPSYSTEM_GM_EQUIPSYSTEMGM_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace EquipSystem
{

namespace GM
{

class CEquipSystemGM : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CEquipSystemGM();
	virtual ~CEquipSystemGM();

	BSLIB_SINGLETON_DECLARE(CEquipSystemGM);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_EQUIPSYSTEM; }

protected:
	virtual bool _init();
	virtual void _final();
	virtual bool _loadGameConfig(const std::string& a_configPath);
	virtual bool _initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void _cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void _cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);

};

}//GM

}//EquipSystem

}//GSLib

#endif//__GSLIB_EQUIPSYSTEM_GM_EQUIPSYSTEMGM_H__
