#include <GSLib/tracer.h>
#include <GSLib/rankSystem/msgRankSystem.h>
#include <GSLib/rankSystem/CN/rankSystemCN.h>
#include <GSLib/rankSystem/CN/rankImpl.h>
#include <GSLib/rankSystem/CN/rankSystemCN.h>
#include <GSLib/rankSystem/CN/roleRankModuleCN.h>
#include <GSLib/playerSystem/CN/roleModuleCNMgr.h>
#include <GSLib/rankSystem/CN/rankConfig.h>
#include <GSLib/mailSystem/CN/mailSystemCN.h>
#include <BSLib/utility/convert.h>
#include <algorithm>

namespace GSLib
{

namespace RankSystem
{	

namespace CN
{
BSLIB_SINGLETON_DEFINE(CRankSystemCN);

CRankSystemCN::CRankSystemCN()
{
}

CRankSystemCN::~CRankSystemCN()
{
	;
}

bool CRankSystemCN::_init()
{	

	GSLib::PlayerSystem::CN::CRoleModuleCNMgr::singleton().addCreateRoleModuleFun(EMODULECTYPE_RANK,
		GSLib::PlayerSystem::CN::createRoleModuleFun<CRoleRankModuleCN>);

	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CRankSystemCN::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CRankSystemCN::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{	
	if( !CRankConfig::singleton().loadConfigFile(a_configPath)){
		return false;
	}

	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_loadGameConfig(a_configPath);
}

bool CRankSystemCN::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	//BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDChatSystemGM2CNReqPrivateChat, &BSLib::Framework::CreateCMessage<CMsgChatSystemGM2CNReqPrivateChat>);
	//GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDChatSystemGM2CNReqPrivateChat, &CChatSystemCN::_onMsgChatSystemGM2CNReqPrivateChat, this);

	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_initServerMsg(a_msgExecMgr);
}

bool CRankSystemCN::_startSystem()
{	
	return GSLib::DBSystem::CDBCommonSystem::_startSystem();
}

bool CRankSystemCN::_cbDateTimer(BSLib::uint64, void* a_para)
{	
	m_dateTimer.update();
	return true;
}

bool CRankSystemCN::_cbSaveTimer(BSLib::uint64, void* a_para)
{	

	if( !m_dataReady)
		return true;

	for(std::vector<Rank*>::iterator it = m_rankContainer.begin(); it != m_rankContainer.end(); ++it)
	{
		Rank *obj = *it;
		if(NULL == obj)
			continue;
		if(!obj->isNeedSave())
			continue;

		BSLib::Utility::CStream buf;
		obj->serializeTo(buf);
		m_outputTablePtr->update(buf);
		m_outputTablePtr->saveDataToDBServer(obj->getDBKey(), true);
	}

// 		for(int i = 0; i < 10000; i++)
// 		{
// 			m_ordered.update(SRoleKey(i , i , i ), i );
// 		}
// 		BSLib::Utility::CStream buf;
// 		m_ordered.serializeTo(buf);
// 
// 		m_outputTablePtr->update(buf);
// 		m_outputTablePtr->saveDataToDBServer(m_ordered.getDBKey(), true);

	return true;
}

void CRankSystemCN::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{	
	if(a_serverID.m_type == SRVTYPE_DATASERVER){
		m_dataReady = true;
	}

	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerEnter(a_serverID, a_key);
}

void CRankSystemCN::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{	
	if(a_serverID.m_type == SRVTYPE_DATASERVER){
		m_dataReady = false;
	}

	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerLeave(a_serverID, a_key);
}

Rank* CRankSystemCN::getRank(BSLib::uint32 a_id)
{
	std::vector<Rank*>::iterator it = m_rankContainer.begin();
	for(; it != m_rankContainer.end(); ++it)
	{
		Rank *obj = *it;
		if( obj->getId() == (BSLib::uint64)a_id)
			return obj;
	}

	return NULL;
}

Rank* CRankSystemCN::regRank(BSLib::uint32 a_id, ERankType a_type)
{	
	if(ERANKTYPE_ORDEREDLESS == a_type)
	{
		Rank *r = new OrderedRankLess(a_id, rankCapacity(a_id));
		m_rankContainer.push_back(r);

		STimeHandle handle;
		if(rankTimeHandle( a_id, handle))
			m_dateTimer.addTimer(handle, this);

		return r;
	}

	return NULL;
}

Rank* CRankSystemCN::CreateRank(BSLib::Utility::CStream& a_stream)
{	
	BSLib::uint64 id = 0;
	BSLib::uint16 zone = 0;
	BSLib::uint32 type = 0;
	a_stream >> id;
	a_stream >> zone;
	a_stream >> type;
	ERankType rankType = (ERankType)type;
	switch(rankType)
	{
	case ERANKTYPE_ORDERED:
		return new OrderedRank(id, rankCapacity(id));

	case ERANKTYPE_BUCKET:
		return new BucketRank(id, rankCapacity(id));

	case ERANKTYPE_TRANSPOSITION:
		return new TranspositionRank(id, rankCapacity(id));

	case ERANKTYPE_ORDEREDLESS:
		return new OrderedRankLess(id, rankCapacity(id));
	}

	return NULL;
}

BSLib::uint32 CRankSystemCN::rankCapacity(BSLib::uint64 a_id)
{	
	SRankMailInfo *info = NULL;
	if( !CRankConfig::singleton().getRankMail((BSLib::int32)a_id, info))
		return 3; // 默认

	return info->m_maxSize;
}

BSLib::uint32 CRankSystemCN::rankPrizeSize(BSLib::uint64 a_id)
{
	SRankMailInfo *info = NULL;
	if( !CRankConfig::singleton().getRankMail((BSLib::int32)a_id, info))
		return 0;

	return info->m_prizeSize;
}

BSLib::uint32 GetGuangZiLiPrize(BSLib::uint32 a_no)
{
	if( a_no >= 1 && a_no <= 10)
	{
		return 17 * a_no * a_no - 350 * a_no + 3333;
	}
	else if( a_no >= 11 && a_no <= 50)
	{	
		float temp = 0.4 * a_no * a_no;
		temp  += (- 44 * a_no  + 1636);
		return temp;
	}
	
	float temp = 402 - 0.03 * a_no;
	temp = std::max<float>(temp, (float)50.0);
	return temp;
}


void CRankSystemCN::cb(BSLib::uint32 a_id)
{
	Rank* obj = getRank(a_id);
	if( NULL == obj)
		return;
	

	if(ERANKID_ARENA == a_id)
	{
		do 
		{	
			SRankMailInfo* mailInfo = NULL;
			if( !CRankConfig::singleton().getRankMail(a_id, mailInfo))
				break;

			for(BSLib::uint32 i = 1; i <= rankPrizeSize(a_id); i++)
			{	
				SRoleKey key;
				if( !obj->getRole(i, key))
					break;

				SRankPosInfo* info = NULL;
				if( !CRankConfig::singleton().getRankPrize(a_id, i, info))
					break;

				MailSystem::SRoleGuid role(key.getAccountID(), key.getZoneID(), key.getIndex());
				std::vector<MailSystem::SRoleGuid> roles;
				roles.push_back(role);
				std::string content(mailInfo->m_content);
				std::string::size_type pos = content.find("*");
				if( pos != std::string::npos)
				{
					std::string strPos = BSLib::Utility::CConvert::toStringA(i);
					content.replace(pos, 1, strPos);
				}

				std::vector<BSLib::uint32> types;
				std::vector<BSLib::uint32> ids;
				std::vector<BSLib::uint32> nums;
				ids.push_back(105);
				nums.push_back(GetGuangZiLiPrize(i));
				MailSystem::CN::CMailSystemCN::singleton().mailSend(mailInfo->m_sender, roles, MailSystem::EMailTypeSelf, mailInfo->m_title, content, 
					types, ids, nums);
			}

		} while (false);
	}
	else if( a_id > ERANKID_END && a_id < 0x80000000)
	{
		do 
		{	
			SRankMailInfo* mailInfo = NULL;
			if( !CRankConfig::singleton().getRankMail(a_id, mailInfo))
				break;

			for(BSLib::uint32 i = 1; i <= rankPrizeSize(a_id); i++)
			{	
				SRoleKey key;
				if( !obj->getRole(i, key))
					break;

				SRankPosInfo* info = NULL;
				if( !CRankConfig::singleton().getRankPrize(a_id, i, info))
					break;

				MailSystem::SRoleGuid role(key.getAccountID(), key.getZoneID(), key.getIndex());
				std::vector<MailSystem::SRoleGuid> roles;
				roles.push_back(role);
				std::string content(mailInfo->m_content);
				std::string::size_type pos = content.find("*");
				if( pos != std::string::npos)
				{
					std::string strPos = BSLib::Utility::CConvert::toStringA(i);
					content.replace(pos, 1, strPos);
				}

				std::vector<BSLib::uint32> types;
				MailSystem::CN::CMailSystemCN::singleton().mailSend(mailInfo->m_sender, roles, MailSystem::EMailTypeSelf, mailInfo->m_title, content, 
					types, info->m_ids, info->m_nums);
			}

		} while (false);
	}

	switch(a_id)
	{
	case ERANKID_ARENA:
		break;

	case ERANKID_INFINITE:
		obj->reset();
		break;

	case ERANKID_PLAYER_ACTIVITY:
		obj->reset();
		break;

	case ERANKID_POWER:
		break;
	default:
		obj->reset();
	}
}

void CRankSystemCN::initRankTimer()
{
	std::vector<Rank*>::iterator it = m_rankContainer.begin();
	for(; it != m_rankContainer.end(); ++it)
	{
		STimeHandle handle;
		if(rankTimeHandle( (*it)->getId(), handle))
			m_dateTimer.addTimer(handle, this);
	}
}

bool CRankSystemCN::rankTimeHandle(BSLib::uint64 a_id, STimeHandle& a_handle)
{
	a_handle.m_id = (BSLib::uint32)a_id;
	if(ERANKID_ARENA == a_id)
	{
		a_handle.m_type = EDATETIMER_DAILY;
		a_handle.m_hour = 00;
		a_handle.m_minute = 00;
		return true;
	}
	else if(ERANKID_INFINITE == a_id)
	{
		a_handle.m_type = EDATETIMER_WEEKLY;
		a_handle.m_day = 1;
		a_handle.m_hour = 14;
		a_handle.m_minute = 4;
		return true;
	}
	else if(a_id > ERANKID_END && a_id < 0x80000000)
	{
		a_handle.m_type = EDATETIMER_DAILY;
		a_handle.m_hour = 00;
		a_handle.m_minute = 00;
		return true;
	}

	return false;
}

bool CRankSystemCN::exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value)
{	
	BSLib::Utility::CStream stream;
	a_value->serializeTo(stream);
	BSLib::Utility::CStream copyStream;
	stream.copyTo(copyStream);
	Rank * obj = CreateRank(copyStream);
	if( NULL == obj)
		return false;

	obj->serializeFrom(stream);
	m_rankContainer.push_back(obj);
	return true;
}

bool CRankSystemCN::_cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, DBSystem::CKeyTablePtr& a_keyTable,
										  EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	// 只加载, 不保存
	if(EDBTABLEID_RANK_DATA == a_tableID){
		a_keyTable->traversal(*this);
		m_outputTablePtr = a_keyTable;
	}
	
