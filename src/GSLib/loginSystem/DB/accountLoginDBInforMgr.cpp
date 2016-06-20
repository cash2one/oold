//////////////////////////////////////////////////////////////////////
//	created:	2014/07/20
//	filename:	src\GSLib\loginSystem\LG\accountLoginLGInforMgr.cpp
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GFLib/commonServer/stubMgr.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <GFLib/commonServer/accountMgr.h>
#include <GSLib/tracer.h>
#include <GSLib/loginSystem/msgLoginSystem.h>
#include <GSLib/loginSystem/DB/netPlayerDBMgr.h>
#include "DB/accountLoginDBInforMgr.h"

#define GSLIB_LOGINSYSTEM_STATE_CN 0x01
#define GSLIB_LOGINSYSTEM_STATE_GT 0x02
#define GSLIB_LOGINSYSTEM_STATE_GM 0x04
#define GSLIB_LOGINSYSTEM_STATE_DB 0x08

#define GSLIB_LOGINSYSTEM_STATE_XX 0x0F

namespace GSLib
{

namespace LoginSystem
{

namespace DB
{

CAccountLoginDBInforMgr::CAccountLoginDBInforMgr()
{
	;
}

CAccountLoginDBInforMgr::~CAccountLoginDBInforMgr()
{
	;
}

BSLIB_SINGLETON_DEFINE(CAccountLoginDBInforMgr);

bool CAccountLoginDBInforMgr::checkCN2DBReqCreatePlayer(GFLib::SServerID a_centerServerID, CMsgLoginSystemCN2DBReqCreatePlayer& a_reqCreatePlayer)
{
	SAccountLoginDBInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_reqCreatePlayer.m_accountKey);
	if (infor != NULL) {
		m_accountInforMgr.destroyByAccountKey(a_reqCreatePlayer.m_accountKey);
		infor = NULL;
	}
	infor = m_accountInforMgr.allcateObject(a_reqCreatePlayer.m_accountKey);
	if (infor == NULL) {
		return false;
	}
	infor->m_accountKey = a_reqCreatePlayer.m_accountKey;
	infor->m_accountName = a_reqCreatePlayer.m_accountName;
	infor->m_centerServerID = a_centerServerID;
	infor->m_centerSessionID = a_reqCreatePlayer.m_centerSessionID;
	infor->m_gameServerID = GFLib::SServerID(a_reqCreatePlayer.m_gameServerID);
	infor->m_gateServerID = GFLib::SServerID(a_reqCreatePlayer.m_gateServerID);
	infor->m_stateFinal = 0;

	CMsgLoginSystemDB2CNAckCreatePlayer ackCreatePlayer;
	ackCreatePlayer.m_accountKey = a_reqCreatePlayer.m_accountKey;
	ackCreatePlayer.m_centerSession = a_reqCreatePlayer.m_centerSessionID;

	CNetPlayerDBMgr* netPlayerDBMgr = CNetPlayerDBMgr::getSingleton();
	if (netPlayerDBMgr == NULL) {
		return false;
	}
	
	CNetPlayerDB* playerDB = netPlayerDBMgr->createNetPlayerDB(a_reqCreatePlayer.m_accountKey, a_reqCreatePlayer.m_accountName);
	if (playerDB == NULL) {
		return false;
	}
	GFLib::CommonServer::CAccountPtr accountPtr = new GFLib::CommonServer::CAccount(a_reqCreatePlayer.m_accountKey);
	if (accountPtr == NULL) {
		return false;
	}
	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "创建账号%s[AccountName=%s]", infor->m_accountKey.toLogString().c_str(), infor->m_accountName.c_str());

	playerDB->_setGameServerID(infor->m_gameServerID);
	playerDB->_setGateServerID(infor->m_gateServerID);
	playerDB->_setCenterServerID(a_centerServerID);

	playerDB->_setAccountPtr(accountPtr);
	accountPtr->setTransferMsgCB(playerDB);

	GFLib::CommonServer::CAccountMgr::singleton().addAccount(accountPtr);

	ackCreatePlayer.m_state = ELOGINRESULT_SUCCESS;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_centerServerID, ackCreatePlayer);

	return true;
}

bool CAccountLoginDBInforMgr::checkCN2DBReqInitPlayer(CMsgLoginSystemCN2DBReqInitPlayer& a_reqInitPlayer)
{
	SAccountLoginDBInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_reqInitPlayer.m_accountKey);
	if (infor == NULL) {
		return false;
	}
	if (infor->m_centerSessionID != a_reqInitPlayer.m_centerSessionID) {
		return false;
	}
	CNetPlayerDBMgr* netPlayerDBMgr = CNetPlayerDBMgr::getSingleton();
	if (netPlayerDBMgr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerDBMgr失败");
		return false;
	}
	CNetPlayerDB* playerDB = netPlayerDBMgr->getNetPlayerDB(a_reqInitPlayer.m_accountKey);
	if (playerDB == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerGM失败%s", a_reqInitPlayer.m_accountKey.toLogString().c_str());
		return false;
	}
	infor->m_isInit = true;
	playerDB->_cbInitPlayer();
	return true;
}

