#include <GFLib/commonServer/serviceMgr.h>
#include <GFLib/commonServer/commonSystemMgr.h>
#include <GSLib/tracer.h>
#include <GSLib/dbSystem/GM/dbSystemGM.h>
#include <GSLib/dbSystem/msgDBSystem.h>
#include <GSLib/loginSystem/GM/netPlayerGMMgr.h>

namespace GSLib
{

namespace DBSystem
{	

namespace GM
{

BSLIB_SINGLETON_DEFINE(CDBSystemGM);

CDBSystemGM::CDBSystemGM()
{
	;
}

CDBSystemGM::~CDBSystemGM()
{
	;
}

bool CDBSystemGM::_init()
{
	return GSLib::DBSystem::CDBCommonSystem::_init();
}

void CDBSystemGM::_final()
{
	GSLib::DBSystem::CDBCommonSystem::_final();
}

bool CDBSystemGM::ICommonSystem_loadGameConfig(const std::string& a_configPath)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_loadGameConfig(a_configPath);
}

bool CDBSystemGM::ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDDBSystemDB2XSAckSelectTableData, &BSLib::Framework::CreateCMessage<CMsgLoginSystemDB2XSAckSelectTableData>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDDBSystemDB2XSAckSelectTableData, &CDBSystemGM::_onMsgDBSystemDB2XSAckSelectTableData, this);

    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDDBSystemDB2XSAckSelectGlobalTableData, &BSLib::Framework::CreateCMessage<CMsgLoginSystemDB2XSAckSelectGlobalTableData>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDDBSystemDB2XSAckSelectGlobalTableData, &CDBSystemGM::_onMsgDBSystemDB2XSAckSelectGlobalTableData, this);

    BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDDBSystemDB2XSAckSelectGlobalMultiTableData, &BSLib::Framework::CreateCMessage<CMsgLoginSystemDB2XSAckSelectGlobalMultiTableData>);
    GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDDBSystemDB2XSAckSelectGlobalMultiTableData, &CDBSystemGM::_onMsgDBSystemDB2XSAckSelectGlobalMultiTableData, this);

	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_initServerMsg(a_msgExecMgr);
}

bool CDBSystemGM::_ICommonSystem_startSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_ICommonSystem_startSystem();
}

bool CDBSystemGM::_ICommonSystem_postStartSystem()
{
	return GSLib::DBSystem::CDBCommonSystem::_ICommonSystem_postStartSystem();
}

void CDBSystemGM::ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerEnter(a_serverID, a_key);

	if (a_serverID.ICommonServer_getServerType() == GSLib::SRVTYPE_DATASERVER) {
		if (!selectTableData("", GSLib::EDBTABLEID_COMMAND_INIT_SERVER)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "从DB获取Server数据失败");
			return ;
		}
	}
}

void CDBSystemGM::ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key)
{
	return GSLib::DBSystem::CDBCommonSystem::ICommonSystem_cbServerLeave(a_serverID, a_key);
}

bool CDBSystemGM::_cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
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

bool CDBSystemGM::_cbSelectKeyIndexTableData(const GSLib::SRoleKey& a_roleKey, CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
	return GSLib::DBSystem::CDBCommonSystem::_cbSelectKeyIndexTableData(a_roleKey, a_keyTable, a_tableID, a_moduleType, a_sessionID);
}


bool CDBSystemGM::_cbSelectGlobalKeyTableData(const GSLib::SRoleKey& a_srcRoleKey,const GSLib::SRoleKey& a_roleKey, CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
    switch(a_tableID)
    {
    case EDBTABLEID_COMMAND_INIT_SERVER_FINSH:
        BSLIB_LOG_DEBUG(ETT_GSLIB_DBSYSTEM, "DB推送Server数据完成");
        return true;
	default:
		;
    }
    return GSLib::DBSystem::CDBCommonSystem::_cbSelectGlobalKeyTableData(a_srcRoleKey,a_roleKey, a_keyTable, a_tableID, a_moduleType, a_sessionID);
}

bool CDBSystemGM::_cbSelectGlobalKeyIndexTableData(const GSLib::SRoleKey& a_srcRoleKey,const GSLib::SRoleKey& a_roleKey, CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID)
{
    return GSLib::DBSystem::CDBCommonSystem::_cbSelectGlobalKeyIndexTableData(a_srcRoleKey,a_roleKey, a_keyTable, a_tableID, a_moduleType, a_sessionID);
}

