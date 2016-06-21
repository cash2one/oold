/*
#include <GSLib/itemSystem/msgItemSystemGC.h>
#include <GSLib/itemSystem/msgItemSystem.h>
#include <GSLib/tracer.h>
#include <BSLib/utility/file/dirInfo.h>
#include <BSLib/utility/table.h>
#include <GSLib/itemSystem/GM/itemstaticdatagmmgr.h>
namespace GSLib
{

namespace ItemSystem
{	

namespace GM
{

BSLIB_SINGLETON_DEFINE(CItemStaticDataGMMgr);

CItemStaticDataGMMgr::CItemStaticDataGMMgr()
:m_uniqueIDByItemIndex(0, ROLE_ITEM_MAXTYPE_ID, INVALID_ITEMINDEX)
{
	m_uniqueIDByItemIndex.setUniqueIDMgr(this);
}

CItemStaticDataGMMgr::~CItemStaticDataGMMgr()
{
}

void CItemStaticDataGMMgr::init()
{
	;
}

void CItemStaticDataGMMgr::final()
{
	removeAllItemDataGM();
	removeAllItemUseConfigGM();
	removeAllItemSellConfigGM();
}

bool CItemStaticDataGMMgr::loadGameConfig(const std::string& a_configPath)
{
	if (!_loadItemConfig(a_configPath)){
		return false;
	}

	if (!_loadItemUseConfig(a_configPath)){
		return false;
	}

	if (!_loadItemSellConfig(a_configPath)){
		return false;
	}


	return true;
}

bool CItemStaticDataGMMgr::_loadItemConfig(const std::string& a_configPath)
{

	BSLib::Utility::CStringA configPath = a_configPath;
	configPath += "\\item\\";
	BSLib::Utility::CDirInfo::standardization(configPath);

	std::string fileName = configPath + "t_item_config.xml";
	BSLib::Utility::CStringA itemAttrPath(fileName);

	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(itemAttrPath)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_ITEMSYSTEM, "加载物品配置失败[%s]", itemAttrPath.c_str());
		return false;
	}
	try {
		BSLIB_LOG_INFOR(ETT_GSLIB_ITEMSYSTEM, "加载物品配置[%s]", itemAttrPath.c_str());
		BSLib::Utility::CTable& table = tableSheet["item"];
		for (BSLib::uint32 i=0; i < table.getRowCount(); ++i) {

			CItemStaticDataGM *itemData = new CItemStaticDataGM();
			if(itemData == NULL){
				BSLIB_LOG_ERROR(ETT_GSLIB_ITEMSYSTEM, "加载物品配置文件失败[itemData == NULL]");
				return false;
			}
			itemData->loadData(table[i]);
			BSLib::uint64 key = itemData->getUniqueID();
			m_ItemDataHashMap.setValue(key,itemData);
		}
		if(table.getRowCount() != m_ItemDataHashMap.size()){
			BSLIB_LOG_ERROR(ETT_GSLIB_ITEMSYSTEM, "加载物品配置文件失败,未加载完全[table.getRowCount()=%d][m_ItemDataHashMap.size()=%d]",table.getRowCount(),m_ItemDataHashMap.size());
			return false;
		}
	} catch (...){
		BSLIB_LOG_ERROR(ETT_GSLIB_ITEMSYSTEM, "加载物品配置文件失败[%s]", itemAttrPath.c_str());
		return false;
	}
	return true;
}


bool CItemStaticDataGMMgr::_loadItemUseConfig(const std::string& a_configPath)
{
	BSLib::Utility::CStringA configPath = a_configPath;
	configPath += "\\item\\";
	BSLib::Utility::CDirInfo::standardization(configPath);

	std::string fileName = configPath + "t_item_use_config.xml";
	BSLib::Utility::CStringA roleAttrPath(fileName);

	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(roleAttrPath)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_ITEMSYSTEM, "加载物品使用配置失败loadXmlFile[%s]", roleAttrPath.c_str());
		return false;
	}
	try {
		BSLIB_LOG_INFOR(ETT_GSLIB_ITEMSYSTEM, "加载物品使用配置[%s]", roleAttrPath.c_str());
		BSLib::Utility::CTable& table = tableSheet["item"];
		for (BSLib::uint32 i=0; i < table.getRowCount(); ++i) {
			SItemUseConfig* itemUseConfig = new SItemUseConfig();
			itemUseConfig->loadData(table[i]);
			m_itemUseDataHashMap.setValue(itemUseConfig->m_id,itemUseConfig);
		}
	} catch (...){
		BSLIB_LOG_ERROR(ETT_GSLIB_ITEMSYSTEM, "加载物品使用配置文件失败[Exception][%s]", roleAttrPath.c_str());
		return false;
	}
	return true;
}

bool CItemStaticDataGMMgr::_loadItemSellConfig(const std::string& a_configPath)
{

	BSLib::Utility::CStringA configPath = a_configPath;
	configPath += "\\item\\";
	BSLib::Utility::CDirInfo::standardization(configPath);

	std::string fileName = configPath + "t_item_sell_config.xml";
	BSLib::Utility::CStringA roleAttrPath(fileName);

	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(roleAttrPath)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_ITEMSYSTEM, "加载物品销售配置失败loadXmlFile[%s]", roleAttrPath.c_str());
		return false;
	}
	try {
		BSLIB_LOG_INFOR(ETT_GSLIB_ITEMSYSTEM, "加载物品销售配置[%s]", roleAttrPath.c_str());
		BSLib::Utility::CTable& table = tableSheet["item"];
		for (BSLib::uint32 i=0; i < table.getRowCount(); ++i) {
			SItemSellConfig* itemConfig = new SItemSellConfig();
			itemConfig->loadData(table[i]);
			m_itemSellDataHashMap.setValue(itemConfig->m_id,itemConfig);
		}
	} catch (...){
		BSLIB_LOG_ERROR(ETT_GSLIB_ITEMSYSTEM, "加载物品销售配置文件失败[Exception][%s]", roleAttrPath.c_str());
		return false;
	}
	return true;
}

bool CItemStaticDataGMMgr::checkUniqueID(BSLib::uint32 id)
{
	return m_ItemDataHashMap.find(id) != m_ItemDataHashMap.end();
}

CItemStaticDataGM* CItemStaticDataGMMgr::getItemStaticDataGM(const BSLib::uint32 a_itemTPID,GSLib::ItemSystem::GM::EItemType a_itemType)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_ITEMSYSTEM, "getItemStaticDataGM[a_itemTPID=%d][a_itemType=%d]", a_itemTPID,a_itemType);
	CItemStaticDataGM* data = NULL;
	BSLib::uint64 key = _makeUInt64Key(a_itemTPID,(BSLib::uint32)a_itemType);
	m_ItemDataHashMap.getValue(key,data);
	return data;
}

void CItemStaticDataGMMgr::removeAllItemDataGM()
{
	BSLib::Utility::CHashMap<BSLib::uint64, CItemStaticDataGM*>::iterator it = m_ItemDataHashMap.begin();

	for (; it != m_ItemDataHashMap.end(); ++it) {
		CItemStaticDataGM* itemData =  it->second;
		if (itemData == NULL) {
			continue;
		}
		BSLIB_SAFE_DELETE(itemData);
	}
	m_ItemDataHashMap.clear();
}

SItemUseConfig* CItemStaticDataGMMgr::getItemUseConfigGM(const BSLib::uint32 a_itemTPID)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_ITEMSYSTEM, "getItemStaticDataGM[a_itemTPID=%d]", a_itemTPID);
	BSLib::Utility::CHashMap<BSLib::uint32, SItemUseConfig*>::iterator it = m_itemUseDataHashMap.begin();
	SItemUseConfig *itemData = NULL;
	for(;it != m_itemUseDataHashMap.end(); ++it){
		itemData = it->second;
		if(itemData->m_id == a_itemTPID){
			break;
		}
	}
	return itemData;
}

void CItemStaticDataGMMgr::removeAllItemUseConfigGM()
{
	BSLib::Utility::CHashMap<BSLib::uint32, SItemUseConfig*>::iterator it = m_itemUseDataHashMap.begin();

	for (; it != m_itemUseDataHashMap.end(); ++it) {
		SItemUseConfig* itemData =  it->second;
		if (itemData == NULL) {
			continue;
		}
		BSLIB_SAFE_DELETE(itemData);
	}
	m_itemUseDataHashMap.clear();
}

SItemSellConfig* CItemStaticDataGMMgr::getItemSellConfigGM(const BSLib::uint32 a_itemTPID)
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_ITEMSYSTEM, "getItemStaticDataGM[a_itemTPID=%d]", a_itemTPID);
	BSLib::Utility::CHashMap<BSLib::uint32, SItemSellConfig*>::iterator it = m_itemSellDataHashMap.begin();
	SItemSellConfig *itemData = NULL ;
	for(;it != m_itemSellDataHashMap.end(); ++it){
		itemData = it->second;
		if (itemData == NULL) {
			continue;
		}
		if(itemData->m_id == a_itemTPID){
			break;
		}
	}
	return itemData;
}

void CItemStaticDataGMMgr::removeAllItemSellConfigGM()
{
	BSLib::Utility::CHashMap<BSLib::uint32, SItemSellConfig*>::iterator it = m_itemSellDataHashMap.begin();

	for (; it != m_itemSellDataHashMap.end(); ++it) {
		SItemSellConfig* itemData =  it->second;
		if (itemData == NULL) {
			continue;
		}
		BSLIB_SAFE_DELETE(itemData);
	}
	m_itemSellDataHashMap.clear();
}

BSLib::uint64 CItemStaticDataGMMgr::_makeUInt64Key(BSLib::uint32 a_left,BSLib::uint32 a_right)
{
	BSLib::uint64 left = (((BSLib::uint64)a_right) << (32)) & 0XFFFFFFFF00000000;
	BSLib::uint64 right = ((BSLib::uint64)a_left) & 0X00000000FFFFFFFF;
	BSLib::uint64 key = (left)|(right);
	return key;
}

}//GM

}//ItemSystem

}//GSLib
*/
