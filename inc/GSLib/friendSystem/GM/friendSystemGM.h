
#ifndef __GSLIB_FRIENDSYSTEM_GM_FRIENDSYSTEMGM_H__
#define __GSLIB_FRIENDSYSTEM_GM_FRIENDSYSTEMGM_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>
#include <GSLib/dbSystem/keyTable.h>
#include <BSLib/database/dbTableRow.h>

namespace GSLib
{

namespace FriendSystem
{

namespace GM
{

class CFriendSystemGM : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CFriendSystemGM();
	virtual ~CFriendSystemGM();

	BSLIB_SINGLETON_DECLARE(CFriendSystemGM);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_FRIENDSYSTEM; }

	void update(BSLib::uint64 a_delayMilliseconds);

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

}

}//GSLib

#endif
