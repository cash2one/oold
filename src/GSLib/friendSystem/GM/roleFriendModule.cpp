
#include <GSLib/friendSystem/GM/roleFriendModule.h>
#include <GSLib/friendSystem/msgFriendSystem.h>
#include <GSLib/tracer.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/playerSystem/GM/playerGM.h>
#include <GSLib/friendSystem/DB/tableFriendDB.h>
#include <GSLib/friendSystem/GM/friendSystemGM.h>
#include <GSLib/playerSystem/GM/playerGM.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <map>
#include <GSLib/friendSystem/CN/msgFriendSystemCN.h>
#include <GSLib/sceneSystem/GM/roleSceneModule.h>

namespace GSLib
{

namespace FriendSystem
{

namespace GM
{

CRoleFriendModule::CRoleFriendModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType)
:  GSLib::PlayerSystem::GM::CRoleModuleGM(a_roleGM, a_moduleType)
{
}

CRoleFriendModule::~CRoleFriendModule()
{
	;
}

void CRoleFriendModule::preInit(bool isFirst)
{	

}

void CRoleFriendModule::postInit(bool isFirst)
{

}

void CRoleFriendModule::initToClient()
{	
}

void CRoleFriendModule::final()
{
	;
}

void CRoleFriendModule::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDFriendSystemGC2GMReqFriendsLocal, 
		&BSLib::Framework::CreateCMessage<CMsgFriendSystemGC2GMReqFriendsLocal>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDFriendSystemGC2GMReqFriendsLocal, &CRoleFriendModule::_onMsgFriendSystemGC2GMReqLocal, this);
	
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDFriendSystemCN2GMNtfFriendsChange, 
		&BSLib::Framework::CreateCMessage<CMsgFriendSystemCN2GMNtfFriendsChange>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDFriendSystemCN2GMNtfFriendsChange, &CRoleFriendModule::_onMsgFriendSystemCN2GMNtfFriendChange, this);
}

void CRoleFriendModule::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	a_msgExecMgr->delMsgExecPtr(msgIDFriendSystemGC2GMReqFriendsLocal);
}

void CRoleFriendModule::_onMsgFriendSystemGC2GMReqLocal(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{	
	using namespace GSLib::SceneSystem::GM;
	using namespace GSLib::PlayerSystem::GM;
	CRoleGM* role = getRoleGM();
	CRoleSceneModule* role_module =  (CRoleSceneModule*)role->getPlayerModuleGM(EMODULECTYPE_SCENE);
	do 
	{
		if(NULL == role_module)
			break;

		std::vector<CSceneRoleInfo> info;
		role_module->getSceneRoles(info);
		CMsgFriendSystemGM2GCAckFriendsLocal ack;
		for(BSLib::uint32 i = 0; i < info.size(); i++)
		{
			const CSceneRoleInfo& it = info[i];
			SFriendInfo f;
			f.m_role = it.m_roleKey;
			f.m_name = it.m_roleName;
			f.m_state = 1;
			f.m_job = it.m_roleTPID;
			f.m_level = it.m_level;
			f.m_power = it.m_combatPower;
			ack.addFriend(f);
		}
		sendMsgToClient(ack);

	} while (false);
}

void CRoleFriendModule::updateDataToDB()
{
}

bool CRoleFriendModule::extendCapacity(BSLib::uint32 a_size)
{
	CMsgFriendSystemGM2CNNtfFriendsExtendCapacity req;
	req.m_size = a_size;
	return sendMsgToCenterServer(req);
}

bool CRoleFriendModule::exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value)
{
	BSLib::Utility::CStream stream;
	a_value->serializeTo(stream);
	return m_myfriend.deserializeFrom(stream);
}

bool CRoleFriendModule::cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable,
											   EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
	if(EDBTABLEID_ROLE_FRIEND_DATA == a_tableID){
		a_keyTable->traversal(*this);
		return true;
	}

	return false;
}

void CRoleFriendModule::_onMsgFriendSystemCN2GMNtfFriendChange(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgFriendSystemCN2GMNtfFriendsChange *ntf = (CMsgFriendSystemCN2GMNtfFriendsChange *)a_msg;
	if(NULL == ntf)
		return;
	
	if(1 == ntf->m_changeType)
	{
		std::copy(ntf->m_changes.begin(), ntf->m_changes.end(), std::back_inserter(m_myfriend.m_friends));
	}
	else if( 2 == ntf->m_changeType)
	{
		for(std::vector<SRoleKey>::iterator it = ntf->m_changes.begin();
			it != ntf->m_changes.end(); ++it)
		{
			std::vector<SRoleKey>::iterator findIt = std::find(m_myfriend.m_friends.begin(), m_myfriend.m_friends.end(), *it);
			if( findIt == m_myfriend.m_friends.end())
				continue;
			m_myfriend.m_friends.erase(findIt);
		}
	}
	
}

bool CRoleFriendModule::isMyFriend(const SRoleKey& a_role)
{
	std::vector<SRoleKey>::iterator findIt = std::find(m_myfriend.m_friends.begin(), m_myfriend.m_friends.end(), a_role);
	return findIt != m_myfriend.m_friends.end();
}

void CRoleFriendModule::getMyFriends(std::vector<SRoleKey>& a_roles)
{
	std::copy(m_myfriend.m_friends.begin(), m_myfriend.m_friends.end(), std::back_inserter(a_roles));
}



}//GM

}

}//GSLib