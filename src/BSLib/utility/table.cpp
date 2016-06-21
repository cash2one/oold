#include <BSLib/utility/tracer.h>
#include <BSLib/utility/table.h>
#include <BSLib/utility/exception.h>

namespace BSLib
{

namespace Utility
{
//////////////////////////////////////////////////////////////////////////
CTableHead::CTableHead()
{
	;
}

CTableHead::~CTableHead()
{
	;
}

BSLib::uint32 CTableHead::getColumnIndex(const std::string& a_columnName)
{
	BSLib::Utility::CStringA columnName = a_columnName;
	columnName.toLower();

	BSLib::uint32 index = 0;
	if (!m_columnInforByName.getValue(columnName, index)) {
		BSLib::Utility::CStringA error;
		error.format("%s�в�����", a_columnName.c_str());
		throw CException(error);
	}
	return index;
}

std::string CTableHead::getColumnName(BSLib::uint32 a_columnIndex)
{
	std::string name = 0;
	if (!m_columnInforByIndex.getValue(a_columnIndex, name)) {
		BSLib::Utility::CStringA error;
		error.format("��%d�в�����", a_columnIndex);
		throw CException(error);
	}
	return name;
}

//////////////////////////////////////////////////////////////////////////
CTableRow::CTableRow()
: m_tableHead(NULL)
{
	;
}

CTableRow::~CTableRow()
{
	;
}

BSLib::Utility::CStringA& CTableRow::operator [](const std::string& a_columnName)
{
	if (m_tableHead == NULL) {
		BSLib::Utility::CStringA error;
		error.format("TableHead������");
		throw CException(error);
	}
	BSLib::uint32 index = m_tableHead->getColumnIndex(a_columnName);
	if (index >= m_tableRow.size()) {
		BSLib::Utility::CStringA error;
		error.format("�±곬����Χ");
		throw CException(error);
	}
	return m_tableRow[index];
}

BSLib::Utility::CStringA& CTableRow::operator [](BSLib::uint32 a_columnIndex)
{
	if (a_columnIndex >= m_tableRow.size()) {
		BSLib::Utility::CStringA error;
		error.format("�±곬����Χ");
		throw CException(error);
	}
	return m_tableRow[a_columnIndex];
}

//////////////////////////////////////////////////////////////////////////
CTable::CTable()
: m_tableHead(NULL)
{
	;
}

CTable::~CTable()
{
	clear();
}

void CTable::clear()
{
	if (m_tableHead != NULL) {
		BSLIB_SAFE_DELETE(m_tableHead);
	}
	for (BSLib::uint32 i=0; i<m_tableRows.size(); ++i) {
		CTableRow* tableRow = m_tableRows[i];
		if (tableRow == NULL) {
			continue;
		}
		BSLIB_SAFE_DELETE(tableRow);
	}
	m_tableRows.clear();
}

BSLib::uint32 CTable::getColumnCount()
{
	if (m_tableHead == NULL) {
		return 0;
	}
	return m_tableHead->getColumnCount();
}

BSLib::uint32 CTable::getRowCount()
{
	return (BSLib::uint32)m_tableRows.size();
}

CTableRow& CTable::operator [](BSLib::uint32 a_rowIndex)
{
	if (a_rowIndex >= m_tableRows.size()) {
		BSLib::Utility::CStringA error;
		error.format("�±곬����Χ");
		throw CException(error);
	}
	CTableRow* tableRow = m_tableRows[a_rowIndex];
	if (tableRow == NULL) {
		BSLib::Utility::CStringA error;
		error.format("�±�ֵ��Χ��Ч");
		throw CException(error);
	}
	return *tableRow;
}

//////////////////////////////////////////////////////////////////////////
CTableSheet::CTableSheet()
{
	;
}

CTableSheet::~CTableSheet()
{
	clear();
}

bool CTableSheet::loadXmlFile(const std::string& a_filePath)
{
	BSLib::Utility::CXmlFile xmlFile;

	if (!xmlFile.loadFile(a_filePath)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "��ȡ%s�ļ�ʧ��", a_filePath.c_str());
		return false;
	}
	BSLib::Utility::HXmlNode root = xmlFile.getRootNode();
	if (root == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "��ȡ%s�ļ����ڵ�ʧ��", a_filePath.c_str());
		return false;
	}
	BSLib::Utility::HXmlNode childreNode = xmlFile.getChildNode(root);
	while (childreNode != NULL) {
		BSLib::Utility::CStringA nodeName;
		if (!xmlFile.getNodeName(childreNode, nodeName)) {
			BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "��ȡ%s�ļ��ڵ�ʧ��", a_filePath.c_str());
			xmlFile.clear();
			return false;
		}
		nodeName.toLower();