void CAccountLoginDBInforMgr::checkGM2DBAckInitPlayer(CMsgLoginSystemGM2DBAckInitPlayer& a_reqInitPlayer)
{
	SAccountLoginDBInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_reqInitPlayer.m_accountKey);
	if (infor == NULL) {
		return ;
	}
	if (a_reqInitPlayer.m_state != ELOGINRESULT_SUCCESS) {
		infor->m_stateFinal |= GSLIB_LOGINSYSTEM_STATE_GM | GSLIB_LOGINSYSTEM_STATE_GT;
	}
}

void CAccountLoginDBInforMgr::finishInitPlayer(GFLib::SAccountKey& a_accountKey, ELoginResult a_result)
{
	SAccountLoginDBInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_accountKey);
	if (infor == NULL) {
		return ;
	}
	if (a_result == ELOGINRESULT_SUCCESS) {
		CMsgLoginSystemDB2GMReqInitPlayer reqInitPlayer;
		reqInitPlayer.m_accountKey = a_accountKey;
		reqInitPlayer.m_centerSessionID = infor->m_centerSessionID;
		reqInitPlayer.m_centerServerID = infor->m_centerServerID.getServerID();

		GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(infor->m_gameServerID, reqInitPlayer);
	} else {
		infor->m_stateFinal |= GSLIB_LOGINSYSTEM_STATE_GM | GSLIB_LOGINSYSTEM_STATE_GT;
	}
	
	CMsgLoginSystemDB2CNAckInitPlayer ackInitPlayer;
	ackInitPlayer.m_accountKey = a_accountKey;
	ackInitPlayer.m_centerSessionID = infor->m_centerSessionID;
	ackInitPlayer.m_state = a_result;

	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(infor->m_centerServerID, ackInitPlayer);
}

bool CAccountLoginDBInforMgr::checkCN2DBReqAccountOffline(BSLib::uint32 a_centerSessionID, GFLib::SAccountKey& a_accountKey)
{
	SAccountLoginDBInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_accountKey);
	if (infor == NULL) {
		return false;
	}
// 	if (infor->m_centerSessionID != a_centerSessionID) {
// 		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "CenterSessionID不一致[AccountID=%lld]", infor->m_accountID);
// 		return false;
// 	}
	CNetPlayerDBMgr* netPlayerDBMgr = CNetPlayerDBMgr::getSingleton();
	if (netPlayerDBMgr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerDBMgr失败");
		return false;
	}
	CNetPlayerDB* playerDB = netPlayerDBMgr->getNetPlayerDB(a_accountKey);
	if (playerDB == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerGM失败%s", a_accountKey.toLogString().c_str());
		return false;
	}

	playerDB->_cbPlayerOffline();
	infor->m_centerSessionID = a_centerSessionID;

	CMsgLoginSystemDB2CNAckAccountOffline ackAccountOffline;
	ackAccountOffline.m_accountKey = a_accountKey;
	ackAccountOffline.m_centerSessionID = a_centerSessionID;

	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(infor->m_centerServerID, ackAccountOffline);
	return true;
}

bool CAccountLoginDBInforMgr::checkCN2DBReqAccountOnline(BSLib::uint32 a_centerSessionID, GFLib::SAccountKey& a_accountKey)
{
	SAccountLoginDBInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_accountKey);
	if (infor == NULL) {
		return false;
	}
// 	if (infor->m_centerSessionID != a_centerSessionID) {
// 		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "CenterSessionID不一致[AccountID=%lld]", infor->m_accountID);
// 		return ;
// 	}
	CNetPlayerDBMgr* netPlayerDBMgr = CNetPlayerDBMgr::getSingleton();
	if (netPlayerDBMgr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerDBMgr失败");
		return false;
	}
	CNetPlayerDB* playerDB = netPlayerDBMgr->getNetPlayerDB(a_accountKey);
	if (playerDB == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerGM失败%s", a_accountKey.toLogString().c_str());
		return false;
	}
	
	infor->m_centerSessionID = a_centerSessionID;

	playerDB->_cbPlayerOnline();

	CMsgLoginSystemDB2CNAckAccountOnline ackAccountOnline;
	ackAccountOnline.m_accountKey = a_accountKey;
	ackAccountOnline.m_centerSessionID = a_centerSessionID;

	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(infor->m_centerServerID, ackAccountOnline);
	return true;
}

