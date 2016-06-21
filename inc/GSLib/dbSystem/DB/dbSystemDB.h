#ifndef __GSLIB_DBSYSTEM_DB_DBSYSTEMDB_H__
#define __GSLIB_DBSYSTEM_DB_DBSYSTEMDB_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/database/dbParam.h>
#include <GSLib/dbTableID.h>
#include <GSLib/moduleType.h>
#include <GSLib/dbSystem/dbCommonSystem.h>
#include <GSLib/dbSystem/msgDBSystem.h>

namespace GSLib
{

namespace DBSystem
{

namespace DB
{
	
class CDBSystemDB : public CDBCommonSystem
{
private:
	struct SInitTableInfor
	{
		EDBTableID m_tableID;
		EModuleType m_moduleType;
		BSLib::uint16 m_funcType;
		GFLib::ServerType m_serverType;
        std::string m_strWhere;
	};

public:
	CDBSystemDB();
	virtual ~CDBSystemDB();

	BSLIB_SINGLETON_DECLARE(CDBSystemDB);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_DBSYSTEM; }

public:
	bool setInitTableByGlobal(GFLib::ServerType a_serverType, BSLib::uint16 a_funcType, EModuleType a_moduleType, EDBTableID a_tableID ,const std::string& a_strWhere = "");
	bool setInitTableByPlayer(GFLib::ServerType a_serverType, BSLib::uint16 a_funcType, EModuleType a_moduleType, EDBTableID a_tableID ,const std::string& a_strWhere = "");
	bool setInitTableByRole(GFLib::ServerType a_serverType, BSLib::uint16 a_funcType, EModuleType a_moduleType, EDBTableID a_tableID ,const std::string& a_strWhere = "");

public:
	bool loadInitTableByPlayer(const std::string& a_tabkeKey, const std::string& a_tableIndex);
	bool loadInitTableByRole(const std::string& a_sqlWhere);

    virtual bool selectTableData(const GSLib::SRoleKey& a_roleKey, const std::string& a_tableKey, const std::string& a_tableIndex, EDBTableID a_tableID, EModuleType a_moduleType = EMODULECTYPE_NULL, BSLib::uint32 a_sessionID = 0, BSLib::uint16 a_funcType = GFLib::EFUNCTYPE_NULL, const std::string& a_strWhere = "");
    virtual bool selectTableDatas(const GSLib::SRoleKey& a_srcRoleKey,EModuleType a_srcModuleType,BSLib::uint32 a_sessionID,void* a_ptr,std::vector<GSLib::DBSystem::SReqTablesData> a_selectDataArray);

	virtual bool updateTableData(const std::string& a_tabkeKey, const std::string& a_tableIndex, const std::string& a_name, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, bool a_needSave = false);
	virtual bool updateTableData(const std::string& a_tabkeKey, const std::string& a_tableIndex, const std::string& a_name, EDBTableID a_tableID, void* a_data, BSLib::uint32 a_dataSize, bool a_needSave = false);

	virtual bool removeTableData(BSLib::Utility::CStream& a_steam, EDBTableID a_tableID, bool a_needSave = false);
	virtual bool removeTableData(const std::string& a_tabkeKey, const std::string& a_tableIndex, EDBTableID a_tableID, bool a_needSave = false);

	virtual bool saveTableData(const std::string& a_tabkeKey, const std::string& a_tableIndex, EDBTableID a_tableID);
	virtual void saveAllTableData(const std::string& a_tabkeKey);

	virtual bool closeTableData(const std::string& a_tabkeKey, const std::string& a_tableIndex, EDBTableID a_tableID);

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

private:
	bool _loadInitTableByGlobal();
	bool _loadInitTableByPlayer();
	bool _loadInitTableByRole();
	bool _selectTableCommand(GFLib::SNetMsgLabel* a_msgLabel, CMsgLoginSystemXS2DBReqSelectTableData* a_reqSelectTableData);

private:
	bool _tick1000(BSLib::uint64 a_para1, void* a_para2);

private:
	void _onMsgDBSystemXS2DBReqSelectTableData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgDBSystemXS2DBReqSelectGlobalTableData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    void _onMsgDBSystemXS2DBReqSelectGlobalMultiTableData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
    
	void _onMsgDBSystemXS2DBNtfUpdateTableData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgDBSystemXS2DBNtfSaveTableData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgDBSystemXS2DBNtfRemoveTableData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgDBSystemXS2DBNtfCloseTableData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	void _onMsgDBSystemCH2DBNtfCharge(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

private:
	std::list<SInitTableInfor> m_initTableByGlobal;
	std::list<SInitTableInfor> m_initTableByPlayer;
	std::list<SInitTableInfor> m_initTableByRole;
	BSLib::Utility::TimerHandle m_tick1000Handle;
	EDBTableID m_currentTableID;
};


}//DB

}//DBSystem

}//GSLib

#endif//__GSLIB_DBSYSTEM_DB_DBSYSTEMDB_H__
