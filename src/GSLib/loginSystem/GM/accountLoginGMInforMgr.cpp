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
#include <GSLib/loginSystem/GM/netPlayerGMMgr.h>
#include "GM/accountLoginGMInforMgr.h"

#define GSLIB_LOGINSYSTEM_STATE_CN 0x01
#define GSLIB_LOGINSYSTEM_STATE_GT 0x02
#define GSLIB_LOGINSYSTEM_STATE_GM 0x04
#define GSLIB_LOGINSYSTEM_STATE_DB 0x08

#define GSLIB_LOGINSYSTEM_STATE_XX 0x0F

namespace GSLib
{

namespace LoginSystem
{

namespace GM
{

CAccountLoginGMInforMgr::CAccountLoginGMInforMgr()
{
	;
}

CAccountLoginGMInforMgr::~CAccountLoginGMInforMgr()
{
	;
}

BSLIB_SINGLETON_DEFINE(CAccountLoginGMInforMgr);


bool CAccountLoginGMInforMgr::checkCN2GMReqCreatePlayer(GFLib::SServerID a_centerServerID, CMsgLoginSystemCN2GMReqCreatePlayer& a_reqCreatePlayer)
{
	SAccountLoginGMInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_reqCreatePlayer.m_accountKey);
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
	infor->m_dataServerID = GFLib::SServerID(a_reqCreatePlayer.m_dataServerID);
	infor->m_gateServerID = GFLib::SServerID(a_reqCreatePlayer.m_gateServerID);

	CMsgLoginSystemGM2CNAckCreatePlayer ackCreatePlayer;
	ackCreatePlayer.m_accountKey = a_reqCreatePlayer.m_accountKey;
	ackCreatePlayer.m_centerSession = a_reqCreatePlayer.m_centerSessionID;

	CNetPlayerGMMgr* netPlayerGMMgr = CNetPlayerGMMgr::getSingleton();
	if (netPlayerGMMgr == NULL) {
		return false;
	}
	CNetPlayerGM* playerGM = netPlayerGMMgr->createNetPlayerGM(a_reqCreatePlayer.m_accountKey, a_reqCreatePlayer.m_accountName);
	if (playerGM == NULL) {
		return false;
	}
	GFLib::CommonServer::CAccountPtr accountPtr = new GFLib::CommonServer::CAccount(a_reqCreatePlayer.m_accountKey);
	if (accountPtr == NULL) {
		return false;
	}
	
	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "创建账号%s[AccountName=%s]", infor->m_accountKey.toLogString().c_str(), infor->m_accountName.c_str());

	GFLib::SServerID dataServerID = GFLib::SServerID(a_reqCreatePlayer.m_dataServerID);
	GFLib::SServerID gateServerID = GFLib::SServerID(a_reqCreatePlayer.m_gateServerID);
	playerGM->_setDataServerID(dataServerID);
	playerGM->_setGateServerID(gateServerID);
	playerGM->_setCenterServerID(a_centerServerID);

	playerGM->_setAccountPtr(accountPtr);
	accountPtr->setTransferMsgCB(playerGM);

	GFLib::CommonServer::CAccountMgr::singleton().addAccount(accountPtr);

	ackCreatePlayer.m_state = ELOGINRESULT_SUCCESS;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_centerServerID, ackCreatePlayer);
	return true;
}

bool CAccountLoginGMInforMgr::checkDB2GMReqInitPlayer(CMsgLoginSystemDB2GMReqInitPlayer& a_reqInitPlayer)
{
	SAccountLoginGMInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_reqInitPlayer.m_accountKey);
	if (infor == NULL) {
		return false;
	}
	if (infor->m_centerSessionID != a_reqInitPlayer.m_centerSessionID) {
		return false;
	}
	
	CNetPlayerGMMgr* netPlayerGMMgr = CNetPlayerGMMgr::getSingleton();
	if (netPlayerGMMgr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取netPlayerGMMgr失败");
		return false;
	}
	CNetPlayerGM* playerGM = netPlayerGMMgr->getNetPlayerGM(infor->m_accountKey);
	if (playerGM == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerGM失败%s", infor->m_accountKey.toLogString().c_str());
		return false;
	}
	infor->m_isInit = true;

	playerGM->_initMsg();
	playerGM->_cbInitPlayer();
	return true;
}

