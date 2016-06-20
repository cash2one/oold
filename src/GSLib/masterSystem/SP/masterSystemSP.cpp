#include <GSLib/masterSystem/SP/masterSystemSP.h>
#include <BSLib/utility/dateTime.h>
#include <GSLib/funType.h>
#include <GSLib/serverType.h>
#include <sstream>
#include <time.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <GSLib/masterSystem/msgMasterSystem.h>
#include <GFLib/commonServer/commonServer.h>
#include <GFLib/commonServer/stubMgr.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <BSLib/utility/thread/thread.h>
#include <BSLib/database/dbConnection.h>
#include <GSLib/tracer.h>
#include <GFLib/commonServer/commonServer.h>
#include <BSLib/utility/convert.h>

namespace GSLib
{

namespace MasterSystem
{

namespace SP
{

BSLIB_SINGLETON_DEFINE(CMasterSystemSP);

CMasterSystemSP::CMasterSystemSP()
{	

}

CMasterSystemSP::~CMasterSystemSP()
{
	;
}

void CMasterSystemSP::update(BSLib::uint64 a_delayMilliseconds)
{
	;
}

bool CMasterSystemSP::_init()
{	
	BSLib::Utility::CHndThread t = BSLib::Utility::CHndThread::createThread(&CMasterSystemSP::_run, this);
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CMasterSystemSP::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CMasterSystemSP::_loadGameConfig(const std::string& a_configPath)
{	
	// 加载 command db path ini
	GFLib::CommonServer::CCommonServer* srv = GFLib::CommonServer::CCommonServer::getCommonServer();
	std::string srvName = srv->getServerTypeName();
	m_cmddb = BSLib::Framework::CSysConfig::singleton().getValueStr(srvName, "CmdMysqlPath");
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CMasterSystemSP::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{	
	GSLIB_MSGFUN_REG(CMsgMasterSystemXX2XSReqAccountSearch, CMasterSystemSP);
	GSLIB_MSGFUN_REG(CMsgMasterSystemXS2XXAckAccountSearch, CMasterSystemSP);

	GSLIB_MSGFUN_REG(CMsgMasterSystemXX2XSReqRoleInfo, CMasterSystemSP);
	GSLIB_MSGFUN_REG(CMsgMasterSystemXS2XXAckRoleInfo, CMasterSystemSP);

	GSLIB_MSGFUN_REG(CMsgMasterSystemXX2XSReqAccountPwd, CMasterSystemSP);
	GSLIB_MSGFUN_REG(CMsgMasterSystemXS2XXAckAccountPwd, CMasterSystemSP);

	GSLIB_MSGFUN_REG(CMsgMasterSystemXX2XSReqAccountForbid, CMasterSystemSP);
	GSLIB_MSGFUN_REG(CMsgMasterSystemXS2XXAckAccountForbid, CMasterSystemSP);

	GSLIB_MSGFUN_REG(CMsgMasterSystemXX2XSReqMail, CMasterSystemSP);
	GSLIB_MSGFUN_REG(CMsgMasterSystemXS2XXAckMail, CMasterSystemSP);

	GSLIB_MSGFUN_REG(CMsgMasterSystemXX2XSReqRoleItemDeduct, CMasterSystemSP);
	GSLIB_MSGFUN_REG(CMsgMasterSystemXS2XXAckRoleItemDeduct, CMasterSystemSP);

	GSLIB_MSGFUN_REG(CMsgMasterSystemXX2XSReqBroadcast, CMasterSystemSP);
	GSLIB_MSGFUN_REG(CMsgMasterSystemXS2XXAckBroadcast, CMasterSystemSP);

	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}


bool CMasterSystemSP::_startSystem()
{	
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CMasterSystemSP::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{	
	if(a_serverID.m_type == GSLib::SRVTYPE_CENTERSERVER)
	{
		m_cnServers.insert(std::make_pair(a_serverID.getZoneID(), a_key));
	}

	return GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

int CMasterSystemSP::_run(void* obj)
{	
	CMasterSystemSP *p = (CMasterSystemSP *)obj;
	BSLib::Utility::CThread::sleep(10);
	p->onCommand();
	return 0;
}


void CMasterSystemSP::handle(shared_ptr_t<accountforbid_req_t> a_req_, BSLib::uint32 a_id)
{
	CMsgMasterSystemXX2XSReqAccountForbid r;
	r.stubId = a_id;
	//r.zone = a_req_->zone;
	getServerKey(a_req_->zone, r.zone);
	r.accountName = a_req_->accountname;
	r.setState = a_req_->setstate;

	sendMsgToCN(a_id,a_req_->zone, r);
}

void CMasterSystemSP::handle(shared_ptr_t<accountpwd_req_t> a_req_, BSLib::uint32 a_id)
{
	CMsgMasterSystemXX2XSReqAccountPwd pwd;
	pwd.stubId = a_id;
	//pwd.zone = a_req_->zone;
	getServerKey(a_req_->zone, pwd.zone);
	pwd.accountName = a_req_->accountname;
	pwd.pwd = a_req_->pwd;

	sendMsgToCN(a_id, a_req_->zone, pwd);
}

void CMasterSystemSP::handle(shared_ptr_t<itemdeduct_req_t> a_req_, BSLib::uint32 a_id)
{
	CMsgMasterSystemXX2XSReqRoleItemDeduct r;
	r.stubId = a_id;
	//r.zone = a_req_->zone;
	getServerKey(a_req_->zone, r.zone);
	r.name = a_req_->name;
	r.itemId = a_req_->itemid;
	r.itemNum = a_req_->itemnum;
	sendMsgToCN(a_id,a_req_->zone, r);

}

void CMasterSystemSP::handle(shared_ptr_t<mail_req_t> a_req_, BSLib::uint32 a_id)
{
	CMsgMasterSystemXX2XSReqMail r;
	r.stubId = a_id;
	//r.zone = a_req_->zone;
	getServerKey(a_req_->zone, r.zone);
	r.type = a_req_->type;
	r.sender = a_req_->sender;
	r.roles = a_req_->roles;
	r.title = a_req_->title;
	r.content = a_req_->content;
	r.itemIds = a_req_->itemids;
	r.itemNums = a_req_->itemnums;
	sendMsgToCN(a_id,a_req_->zone, r);
}

void CMasterSystemSP::handle(shared_ptr_t<broadcast_req_t> a_req_, BSLib::uint32 a_id)
{
	CMsgMasterSystemXX2XSReqBroadcast r;
	r.stubId = a_id;
	//r.zone = a_req_->zone;
	getServerKey(a_req_->zone, r.zone);
	r.content = a_req_->content;
	sendMsgToCN(a_id,a_req_->zone, r);
}

void CMasterSystemSP::onRequest(BSLib::uint32 a_id, DB::Commandst& a_cmd)
{
	m_cmds.insert(std::make_pair(a_id, a_cmd));
}

void CMasterSystemSP::onReply(BSLib::uint32 a_id, BSLib::uint32 a_result, std::string  a_info)
{
	BSLib::Utility::CMutexFun f(&m_mutex);
	Replyst reply;
	reply.m_id =a_id;
	reply.m_result = a_result;
	reply.m_info = a_info;
	m_replies.push_back(reply);
}

bool CMasterSystemSP::getServerKey(std::string a_serverID, std::string& a_serverKey)
{
	GFLib::ServerID serverID = BSLib::Utility::CConvert::toUint32(a_serverID);
	std::map<GFLib::ServerID, std::string>::iterator it = m_cnServers.find(serverID);
	if(it == m_cnServers.end())
		return false;

	a_serverKey = it->second;
	return true;
}

void CMasterSystemSP::sendMsgToCN(BSLib::uint32 a_id, std::string& a_zone, GFLib::CMessage& a_msg)
{	
	GFLib::ServerID serverID = BSLib::Utility::CConvert::toUint32(a_zone);
	std::map<GFLib::ServerID, std::string>::iterator it = m_cnServers.find(serverID);
	if(it == m_cnServers.end())
	{	
		onReply(a_id, REPLY_FAILED, "zone offline");
		return;
	}

	using namespace GFLib::CommonServer;
	CServiceMgr::singleton().sendMsgToServer(it->second, a_msg);
}

void CMasterSystemSP::Test()
{
	// 测试
	DB::Commandst st;
	{	
		accountpwd_req_t req;
		req.zone = "23";
		req.accountname = "test_1";
		req.pwd = "1";
		st.m_id = 1;
		st.m_request = req.encode_json();
		BSLib::Utility::CStream inf;
		st.serializeTo(inf);
		m_con.executeInsert(std::string("Command"), DB::g_commandDataColumn, inf);
	}

	{	
		accountforbid_req_t req;
		req.zone = "23";
		req.accountname = "test_1";
		req.setstate = 1;

		st.m_id = 2;
		st.m_request = req.encode_json();
		BSLib::Utility::CStream inf;
		st.serializeTo(inf);
		m_con.executeInsert(std::string("Command"), DB::g_commandDataColumn, inf);
	}

	{	
		itemdeduct_req_t req;
		req.zone = "23";
		req.name = "test_1";
		req.itemid = 1;
		req.itemnum = 1;

		st.m_id = 3;
		st.m_request = req.encode_json();
		BSLib::Utility::CStream inf;
		st.serializeTo(inf);
		m_con.executeInsert(std::string("Command"), DB::g_commandDataColumn, inf);
	}

	{	
		mail_req_t req;
		req.zone = "23";
		req.type = 2;
		req.sender = "admin";
		req.title = "all type 2";
		req.content = "all";

		st.m_id = 4;
		st.m_request = req.encode_json();
		BSLib::Utility::CStream inf;
		st.serializeTo(inf);
		m_con.executeInsert(std::string("Command"), DB::g_commandDataColumn, inf);
	}

	{	
		broadcast_req_t req;
		req.zone = "23";
		req.content = "content";
		st.m_id = 5;
		st.m_request = req.encode_json();
		BSLib::Utility::CStream inf;
		st.serializeTo(inf);
		m_con.executeInsert(std::string("Command"), DB::g_commandDataColumn, inf);
	}

	{	
		broadcast_req_t req;
		req.zone = "23";
		req.content = "content";
		st.m_id = 6;
		st.m_request = req.encode_json();
		st.m_request += "fdfd";
		BSLib::Utility::CStream inf;
		st.serializeTo(inf);
		m_con.executeInsert(std::string("Command"), DB::g_commandDataColumn, inf);
	}

	{	
		broadcast_req_t req;
		req.zone = "24";
		req.content = "content";
		st.m_id = 7;
		st.m_request = req.encode_json();
		BSLib::Utility::CStream inf;
		st.serializeTo(inf);
		m_con.executeInsert(std::string("Command"), DB::g_commandDataColumn, inf);
	}

	{	
		mail_req_t req;
		req.zone = "23";
		req.type = 1;
		req.sender = "admin";
		req.title = "one type 1";
		req.content = "one";

		req.roles.push_back("test_1");
		st.m_id = 8;
		st.m_request = req.encode_json();
		BSLib::Utility::CStream inf;
		st.serializeTo(inf);
		m_con.executeInsert(std::string("Command"), DB::g_commandDataColumn, inf);
	}
}

void CMasterSystemSP::onCommand()
{
	if( !m_con.connect(m_cmddb, false))
	{
		BSLIB_LOG_ERROR(ETT_GSLIB_MASTERSYSTEM, "连接GM指令db失败[%s]", m_cmddb.c_str());
		return;
	}
	
	// 测试
	#ifdef BIANJIANTEST1
		Test();
	#endif
	

	while(true)
	{
		BSLib::Utility::CStream outbuf;
		int result = m_con.executeSelect(std::string("Command"), std::string("ReadFlag = 0"), std::string("Id ASC"), DB::g_commandDataColumn, outbuf);
		for(int i = 0; i < result; i++)
		{	
			DB::Commandst cmd;
			cmd.serializeFrom(outbuf);

			// 设置已读标志
			cmd.m_readFlag = 1;
			BSLib::Utility::CStream inBuf;
			cmd.serializeTo(inBuf);
			m_con.executeReplace(std::string("Command"), DB::g_commandDataColumn, inBuf);

			// 解析指令
			try
			{	
				msg_dispather_t<CMasterSystemSP, BSLib::uint32> msg_dispather(*this);
				onRequest(cmd.m_id, cmd);
				msg_dispather.dispath(cmd.m_request, cmd.m_id);
			}
			catch(exception& e)
			{
				BSLIB_LOG_ERROR(ETT_GSLIB_MASTERSYSTEM, "解析GM指令失败[%s]", e.what());
				onReply(cmd.m_id, REPLY_FAILED, std::string("failed to parse command"));
			}

		}
		
		std::vector<Replyst> replies;
		{
			BSLib::Utility::CMutexFun f(&m_mutex);
			m_replies.swap(replies);
		}
		
		for(std::vector<Replyst>::iterator it = replies.begin(); it != replies.end(); ++it)
		{
			command_ret_t ret;
			ret.result = it->m_result;
			ret.info = it->m_info;
			
			std::map<BSLib::uint32, DB::Commandst>::iterator cmdIt = m_cmds.find(it->m_id);
			if(cmdIt == m_cmds.end())
				continue;
			
			cmdIt->second.m_reply = ret.encode_json();
			cmdIt->second.m_returnFlag = 1;
			BSLib::Utility::CStream reply;
			cmdIt->second.serializeTo(reply);
			m_cmds.erase(cmdIt);
			m_con.executeReplace(std::string("Command"), DB::g_commandDataColumn, reply);
		}

		BSLib::Utility::CThread::msleep(1000);
	}
}

void CMasterSystemSP::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{	
	if(a_serverID.m_type == GSLib::SRVTYPE_CENTERSERVER)
	{	
		std::map<GFLib::ServerID,std::string>::iterator it = m_cnServers.find(a_serverID.getZoneID());
		if(it != m_cnServers.end())
			m_cnServers.erase(it);
	}

	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}

GSLIB_FORWARD_MSGFUN_DEFINE(CMsgMasterSystemXX2XSReqRoleInfo, CMasterSystemSP)
GSLIB_BACKWARD_MSGFUN_DEFINE(CMsgMasterSystemXS2XXAckRoleInfo, CMasterSystemSP)

GSLIB_FORWARD_MSGFUN_DEFINE(CMsgMasterSystemXX2XSReqAccountSearch, CMasterSystemSP)
GSLIB_BACKWARD_MSGFUN_DEFINE(CMsgMasterSystemXS2XXAckAccountSearch, CMasterSystemSP)

GSLIB_FORWARD_MSGFUN_DEFINE(CMsgMasterSystemXX2XSReqAccountPwd, CMasterSystemSP)
GSLIB_BACKWARD_MSGFUN_DEFINE(CMsgMasterSystemXS2XXAckAccountPwd, CMasterSystemSP)

GSLIB_FORWARD_MSGFUN_DEFINE(CMsgMasterSystemXX2XSReqAccountForbid, CMasterSystemSP)
void  CMasterSystemSP::_onCMsgMasterSystemXS2XXAckAccountForbid(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{ 
	CMsgMasterSystemXS2XXAckAccountForbid *ack = (CMsgMasterSystemXS2XXAckAccountForbid *)a_msg;
	onReply(ack->stubId, 0, "");
}	


GSLIB_FORWARD_MSGFUN_DEFINE(CMsgMasterSystemXX2XSReqMail, CMasterSystemSP)
GSLIB_BACKWARD_MSGFUN_DEFINE(CMsgMasterSystemXS2XXAckMail, CMasterSystemSP)

GSLIB_FORWARD_MSGFUN_DEFINE(CMsgMasterSystemXX2XSReqRoleItemDeduct, CMasterSystemSP)
GSLIB_BACKWARD_MSGFUN_DEFINE(CMsgMasterSystemXS2XXAckRoleItemDeduct, CMasterSystemSP)

GSLIB_FORWARD_MSGFUN_DEFINE(CMsgMasterSystemXX2XSReqBroadcast, CMasterSystemSP)
GSLIB_BACKWARD_MSGFUN_DEFINE(CMsgMasterSystemXS2XXAckBroadcast, CMasterSystemSP)


}//GM

}

}//GSLib
