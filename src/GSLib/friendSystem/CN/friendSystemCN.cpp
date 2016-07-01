#include <GSLib/friendSystem/CN/friendSystemCN.h>
#include <BSLib/utility/dateTime.h>
#include <GSLib/funType.h>
#include <GSLib/serverType.h>
#include <sstream>
#include <time.h>
#include <GSLib/friendSystem/GM/msgFriendSystemGM.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <GSLib/friendSystem/msgFriendSystem.h>
#include <GFLib/commonServer/commonServer.h>
#include <GSLib/playerSystem/CN/playerCN.h>
#include <GSLib/playerSystem/CN/playerCNMgr.h>
#include <GSLib/playerSystem/CN/roleModuleCNMgr.h>
#include <GSLib/friendSystem/CN/roleFriendModuleCN.h>
#include <BSLib/utility/dateTime.h>


namespace GSLib
{

namespace FriendSystem
{

namespace CN
{

BSLIB_SINGLETON_DEFINE(CFriendSystemCN);

CFriendSystemCN::CFriendSystemCN()
{	

}

CFriendSystemCN::~CFriendSystemCN()
{
	;
}

void CFriendSystemCN::update(BSLib::uint64 a_delayMilliseconds)
{
	;
}

bool CFriendSystemCN::_init()
{	
	GSLib::PlayerSystem::CN::CRoleModuleCNMgr::singleton().addCreateRoleModuleFun(EMODULETYPE_FRIEND,
		GSLib::PlayerSystem::CN::createRoleModuleFun<CRoleFriendModuleCN>);

	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CFriendSystemCN::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CFriendSystemCN::ICommonServer_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_loadGameConfig(a_configPath);
}

bool CFriendSystemCN::ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{	
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_initServerMsg(a_msgExecMgr);
}


bool CFriendSystemCN::_startSystem()
{	
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CFriendSystemCN::ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{	
	return GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerEnter(a_serverID, a_key);
}

void CFriendSystemCN::ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{	
	GSLib::DBSystem::CDBCommonSystem::ICommonServer_cbServerLeave(a_serverID, a_key);
}


bool CFriendSystemCN::exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value)
{
	BSLib::Utility::CStream stream;
	a_value->serializeTo(stream);
	DB::SRoleFriendPendingQueueData* data = new DB::SRoleFriendPendingQueueData;
	if(!data->deserializeFrom(stream)){
		return false;
	}

	m_friendPendingQueue.setValue(data->getDBKey(), data);
	return true;
}

bool CFriendSystemCN::_cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, DBSystem::CKeyTablePtr& a_keyTable,
											EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	if(EDBTABLEID_FRIEND_PENDING_QUEUE_DATA == a_tableID){
		a_keyTable->traversal(*this);
		m_dbPtr = a_keyTable;
		return true;
	}

