#ifndef __GSLIB_DBSYSTEM_CN_DBSYSTEMCN_H__
#define __GSLIB_DBSYSTEM_CN_DBSYSTEMCN_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace DBSystem
{

namespace CN
{

class CDBSystemCN : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CDBSystemCN();
	virtual ~CDBSystemCN();

	BSLIB_SINGLETON_DECLARE(CDBSystemCN);

	virtual BSLib::uint16 ICommonSystem_getFuncType() { return GSLib::EFUNCTYPE_DBSYSTEM; }

protected:
	virtual bool _init();
	virtual void _final();
	virtual bool ICommonSystem_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _ICommonSystem_startSystem();
	virtual bool _ICommonSystem_postStartSystem();
	virtual void ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);

	virtual bool _cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
	virtual bool _cbSelectKeyIndexTableData(const GSLib::SRoleKey& a_roleKey, CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);

private:
	void _onMsgDBSystemDB2XSAckSelectTableData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

};

}//CN

}//DBSystem

}//GSLib

#endif//__GSLIB_DBSYSTEM_CN_DBSYSTEMXS_H__

