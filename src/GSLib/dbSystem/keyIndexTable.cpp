//////////////////////////////////////////////////////////////////////
//	created:	2014/10/29
//	filename: 	src\GSLib\dbSystem\keyIndexTable.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/dbSystem/keyIndexTable.h>

namespace GSLib
{

namespace DBSystem
{


CKeyIndexTable::CKeyIndexTable(GSLib::DBSystem::CDBCommonSystem* a_commonSystem, const SDbColumnInfor* a_dbColumnInfor)
: BSLib::Database::CDBKeyIndexTable(a_dbColumnInfor->m_dbTableColumn)
, m_commonSystem(a_commonSystem)
, m_dbColumnInfor(a_dbColumnInfor)
{
	;
}

CKeyIndexTable::~CKeyIndexTable()
{
	;
}

//更新数据到DBServer，根据a_needSaveDB保存数据库
bool CKeyIndexTable::saveDataToDBServer(bool a_needSaveDB)
{
	return saveDataToDBServer("", "", a_needSaveDB);
}

bool CKeyIndexTable::saveDataToDBServer(const std::string& a_key, bool a_needSaveDB)
{
	return saveDataToDBServer(a_key, "", a_needSaveDB);
}

bool CKeyIndexTable::saveDataToDBServer(const std::string& a_key, const std::string& a_index, bool a_needSaveDB)
{
	if (m_commonSystem == NULL) {
		return false;
	}
	BSLib::Utility::CStream stream;
	if (!BSLib::Database::CDBKeyIndexTable::serializeTo(a_key, a_index, stream, BSLib::Database::EDBTBLRWST_UPDATE, true)) {
		return false;
	}
	if (stream.readReady()) {
		if (!m_commonSystem->updateTableData(a_key, a_index, "", m_dbColumnInfor->m_tableID, stream, a_needSaveDB)) {
			return false;
		}
	}
	stream.reset();
	if (!BSLib::Database::CDBKeyIndexTable::serializeKeyIndexTo(stream, BSLib::Database::EDBTBLRWST_REMOVE, true)) {
		return false;
	}

	if (stream.readReady()) {
		if (!m_commonSystem->removeTableData(stream, m_dbColumnInfor->m_tableID, a_needSaveDB)) {
			return false;
		}
	}
	return true;
}

//要求DBServer释放数据，但不数据库中删除数据
bool CKeyIndexTable::closeTableDataToDB()
{
	return closeTableDataToDB("", "");
}

bool CKeyIndexTable::closeTableDataToDB(const std::string& a_key)
{
	return closeTableDataToDB(a_key, "");
}

bool CKeyIndexTable::closeTableDataToDB(const std::string& a_key, const std::string& a_index)
{
	if (m_commonSystem == NULL) {
		return false;
	}
	if (!m_commonSystem->closeTableData(a_key, a_index, m_dbColumnInfor->m_tableID)) {
		return false;
	}
	return true;
}

}//DBSystem

}//GSLib