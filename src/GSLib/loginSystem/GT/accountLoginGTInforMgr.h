//////////////////////////////////////////////////////////////////////
//	created:	2014/07/21
//	filename: 	src\GSLib\loginSystem\GT\accountLoginGTInforMgr.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_LOGINSYSTEM_GT_ACCOUNTLOGINGTINFORMGR_H__
#define __GSLIB_LOGINSYSTEM_GT_ACCOUNTLOGINGTINFORMGR_H__

#include <BSLib/utility/memory/objectMgr.h>
#include <BSLib/utility/uniqueID.h>
#include <GFLib/commonServer/baseDef.h>
#include <GSLib/loginSystem/msgLoginSystem.h>
#include <GSLib/loginSystem/GT/loginSystemGT.h>

namespace GSLib
{

namespace LoginSystem
{

namespace GT
{

enum EAccountStateGT
{
	EACCNTSTT_GT_NULL		 = 0,
	EACCNTSTT_GT_WAIT_CLIENT = 1, //等待玩家登陆
	EACCNTSTT_GT_WAIT_CENTER = 2, //等待Center返回
	EACCNTSTT_GT_OK			 = 3, //登陆完成
	EACCNTSTT_GT_OFFINE = 4,	  //离线状态
	EACCNTSTT_GT_FINAL = 5,	  //离线状态
// 
// 	EACCNTSTT_GT_BREAK_WAIT_CENTER = 6, //登陆完成
// 	EACCNTSTT_GT_OFFLINE_WAIT_CLIENT = 7, //等待玩家登陆
// 	EACCNTSTT_GT_OFFLINE_WAIT_CENTER = 8, //等待Center返回
};

//////////////////////////////////////////////////////////////////////////
struct SAccountLoginGTInfor
{
	BSLib::uint32 m_gtSessionID;
	BSLib::uint32 m_gateKey;
	BSLib::uint32 m_channelID;
	std::string m_accountName;
	std::string m_accountLoginIP;
	GFLib::SAccountKey m_accountKey;
	GFLib::SServerID m_centerServerID;
	GFLib::SServerID m_gameServerID;
	GFLib::SServerID m_dataServerID;
	BSLib::uint32 m_centerSessionID;
	GFLib::StubID m_stubID;
	EAccountStateGT m_state;
	CVerifyAccountLoginCallBack* m_cbverifyAccountLogin;
	bool m_isInit;

	SAccountLoginGTInfor()
	{
		m_gtSessionID = 0;
		m_gateKey = 0;
		m_channelID = 0;
		m_centerSessionID = 0;
		m_stubID = GFLib::INVALID_STUBID;
		m_state = EACCNTSTT_GT_NULL;
		m_cbverifyAccountLogin = NULL;
		m_isInit = false;
	}

	BSLib::uint32 getGTSessionID() { return m_gtSessionID; }
	GFLib::SAccountKey getAccountKey() { return m_accountKey; }
};

BSLIB_UTILITY_OBJECTMGR_KEY2(CObjectAccountLoginGTInfor, GTSessionID, AccountKey);


//////////////////////////////////////////////////////////////////////////
class CAccountLoginGTInforMgr : public BSLib::Utility::CUniqueIDMgr<BSLib::uint32>
{
public:
	CAccountLoginGTInforMgr();
	~CAccountLoginGTInforMgr();

	BSLIB_SINGLETON_DECLARE(CAccountLoginGTInforMgr);

public:
	int registerCN2GTReqAccountLogin(BSLib::uint32& a_sessionID, GFLib::SServerID& a_centerServerID, CMsgLoginSystemCN2GTReqAccountLogin& a_reqAccountLogin, CMsgLoginSystemGT2CNAckAccountLogin& a_ackAccountLogin);
	bool verifyAccountLogin(GFLib::StubID a_stubID, std::string& a_gateLoginIP, CMsgLoginSystemGC2GTReqAccountLogin& a_reqAccountLogin, CMsgLoginSystemGT2GCAckAccountLogin& a_ackAccountLogin, CVerifyAccountLoginCallBack* a_cbverifyAccountLogin);
	
	void timeroutAccountLogin(BSLib::uint32& a_sessionID);
	void terminateAccountLoginInfor(GFLib::SAccountKey& a_accountKey, BSLib::uint32 a_gateKey, BSLib::uint32 a_gateSession, GFLib::StubID a_stubID);

	void checCN2GTAckAccountLogin(CMsgLoginSystemCN2GTAckAccountLogin& a_ackAccountLogin);

	bool checCN2GTReqCreatePlayer(CMsgLoginSystemCN2GTReqCreatePlayer& a_reqCreatePlayer);
	bool checCN2GTReqInitPlayer(CMsgLoginSystemCN2GTReqInitPlayer& a_reqInitPlayer);

	void checCN2GTAckAccountBreak(BSLib::uint32 a_gateSessionID, GFLib::SAccountKey& a_accountKey);
	bool checCN2GTReqAccountOffline(BSLib::uint32 a_gateSessionID, GFLib::SAccountKey& a_accountKey);
	bool checCN2GTReqAccountOnline(BSLib::uint32 a_gateSessionID, GFLib::SAccountKey& a_accountKey);
	bool checCN2GTReqAccountFinal(BSLib::uint32 a_gateSessionID, GFLib::SAccountKey& a_accountKey);

	void finishInitPlayer(GFLib::SAccountKey& a_accountKey, ELoginResult a_result);

	void checkNtfAccountQuit(GFLib::SAccountKey& a_accountKey);

	void dataServerLeave(const GFLib::SServerID& a_dataServerID);
	void gameServerLeave(const GFLib::SServerID& a_gameServerID);
	void centerServerLeave(const GFLib::SServerID& a_centerServerID);

	void broadcastMsg(CMsgLoginSystemXS2GTNtfBroadcastMsg* a_ntfBroadcastMsg);

private:
	virtual bool checkUniqueID(BSLib::uint32 a_id);
	void _terminateAccount(SAccountLoginGTInfor* a_infor);
	void _finishFinal(SAccountLoginGTInfor* a_infor, bool a_needNotifyDB = true, bool a_needNotyfyCN = true);

private:
	CObjectAccountLoginGTInfor<BSLib::uint32, GFLib::SAccountKey, SAccountLoginGTInfor> m_accountInforMgr;
	BSLib::Utility::CUniqueID32 m_sessionAllocator;
};

}//GT

}//LoginSystem

}//GSLib


#endif//__GSLIB_LOGINSYSTEM_GT_ACCOUNTLOGINGTINFORMGR_H__
