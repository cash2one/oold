//////////////////////////////////////////////////////////////////////
//	created:	2014/10/28
//	filename: 	GSLib\dbSystem\dbCommonSystem.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_DBSYSTEM_DBCOMMONSYSTEM_H__
#define __GSLIB_DBSYSTEM_DBCOMMONSYSTEM_H__

#include <BSLib/database/dbParam.h>
#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/dbTableID.h>
#include <GSLib/dbSystem/msgDBSystem.h>

namespace GSLib
{

namespace DBSystem
{

class CKeyTable;
class CKeyIndexTable;

typedef BSLib::Utility::CPointer<CKeyTable> CKeyTablePtr;
typedef BSLib::Utility::CPointer<CKeyIndexTable> CKeyIndexTablePtr;

enum ETableKeyType
{
	ETABLEKEYTYPE_NULL = 0,
	ETABLEKEYTYPE_KEY = 1,
	ETABLEKEYTYPE_KEY_INDEX,
};

enum EDBConnnectType
{
	EDBCNNCTTYPE_LOCAL = 0,
	EDBCNNCTTYPE_GLOBAL,
};

enum EDBTableDataType
{
    EDBDATA_EMPTY = 0,
    EDBDATA_NOT_EMPTY = 1,
};

enum EDBOptionType
{
    EDBOPTION_SUCCESS = 0,
    EDBOPTION_FAIL = 1,
};

struct SDbColumnInfor 
{
public:
	SDbColumnInfor()
		: m_tableID(EDBTABLEID_NULL), m_dbTableColumn(NULL), m_tableKeyType(ETABLEKEYTYPE_NULL), m_connectType(EDBCNNCTTYPE_LOCAL) {}

public:
	EDBTableID m_tableID;
	std::string m_dbTableName;
	const BSLib::Database::SDbColumn* m_dbTableColumn;
	ETableKeyType m_tableKeyType;
	EDBConnnectType m_connectType;
};

struct SAckTablesData
{
public:
    SAckTablesData()
        : m_roleKey(0,0,0)
        ,m_tableID(GSLib::EDBTABLEID_NULL)
        ,m_funcType(GFLib::EFUNCTYPE_NULL)
        ,m_moduleType(GSLib::EMODULECTYPE_NULL)
        ,m_status(0)
        ,m_size(0)
    {
        m_stream.reset();
    } 

    ~SAckTablesData()
    {
        m_stream.reset();
    } 

public:
    bool serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_roleKey;
        stream << m_tableID;
        stream << m_funcType;
        stream << m_moduleType;
        stream << m_status;
        stream << m_size;
        if(m_size == 0){
            return true;
        }
        stream << m_stream;
        return true;
    }

    bool serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_roleKey;
        stream >> m_tableID;
        stream >> m_funcType;
        stream >> m_moduleType;
        stream >> m_status;
        stream >> m_size;
        if(m_size == 0){
            return true;
        }
        m_stream.reset();
        m_stream.write((char*)stream.readPtr(), m_size);
        stream.readFlip(m_size);

        return true;
    }

public:
    GSLib::SRoleKey m_roleKey;
    GSLib::EDBTableID m_tableID;
    BSLib::uint16 m_funcType;
    GSLib::EModuleType m_moduleType;
    BSLib::uint32 m_status;
    BSLib::uint32 m_size;
    BSLib::Utility::CStream m_stream;
};


struct SReqTablesData
{
public:
    SReqTablesData()
    {
        clear();
    } 

    void clear()
    {
       m_roleKey.setIndex(0);
       m_roleKey.setAccountID(0);
       m_roleKey.setZoneID(0);
       m_tableKey="";
       m_tableIndex="";
       m_tableID = GSLib::EDBTABLEID_NULL;
       m_funcType = GFLib::EFUNCTYPE_NULL;
       m_moduleType = GSLib::EMODULECTYPE_NULL;
       m_strWhere = "";
    } 
public:
    bool serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_roleKey;
        stream << m_tableKey;
        stream << m_tableIndex;
        stream << m_tableID;
        stream << m_funcType;
        stream << m_moduleType;
        stream << m_strWhere;
        return true;
    }

    bool serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_roleKey;
        stream >> m_tableKey;
        stream >> m_tableIndex;
        stream >> m_tableID;
        stream >> m_funcType;
        stream >> m_moduleType;
        stream >> m_strWhere;
        return true;
    }
