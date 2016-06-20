
#ifndef __GSLIB_MASTERSYSTEM_SP_MASTERSYSTEMSP_H__
#define __GSLIB_MASTERSYSTEM_SP_MASTERSYSTEMSP_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>
#include <GSLib/dbSystem/keyTable.h>
#include <GSLib/dbSystem/keyIndexTable.h>
#include <GSLib/masterSystem/msgMasterSystem.h>
#include <GSLib/masterSystem/DB/tableMasterDB.h>

#include <json/inc/config.h>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>
// #include <json/inc/rapidjson/document.h>
// #include <json/inc/rapidjson/prettywriter.h>
// #include <json/inc/rapidjson/filestream.h>
#include "msg_def.h"

namespace GSLib
{

namespace MasterSystem
{

namespace SP
{


#define  REPLY_SUCCESS	0
#define	 REPLY_FAILED	1

struct Replyst
{	
	Replyst()
		:m_id(0)
		,m_result(0)
	{
	}

	Replyst(const Replyst& other)
	{
		this->m_id = other.m_id;
		this->m_result = other.m_result;
		this->m_info = other.m_info;
	}

	BSLib::uint32 m_id;
	BSLib::uint32 m_result;
	std::string m_info;
};

class CMasterSystemSP : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CMasterSystemSP();
	virtual ~CMasterSystemSP();

	BSLIB_SINGLETON_DECLARE(CMasterSystemSP);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_MASTERSYSTEM; }

	void update(BSLib::uint64 a_delayMilliseconds);

public:
	virtual bool _init();
	virtual void _final();
	virtual bool _loadGameConfig(const std::string& a_configPath);
	virtual bool _initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void _cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void _cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);
	
	typedef CMasterSystemSP* CMasterSystemSP_ptr_t;
	void handle(shared_ptr_t<accountforbid_req_t> a_req_,  BSLib::uint32 a_id);
	void handle(shared_ptr_t<accountpwd_req_t> a_req_,  BSLib::uint32 a_id);
	void handle(shared_ptr_t<itemdeduct_req_t> a_req_, BSLib::uint32 a_id);
	void handle(shared_ptr_t<mail_req_t> a_req_,  BSLib::uint32 a_id);
	void handle(shared_ptr_t<broadcast_req_t> a_req_,  BSLib::uint32 a_id);

private:
	static int	_run(void* obj);
	void	onCommand();	
	
	void onRequest(BSLib::uint32 a_id, DB::Commandst& a_cmd);
	void onReply(BSLib::uint32 a_id, BSLib::uint32 a_result, std::string  a_info);
	void sendMsgToCN(BSLib::uint32 a_id, std::string& a_zone, GFLib::CMessage& a_msg);

	bool getServerKey(std::string a_serverID, std::string& a_serverKey);
	
	void Test();
	std::map<BSLib::uint32, DB::Commandst> m_cmds;
	std::map<GFLib::ServerID, std::string> m_cnServers;
	BSLib::Utility::CMutex  m_mutex;
	std::vector<Replyst> m_replies;
	BSLib::Database::CDbConnection m_con;
	std::string m_cmddb;
private:
	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXX2XSReqAccountSearch);
	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXS2XXAckAccountSearch);

	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXX2XSReqRoleInfo);
	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXS2XXAckRoleInfo);

	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXX2XSReqAccountPwd);
	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXS2XXAckAccountPwd);

	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXX2XSReqAccountForbid);
	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXS2XXAckAccountForbid);

	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXX2XSReqMail);
	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXS2XXAckMail);

	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXX2XSReqRoleItemDeduct);
	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXS2XXAckRoleItemDeduct);

	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXX2XSReqBroadcast);
	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXS2XXAckBroadcast);
};

}

}

}//GSLib

#endif
