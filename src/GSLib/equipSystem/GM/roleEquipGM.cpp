#include <GSLib/tracer.h>
#include <GSLib/equipSystem/GM/roleEquipGM.h>
#include "equipConfigGMMgr.h"

namespace GSLib
{

namespace EquipSystem
{	

namespace GM
{

CRoleEquipGM::CRoleEquipGM(EEquipType a_equipType,BSLib::uint32 a_equipID,
                           BSLib::uint32 a_equipTPID,BSLib::uint32 a_equipLevel,BSLib::uint32 a_equipAddLevel,float a_resetSum,
                           BSLib::uint64 a_equipColorGemsCount[EQUIP_COLOR_GEMS_COUNT],
        EQualityID qualityID,
        const SBattleAttribute a_attr,
        const CAttachAttr& a_attachAttr,
        SBattleAttribute a_addAttr,
        EEquipStatus a_equipStatus)
:m_equipID(a_equipID),
m_equipTPID(a_equipTPID),
m_quality(qualityID),
m_equipLevel(a_equipLevel),
m_equipAddLevel(a_equipAddLevel),
m_equipType(a_equipType),
m_equipStatus(a_equipStatus),
m_baseBattleAttr(a_attr),
m_addBattleAttr(a_addAttr)
{
    for(BSLib::uint32 i=0;i<EQUIP_COLOR_GEMS_COUNT;++i){
        m_equipColorGemsCount[i] = a_equipColorGemsCount[i];
    }
    m_slotCount = EQUIP_GEM_MAXCOUNT;
	m_gemCount = 0;
	for(BSLib::uint32 i=0;i<m_slotCount;++i){
		m_slotGemTPID[i] = 0;
	}
    m_combat = 0;
	m_canUndo = false;
}

CRoleEquipGM::CRoleEquipGM()
:m_equipID(0)
,m_equipTPID(0)
,m_quality(QUALITY_INVALID)
,m_equipLevel(0)
,m_equipAddLevel(0)
,m_resetSum(0)
,m_slotCount(0)
,m_gemCount(0)
{
	m_canUndo = false;
}

CRoleEquipGM::CRoleEquipGM(EEquipType a_equipType,const DB::SRoleEquipData& a_equipData)
:m_equipID(a_equipData.m_equipID),
m_equipTPID(a_equipData.m_equipTPID),
m_quality((EQualityID)a_equipData.m_equipQuality),
m_equipLevel(a_equipData.m_equipLevel),
m_equipAddLevel(a_equipData.m_equipAddLevel),
m_equipType(a_equipType),
m_equipStatus((EEquipStatus)a_equipData.m_equipStatus),
m_resetSum(a_equipData.m_resetSum),
m_baseBattleAttr(a_equipData.m_equipAttr),
m_attachAttr(a_equipData.m_equipAttachAttr),
m_addBattleAttr(a_equipData.m_equipAddAttr)
{
    m_slotCount = a_equipData.m_slotCount;
    for(BSLib::uint32 i=0;i<EQUIP_COLOR_GEMS_COUNT;++i){
        m_equipColorGemsCount[i] = a_equipData.m_equipColorGemsCount[i];
    }
    m_gemCount = 0;
    for(BSLib::uint32 i=0;i<EQUIP_GEM_MAXCOUNT;++i){
        m_slotGemTPID[i] = 0;
    }
    m_combat = 0;
	m_canUndo = false;
}
CRoleEquipGM::~CRoleEquipGM()
{
}

bool CRoleEquipGM::initGems(BSLib::uint32 slotCount,const BSLib::uint32 a_slotGemTPID[4])
{
    m_slotCount = slotCount;
    for(BSLib::uint32 i=0;i<4;++i){
        if(m_slotGemTPID[i] !=0){
            EGemSlot index = (EGemSlot)i;
            setGemTPID(index,a_slotGemTPID[i]);
        }
    }
    // todo:加载宝石属性
	updateEquipBattleAttr();
	return true;
}

void CRoleEquipGM::final()
{

}

bool CRoleEquipGM::setGemTPID(EGemSlot a_posIndex,ItemTPID a_gemTPID)
{
    BSLib::uint32 curCount = (BSLib::uint32)a_posIndex + 1;
    BSLib::uint32 slotCount = getSlotCount();
    if(curCount > slotCount){
        return false;
    }
    m_slotGemTPID[a_posIndex] = a_gemTPID;
    BSLib::uint32 gemCount = 0;
    for(BSLib::uint32 i=0;i<slotCount;++i){
        if(m_slotGemTPID[i] !=0){
            gemCount ++;
        }
    }
    setGemCount(gemCount);
    return true;
}

void CRoleEquipGM::setGemCount(BSLib::uint32 a_gemCount)
{
	m_gemCount = a_gemCount;
}

BSLib::uint32 CRoleEquipGM::getGemTPID(BSLib::uint32 a_posIndex) const
{ 
	return ((a_posIndex<EQUIP_GEM_MAXCOUNT)&&(a_posIndex>=0))?m_slotGemTPID[a_posIndex]:INVALID_EQUIPGEM_DATA;
}

BSLib::uint32 CRoleEquipGM::getGemCount() const
{
	return m_gemCount;
}

bool CRoleEquipGM::serializeTo(BSLib::Utility::CStream& stream) const
{
	stream << getEquipID();
	stream << getType();
	stream << getTPID();
	stream << getLevel();
	stream << getEquipAddLevel();
	stream << getQuality();
	BSLib::uint64 now = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
	BSLib::uint64 left = m_equipColorGemsCount[0] - now;
	stream << left;
    BSLib::uint32 status = (BSLib::uint32)getEquipStatus();
    stream << status;
    m_baseBattleAttr.serializeTo(stream);
    m_attachAttr.serializeTo(stream);
    m_addBattleAttr.serializeTo(stream);
	stream << getSlotCount();
    if(!getGemsData(stream))
    {
        return false;
    }
    stream << getCombat();
    return true;
}

bool CRoleEquipGM::getDataForBag(BSLib::Utility::CStream& stream) const
{
    BSLib::uint32 level = getEquipAddLevel();
    stream << level;
    return getGemsData(stream);	
}

bool CRoleEquipGM::getNextAddLevelData(BSLib::Utility::CStream& stream)
{
    stream << getEquipID();
    stream << getType();
    stream << getTPID();
    stream << getLevel();
    BSLib::uint32 level = getEquipAddLevel() + 1;
    stream << level;
    stream << getQuality();
    BSLib::uint32 status = (BSLib::uint32)getEquipStatus();
    stream << status;
    m_baseBattleAttr.serializeTo(stream);
    m_attachAttr.serializeTo(stream);
    if(level >=101){
        m_addBattleAttr.serializeTo(stream);
    }
    else{
        SBattleAttribute addAttr;
		if(EQUIP_NENGLIANGQIU == getType())
		{
			modifyNengliangqiuBattleAddAttr(addAttr);
		}
		else
		{
			CEquipConfigGMMgr::singleton().getCurAddAttr(level,m_baseBattleAttr,addAttr, getQuality(), m_equipType);
		}
        
        addAttr.serializeTo(stream);
    }
    stream << getSlotCount();

    if(!getGemsData(stream))
    {
        return false;
    }
    stream << getCombat();
    return true;
}

bool CRoleEquipGM::getGemsData(BSLib::Utility::CStream& stream) const
{
    BSLib::uint32 GemCount = getGemCount();
    stream << GemCount;
    for(BSLib::uint32 posIndex=0;posIndex<GemCount;++posIndex){
        stream << getGemTPID(posIndex);
        stream << posIndex;
    }
    return true;
}

bool CRoleEquipGM::serializeEquipOptionResultTo(EEquipOperation operate,EQualityID qualityID,const SBattleAttribute& a_battleAttr,BSLib::Utility::CStream& stream) const
{
    stream << getEquipID();
    stream << getType();
    stream << getTPID();
    stream << getLevel();
    stream << getEquipAddLevel();

    if(operate == EQUIP_UPGRADE_QUALITY){
         stream << qualityID;
         BSLib::uint32 status = (BSLib::uint32)getEquipStatus();
         stream << status;
         a_battleAttr.serializeTo(stream);
         m_attachAttr.serializeTo(stream);
         m_addBattleAttr.serializeTo(stream);
    }
    else if(operate == EQUIP_RESET_ATTR){
        stream << getQuality();
        BSLib::uint32 status = (BSLib::uint32)getEquipStatus();
        stream << status;
        m_baseBattleAttr.serializeTo(stream);
        a_battleAttr.serializeTo(stream);
        m_addBattleAttr.serializeTo(stream);
    }
    stream << getSlotCount();
    if(!getGemsData(stream))
    {
        return false;
    }
    stream << getCombat();
    return true;
}

bool CRoleEquipGM::serializeResetAttrResultTo(EEquipOperation operate,EQualityID qualityID,const CAttachAttr& a_battleAttr,BSLib::Utility::CStream& stream) const
{
    stream << getEquipID();
    stream << getType();
    stream << getTPID();
    stream << getLevel();
    stream << getEquipAddLevel();
    stream << getQuality();
    BSLib::uint32 status = (BSLib::uint32)getEquipStatus();
    stream << status;
    m_baseBattleAttr.serializeTo(stream);
    a_battleAttr.serializeTo(stream);
    m_addBattleAttr.serializeTo(stream);
    stream << getSlotCount();
    if(!getGemsData(stream))
    {
        return false;
    }
    stream << getCombat();
    return true;
}

bool CRoleEquipGM::getEquipData(DB::SRoleEquipData& equipData) const
{
	equipData.m_equipID = getEquipID();
	equipData.m_equipTPID = getTPID();
	equipData.m_equipLevel = getLevel();

	equipData.m_equipAddLevel = getEquipAddLevel();
    equipData.m_equipQuality = getQuality();
    equipData.m_equipStatus = getEquipStatus();

    equipData.m_equipAttr = m_baseBattleAttr;
    equipData.m_equipAttachAttr = m_attachAttr;
    equipData.m_equipAddAttr = m_addBattleAttr;
    equipData.m_slotCount = getSlotCount();
    equipData.m_resetSum = m_resetSum;
    for(BSLib::uint32 i=0;i<EQUIP_COLOR_GEMS_COUNT;++i){
        equipData.m_equipColorGemsCount[i] = m_equipColorGemsCount[i]; 
    }

	for(BSLib::uint32 i=0;i<EQUIP_GEM_MAXCOUNT;++i){
		equipData.m_slotGemTPID[i] = m_slotGemTPID[i]; 
	}

	return true;
}

bool CRoleEquipGM::getEquipDetailData(CEquipData& equipData) const
{
	equipData.m_equipTPID = getTPID();
	for(BSLib::uint32 i=0;i<EQUIP_GEM_MAXCOUNT;++i){
		equipData.m_gemTPID[i] = m_slotGemTPID[i];
	}

	return true;
}

bool CRoleEquipGM::getTotalBattleAttr(SBattleAttribute& a_equipBattleAttr) const
{
    a_equipBattleAttr = m_totalBattleAttr;
    return true;
}

bool CRoleEquipGM::getAttachAttr(CAttachAttr& a_attachAttr) const
{
    a_attachAttr = m_attachAttr;
    return true;
}

BSLib::uint32 CRoleEquipGM::getBaseAttr(EAttrID a_id)
{
	switch(a_id)
	{
	case ATTR_ATK:
		return m_baseBattleAttr.m_atk;

	case ATTR_DEF:
		return m_baseBattleAttr.m_def;

	case ATTR_MAXHP:
		return m_baseBattleAttr.m_maxHP;
	}

	return 0;
}

bool CRoleEquipGM::getNengLiangQiuAttr(EAttrID& mainId, EAttrID& viceId)
{
	if(0 != m_baseBattleAttr.m_atk)
	{
		mainId = ATTR_ATK;
	}

	if( 0 != m_baseBattleAttr.m_def)
	{
		if( ATTR_INVALID == mainId)
		{
			mainId = ATTR_DEF;
		}
		else
		{
			viceId = ATTR_DEF;
		}
	}

	if( 0 != m_baseBattleAttr.m_maxHP)
	{
		if( ATTR_INVALID == mainId)
		{
			mainId = ATTR_MAXHP;
		}
		else
		{
			viceId = ATTR_MAXHP;
		}
	}

	GSLib::ItemSystem::GM::CItemDataGM* itemData = GSLib::ItemSystem::GM::CItemGMMgr::singleton().getItem(m_equipTPID);
	if(itemData == NULL){
		return false;
	}
	EAttrID itemMainId = (EAttrID)itemData->getSpecfunc1();
// 	if(getBaseAttr(mainId) != CEquipConfigGMMgr::singleton().getQiangDu(mainId, m_quality, 1, true)) // 1 强化等级
// 	{
// 		std::swap(mainId, viceId);
// 	}

	if(itemMainId != mainId)
	{
	 		std::swap(mainId, viceId);
 	}

	return true;
}

bool CRoleEquipGM::getUpgradeNengLiangQiuCond(CConditionData& a_conditionData)
{
	BSLib::uint32 oldAddLevel = getEquipAddLevel();
	EAttrID mainId = ATTR_INVALID;
	EAttrID viceId = ATTR_INVALID;
	
	getNengLiangQiuAttr(mainId, viceId);
	a_conditionData.m_guangzili = CEquipConfigGMMgr::singleton().getGuangZiLi(m_quality, m_equipAddLevel + 1, viceId != ATTR_INVALID);
	return true;
}

bool CRoleEquipGM::getUpgradeCondition(CConditionData& a_conditionData) const
{
    BSLib::uint32 oldAddLevel = getEquipAddLevel();
    return CEquipConfigGMMgr::singleton().getUpgradeEquipAddLevelCondition(oldAddLevel,m_baseBattleAttr, &a_conditionData, m_quality, m_equipLevel, m_equipType);
}

bool CRoleEquipGM::isStatusOn() const
{
    return (getEquipStatus() == EQUIP_STATUS_ON);
}


bool CRoleEquipGM::getDisassemblyEquipResult(std::vector<ItemSystem::GM::CPrizeItem>& a_itemArray)
{	
	EQualityID qid = getQuality();

	if( EQUIP_NENGLIANGQIU == getType())
	{	
// 		EAttrID mainid = ATTR_INVALID;
// 		EAttrID viceid = ATTR_INVALID;
// 		getNengLiangQiuAttr(mainid, viceid);
// 		BSLib::uint32 guangzili = CEquipConfigGMMgr::singleton().getGuangZiLi(m_quality, getEquipAddLevel(), viceid != ATTR_INVALID);
// 		double sum = guangzili * getEquipAddLevel();
// 		sum /= 2.5;

		BSLib::uint32 base[MAX_QUALITY_INDEX] = {0, 20, 180, 450, 850, 1900, 5000};
		BSLib::uint32 delta[MAX_QUALITY_INDEX] = {0, 50, 100, 140, 180, 220, 300};
		BSLib::uint32 sum =  base[qid] + getEquipAddLevel() * delta[qid];

		
		ItemSystem::GM::CPrizeItem item;
		item.m_itemTPID = 107;
		item.m_itemType = ItemSystem::GM::EITEM_TP_EQUIP_NENGLIANGQIU;
		item.m_itemCount = sum;
		a_itemArray.push_back(item);
		return true;
	}	
	
	BSLib::uint32 levelNum = 0;
	BSLib::uint32 upgradeNumLow = 0;
	BSLib::uint32 upgradeNumMid = 0;
	BSLib::uint32 upgradeNumHigh = 0;
	BSLib::uint32 colorBase[MAX_QUALITY_INDEX] = {0, 60, 30, 60, 30, 60, 20};

	BSLib::uint32 num = 1 + getLevel() / colorBase[qid];
	if(QUALITY_WHITE <= qid && QUALITY_GREEN >= qid)
	{
		upgradeNumLow = num;
	}
	else if( QUALITY_GREEN  <= qid && QUALITY_PURPLE >= qid)
	{
		upgradeNumMid = num;
	}
	else 
	{
		upgradeNumHigh = num;
	}

// 	switch(m_equipAddLevel)
// 	{
// 	case 0:
// 		levelNum = 1;
// 		upgradeNumLow = 1;
// 		upgradeNumMid = 0;
// 		upgradeNumHigh = 0;
// 		break;
// 	case 1:
// 		levelNum = 2;
// 		upgradeNumLow = 2;
// 		upgradeNumMid = 0;
// 		upgradeNumHigh = 0;
// 		break;
// 	case 2:
// 		levelNum = 3;
// 		upgradeNumLow = 3;
// 		upgradeNumMid = 0;
// 		upgradeNumHigh = 0;
// 		break;
// 	case 3:
// 		levelNum = 4;
// 		upgradeNumLow = 4;
// 		upgradeNumMid = 0;
// 		upgradeNumHigh = 0;
// 		break;
// 	case 4:
// 		levelNum = 5;
// 		upgradeNumLow = 5;
// 		upgradeNumMid = 0;
// 		upgradeNumHigh = 0;
// 		break;
// 	case 5:
// 		levelNum = 6;
// 		upgradeNumLow = 6;
// 		upgradeNumMid = 0;
// 		upgradeNumHigh = 0;
// 		break;
// 	case 6:
// 		levelNum = 7;
// 		upgradeNumLow = 7;
// 		upgradeNumMid = 0;
// 		upgradeNumHigh = 0;
// 		break;
// 	case 7:
// 		levelNum = 8;
// 		upgradeNumLow = 7;
// 		upgradeNumMid = 1;
// 		upgradeNumHigh = 0;
// 		break;
// 	case 8:
// 		levelNum = 9;
// 		upgradeNumLow = 8;
// 		upgradeNumMid = 2;
// 		upgradeNumHigh = 0;
// 		break;
// 	case 9:
// 		levelNum = 10;
// 		upgradeNumLow = 7;
// 		upgradeNumMid = 2;
// 		upgradeNumHigh = 0;
// 		break;
// 	case 10:
// 		levelNum = 11;
// 		upgradeNumLow = 8;
// 		upgradeNumMid = 3;
// 		upgradeNumHigh = 0;
// 		break;
// 	case 11:
// 		levelNum = 12;
// 		upgradeNumLow = 9;
// 		upgradeNumMid = 4;
// 		upgradeNumHigh = 1;
// 		break;
// 	case 12:
// 		levelNum = 13;
// 		upgradeNumLow = 10;
// 		upgradeNumMid = 5;
// 		upgradeNumHigh = 2;
// 		break;
// 	case 13:
// 		levelNum = 14;
// 		upgradeNumLow = 11;
// 		upgradeNumMid = 6;
// 		upgradeNumHigh = 3;
// 		break;
// 	}

	if( 0 != upgradeNumLow){	
		ItemSystem::GM::CPrizeItem item;
		item.m_itemTPID = EQUIP_UPGRADE_GEM_LOW;
		item.m_itemType = ItemSystem::GM::EITEM_TP_EQUIP_UPGRADE_MATERIAL;
		item.m_itemCount = upgradeNumLow;
		a_itemArray.push_back(item);
	}

	if( 0 != upgradeNumMid){
		ItemSystem::GM::CPrizeItem item;
		item.m_itemTPID = EQUIP_UPGRADE_GEM_MID;
		item.m_itemType = ItemSystem::GM::EITEM_TP_EQUIP_UPGRADE_MATERIAL;
		item.m_itemCount = upgradeNumMid;
		a_itemArray.push_back(item);
	}

	if( 0 != upgradeNumHigh){
		ItemSystem::GM::CPrizeItem item;
		item.m_itemTPID = EQUIP_UPGRADE_GEM_HIGH;
		item.m_itemType = ItemSystem::GM::EITEM_TP_EQUIP_UPGRADE_MATERIAL;
		item.m_itemCount = upgradeNumHigh;
		a_itemArray.push_back(item);
	}

	if(0 != levelNum){	
		ItemSystem::GM::CPrizeItem item;
		BSLib::uint32 num = 0;
		item.m_itemTPID = CEquipConfigGMMgr::singleton().getEquipUpgradeMetarialByEquipLevel(m_equipLevel, m_equipAddLevel, num);
		item.m_itemType = ItemSystem::GM::EITEM_TP_EQUIP_QUALITY_MATERIAL;
		item.m_itemCount = levelNum;
		a_itemArray.push_back(item);
	}

	return true;


	////////////////////////////////////////////////////////

    // 强化宝石部分材料
    for(int i=0;i<EQUIP_COLOR_GEMS_COUNT;++i){
        ItemSystem::GM::CPrizeItem item;
        if(!_getUseGemsItem(i,item)){
            continue;
        }
        a_itemArray.push_back(item);
    }
    //根据对应装备的品质，返还额外的强化石
    EQualityID qualityID = getQuality();
    
    ItemSystem::GM::CPrizeItem itemEx;
    itemEx.m_itemCount = 1;
    itemEx.m_itemType = ItemSystem::GM::EITEM_TP_EQUIP_UPGRADE_MATERIAL;
    itemEx.m_itemTPID = CEquipConfigGMMgr::singleton().getGemsTPIDByQualityID(qualityID);
    a_itemArray.push_back(itemEx);
    // 镶嵌宝石拆解
    for(int i=0;i<EQUIP_GEM_MAXCOUNT;++i){
        ItemTPID gemTPID = m_slotGemTPID[i];
        if(gemTPID == 0){
            continue;
        }
        ItemSystem::GM::CPrizeItem item;
        item.m_itemCount = 1;
        item.m_itemType = ItemSystem::GM::EITEM_TP_GEMS;
        item.m_itemTPID = gemTPID;
        a_itemArray.push_back(item);
    }
    
    return true;
}

bool CRoleEquipGM::modifyBattleAddAttr()
{
    BSLib::uint32 curAddLevel = getEquipAddLevel();
	bool bSuccess = false;
	if(EQUIP_NENGLIANGQIU == getType())
	{
		SBattleAttribute addAttr;
		bSuccess = modifyNengliangqiuBattleAddAttr(addAttr);
	}
	else
	{
		bSuccess = CEquipConfigGMMgr::singleton().getCurAddAttr(curAddLevel,m_baseBattleAttr,m_addBattleAttr, m_quality, m_equipType);
	}
    
    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "更新装备强化属性[m_addBattleAttr=%s]",m_addBattleAttr.toLogString().c_str());
    return bSuccess;
}

bool CRoleEquipGM::modifyNengliangqiuBattleAddAttr(SBattleAttribute& a_addAttr)
{
	EAttrID mainid = ATTR_INVALID;
	EAttrID viceid = ATTR_INVALID;
	getNengLiangQiuAttr(mainid, viceid);
	BSLib::uint32 curAddLevel = getEquipAddLevel();
	
	
	for(BSLib::uint32 i=0; i<MAX_ATTR_INDEX; ++i){
		EAttrID curid = (EAttrID)i;

		if( curid == mainid)
		{
			BSLib::uint32 oldAllValue = m_addBattleAttr.getValue(curid) + getBaseAttr(curid);
			BSLib::uint32 newAllValue = CEquipConfigGMMgr::singleton().getQiangDu(curid, m_quality, curAddLevel, true);
			if(oldAllValue != newAllValue)
			{
				m_addBattleAttr.setValue(curid, m_addBattleAttr.getValue(curid) + (newAllValue - oldAllValue));
			}
		}
		else if( curid == viceid)
		{
			BSLib::uint32 oldAllValue = m_addBattleAttr.getValue(curid) + getBaseAttr(curid);
			BSLib::uint32 newAllValue = CEquipConfigGMMgr::singleton().getQiangDu(curid, m_quality, curAddLevel, false);
			if(oldAllValue != newAllValue)
			{
				m_addBattleAttr.setValue(curid, m_addBattleAttr.getValue(curid) + (newAllValue - oldAllValue));
			}
		}
		else
		{
			m_addBattleAttr.setValue(curid,0);
		}

	}
	
	a_addAttr = m_addBattleAttr;
	return true;
}

const SBattleAttribute& CRoleEquipGM::getBattleAttr() const
{
    return m_baseBattleAttr;
}

bool CRoleEquipGM::updateEquipBattleAttr()
{
    // 更新宝石相关属性
    if(!_updateFixAttr()){
        return false;
    }
    return updateTotalAttr();
}

void CRoleEquipGM::addUseGemsCount(const std::vector<ItemSystem::GM::CPrizeItem>& a_itemArray)
{
    std::vector<ItemSystem::GM::CPrizeItem>::const_iterator it = a_itemArray.begin();
    for(;it != a_itemArray.end(); ++it){
        const ItemSystem::GM::CPrizeItem item = *it;
        _addUseGems(item.m_itemTPID);
    }
}

void CRoleEquipGM::serializeDisassemblyEquipResultTo(BSLib::Utility::CStream& stream)
{
    std::vector<ItemSystem::GM::CPrizeItem> itemArray;
    getDisassemblyEquipResult(itemArray);
    std::vector<ItemSystem::GM::CPrizeItem>::const_iterator it = itemArray.begin();
    BSLib::uint32 count = itemArray.size();
    stream << count;
    for(;it != itemArray.end(); ++it){
       const ItemSystem::GM::CPrizeItem item = *it;
       item.serializeTo(stream); 
    }
}

void CRoleEquipGM::_addUseGems(ItemTPID a_tpid)
{
    BSLib::uint32 index = CEquipConfigGMMgr::singleton().getIndexByGemsTPID(a_tpid);
    if(index >= EQUIP_COLOR_GEMS_COUNT){
        return;
    }

    m_equipColorGemsCount[index]++;
}

bool CRoleEquipGM::_getUseGemsItem(BSLib::uint32 a_itemIndex,ItemSystem::GM::CPrizeItem& a_item) const
{
    if(m_equipColorGemsCount[a_itemIndex] <=0 ){
        return false;
    }
    if(a_itemIndex >= EQUIP_COLOR_GEMS_COUNT){
        return false;
    }

    a_item.m_itemTPID = CEquipConfigGMMgr::singleton().getGemsTPIDByIndex(a_itemIndex);
    a_item.m_itemType = ItemSystem::GM::EITEM_TP_EQUIP_UPGRADE_MATERIAL;
    // B=INT(A*0.3)+1
    BSLib::uint32 A =  m_equipColorGemsCount[a_itemIndex];
    a_item.m_itemCount = (A*3)/10 + 1;
    return true;
}

bool CRoleEquipGM::updateTotalAttr()
{
    m_totalBattleAttr.cleanAttr();
    m_totalBattleAttr.addAttr(m_baseBattleAttr);
    m_totalBattleAttr.addAttr(m_addBattleAttr);

    SBattleAttribute attr;
    m_attachAttr.getBattleAttr(attr);
    m_totalBattleAttr.addAttr(attr);
    m_totalBattleAttr.addAttr(m_fixBattleAttr);

    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "更新总的装备属性[EquipTPID=%d][EquipLevel=%d]总影响[fixAttribute=%s]",getTPID(),getLevel(),m_totalBattleAttr.toLogString().c_str());
    _updateCombat();
    return true;
}

bool CRoleEquipGM::_updateFixAttr()
{
    m_fixBattleAttr.cleanAttr();
    for(BSLib::uint32 i = GEM_SLOT_FIRST; i <GEM_SLOT_MAX; ++i){
        BSLib::uint32 gemTPID = getGemTPID(i); 
        if(gemTPID != 0){
            SBattleAttribute battleAttr;
            battleAttr.cleanAttr();
            if(!ItemSystem::GM::CItemGMMgr::singleton().getGemAttr(gemTPID,battleAttr)){
                BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "无效的宝石ID[gemTPID=%d]",gemTPID);
            }
            m_fixBattleAttr.addAttr(battleAttr);
        }
    }
    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "宝石对装备[EquipTPID=%d][EquipLevel=%d]总影响[fixAttribute=%s]",getTPID(),getLevel(),m_fixBattleAttr.toLogString().c_str());
    return true;
}

void CRoleEquipGM::_updateCombat()
{
    // 战斗力公式 i.	战斗力=攻击力*2 + 防御力 + 生命值/5 + 命中/5 + 闪避/2 + 暴击/2 + 抗暴/5 
    float combat = (float)(m_totalBattleAttr.m_atk * 2 
        + m_totalBattleAttr.m_def 
        + (m_totalBattleAttr.m_atkCrift / 2) 
        + (m_totalBattleAttr.m_defCrift / 5) 
        + (m_totalBattleAttr.m_hitRate / 5)
        + (m_totalBattleAttr.m_missRate / 2)
        + (m_totalBattleAttr.m_maxHP / 5 ) );
    m_combat = (BSLib::uint32)combat;
}

}//GM

}//EquipSystem

}//GSLib

