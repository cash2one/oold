
#include <GSLib/playerSystem/GM/roleModuleGMMgr.h>
#include <GSLib/masterSystem/GM/masterSystemGM.h>
#include <GSLib/playerSystem/GM/playerGMMgr.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/masterSystem/msgMasterSystem.h>
#include <GFLib/commonServer/commonServer.h>
#include <GSLib/dbSystem/DB/dbSystemDB.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <BSLib/utility/convert.h>
#include <GSLib/chatSystem/GM/chatSystemGM.h>

namespace GSLib
{

namespace MasterSystem
{

namespace GM
{

BSLIB_SINGLETON_DEFINE(CMasterSystemGM);

CMasterSystemGM::CMasterSystemGM()
{	
	m_count = 0;
}

CMasterSystemGM::~CMasterSystemGM()
{
	;
}

void CMasterSystemGM::update(BSLib::uint64 a_delayMilliseconds)
{
}

bool CMasterSystemGM::_init()
{
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CMasterSystemGM::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CMasterSystemGM::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_loadGameConfig(a_configPath);
}

bool CMasterSystemGM::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{	
	GSLIB_MSGFUN_REG(CMsgMasterSystemXX2XSReqAccountSearch, CMasterSystemGM);
	GSLIB_MSGFUN_REG(CMsgMasterSystemXX2XSReqAccountPwd, CMasterSystemGM);
	GSLIB_MSGFUN_REG(CMsgMasterSystemXX2XSReqAccountForbid, CMasterSystemGM);
	GSLIB_MSGFUN_REG(CMsgMasterSystemXX2XSReqBroadcast, CMasterSystemGM);
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_initServerMsg(a_msgExecMgr);
}

bool CMasterSystemGM::_ICommonSystem_startSystem()
{	
	return GSLib::DBSystem::CDBCommonSystem::_ICommonSystem_startSystem();
}

void CMasterSystemGM::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{	
	if(a_serverID.m_type == GSLib::SRVTYPE_CENTERSERVER)
	{
		m_cnKey = a_key;
	}
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerEnter(a_serverID, a_key);
}

void CMasterSystemGM::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{	
	if(a_serverID.m_type == GSLib::SRVTYPE_CENTERSERVER)
	{
		m_cnKey = "";
	}
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerLeave(a_serverID, a_key);
}

void CMasterSystemGM::_onCMsgMasterSystemXX2XSReqBroadcast(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgMasterSystemXX2XSReqBroadcast* req = (CMsgMasterSystemXX2XSReqBroadcast*)a_msg;
	GSLib::ChatSystem::GM::CChatSystemGM::singleton().sendAnnounce(req->content);
}


void CMasterSystemGM::_onCMsgMasterSystemXX2XSReqAccountForbid(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgMasterSystemXX2XSReqAccountForbid* req = (CMsgMasterSystemXX2XSReqAccountForbid*)a_msg;
	
	AccountForbid *task = new AccountForbid;
	task->id = nextCount();
	task->type = eAccountForbid;
	task->stubId = req->stubId;
	task->newState = req->setState ? 1 : 0;
	task->accountName = req->accountName;
	m_taskMap.insert(std::make_pair(task->id, task));

	std::string sqlWhere = "AccountName = \'";
	sqlWhere += req->accountName;
	sqlWhere += "\'";
	GSLib::SRoleKey roleKey(0, 0, GSLib::INVALID_ROLEINDEX);
	selectGlobalTableData(roleKey,roleKey, "" , "", GSLib::EDBTABLEID_ACCOUNT_DATA, EMODULECTYPE_MASTER,
		task->id, GFLib::EFUNCTYPE_NULL, sqlWhere);

// 	CMsgMasterSystemXS2XXAckAccountForbid ack;
// 	ack.stubId = req->stubId;
// 	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_cnKey, ack);
}

void CMasterSystemGM::_onCMsgMasterSystemXX2XSReqAccountPwd(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgMasterSystemXX2XSReqAccountPwd* req = (CMsgMasterSystemXX2XSReqAccountPwd*)a_msg;
	
	AccountPwd *task = new AccountPwd;
	task->id = nextCount();
	task->type = eAccountPwd;
	task->stubId = req->stubId;
	task->newPwd = req->pwd;
	task->accountName = req->accountName;
	m_taskMap.insert(std::make_pair(task->id, task));

	std::string sqlWhere = "AccountName = \'";
	sqlWhere += req->accountName;
	sqlWhere += "\'";
	GSLib::SRoleKey roleKey(0, 0, GSLib::INVALID_ROLEINDEX);
	selectGlobalTableData(roleKey,roleKey, "" , "", GSLib::EDBTABLEID_ACCOUNT_DATA, EMODULECTYPE_MASTER,
		task->id, GFLib::EFUNCTYPE_NULL, sqlWhere);

	// 	CMsgMasterSystemXS2XXAckAccountPwd ack;
	// 	ack.stubId = req->stubId;
	// 	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_cnKey, ack);
}

void CMasterSystemGM::_onCMsgMasterSystemXX2XSReqAccountSearch(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{	
	CMsgMasterSystemXX2XSReqAccountSearch *req = (CMsgMasterSystemXX2XSReqAccountSearch *)a_msg;
	
	AccountTask *task = new AccountTask;
	task->id = nextCount();
	task->type = eAccountTask;
	task->stubId = req->stubId;
	m_taskMap.insert(std::make_pair(task->id, task));

	std::string sqlWhere = "AccountName = \'";
	sqlWhere += req->accountName;
	sqlWhere += "\'";
	GSLib::SRoleKey roleKey(0, 0, GSLib::INVALID_ROLEINDEX);
	selectGlobalTableData(roleKey,roleKey, "" , "", GSLib::EDBTABLEID_ACCOUNT_DATA, EMODULECTYPE_MASTER,
		task->id, GFLib::EFUNCTYPE_NULL, sqlWhere);
}

void CMasterSystemGM::_onAccountPwd(BSLib::uint32 a_id, bool success)
{
	AccountPwd *task = (AccountPwd*)_getTask(m_curSession);
	if( NULL == task)
		return;

	CMsgMasterSystemXS2XXAckAccountPwd ack;
	ack.accountName = task->accountName;
	if(success)
	{
		BSLibSprintf(task->accountData.m_accountPassword,sizeof(char)*(GSLIB_TEXT_MAX_ACCOUNT_PASSWORD + 1),"%s",task->newPwd.c_str());
		BSLib::Utility::CStream stream;
		stream.reset();
		stream.write((const char*)&(task->accountData),sizeof(task->accountData));
		task->accountPtr->update(stream);
		task->accountPtr->saveDataToDBServer(true);
	}
	else
		ack.result = 1;

	
	ack.stubId = task->stubId;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_cnKey, ack);
}

void CMasterSystemGM::_onAccountForbid(BSLib::uint32 a_id, bool success)
{
	AccountForbid *task = (AccountForbid*)_getTask(m_curSession);
	if( NULL == task)
		return;

	CMsgMasterSystemXS2XXAckAccountForbid ack;
	ack.accountName = task->accountName;
	if(success)
	{
		task->accountData.m_forbidden = task->newState;
		BSLib::Utility::CStream stream;
		stream.reset();
		stream.write((const char*)&(task->accountData),sizeof(task->accountData));
		task->accountPtr->update(stream);
		task->accountPtr->saveDataToDBServer(true);
	}

	ack.state = task->accountData.m_forbidden;
		

	ack.stubId = task->stubId;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_cnKey, ack);
}

void CMasterSystemGM::_onAccountTask(BSLib::uint32 a_id, bool success)
{	
	AccountTask *task = (AccountTask*)_getTask(m_curSession);
	if( NULL == task)
		return;
	
	CMsgMasterSystemXS2XXAckAccountSearch ack;
	ack.stubId = task->stubId;
	if(success)
	{
		ack.accountID = task->accountData.m_accountID;
		ack.accountName = task->accountData.m_accountName;
		ack.regTime = task->accountData.m_registerTime;
		ack.channel = task->accountData.m_channelID;
		ack.state = task->accountData.m_forbidden;
		for(std::vector<GSLib::PlayerSystem::DB::SRoleData>::iterator it = task->roles.begin();
			it != task->roles.end(); ++it)
		{
			ack.roles.push_back(it->m_roleName);
		}
	}
	else
		ack.result = 1;

	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_cnKey, ack);
}

bool CMasterSystemGM::_cbSelectGlobalKeyTableData(const GSLib::SRoleKey& a_srcRoleKey, const GSLib::SRoleKey& a_roleKey,
												  DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType,
												  BSLib::uint32 a_sessionID)
{	
	m_curSession = a_sessionID;
	m_tableID = a_tableID;

	Task *task = _getTask(m_curSession);
	if( NULL == task)
		return false;

	if(GSLib::EDBTABLEID_ACCOUNT_DATA == a_tableID)
	{
		if(eAccountTask == task->type)
		{
			if( 1 != a_keyTable->getRowCount())
			{
				_onAccountTask(a_sessionID, false);
				return true;
			}

			a_keyTable->traversal(*this);
		}
		else if(eAccountPwd == task->type)
		{
			if( 1 != a_keyTable->getRowCount())
			{
				_onAccountPwd(a_sessionID, false);
				return true;
			}
			
			AccountPwd *pwd = (AccountPwd *)task;
			pwd->accountPtr = a_keyTable;
			a_keyTable->traversal(*this);
			_onAccountPwd(a_sessionID, true);
		}

		else if(eAccountForbid == task->type)
		{
			if( 1 != a_keyTable->getRowCount())
			{
				_onAccountForbid(a_sessionID, false);
				return true;
			}

			AccountForbid *forbid = (AccountForbid *)task;
			forbid->accountPtr = a_keyTable;
			a_keyTable->traversal(*this);
			_onAccountForbid(a_sessionID, true);
		}
	}

	return true;
}

bool CMasterSystemGM::_cbSelectGlobalKeyIndexTableData(const GSLib::SRoleKey& a_srcRoleKey, const GSLib::SRoleKey& a_roleKey,
													   DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType,
													   BSLib::uint32 a_sessionID)
{	
	m_curSession = a_sessionID;
	m_tableID = a_tableID;

	Task *task = _getTask(m_curSession);
	if( NULL == task)
		return false;

	if( GSLib::EDBTABLEID_ROLE_DATA == a_tableID)
	{	
		if(eAccountTask == task->type)
		{
			a_keyTable->traversal(*this);
			_onAccountTask(a_sessionID, true);
		}
	}

	return true;
}

bool CMasterSystemGM::exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value)
{	
	Task *task = _getTask(m_curSession);
	if( NULL == task)
		return false;

	if(eAccountTask == task->type)
	{
		if(GSLib::EDBTABLEID_ACCOUNT_DATA == m_tableID)
		{
			_onAccountTaskExec1((AccountTask*)task, a_key, a_value);
		}

		if(GSLib::EDBTABLEID_ROLE_DATA == m_tableID)
		{
			_onAccountTaskExec2((AccountTask*)task, a_key, a_value);
		}
	}
	else if( eAccountPwd == task->type)
	{
		if(GSLib::EDBTABLEID_ACCOUNT_DATA == m_tableID)
		{
			_onAccountPwdExec((AccountPwd*)task, a_key, a_value);
		}
	}
	else if( eAccountForbid == task->type)
	{
		if(GSLib::EDBTABLEID_ACCOUNT_DATA == m_tableID)
		{
			_onAccountForbidExec((AccountForbid*)task, a_key, a_value);
		}
	}

	return true;
}