	return false;
}

bool CFriendSystemCN::_dbUpdate(DB::SRoleFriendPendingQueueData* a_queue)
{	
	if(m_dbPtr == NULL)
		return false;

	BSLib::Utility::CStream stream;
	a_queue->serializeTo(stream);
	m_dbPtr->update(stream);
	return m_dbPtr->saveDataToDBServer(a_queue->getDBKey(), true);
}

bool CFriendSystemCN::_dbDel(DB::SRoleFriendPendingQueueData* a_queue)
{	
	if(m_dbPtr == NULL)
		return false;
	
	m_dbPtr->remove(a_queue->getDBKey());
	m_dbPtr->saveDataToDBServer(a_queue->getDBKey(), true);
	return true;
}

DB::SRoleFriendPendingQueueData*
CFriendSystemCN::_getData(std::string a_key)
{
	BSLib::Utility::CHashMap<std::string, 
	DB::SRoleFriendPendingQueueData*>::iterator it = 
	m_friendPendingQueue.find(a_key);
	
	if( it == m_friendPendingQueue.end())
		return NULL;
	
	return it->second;
}

bool CFriendSystemCN::tryToUpdateQueue(const SRoleKey& a_role, BSLib::uint32 a_left)
{	
	DB::SRoleFriendPendingQueueData temp;
	temp.m_role = a_role;
	DB::SRoleFriendPendingQueueData* data = _getData(temp.getDBKey());
	if(NULL == data)
		return false;


	data = new DB::SRoleFriendPendingQueueData;
	data->m_role = a_role;
	data->m_left = a_left;
	BSLib::Utility::CDateTime now = BSLib::Utility::CDateTime::getCurrentTime();
	data->m_leftAddTime = now.getSeconds();
	m_friendPendingQueue.setValue(data->getDBKey(), data);
	_dbUpdate(data);
	return true;
}

bool CFriendSystemCN::createAndUpdateQueue(const SRoleKey& a_role, BSLib::uint32 a_left)
{
	DB::SRoleFriendPendingQueueData temp;
	temp.m_role = a_role;
	DB::SRoleFriendPendingQueueData* data = _getData(temp.getDBKey());
	if(NULL == data)
	{
		data = new DB::SRoleFriendPendingQueueData;
		data->m_role = a_role;
		m_friendPendingQueue.setValue(data->getDBKey(), data);
	}
	
	data->m_left = a_left;
	BSLib::Utility::CDateTime now = BSLib::Utility::CDateTime::getCurrentTime();
	data->m_leftAddTime = now.getSeconds();

	_dbUpdate(data);
	return true;
}

bool CFriendSystemCN::delQueue()
{
	return false;
}

bool CFriendSystemCN::newFriendRequest(const SRoleKey& a_role, const SRoleKey& a_destRole)
{	
	DB::SRoleFriendPendingQueueData temp;
	temp.m_role = a_role;
	DB::SRoleFriendPendingQueueData* data = _getData(temp.getDBKey());
	if(NULL == data)
	{
		data = new DB::SRoleFriendPendingQueueData;
		data->m_role = a_role;
		m_friendPendingQueue.setValue(data->getDBKey(), data);
	}

	data->m_toBeDecided.push_back(a_destRole);
	_dbUpdate(data);
	return true;
}

bool CFriendSystemCN::delFriendRequest(const SRoleKey& a_role, const SRoleKey& a_destRole)
{	
	DB::SRoleFriendPendingQueueData temp;
	temp.m_role = a_role;
	DB::SRoleFriendPendingQueueData* data = _getData(temp.getDBKey());
	if(NULL == data)
		return false;

	std::vector<SRoleKey>::iterator it = std::find(data->m_toBeDecided.begin(), data->m_toBeDecided.end(), a_destRole);
	if(it == data->m_toBeDecided.end())
		return false;

	data->m_toBeDecided.erase(it);
	_dbUpdate(data);
	return true;
}

bool CFriendSystemCN::newFriendTotal(const SRoleKey& a_role, std::vector<SRoleKey>& a_destRoles)
{
	DB::SRoleFriendPendingQueueData temp;
	temp.m_role = a_role;
	DB::SRoleFriendPendingQueueData* data = _getData(temp.getDBKey());
	if(NULL == data)
		return false;

	a_destRoles = data->m_toBeDecided;
	return true;
}

bool CFriendSystemCN::checkNewFriendConditon(const SRoleKey& a_role, const SRoleKey& a_destRole)
{	
	// 1.没有尚未处理的
	// 2. 空间够
	DB::SRoleFriendPendingQueueData temp;
	temp.m_role = a_role;
	DB::SRoleFriendPendingQueueData* data = _getData(temp.getDBKey());
	// 空的话, 返回true吧
	if(NULL == data)
		return true;

	std::vector<SRoleKey>::iterator it = std::find(data->m_toBeDecided.begin(), data->m_toBeDecided.end(), a_destRole);
	if(it != data->m_toBeDecided.end())
		return false;

	it = std::find(data->m_tobeDel.begin(), data->m_tobeDel.end(), a_destRole);
	if(it != data->m_tobeDel.end())
		return false;

	it = std::find(data->m_quasiFriends.begin(), data->m_quasiFriends.end(), a_destRole);
	if(it != data->m_quasiFriends.end())	
		return false;
	
	// 无论是未初始化, 还是没有剩余 都返回false
	if(0 == data->m_left)
		return false;

	return true;
}

bool CFriendSystemCN::checkNewFriendConfirmConditon(const SRoleKey& a_role, const SRoleKey& a_destRole)
{
	DB::SRoleFriendPendingQueueData temp;
	temp.m_role = a_role;
	DB::SRoleFriendPendingQueueData* data = _getData(temp.getDBKey());
	// 理论上应该存在的
	if(NULL == data)
		return false;

	std::vector<SRoleKey>::iterator it = std::find(data->m_toBeDecided.begin(), data->m_toBeDecided.end(), a_destRole);
	if(it != data->m_toBeDecided.end())
		return false;

	it = std::find(data->m_tobeDel.begin(), data->m_tobeDel.end(), a_destRole);
	if(it != data->m_tobeDel.end())
		return false;

	it = std::find(data->m_quasiFriends.begin(), data->m_quasiFriends.end(), a_destRole);
	if(it != data->m_quasiFriends.end())	
		return false;

	// 要初始化的
	if( 0 == data->m_left)
		return false;

	return true;
}

// 删除好友 ,不更新空余数
bool CFriendSystemCN::newUnfriendRequest(const SRoleKey& a_role, const SRoleKey& a_destRole)
{
	DB::SRoleFriendPendingQueueData temp;
	temp.m_role = a_role;
	DB::SRoleFriendPendingQueueData* data = _getData(temp.getDBKey());
	if(NULL == data)
	{
		data = new DB::SRoleFriendPendingQueueData;
		data->m_role = a_role;
		m_friendPendingQueue.setValue(data->getDBKey(), data);
	}

	
	std::vector<SRoleKey>::iterator it = std::find(data->m_toBeDecided.begin(), data->m_toBeDecided.end(), a_destRole);
	if(it != data->m_toBeDecided.end())
		return false;

	it = std::find(data->m_tobeDel.begin(), data->m_tobeDel.end(), a_destRole);
	if(it != data->m_tobeDel.end())
		return false;

	it = std::find(data->m_quasiFriends.begin(), data->m_quasiFriends.end(), a_destRole);
	if(it != data->m_quasiFriends.end())	
		return false;
	
	data->m_tobeDel.push_back(a_destRole);
	_dbUpdate(data);
	return true;
}

bool CFriendSystemCN::delUnfriendRequest(const SRoleKey& a_role, const SRoleKey& a_destRole)
{
	DB::SRoleFriendPendingQueueData temp;
	temp.m_role = a_role;
	DB::SRoleFriendPendingQueueData* data = _getData(temp.getDBKey());
	if(NULL == data)
		return false;

	std::vector<SRoleKey>::iterator it = std::find(data->m_tobeDel.begin(), data->m_tobeDel.end(), a_destRole);
	if(it == data->m_tobeDel.end())
		return false;

	data->m_tobeDel.erase(it);
	_dbUpdate(data);
	return true;
}

bool CFriendSystemCN::newUnfriendTotal(const SRoleKey& a_role, std::vector<SRoleKey>& a_destRoles)
{
	DB::SRoleFriendPendingQueueData temp;
	temp.m_role = a_role;
	DB::SRoleFriendPendingQueueData* data = _getData(temp.getDBKey());
	if(NULL == data)
		return false;

	a_destRoles = data->m_tobeDel;
	return true;
}

// 准好友, 更新剩余数
bool CFriendSystemCN::newQuasiFriendRequest(const SRoleKey& a_role, const SRoleKey& a_destRole)
{
	DB::SRoleFriendPendingQueueData temp;
	temp.m_role = a_role;
	DB::SRoleFriendPendingQueueData* data = _getData(temp.getDBKey());
	if(NULL == data)
	{
		data = new DB::SRoleFriendPendingQueueData;
		data->m_role = a_role;
		m_friendPendingQueue.setValue(data->getDBKey(), data);
	}


	std::vector<SRoleKey>::iterator it = std::find(data->m_toBeDecided.begin(), data->m_toBeDecided.end(), a_destRole);
	if(it != data->m_toBeDecided.end())
		return false;

	it = std::find(data->m_tobeDel.begin(), data->m_tobeDel.end(), a_destRole);
	if(it != data->m_tobeDel.end())
		return false;

	it = std::find(data->m_quasiFriends.begin(), data->m_quasiFriends.end(), a_destRole);
	if(it != data->m_quasiFriends.end())	
		return false;
	
	data->m_left--;
	data->m_quasiFriends.push_back(a_destRole);
	_dbUpdate(data);
	return true;
}

bool CFriendSystemCN::delQuasiFriendRequest(const SRoleKey& a_role, const SRoleKey& a_destRole)
{
	DB::SRoleFriendPendingQueueData temp;
	temp.m_role = a_role;
	DB::SRoleFriendPendingQueueData* data = _getData(temp.getDBKey());
	if(NULL == data)
		return false;

	std::vector<SRoleKey>::iterator it = std::find(data->m_quasiFriends.begin(), data->m_quasiFriends.end(), a_destRole);
	if(it == data->m_quasiFriends.end())
		return false;

	data->m_quasiFriends.erase(it);
	data->m_left++;
	_dbUpdate(data);
	return true;
}

bool CFriendSystemCN::newQuasFriendTotal(const SRoleKey& a_role, std::vector<SRoleKey>& a_destRoles)
{
	DB::SRoleFriendPendingQueueData temp;
	temp.m_role = a_role;
	DB::SRoleFriendPendingQueueData* data = _getData(temp.getDBKey());
	if(NULL == data)
		return false;

	a_destRoles = data->m_quasiFriends;
	return true;
}

void CFriendSystemCN::onRoleOnline(std::string a_key)
{
	m_onlineRoles.setValue(a_key, 0);
}

void CFriendSystemCN::onRoleOffline(std::string a_key)
{
	BSLib::Utility::CHashMap<std::string, BSLib::uint32>::iterator it = 
		m_onlineRoles.find(a_key);

	if( it == m_onlineRoles.end())
		return;

	m_onlineRoles.erase(it);
}



}//GM

}

}//GSLib
