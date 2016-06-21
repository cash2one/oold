#ifndef __BSLIB_DATEBSLIB_DBTABLEROW__
#define __BSLIB_DATEBSLIB_DBTABLEROW__

#include <BSLib/utility/hashMap.h>
#include <BSLib/utility/stream.h>
#include <BSLib/database/dbReader.h>
#include <BSLib/database/dbTableHead.h>
#include <BSLib/database/dbTableCell.h>

namespace BSLib
{

namespace Database
{

enum EDBTableRowState
{
	EDBTBLRWST_NULL = 0,
	EDBTBLRWST_UPDATE,
	EDBTBLRWST_REMOVE,
};

//////////////////////////////////////////////////////////////////////////
/// @brief 对应数据库表一个记录
//////////////////////////////////////////////////////////////////////////
class CDBTableRow
{
public:
	CDBTableRow(CDBTableHead* a_dbTableHead);
	~CDBTableRow();

	//导入导出数据
	bool serializeTo(void* a_buffer, BSLib::uint32 a_buffSize) const;
	bool serializeTo(BSLib::Utility::CStream& a_stream) const;
	bool serializeFrom(BSLib::Utility::CStream& a_stream);

	//更新或添加数据
	bool update(const std::string& a_itemName, BSLib::Utility::CStream& a_stream);
	bool update(BSLib::int32 a_itemNumber, BSLib::Utility::CStream& a_stream);
	bool update(BSLib::Utility::CStream& a_stream);

	bool create(const std::string& a_key, const std::string& a_index);

	//删除本行数据
	void remove() { m_rowState = EDBTBLRWST_REMOVE; }
	void clear();

	CDBTableCell* getCellValue(const std::string& a_itemName);
	CDBTableCell* getCellValue(BSLib::int32 a_itemNumber);

	CDBTableCell& operator [](const std::string& a_itemName);
	CDBTableCell& operator [](BSLib::int32 a_itemNumber);

	EDBTableRowState getRowState() { return m_rowState; }
	void setRowState(EDBTableRowState a_rowState) { m_rowState = a_rowState; }

	const std::string& getKey() { return m_key; }
	const std::string& getIndex() { return m_index; }

private:
	bool _createTalbeRow();

private:
	CDBTableHead* m_dbTableHead;
	std::vector<CDBTableCell*> m_tableCells;
	EDBTableRowState m_rowState;

	std::string m_key;
	std::string m_index;
};

}//Database

}//BSLib

#endif//__BSLIB_DATEBSLIB_DBTABLEROW__

