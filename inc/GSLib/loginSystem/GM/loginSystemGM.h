#ifndef __GSLIB_LOGINSYSTEM_GM_LOGINSYSTEMGM_H__
#define __GSLIB_LOGINSYSTEM_GM_LOGINSYSTEMGM_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace LoginSystem
{

namespace GM
{

class CLoginSystemGM : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CLoginSystemGM();
	virtual ~CLoginSystemGM();

	BSLIB_SINGLETON_DECLARE(CLoginSystemGM);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_LOGINSYSTEM; }

protected:
	virtual bool _init();
	virtual void _final();
	virtual bool ICommonServer_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);

private:
	void _onMsgLoginSystemCN2GMReqCreatePlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemDB2GMReqInitPlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	void _onMsgLoginSystemCN2GMReqAccountOffline(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemCN2GMReqAccountOnline(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemCN2GMReqAccountFinal(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
};

}//GM

}//LoginSystem

}//GSLib

#endif//__GSLIB_LOGINSYSTEM_GM_LOGINSYSTEMGM_H__

