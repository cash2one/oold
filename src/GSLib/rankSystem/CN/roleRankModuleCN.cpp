#include <GSLib/rankSystem/CN/roleRankModuleCN.h>
#include <GSLib/rankSystem/CN/msgRankSystemCN.h>
#include <GSLib/playerSystem/CN/playerCN.h>
#include <GSLib/rankSystem/CN/rankSystemCN.h>
#include <GSLib/rankSystem/GM/msgRankSystemGM.h>
#include <GSLib/rankSystem/msgRankSystemGC.h>
#include <BSLib/utility/dateTime.h>

namespace GSLib
{
namespace RankSystem
{

namespace CN
{

CRoleRankModuleCN::CRoleRankModuleCN(GSLib::PlayerSystem::CN::CRoleCN* a_roleCN, EModuleType a_moduleType)
	:GSLib::PlayerSystem::CN::CRoleModuleCN(a_roleCN, a_moduleType)
{

}

CRoleRankModuleCN::~CRoleRankModuleCN()
{

}

void CRoleRankModuleCN::preInit(bool isFirst)
{

}

void CRoleRankModuleCN::postInit(bool isFirst)
{
	if(!isFirst)
		return;
	
	m_roleRankCN.m_role = getRoleCN()->getRoleKey();
	_dbUpdate();
}

void CRoleRankModuleCN::initToClient()
{

// 	Rank* obj = CRankSystemCN::singleton().getRank(ERANKID_ARENA);
// 	if( NULL == obj)
// 		return;
// 	
// 	SRoleKey key = getRoleCN()->getRoleKey();
// 	obj->update(key, SRoleKey(0, 0, 0));
// 
// 	SRoleKey a1(10007234, 23, 0);
// 	SRoleKey b1(10007917, 23, 0);
// 	obj->update(key, b1);

// 	SRoleKey a2(10007252, 23, 0);
// 	SRoleKey b2(10007235, 23, 0);
// 	obj->update(a2, b2);
// 
// 	SRoleKey a3(10007236, 23, 0);
// 	SRoleKey b3(10007237, 23, 0);
// 	obj->update(a3, b3);
// 
// 	SRoleKey a4(10007250, 23, 0);
// 	SRoleKey b4(10007189, 23, 0);
// 	obj->update(a4, b4);

	Rank * obj = CRankSystemCN::singleton().getRank(ERANKID_ARENA);
	if( NULL == obj)
		return;

	if(0 == obj->getSize())
	{
		SRoleKey key = getRoleCN()->getRoleKey();
		SRoleKey roleKey = SRoleKey(0, 0, 0);
		obj->update(key, roleKey);
	}
}

void CRoleRankModuleCN::init(bool isFirst)
{
}

void CRoleRankModuleCN::final()
{

}

void CRoleRankModuleCN::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDRankSystemGC2CNReqRankList, 
		&BSLib::Framework::CreateCMessage<CMsgRankSystemGC2CNReqRankList>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDRankSystemGC2CNReqRankList, &CRoleRankModuleCN::_onMsgRankSystemGC2CNReqRankList, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDRankSystemGM2CNNtfUpdate, 
		&BSLib::Framework::CreateCMessage<CMsgRankSystemGM2CNNtfUpdate>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDRankSystemGM2CNNtfUpdate, &CRoleRankModuleCN::_onMsgRankSystemGM2CNNtfUpdate, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDRankSystemGM2CNNtfInitFinish, 
		&BSLib::Framework::CreateCMessage<CMsgRankSystemGM2CNNtfInitFinish>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDRankSystemGM2CNNtfInitFinish, &CRoleRankModuleCN::_onMsgRankSystemGM2CNNtfInitFinish, this);
}

void CRoleRankModuleCN::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	a_msgExecMgr->delMsgExecPtr(MsgIDRankSystemGC2CNReqRankList);
	a_msgExecMgr->delMsgExecPtr(MsgIDRankSystemGM2CNNtfUpdate);
}

void CRoleRankModuleCN::updateDataToDB()
{

}

void CRoleRankModuleCN::cbSelectTableData(BSLib::uint32 a_sessionID, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream)
{

}

void CRoleRankModuleCN::synPlaceToGM(BSLib::uint32 a_id)
{
	Rank * obj = CRankSystemCN::singleton().getRank(a_id);
	if( NULL == obj)
		return;

	SRoleKey key = getRoleCN()->getRoleKey();
	BSLib::uint32 place = obj->getPlace(key);
	if( 0 == place)
		return;

	CMsgRankSystemCN2GMNtfPlace ntf;
	ntf.m_id = a_id;
	ntf.m_place =  place;
	sendMsgToGameServer(ntf);
}

