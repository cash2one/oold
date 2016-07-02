#ifndef __GSLIB_LOGINSYSTEM_GT_LOGINSYSTEMGT_H__
#define __GSLIB_LOGINSYSTEM_GT_LOGINSYSTEMGT_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>
#include <GSLib/loginSystem/msgLoginSystem.h>

namespace GSLib
{

namespace LoginSystem
{

namespace GT
{

class CVerifyAccountLoginCallBack
{
protected:
	virtual void _cbVerifyAccountLogin(GFLib::SServerID& a_gameServerID, GFLib::SServerID& a_dbServerID, GFLib::SServerID& a_centerServerID) = 0;

	friend class CAccountLoginGTInforMgr;
};

class CLoginSystemGT : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CLoginSystemGT();
	virtual ~CLoginSystemGT();

	BSLIB_SINGLETON_DECLARE(CLoginSystemGT);

	virtual BSLib::uint16 ICommonSystem_getFuncType() { return GSLib::EFUNCTYPE_LOGINSYSTEM; }

public:
	bool verifyAccountLogin(GFLib::StubID a_stubID, std::string& a_gateLoginIP, CMsgLoginSystemGC2GTReqAccountLogin& a_reqAccountLogin, CMsgLoginSystemGT2GCAckAccountLogin& a_ackAccountLogin, CVerifyAccountLoginCallBack* a_cbverifyAccountLogin);
	void terminateAccountLogin(GFLib::SAccountKey& a_accountKey, BSLib::uint32 a_gateKey, BSLib::uint32 a_gateSession, GFLib::StubID a_stubID);

protected:
	virtual bool _init();
	virtual void _final();
	virtual bool ICommonSystem_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _ICommonSystem_startSystem();
	virtual void ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonSystem_cbServerLeave(const  GFLib::SServerID& a_serverID, const std::string& a_key);

private:
	void _onMsgLoginSystemCN2GTReqAccountLogin(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemCN2GTAckAccountLogin(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemCN2GTReqCreatePlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemCN2GTReqInitPlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	void _onMsgLoginSystemCN2GTAckAccountBreak(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemCN2GTReqAccountOffline(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemCN2GTReqAccountOnline(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemCN2GTReqAccountFinal(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	void _onMsgLoginSystemXS2GTNtfBroadcastMsg(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	bool _cbTimerAccountLogin(BSLib::uint64 a_para1, void* a_para2);

private:
	BSLib::Utility::CMutex m_mutex;
};

}//GT

}//LoginSystem

}//GSLib

#endif//__GSLIB_LOGINSYSTEM_GT_LOGINSYSTEMGT_H__

