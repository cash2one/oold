#include <GFLib/commonServer/commonSystemMgr.h>
#include <GSLib/tracer.h>
#include <GSLib/dbSystem/CN/dbSystemCN.h>

namespace GSLib
{

namespace DBSystem
{	

namespace CN
{

BSLIB_SINGLETON_DEFINE(CDBSystemCN);

CDBSystemCN::CDBSystemCN()
{
	;
}

CDBSystemCN::~CDBSystemCN()
{
	;
}

bool CDBSystemCN::_init()
{
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CDBSystemCN::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CDBSystemCN::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_loadGameConfig(a_configPath);
}

bool CDBSystemCN::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDDBSystemDB2XSAckSelectTableData, &BSLib::Framework::CreateCMessage<CMsgLoginSystemDB2XSAckSelectTableData>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDDBSystemDB2XSAckSelectTableData, &CDBSystemCN::_onMsgDBSystemDB2XSAckSelectTableData, this);

	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_initServerMsg(a_msgExecMgr);
}

bool CDBSystemCN::_ICommonSystem_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_ICommonSystem_startSystem();
}

bool CDBSystemCN::_ICommonSystem_postStartSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_ICommonSystem_postStartSystem();
}

void CDBSystemCN::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerEnter(a_serverID, a_key);

	if (a_serverID.getServerType() == GSLib::SRVTYPE_DATASERVER) {
        if (!selectTableData("", GSLib::EDBTABLEID_COMMAND_INIT_SERVER,EMODULECTYPE_NULL,GSLIB_SESSIONID_INIT_GLOBALDATA,GFLib::EFUNCTYPE_NULL)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "从DB获取Server数据失败");
			return ;
		}
	}
}

void CDBSystemCN::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerLeave(a_serverID, a_key);
}

bool CDBSystemCN::_cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	switch(a_tableID)
	{
	case EDBTABLEID_COMMAND_INIT_SERVER_FINSH:
		BSLIB_LOG_DEBUG(ETT_GSLIB_DBSYSTEM, "DB推送Server数据完成");
		return true;
	default:
		;
	}
	return GSLib::DBSystem::CDBCommonSystem::_cbSelectKeyTableData(a_roleKey, a_keyTable, a_tableID, a_moduleType, a_sessionID);
}

bool CDBSystemCN::_cbSelectKeyIndexTableData(const GSLib::SRoleKey& a_roleKey, CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	return GSLib::DBSystem::CDBCommonSystem::_cbSelectKeyIndexTableData(a_roleKey, a_keyTable, a_tableID, a_moduleType, a_sessionID);
}

void CDBSystemCN::_onMsgDBSystemDB2XSAckSelectTableData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgLoginSystemDB2XSAckSelectTableData* ackSelectData = (CMsgLoginSystemDB2XSAckSelectTableData*)a_msg;

	if (ackSelectData->m_funcType == GFLib::EFUNCTYPE_NULL || ackSelectData->m_funcType == ICommonSystem_getFuncType()){
		cbSelectTableData(ackSelectData->m_roleKey, ackSelectData->m_moduleType, ackSelectData->m_tableID, ackSelectData->m_stream, ackSelectData->m_sessionID);
		return ;
	}
	GFLib::CommonServer::ICommonSystem* commonSystem = NULL;
	if (ackSelectData->m_moduleType == GSLib::EMODULECTYPE_NULL) {
		commonSystem = GFLib::CommonServer::CCommonSystemMgr::singleton().getSystem(ackSelectData->m_funcType);
		if (commonSystem == NULL) {
			BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select返回数据失败,没有找到相应的系统[FuncType=%d][TableID=%d]", ackSelectData->m_funcType, ackSelectData->m_tableID);
			return ;
		}
		if (commonSystem->ICommonSystem_getFuncType() != ackSelectData->m_funcType) {
			BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select返回数据失败,功能模块不一致[FuncType=%d][TableID=%d]", ackSelectData->m_funcType, ackSelectData->m_tableID);
			return ;
		}

	} else {
		commonSystem = GFLib::CommonServer::CCommonSystemMgr::singleton().getSystem(GSLib::EFUNCTYPE_PLAYERSYSTEM);
		if (commonSystem == NULL) {
			BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select返回数据失败,没有找到相应的PlayerSystem系统[TableID=%d]", ackSelectData->m_tableID);
			return ;
		}
		if (commonSystem->ICommonSystem_getFuncType() != GSLib::EFUNCTYPE_PLAYERSYSTEM) {
			BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select返回数据失败,功能模块不一致[FuncType=%d][TableID=%d]", ackSelectData->m_funcType, ackSelectData->m_tableID);
			return ;
		}
	}

	GSLib::DBSystem::CDBCommonSystem* dbCommonSystem = dynamic_cast<GSLib::DBSystem::CDBCommonSystem*>(commonSystem);
	if (dbCommonSystem == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select返回数据失败,功能模块异常[FuncType=%d][TableID=%d]", ackSelectData->m_funcType, ackSelectData->m_tableID);
		return ;
	}
	BSLIB_LOG_DEBUG(ETT_GSLIB_DBSYSTEM, "select返回数据[FuncType=%d][TableID=%d]", ackSelectData->m_funcType, ackSelectData->m_tableID);

	dbCommonSystem->cbSelectTableData(ackSelectData->m_roleKey, ackSelectData->m_moduleType, ackSelectData->m_tableID, ackSelectData->m_stream, ackSelectData->m_sessionID);
}

}//CN

}//DBSystem

}//GSLib