bool CRoleRankModuleCN::_dbUpdate()
{	
	if(m_keyTableCNPtr == NULL)
		return false;

	BSLib::Utility::CStream stream;
	m_roleRankCN._serializeTo(stream);
	m_keyTableCNPtr->update(stream);
	return m_keyTableCNPtr->saveDataToDBServer(m_roleRankCN.m_role.getDBKey(), true);
}


bool CRoleRankModuleCN::exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value)
{
	using namespace BSLib::Database;
	BSLib::Utility::CStream stream;
	a_value->serializeTo(stream);
	m_roleRankCN._serializeFrom(stream);
	return true;
}

bool CRoleRankModuleCN::cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
	if(EDBTABLEID_ROLE_RANK_CN_DATA == a_tableID){
		a_keyTable->traversal(*this);
		m_keyTableCNPtr = a_keyTable;
	}

	return true ;
}

void CRoleRankModuleCN::_onMsgRankSystemGM2CNNtfInitFinish(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	synPlaceToGM(ERANKID_ARENA);
}

void CRoleRankModuleCN::_onMsgRankSystemGM2CNNtfUpdate(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgRankSystemGM2CNNtfUpdate *req = (CMsgRankSystemGM2CNNtfUpdate *)a_msg;
// 	if( req->m_id >= ERANKID_END)
// 		return;
	
	SRoleKey key = getRoleCN()->getRoleKey();
	
	if( req->m_id > ERANKID_END)
	{	
		BSLib::uint32 todayId = req->m_id;
		BSLib::uint32 totalId = req->m_id + 0x80000000;
		Rank * todayObj = CRankSystemCN::singleton().getRank(todayId);
		if( NULL == todayObj)
		{	
			todayObj = CRankSystemCN::singleton().regRank(todayId, ERANKTYPE_ORDEREDLESS);
		}
		todayObj->update(key, req->m_Param);

		Rank * allObj = CRankSystemCN::singleton().getRank(totalId);
		if(NULL == allObj)
		{
			allObj = CRankSystemCN::singleton().regRank(totalId, ERANKTYPE_ORDEREDLESS);
		}

		allObj->update(key, req->m_Param);
		return;
	}
	
	Rank * obj = CRankSystemCN::singleton().getRank(req->m_id);
	if( NULL == obj)
	{
		return;
	}

	
	switch(obj->getId())
	{
	case ERANKID_ARENA:
		obj->update(key, req->m_key);
		break;

	case ERANKID_INFINITE:
		{	
			// 更新时间, 重置sum 结果
			if(m_roleRankCN.m_infiniteRefreshTime != obj->getRefreshTime())
			{
				m_roleRankCN.m_infinite = 0;
				m_roleRankCN.m_infiniteRefreshTime = obj->getRefreshTime();
			}
			
			// 累加
			BSLib::int32 preParam = m_roleRankCN.m_infinite;
			BSLib::int32 curParam = preParam + req->m_Param;
			m_roleRankCN.m_infinite = curParam;
			_dbUpdate();

			obj->update(key, preParam, curParam);
		}
		break;

	case ERANKID_POWER:
		obj->update(key, req->m_Param);
		break;

	case ERANKID_PLAYER_ACTIVITY:
		// todo 
		break;

	case ERANKID_LEVEL:
		obj->update(key, req->m_Param);
		break;
	}
}

void CRoleRankModuleCN::_onMsgRankSystemGC2CNReqRankList(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgRankSystemGC2CNReqRankList *req = (CMsgRankSystemGC2CNReqRankList *)a_msg;
	CMsgRankSystemCN2GCAckGetRankList ack;
	ack.m_id = req->m_id;
	ack.m_type = req->m_type;

	do 
	{
// 		if( req->m_id >= ERANKID_END)
// 			break;
		if( 1 != req->m_type && 2 != req->m_type)
			break;
		
		Rank * obj = CRankSystemCN::singleton().getRank(req->m_id);
		if( NULL == obj)
			break;

		SRoleKey key(0, 0, 0);
		if( 2 == req->m_type)
			key = getRoleCN()->getRoleKey();
		
		BSLib::int32 curParam = req->m_param;
		if(ERANKID_INFINITE == req->m_id)
		{
			curParam = m_roleRankCN.m_infinite;
		}

		obj->getState(key, ack.m_list, curParam);

	} while (false);

	sendMsgToClient(ack);
}



}
}
}