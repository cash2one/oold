
#include <GSLib/itemSystem/msgItemSystemGC.h>
#include <GSLib/itemSystem/msgItemSystem.h>
#include <GSLib/tracer.h>
#include <BSLib/utility/file/dirInfo.h>
#include <BSLib/utility/table.h>
#include <GSLib/itemSystem/GM/itemGMMgr.h>
#include <math.h>
#include <BSLib/utility/random.h>
namespace GSLib
{

namespace ItemSystem
{	

namespace GM
{

BSLIB_SINGLETON_DEFINE(CItemGMMgr);

CItemGMMgr::CItemGMMgr()
{

}

CItemGMMgr::~CItemGMMgr()
{
}

void CItemGMMgr::init()
{
	;
}

void CItemGMMgr::final()
{
	_removeAllItem();
}

bool CItemGMMgr::loadGameConfig(const std::string& a_configPath)
{
	if (!_loadItemConfig(a_configPath)){
		return false;
	}
	return true;
}

bool CItemGMMgr::_loadItemConfig(const std::string& a_configPath)
{
	BSLib::Utility::CStringA configPath = a_configPath;
	configPath += "\\item\\";
	std::string fileName = configPath + "t_item_config.xml";
	BSLib::Utility::CDirInfo::standardization(fileName);
	BSLib::Utility::CStringA path(fileName);

	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(path)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_ITEMSYSTEM, "[LOADCONFIG_ERROR][%s]", path.c_str());
		return false;
	}
	try {
		BSLIB_LOG_DEBUG(ETT_GSLIB_ITEMSYSTEM, "加载物品配置[%s]", path.c_str());
		BSLib::Utility::CTable& table = tableSheet["item"];
		for (BSLib::uint32 i=0; i < table.getRowCount(); ++i) {
			CItemDataGM *itemData = new CItemDataGM();
			if(itemData == NULL){
				BSLIB_LOG_ERROR(ETT_GSLIB_ITEMSYSTEM, "[MEMERROR]加载物品分配内存失败");
				return false;
			}
			itemData->loadData(table[i]);
			ItemTPID key = itemData->getTPID();
            if(itemData->getMainType() == EMAIN_TP_PET){
                m_petTPIDArray.push_back(key);
            }
			m_itemHashMap.setValue(key,itemData);
		}
		if(table.getRowCount() != m_itemHashMap.size()){
			BSLIB_LOG_ERROR(ETT_GSLIB_ITEMSYSTEM, "未加载完全[RowCount=%d][size=%d][%s]",table.getRowCount(),m_itemHashMap.size(), path.c_str());
			return false;
		}
	} catch (...){
		BSLIB_LOG_ERROR(ETT_GSLIB_ITEMSYSTEM, "[LOADCONFIG_ERROR][Exception][%s]", path.c_str());
		return false;
	}
	return true;
}

CItemDataGM* CItemGMMgr::getItem(ItemTPID a_tpid) const
{
	CItemDataGM* data = NULL;
	m_itemHashMap.getValue(a_tpid,data);
	return data;
}

BSLib::uint32 CItemGMMgr::getAddVitality(ItemTPID a_tpid) const
{
    CItemDataGM* item = getItem(a_tpid);
    if(NULL == item){
        return 0;
    }
    return item->getSpecfunc1();
}

BSLib::uint32 CItemGMMgr::getBuyVitalityMaxTimes(BSLib::uint32 vipLevel) const
{
     switch(vipLevel)
     {
     case 0: return 1;
     case 1: return 2;
     case 2: return 2;
     case 3: return 3;
     case 4: return 3;
     case 5: return 4;
     case 6: return 4;
     case 7: return 5;
     case 8: return 5;
     case 9: return 6;
     case 10:return 7;
     default:return 0;
     }
}

BSLib::uint32 CItemGMMgr::getBuyVitalityNeedDiamond(BSLib::uint32 a_buyTimes) const
{
    //float fDiamond = pow(1.26f,(float)a_buyTimes);
    //BSLib::uint32 addDiamond = (BSLib::uint32)floor(fDiamond);
    //BSLib::uint32 totalDiamond = 9 + addDiamond;
    //return totalDiamond;
	return  100 + 50 * (a_buyTimes - 1) * (a_buyTimes - 1);
}

bool CItemGMMgr::getCombineGemTPID(ItemTPID a_itemTPID,ItemTPID& a_newGemTPID) const
{
    CItemDataGM* itemData = getItem( a_itemTPID);
    if(itemData == NULL){
        return false;
    }

    if(getType(a_itemTPID) != EITEM_TP_GEMS){
        return false;
    }
    a_newGemTPID = itemData->getSpecfunc1();

    if(getType(a_newGemTPID) != EITEM_TP_GEMS){
        return false;
    }
    return true;
}

BSLib::uint32 CItemGMMgr::getPetAddFriendlyValue(bool isFavorite, ItemTPID a_tpid) const
{
    CItemDataGM* item = getItem(a_tpid);
    if(NULL == item){
        return 0;
    }
	return isFavorite ? item->getSpecfunc1() : item->getSpecfunc2();
}

BSLib::uint32 CItemGMMgr::getPetMaxLevel(ItemTPID a_tpid) const
{
    CItemDataGM* item = getItem(a_tpid);
    if(NULL == item){
        return 100;
    }
    return item->getLevel();
}

bool CItemGMMgr::getPetAttrB(ItemTPID a_tpid,EAttrID a_attrID,float& a_b) const
{
    CItemDataGM* itemData = getItem(a_tpid);
    if(itemData == NULL){
        return false;
    }

    a_b = itemData->getAttrValue(a_attrID);
    return true;
}

bool CItemGMMgr::getGemAttr(ItemTPID a_tpid,SBattleAttribute& a_battleAttr) const
{
     CItemDataGM* itemData = getItem(a_tpid);
    if(itemData == NULL){
        return false;
    }
    itemData->getGemAttr(a_battleAttr);
    return true;
}

bool CItemGMMgr::getPetTPIDArray(std::vector<ItemTPID>& a_petTPIDArrays) const
{
    a_petTPIDArrays = m_petTPIDArray;
    return true;
}

bool CItemGMMgr::getPetBaseAttrs(ItemTPID a_tpid,SBattleAttribute& a_petBaseAttr) const
{
    CItemDataGM* item = getItem(a_tpid);
    if(NULL == item){
        return false;
    }
    return item->getPetBaseAttrs(a_petBaseAttr);
}

bool CItemGMMgr::getPetUpgradeAttrs(ItemTPID a_tpid,SBattleAttribute& a_petUpgradeAttr) const
{
    CItemDataGM* item = getItem(a_tpid);
    if(NULL == item){
        return false;
    }
    return item->getPetUpgradeAttrs(a_petUpgradeAttr);
}

bool CItemGMMgr::isValid(ItemTPID a_tpid) const
{
	if(NULL == getItem(a_tpid)){
        BSLIB_LOG_ERROR(ETT_GSLIB_ITEMSYSTEM, "InValid[a_tpid=%d]", a_tpid);
		return false;
	}
	return true;
}

bool CItemGMMgr::isUse(ItemTPID a_tpid) const
{
	CItemDataGM* item = getItem(a_tpid);
	if(NULL == item){
		return false;
	}
	return item->isUse();
}

bool CItemGMMgr::isSell(ItemTPID a_tpid) const
{
    CItemDataGM* item = getItem(a_tpid);
    if(NULL == item){
        return false;
    }
    return item->isSell();
}

bool CItemGMMgr::isRepeated(ItemTPID a_tpid) const
{
    CItemDataGM* item = getItem(a_tpid);
    if(NULL == item){
        return false;
    }
    if (item->getStackCount() <= 1){
        return false;
    }

    return true;
}

bool CItemGMMgr::isTPResource(ItemTPID a_tpid) const
{
    EMainType type = getMainType(a_tpid);
    if(EMAIN_TP_RESOURCE == type){
        return true;
    }
    return false;
}

bool CItemGMMgr::isTPItem(ItemTPID a_tpid) const
{
    EMainType type = getMainType(a_tpid);
    if(EMAIN_TP_ITEM== type){
        return true;
    }
    return false;
}

float CItemGMMgr::getItemValue(ItemTPID a_tpid) const
{
    CItemDataGM* item = getItem(a_tpid);
    if(NULL == item){
        return 0;
    }
    return item->getItemValue();
}

BSLib::uint32 CItemGMMgr::getPrice(ItemTPID a_tpid) const
{
    CItemDataGM* item = getItem(a_tpid);
    if(NULL == item){
        return 0;
    }
    return item->getPrice();
}

BSLib::uint32 CItemGMMgr::getStackCount(ItemTPID a_tpid) const
{
	CItemDataGM* item = getItem(a_tpid);
	if(NULL == item){
		return 0;
	}
	return item->getStackCount();
}

EItemType CItemGMMgr::getType(ItemTPID a_tpid) const
{
	CItemDataGM* item = getItem(a_tpid);
	if(NULL == item){
		return EITEM_TP_IVALID;
	}
	return item->getType();
}

EMainType CItemGMMgr::getMainType(ItemTPID a_tpid) const
{
    CItemDataGM* item = getItem(a_tpid);
    if(NULL == item){
        return EMAIN_TP_IVALID;
    }
    return item->getMainType();
}


EQualityID CItemGMMgr::getQualityID(ItemTPID a_tpid) const
{
    CItemDataGM* item = getItem(a_tpid);
    if(NULL == item){
        return QUALITY_INVALID;
    }
    return item->getQualityID();
}

BSLib::uint32 CItemGMMgr::getProLimit(ItemTPID a_tpid) const
{  
    CItemDataGM* item = getItem(a_tpid);
    if(NULL == item){
        return EITEM_TP_IVALID;
    }
    return item->getProLimit();
}

BSLib::uint32 CItemGMMgr::getLevelLimit(ItemTPID a_tpid) const
{  
    CItemDataGM* item = getItem(a_tpid);
    if(NULL == item){
        return EITEM_TP_IVALID;
    }
    return item->getLevel();
}

BSLib::uint32 CItemGMMgr::getSpecfunc1(ItemTPID a_tpid) const
{  
    CItemDataGM* item = getItem(a_tpid);
    if(NULL == item){
        return EITEM_TP_IVALID;
    }
    return item->getSpecfunc1();
}

BSLib::uint32 CItemGMMgr::getSpecfunc2(ItemTPID a_tpid) const
{  
    CItemDataGM* item = getItem(a_tpid);
    if(NULL == item){
        return EITEM_TP_IVALID;
    }
    return item->getSpecfunc2();
}

std::string CItemGMMgr::getSpecfunc3(ItemTPID a_tpid) const
{  
    CItemDataGM* item = getItem(a_tpid);
    if(NULL == item){
        return "";
    }
    return item->getSpecfunc3();
}

std::string CItemGMMgr::getSpecfunc4(ItemTPID a_tpid) const
{  
    CItemDataGM* item = getItem(a_tpid);
    if(NULL == item){
        return "";
    }
    return item->getSpecfunc4();
}

bool CItemGMMgr::isPetLovelyItems(ItemTPID a_tpid,ItemTPID a_lovelyItemTPID) const
{
    CItemDataGM* item = getItem(a_tpid);
    if(NULL == item){
        return false;
    }
    std::vector<ItemTPID> itemTPIDArray = item->getPetLovelyItems();
    for(BSLib::uint32 i=0;i<itemTPIDArray.size(); ++i){
        ItemTPID tpid = itemTPIDArray[i];
        if(tpid == a_lovelyItemTPID){
            return true;
        }
    }

    return false;
}

bool CItemGMMgr::getPetLovelyItems(ItemTPID a_tpid,std::vector<ItemTPID>& a_itemTPIDArray) const
{  
    CItemDataGM* item = getItem(a_tpid);
    if(NULL == item){
        return false;
    }
    a_itemTPIDArray = item->getPetLovelyItems();
    return true;
}

bool CItemGMMgr::getSynthesisArray(ItemTPID a_tpid,std::vector<CPrizeItem>& a_itemArray) const
{  
    CItemDataGM* item = getItem(a_tpid);
    if(NULL == item){
        return false;
    }
    a_itemArray = item->getSynthesisArray();
    return true;
}


void CItemGMMgr::_removeAllItem()
{
    BSLib::Utility::CHashMap<ItemTPID, CItemDataGM*>::iterator it = m_itemHashMap.begin();
    for (; it != m_itemHashMap.end(); ++it) {
        CItemDataGM* itemData =  it->second;
        if (itemData == NULL) {
            continue;
        }
        BSLIB_SAFE_DELETE(itemData);
    }
    m_itemHashMap.clear();
}

}//GM

}//ItemSystem

}//GSLib

