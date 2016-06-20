#include <BSLib/utility/file/dirInfo.h>
#include <GSLib/shopSystem/GM/cardConfig.h>
#include <BSLib/utility/file/xmlFile.h>
#include <GSLib/tracer.h>
#include <algorithm>
#include <BSLib/utility/random.h>
#include <GSLib/prizeSystem/lexical.h>
#include <BSLib/utility/random.h>

namespace GSLib
{
namespace ShopSystem
{
namespace GM
{

CCardConfig::CCardConfig()
{
}

CCardConfig::~CCardConfig()
{	
}


typedef bool (*cbReadNode)(BSLib::Utility::CXmlFile& a_xmlFile, BSLib::Utility::HXmlNode& a_Node, BSLib::int32& a_Id, void*& a_config);


bool readCardConfigNode(BSLib::Utility::CXmlFile& a_xmlFile, BSLib::Utility::HXmlNode& a_Node, BSLib::int32& a_Id,
						void*& a_shopConfig)
{	

	bool success = true;
	SCardConfigInfo* item = new SCardConfigInfo;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_id", item->m_id) && success;
	a_Id = item->m_id;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_free_gold", item->m_free_gold) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_free_gold_cd", item->m_free_gold_cd) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_gold1_cost", item->m_gold1_cost) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_gold10_cost", item->m_gold10_cost) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_free_diamond", item->m_free_diamond) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_free_diamond_cd", item->m_free_diamond_cd) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_diamond1_cost", item->m_diamond1_cost) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_diamond10_cost", item->m_diamond10_cost) && success;
	std::string events;
	std::string prizes;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_event", events) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_prize", prizes) && success;
	do 
	{
		if(!success)
			break;

		if(events.empty() || "0" == events)
			break;

		success = false; // 默认为false;
		std::vector<std::string> sub_vips;
		if( !GSLib::PrizeSystem::lexicalCast(events, sub_vips, "|"))
			break;

		if(sub_vips.empty())
			break;

		for(std::vector<std::string>::size_type i = 0; i < sub_vips.size(); i++)
		{
			std::vector<BSLib::int32> vipPair;
			if(!GSLib::PrizeSystem::lexicalCast(sub_vips[i], vipPair, "_"))
				goto exit;

			if( 2 != vipPair.size())
				goto exit;

			item->m_event_names.push_back(vipPair[0]);
			item->m_event_ratio.push_back(vipPair[1]);
		}
		
		success = true;
	} while (false);

	do 
	{
		if(!success)
			break;

		if(prizes.empty() || "0" == prizes)
			break;

		success = false; // 默认为false;
		std::vector<std::string> sub_vips;
		if( !GSLib::PrizeSystem::lexicalCast(prizes, sub_vips, "|"))
			break;

		if(sub_vips.empty())
			break;

		for(std::vector<std::string>::size_type i = 0; i < sub_vips.size(); i++)
		{
			std::vector<BSLib::int32> vipPair;
			if(!GSLib::PrizeSystem::lexicalCast(sub_vips[i], vipPair, "_"))
				goto exit;

			if( 2 != vipPair.size())
				goto exit;

			item->m_prize_names.push_back(vipPair[0]);
			item->m_prize_ratio.push_back(vipPair[1]);
		}

		success = true;
	} while (false);


exit:

	if( !success){
		BSLIB_LOG_ERROR(ETT_GSLIB_SHOPSYSTEM, "获取item属性失败, id:%d", a_Id);
		delete item;
		return false;
	}

	a_shopConfig = item;
	a_Id = item->m_id;
	return true;
}


bool readCardItemNode(BSLib::Utility::CXmlFile& a_xmlFile, BSLib::Utility::HXmlNode& a_Node, BSLib::int32& a_Id,
					  void*& a_shopItem)
{	
	bool success = true;
	SCardItemInfo* item = new SCardItemInfo;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_id", item->m_id) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_type", item->m_Type) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_lib_type", item->m_libType) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_item", item->m_itemId) && success;
	std::string nums;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_num", nums) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_ratio", item->m_ratio) && success;
	success = GSLib::PrizeSystem::lexicalCast(nums, item->m_itemNum, ",") && success;
	if( !success){
		BSLIB_LOG_ERROR(ETT_GSLIB_SHOPSYSTEM, "获取item属性失败, id:%d", a_Id);
		delete item;
		return false;
	}

	a_shopItem = item;
	a_Id = item->m_id;
	return true;
}