void CMasterSystemGM::_onAccountPwdExec(AccountPwd * task, const std::string& a_key, BSLib::Database::CDBTableRow*& a_value)
{
	BSLib::Utility::CStream stream;
	a_value->serializeTo(stream);
	GSLib::DBSystem::LG::SAccountData accountData;
	if (stream.readSize() < sizeof(accountData))
	{
		return;
	}

	stream.read((char*)&(task->accountData), sizeof(task->accountData));
}

void CMasterSystemGM::_onAccountForbidExec(AccountForbid * task, const std::string& a_key, BSLib::Database::CDBTableRow*& a_value)
{
	BSLib::Utility::CStream stream;
	a_value->serializeTo(stream);
	GSLib::DBSystem::LG::SAccountData accountData;
	if (stream.readSize() < sizeof(accountData))
	{
		return;
	}

	stream.read((char*)&(task->accountData), sizeof(task->accountData));
}

void CMasterSystemGM::_onAccountTaskExec1(AccountTask * task, const std::string& a_key, BSLib::Database::CDBTableRow*& a_value)
{
	BSLib::Utility::CStream stream;
	a_value->serializeTo(stream);
	GSLib::DBSystem::LG::SAccountData accountData;
	if (stream.readSize() < sizeof(accountData))
	{
		return;
	}

	stream.read((char*)&(task->accountData), sizeof(task->accountData));

	std::string sqlWhere = "AccountID = ";
	sqlWhere += BSLib::Utility::CConvert::toStringA(task->accountData.m_accountID);

	GSLib::SRoleKey roleKey(task->accountData.m_accountID, 23, GSLib::INVALID_ROLEINDEX);
	selectGlobalTableData(roleKey,roleKey, "" , "", GSLib::EDBTABLEID_ROLE_DATA, EMODULECTYPE_MASTER,
		task->id, GFLib::EFUNCTYPE_NULL, sqlWhere);
}

void CMasterSystemGM::_onAccountTaskExec2(AccountTask * task, const std::string& a_key, BSLib::Database::CDBTableRow*& a_value)
{
	BSLib::Utility::CStream stream;
	a_value->serializeTo(stream);
	PlayerSystem::DB::SRoleData roleData;
	if (stream.readSize() < sizeof(roleData))
	{
		return;
	}

	stream.read((char*)&(roleData), sizeof(roleData));
	task->roles.push_back(roleData);
}

Task* CMasterSystemGM::_getTask(BSLib::uint32 a_id)
{
	std::map<BSLib::uint32, Task* >::iterator it = m_taskMap.find(a_id);
	if(it == m_taskMap.end())
		return NULL;

	return it->second;
}

BSLib::uint32 CMasterSystemGM::nextCount()
{
	return m_count++;
}



}//GM

}

}//GSLib
