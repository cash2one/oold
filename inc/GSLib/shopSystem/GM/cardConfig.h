#ifndef cardConfig_h__
#define cardConfig_h__

#include <BSLib/utility/singleton.h>
#include <map>
#include <BSLib/utility/baseDef.h>

namespace GSLib
{
namespace ShopSystem
{
namespace GM
{

struct SCardItemInfo
{	
	SCardItemInfo()
		:m_id(0)
		,m_Type(0)
		,m_libType(0)
		,m_itemId(0)
		,m_itemNum(0)
		,m_ratio(0)
	{
	}

	BSLib::int32				m_id;
	BSLib::int32				m_Type;
	BSLib::int32				m_libType;
	BSLib::int32				m_itemId;
	std::vector<BSLib::int32>	m_itemNum;
	BSLib::int32				m_ratio;
};


struct SCardConfigInfo
{
	SCardConfigInfo()
		:m_id(0)
		,m_free_gold(0)
		,m_free_gold_cd(0)
		,m_gold1_cost(0)
		,m_gold10_cost(0)
		,m_free_diamond(0)
		,m_free_diamond_cd(0)
		,m_diamond1_cost(0)
		,m_diamond10_cost(0)
	{

	}

	BSLib::int32	m_id;
	BSLib::int32	m_free_gold;
	BSLib::int32	m_free_gold_cd;
	BSLib::int32	m_gold1_cost;
	BSLib::int32	m_gold10_cost;
	BSLib::int32	m_free_diamond;
	BSLib::int32	m_free_diamond_cd;
	BSLib::int32	m_diamond1_cost;
	BSLib::int32	m_diamond10_cost;
	std::vector<BSLib::int32> m_event_names;
	std::vector<BSLib::int32> m_event_ratio;

	std::vector<BSLib::int32> m_prize_names;
	std::vector<BSLib::int32> m_prize_ratio;
};

enum CardSumType
{
	eCardSumTypeFriend = 1,
	eCardSumTypeGuangZiLi,
};

enum CardType
{
	eCardTypeFriendGold = 1,
	eCardTypeFriendDiamond,
	eCardTypeGuangZiLiGold,
	eCardTypeGuangZiLiDiamond,
};

enum LibType
{
	eLibType1 = 1,
	eLibType2,
	eLibType3
};

class CCardConfig
{
public:
	CCardConfig();
	~CCardConfig();

	bool loadConfigFile(const std::string& a_configFile);
	bool getCardItem(BSLib::int32 a_shopId, BSLib::int32 a_id, SCardItemInfo*& a_shopItem);
	bool getShop(BSLib::int32 a_shopId, std::map<BSLib::int32, SCardItemInfo *>*& a_shopItemList);
	bool getShopConfig(BSLib::int32 a_shopId, SCardConfigInfo*& a_shopConfig);

	bool oneClick(CardType a_type, std::vector<BSLib::uint32>& a_ids, std::vector<BSLib::uint32>& a_nums);
	bool tenClick(CardType a_type, std::vector<BSLib::uint32>& a_ids, std::vector<BSLib::uint32>& a_nums, BSLib::uint32& a_event);
	bool getTriggerItem(BSLib::uint32& a_item);
	bool getConfig(CardSumType a_type, SCardConfigInfo*& info);
private:
	bool initRatio();
	bool getItem(std::vector<BSLib::uint32>& a_ids, std::vector<BSLib::uint32>& a_nums, BSLib::uint32 a_id);

	std::map<BSLib::int32, std::map<BSLib::int32, SCardItemInfo* >* > m_cardItemsHashMap;
	std::map<BSLib::int32, SCardConfigInfo* > m_cardConfigHashMap;

	std::map<std::string, std::vector<BSLib::int32> > m_ratio;
	std::map<BSLib::int32, std::set<BSLib::int32> > m_minLib; // ±£µ×¿â 
};


} // GM
} // CardSystem
} // BSLib


#endif // cardConfig_h__