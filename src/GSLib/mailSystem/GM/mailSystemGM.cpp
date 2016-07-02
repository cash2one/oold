#include <GSLib/playerSystem/GM/roleModuleGMMgr.h>
#include <GSLib/mailSystem/GM/mailSystemGM.h>
#include <GSLib/mailSystem/GM/roleMailModule.h>
#include <GSLib/playerSystem/GM/playerGMMgr.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <BSLib/utility/dateTime.h>
#include <sstream>
#include <time.h>
#include <GSLib/mailSystem/msgMailSystem.h>
#include <GFLib/commonServer/commonServer.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>

namespace GSLib
{

namespace MailSystem
{

namespace GM
{

BSLIB_SINGLETON_DEFINE(CMailSystemGM);

CMailSystemGM::CMailSystemGM()
{	
	m_mailIdBase = _currentTime();
	m_mailIdSeed = 0;
	m_lastestSystemMailId = 0;
	m_serverNO = 0;

	GFLib::CommonServer::ICommonServer* server = GFLib::CommonServer::ICommonServer::getCommonServer();
	if (server != NULL){
		m_serverNO = server->getServerID().m_number;
		//m_uniqueMailer.m_zoneId = server->getServerID().getZoneID();
	}
	
}

CMailSystemGM::~CMailSystemGM()
{
	;
}

void CMailSystemGM::update(BSLib::uint64 a_delayMilliseconds)
{
}

bool CMailSystemGM::_init()
{
	GSLib::PlayerSystem::GM::CRoleModuleGMMgr::singleton().addCreateRoleModuleFun(EMODULECTYPE_MAIL, GSLib::PlayerSystem::GM::createRoleModuleFun<CRoleMailModule>);

	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CMailSystemGM::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CMailSystemGM::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_loadGameConfig(a_configPath);
}

bool CMailSystemGM::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{	
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDMailSystemCN2GMNtfNewSystemMail, 
		&BSLib::Framework::CreateCMessage<CMsgMailSystemCN2GMNtfNewSystemMail>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDMailSystemCN2GMNtfNewSystemMail, &CMailSystemGM::_onMsgMailSystemCN2GMNtfNewSystemMail, this);

	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_initServerMsg(a_msgExecMgr);
}

void CMailSystemGM::_onMsgMailSystemCN2GMNtfNewSystemMail(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgMailSystemCN2GMNtfNewSystemMail *systemMail = (CMsgMailSystemCN2GMNtfNewSystemMail *)a_msg;
	
	SMail *newMail = new SMail;
	newMail->serializeFrom(systemMail->m_MailStream);
	TMailContainerMap* systemcontainer = mailOpenBox(m_uniqueMailer);
	if(NULL == systemcontainer)
	{
		systemcontainer = new TMailContainerMap;
		m_systemOutputBox.insert(std::make_pair(m_uniqueMailer, systemcontainer));
	}
	
	TMailContainerMap::iterator it = systemcontainer->find(newMail->m_mailId);
	if( it != systemcontainer->end()){
		delete newMail;
		BSLIB_LOG_ERROR(ETT_GSLIB_MAILSYSTEM, "duplicate system maiil id:%llu", newMail->m_mailId);
		return;
	}

	systemcontainer->insert(std::make_pair(newMail->m_mailId, newMail));
	m_lastestSystemMailId = newMail->m_mailId;
	std::vector<SRoleGuid>& roleGuids = _getOnlineRoles();
	for(BSLib::uint32 i = 0; i < roleGuids.size(); i++)
	{	
		SelfMailst st(roleGuids[i], EMailTypeSystem, newMail->m_mailId, newMail->m_timeStamp);
		SMail *self_mail = _createSelfMail(st);
		if(!_notifyRoleNewMail(roleGuids[i], self_mail)){
			delete self_mail; // 未发送成功则删除
		}


	}
}


bool CMailSystemGM::_cbTimerSendSystemMailTest(BSLib::uint64, void* a_para)
{
	SRoleGuid role(10000000, 23, 0);
	std::vector<SRoleGuid> con;
	con.push_back(role);
	for(int i = 0; i < 1; i++)
	{
		std::vector<BSLib::uint32> types = std::vector<BSLib::uint32>(3, 3);
		std::vector<BSLib::uint32> ids = std::vector<BSLib::uint32>(3, 3);
		std::vector<BSLib::uint32> nums = std::vector<BSLib::uint32>(3, 3);
		mailSend("test", con, "title", "content", types, ids, nums);
	}

	return true;
}


bool CMailSystemGM::_ICommonSystem_startSystem()
{	

#ifdef  BIANJIANTEST1
	BSLib::Utility::CTimerServer* timeServer = _getTimerServer();
	timeServer->addTimer(&CMailSystemGM::_cbTimerSendSystemMailTest, this, BSLib::uint64(0), NULL,  5000, 20 * 1000);
#endif


	return GSLib::DBSystem::CDBCommonSystem::_ICommonSystem_startSystem();
}

void CMailSystemGM::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GFLib::CommonServer::ICommonSystem::ICommonSystem_cbServerEnter(a_serverID, a_key);
}

void CMailSystemGM::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GFLib::CommonServer::ICommonSystem::ICommonSystem_cbServerLeave(a_serverID, a_key);
}


