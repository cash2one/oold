//////////////////////////////////////////////////////////////////////
//	created:	2014/08/03
//	filename:	GSLib\equipSystem\GM\playerGMMgr.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////

#ifndef __GSLIB_EQUIPSYSTEM_GM_EQUIPGMMGR_H__
#define __GSLIB_EQUIPSYSTEM_GM_EQUIPGMMGR_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/memory/objectMgr.h>
#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/itemSystem/GM/itemGMMgr.h>
#include <GSLib/baseDef.h>
#include <GSLib/equipSystem/GM/equipAttributeGM.h>
namespace GSLib
{

namespace EquipSystem
{

namespace GM
{

class CConditionData;
class CEquipConfigGMMgr
{
public:
	CEquipConfigGMMgr();
	virtual ~CEquipConfigGMMgr();

    BSLIB_SINGLETON_DECLARE(CEquipConfigGMMgr);
	void init();
	void final();


private:
	std::map< EQualityID, std::vector<BSLib::uint32> > m_attNumProb; // 获得属性数量概率
	std::vector<EAttrID> m_attIDProb;	// 获取指定属性项
	std::vector<float> m_attrRatie;  // 装备提升率
	std::vector<BSLib::uint32> m_attrSusRate;
public:
    BSLib::uint32 getRound(float a_value) const;
    // 装备相关
public:
    // 获取装备初始品质参数表
	BSLib::uint32 getEquipAttachAttrCount(EQualityID a_qualityID, std::vector<EAttrID>& a_attrs) const;
	BSLib::uint32 getEquipAttachAttrCount(EQualityID a_qualityID) const;

    // 获取装备初始品质参数表
    float getEquipQualityParam(EQualityID a_qualityID) const;

    // 强化：获取装备强化等级上限
    BSLib::uint32 getEquipUpgradeMaxLevelByQuality(EEquipType a_type, EQualityID a_qualityID) const;

    // 强化, 获取强化所需材料
    ItemTPID getEquipUpgradeMetarialByQuality(BSLib::uint32  a_lv) const;

	ItemTPID getEquipUpgradeMetarialByEquipLevel(BSLib::uint32  a_equipLv, BSLib::uint32 a_addLevel, BSLib::uint32 & a_num) const ;

    // 宝石：获取槽个数
    BSLib::uint32 getEquipSlotCount(EQualityID a_qualityID) const;
    BSLib::uint32 getEquipBassAttrParam(EAttrID a_attributeID) const;

    // 强化：获取强化增加的属性值
    BSLib::uint32 getEquipUpgradeLevelAddAttr(EAttrID a_attrID,BSLib::uint32 a_curAddLevel,BSLib::uint32 a_attrValue) const;

	// 强化 : 获得装备提升率
	float	getEquipUpgradeRatie(BSLib::uint32 a_lv) const;
	// 返回强化成功的等级
	BSLib::uint32 equipGrade(BSLib::uint32 a_lv);

    // 强化：获取强化增加的属性价值 用来算消耗
    float getEquipUpgradeLevelAddAttrValue(EAttrID a_attrID,BSLib::uint32 a_attrValue) const;

    // 附加属性中间值转属性参数
    float getEquipAttachAttrParam(EAttrID a_attributeID) const;

    // 熔炼： 属性价值计算
    float getEquipUpgradeQualityAttrValue(EAttrID a_attrID,BSLib::uint32 a_attrValue) const;

    // 洗练: 属性计算参数
    float getEquipAttachResetAttrParam(EAttrID a_attributeID) const;
public:
    ItemTPID getGemsTPIDByIndex(BSLib::uint32 a_itemIndex) const;
    ItemTPID getGemsTPIDByQualityID(EQualityID a_qualityID) const;
    BSLib::uint32 getIndexByGemsTPID(ItemTPID a_tpid) const;


	//** 需要的光子力
	BSLib::uint32 getGuangZiLi(EQualityID a_quality, BSLib::uint32 lv, bool a_twoAttribute);

	//** 获得的强度
	BSLib::uint32 getQiangDu(EAttrID a_attr, EQualityID a_quality, BSLib::uint32 lv, bool a_first);
	
	// **随即能量球基本属性
	BSLib::uint32 randNengLiangQiuAttr(EQualityID a_quality, SBattleAttribute& a_battleAttr, BSLib::uint32 type);

