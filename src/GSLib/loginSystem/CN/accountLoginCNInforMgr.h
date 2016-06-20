//////////////////////////////////////////////////////////////////////
//	created:	2014/07/21
//	filename: 	src\GSLib\loginSystem\CN\accountLoginCNInforMgr.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_LOGINSYSTEM_CN_ACCOUNTLOGINCNINFORMGR_H__
#define __GSLIB_LOGINSYSTEM_CN_ACCOUNTLOGINCNINFORMGR_H__

#include <BSLib/utility/memory/objectMgr.h>
#include <BSLib/utility/uniqueID.h>
#include <GFLib/commonServer/baseDef.h>
#include <GSLib/loginSystem/msgLoginSystem.h>
#include "CN/gateInforMgr.h"
#include "CN/gameInforMgr.h"

namespace GSLib
{

namespace LoginSystem
{

namespace CN
{

enum EAccountStateCN
{
	EACCNTSTT_CN_NULL		 = 0, //无效
	EACCNTSTT_CN_WAIT_GATE	 = 1, //等待gate返回
	EACCNTSTT_CN_WAIT_CLIENT = 2, //等待玩家登陆
	EACCNTSTT_CN_PLAYER_INIT = 3, //初始化玩家
	EACCNTSTT_CN_OK			 = 4, //初始化完成

	EACCNTSTT_CN_PLAYER_OFFLINE_BREAK = 5,	//玩家断线，进入离线状态
	EACCNTSTT_CN_KICK_ACCOUNT = 6,			//踢下在线玩家
	EACCNTSTT_CN_PLAYER_OFFLINE_KICK = 7,   //踢下在线玩家，进入离线状态

	EACCNTSTT_CN_OFFLINE_WAIT_CLIENT = 8,	//等待玩家上线
	EACCNTSTT_CN_OFFLINE_WAIT_GATE = 9,		//等待玩家上线, 等待gate返回

	EACCNTSTT_CN_PLAYER_ONLINE = 10,//玩家上线状态
	EACCNTSTT_CN_ACCOUNT_FINAL = 11, //玩家退出
};

//////////////////////////////////////////////////////////////////////////
struct SAccountLoginCNInfor
{
	BSLib::uint32 m_cnSessionID;
	BSLib::uint32 m_loginSession;
	GFLib::SAccountKey m_accountKey;
	std::string m_accountName;
	GFLib::SServerID m_loginServerID;
	GFLib::SServerID m_gateServerID;
	GFLib::SServerID m_gameServerID;
	EAccountStateCN m_accountState;
	BSLib::uint32 m_gateKey;
	BSLib::uint32 m_gateSession;

	BSLib::uint8 m_stateCreatePlayerGM;
	BSLib::uint8 m_stateCreatePlayerGT;
	BSLib::uint8 m_stateCreatePlayerDB;

	BSLib::uint8 m_stateInitPlayer;
	BSLib::uint8 m_stateOffline;
	BSLib::uint8 m_stateOnline;
	BSLib::uint8 m_stateFinal;
	BSLib::uint8 m_isInit;

	BSLib::Utility::TimerHandle m_timeHandleOffline;

	SAccountLoginCNInfor()
	{
		m_cnSessionID = 0;
		m_loginSession = 0;

		m_accountState = EACCNTSTT_CN_NULL;

		m_gateKey = 0;
		m_gateSession = 0;

		m_stateCreatePlayerGM = 0;
		m_stateCreatePlayerGT = 0;
		m_stateCreatePlayerDB = 0;

		m_stateInitPlayer = 0;
		m_stateOffline = 0;
		m_stateOnline = 0;
		m_stateFinal = 0;

		m_isInit = false;

		m_timeHandleOffline = BSLib::Utility::INVALID_TIMER;
	}

	void setAccountState(EAccountStateCN a_state) {	m_accountState = a_state; }
	EAccountStateCN getAccountState() { return m_accountState; }

	BSLib::uint32 getCNSessionID() { return m_cnSessionID; }
	GFLib::SAccountKey& getAccountKey() { return m_accountKey; }
};

BSLIB_UTILITY_OBJECTMGR_KEY2(CObjectAccountLoginCNInforMgr, CNSessionID, AccountKey);

//////////////////////////////////////////////////////////////////////////
class CAccountLoginCNInforMgr : public BSLib::Utility::CUniqueIDMgr<BSLib::uint32>
{
public:
	CAccountLoginCNInforMgr();
	~CAccountLoginCNInforMgr();

