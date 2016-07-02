#ifndef __GSLIB_LOGINSYSTEM_CN_LOGINSYSTEMCN_H__
#define __GSLIB_LOGINSYSTEM_CN_LOGINSYSTEMCN_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace LoginSystem
{

namespace CN
{

class CLoginSystemCN : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CLoginSystemCN();
	virtual ~CLoginSystemCN();

	BSLIB_SINGLETON_DECLARE(CLoginSystemCN);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_LOGINSYSTEM; }

	BSLib::Utility::TimerHandle addTimeoutAccountOnline(BSLib::uint32& a_sessionID);
	void delTimeoutAccountOnline(BSLib::Utility::TimerHandle& a_timeHandle);

protected:
	virtual bool _init();
	virtual void _final();
	virtual bool ICommonSystem_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);

private:
	void _onMsgLoginSystemLG2CNReqAccountLogin(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemGT2CNAckAccountLogin(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemGT2CNReqAccountLogin(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	void _onMsgLoginSystemGM2CNAckCreatePlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemGT2CNAckCreatePlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemDB2CNAckCreatePlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	
	void _onMsgLoginSystemGM2CNNtfInitPlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemGT2CNAckInitPlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemDB2CNAckInitPlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	void _onMsgLoginSystemGT2CNReqAccountBreak(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemGT2CNAckAccountOffline(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemGM2CNAckAccountOffline(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemDB2CNAckAccountOffline(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	void _onMsgLoginSystemGT2CNAckAccountOnline(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemGM2CNAckAccountOnline(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemDB2CNAckAccountOnline(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	void _onMsgLoginSystemGT2CNNtfAccountQuit(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemGM2CNNtfAccountQuit(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemDB2CNNtfAccountQuit(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	void _onMsgLoginSystemGT2CNAckAccountFinal(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemGM2CNAckAccountFinal(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemDB2CNAckAccountFinal(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	void _onMsgLoginSystemGT2CNNtfAccountTimeout(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	
//	bool _cbTimerAccountLogin(BSLib::uint64 a_para1, void* a_para2);
	bool _cbTimerAccountOfflineTimeout(BSLib::uint64 a_para1, void* a_para2);
};

}//CN

}//LoginSystem

}//GSLib

#endif//__GSLIB_LOGINSYSTEM_CN_LOGINSYSTEMCN_H__