	std::vector<std::vector<BSLib::uint32> > m_nengLiangQiuGaiLv;
	std::vector<EAttrID> m_nengLiangQiuAttr;

    // 强化相关
public:
    // 获取当前强化等级对应的基础属性值
    bool getEquipBaseAttr(BSLib::uint32 a_tpid,const BSLib::uint32 a_equipLevel,EQualityID a_quality,SBattleAttribute& a_battleAttr) const;
    BSLib::uint32 getEquipUpgradeMainAttr(EAttrID a_attrID,const BSLib::uint32 a_equipLevel,EQualityID a_quality,float a_mainAttrPercent) const;
    // 获取当前强化等级对应的强化属性值
    bool getCurAddAttr(BSLib::uint32 a_addLevel,const SBattleAttribute&a_attr,SBattleAttribute& a_addAttr, EQualityID a_quality, EEquipType a_type);
    // 获取当前强化等级对应的强化属性价值
    bool getCurAddAttrValue(const SBattleAttribute&a_addAttr,SBattleAttribute& a_addAttrValue,float& a_addValue);

    // 熔炼相关
public:
    // 装备熔炼参数
    BSLib::uint32 getQualityValue(float a_proValue,BSLib::uint32 a_attrValue);
    // 装备熔炼属性价值
    float getCurQualityAddAttrValue(const SBattleAttribute& a_addAttr);

    // 强化相关
public:
    // 强化消耗计算
    bool getUpgradeEquipAddLevelCondition(BSLib::uint32 a_addLevel,SBattleAttribute a_baseAddAttr, CConditionData* a_conditionData,
		EQualityID a_quality, BSLib::uint32 a_lv, EEquipType a_type);
    // 强化消耗计算
	bool getNeedItemsByAddLevel(BSLib::uint32 a_addLevel,float a_diffValue, std::vector<ItemSystem::GM::CPrizeItem>& a_itemArray,
		EQualityID a_quality, BSLib::uint32 a_lv, BSLib::uint32& a_gold, BSLib::uint32& a_diamond, BSLib::uint32& a_guangzili, EEquipType a_type);

    // 创建装备
public:
    bool randNewEquip(BSLib::uint32 a_tpid,ItemSystem::GM::EItemType& a_itemType,EQualityID& a_quality,
		BSLib::uint32& a_level,SBattleAttribute& a_battleAttr,CAttachAttr& a_attachAttrs, BSLib::uint32& a_specfun1);
    bool randEquipAttachAttr(BSLib::uint32 a_tpid, EQualityID a_quality,BSLib::uint32 a_level,CAttachAttr& a_attachAttrs) const;
    BSLib::uint32 randEquipAttachAttrM(BSLib::uint32 a_equipLevel,float a_resetSum) const;
    bool randNewEquipAttachAttr(EQualityID a_quality,BSLib::uint32 a_equipLevel,float a_resetSum,const std::vector<BSLib::uint32>& a_lockAttrIndexArray,CAttachAttr& a_attachAttrs) const;
    // 计算基础属性用于计算属性
    BSLib::uint32 getEquipAttachAttr(EAttrID a_attrID,const BSLib::uint32 a_equipLevel, EQualityID &a_quality) const;

	BSLib::uint32 getResetRate(EQualityID a_id); // 获取洗练的概率

private:
    BSLib::uint32 _getEquipBaseAttr(EAttrID a_attrID,const BSLib::uint32 a_equipLevel,EQualityID a_quality,float a_mainAttrPercent) const;
    float _getEquipAttachAttrBaseValue(BSLib::uint32 a_level) const;
	BSLib::uint32 _getColorProb(BSLib::uint32 a_left, EQualityID a_id, BSLib::uint32 a_level) const;
	BSLib::uint32 _getAttrValueProb(EQualityID a_id) const;
    BSLib::uint32 _getEquipAttachAttrMinValue(BSLib::uint32 a_level) const;
    BSLib::uint32 _getEquipPointA(BSLib::uint32 a_level) const;
    BSLib::uint32 _getEquipAttachAttrMaxValue(BSLib::uint32 a_level) const;
    BSLib::uint32 _getEquipPointB(BSLib::uint32 a_pointA,BSLib::uint32 a_max,BSLib::uint32 a_min) const;
};

}//GM

}//EquipSystem

}//GSLib

#endif//__GSLIB_EQUIPSYSTEM_GM_EQUIPGMMGR_H__
