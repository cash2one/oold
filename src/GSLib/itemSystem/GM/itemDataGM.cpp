#include <GSLib/tracer.h>
#include <GSLib/itemSystem/msgItemSystem.h>
#include <GSLib/dbSystem/GM/dbSystemGM.h>
#include <GSLib/itemSystem/GM/itemDataGM.h>

namespace GSLib
{

namespace ItemSystem
{	

namespace GM
{

CItemDataGM::CItemDataGM()
:m_announce(false)
{
}

	
CItemDataGM::~CItemDataGM()
{
}

bool CItemDataGM::loadData(BSLib::Utility::CTableRow& a_tableRow)
{
	a_tableRow["f_name"] >> m_name;
    a_tableRow["f_id"] >> m_itemTPID;
    BSLib::uint32 itemType = 0;
    a_tableRow["f_type"] >> itemType;
    m_itemType = (GSLib::ItemSystem::GM::EItemType)itemType;
    a_tableRow["f_specfunc1"] >> m_specfunc1;
    a_tableRow["f_specfunc2"] >> m_specfunc2;
    a_tableRow["f_specfunc3"] >> m_specfunc3;
    a_tableRow["f_specfunc4"] >> m_specfunc4;
    
    a_tableRow["f_level"] >> m_level;
    a_tableRow["f_value"] >> m_value;

    a_tableRow["f_atk"] >> m_atk;
    a_tableRow["f_def"] >> m_def;
    a_tableRow["f_hp"] >> m_hp;
    a_tableRow["f_hit_rate"] >> m_hitRate;
    a_tableRow["f_miss_rate"] >> m_missRate;
    a_tableRow["f_atk_crift"] >> m_atkCrift;
    a_tableRow["f_def_crift"] >> m_defCrift;
    
    a_tableRow["f_pro_limit"] >> m_proLimit;
    BSLib::uint32 quality = 0;
    a_tableRow["f_quality"] >> quality;
    m_quality = (EQualityID)quality;
    a_tableRow["f_use_level"] >> m_useLevel;
    a_tableRow["f_time_limit"] >> m_timeLimit;
    a_tableRow["f_limit_count"] >> m_countLimit;

    BSLib::uint32 isSell = 0;
    a_tableRow["f_issell"] >> isSell;
    m_isSell = (isSell == 0)? false:true;

    BSLib::uint32 isUse = 0;
    a_tableRow["f_isuse"] >> isUse;
    m_isUse = (isUse == 0)? false:true;

    a_tableRow["f_price"] >> m_price;
    a_tableRow["f_synthesis"] >> m_synthesis;
	BSLib::uint32 announce;
	a_tableRow["f_announce"] >> announce;
	m_announce = (announce == 1);

    if(EMAIN_TP_PET == getMainType()){
        BSLib::Utility::CStringA strItems(m_synthesis);
        std::vector<std::string> vecStr;
        std::string separator(";");
        strItems.split(vecStr, separator);
        for(BSLib::uint32 i=0;i<vecStr.size();++i){
            const std::string str = vecStr[i];
            const std::string subSeparator(",");
            CPrizeItem item;
            item.init(str,subSeparator);
            m_synthesisArray.push_back(item);
        }
        if(!_initPetAttr()){
            return false;
        }
        if(!_initPetLovelyItems()){
            return false;
        }
    }
    
    return true;
}

std::string CItemDataGM::getName() const
{
	return m_name;
}

const std::vector<ItemTPID>& CItemDataGM::getPetLovelyItems() const
{
    return m_petLovelyItemArray;
}

const std::vector<CPrizeItem>& CItemDataGM::getSynthesisArray() const
{
    return m_synthesisArray;
}

bool CItemDataGM::isItemData(ItemTPID a_itemTPID,GSLib::ItemSystem::GM::EItemType a_itemType) const
{
	if(m_itemTPID != a_itemTPID){
		return false;
	}
	else if(m_itemType != a_itemType){
		return false;
	}

	return true;
}

bool CItemDataGM::isValid(ItemTPID a_itemTPID) const
{
	if(m_itemTPID != a_itemTPID){
		return false;
	}
	return true;
}

bool CItemDataGM::isSell() const
{
	return m_isSell;
}

bool CItemDataGM::isUse() const
{
	return m_isUse;
}

BSLib::uint32 CItemDataGM::getStackCount() const
{
   return m_countLimit; 
}

BSLib::uint32 CItemDataGM::getLevel() const
{
    return m_level; 
}

BSLib::uint32 CItemDataGM::getPrice() const
{
    return m_price;
}

EItemType CItemDataGM::getType() const
{
	return (EItemType)m_itemType;
}

EMainType CItemDataGM::getMainType() const
{
    EItemType type = getType();
    if((type <= EITEM_TP_PRO_END) && (type >= EITEM_TP_MATERIAL_BEGIN)){
        return EMAIN_TP_ITEM;
    }
    else if((type >= EITEM_TP_EQUIP_BEGIN) && (type <= EITEM_TP_EQUIP_END)){
        return EMAIN_TP_EQUIP;
    }
    else if(type == EITEM_TP_VIR_PET){
        return EMAIN_TP_PET;
    }
    else if((type < EITEM_TP_MAX) && (type > EITEM_TP_VIR_PET)){
        return EMAIN_TP_RESOURCE;
    }

    return EMAIN_TP_IVALID;
}

BSLib::uint32 CItemDataGM::getProLimit() const
{  
    return m_proLimit;
}

ItemTPID CItemDataGM::getTPID() const
{
	return m_itemTPID; 
}
EQualityID CItemDataGM::getQualityID() const
{
    return m_quality; 
}

void CItemDataGM::getGemAttr(SBattleAttribute& a_battleAttr) const
{
    for(BSLib::uint32 i=0;i<MAX_ATTR_INDEX;++i){
         float f_value = getAttrValue((EAttrID)i);
         BSLib::uint32 d_value = (BSLib::uint32)f_value;
         a_battleAttr.setValue((EAttrID)i,d_value);
    }
}

BSLib::uint32 CItemDataGM::getPetAttrCount(std::vector<EAttrID>& a_attrIDs) const
{
    BSLib::uint32 count = 0;
    for(BSLib::uint32 i=0;i<MAX_ATTR_INDEX;++i){
        float f_value = getAttrValue((EAttrID)i);
        BSLib::uint32 d_value = (BSLib::uint32)f_value;
        if(d_value != 0){
            EAttrID id = (EAttrID)i;
            a_attrIDs.push_back(id);
            count++;
        }
    }
    return count;
}

bool CItemDataGM::getPetBaseAttrs(SBattleAttribute& a_petBaseAttrs) const
{
    a_petBaseAttrs = m_petBaseAttr;
    return true;
}

bool CItemDataGM::getPetUpgradeAttrs(SBattleAttribute& a_petUpgradeAttrs) const
{
    a_petUpgradeAttrs = m_petUpgradeAttr;
    return true;
}

float CItemDataGM::getAtk() const
{
   return m_atk;
}

float CItemDataGM::getDef() const
{
   return m_def;
}

float CItemDataGM::getHP() const
{
   return m_hp;
}

float CItemDataGM::getHitRate()const
{
   return m_hitRate;
}

float CItemDataGM::getMissRate() const
{
   return m_missRate;
}

float CItemDataGM::getAtkCrift() const
{
   return m_atkCrift;
}

float CItemDataGM::getDefCrift() const
{
   return m_defCrift;
}

float CItemDataGM::getItemValue() const
{
    return m_value;
}

BSLib::uint32 CItemDataGM::getSpecfunc1() const
{
    return m_specfunc1;
}

BSLib::uint32 CItemDataGM::getSpecfunc2() const
{
    return m_specfunc2;
}


std::string CItemDataGM::getSpecfunc3() const
{
    return m_specfunc3;
}

std::string CItemDataGM::getSpecfunc4() const
{
    return m_specfunc4;
}

float CItemDataGM::getAttrValue(EAttrID a_attrID) const
{
    switch (a_attrID)
    {
    case ATTR_ATK: { return m_atk; } break;
    case ATTR_DEF: { return m_def; } break;

    case ATTR_ATK_CRIFT: { return m_atkCrift; } break;
    case ATTR_DEF_CRIFT: { return m_defCrift; } break;

    case ATTR_HIT_RATE: { return m_hitRate; } break;
    case ATTR_MISS_RATE: { return m_missRate; } break;
    case ATTR_MAXHP: { return m_hp; } break;
    default: { return 0; } break;
    }
}

std::string CItemDataGM::getSynthesis() const
{
    return m_synthesis;
}

bool CItemDataGM::enableAnnounce() const
{
	return m_announce;
}

BSLib::uint32 CItemDataGM::getTimeLimit() const
{
	return m_timeLimit;
}

bool CItemDataGM::_initPetAttr()
{
    BSLib::Utility::CStringA strAttr(m_specfunc4);
    std::vector<std::string> petVecStr;
    std::string petSeparator(";");
    strAttr.split(petVecStr, petSeparator);
    std::vector<EAttrID> attrIDs;
    BSLib::uint32 attrCount = getPetAttrCount(attrIDs);
    if((petVecStr.size() != attrCount) || (attrCount != attrIDs.size())){
        return false;
    }
    m_petBaseAttr.cleanAttr();
    m_petUpgradeAttr.cleanAttr();

    for(BSLib::uint32 i=0;i<attrCount;++i){
        const std::string strAttrValue = petVecStr[i];
        const std::string subPetSeparator(",");
        BSLib::Utility::CStringA strItem(strAttrValue);
        std::vector<std::string> vecPet;
        strItem.split(vecPet, subPetSeparator);
        if(vecPet.size() != 2){
            return false;
        }
        BSLib::uint32 baseValue = (BSLib::uint32)atoi(vecPet[0].c_str());
        BSLib::uint32 upgradeValue = (BSLib::uint32)atoi(vecPet[1].c_str());
        EAttrID id = attrIDs[i];
        m_petBaseAttr.setValue(id,baseValue);
        m_petUpgradeAttr.setValue(id,upgradeValue);
    }
    return true;
}

bool CItemDataGM::_initPetLovelyItems()
{
    m_petLovelyItemArray.clear();
    BSLib::Utility::CStringA strItems(m_specfunc3);
    std::vector<std::string> vecStr;
    std::string separator("|");
    strItems.split(vecStr, separator);
    for(BSLib::uint32 i=0;i<vecStr.size();++i){
        const std::string str = vecStr[i];
        BSLib::uint32 itemTPID = (BSLib::uint32)atoi(str.c_str());
        m_petLovelyItemArray.push_back(itemTPID);
    }
    return true;
}

}//GM

}//ItemSystem

}//GSLib