	 initRankTimer();

	 // 首次初始化...
	 if(m_rankContainer.empty())
	 {
		 m_rankContainer.push_back(new TranspositionRank(ERANKID_ARENA, rankCapacity(ERANKID_ARENA)));
		 m_rankContainer.push_back(new BucketRank(ERANKID_INFINITE, rankCapacity(ERANKID_INFINITE)));
		 m_rankContainer.push_back(new BucketRank(ERANKID_PLAYER_ACTIVITY, rankCapacity(ERANKID_PLAYER_ACTIVITY)));
		 m_rankContainer.push_back(new OrderedRank(ERANKID_POWER, rankCapacity(ERANKID_POWER)));
		 m_rankContainer.push_back(new OrderedRank(ERANKID_LEVEL, rankCapacity(ERANKID_LEVEL)));
	 }
	

	 BSLib::Utility::CTimerServer* timeServer = _getTimerServer();
	 timeServer->addTimer(&CRankSystemCN::_cbSaveTimer, this, BSLib::uint64(0), NULL,  5000, 5 * 1000);
	 timeServer->addTimer(&CRankSystemCN::_cbDateTimer, this, BSLib::uint64(0), NULL,  1000, 5 * 1000);

	return true;
}

}//CN

}//RankSystem

}//GSLib

