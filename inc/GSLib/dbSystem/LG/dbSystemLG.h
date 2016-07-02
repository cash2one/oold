#ifndef __GSLIB_DBSYSTEM_LG_DBSYSTEMLG_H__
#define __GSLIB_DBSYSTEM_LG_DBSYSTEMLG_H__

#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/dbSystem/msgDBSystem.h>
#include <BSLib/database/dbConnection.h>
#include <GSLib/dbSystem/LG/dbTableLG.h>

namespace GSLib
{

namespace DBSystem
{

namespace LG
{

class CDBSystemLG : public GFLib::CommonServer::ICommonSystem
{
public:
	CDBSystemLG();
	virtual ~CDBSystemLG();

	BSLIB_SINGLETON_DECLARE(CDBSystemLG);

	virtual BSLib::uint16 ICommonSystem_getFuncType() { return GSLib::EFUNCTYPE_DBSYSTEM; }

	///////////////////////////////////////////////////////////////////////////
	// Method:    selectAccountData
	// Qualifier: ��ȡ�˺��������
	// Returns:   int -1 �쳣��0 û�в鵽���˺ţ�1��ø��˺ųɹ�
	// Parameter: const std::string a_accountName ��Ҫ��ѯ���˺�
	// Parameter: SAccountData & a_accountData �˺��������
	///////////////////////////////////////////////////////////////////////////
	int selectAccountData(const std::string a_accountName, SAccountData& a_accountData);
    int selectActivationCodeData(std::string a_key, SActivationCodeData& a_dbData);
    bool updateActivationCodeData(SActivationCodeData& a_dbData);
	int selectFastLoginAccountData(const std::string a_uniqueID, const std::string a_uniqueKey,const BSLib::uint32 a_bindFlag,SAccountData& a_accountData);
	bool insertAccountData(BSLib::Utility::CStream& a_stream, BSLib::uint64* a_autoIncrement = NULL);

protected:
	virtual bool _init();
	virtual void _final();
	virtual bool ICommonSystem_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _ICommonSystem_startSystem();
	virtual void ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);

private:
	BSLib::Database::CDbConnection m_dbConnection;
};

}//LG

}//DBSystem

}//GSLib

#endif//__GSLIB_DBSYSTEM_LG_DBSYSTEMLG_H__