TMailContainerMap * CMailSystemGM::mailOpenBox(SRoleGuid &a_mailer)
{	
	TRoleMailContainerMap::iterator it = m_systemOutputBox.find(a_mailer);
	if( it == m_systemOutputBox.end())
		return NULL;

	return it->second;
}

SMail* CMailSystemGM::mailOpen(SRoleGuid &a_mailer, BSLib::uint64 a_mailId)
{
	TRoleMailContainerMap::iterator it = m_systemOutputBox.find(a_mailer);
	if( it == m_systemOutputBox.end())
		return NULL;

	TMailContainerMap* container =  it->second;
	TMailContainerMap::iterator mail_it = container->find(a_mailId);
	if( mail_it == container->end())
		return NULL;

	return mail_it->second;
}

bool CMailSystemGM::_notifyRoleNewMail(SRoleGuid &a_receiver, SMail *a_obj)
{		
	using namespace GSLib::PlayerSystem::GM;
	CPlayerGM* player = CPlayerGMMgr::singleton().getPlayerGM(GFLib::SAccountKey(a_receiver.m_accountId, a_receiver.m_zoneId));
	if( NULL == player)
		return false;

	if( a_receiver.m_roleIndex != (BSLib::uint32)player->getCurRoleIndex())
		return false;
	
	CRoleGM* role = player->getCurRole();
	CRoleMailModule* mail_module =  (CRoleMailModule*)role->getPlayerModuleGM(EMODULECTYPE_MAIL);
	return mail_module->cbNewMailNotify(a_obj);
}

bool CMailSystemGM::mailSend(const std::string& a_sender, std::vector<SRoleGuid> &a_receiver, const std::string &a_title, const std::string &a_content,
							 std::vector<BSLib::uint32> &a_types, std::vector<BSLib::uint32> &a_ids, std::vector<BSLib::uint32> &a_nums)
{	
	// 发送给个人的系统邮件..
	BSLib::uint64 cur_time = _currentTime();
	for(BSLib::uint32 i = 0; i < a_receiver.size(); i++)
	{	
		SelfMailst st(a_receiver[i], EMailTypeSelf, 0, cur_time, a_title, a_content, a_sender, a_types, a_ids, a_nums);
		SMail *self_mail = _createSelfMail(st);
		if(!_notifyRoleNewMail(a_receiver[i], self_mail)){
			delete self_mail; // 未发送成功则删除
		}
	}

	return true;
}

std::vector<SRoleGuid>& CMailSystemGM::_getOnlineRoles()
{	
	m_totaoRoles.clear();

	using namespace GSLib::PlayerSystem::GM;
	typedef std::list<CRoleGM*> RoleList;
	RoleList roles;
	CPlayerGMMgr::singleton().getActiveRolesGM(roles);
	for(RoleList::iterator it = roles.begin(); it != roles.end(); ++it)
	{	
		CRoleGM * role = *it;
		if(NULL == role)
			continue;

		CRoleMailModule* mail_module =  (CRoleMailModule*)role->getPlayerModuleGM(EMODULECTYPE_MAIL);
		m_totaoRoles.push_back(mail_module->getRoleGuid());
	}

	return m_totaoRoles;
}