public:
    GSLib::SRoleKey m_roleKey;
    std::string m_tableKey;
    std::string m_tableIndex;
    GSLib::EDBTableID m_tableID;
    GSLib::EModuleType m_moduleType;
    BSLib::uint16 m_funcType;
    std::string m_strWhere;
};



struct SSelectTablesResult
{
public:
    SSelectTablesResult()
        : m_roleKey(0,0,INVALID_ROLEINDEX)
        ,m_tableID(GSLib::EDBTABLEID_NULL)
        ,m_funcType(GFLib::EFUNCTYPE_NULL)
        ,m_moduleType(GSLib::EMODULECTYPE_NULL)
        ,m_tableKeyType(GSLib::DBSystem::ETABLEKEYTYPE_NULL)
        ,m_status(0)
    {
    } 

public:
    GSLib::SRoleKey m_roleKey;
    GSLib::EDBTableID m_tableID;
    BSLib::uint16 m_funcType;
    GSLib::EModuleType m_moduleType;
    ETableKeyType m_tableKeyType;
    BSLib::uint32 m_status;
};

class CDBCommonSystem : public GFLib::CommonServer::CCommonSystem
{
public:
	CDBCommonSystem();
	virtual ~CDBCommonSystem();

	virtual BSLib::uint16 getFuncType() { return GFLib::EFUNCTYPE_NULL; }
	
public:
	//请求查询数据，回调函数_cbSelectKeyTableData或_cbSelectKeyIndexTableData
	bool selectTableData(const std::string& a_tableKey, EDBTableID a_tableID, EModuleType a_moduleType = EMODULECTYPE_NULL, BSLib::uint32 a_sessionID = 0, BSLib::uint16 a_funcType = GFLib::EFUNCTYPE_NULL, const std::string& a_strWhere = "");
	bool selectTableData(const GSLib::SRoleKey& a_roleKey, const std::string& a_tableKey, EDBTableID a_tableID, EModuleType a_moduleType = EMODULECTYPE_NULL, BSLib::uint32 a_sessionID = 0, BSLib::uint16 a_funcType = GFLib::EFUNCTYPE_NULL, const std::string& a_strWhere = "");
    bool selectGlobalTableData(const GSLib::SRoleKey& a_srcRoleKey,const GSLib::SRoleKey& a_roleKey, const std::string& a_tableKey, const std::string& a_tableIndex, EDBTableID a_tableID, EModuleType a_moduleType = EMODULECTYPE_NULL, BSLib::uint32 a_sessionID = 0, BSLib::uint16 a_funcType = GFLib::EFUNCTYPE_NULL, const std::string& a_strWhere = "");
    bool selectGlobalMultiTableData(const GSLib::SRoleKey& a_srcRoleKey,EModuleType a_srcModuleType,BSLib::uint32 a_sessionID,void* a_ptr,std::vector<SReqTablesData> a_selectDataArray);

    virtual bool selectTableData(const GSLib::SRoleKey& a_roleKey, const std::string& a_tableKey, const std::string& a_tableIndex, EDBTableID a_tableID, EModuleType a_moduleType = EMODULECTYPE_NULL, BSLib::uint32 a_sessionID = 0, BSLib::uint16 a_funcType = GFLib::EFUNCTYPE_NULL, const std::string& a_strWhere = "");

