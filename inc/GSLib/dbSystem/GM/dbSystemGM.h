//////////////////////////////////////////////////////////////////////
//	created:	2014/08/05
//	filename: 	GSLib\dbSystem\GM\dbSystemGM.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_DBSYSTEM_GM_DBSYSTEMGM_H__
#define __GSLIB_DBSYSTEM_GM_DBSYSTEMGM_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>
#include <GSLib/dbTableID.h>
#include <GSLib/moduleType.h>

namespace GSLib
{

namespace DBSystem
{

namespace GM
{

class CDBSystemGM : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CDBSystemGM();
	virtual ~CDBSystemGM();

	BSLIB_SINGLETON_DECLARE(CDBSystemGM);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_DBSYSTEM; }

protected:
	virtual bool _init();
	virtual void _final();
	virtual bool _loadGameConfig(const std::string& a_configPath);
	virtual bool _initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual bool _postStartSystem();
	virtual void _cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void _cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);

	virtual bool _cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
	virtual bool _cbSelectKeyIndexTableData(const GSLib::SRoleKey& a_roleKey, CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);

    virtual bool _cbSelectGlobalKeyTableData(const GSLib::SRoleKey& a_srcRoleKey, const GSLib::SRoleKey& a_roleKey, CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
    virtual bool _cbSelectGlobalKeyIndexTableData(const GSLib::SRoleKey& a_srcRoleKey, const GSLib::SRoleKey& a_roleKey, CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
    virtual bool _cbSelectGlobalMultiTableData(const GSLib::SRoleKey& a_srcRoleKey,EModuleType a_srcModuleType, BSLib::uint32 a_sessionID,void* a_ptr,BSLib::uint32 a_state,std::vector<SSelectTablesResult>& a_ackSelectTablesResultArray,std::vector<CKeyTablePtr>& a_keyTablePtrArray,std::vector<CKeyIndexTablePtr>& a_keyIndexTablePtrArray);

private:
	void _onMsgDBSystemDB2XSAckSelectTableData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgDBSystemDB2XSAckSelectGlobalTableData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgDBSystemDB2XSAckSelectGlobalMultiTableData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

    
};

}//GM

}//DBSystem

}//GSLib

#endif//__GSLIB_DBSYSTEM_GM_DBSYSTEMGM_H__
