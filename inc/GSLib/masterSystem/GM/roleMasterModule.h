
#ifndef __GSLIB_MASTERSYSTEM_GM_ROLEMASTERMODULE_H__
#define __GSLIB_MASTERSYSTEM_GM_ROLEMASTERMODULE_H__

#include <GSLib/playerSystem/GM/roleModuleGM.h>
#include <BSLib/database/dbTableRow.h>
#include <GSLib/masterSystem/DB/tableMasterDB.h>

namespace GSLib
{

namespace MasterSystem
{

namespace GM
{


class CRoleMasterModule : public GSLib::PlayerSystem::GM::CRoleModuleGM
{
public:
	CRoleMasterModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType);
	virtual ~CRoleMasterModule();

	virtual void preInit(bool isFirst);
	virtual void postInit(bool isFirst);
	virtual void initToClient();
	virtual void final();

	virtual void initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual void freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	virtual void updateDataToDB();
	virtual bool cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
	virtual bool cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
	virtual bool exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value);


};

}//GM

}

}//GSLib

#endif