bool CDBSystemGM::_cbSelectGlobalMultiTableData(const GSLib::SRoleKey& a_srcRoleKey,EModuleType a_srcModuleType,BSLib::uint32 a_sessionID,void* a_ptr,BSLib::uint32 a_state,std::vector<SSelectTablesResult>& a_ackSelectTablesResultArray,std::vector<CKeyTablePtr>& a_keyTablePtrArray,std::vector<CKeyIndexTablePtr>& a_keyIndexTablePtrArray)
{
    return GSLib::DBSystem::CDBCommonSystem::_cbSelectGlobalMultiTableData(a_srcRoleKey,a_srcModuleType,a_sessionID,a_ptr,a_state,a_ackSelectTablesResultArray,a_keyTablePtrArray,a_keyIndexTablePtrArray);
}

void CDBSystemGM::_onMsgDBSystemDB2XSAckSelectTableData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
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

void CDBSystemGM::_onMsgDBSystemDB2XSAckSelectGlobalTableData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgLoginSystemDB2XSAckSelectGlobalTableData* ackSelectData = (CMsgLoginSystemDB2XSAckSelectGlobalTableData*)a_msg;

    if (ackSelectData->m_funcType == GFLib::EFUNCTYPE_NULL || ackSelectData->m_funcType == ICommonSystem_getFuncType()){
        cbSelectGlobalTableData(ackSelectData->m_srcRoleKey,ackSelectData->m_roleKey, ackSelectData->m_moduleType, ackSelectData->m_tableID, ackSelectData->m_stream, ackSelectData->m_sessionID);
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

    dbCommonSystem->cbSelectGlobalTableData(ackSelectData->m_srcRoleKey,ackSelectData->m_roleKey, ackSelectData->m_moduleType, ackSelectData->m_tableID, ackSelectData->m_stream, ackSelectData->m_sessionID);
}


void CDBSystemGM::_onMsgDBSystemDB2XSAckSelectGlobalMultiTableData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
    CMsgLoginSystemDB2XSAckSelectGlobalMultiTableData* ackSelectData = (CMsgLoginSystemDB2XSAckSelectGlobalMultiTableData*)a_msg;
    GFLib::CommonServer::ICommonSystem* commonSystem = GFLib::CommonServer::CCommonSystemMgr::singleton().getSystem(GSLib::EFUNCTYPE_PLAYERSYSTEM);
    if (commonSystem == NULL) {
        //BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select返回数据失败,没有找到相应的PlayerSystem系统[TableID=%d]", ackSelectData->m_tableID);
        return ;
    }
    if (commonSystem->ICommonSystem_getFuncType() != GSLib::EFUNCTYPE_PLAYERSYSTEM) {
        BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select返回数据失败,功能模块不一致[m_sessionID=%d][m_state=%d]", ackSelectData->m_sessionID, ackSelectData->m_state);
        return ;
    }

    GSLib::DBSystem::CDBCommonSystem* dbCommonSystem = dynamic_cast<GSLib::DBSystem::CDBCommonSystem*>(commonSystem);
    if (dbCommonSystem == NULL) {
        BSLIB_LOG_ERROR(ETT_GSLIB_DBSYSTEM, "select返回数据失败,功能模块异常[m_sessionID=%d][m_state=%d]", ackSelectData->m_sessionID, ackSelectData->m_state);
        return ;
    }
    BSLIB_LOG_DEBUG(ETT_GSLIB_DBSYSTEM, "_onMsgDBSystemDB2XSAckSelectGlobalMultiTableData select返回数据[m_sessionID=%d][m_state=%d]", ackSelectData->m_sessionID, ackSelectData->m_state);

    std::vector<GSLib::DBSystem::SAckTablesData> ackTablesDataArray;
    ackTablesDataArray.clear();
    for(BSLib::uint32 i=0; i<ackSelectData->m_tableCount; ++i){
        GSLib::DBSystem::SAckTablesData data;
        memset((void*)&data,0,sizeof(GSLib::DBSystem::SAckTablesData));
        data.serializeFrom(ackSelectData->m_stream);
        ackTablesDataArray.push_back(data);
    }
    dbCommonSystem->cbSelectGlobalMultiTableData(ackSelectData->m_srcRoleKey,ackSelectData->m_srcModuleType,ackSelectData->m_sessionID,ackSelectData->m_ptr,ackSelectData->m_state, ackTablesDataArray);
}

}//GM

}//DBSystem

}//GSLib

