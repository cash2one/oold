//////////////////////////////////////////////////////////////////////
//	created:	2014/07/19
//	filename:	GSLib\loginSystem\DB\loginSystemDB.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_LOGINSYSTEM_DB_LOGINSYSTEMDB_H__
#define __GSLIB_LOGINSYSTEM_DB_LOGINSYSTEMDB_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace LoginSystem
{

namespace DB
{

class CLoginSystemDB : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CLoginSystemDB();
	virtual ~CLoginSystemDB();

	BSLIB_SINGLETON_DECLARE(CLoginSystemDB);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_LOGINSYSTEM; }

protected:
	virtual bool _init();
	virtual void _final();
	virtual bool _loadGameConfig(const std::string& a_configPath);
	virtual bool _initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void _cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void _cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);

private:
	void _onMsgLoginSystemCN2DBReqCreatePlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemCN2DBReqInitPlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemGM2DBAckInitPlayer(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	void _onMsgLoginSystemCN2DBReqAccountOffline(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemCN2DBReqAccountOnline(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	void _onMsgLoginSystemGT2DBNtfAccountFinal(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemGM2DBNtfAccountFinal(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemCN2DBReqAccountFinal(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

};

}//DB

}//LoginSystem

}//GSLib

#endif//__GSLIB_LOGINSYSTEM_DB_LOGINSYSTEMDB_H__
