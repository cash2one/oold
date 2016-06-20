//////////////////////////////////////////////////////////////////////
//	created:	2014/10/29
//	filename: 	src\GSLib\dbSystem\keyTable.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/dbSystem/keyTable.h>
namespace GSLib
{

namespace DBSystem
{


CKeyTable::CKeyTable(GSLib::DBSystem::CDBCommonSystem* a_commonSystem, const GSLib::DBSystem::SDbColumnInfor* a_dbColumnInfor)
: BSLib::Database::CDBKeyTable(a_dbColumnInfor->m_dbTableColumn)
, m_commonSystem(a_commonSystem)
, m_dbColumnInfor(a_dbColumnInfor)
{
	;
}

CKeyTable::~CKeyTable()
{
	;
}

bool CKeyTable::saveDataToDBServer(bool a_needSaveDB)
{
	return saveDataToDBServer("", a_needSaveDB);
}

bool CKeyTable::saveDataToDBServer(const std::string& a_key, bool a_needSaveDB)
{
	if (m_commonSystem == NULL) {
		return false;
	}
	BSLib::Utility::CStream stream;
	if (!BSLib::Database::CDBKeyTable::serializeTo(a_key, stream, BSLib::Database::EDBTBLRWST_UPDATE, true)) {
		return false;
	}
	if (stream.readReady()) {
		if (!m_commonSystem->updateTableData(a_key, "", "", m_dbColumnInfor->m_tableID, stream, a_needSaveDB)) {
			return false;
		}
	}
	stream.reset();
	if (!BSLib::Database::CDBKeyTable::serializeKeyTo(stream, BSLib::Database::EDBTBLRWST_REMOVE, true)) {
		return false;
	}

	if (stream.readReady()) {
		if (!m_commonSystem->removeTableData(stream, m_dbColumnInfor->m_tableID, a_needSaveDB)) {
			return false;
		}
	}
	return true;
}

bool CKeyTable::closeTableDataToDB()
{
	return closeTableDataToDB("");
}

bool CKeyTable::closeTableDataToDB(const std::string& a_key)
{
	if (m_commonSystem == NULL) {
		return false;
	}
	if (!m_commonSystem->closeTableData(a_key, "", m_dbColumnInfor->m_tableID)) {
		return false;
	}
	return true;
}

}//DBSystem

}//GSLib


