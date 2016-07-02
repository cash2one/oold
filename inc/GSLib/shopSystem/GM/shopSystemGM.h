
#ifndef __GSLIB_SHOPSYSTEM_GM_SHOPSYSTEMGM_H__
#define __GSLIB_SHOPSYSTEM_GM_SHOPSYSTEMGM_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>
#include <GSLib/dbSystem/keyTable.h>
#include <BSLib/database/dbTableRow.h>
#include <GSLib/shopSystem/GM/shopConfig.h>
#include <GSLib/shopSystem/GM/cardConfig.h>
#include <string>

namespace GSLib
{

namespace ShopSystem
{

namespace GM
{

class CShopSystemGM : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CShopSystemGM();
	virtual ~CShopSystemGM();

	BSLIB_SINGLETON_DECLARE(CShopSystemGM);

	virtual BSLib::uint16 ICommonSystem_getFuncType() { return GSLib::EFUNCTYPE_SHOPSYSTEM; }

	void update(BSLib::uint64 a_delayMilliseconds);

public:
	virtual bool _init();
	virtual void _final();
	virtual bool ICommonSystem_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _ICommonSystem_startSystem();
	virtual void ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);
	
	CShopConfig& getConfig();
	bool reloadConfig();

	CCardConfig& getCardConfig() { return m_cardConfig;}
private:
	CShopConfig *m_shopConfig;
	std::string	m_configPath;
	CCardConfig m_cardConfig;
};

}//GM

}

}//GSLib

#endif
