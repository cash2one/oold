#ifndef __GSLIB_DBSYSTEM_KEYINDEXTABLE_H__
#define __GSLIB_DBSYSTEM_KEYINDEXTABLE_H__

#include <BSLib/database/dbKeyIndexTable.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace DBSystem
{

class CKeyIndexTable : public BSLib::Database::CDBKeyIndexTable
{
public:
	CKeyIndexTable(GSLib::DBSystem::CDBCommonSystem* a_commonSystem, const SDbColumnInfor* a_dbColumnInfor);
	~CKeyIndexTable();

	//�������ݵ�DBServer������a_needSaveDB�������ݿ�
	bool saveDataToDBServer(bool a_needSaveDB = false);
	bool saveDataToDBServer(const std::string& a_key, bool a_needSaveDB = false);
	bool saveDataToDBServer(const std::string& a_key, const std::string& a_index, bool a_needSaveDB = false);

	//Ҫ��DBServer�ͷ����ݣ��������ݿ���ɾ������
	bool closeTableDataToDB();
	bool closeTableDataToDB(const std::string& a_key);
	bool closeTableDataToDB(const std::string& a_key, const std::string& a_index);

	EDBTableID getTableID() { return m_dbColumnInfor->m_tableID; }
	const std::string& getTableName() { return m_dbColumnInfor->m_dbTableName; }

private:
	GSLib::DBSystem::CDBCommonSystem* m_commonSystem;
	const GSLib::DBSystem::SDbColumnInfor* m_dbColumnInfor;
};
typedef BSLib::Utility::CPointer<CKeyIndexTable> CKeyIndexTablePtr;

}//DBSystem

}//GSLib

#endif//__GSLIB_DBSYSTEM_KEYINDEXTABLE_H__
