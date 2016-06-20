//////////////////////////////////////////////////////////////////////
//	created:	2014/08/15
//	filename: 	src\GSLib\loginSystem\GM\accountLoginGMInforMgr.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_LOGINSYSTEM_GM_ACCOUNTLOGINGMINFORMGR_H__
#define __GSLIB_LOGINSYSTEM_GM_ACCOUNTLOGINGMINFORMGR_H__

#include <BSLib/utility/memory/objectMgr.h>
#include <BSLib/utility/uniqueID.h>
#include <GFLib/commonServer/baseDef.h>
#include <GSLib/loginSystem/msgLoginSystem.h>

namespace GSLib
{

namespace LoginSystem
{

namespace GM
{

//////////////////////////////////////////////////////////////////////////
struct SAccountLoginGMInfor
{
	GFLib::SAccountKey m_accountKey;
	std::string m_accountName;
	GFLib::SServerID m_centerServerID;
	BSLib::uint32 m_centerSessionID;
	GFLib::SServerID m_dataServerID;
	GFLib::SServerID m_gateServerID;
	bool m_isInit;

	SAccountLoginGMInfor()
	{
		m_centerSessionID = 0;
		m_isInit = false;
	}
	GFLib::SAccountKey getAccountKey() { return m_accountKey; }
};

BSLIB_UTILITY_OBJECTMGR_KEY1(CObjectAccountLoginGMInforMgr, AccountKey);

//////////////////////////////////////////////////////////////////////////
class CAccountLoginGMInforMgr
{
public:
	CAccountLoginGMInforMgr();
	~CAccountLoginGMInforMgr();

	BSLIB_SINGLETON_DECLARE(CAccountLoginGMInforMgr);

public:
 	bool checkCN2GMReqCreatePlayer(GFLib::SServerID a_centerServerID, CMsgLoginSystemCN2GMReqCreatePlayer& a_reqCreatePlayer);
 	bool checkDB2GMReqInitPlayer(CMsgLoginSystemDB2GMReqInitPlayer& a_reqInitPlayer);

	void finishInitPlayer(GFLib::SAccountKey& a_accountKey, ELoginResult a_result);

 	bool checkCN2GMReqAccountOffline(BSLib::uint32 a_centerSessionID, GFLib::SAccountKey& a_accountKey);
	bool checkCN2GMReqAccountOnline(BSLib::uint32 a_centerSessionID, GFLib::SAccountKey& a_accountKey);
	bool checkCN2GMReqAccountFinal(BSLib::uint32 a_centerSessionID, GFLib::SAccountKey& a_accountKey);

	void dataServerLeave(const GFLib::SServerID& a_dataServerID);
	void gateServerLeave(const GFLib::SServerID& a_gameServerID);
	void centerServerLeave(const GFLib::SServerID& a_centerServerID);

private:
	bool _notifyExit(SAccountLoginGMInfor* a_infor, bool a_neadNotifyDB = true, bool a_needNotifyCN = true);

private:
	CObjectAccountLoginGMInforMgr<GFLib::SAccountKey, SAccountLoginGMInfor> m_accountInforMgr;
};

}//GM

}//LoginSystem

}//GSLib


#endif//__GSLIB_LOGINSYSTEM_GM_ACCOUNTLOGINGMINFORMGR_H__