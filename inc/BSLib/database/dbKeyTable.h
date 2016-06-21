#ifndef __BSLIB_DATEBSLIB_DBKEYTABLE__
#define __BSLIB_DATEBSLIB_DBKEYTABLE__

#include <BSLib/database/dbConnection.h>
#include <BSLib/database/dbTableRow.h>

namespace BSLib
{

namespace Database
{

class CDBKeyTable
{
public:
	CDBKeyTable(const SDbColumn* a_dbColumn);
	~CDBKeyTable();

	//导入导出数据
	bool serializeTo(BSLib::Utility::CStream& a_stream, EDBTableRowState a_tableRowState = EDBTBLRWST_NULL, bool a_resetState = false);
	bool serializeTo(const std::string& a_key, BSLib::Utility::CStream& a_stream, EDBTableRowState a_tableRowState = EDBTBLRWST_NULL, bool a_resetState = false);
	bool serializeFrom(BSLib::Utility::CStream& a_stream);

	bool serializeKeyTo(BSLib::Utility::CStream& a_stream, EDBTableRowState a_tableRowState = EDBTBLRWST_NULL, bool a_resetState = false);

	//更新或添加数据
	bool update(const std::string& a_key, const std::string& a_itemName, void* a_buffer, BSLib::uint32 a_buffSize);
	bool update(const std::string& a_key, const std::string& a_itemName, BSLib::Utility::CStream& a_stream);
	bool update(const std::string& a_key, BSLib::int32 a_itemNumber, void* a_buffer, BSLib::uint32 a_buffSize);
	bool update(const std::string& a_key, BSLib::int32 a_itemNumber, BSLib::Utility::CStream& a_stream);
	bool update(const std::string& a_key, void* a_buffer, BSLib::uint32 a_buffSize);
	bool update(const std::string& a_key, BSLib::Utility::CStream& a_stream);
	bool update(BSLib::Utility::CStream& a_stream);

	//删除本行数据
	void remove(const std::string& a_key);
	void removeAll();

	//释放数据，但不删除
	void clear(const std::string& a_key);
	void clear();

	CDBTableRow* getRow(const std::string& a_key);

	//获取失败，则抛出异常
	CDBTableRow& operator [](const std::string& a_key);

	void traversal(BSLib::Utility::CHashMap<std::string, CDBTableRow*>::CCallback& a_callback) { m_tableRowsHashMap.traversal(a_callback); }

	CDBTableHead& getTableHead() { return m_dbTableHead; }
public:
	//从DB加载数据
	bool loadDataFromDBByWhere(CDbConnection* a_dbConnection, const std::string& a_dbTableName, const std::string& a_sqlWhere);
    bool loadDataFromDBByWhere(CDbConnection* a_dbConnection, const std::string& a_dbTableName, const std::string& a_key, const std::string& a_strWhere);
	bool loadDataFromDB(CDbConnection* a_dbConnection, const std::string& a_dbTableName);
	bool loadDataFromDB(CDbConnection* a_dbConnection, const std::string& a_dbTableName, const std::string& a_key);
    
	
	//保存数据到DB
	bool saveDataToDB(CDbConnection* a_dbConnection, const std::string& a_dbTableName);
	bool saveDataToDB(CDbConnection* a_dbConnection, const std::string& a_dbTableName, const std::string& a_key);

    BSLib::uint32 getRowCount()const {return m_tableRowsHashMap.size();}
private:
	CDBTableRow* _createTableRow(BSLib::Utility::CStream& a_stream);
	bool _addTableRow(CDBTableRow* a_talbeRow);
	void _resetTableRowState(EDBTableRowState a_tableRowState);

private:
	CDBTableHead m_dbTableHead;
	BSLib::Utility::CHashMap<std::string, CDBTableRow*> m_tableRowsHashMap;
};

}//Database

}//BSLib

#endif//__BSLIB_DATEBSLIB_DBKEYTABLE__
