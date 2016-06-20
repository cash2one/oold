#include <BSLib/utility/file/dirInfo.h>
#include <GSLib/shopSystem/GM/shopConfig.h>
#include <BSLib/utility/file/xmlFile.h>
#include <GSLib/tracer.h>
#include <GSLib/shopSystem/msgNumIDShopSystem.h>
#include <algorithm>
#include <BSLib/utility/random.h>
#include <GSLib/prizeSystem/lexical.h>

namespace GSLib
{
namespace ShopSystem
{
namespace GM
{

CShopConfig::CShopConfig()
{
}

CShopConfig::~CShopConfig()
{	
	typedef std::map<BSLib::int32, SShopItemInfo* > ShopItemMap_t;
	typedef std::map<BSLib::int32, ShopItemMap_t* > ShopItemMapMap_t;
	for(ShopItemMapMap_t::iterator it = m_shopItemsHashMap.begin(); it != m_shopItemsHashMap.end(); ++it)
	{
		ShopItemMap_t* obj = it->second;
		for(ShopItemMap_t::iterator subIt = obj->begin(); subIt != obj->end(); ++subIt)
		{
			delete subIt->second;
		}

		delete obj;
	}

	typedef std::map<BSLib::int32, SShopConfigInfo* > ShopConfig_t;
	for(ShopConfig_t::iterator it = m_shopConfigHashMap.begin(); it != m_shopConfigHashMap.end(); ++it)
	{
		delete it->second;
	}
		
}


typedef bool (*cbReadNode)(BSLib::Utility::CXmlFile& a_xmlFile, BSLib::Utility::HXmlNode& a_Node, BSLib::int32& a_Id, void*& a_config);


bool readShopConfigNode(BSLib::Utility::CXmlFile& a_xmlFile, BSLib::Utility::HXmlNode& a_Node, BSLib::int32& a_Id,
						void*& a_shopConfig)
{	

	bool success = true;
	SShopConfigInfo* item = new SShopConfigInfo;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_id", item->m_id) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_shop_path", item->m_shopPath) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_show_num", item->m_showNum) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_refresh_period", item->m_refreshPeriod) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_manual_refresh", item->m_manualRefresh) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_pay_type", item->m_payType) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_price", item->m_price) && success;
	std::string vip_string;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_vip", vip_string) && success;
	do 
	{
		if(!success)
			break;

		if(vip_string.empty() || "0" == vip_string)
			break;

		success = false; // 默认为false;
		std::vector<std::string> sub_vips;
		if( !GSLib::PrizeSystem::lexicalCast(vip_string, sub_vips, "|"))
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

			item->m_vip_prices.insert(std::make_pair(vipPair[0], vipPair[1]));
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


bool readShopItemNode(BSLib::Utility::CXmlFile& a_xmlFile, BSLib::Utility::HXmlNode& a_Node, BSLib::int32& a_Id,
					  void*& a_shopItem)
{	

	bool success = true;
	SShopItemInfo* item = new SShopItemInfo;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_id", item->m_id) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_item_type", item->m_itemType) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_item_id", item->m_itemId) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_item_no", item->m_itemNum) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_pay_type", item->m_payType) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_price", item->m_price) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_limit_num", item->m_limitNum) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_discount", item->m_discount) && success;
	if( !success){
		BSLIB_LOG_ERROR(ETT_GSLIB_SHOPSYSTEM, "获取item属性失败, id:%d", a_Id);
		delete item;
		return false;
	}

	a_shopItem = item;
	a_Id = item->m_id;
	return true;
}

bool readPVPShopItemNode(BSLib::Utility::CXmlFile& a_xmlFile, BSLib::Utility::HXmlNode& a_Node, BSLib::int32& a_Id,
					  void*& a_shopItem)
{	

	bool success = true;
	SPVPShopItemInfo* item = new SPVPShopItemInfo;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_id", item->m_id) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_item_type", item->m_itemType) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_item_id", item->m_itemId) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_item_no", item->m_itemNum) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_pay_type", item->m_payType) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_price", item->m_price) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_limit_num", item->m_limitNum) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_discount", item->m_discount) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_probability", item->m_probability) && success;
	success = a_xmlFile.getNodeAttrValue(a_Node, "f_flag", item->m_flag) && success;
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

bool CShopConfig::loadConfigFile(const std::string& a_configFile)
{	
	std::string configPath(a_configFile);
	configPath +="\\shop\\t_shop_cfg_data.xml";
	BSLib::Utility::CDirInfo::standardization(configPath);

	if( !loadXml(configPath, m_shopConfigHashMap, readShopConfigNode)){
		return false;
	}
	
	typedef std::map<BSLib::int32, SShopConfigInfo* > ShopConfigMap;
	bool success = true;
	for(ShopConfigMap::iterator it = m_shopConfigHashMap.begin(); it != m_shopConfigHashMap.end(); ++it)
	{
		SShopConfigInfo* info = it->second;
		std::string shopPath(a_configFile);
		shopPath += "\\shop\\";
		shopPath += info->m_shopPath;
		shopPath += ".xml";

		typedef std::map<BSLib::int32, SShopItemInfo *> ShopMap;
		ShopMap *shop = new ShopMap;
		if(ESHOPTYPE_PVP == info->m_id){
			BSLib::Utility::CDirInfo::standardization(shopPath);
			if( !loadXml(shopPath, *shop, readPVPShopItemNode)){
				success = false;
				break;
			}

			_initPVPProbability(shop);
		}
		else {
			BSLib::Utility::CDirInfo::standardization(shopPath);
			if(!loadXml(shopPath, *shop, readShopItemNode)){
				success = false;
				break;
			}
		}
		
		m_shopItemsHashMap.insert(std::make_pair(info->m_id, shop));
	}

	return success;
}

