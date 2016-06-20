//////////////////////////////////////////////////////////////////////
//	created:	2014/10/09
//	filename: 	src\GSLib\mailSystem\GM\mailSystemGM.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/mailSystem/CN/mailSystemCN.h>
#include <BSLib/utility/dateTime.h>
#include <GSLib/funType.h>
#include <GSLib/serverType.h>
#include <sstream>
#include <time.h>
#include <GSLib/mailSystem/GM/msgMailSystemGM.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <GSLib/mailSystem/msgMailSystem.h>
#include <GFLib/commonServer/commonServer.h>
#include <GSLib/playerSystem/CN/playerCN.h>
#include <GSLib/playerSystem/CN/playerCNMgr.h>
#include <GSLib/playerSystem/CN/roleModuleCNMgr.h>
#include <GSLib/mailSystem/CN/roleMailModuleCN.h>

namespace GSLib
{

namespace MailSystem
{

namespace CN
{

BSLIB_SINGLETON_DEFINE(CMailSystemCN);

CMailSystemCN::CMailSystemCN()
{	
	m_mailIdBase = _currentTime();
	m_mailIdSeed = 0;
	m_serverNO = 0;

	GFLib::CommonServer::CCommonServer* server = GFLib::CommonServer::CCommonServer::getCommonServer();
	if (server != NULL){
		m_serverNO = server->getServerID().m_number;
		//m_uniqueMailer.m_zoneId = server->getServerID().getZoneID();
	}

	m_gmReady = false;
	m_dataReady = false;

}

CMailSystemCN::~CMailSystemCN()
{
	;
}

void CMailSystemCN::update(BSLib::uint64 a_delayMilliseconds)
{
	;
}

bool CMailSystemCN::_init()
{
	GSLib::PlayerSystem::CN::CRoleModuleCNMgr::singleton().addCreateRoleModuleFun(EMODULECTYPE_MAIL,
		GSLib::PlayerSystem::CN::createRoleModuleFun<CRoleMailModuleCN>);

	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CMailSystemCN::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CMailSystemCN::_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CMailSystemCN::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{	
	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}


bool CMailSystemCN::_cbTimerSendSystemMailTest(BSLib::uint64, void* a_para)
{	
	// 测试系统
	if(m_dataReady && m_gmReady){

#ifdef BIANJIANTEST

		std::vector<SRoleGuid> receivers;
		//receivers.push_back(SRoleGuid(10000010, 23, 0));
		std::stringstream title;
		title << "title ";
		title << _currentTime();
		std::string title1 = title.str();
		title1 += " with bonus";
		std::vector<BSLib::uint32> ids;
		std::vector<BSLib::uint32> nums;
		ids.push_back(100200001);
		ids.push_back(100100001);
		ids.push_back(100110001);
		nums.push_back(10);
		nums.push_back(10);
		nums.push_back(10);
		mailSend("GM", receivers, EMailTypeSystem, title1, std::string("content"),
			std::vector<BSLib::uint32>(4, 3), ids, nums);

		std::string title2 = title.str();
		title2 += " no bonus";
		mailSend("GM", receivers, EMailTypeSystem, title2, std::string("content"), 
			std::vector<BSLib::uint32>(), std::vector<BSLib::uint32>(), std::vector<BSLib::uint32>());
#endif

	}

	return true;
}

bool CMailSystemCN::_startSystem()
{	

#ifdef  BIANJIANTEST1
	BSLib::Utility::CTimerServer* timeServer = _getTimerServer();
	timeServer->addTimer(&CMailSystemCN::_cbTimerSendSystemMailTest, this, BSLib::uint64(0), NULL,  5000, 10 * 1000);
#endif

	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CMailSystemCN::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{	

#ifdef  BIANJIANTEST
	if(a_serverID.m_type == SRVTYPE_DATASERVER){
		m_dataReady = true;
	}

	if( a_serverID.m_type == SRVTYPE_GAMESERVER){
		m_gmReady = true;
	}
#endif

	return GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CMailSystemCN::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{	

#ifdef  BIANJIANTEST
	if(a_serverID.m_type == SRVTYPE_DATASERVER){
		m_dataReady = false;
	}

	if( a_serverID.m_type == SRVTYPE_GAMESERVER){
		m_gmReady = false;
	}
#endif

	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}


TMailContainerMap * CMailSystemCN::mailOpenBox(SRoleGuid &a_mailer)
{	
	TRoleMailContainerMap::iterator it = m_outputBox.find(a_mailer);
	if( it == m_outputBox.end())
		return NULL;

	return it->second;
}

SMail* CMailSystemCN::mailOpen(SRoleGuid &a_mailer, BSLib::uint64 a_mailId)
{
	TRoleMailContainerMap::iterator it = m_outputBox.find(a_mailer);
	if( it == m_outputBox.end())
		return NULL;

	TMailContainerMap* container =  it->second;
	TMailContainerMap::iterator mail_it = container->find(a_mailId);
	if( mail_it == container->end())
		return NULL;

	return mail_it->second;
}

bool CMailSystemCN::mailDelete(SRoleGuid &a_mailer, BSLib::uint64 a_mailId)
{
	TRoleMailContainerMap::iterator it = m_outputBox.find(a_mailer);
	if( it == m_outputBox.end())
		return false;

	TMailContainerMap* container =  it->second;
	TMailContainerMap::iterator mail_it = container->find(a_mailId);
	if( mail_it == container->end())
		return false;
	
	SMail *mailObj = mail_it->second;
	_dbDelRoleMail(mailObj);
	delete mailObj;
	container->erase(mail_it);
	return true;
}

bool CMailSystemCN::_notifySystemNewMail(SMail *a_obj)
{	
	CMsgMailSystemCN2GMNtfNewSystemMail ack;
	a_obj->serializeTo(ack.m_MailStream);

	return GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServerType(SRVTYPE_GAMESERVER, ack);
}

bool CMailSystemCN::_notifyRoleNewMail(SRoleGuid &a_receiver, SMail *a_obj)
{	
	using namespace GSLib::PlayerSystem::CN;
	CPlayerCN *player = CPlayerCNMgr::singleton().getPlayerCN(GFLib::SAccountKey(a_receiver.m_accountId, a_receiver.m_zoneId));
	if(NULL == player)
		return false;

	if(player->getCurRoleIndex() != (int)a_receiver.m_roleIndex)
		return false;
	
	CRoleCN * role = player->getCurRole();
	CRoleMailModuleCN* mailModule = (CRoleMailModuleCN*)role->getPlayerModuleCN(EMODULECTYPE_MAIL);
	return mailModule->cbNewRoleMail(a_obj);
}


bool CMailSystemCN::mailSend(const std::string& a_sender, std::vector<SRoleGuid> &a_receiver, EMailType a_mailType, std::string &a_title,
							 std::string &a_content, std::vector<BSLib::uint32> &a_types, std::vector<BSLib::uint32> &a_ids, std::vector<BSLib::uint32> &a_nums)
{	
	// 个人邮件
	BSLib::uint64 cur_time = _currentTime();
	if( 0 != a_receiver.size())
	{
		for(BSLib::uint32 i = 0; i < a_receiver.size(); i++)
		{	
			SelfMailst st(a_receiver[i], a_mailType, 0, cur_time, a_title, a_content, a_sender, a_types, a_ids, a_nums);
			SMail *self_mail = _createSelfMail(st, true);
			_notifyRoleNewMail(a_receiver[i], self_mail);
				
		}

		return true;
	}

	// 全体
	if( 0 == a_receiver.size() && EMailTypeSystem == a_mailType)
	{
		SMail *systemMail = _createUniqueMail(a_title, a_content, a_sender, cur_time, a_types, a_ids, a_nums);
		_notifySystemNewMail(systemMail);

		return true;
	}
	

	return false;
}



SRoleGuid CMailSystemCN::getUniqueRoleGuid()
{
	return m_uniqueMailer;
}

bool CMailSystemCN::mailGetSelf(SRoleGuid& a_mailer, TMailContainerMap& a_container)
{
	TRoleMailContainerMap::iterator it = m_outputBox.find(a_mailer);
	if( it == m_outputBox.end())
		return false;
	
	TMailContainerMap *self_container = it->second;
	if(self_container->empty())
		return false;
	
	a_container = *self_container;
	return true;
}

BSLib::uint64 CMailSystemCN::_newMailId()
{	
	if(m_mailIdSeed < 0xfffff)
	{
		m_mailIdSeed++;
	}
	else
	{	
		m_mailIdBase = _currentTime();	
		m_mailIdSeed = 1;
	}
	
	BSLib::uint64 mail_id_index = CREATE_NEW_MAILID(SRVTYPE_CENTERSERVER, m_serverNO, m_mailIdBase, m_mailIdSeed);

	return mail_id_index;
}

BSLib::uint64 CMailSystemCN::_currentTime()
{	
	//BSLib::Utility::CRealTime time;
	//return time.seconds();
	time_t tt;
	time(&tt);
	return tt;
}

SMail* CMailSystemCN::_createSelfMail(SelfMailst& a_st, bool a_save)

{
	SMail *obj = new SMail(a_st.m_receiver);
	obj->m_mailId = _newMailId();
	obj->m_mailType = a_st.m_mailType;
	obj->m_timeStamp = a_st.m_timeStamp;
	
	// 非全体邮件
	if(0 == a_st.m_uniqueMail)
	{
		obj->m_title = a_st.m_title;
		obj->m_content = a_st.m_content;
		obj->m_sender = a_st.m_sender;
		obj->m_types = a_st.m_types;
		obj->m_ids = a_st.m_ids;
		obj->m_nums = a_st.m_nums;
	}
	else
	{
		obj->m_systemMail = a_st.m_uniqueMail;
	}
	
	if(a_save)
	{
		TMailContainerMap* container = mailOpenBox(a_st.m_receiver);
		if( NULL == container)
		{
			container = new TMailContainerMap;
			m_outputBox.insert(std::make_pair(a_st.m_receiver, container));
		}
		container->insert(std::make_pair(obj->m_mailId, obj));

		_dbUpdateRoleMail(obj);
	}

	return obj;
}

SMail* CMailSystemCN::_createUniqueMail(const std::string& a_title, const std::string& a_content, const std::string& a_sender, BSLib::uint64 a_timeStamp,
										std::vector<BSLib::uint32> &a_types, std::vector<BSLib::uint32>& a_ids, std::vector<BSLib::uint32>& a_nums)
{
	SMail  *obj = new SMail(m_uniqueMailer);
	obj->m_mailId = _newMailId();
	obj->m_mailType = EMailTypeSystem;
	obj->m_title = a_title;
	obj->m_content = a_content;
	obj->m_sender = a_sender;
	obj->m_timeStamp = a_timeStamp;
	obj->m_types = a_types;
	obj->m_ids = a_ids;
	obj->m_nums = a_nums;

	TMailContainerMap* container = mailOpenBox(m_uniqueMailer);
	if( NULL == container)
	{
		container = new TMailContainerMap;
		m_outputBox.insert(std::make_pair(m_uniqueMailer, container));
	}
	container->insert(std::make_pair(obj->m_mailId, obj));

	_dbUpdateRoleMail(obj);
	
	return obj;
}

bool CMailSystemCN::_cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyTablePtr& a_keyTable,
										  EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{

	return true;
}

bool CMailSystemCN::_cbSelectKeyIndexTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable,
											   EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{	
	// 只加载, 不保存
	if(EDBTABLEID_MAIL_OUTPUT_DATA == a_tableID){
		a_keyTable->traversal(*this);
		m_outputTablePtr = a_keyTable;
	}

	// 测试系统
#ifdef BIANJIANTEST1
	for(int i = 0; i < 20; i++)
	{	
		std::stringstream title;
		title << "title ";
		title << i;
		std::string title1 = title.str();
		title1 += " with bonus";
		mailSend("GM", std::vector<SRoleGuid>(), EMailTypeSystem, title1, std::string("content"), 
			std::vector<BSLib::uint32>(4, 3), std::vector<BSLib::uint32>(4, 3), std::vector<BSLib::uint32>(4, 3));

		std::string title2 = title.str();
		title2 += " no bonus";
		mailSend("GM", std::vector<SRoleGuid>(), EMailTypeSystem, title2, std::string("content"),
			std::vector<BSLib::uint32>(), std::vector<BSLib::uint32>(), std::vector<BSLib::uint32>());
	}
#endif

	return true;
}

bool CMailSystemCN::exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value)
{	
	BSLib::Utility::CStream stream;
	a_value->serializeTo(stream);
	SMail *systemMail = new SMail;
	systemMail->serializeFrom(stream);

	SRoleGuid roleGuid(systemMail->m_accountId, systemMail->m_zoneId, systemMail->m_roleIndex);
	TMailContainerMap * systemMailCon = NULL;
	TRoleMailContainerMap::iterator it = m_outputBox.find(roleGuid);
	if( it == m_outputBox.end()){
		systemMailCon = new TMailContainerMap;
		m_outputBox.insert(make_pair(roleGuid, systemMailCon));
	}
	else{
		systemMailCon = it->second;
	}

	systemMailCon->insert(std::make_pair(systemMail->m_mailId, systemMail));
	return true;
}

void CMailSystemCN::_dbUpdateRoleMail(SMail *mail)
{
	BSLib::Utility::CStream db_stream;
	mail->serializeTo(db_stream);
	if(m_outputTablePtr == NULL)
		return;
	m_outputTablePtr->update(mail->getDBKey(), mail->getIndexKey(), db_stream);
	m_outputTablePtr->saveDataToDBServer(mail->getDBKey(), mail->getIndexKey(), true);
}

void CMailSystemCN::_dbDelRoleMail(SMail *mail)
{
	BSLib::Utility::CStream db_stream;
	mail->serializeTo(db_stream);
	if(m_outputTablePtr == NULL)
		return;
	m_outputTablePtr->remove(mail->getDBKey(), mail->getIndexKey());
	m_outputTablePtr->saveDataToDBServer(mail->getDBKey(), mail->getIndexKey(), true);
}


}//GM

}//MailSystem

}//GSLib
