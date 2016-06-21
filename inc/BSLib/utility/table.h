#ifndef __BSLIB_UTILITY_TABLE_H_
#define __BSLIB_UTILITY_TABLE_H_

#include <BSLib/utility/file/xmlFile.h>
#include <BSLib/utility/hashMap.h>
#include <BSLib/utility/string.h>

namespace BSLib
{

namespace Utility
{

class BSLIB_UTILITY_API CTableHead
{
public:
	CTableHead();
	~CTableHead();

	BSLib::uint32 getColumnCount() { return m_columnInforByIndex.size(); }

	BSLib::uint32 getColumnIndex(const std::string& a_columnName);
	std::string getColumnName(BSLib::uint32 a_columnIndex);
	
private:
	BSLib::Utility::CHashMap<BSLib::uint32, std::string> m_columnInforByIndex;
	BSLib::Utility::CHashMap<std::string, BSLib::uint32> m_columnInforByName;

	friend class CTableSheet;
};

class BSLIB_UTILITY_API CTableRow
{
public:
	CTableRow();
	~CTableRow();

	BSLib::Utility::CStringA& operator [](const std::string& a_columnName);
	BSLib::Utility::CStringA& operator [](BSLib::uint32 a_columnIndex);

	BSLib::Utility::CStringA& getText() { return m_rowText; }

private:
	CTableHead* m_tableHead;
	std::vector<BSLib::Utility::CStringA> m_tableRow;
	BSLib::Utility::CStringA m_rowText;

	friend class CTableSheet;
};

class BSLIB_UTILITY_API CTable
{
public:
	CTable();
	~CTable();

	void clear();

	BSLib::uint32 getColumnCount();
	BSLib::uint32 getRowCount();

	CTableRow& operator [](BSLib::uint32 a_rowIndex);

private:
	CTableHead* m_tableHead;
	std::vector<CTableRow*> m_tableRows;

	friend class CTableSheet;
};

class BSLIB_UTILITY_API CTableSheet
{
public:
	CTableSheet();
	~CTableSheet();

	bool loadXmlFile(const std::string& a_filePath);
	void clear();

	CTable& operator [](const std::string& a_tableName);

private:
	bool _readTableNode(BSLib::Utility::CXmlFile& a_xmlFile, BSLib::Utility::HXmlNode& a_tableNode, CTable* a_table);

private:
	BSLib::Utility::CHashMap<std::string, CTable*> m_columnInforByIndex;
};

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_TABLE_H_