void CShopConfig::_initPVPProbability(std::map<BSLib::int32, SShopItemInfo *>* a_pvpMap)
{
	std::map<BSLib::int32, SShopItemInfo *>::iterator it = a_pvpMap->begin();
	for(; it != a_pvpMap->end(); ++it){
		SPVPShopItemInfo* info = (SPVPShopItemInfo *)it->second;
		for(BSLib::int32 i = 0; i < info->m_probability; i++){
			m_pvpProbability.push_back(it->first);
		}

		if(1 == info->m_flag){
			m_specialIds.push_back(it->first);
		}
	}
}

bool CShopConfig::getShopItem(BSLib::int32 a_shopId, BSLib::int32 a_id, SShopItemInfo*& a_shopItem)
{	
	typedef std::map<BSLib::int32, SShopItemInfo *> ShopMap; 
	ShopMap* shop = NULL;
	if(!getShop(a_shopId, shop))
		return false;
	
	ShopMap::iterator it = shop->find(a_id);
	if( it == shop->end())
		return false;

	a_shopItem = it->second;
	return true;
}

BSLib::int32 CShopConfig::getDiscount(BSLib::int32 a_shopId, BSLib::int32 a_vipLevel)
{
	SShopConfigInfo *config = NULL;
	if( !getShopConfig(a_shopId, config))
		return 0;

	std::map<BSLib::int32, BSLib::int32>::reverse_iterator it = config->m_vip_prices.rbegin();
	for(; it != config->m_vip_prices.rend(); ++it)
	{
		if(a_vipLevel >= it->first)
			return it->second;
	}

	return 100;
}

bool CShopConfig::getShop(BSLib::int32 a_shopId, std::map<BSLib::int32, SShopItemInfo *>*& a_shopItemList)
{	
	typedef std::map<BSLib::int32, std::map<BSLib::int32, SShopItemInfo* >* > ShopItemMapMap;
	ShopItemMapMap::iterator it = m_shopItemsHashMap.find(a_shopId);
	if( it == m_shopItemsHashMap.end())
		return false;

	a_shopItemList = it->second;
	return true;
}

bool CShopConfig::getShopConfig(BSLib::int32 a_shopId, SShopConfigInfo*& a_shopConfig)
{	
	typedef std::map<BSLib::int32, SShopConfigInfo* > ShopConfigMap;
	ShopConfigMap::iterator it = m_shopConfigHashMap.find(a_shopId);
	if( it == m_shopConfigHashMap.end())
		return false;
	
	a_shopConfig = it->second;
	return true;
}

bool CShopConfig::getPVPShopShowItem(BSLib::int32 a_shopId, bool a_usePaidCount, BSLib::uint32& a_paidRefreshCount, std::vector<BSLib::int32>& a_ids)
{	
	SShopConfigInfo* shopConfig = NULL;
	if( !getShopConfig(a_shopId, shopConfig)){
		return false;
	}
	
	BSLib::int32 showNUm = shopConfig->m_showNum;
	if( 0 == showNUm){
		return false;
	}
	
	// 假如 全部显示
	if( -1 == showNUm || 0 == showNUm){
		std::map<BSLib::int32, SShopItemInfo *>* shopItemList = NULL;
		if( !getShop(a_shopId, shopItemList)){
			return false;
		}

		std::map<BSLib::int32, SShopItemInfo *>::iterator it = shopItemList->begin();
		for(; it != shopItemList->end(); ++it){
			a_ids.push_back(it->first);
		}

		return true;
	}
	
	// 部分显示
	BSLib::int32 left = showNUm;
	if(a_usePaidCount && a_paidRefreshCount >= 10 && !m_specialIds.empty()){
		a_paidRefreshCount -= 10;
		std::random_shuffle(m_specialIds.begin(), m_specialIds.end());
		a_ids.push_back(m_specialIds[0]);
		left--;
	}
	
	while( left > 0){
		BSLib::int32 randNum = BSLib::Utility::CRandom::randomBetween(0, m_pvpProbability.size() - 1);
		BSLib::int32 id = m_pvpProbability[randNum];
		if(std::find(a_ids.begin(), a_ids.end(), id) == a_ids.end()){
			a_ids.push_back(id);
			left--;
		}
	}

	return true;
}

bool CShopConfig::getShopShowItem(BSLib::int32 a_shopId, std::vector<BSLib::int32>& a_ids)
{
	std::map<BSLib::int32, SShopItemInfo *>* shopItemList = NULL;
	if( !getShop(a_shopId, shopItemList)){
		return false;
	}

	std::vector<BSLib::int32> ids;
	std::map<BSLib::int32, SShopItemInfo *>::iterator it = shopItemList->begin();
	for(; it != shopItemList->end(); ++it){
		ids.push_back(it->first);
	}

	SShopConfigInfo* shopConfig = NULL;
	if( !getShopConfig(a_shopId, shopConfig)){
		return false;
	}

	if( -1 == shopConfig->m_showNum || 0 == shopConfig->m_showNum){
		a_ids = ids;
	}
	else{
		std::random_shuffle(ids.begin(), ids.end());
		BSLib::int32 size = ids.size();
		BSLib::int32 min_size = shopConfig->m_showNum < size ? shopConfig->m_showNum : size;
		std::copy(ids.begin(), ids.begin() + min_size, std::back_inserter(a_ids));
	}
	
	return true;
}


} // GM
} // ShopSystem
} // GSLib