void CAccountLoginGMInforMgr::finishInitPlayer(GFLib::SAccountKey& a_accountKey, ELoginResult a_result)
{
	SAccountLoginGMInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_accountKey);
	if (infor == NULL) {
		return ;
	}

	CMsgLoginSystemGM2DBAckInitPlayer ackInitPlayer;
	ackInitPlayer.m_accountKey = a_accountKey;
	ackInitPlayer.m_centerSessionID = infor->m_centerSessionID;
	ackInitPlayer.m_state = a_result;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(infor->m_dataServerID, ackInitPlayer);

	CMsgLoginSystemGM2CNNtfInitPlayer ntfInitPlayer;
	ntfInitPlayer.m_accountKey = a_accountKey;
	ntfInitPlayer.m_centerSessionID = infor->m_centerSessionID;
	ntfInitPlayer.m_state = a_result;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(infor->m_centerServerID, ntfInitPlayer);
}

bool CAccountLoginGMInforMgr::checkCN2GMReqAccountOffline(BSLib::uint32 a_centerSessionID, GFLib::SAccountKey& a_accountKey)
{
	SAccountLoginGMInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_accountKey);
	if (infor == NULL) {
		return false;
	}
// 	if (infor->m_centerSessionID != a_centerSessionID) {
// 		return false;
// 	}

	CNetPlayerGMMgr* netPlayerGMMgr = CNetPlayerGMMgr::getSingleton();
	if (netPlayerGMMgr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerGMMgr失败");
		return false;
	}
	CNetPlayerGM* playerGM = netPlayerGMMgr->getNetPlayerGM(a_accountKey);
	if (playerGM == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerGM失败%s", a_accountKey.toLogString().c_str());
		return false;
	}

	playerGM->_cbPlayerOffline();

	CMsgLoginSystemGM2CNAckAccountOffline ackAccountOffline;
	ackAccountOffline.m_centerSessionID = a_centerSessionID;
	ackAccountOffline.m_accountKey = a_accountKey;

	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(infor->m_centerServerID, ackAccountOffline);
	return true;
}

bool CAccountLoginGMInforMgr::checkCN2GMReqAccountOnline(BSLib::uint32 a_centerSessionID, GFLib::SAccountKey& a_accountKey)
{
	SAccountLoginGMInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_accountKey);
	if (infor == NULL) {
		return false;
	}
// 	if (infor->m_centerSessionID != a_centerSessionID) {
// 		return ;
// 	}

	CNetPlayerGMMgr* netPlayerGMMgr = CNetPlayerGMMgr::getSingleton();
	if (netPlayerGMMgr == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerGMMgr失败");
		return false;
	}
	CNetPlayerGM* playerGM = netPlayerGMMgr->getNetPlayerGM(a_accountKey);
	if (playerGM == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerGM失败%s", a_accountKey.toLogString().c_str());
		return false;
	}

	infor->m_centerSessionID = a_centerSessionID;

	playerGM->_cbPlayerOnline();


	CMsgLoginSystemGM2CNAckAccountOnline ackAccountOnline;
	ackAccountOnline.m_centerSessionID = a_centerSessionID;
	ackAccountOnline.m_accountKey = a_accountKey;

	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(infor->m_centerServerID, ackAccountOnline);
	return true;
}

bool CAccountLoginGMInforMgr::checkCN2GMReqAccountFinal(BSLib::uint32 a_centerSessionID, GFLib::SAccountKey& a_accountKey)
{
	SAccountLoginGMInfor* infor = m_accountInforMgr.getObjectByAccountKey(a_accountKey);
	if (infor == NULL) {
		return false;
	}
	if (infor->m_centerSessionID != a_centerSessionID) {
		return false;
	}
	return _notifyExit(infor);
}

void CAccountLoginGMInforMgr::dataServerLeave(const GFLib::SServerID& a_dataServerID)
{
	class CTraversalAccountCB : public CObjectAccountLoginGMInforMgr<GFLib::SAccountKey, SAccountLoginGMInfor>::CCallback
	{
	public:
		CTraversalAccountCB(const GFLib::SServerID& a_dataServerID) : m_dataServerID(a_dataServerID)
		{
			;
		}

		virtual bool exec(SAccountLoginGMInfor* _value)
		{
			if (_value->m_dataServerID != m_dataServerID) {
				return true;
			}
			m_gateAcountArray.push_back(_value);
			return true;
		}

		GFLib::SServerID m_dataServerID;
		std::vector<SAccountLoginGMInfor*> m_gateAcountArray;
	};

	CTraversalAccountCB cb(a_dataServerID);

	m_accountInforMgr.traversal(cb);

	for (BSLib::uint32 i=0; i<cb.m_gateAcountArray.size(); ++i) {
		_notifyExit(cb.m_gateAcountArray[i], false, false);
	}
}