	//更新数据
	virtual bool updateTableData(const std::string& a_tabkeKey, const std::string& a_tableIndex, const std::string& a_name, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, bool a_needSave = false);
	virtual bool updateTableData(const std::string& a_tabkeKey, const std::string& a_tableIndex, const std::string& a_name, EDBTableID a_tableID, void* a_data, BSLib::uint32 a_dataSize, bool a_needSave = false);
	template<class T>
	bool updateTableData(const std::string& a_tabkeKey, const std::string& a_tableIndex, const std::string& a_name, EDBTableID a_tableID, T a_data, bool a_needSave = false)
	{
		return updateTableData(a_tabkeKey, a_tableIndex, a_name, a_tableID, &a_data, sizeof(T), a_needSave);
	}

	//删除多个数据 a_steam 是key和index组合
	virtual bool removeTableData(BSLib::Utility::CStream& a_steam, EDBTableID a_tableID, bool a_needSave = false);
	virtual bool removeTableData(const std::string& a_tabkeKey, const std::string& a_tableIndex, EDBTableID a_tableID, bool a_needSave = false);

	virtual bool saveTableData(const std::string& a_tabkeKey, const std::string& a_tableIndex, EDBTableID a_tableID);

	//清除，但不保存数据库
	virtual bool closeTableData(const std::string& a_tabkeKey, const std::string& a_tableIndex, EDBTableID a_tableID);
	
	const SDbColumnInfor* getDbColumnInfor(EDBTableID a_tableID);

	bool addDbColumn(EDBTableID a_tableID, const std::string& a_tableName, const BSLib::Database::SDbColumn* a_dbColumn, EDBConnnectType a_connectType = EDBCNNCTTYPE_LOCAL);

	void cbSelectTableData(const GSLib::SRoleKey& a_roleKey, EModuleType a_moduleType, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, BSLib::uint32 a_sessionID);
    void cbSelectGlobalTableData(const GSLib::SRoleKey& a_srcRoleKey,const GSLib::SRoleKey& a_roleKey, EModuleType a_moduleType, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, BSLib::uint32 a_sessionID);
    void cbSelectGlobalMultiTableData(const GSLib::SRoleKey& a_srcRoleKey,EModuleType a_moduleType, BSLib::uint32 a_sessionID,void* a_ptr,BSLib::uint32 a_state,std::vector<SAckTablesData> a_ackTablesDataArray);

private:
    bool _getSelectGlobalTableData(EDBTableID a_tableID,BSLib::Utility::CStream& a_stream,ETableKeyType& a_tableKeyType,CKeyTablePtr& a_keyTablePtr,CKeyIndexTablePtr& keyIndexTablePtr);

protected:
	GFLib::SServerID _getDataServerID() { return m_dataServerID; }
	ETableKeyType _getTableKey(const BSLib::Database::SDbColumn* a_dbTableColumn);

	virtual bool _init();
	virtual void _final();
	virtual void _cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void _cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);

	virtual bool _cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
	virtual bool _cbSelectKeyIndexTableData(const GSLib::SRoleKey& a_roleKey, CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);

    virtual bool _cbSelectGlobalKeyTableData(const GSLib::SRoleKey& a_srcRoleKey, const GSLib::SRoleKey& a_roleKey, CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
    virtual bool _cbSelectGlobalKeyIndexTableData(const GSLib::SRoleKey& a_srcRoleKey, const GSLib::SRoleKey& a_roleKey, CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);

    virtual bool _cbSelectGlobalMultiTableData(const GSLib::SRoleKey& a_srcRoleKey, EModuleType a_srcModuleType, BSLib::uint32 a_sessionID,void* a_ptr,BSLib::uint32 a_state,std::vector<SSelectTablesResult>& a_ackSelectTablesResultArray,std::vector<CKeyTablePtr>& keyTablePtrArray,std::vector<CKeyIndexTablePtr>& keyIndexTablePtrArray);

private:
	GFLib::SServerID m_dataServerID;
	BSLib::Utility::CHashMap<EDBTableID, SDbColumnInfor*> m_tableColumnHashMap;
};

}//DBSystem

}//GSLib

#endif//__GSLIB_DBSYSTEM_DBCOMMONSYSTEM_H__
