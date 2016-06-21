#include <GSLib/rankSystem/GM/roleRankModule.h>
#include <GSLib/rankSystem/msgRankSystem.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <BSLib/utility/random.h>

namespace GSLib
{

namespace RankSystem
{

namespace GM
{

CRoleRankModule::CRoleRankModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType)
:  GSLib::PlayerSystem::GM::CRoleModuleGM(a_roleGM, a_moduleType)
{
	m_place = 0;
}

CRoleRankModule::~CRoleRankModule()
{
	;
}

void CRoleRankModule::preInit(bool isFirst)
{
	;
}

void CRoleRankModule::postInit(bool isFirst)
{
	if(!isFirst)
		return;

	m_roleRank.m_role = getRoleGM()->getRoleKey();
	_dbUpdate();
}

void CRoleRankModule::initToClient()
{
	//update(ERANKID_INFINITE, BSLib::Utility::CRandom::randomBetween(1, 10));
	CMsgRankSystemGM2CNNtfInitFinish ntf;
	sendMsgToCenterServer(ntf);
	//update(110001, BSLib::Utility::CRandom::randomBetween(1, 100));
}

void CRoleRankModule::final()
{
	;
}

void CRoleRankModule::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDRankSystemCN2GMNtfPlace, &BSLib::Framework::CreateCMessage<CMsgRankSystemCN2GMNtfPlace>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDRankSystemCN2GMNtfPlace, &CRoleRankModule::_onMsgRankSystemCN2GMNtfPlace, this);
}

void CRoleRankModule::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	a_msgExecMgr->delMsgExecPtr(MsgIDRankSystemCN2GMNtfPlace);
}

void CRoleRankModule::updateDataToDB()
{
	;
}

bool CRoleRankModule::cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{	
	if(EDBTABLEID_ROLE_RANK_DATA == a_tableID){
		a_keyTable->traversal(*this);
		m_keyTablePtr = a_keyTable;
	}

	return true ;
}

bool CRoleRankModule::exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value)
{	
	using namespace BSLib::Database;
	BSLib::Utility::CStream stream;
	a_value->serializeTo(stream);
	m_roleRank._serializeFrom(stream);
	return true;
}

void CRoleRankModule::update(BSLib::uint32 a_id, BSLib::int32 a_param)
{
	CMsgRankSystemGM2CNNtfUpdate ntf;
	ntf.m_id = a_id;
	ntf.m_Param = a_param;

	sendMsgToCenterServer(ntf);
}

void CRoleRankModule::updateArena(const SRoleKey& a_opponent)
{
	CMsgRankSystemGM2CNNtfUpdate ntf;
	ntf.m_id = ERANKID_ARENA;
	ntf.m_key = a_opponent;

	sendMsgToCenterServer(ntf);
}

BSLib::uint32 CRoleRankModule::getPlace(BSLib::uint32 a_id)
{
	return 0;
}

bool CRoleRankModule::_dbUpdate()
{	
	if(m_keyTablePtr == NULL)
		return false;

	BSLib::Utility::CStream stream;
	m_roleRank._serializeTo(stream);
	m_keyTablePtr->update(stream);
	return m_keyTablePtr->saveDataToDBServer(m_roleRank.m_role.getDBKey(), true);
}


void CRoleRankModule::_onMsgRankSystemGC2GMReqGetRankData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
// 	if (a_msg == NULL) {
// 		return;
// 	}
// 
// 	EGetRankDataResult result(EGET_RANK_DATA_RESULT_SUCCESS);
// 	CMsgRankSystemGC2GMReqGetRankData *msgReq = (CMsgRankSystemGC2GMReqGetRankData *)a_msg;
// 	ERankType rankType = msgReq->m_rankType;
// 	if ( rankType < ERANK_TYPE_ARENA || rankType >= ERANK_TYPE_MAX) {
// 		result = EGET_RANK_DATA_RESULT_FAIL;
// 	}
// 
// 	CMsgRankSystemGM2GCAckGetRankData msgAck;
// 	msgAck.m_result = EGET_RANK_DATA_RESULT_SUCCESS;
// 	msgAck.m_rankType = ERANK_TYPE_ARENA;
// 	msgAck.m_vecRankData = CRankMgr::singleton().getArenaRankData();
// 
// 	sendMsgToClient(msgAck);
}

void CRoleRankModule::_onMsgRankSystemCN2GMNtfPlace(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgRankSystemCN2GMNtfPlace *req = (CMsgRankSystemCN2GMNtfPlace *)a_msg;
	if(req->m_id == ERANKID_ARENA)
		m_place = req->m_place;
}


}//GM

}//RankSystem

}//GSLib