	BSLIB_SINGLETON_DECLARE(CAccountLoginCNInforMgr);

public:
	EAccountStateCN checkLG2CNReqAccountLogin(GFLib::SAccountKey& a_accountKey, GFLib::SServerID& a_gateServerID);
	bool registerLG2CNReqAccountLogin(BSLib::uint32& a_sessionID, GFLib::SServerID& a_loginServerID, GFLib::SServerID& a_gateServerID, CMsgLoginSystemLG2CNReqAccountLogin& a_reqAccountLogin, EAccountStateCN a_state);
	
	void checkGT2CNAckAccountLogin(CMsgLoginSystemGT2CNAckAccountLogin& a_ackAccountLogin);
	void removeCN2LGAckAccountLogin(BSLib::uint32& a_sessionID, ELoginResult a_loginResult);
	
	void timeoutAccountLoginInfor(BSLib::uint32& a_sessionID);
	void timeoutAccountOffline(BSLib::uint32& a_sessionID);

	bool checkGT2CNReqAccountLogin(CMsgLoginSystemGT2CNReqAccountLogin& a_reqAccountLogin, CMsgLoginSystemCN2GTAckAccountLogin& a_ackAccountLogin);
	
	void gateServerLeave(const GFLib::SServerID& a_gateServerID);
	void gameServerLeave(const GFLib::SServerID& a_gameServerID);
	void dataServerLeave(const GFLib::SServerID& a_dataServerID);
	
	void setDataServerID(const GFLib::SServerID& a_serverID) {  m_dataServerID = a_serverID; }
	
	void checkGM2CNAckCreatePlayer(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey, BSLib::uint32 a_state);
	void checkGT2CNAckCreatePlayer(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey, BSLib::uint32 a_state);
	void checkDB2CNAckCreatePlayer(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey, BSLib::uint32 a_state);

	void checkGM2CNNtfInitPlayer(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey, BSLib::uint32 a_state);
	void checkGT2CNAckInitPlayer(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey, BSLib::uint32 a_state);
	void checkDB2CNAckInitPlayer(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey, BSLib::uint32 a_state);

	void checkGT2CNReqAccountBreak(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey);
	void checkGT2CNAckAccountOffline(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey);
	void checkGM2CNAckAccountOffline(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey);
	void checkDB2CNAckAccountOffline(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey);

	void checkGT2CNAckAccountOnline(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey);
	void checkGM2CNAckAccountOnline(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey);
	void checkDB2CNAckAccountOnline(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey);

	void checkNtfAccountQuit(GFLib::SAccountKey& a_accountKey);

	void checkGT2CNAckAccountFinal(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey);
	void checkGM2CNAckAccountFinal(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey);
	void checkDB2CNAckAccountFinal(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey);

	void checkGT2CNNtfAccountTimeout(BSLib::uint32& a_sessionID, GFLib::SAccountKey& a_accountKey);
	
	void checkCNInitPlayer(GFLib::SAccountKey& a_accountKey, ELoginResult a_state);

	const GFLib::SServerID& getDataServerID() { return m_dataServerID; }

	virtual bool checkUniqueID(BSLib::uint32 a_id);

private:
	bool _notifyCreatePlayer(SAccountLoginCNInfor* a_infor);
	void _notifyInitPlayer(SAccountLoginCNInfor* a_infor);

	bool _createPlayer(SAccountLoginCNInfor* a_infor);
	bool _initPlayer(SAccountLoginCNInfor* a_infor);

	void _finishInitPlayer(SAccountLoginCNInfor* a_infor);

	void _notifyExitByInit(SAccountLoginCNInfor* a_infor);
	void _notifyExitByCreate(SAccountLoginCNInfor* a_infor);

	void _notifyOffline(SAccountLoginCNInfor* a_infor);
	void _finishOffline(SAccountLoginCNInfor* a_infor);

	void _notifyOnline(SAccountLoginCNInfor* a_infor);
	void _finishOnline(SAccountLoginCNInfor* a_infor);

	void _notifyFinal(SAccountLoginCNInfor* a_infor);
	void _finishFinal(SAccountLoginCNInfor* a_infor);

	void _notifyExit(SAccountLoginCNInfor* a_infor);

private:
	CObjectAccountLoginCNInforMgr<BSLib::uint32, GFLib::SAccountKey, SAccountLoginCNInfor> m_accountInforMgr;
	GFLib::SServerID m_dataServerID;
	BSLib::Utility::CUniqueID32 m_sessionAllocator;
};

}//CN

}//LoginSystem

}//GSLib


#endif//__GSLIB_LOGINSYSTEM_CN_ACCOUNTLOGINCNINFORMGR_H__
