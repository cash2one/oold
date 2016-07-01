
#ifndef __GSLIB_SHOPSYSTEM_DB_SHOPSYSTEMDB_H__
#define __GSLIB_SHOPSYSTEM_DB_SHOPSYSTEMDB_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace ShopSystem
{

namespace DB
{

class CShopSystemDB : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CShopSystemDB();
	virtual ~CShopSystemDB();

	BSLIB_SINGLETON_DECLARE(CShopSystemDB);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_SHOPSYSTEM; }

public:
	virtual bool _init();
	virtual void _final();
	virtual bool ICommonServer_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);
};

}//DB

}

}//GSLib

#endif
