#include <GSLib/masterSystem/CN/masterSystemCN.h>
#include <BSLib/utility/dateTime.h>
#include <GSLib/funType.h>
#include <GSLib/serverType.h>
#include <sstream>
#include <time.h>
#include <GSLib/masterSystem/GM/msgMasterSystemGM.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <GSLib/masterSystem/msgMasterSystem.h>
#include <GFLib/commonServer/commonServer.h>
#include <GSLib/playerSystem/CN/playerCN.h>
#include <GSLib/playerSystem/CN/playerCNMgr.h>
#include <GSLib/playerSystem/CN/roleModuleCNMgr.h>
#include <GSLib/masterSystem/CN/roleMasterModuleCN.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <GSLib/playerSystem/CN/roleBaseInfoCNMgr.h>
#include <GSLib/friendSystem/CN/roleFriendModuleCN.h>
#include <GSLib/mailSystem/CN/mailSystemCN.h>

namespace GSLib
{

namespace MasterSystem
{

namespace CN
{

BSLIB_SINGLETON_DEFINE(CMasterSystemCN);

CMasterSystemCN::CMasterSystemCN()
{	

}

CMasterSystemCN::~CMasterSystemCN()
{
	;
}

void CMasterSystemCN::update(BSLib::uint64 a_delayMilliseconds)
{
	;
}

bool CMasterSystemCN::_init()
{
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CMasterSystemCN::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CMasterSystemCN::_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::_loadGameConfig(a_configPath);
}

bool CMasterSystemCN::_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{	
	GSLIB_MSGFUN_REG(CMsgMasterSystemXX2XSReqRoleInfo, CMasterSystemCN);
	GSLIB_MSGFUN_REG(CMsgMasterSystemXX2XSReqMail, CMasterSystemCN);
	GSLIB_MSGFUN_REG(CMsgMasterSystemXX2XSReqRoleItemDeduct, CMasterSystemCN);
	GSLIB_MSGFUN_REG(CMsgMasterSystemXX2XSReqBroadcast, CMasterSystemCN);

	GSLIB_MSGFUN_REG(CMsgMasterSystemXX2XSReqAccountSearch, CMasterSystemCN);
	GSLIB_MSGFUN_REG(CMsgMasterSystemXS2XXAckAccountSearch, CMasterSystemCN);

	GSLIB_MSGFUN_REG(CMsgMasterSystemXX2XSReqAccountPwd, CMasterSystemCN);
	GSLIB_MSGFUN_REG(CMsgMasterSystemXS2XXAckAccountPwd, CMasterSystemCN);

	GSLIB_MSGFUN_REG(CMsgMasterSystemXX2XSReqAccountForbid, CMasterSystemCN);
	GSLIB_MSGFUN_REG(CMsgMasterSystemXS2XXAckAccountForbid, CMasterSystemCN);


	return GSLib::DBSystem::CDBCommonSystem::_initServerMsg(a_msgExecMgr);
}


bool CMasterSystemCN::_startSystem()
{	
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

void CMasterSystemCN::_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{	
	if(a_serverID.m_type == GSLib::SRVTYPE_SUPERSERVER)
	{
		m_superKey = a_key;
	}
	else if(a_serverID.m_type == GSLib::SRVTYPE_GAMESERVER)
	{	
		m_gmkeys.push_back(a_key);
		if(m_gmKey.empty())
			m_gmKey = a_key;
	}
	return GSLib::DBSystem::CDBCommonSystem::_cbServerEnter(a_serverID, a_key);
}

void CMasterSystemCN::_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{	
	if(a_serverID.m_type == GSLib::SRVTYPE_SUPERSERVER)
	{
		m_superKey = "";
	}
	else if(a_serverID.m_type == GSLib::SRVTYPE_GAMESERVER)
	{	
		std::vector<std::string>::iterator it = std::find(m_gmkeys.begin(), m_gmkeys.end(), a_key);
		if( it != m_gmkeys.end())
		{
			m_gmkeys.erase(it);
		}

		if(m_gmKey == a_key)
			m_gmKey = "";
	}
	GSLib::DBSystem::CDBCommonSystem::_cbServerLeave(a_serverID, a_key);
}

void CMasterSystemCN::_onCMsgMasterSystemXX2XSReqRoleItemDeduct(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgMasterSystemXX2XSReqRoleItemDeduct* req = (CMsgMasterSystemXX2XSReqRoleItemDeduct*)a_msg;
	CMsgMasterSystemXS2XXAckRoleItemDeduct ack;

	do 
	{
		std::vector<MailSystem::SRoleGuid> roleGuids;
		using namespace PlayerSystem::CN;
		CRoleBaseInfoCN * base = 
			CRoleBaseInfoCNMgr::singleton().getRoleBaseInfoCNByRoleName(req->name);

		if(NULL == base)
		{	
			ack.result = 1;
			break;
		}
		
		std::vector<BSLib::uint32> ids;
		std::vector<BSLib::uint32> nums;
		ids.push_back(req->itemId);
		nums.push_back(req->itemNum);
		roleGuids.push_back(MailSystem::SRoleGuid(base->getRoleKey().getAccountID(), base->getRoleKey().getZoneID(), base->getRoleKey().getIndex()));
		std::vector<BSLib::uint32> types;
		std::string dummy;
		MailSystem::CN::CMailSystemCN::singleton().mailSend(dummy, roleGuids, MailSystem::EMailTypeDeduct, 
			dummy, dummy, types, ids, nums);

	} while (false);


	ack.stubId = req->stubId;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_superKey, ack);
}

void CMasterSystemCN::_onCMsgMasterSystemXX2XSReqBroadcast(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgMasterSystemXX2XSReqBroadcast* req = (CMsgMasterSystemXX2XSReqBroadcast*)a_msg;
	using namespace GFLib::CommonServer;
	for(std::vector<std::string>::iterator it = m_gmkeys.begin(); it != m_gmkeys.end(); ++it)
	{
		CServiceMgr::singleton().sendMsgToServer(*it, *req);
	}

	CMsgMasterSystemXS2XXAckBroadcast ack;
	ack.stubId = req->stubId;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_superKey, ack);
}

void CMasterSystemCN::_onCMsgMasterSystemXX2XSReqMail(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgMasterSystemXX2XSReqMail* req = (CMsgMasterSystemXX2XSReqMail*)a_msg;
	CMsgMasterSystemXS2XXAckMail ack;
	// Θ«Με
	do 
	{
		if(2 == req->type)
		{	
			std::vector<MailSystem::SRoleGuid> roles;
			std::vector<BSLib::uint32> types;
			MailSystem::CN::CMailSystemCN::singleton().mailSend(req->sender, roles, MailSystem::EMailTypeSystem, 
				req->title, req->content, types, req->itemIds, req->itemNums);
		}
		else if( 1 == req->type)
		{
			if( 0 == req->roles.size())
			{
				ack.result = 1;
				break;
			}
			
			std::vector<MailSystem::SRoleGuid> roleGuids;
			for(BSLib::uint32 i = 0; i < req->roles.size(); i++)
			{
				using namespace PlayerSystem::CN;
				CRoleBaseInfoCN * base = 
					CRoleBaseInfoCNMgr::singleton().getRoleBaseInfoCNByRoleName(req->roles[i]);

				if(NULL == base)
					continue;;
				
				roleGuids.push_back(MailSystem::SRoleGuid(base->getRoleKey().getAccountID(), base->getRoleKey().getZoneID(), base->getRoleKey().getIndex()));
			}

			if( 0 == roleGuids.size())
			{
				ack.result = 1;
				break;
			}
			
			std::vector<BSLib::uint32> types;	
			MailSystem::CN::CMailSystemCN::singleton().mailSend(req->sender, roleGuids, MailSystem::EMailTypeSystem, 
				req->title, req->content, types, req->itemIds, req->itemNums);
		}


	} while (false);
	
	ack.stubId = req->stubId;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_superKey, ack);
}

void CMasterSystemCN::_onCMsgMasterSystemXX2XSReqRoleInfo(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{	
	CMsgMasterSystemXX2XSReqRoleInfo *req = (CMsgMasterSystemXX2XSReqRoleInfo *)a_msg;
	CMsgMasterSystemXS2XXAckRoleInfo ack;

	using namespace PlayerSystem::CN;
	CRoleBaseInfoCN * base = 
		CRoleBaseInfoCNMgr::singleton().getRoleBaseInfoCNByRoleName(req->role);
	if(NULL != base)
	{
		ack.name = base->getRoleName();
		ack.level = base->getRoleLevel();
		ack.tpID = base->getRoleTPID();
		ack.accountID = base->getRoleKey().getAccountID();
		ack.roleIndex = base->getRoleKey().getIndex();
		ack.exp = base->getRoleExp();
		ack.gold = base->getGold();
		ack.diamond = base->getChargeDiamond() + base->getBindDiamond();
		
		using namespace GSLib::PlayerSystem::CN;
		using namespace GSLib::FriendSystem::CN;
		do 
		{	
			GFLib::SAccountKey account(base->getRoleKey().getAccountID(), base->getRoleKey().getZoneID());
			CPlayerCN *player = CPlayerCNMgr::singleton().getPlayerCN(account);
			if(NULL == player)
				break;

			if(player->getCurRoleIndex() != base->getRoleKey().getIndex())
				break;

			CRoleCN * role = player->getCurRole();
			CRoleFriendModuleCN* friendModule = (CRoleFriendModuleCN*)role->getPlayerModuleCN(EMODULETYPE_FRIEND);
			if(NULL == friendModule)
				break;

			std::vector<SRoleKey> roles;
			friendModule->getMyFriends(roles);
			for(std::vector<SRoleKey>::iterator it = roles.begin(); it != roles.end(); ++it)
			{
				CRoleBaseInfoCN * friendBase = 
					CRoleBaseInfoCNMgr::singleton().getRoleBaseInfoCNByRoleKey(it->getDBKey());
				if(NULL == friendBase)
					continue;

				ack.friends.push_back(friendBase->getRoleName());
			}

		} while (false);

	}
	else
	{
		ack.result = 1;
	}

	ack.stubId = req->stubId;
	GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(m_superKey, ack);
}

bool CMasterSystemCN::_cbSelectGlobalKeyTableData(const GSLib::SRoleKey& a_srcRoleKey, const GSLib::SRoleKey& a_roleKey,
												  DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType,
												  BSLib::uint32 a_sessionID)
{

	return true;
}

bool CMasterSystemCN::_cbSelectGlobalKeyIndexTableData(const GSLib::SRoleKey& a_srcRoleKey, const GSLib::SRoleKey& a_roleKey,
													   DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType,
													   BSLib::uint32 a_sessionID)
{	
// 	if(EDBTABLEID_MAIL_OUTPUT_DATA == a_tableID){
// 		a_keyTable->traversal(*this);
// 		m_outputTablePtr = a_keyTable;
// 	}
	return true;
}

bool CMasterSystemCN::exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value)
{	
// 	BSLib::Utility::CStream stream;
// 	a_value->serializeTo(stream);
// 	SMail *systemMail = new SMail;
// 	systemMail->serializeFrom(stream);
	return true;
}

GSLIB_CN2GM_MSGFUN_DEFINE(CMsgMasterSystemXX2XSReqAccountSearch, CMasterSystemCN)
GSLIB_CN2SP_MSGFUN_DEFINE(CMsgMasterSystemXS2XXAckAccountSearch, CMasterSystemCN)

GSLIB_CN2GM_MSGFUN_DEFINE(CMsgMasterSystemXX2XSReqAccountPwd, CMasterSystemCN)
GSLIB_CN2SP_MSGFUN_DEFINE(CMsgMasterSystemXS2XXAckAccountPwd, CMasterSystemCN)

GSLIB_CN2GM_MSGFUN_DEFINE(CMsgMasterSystemXX2XSReqAccountForbid, CMasterSystemCN)
GSLIB_CN2SP_MSGFUN_DEFINE(CMsgMasterSystemXS2XXAckAccountForbid, CMasterSystemCN)


}//GM

}

}//GSLib