template<class T>
bool loadXml(const std::string& a_path, std::map<BSLib::int32, T* >& container, cbReadNode a_cb)
{
	BSLib::Utility::CXmlFile xmlFile;

	if (!xmlFile.loadFile(a_path)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SHOPSYSTEM, "读取%s文件失败", a_path.c_str());
		return false;
	}
	BSLib::Utility::HXmlNode root = xmlFile.getRootNode();
	if (root == NULL) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SHOPSYSTEM, "获取%s文件根节点失败", a_path.c_str());
		return false;
	}
	BSLib::Utility::HXmlNode childerNode = xmlFile.getChildNode(root);
	bool success = true;
	for(; childerNode != NULL; childerNode = xmlFile.getNextNode(childerNode)) 
	{
		BSLib::Utility::CStringA nodeName;
		if (!xmlFile.getNodeName(childerNode, nodeName)) {
			success = false;
			break;
		}

		nodeName.toLower();
		if (nodeName != "item") {
			success = false;
			break;
		}

		BSLib::int32 id = 0;
		T* node = NULL;
		if (!(*a_cb)(xmlFile, childerNode, id, (void *&)node)) {
			success = false;
			break;
		}

		if (container.find(id) != container.end()) {
			success = false;
			break;
		}

		container.insert(std::make_pair(id, node));
	}

	if( !success){
		BSLIB_LOG_ERROR(ETT_GSLIB_SHOPSYSTEM, " 读取%s文件节点值失败", a_path.c_str());
	}

	xmlFile.clear();
	return success;
}

bool CCardConfig::loadConfigFile(const std::string& a_configFile)
{	
	std::string configPath(a_configFile);
	configPath +="\\shop\\t_card_config.xml";
	BSLib::Utility::CDirInfo::standardization(configPath);

	if( !loadXml(configPath, m_cardConfigHashMap, readCardConfigNode)){
		return false;
	}
	
	typedef std::map<BSLib::int32, SCardConfigInfo* > ShopConfigMap;
	std::string shopPath(a_configFile);
	shopPath += "\\shop\\";
	shopPath += "t_card_number.xml";

	typedef std::map<BSLib::int32, SCardItemInfo *> ShopMap;
	ShopMap *shop = new ShopMap;
	BSLib::Utility::CDirInfo::standardization(shopPath);
	if(!loadXml(shopPath, *shop, readCardItemNode)){
		return false;
	}

	m_cardItemsHashMap.insert(std::make_pair(1, shop));

	return initRatio();
}

bool CCardConfig::getCardItem(BSLib::int32 a_shopId, BSLib::int32 a_id, SCardItemInfo*& a_shopItem)
{	
	typedef std::map<BSLib::int32, SCardItemInfo *> ShopMap; 
	ShopMap* shop = NULL;
	if(!getShop(a_shopId, shop))
		return false;
	
	ShopMap::iterator it = shop->find(a_id);
	if( it == shop->end())
		return false;

	a_shopItem = it->second;
	return true;
}


bool CCardConfig::getShop(BSLib::int32 a_shopId, std::map<BSLib::int32, SCardItemInfo *>*& a_shopItemList)
{	
	typedef std::map<BSLib::int32, std::map<BSLib::int32, SCardItemInfo* >* > ShopItemMapMap;
	ShopItemMapMap::iterator it = m_cardItemsHashMap.find(a_shopId);
	if( it == m_cardItemsHashMap.end())
		return false;

	a_shopItemList = it->second;
	return true;
}

bool CCardConfig::getShopConfig(BSLib::int32 a_shopId, SCardConfigInfo*& a_shopConfig)
{	
	typedef std::map<BSLib::int32, SCardConfigInfo* > CardConfigMap;
	CardConfigMap::iterator it = m_cardConfigHashMap.find(a_shopId);
	if( it == m_cardConfigHashMap.end())
			return false;
		
	a_shopConfig = it->second;
	return true;
}

