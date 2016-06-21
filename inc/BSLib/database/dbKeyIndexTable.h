#ifndef __BSLIB_DATEBSLIB_DBKEYINDEXTABLE__
#define __BSLIB_DATEBSLIB_DBKEYINDEXTABLE__

#include <BSLib/database/dbConnection.h>
#include <BSLib/database/dbTableRow.h>

namespace BSLib
{

namespace Database
{

class CDBKeyIndexTable
{
public:
	CDBKeyIndexTable(const SDbColumn* a_dbColumn);
	~CDBKeyIndexTable();

	//导入导出数据
	bool serializeTo(BSLib::Utility::CStream& a_stream, EDBTableRowState a_tableRowState = EDBTBLRWST_NULL, bool a_resetState = false);
	bool serializeTo(const std::string& a_key, BSLib::Utility::CStream& a_stream, EDBTableRowState a_tableRowState = EDBTBLRWST_NULL, bool a_resetState = false);
	bool serializeTo(const std::string& a_key, const std::string& a_index, BSLib::Utility::CStream& a_stream, EDBTableRowState a_tableRowState = EDBTBLRWST_NULL, bool a_resetState = false);

	bool serializeFrom(BSLib::Utility::CStream& a_stream);

	bool serializeKeyIndexTo(BSLib::Utility::CStream& a_stream, EDBTableRowState a_tableRowState = EDBTBLRWST_NULL, bool a_resetState = false);

	//更新或添加数据
	bool update(const std::string& a_key, const std::string& a_index, const std::string& a_itemName, void* a_buffer, BSLib::uint32 a_buffSize);
	bool update(const std::string& a_key, const std::string& a_index, const std::string& a_itemName, BSLib::Utility::CStream& a_stream);
	bool update(const std::string& a_key, const std::string& a_index, BSLib::int32 a_itemNumber, void* a_buffer, BSLib::uint32 a_buffSize);
	bool update(const std::string& a_key, const std::string& a_index, BSLib::int32 a_itemNumber, BSLib::Utility::CStream& a_stream);
	bool update(const std::string& a_key, const std::string& a_index, void* a_buffer, BSLib::uint32 a_buffSize);
	bool update(const std::string& a_key, const std::string& a_index, BSLib::Utility::CStream& a_stream);
	bool update(BSLib::Utility::CStream& a_stream);
	bool update(const std::string& a_key, BSLib::Utility::CStream& a_stream);

	//删除本行数据
	void remove(const std::string& a_key);
	void remove(const std::string& a_key, const std::string& a_index);
	void removeAll();

	//释放数据，但不删除
	void clear(const std::string& a_key);
	void clear(const std::string& a_key, const std::string& a_index);
	void clear();

	const BSLib::Utility::CHashMap<std::string, CDBTableRow*>* getRows(const std::string& a_key);
	CDBTableRow* getRow(const std::string& a_key, const std::string& a_index);

	CDBTableRow& operator ()(const std::string& a_key, const std::string& a_index);

	void traversal(BSLib::Utility::CHashMap<std::string, CDBTableRow*>::CCallback& a_callback);
	void traversal(const std::string& a_key, BSLib::Utility::CHashMap<std::string, CDBTableRow*>::CCallback& a_callback);

	const CDBTableHead& getTableHead() { return m_dbTableHead; }

public:
	//从DB加载数据
	bool loadDataFromDBByWhere(CDbConnection* a_dbConnection, const std::string& a_dbTableName, const std::string& a_sqlWhere);
    bool loadDataFromDBByWhere(CDbConnection* a_dbConnection, const std::string& a_dbTableName, const std::string& a_key, const std::string& a_index, const std::string& a_sqlWhere);
	bool loadDataFromDB(CDbConnection* a_dbConnection, const std::string& a_dbTableName);
	bool loadDataFromDB(CDbConnection* a_dbConnection, const std::string& a_dbTableName, const std::string& a_key, const std::string& a_index);

	//保存数据到DB
	bool saveDataToDB(CDbConnection* a_dbConnection, const std::string& a_dbTableName);
	bool saveDataToDB(CDbConnection* a_dbConnection, const std::string& a_dbTableName, const std::string& a_key, const std::string& a_index);

private:
	bool _serializeTo(BSLib::Utility::CHashMap<std::string, CDBTableRow*>* a_indexTableRows, BSLib::Utility::CStream& a_stream, EDBTableRowState a_tableRowState, bool a_resetState);
	bool _serializeKeyIndexTo(BSLib::Utility::CHashMap<std::string, CDBTableRow*>* a_indexTableRows, BSLib::Utility::CStream& a_stream, EDBTableRowState a_tableRowState, bool a_resetState);
	CDBTableRow* _createTableRow(BSLib::Utility::CStream& a_stream);
	bool _addTableRow(CDBTableRow* a_talbeRow);
	void _resetTableRowState(EDBTableRowState a_tableRowState);
	void _resetTableRowState(BSLib::Utility::CHashMap<std::string, CDBTableRow*>* a_indexTableRows, EDBTableRowState a_tableRowState);

private:
	CDBTableHead m_dbTableHead;
	BSLib::Utility::CHashMap<std::string, BSLib::Utility::CHashMap<std::string, CDBTableRow*>* > m_tableRowsHashMap;
};

}//Database

}//BSLib

#endif//__BSLIB_DATEBSLIB_DBKEYINDEXTABLE__
