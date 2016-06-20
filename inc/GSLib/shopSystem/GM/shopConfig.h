#ifndef SHOSYSTEM_GM_SHOPCONFIG_H__
#define SHOSYSTEM_GM_SHOPCONFIG_H__
#include <BSLib/utility/singleton.h>
#include <map>
#include <BSLib/utility/baseDef.h>

namespace GSLib
{
namespace ShopSystem
{
namespace GM
{

struct SShopItemInfo
{	
	SShopItemInfo()
		:m_id(0)
		,m_itemType(0)
		,m_itemId(0)
		,m_itemNum(0)
		,m_payType(0)
		,m_price(0)
		,m_limitNum(0)
		,m_discount(0)
	{

	}

	BSLib::int32				m_id;
	BSLib::int32				m_itemType;
	BSLib::int32				m_itemId;
	BSLib::int32				m_itemNum;
	BSLib::int32				m_payType;
	BSLib::int32				m_price;
	BSLib::int32				m_limitNum;
	BSLib::int32				m_discount;
};

struct SPVPShopItemInfo
	:public SShopItemInfo
{
	SPVPShopItemInfo()
		:m_probability(0)
		,m_flag(0)
	{

	}

	BSLib::int32 m_probability;
	BSLib::int32 m_flag;
};

struct SShopConfigInfo
{
	SShopConfigInfo()
		:m_id(0)
		,m_showNum(0)
		,m_refreshPeriod(0)
		,m_manualRefresh(0)
		,m_payType(0)
		,m_price(0)
	{

	}

	BSLib::int32	m_id;
	std::string		m_shopPath;
	BSLib::int32	m_showNum;
	BSLib::int32	m_refreshPeriod;
	BSLib::int32	m_manualRefresh;
	BSLib::int32	m_payType;
	BSLib::int32	m_price;
	std::map<BSLib::int32, BSLib::int32> m_vip_prices;
};


class CShopConfig
{
public:
	CShopConfig();
	~CShopConfig();

	bool loadConfigFile(const std::string& a_configFile);
	bool getShopItem(BSLib::int32 a_shopId, BSLib::int32 a_id, SShopItemInfo*& a_shopItem);
	bool getShop(BSLib::int32 a_shopId, std::map<BSLib::int32, SShopItemInfo *>*& a_shopItemList);
	bool getShopConfig(BSLib::int32 a_shopId, SShopConfigInfo*& a_shopConfig);
	bool getPVPShopShowItem(BSLib::int32 a_shopId, bool a_usePaidCount, BSLib::uint32& a_paidRefreshCount, std::vector<BSLib::int32>& a_ids);
	bool getShopShowItem(BSLib::int32 a_shopId, std::vector<BSLib::int32>& a_ids);
	BSLib::int32 getDiscount(BSLib::int32 a_shopId, BSLib::int32 a_vipLevel);	// ªÒ»°…ÃµÍ’€ø€
private:
	void _initPVPProbability(std::map<BSLib::int32, SShopItemInfo *>* a_pvpMap);
private:
	std::map<BSLib::int32, std::map<BSLib::int32, SShopItemInfo* >* > m_shopItemsHashMap;
	std::map<BSLib::int32, SShopConfigInfo* > m_shopConfigHashMap;
	
	std::vector<BSLib::int32> m_pvpProbability;
	std::vector<BSLib::int32> m_specialIds;
};


} // GM
} // ShopSystem
} // BSLib

#endif // SHOSYSTEM_GM_SHOPCONFIG_H__
