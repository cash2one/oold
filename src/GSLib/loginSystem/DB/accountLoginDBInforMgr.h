#ifndef __GSLIB_LOGINSYSTEM_DB_ACCOUNTLOGINDBINFORMGR_H__
#define __GSLIB_LOGINSYSTEM_DB_ACCOUNTLOGINDBINFORMGR_H__

#include <BSLib/utility/memory/objectMgr.h>
#include <BSLib/utility/uniqueID.h>
#include <GFLib/commonServer/baseDef.h>
#include <GSLib/loginSystem/msgLoginSystem.h>

namespace GSLib
{

namespace LoginSystem
{

namespace DB
{

//////////////////////////////////////////////////////////////////////////
struct SAccountLoginDBInfor
{
	GFLib::SAccountKey m_accountKey;
	std::string m_accountName;
	GFLib::SServerID m_centerServerID;
	BSLib::uint32 m_centerSessionID;
	GFLib::SServerID m_gameServerID;
	GFLib::SServerID m_gateServerID;
	BSLib::uint8 m_stateFinal;
	bool m_isInit;

	SAccountLoginDBInfor()
	{
		m_centerSessionID = 0;
		m_stateFinal = 0;
		m_isInit = false;
	}

	GFLib::SAccountKey getAccountKey() { return m_accountKey; }
};

BSLIB_UTILITY_OBJECTMGR_KEY1(CObjectAccountLoginDBInforMgr, AccountKey);

//////////////////////////////////////////////////////////////////////////
class CAccountLoginDBInforMgr
{
public:
	CAccountLoginDBInforMgr();
	~CAccountLoginDBInforMgr();

	BSLIB_SINGLETON_DECLARE(CAccountLoginDBInforMgr);

public:
	bool checkCN2DBReqCreatePlayer(GFLib::SServerID a_centerServerID, CMsgLoginSystemCN2DBReqCreatePlayer& a_reqCreatePlayer);
	bool checkCN2DBReqInitPlayer(CMsgLoginSystemCN2DBReqInitPlayer& a_reqInitPlayer);
	void checkGM2DBAckInitPlayer(CMsgLoginSystemGM2DBAckInitPlayer& a_reqInitPlayer);

	void finishInitPlayer(GFLib::SAccountKey& a_accountKey, ELoginResult a_result);

	bool checkCN2DBReqAccountOffline(BSLib::uint32 a_centerSessionID, GFLib::SAccountKey& a_accountKey);
	bool checkCN2DBReqAccountOnline(BSLib::uint32 a_centerSessionID, GFLib::SAccountKey& a_accountKey);
	void checkGT2DBNtfAccountFinal(BSLib::uint32 a_centerSessionID, GFLib::SAccountKey& a_accountKey);
	void checkGM2DBNtfAccountFinal(BSLib::uint32 a_centerSessionID, GFLib::SAccountKey& a_accountKey);
	bool checkCN2DBReqAccountFinal(BSLib::uint32 a_centerSessionID, GFLib::SAccountKey& a_accountKey);

	void checkNtfAccountQuit(GFLib::SAccountKey& a_accountKey);

	void gateServerLeave(const GFLib::SServerID& a_gateServerID);
	void gameServerLeave(const GFLib::SServerID& a_gameServerID);
	void centerServerLeave(const GFLib::SServerID& a_centerServerID);

private:
	bool _finishFinal(SAccountLoginDBInfor* a_infor, bool a_needNotifyCN = true);

private:
	CObjectAccountLoginDBInforMgr<GFLib::SAccountKey, SAccountLoginDBInfor> m_accountInforMgr;
};

}//DB

}//LoginSystem

}//GSLib


#endif//__GSLIB_LOGINSYSTEM_DB_ACCOUNTLOGINDBINFORMGR_H__