bool CCardConfig::initRatio()
{	
	typedef std::map<BSLib::int32, SCardItemInfo *> ItemInfo;
	typedef std::map<BSLib::int32, ItemInfo* > ShopItemMapMap;
	ShopItemMapMap::iterator it = m_cardItemsHashMap.find(1);
	if( it == m_cardItemsHashMap.end())
		return false;
	
	ItemInfo *info = it->second;
	typedef std::map<std::string, std::vector<BSLib::int32> > RatioMap_t;
	for(ItemInfo::iterator iit = info->begin(); iit != info->end(); ++iit)
	{
		SCardItemInfo * cardInfo = iit->second;
		std::string key;
		char buf[40] = {0};
		sprintf(buf, "%d:%d", cardInfo->m_Type, cardInfo->m_libType);
		key = buf;
		RatioMap_t::iterator it = m_ratio.find(key);
		if( it == m_ratio.end())
		{
			std::pair<RatioMap_t::iterator, bool> res 
				= m_ratio.insert(std::make_pair(key, std::vector<BSLib::int32>() ));
			it = res.first;
		}
		
		std::vector<BSLib::int32>& ratios = it->second;
		ratios.insert(ratios.begin(), cardInfo->m_ratio, cardInfo->m_id);	

		if( eLibType3 != cardInfo->m_libType)
			continue;
		
		typedef std::set<BSLib::int32> Int32Set_t;
		typedef std::map<BSLib::int32, Int32Set_t> MinLib_t;
		MinLib_t::iterator minIt = m_minLib.find(cardInfo->m_Type);
		if( minIt == m_minLib.end())
		{
			std::pair<MinLib_t::iterator, bool> res = m_minLib.insert(std::make_pair(cardInfo->m_Type, Int32Set_t()));
			minIt = res.first;
		}
		
		Int32Set_t& sets = minIt->second;
		sets.insert(cardInfo->m_id);
	}

	return true;
}

bool CCardConfig::oneClick(CardType a_type, std::vector<BSLib::uint32>& a_ids, std::vector<BSLib::uint32>& a_nums)
{	

	//  在值钱库里roll
	std::string key;
	char buf[40] = {0};
	sprintf(buf, "%d:%d", a_type, eLibType1);
	key = buf;
	
	typedef std::map<std::string, std::vector<BSLib::int32> > RatioMap_t;
	RatioMap_t::iterator it = m_ratio.find(key);
	if( it == m_ratio.end())
		return false;

	std::vector<BSLib::int32>& ratios1 = it->second;
	BSLib::uint32 rand1 = BSLib::Utility::CRandom::randomBetween(0, 9999);
	if( rand1 < ratios1.size())
	{
		return getItem(a_ids, a_nums, ratios1[rand1]);
	}

	// 在垃圾库里roll
	sprintf(buf, "%d:%d", a_type, eLibType2);
	key = buf;
	it = m_ratio.find(key);
	if( it == m_ratio.end())
		return false;
	
	std::vector<BSLib::int32>& ratios2 = it->second;
	if( ratios2.size() < 1)
		return false;
	BSLib::uint32 rand2 = BSLib::Utility::CRandom::randomBetween(0, ratios2.size() - 1);
	return getItem(a_ids, a_nums, ratios2[rand2]);	
}

bool CCardConfig::getItem(std::vector<BSLib::uint32>& a_ids, std::vector<BSLib::uint32>& a_nums, BSLib::uint32 a_id)
{
	typedef std::map<BSLib::int32, SCardItemInfo* > CardItem_t;
	typedef std::map<BSLib::int32, CardItem_t* > CardItemMap_t;
	CardItemMap_t::iterator it = m_cardItemsHashMap.find(1);
	if( it == m_cardItemsHashMap.end())
		return false;

	CardItem_t* info = it->second;
	CardItem_t::iterator cardIt = info->find(a_id);
	if( cardIt == info->end())
		return false;
	
	SCardItemInfo * cardInfo =cardIt->second;
	if( 2 == cardInfo->m_itemNum.size())
	{
		a_nums.push_back(BSLib::Utility::CRandom::randomBetween(cardInfo->m_itemNum[0], cardInfo->m_itemNum[1]));
	}
	else if( 1 == cardInfo->m_itemNum.size())
	{
		a_nums.push_back(cardInfo->m_itemNum[0]);
	}
	else 
	{
		return false;
	}

	a_ids.push_back(cardInfo->m_itemId);
	return true;
}

