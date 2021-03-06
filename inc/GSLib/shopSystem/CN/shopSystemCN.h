
#ifndef __GSLIB_SHOPSYSTEM_GM_SHOPSYSTEMGM_H__
#define __GSLIB_SHOPSYSTEM_GM_SHOPSYSTEMGM_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>
#include <GSLib/dbSystem/keyTable.h>
#include <GSLib/dbSystem/keyIndexTable.h>

namespace GSLib
{

namespace ShopSystem
{

namespace CN
{

class CShopSystemCN : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CShopSystemCN();
	virtual ~CShopSystemCN();

	BSLIB_SINGLETON_DECLARE(CShopSystemCN);

	virtual BSLib::uint16 ICommonSystem_getFuncType() { return GSLib::EFUNCTYPE_SHOPSYSTEM; }

	void update(BSLib::uint64 a_delayMilliseconds);

public:
	virtual bool _init();	// test
	virtual void _final();
	virtual bool ICommonSystem_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _ICommonSystem_startSystem();
	virtual void ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);


	
};

}//GM

}

}//GSLib

#endif