SRoleGuid CMailSystemGM::getUniqueRoleGuid()
{
	return m_uniqueMailer;
}

BSLib::uint64 CMailSystemGM::getLastestSystemMailId()
{
	return m_lastestSystemMailId;
}

bool CMailSystemGM::mailGetSystem(SRoleGuid& a_mailer, BSLib::uint64 a_roleLastUniqueId, TMailContainerMap& a_container)
{
	TMailContainerMap *unique_container = mailOpenBox(m_uniqueMailer);
	if(NULL == unique_container)
		return false;

	TMailContainerMap::iterator it = unique_container->upper_bound(a_roleLastUniqueId);
	for(; it != unique_container->end(); ++it)
	{
		SMail * unique_mail = it->second;
		SelfMailst st(a_mailer, unique_mail->m_mailType, unique_mail->m_mailId, unique_mail->m_timeStamp);
		SMail *self_mail = _createSelfMail(st);
		a_container.insert(std::make_pair(self_mail->m_mailId, self_mail));
	}

	return  !a_container.empty();
}

BSLib::uint64 CMailSystemGM::_newMailId()
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
	
	BSLib::uint64 mail_id_index =  CREATE_NEW_MAILID(SRVTYPE_GAMESERVER, m_serverNO, m_mailIdBase, m_mailIdSeed);

	return mail_id_index;
}

BSLib::uint64 CMailSystemGM::_currentTime()
{	
	BSLib::Utility::CDateTime t = BSLib::Utility::CDateTime::getCurrentTime();
	return t.getSeconds();

// 	time_t tt;
// 	time(&tt);
// 	return tt;
}

SMail* CMailSystemGM::_createSelfMail(SelfMailst &a_st)

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

	return obj;
}


bool CMailSystemGM::_cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, DBSystem::CKeyTablePtr& a_keyTable,
										  EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	
	return true;
}

bool CMailSystemGM::_cbSelectKeyIndexTableData(const GSLib::SRoleKey& a_roleKey, DBSystem::CKeyIndexTablePtr& a_keyTable,
											   EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{	
	// 只加载, 不保存
	if(EDBTABLEID_MAIL_OUTPUT_DATA == a_tableID){
		a_keyTable->traversal(*this);
		m_lastestSystemMailId = _getMaxSystemMailId();
	}

	return true;
}

BSLib::uint64 CMailSystemGM::_getMaxSystemMailId()
{
	TRoleMailContainerMap::iterator it = m_systemOutputBox.find(m_uniqueMailer);
	if( it == m_systemOutputBox.end()){
		return 0;
	}
	
	TMailContainerMap * systemMailCon  = it->second;
	TMailContainerMap::reverse_iterator mailIt = systemMailCon->rbegin();
	if( mailIt == systemMailCon->rend())
		return 0;
	
	return mailIt->first;
}

bool CMailSystemGM::exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value)
{	
	BSLib::Utility::CStream stream;
	a_value->serializeTo(stream);
	SMail *systemMail = new SMail;
	systemMail->serializeFrom(stream);
	
	SRoleGuid roleGuid(systemMail->m_accountId, systemMail->m_zoneId, systemMail->m_roleIndex);
	// 只加载系统邮件
	if( roleGuid != m_uniqueMailer)
		return true;

	TMailContainerMap * systemMailCon = NULL;
	TRoleMailContainerMap::iterator it = m_systemOutputBox.find(roleGuid);
	if( it == m_systemOutputBox.end()){
		 systemMailCon = new TMailContainerMap;
		 m_systemOutputBox.insert(make_pair(roleGuid, systemMailCon));
	}
	else{
		systemMailCon = it->second;
	}

	systemMailCon->insert(std::make_pair(systemMail->m_mailId, systemMail));
	return true;
}


}//GM

}//MailSystem

}//GSLib

