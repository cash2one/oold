//////////////////////////////////////////////////////////////////////
//	created:	2014/10/29
//	filename: 	GSLib\dbSystem\keyTable.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_DBSYSTEM_KEYTABLE_H__
#define __GSLIB_DBSYSTEM_KEYTABLE_H__

#include <BSLib/database/dbKeyTable.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace DBSystem
{

class CKeyTable : public BSLib::Database::CDBKeyTable
{
public:
	CKeyTable(GSLib::DBSystem::CDBCommonSystem* a_commonSystem, const GSLib::DBSystem::SDbColumnInfor* a_dbColumnInfor);
	virtual ~CKeyTable();

	//�������ݵ�DBServer������a_needSaveDB�������ݿ�
	bool saveDataToDBServer(bool a_needSaveDB = false);
	bool saveDataToDBServer(const std::string& a_key, bool a_needSaveDB = false);

	//Ҫ��DBServer�ͷ����ݣ��������ݿ���ɾ������
	bool closeTableDataToDB();
	bool closeTableDataToDB(const std::string& a_key);

	EDBTableID getTableID() { return m_dbColumnInfor->m_tableID; }
	const std::string& getTableName() { return m_dbColumnInfor->m_dbTableName; }

private:
	GSLib::DBSystem::CDBCommonSystem* m_commonSystem;
	const GSLib::DBSystem::SDbColumnInfor* m_dbColumnInfor;
};
typedef BSLib::Utility::CPointer<CKeyTable> CKeyTablePtr;

}//DBSystem

}//GSLib

#endif//__GSLIB_DBSYSTEM_KEYTABLE_H__