void CAccountLoginDBInforMgr::checkGT2DBNtfAccountFinal(BSLib::uint32 a_centerSessionID, GFLib::SAccountKey& a_accountKey)
{
	SAccountLoginDBInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_accountKey);
	if (infor == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "AccountKey[%s]不存在", a_accountKey.toLogString().c_str());
		return ;
	}
// 	if (infor->m_centerSessionID != a_centerSessionID) {
// 		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "CenterSessionID不一致%s", infor->m_accountKey.toLogString().c_str());
// 		return ;
// 	}
	infor->m_stateFinal |= (GSLIB_LOGINSYSTEM_STATE_GT | GSLIB_LOGINSYSTEM_STATE_DB);
	if (infor->m_stateFinal == GSLIB_LOGINSYSTEM_STATE_XX) {
		_finishFinal(infor);
	}
}

void CAccountLoginDBInforMgr::checkGM2DBNtfAccountFinal(BSLib::uint32 a_centerSessionID, GFLib::SAccountKey& a_accountKey)
{
	SAccountLoginDBInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_accountKey);
	if (infor == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "AccountKey[%s]不存在", a_accountKey.toLogString().c_str());
		return ;
	}
// 	if (infor->m_centerSessionID != a_centerSessionID) {
// 		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "CenterSessionID不一致%s", infor->m_accountKey.toLogString().c_str());
// 		return ;
// 	}
	infor->m_stateFinal |= (GSLIB_LOGINSYSTEM_STATE_GM | GSLIB_LOGINSYSTEM_STATE_DB);
	if (infor->m_stateFinal == GSLIB_LOGINSYSTEM_STATE_XX) {
		_finishFinal(infor);
	}
}

bool CAccountLoginDBInforMgr::checkCN2DBReqAccountFinal(BSLib::uint32 a_centerSessionID, GFLib::SAccountKey& a_accountKey)
{
	SAccountLoginDBInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_accountKey);
	if (infor == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "AccountKey[%s]不存在", a_accountKey.toLogString().c_str());
		return false;
	}
// 	if (infor->m_centerSessionID != a_centerSessionID) {
// 		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "CenterSessionID不一致%s", infor->m_accountKey.toLogString().c_str());
// 		return false;
// 	}
	infor->m_stateFinal |= (GSLIB_LOGINSYSTEM_STATE_CN | GSLIB_LOGINSYSTEM_STATE_DB);
	if (infor->m_stateFinal == GSLIB_LOGINSYSTEM_STATE_XX) {
		return _finishFinal(infor);
	}
	return true;
}

void CAccountLoginDBInforMgr::checkNtfAccountQuit(GFLib::SAccountKey& a_accountKey)
{
	SAccountLoginDBInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_accountKey);
	if (infor == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "AccountKey[%s]不存在", a_accountKey.toLogString().c_str());
		return ;
	}
	CMsgLoginSystemDB2CNNtfAccountQuit ackAccountQuit;
	ackAccountQuit.m_accountKey = infor->m_accountKey;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(infor->m_centerServerID, ackAccountQuit);
}

void CAccountLoginDBInforMgr::gateServerLeave(const GFLib::SServerID& a_gateServerID)
{
	class CTraversalAccountCB : public CObjectAccountLoginDBInforMgr<GFLib::SAccountKey, SAccountLoginDBInfor>::CCallback
	{
	public:
		CTraversalAccountCB(const GFLib::SServerID& a_gateServerID) : m_gateServerID(a_gateServerID)
		{
			;
		}

		virtual bool exec(SAccountLoginDBInfor* _value)
		{
			if (_value->m_gateServerID != m_gateServerID) {
				return true;
			}
			_value->m_stateFinal |= (GSLIB_LOGINSYSTEM_STATE_GT | GSLIB_LOGINSYSTEM_STATE_DB);
			m_gateAcountArray.push_back(_value);
			return true;
		}

		GFLib::SServerID m_gateServerID;
		std::vector<SAccountLoginDBInfor*> m_gateAcountArray;
	};

	CTraversalAccountCB cb(a_gateServerID);

	m_accountInforMgr.traversal(cb);

	for (BSLib::uint32 i=0; i<cb.m_gateAcountArray.size(); ++i) {
		if (cb.m_gateAcountArray[i]->m_stateFinal == GSLIB_LOGINSYSTEM_STATE_XX) {
			_finishFinal(cb.m_gateAcountArray[i]);
		}
	}
}