void CAccountLoginGMInforMgr::gateServerLeave(const GFLib::SServerID& a_gameServerID)
{
	;
}

void CAccountLoginGMInforMgr::centerServerLeave(const GFLib::SServerID& a_centerServerID)
{
	class CTraversalAccountCB : public CObjectAccountLoginGMInforMgr<GFLib::SAccountKey, SAccountLoginGMInfor>::CCallback
	{
	public:
		CTraversalAccountCB(const GFLib::SServerID& a_centerServerID) : m_centerServerID(a_centerServerID)
		{
			;
		}

		virtual bool exec(SAccountLoginGMInfor* _value)
		{
			if (_value->m_centerServerID != m_centerServerID) {
				return true;
			}
			m_gateAcountArray.push_back(_value);
			return true;
		}

		GFLib::SServerID m_centerServerID;
		std::vector<SAccountLoginGMInfor*> m_gateAcountArray;
	};

	CTraversalAccountCB cb(a_centerServerID);

	m_accountInforMgr.traversal(cb);

	for (BSLib::uint32 i=0; i<cb.m_gateAcountArray.size(); ++i) {
		_notifyExit(cb.m_gateAcountArray[i], true, false);
	}
}

bool CAccountLoginGMInforMgr::_notifyExit(SAccountLoginGMInfor* a_infor, bool a_neadNotifyDB, bool a_needNotifyCN)
{
	CNetPlayerGMMgr* netPlayerGMMgr = CNetPlayerGMMgr::getSingleton();
	if (netPlayerGMMgr == NULL) {
		GFLib::CommonServer::CAccountMgr::singleton().delAccount(a_infor->m_accountKey);
		m_accountInforMgr.destroyByAccountKey(a_infor->m_accountKey);
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerGMMgr失败");
		return false;
	}

	CNetPlayerGM* playerGM = netPlayerGMMgr->getNetPlayerGM(a_infor->m_accountKey);
	if (playerGM == NULL) {
		GFLib::CommonServer::CAccountMgr::singleton().delAccount(a_infor->m_accountKey);
		m_accountInforMgr.destroyByAccountKey(a_infor->m_accountKey);
		BSLIB_LOG_ERROR(ETT_GSLIB_LOGINSYSTEM, "获取CNetPlayerGM失败%s", a_infor->m_accountKey.toLogString().c_str());
		return false;
	}
	if (a_infor->m_isInit) {
		playerGM->_cbFinalPlayer();
	}
	
	if (a_neadNotifyDB) {
		CMsgLoginSystemGM2DBNtfAccountFinal ackAccountFinalDB;
		ackAccountFinalDB.m_accountKey = a_infor->m_accountKey;
		ackAccountFinalDB.m_centerSessionID = a_infor->m_centerSessionID;
		GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_infor->m_dataServerID, ackAccountFinalDB);
	}
	if (a_needNotifyCN) {
		CMsgLoginSystemGM2CNAckAccountFinal ackAccountFinalCN;
		ackAccountFinalCN.m_centerSessionID = a_infor->m_centerSessionID;
		ackAccountFinalCN.m_accountKey = a_infor->m_accountKey;

		GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_infor->m_centerServerID, ackAccountFinalCN);
	}

	BSLIB_LOG_DEBUG(ETT_GSLIB_LOGINSYSTEM, "释放账号%s[AccountName=%s]", a_infor->m_accountKey.toLogString().c_str(), a_infor->m_accountName.c_str());

	GFLib::CommonServer::CAccountMgr::singleton().delAccount(a_infor->m_accountKey);
	netPlayerGMMgr->removeNetPlayerGM(a_infor->m_accountKey);
	m_accountInforMgr.destroyByAccountKey(a_infor->m_accountKey);
	return true;
}

}//GM

}//LoginSystem

}//GSLib
