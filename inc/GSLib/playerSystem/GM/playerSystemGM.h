#ifndef __GSLIB_PLAYERSYSTEM_GM_PLAYERSYSTEMGM_H__
#define __GSLIB_PLAYERSYSTEM_GM_PLAYERSYSTEMGM_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>
#include <GSLib/dbSystem/keyIndexTable.h>
#include <GSLib/dbSystem/keyTable.h>
#include <GSLib/playerSystem/GM/playerGMMgr.h>
namespace GSLib
{

namespace PlayerSystem
{

namespace GM
{

class CPlayerSystemGM : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CPlayerSystemGM();
	virtual ~CPlayerSystemGM();

	BSLIB_SINGLETON_DECLARE(CPlayerSystemGM);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_PLAYERSYSTEM; }

protected:
	virtual bool _init();
	virtual void _final();
	virtual bool ICommonServer_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _initCommand(BSLib::Utility::CCmdExecMgr* a_cmdExecMgr);

	virtual bool _startSystem();
	virtual void ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);

protected:
	virtual bool _cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
	virtual bool _cbSelectKeyIndexTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);

    virtual bool _cbSelectGlobalKeyTableData(const GSLib::SRoleKey& a_srcRoleKey, const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
    virtual bool _cbSelectGlobalKeyIndexTableData(const GSLib::SRoleKey& a_srcRoleKey, const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
    virtual bool _cbSelectGlobalMultiTableData(const GSLib::SRoleKey& a_srcRoleKey,EModuleType a_srcModuleType, BSLib::uint32 a_sessionID,void* a_ptr,BSLib::uint32 a_state,std::vector<GSLib::DBSystem::SSelectTablesResult>& a_ackSelectTablesResultArray,std::vector<GSLib::DBSystem::CKeyTablePtr>& a_keyTablePtrArray,std::vector<GSLib::DBSystem::CKeyIndexTablePtr>& a_keyIndexTablePtrArray);

public:
    BSLib::Utility::CTimerServer* getTimerServer() { return _getTimerServer();}

    void update(BSLib::uint64 a_delayMilliseconds);
private:
	void _onMsgPlayerSystem(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg);

private:
    CRoleGM* getRoleByCmd(BSLib::Utility::CProperties& a_properties) const;
    
	int _onCmdTest(BSLib::Utility::CProperties& a_properties, void* a_tempPara);
	int _onCmdAddGold(BSLib::Utility::CProperties& a_properties, void* a_tempPara);
    int _onCmdAddExp(BSLib::Utility::CProperties& a_properties, void* a_tempPara);
    int _onCmdAddDiamond(BSLib::Utility::CProperties& a_properties, void* a_tempPara); 
	int _onCmdAddItem(BSLib::Utility::CProperties& a_properties, void* a_tempPara);
    int _onCmdUpdateLevel(BSLib::Utility::CProperties& a_properties, void* a_tempPara);
    int _onCmdSetVIPLevel(BSLib::Utility::CProperties& a_properties, void* a_tempPara);

    bool _initEvent();
    void _onEventAchieveUpdate(BSLib::Utility::EventID& a_eventID, BSLib::Utility::CStream& a_stream);

private:
    BSLib::Database::CDbConnection m_dbConnection;
};

}//GM

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_GM_PLAYERSYSTEMGM_H__