		CTable* talbe = NULL;
		m_columnInforByIndex.getValue(nodeName, talbe);
		if (talbe != NULL) {
			if (!_readTableNode(xmlFile, childreNode, talbe)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, " ��ȡ%s�ļ�%s�ڵ�ֵʧ��", a_filePath.c_str(), nodeName.c_str());
				xmlFile.clear();
				return false;
			}
			childreNode = xmlFile.getNextNode(childreNode);
			continue;
		}
		talbe = new CTable();
		if (talbe == NULL) {
			return false;
		}
		if (!_readTableNode(xmlFile, childreNode, talbe)) {
			BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, " ��ȡ%s�ļ�%s�ڵ�ֵʧ��", a_filePath.c_str(), nodeName.c_str());
			BSLIB_SAFE_DELETE(talbe);
			xmlFile.clear();
			return false;
		}
		m_columnInforByIndex.setValue(nodeName, talbe);

		childreNode = xmlFile.getNextNode(childreNode);
	}
	xmlFile.clear();
	return true;
}

void CTableSheet::clear()
{
	BSLib::Utility::CHashMap<std::string, CTable*>::iterator it = m_columnInforByIndex.begin();
	for (; it != m_columnInforByIndex.end(); ++it) {
		CTable* talbe = it->second;
		if (talbe == NULL) {
			continue;
		}
		talbe->clear();
		BSLIB_SAFE_DELETE(talbe);
	}
	m_columnInforByIndex.clear();
}

CTable& CTableSheet::operator [](const std::string& a_tableName)
{
	BSLib::Utility::CStringA tableName = a_tableName;
	tableName.toLower();

	CTable* table = NULL;
	m_columnInforByIndex.getValue(tableName, table);
	if (table == NULL) {
		BSLib::Utility::CStringA error;
		error.format("[TableName=%s]������", a_tableName.c_str());
		throw CException(error);
	}
	return *table;
}

bool CTableSheet::_readTableNode(BSLib::Utility::CXmlFile& a_xmlFile, BSLib::Utility::HXmlNode& a_tableNode, CTable* a_table)
{
	CTableHead* tableHead = a_table->m_tableHead;
	if (tableHead == NULL) {
		tableHead = new CTableHead();
		if (tableHead == NULL) {
			return false;
		}
		BSLib::uint32 index = 0;
		BSLib::Utility::HXmlAttr btAttr = a_xmlFile.getFirstAttr(a_tableNode);
		while (btAttr != NULL){
			BSLib::Utility::CStringA attrName;
			if (!a_xmlFile.getAttrName(btAttr, attrName)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "��ȡ�ڵ�����ʧ��");
				BSLIB_SAFE_DELETE(tableHead);
				return false;
			}
			attrName.toLower();

			tableHead->m_columnInforByIndex.setValue(index, attrName);
			tableHead->m_columnInforByName.setValue(attrName, index);

			btAttr = a_xmlFile.getNextAttr(btAttr);
			++index;
		}
		a_table->m_tableHead = tableHead;
	}
	CTableRow* tableRow = new CTableRow();
	if (tableRow == NULL) {
		return false;
	}
	tableRow->m_tableHead = tableHead;
	tableRow->m_tableRow.resize(tableHead->getColumnCount(), "");

	{
		BSLib::Utility::HXmlAttr btAttr = a_xmlFile.getFirstAttr(a_tableNode);
		while (btAttr != NULL){
			BSLib::Utility::CStringA attrName;
			if (!a_xmlFile.getAttrName(btAttr, attrName)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "��ȡ�ڵ�����ʧ��");
				BSLIB_SAFE_DELETE(tableRow);
				return false;
			}
			attrName.toLower();

			BSLib::uint32 index = 0;
			if (!tableHead->m_columnInforByName.getValue(attrName, index)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "����%s����", attrName.c_str());
				BSLIB_SAFE_DELETE(tableRow);
				return false;
			}
			if (index >= tableRow->m_tableRow.size()) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "%s�����±곬����Χ", attrName.c_str());
				BSLIB_SAFE_DELETE(tableRow);
				return false;
			}
			std::string attrValue;
			if (!a_xmlFile.getAttrValue(btAttr, attrValue)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "��ȡ�ڵ�%s����ʧ��", attrName.c_str());
				BSLIB_SAFE_DELETE(tableRow);
				return false;
			}
			tableRow->m_tableRow[index] = attrValue;

			btAttr = a_xmlFile.getNextAttr(btAttr);
		}
	}
	
	if (!a_xmlFile.getNodeValue(a_tableNode, tableRow->m_rowText)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "��ȡ�ڵ�ֵʧ��");
		BSLIB_SAFE_DELETE(tableRow);
		return false;
	}
	
	a_table->m_tableRows.push_back(tableRow);
	
	return true;
}

}//Utility

}//BSLib
