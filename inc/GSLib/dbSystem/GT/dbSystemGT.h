#ifndef __GSLIB_DBSYSTEM_GT_DBSYSTEMGT_H__
#define __GSLIB_DBSYSTEM_GT_DBSYSTEMGT_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace DBSystem
{

namespace GT
{

struct SDBTable 
{
};
class CDBSystemGT : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CDBSystemGT();
	virtual ~CDBSystemGT();

	BSLIB_SINGLETON_DECLARE(CDBSystemGT);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_DBSYSTEM; }

protected:
	virtual bool _init();
	virtual void _final();
	virtual bool _loadGameConfig(const std::string& a_configPath);
	virtual bool _initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual bool _postStartSystem();
	virtual void _cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void _cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);

	virtual bool _cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
	virtual bool _cbSelectKeyIndexTableData(const GSLib::SRoleKey& a_roleKey, CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);

private:
	void _onMsgDBSystemDB2XSAckSelectTableData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
};

}//GT

}//DBSystem

}//GSLib

#endif//__GSLIB_DBSYSTEM_GT_DBSYSTEMGT_H__

