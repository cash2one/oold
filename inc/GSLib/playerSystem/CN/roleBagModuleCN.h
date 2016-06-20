//////////////////////////////////////////////////////////////////////
//	created:	2014/09/3
//	filename: 	GSLib\playerSystem\GM\roleBagModuleGM.h
//	author:		zhangping
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PLAYERSYSTEM_CN_ROLEBAGMODULE_H__
#define __GSLIB_PLAYERSYSTEM_CN_ROLEBAGMODULE_H__
#include <GSLib/tracer.h>
#include <BSLib/utility/baseDef.h>
#include <BSLib/utility/hashMap.h>
#include <GSLib/playerSystem/CN/roleModuleCN.h>
#include <GSLib/playerSystem/baseDef.h>
#include <BSLib/utility/table.h>
#include <GSLib/playerSystem/DB/tablePlayerDB.h>


namespace GSLib
{

namespace PlayerSystem
{

namespace CN
{

class CRoleBagModuleCN : public CRoleModuleCN
{
public:
	CRoleBagModuleCN(CRoleCN* a_roleCN, EModuleType a_moduleType);
	virtual ~CRoleBagModuleCN();
public:
public:
	virtual void preInit(bool isFirst);
	virtual void postInit(bool isFirst);
	virtual void initToClient();
	virtual void final();

	virtual void initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual void freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	virtual void updateDataToDB();

	virtual bool cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
	virtual bool cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);

	bool updateTableData(const std::string& a_tableIndex, const std::string& a_name, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream, bool a_needSave = false);
	bool updateTableData(EDBTableID a_tableID, void* a_data, BSLib::uint32 a_dataSize,  bool a_needSave = false);
};

}//CN

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_CN_ROLEBAGMODULE_H__