bool CCardConfig::tenClick(CardType a_type, std::vector<BSLib::uint32>& a_ids, std::vector<BSLib::uint32>& a_nums, BSLib::uint32& a_event)
{	
	for(int i = 0; i < 9; i++)
	{
		if( !oneClick(a_type, a_ids, a_nums))
			return false;
	}
	
	// 在10连抽保底库里抽
	typedef std::set<BSLib::int32> Int32Set_t;
	typedef std::map<BSLib::int32, Int32Set_t> MinLib_t;
	MinLib_t::iterator minIt = m_minLib.find(a_type);
	if( minIt == m_minLib.end())
		return false;

	Int32Set_t& sets = minIt->second;
	bool needBaodi = true;
	for(std::vector<BSLib::uint32>::iterator sectionIt = a_ids.begin(); sectionIt != a_ids.end(); ++sectionIt)
	{
		Int32Set_t::iterator findIt = sets.find(*sectionIt);
		if(findIt != sets.end())
		{
			needBaodi = false;
			break;
		}
	}
	
	// 从保底库里抽取
	if( needBaodi)
	{	
		std::string key;
		char buf[40] = {0};
		sprintf(buf, "%d:%d", a_type, eLibType3);
		key = buf;
		typedef std::map<std::string, std::vector<BSLib::int32> > RatioMap_t;
		RatioMap_t::iterator it = m_ratio.find(key);
		if( it == m_ratio.end())
			return false;

		std::vector<BSLib::int32>& ratios3 = it->second;
		if( ratios3.size() < 1)
			return false;
		BSLib::uint32 rand3 = BSLib::Utility::CRandom::randomBetween(0, ratios3.size() - 1);
		getItem(a_ids, a_nums, ratios3[rand3]);	
	}
	else
	{
		oneClick(a_type, a_ids, a_nums);
	}

	BSLib::uint32 myType = 2;
	if( eCardTypeGuangZiLiDiamond != a_type && eCardTypeGuangZiLiGold != a_type)
	{
		return true; // 只有光子力有事件
	}

	typedef std::map<BSLib::int32, SCardConfigInfo* > CardConfig_t;
	CardConfig_t::iterator configIt = m_cardConfigHashMap.find(myType);
	if( configIt == m_cardConfigHashMap.end())
		return false;

	SCardConfigInfo* configInfo = configIt->second;
	std::vector<BSLib::int32> all;
	for(size_t i = 0; i < configInfo->m_event_names.size() ; ++i)
	{
		all.insert(all.begin(), configInfo->m_event_ratio[i], configInfo->m_event_names[i]);
	}
	
	if( all.size() < 1)
		return false;

	BSLib::uint32 res = BSLib::Utility::CRandom::randomBetween(0, all.size() - 1);
	a_event = all[res];
	return true;
}

bool CCardConfig::getTriggerItem(BSLib::uint32& a_item)
{	
	BSLib::uint32 myType = 2;
	typedef std::map<BSLib::int32, SCardConfigInfo* > CardConfig_t;
	CardConfig_t::iterator configIt = m_cardConfigHashMap.find(myType);
	if( configIt == m_cardConfigHashMap.end())
		return false;

	SCardConfigInfo* configInfo = configIt->second;
	std::vector<BSLib::int32> all;
	for(size_t i = 0; i < configInfo->m_prize_names.size() ; ++i)
	{
		all.insert(all.begin(), configInfo->m_prize_ratio[i], configInfo->m_prize_names[i]);
	}

	if( all.size() < 1)
		return false;

	BSLib::uint32 res = BSLib::Utility::CRandom::randomBetween(0, all.size() - 1);
	a_item = all[res];
	return true;
}

bool CCardConfig::getConfig(CardSumType a_type, SCardConfigInfo*& info)
{
	typedef std::map<BSLib::int32, SCardConfigInfo* > CardConfig_t;
	CardConfig_t::iterator configIt = m_cardConfigHashMap.find(a_type);
	if( configIt == m_cardConfigHashMap.end())
		return false;

	info = configIt->second;
	return true;
}


} // GM
} // CardSystem
} // GSLib