void CAccountLoginDBInforMgr::gameServerLeave(const GFLib::SServerID& a_gameServerID)
{
	class CTraversalAccountCB : public CObjectAccountLoginDBInforMgr<GFLib::SAccountKey, SAccountLoginDBInfor>::CCallback
	{
	public:
		CTraversalAccountCB(const GFLib::SServerID& a_gameServerID) : m_gameServerID(a_gameServerID)
		{
			;
		}

		virtual bool exec(SAccountLoginDBInfor* _value)
		{
			if (_value->m_gameServerID != m_gameServerID) {
				return true;
			}
			_value->m_stateFinal |= (GSLIB_LOGINSYSTEM_STATE_GM | GSLIB_LOGINSYSTEM_STATE_DB);
			m_gateAcountArray.push_back(_value);
			return true;
		}

		GFLib::SServerID m_gameServerID;
		std::vector<SAccountLoginDBInfor*> m_gateAcountArray;
	};

	CTraversalAccountCB cb(a_gameServerID);

	m_accountInforMgr.traversal(cb);

	for (BSLib::uint32 i=0; i<cb.m_gateAcountArray.size(); ++i) {
		if (cb.m_gateAcountArray[i]->m_stateFinal == GSLIB_LOGINSYSTEM_STATE_XX) {
			_finishFinal(cb.m_gateAcountArray[i]);
		}
	}
}

void CAccountLoginDBInforMgr::centerServerLeave(const GFLib::SServerID& a_centerServerID)
{
	class CTraversalAccountCB : public CObjectAccountLoginDBInforMgr<GFLib::SAccountKey, SAccountLoginDBInfor>::CCallback
	{
	public:
		CTraversalAccountCB(const GFLib::SServerID& a_centerServerID) : m_centerServerID(a_centerServerID)
		{
			;
		}

		virtual bool exec(SAccountLoginDBInfor* _value)
		{
			if (_value->m_centerServerID != m_centerServerID) {
				return true;
			}
			_value->m_stateFinal |= (GSLIB_LOGINSYSTEM_STATE_CN | GSLIB_LOGINSYSTEM_STATE_DB);
			m_gateAcountArray.push_back(_value);
			return true;
		}

		GFLib::SServerID m_centerServerID;
		std::vector<SAccountLoginDBInfor*> m_gateAcountArray;
	};

	CTraversalAccountCB cb(a_centerServerID);

	m_accountInforMgr.traversal(cb);

	for (BSLib::uint32 i=0; i<cb.m_gateAcountArray.size(); ++i) {
		if (cb.m_gateAcountArray[i]->m_stateFinal == GSLIB_LOGINSYSTEM_STATE_XX) {
			_finishFinal(cb.m_gateAcountArray[i], false);
		}
	}
}

bool CAccountLoginDBInforMgr::_finishFinal(SAccountLoginDBInfor* a_infor, bool a_needNotifyCN)
{
	CNetPlayerDBMgr* netPlayerDBMgr = CNetPlayerDBMgr::getSingleton();
	if (netPlayerDBMgr == NULL) {
		GFLib::CommonServer::CAccountMgr::singleton().delAccount(a_infor->m_accountKey);
		m_accountInforMgr.destroyByAccountKey(a_infor->m_accountKey);
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerDBMgr失败");
		return false;
	}
	CNetPlayerDB* playerDB = netPlayerDBMgr->getNetPlayerDB(a_infor->m_accountKey);
	if (playerDB == NULL) {
		GFLib::CommonServer::CAccountMgr::singleton().delAccount(a_infor->m_accountKey);
		m_accountInforMgr.destroyByAccountKey(a_infor->m_accountKey);
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerGM失败%s", a_infor->m_accountKey.toLogString().c_str());
		return false;
	}

	if (a_infor->m_isInit) {
		playerDB->_cbFinalPlayer();
	}

	if (a_needNotifyCN) {
		CMsgLoginSystemDB2CNAckAccountFinal ackAccountFinal;
		ackAccountFinal.m_accountKey = a_infor->m_accountKey;
		ackAccountFinal.m_centerSessionID = a_infor->m_centerSessionID;

		GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_infor->m_centerServerID, ackAccountFinal);
	}

	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "释放账号%s[AccountName=%s]", a_infor->m_accountKey.toLogString().c_str(), a_infor->m_accountName.c_str());

	netPlayerDBMgr->removeNetPlayerDB(a_infor->m_accountKey);
	GFLib::CommonServer::CAccountMgr::singleton().delAccount(a_infor->m_accountKey);
	m_accountInforMgr.destroyByAccountKey(a_infor->m_accountKey);

	return true;

}

}//DB

}//LoginSystem

}//GSLib
