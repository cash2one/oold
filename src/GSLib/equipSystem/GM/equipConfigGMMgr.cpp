
#include <GSLib/equipSystem/msgEquipSystemGC.h>
#include <GSLib/equipSystem/msgEquipSystem.h>
#include <GSLib/tracer.h>
#include <BSLib/utility/file/dirInfo.h>
#include <BSLib/utility/table.h>
#include <BSLib/utility/random.h>
#include "equipConfigGMMgr.h"
#include <GSLib/itemSystem/GM/itemGMMgr.h>
#include <GSLib/equipSystem/baseDef.h>
#include <math.h>
#include <algorithm>
#include <GSLib/equipSystem/GM/roleEquipGM.h>

namespace GSLib
{

namespace EquipSystem
{	

namespace GM
{

using namespace ItemSystem::GM;
BSLIB_SINGLETON_DEFINE(CEquipConfigGMMgr);

CEquipConfigGMMgr::CEquipConfigGMMgr()
{
	init();
}

CEquipConfigGMMgr::~CEquipConfigGMMgr()
{
}

void CEquipConfigGMMgr::init()
{
	std::vector<BSLib::uint32> buf;
	buf.insert(buf.begin(), 100, 6);
	std::random_shuffle(buf.begin(), buf.end());
	m_attNumProb[QUALITY_RED] = buf;

	buf.clear();
	buf.insert(buf.begin(), 100, 5);
	std::random_shuffle(buf.begin(), buf.end());
	m_attNumProb[QUALITY_ORANGE] = buf;

	buf.clear();
	buf.insert(buf.begin(), 100, 4);
	std::random_shuffle(buf.begin(), buf.end());
	m_attNumProb[QUALITY_PURPLE] = buf;

	buf.clear();
	buf.insert(buf.begin(), 100, 3);
	std::random_shuffle(buf.begin(), buf.end());
	m_attNumProb[QUALITY_BLUE] = buf;

	buf.clear();
	buf.insert(buf.begin(), 100, 0);
	std::random_shuffle(buf.begin(), buf.end());
	m_attNumProb[QUALITY_GREEN] = buf;

	buf.clear();
	buf.insert(buf.begin(), 100, 0);
	std::random_shuffle(buf.begin(), buf.end());
	m_attNumProb[QUALITY_WHITE] = buf;


	m_attIDProb.insert(m_attIDProb.begin(), 11, ATTR_ATK);
	m_attIDProb.insert(m_attIDProb.begin(), 17, ATTR_DEF);
	m_attIDProb.insert(m_attIDProb.begin(), 13, ATTR_MAXHP);
	m_attIDProb.insert(m_attIDProb.begin(), 14, ATTR_HIT_RATE);
	m_attIDProb.insert(m_attIDProb.begin(), 17, ATTR_MISS_RATE);
	m_attIDProb.insert(m_attIDProb.begin(), 17, ATTR_ATK_CRIFT);
	m_attIDProb.insert(m_attIDProb.begin(), 11, ATTR_DEF_CRIFT);
	std::random_shuffle(m_attIDProb.begin(), m_attIDProb.end());


	m_attrRatie.push_back(0.0f);
	m_attrRatie.push_back(0.05f);
	m_attrRatie.push_back(0.10f);
	m_attrRatie.push_back(0.15f);
	m_attrRatie.push_back(0.20f);
	m_attrRatie.push_back(0.30f);
	m_attrRatie.push_back(0.40f);
	m_attrRatie.push_back(0.60f);
	m_attrRatie.push_back(0.80f);
	m_attrRatie.push_back(1.0f);
	m_attrRatie.push_back(1.2f);
	m_attrRatie.push_back(1.5f);
	m_attrRatie.push_back(1.8f);
	m_attrRatie.push_back(2.2f);

	m_attrSusRate.push_back(0);
	m_attrSusRate.push_back(100);
	m_attrSusRate.push_back(85);
	m_attrSusRate.push_back(65);
	m_attrSusRate.push_back(45);
	m_attrSusRate.push_back(30);
	m_attrSusRate.push_back(40);
	m_attrSusRate.push_back(30);
	m_attrSusRate.push_back(20);
	m_attrSusRate.push_back(10);
	m_attrSusRate.push_back(10);
	m_attrSusRate.push_back(30);
	m_attrSusRate.push_back(20);
	m_attrSusRate.push_back(20);
	m_attrSusRate.push_back(10);
	m_attrSusRate.push_back(10);



	std::vector<BSLib::uint32> gailv; 
	m_nengLiangQiuGaiLv.push_back(gailv);	// invalid

	gailv.insert(gailv.begin(), 100, 1);
	m_nengLiangQiuGaiLv.push_back(gailv);	// white

	gailv.clear();
	gailv.insert(gailv.begin(), 80, 1);
	gailv.insert(gailv.begin(), 20, 2);	
	std::random_shuffle(gailv.begin(), gailv.end());
	m_nengLiangQiuGaiLv.push_back(gailv);	// green

	gailv.clear();
	gailv.insert(gailv.begin(), 60, 1);
	gailv.insert(gailv.begin(), 40, 2);
	std::random_shuffle(gailv.begin(), gailv.end());
	m_nengLiangQiuGaiLv.push_back(gailv);	// blue


	gailv.clear();
	gailv.insert(gailv.begin(), 20, 1);
	gailv.insert(gailv.begin(), 80, 2);
	std::random_shuffle(gailv.begin(), gailv.end());
	m_nengLiangQiuGaiLv.push_back(gailv);	// pupple


	gailv.clear();
	gailv.insert(gailv.begin(), 100, 2);
	m_nengLiangQiuGaiLv.push_back(gailv);	// orange

	gailv.clear();
	gailv.insert(gailv.begin(), 100, 2);
	m_nengLiangQiuGaiLv.push_back(gailv);	// red

	
	m_nengLiangQiuAttr.insert(m_nengLiangQiuAttr.begin(), 4, ATTR_ATK);
	m_nengLiangQiuAttr.insert(m_nengLiangQiuAttr.begin(), 5, ATTR_DEF);
	m_nengLiangQiuAttr.insert(m_nengLiangQiuAttr.begin(), 6, ATTR_MAXHP);
	std::random_shuffle(m_nengLiangQiuAttr.begin(), m_nengLiangQiuAttr.end());

}

void CEquipConfigGMMgr::final()
{
}


BSLib::uint32 CEquipConfigGMMgr::getRound(float a_value) const
{
    float f_value = a_value;
    BSLib::uint32 val = (BSLib::uint32)f_value;
    BSLib::uint32 temp = (BSLib::uint32)(f_value*10);
    BSLib::uint32 num = temp%10;
    if(num >= 5){
        val +=1;
    }
    return val;
}
// 获取装备初始品质参数表
BSLib::uint32 CEquipConfigGMMgr::getEquipAttachAttrCount(EQualityID a_qualityID, std::vector<EAttrID>& a_attrs) const
{	
	std::map< EQualityID, std::vector<BSLib::uint32> >::const_iterator it = m_attNumProb.find(a_qualityID);
	if( it == m_attNumProb.end())
		return 0;

	const std::vector<BSLib::uint32>& a = it->second;
	BSLib::uint32 randNum = BSLib::Utility::CRandom::randomBetween(0, 99);
	BSLib::uint32 attrNum = a[randNum];
	a_attrs.clear();
	std::set<EAttrID> attrSet;
	for(BSLib::uint32 i = attrSet.size(); i < attrNum; i = attrSet.size())
	{
		randNum = BSLib::Utility::CRandom::randomBetween(0, 99);
		attrSet.insert(m_attIDProb[randNum]);
	}

	std::copy(attrSet.begin(), attrSet.end(), std::back_inserter(a_attrs));

	return attrNum;
}

BSLib::uint32 CEquipConfigGMMgr::getEquipAttachAttrCount(EQualityID a_qualityID) const
{
	switch (a_qualityID)
	{
	case QUALITY_WHITE:    { return 1; } break;
	case QUALITY_GREEN:    { return 1;} break;
	case QUALITY_BLUE:     { return 2; } break;
	case QUALITY_PURPLE:   { return 2; } break;
	case QUALITY_ORANGE:   { return 3; } break;
		//case QUALITY_RED:      { return 3; } break;
	default:               { return 0; } break;
	}
}


// 获取装备初始品质参数表
float CEquipConfigGMMgr::getEquipQualityParam(EQualityID a_qualityID) const
{
    switch (a_qualityID)
    {
    case QUALITY_WHITE:    { return 0.3f; } break;
    case QUALITY_GREEN:    { return 0.35f;} break;
    case QUALITY_BLUE:     { return 0.5f; } break;
    case QUALITY_PURPLE:   { return 0.7f; } break;
    case QUALITY_ORANGE:   { return 0.9f; } break;
        //case QUALITY_RED:      { return 1.0f; } break;
    default:               { return 0.0f; } break;
    }
}

// 获取装备强化等级上限
BSLib::uint32 CEquipConfigGMMgr::getEquipUpgradeMaxLevelByQuality(EEquipType a_type, EQualityID a_qualityID) const
{	
	if(EQUIP_NENGLIANGQIU == a_type)
		return 50;

    switch (a_qualityID)
    {
    case QUALITY_WHITE:    { return EQUIP_ADD_MAX_LEVEL; } break;
    case QUALITY_GREEN:    { return EQUIP_ADD_MAX_LEVEL;} break;
    case QUALITY_BLUE:     { return EQUIP_ADD_MAX_LEVEL; } break;
    case QUALITY_PURPLE:   { return EQUIP_ADD_MAX_LEVEL; } break;
    case QUALITY_ORANGE:   { return EQUIP_ADD_MAX_LEVEL; } break;
        //case QUALITY_RED:      { return 100; } break;
    default:               { return EQUIP_ADD_MAX_LEVEL; } break;
    }
}

// 获取装备强化等级上限
ItemTPID CEquipConfigGMMgr::getEquipUpgradeMetarialByQuality(BSLib::uint32 a_addLevel) const
{		

		if(1 <= a_addLevel && a_addLevel <= 5)
		{	
			return EQUIP_UPGRADE_GEM_LOW;
		}
		else if( 6 <= a_addLevel && a_addLevel <= 10)
		{	
			return EQUIP_UPGRADE_GEM_MID;
		}
		else
		{	
			return EQUIP_UPGRADE_GEM_HIGH;
		}

//     switch (a_qualityID)
//     {
//     case QUALITY_WHITE:    { return 2321; } break;
//     case QUALITY_GREEN:    { return 2322; } break;
//     case QUALITY_BLUE:     { return 2323; } break;
//     case QUALITY_PURPLE:   { return 2324; } break;
//     case QUALITY_ORANGE:   { return 2325; } break;
//         // case QUALITY_RED:      { return 2326; } break;
//     default:               { return 0; } break;
//     }
}

// todo  更改返回item id
ItemTPID CEquipConfigGMMgr::getEquipUpgradeMetarialByEquipLevel(BSLib::uint32  a_equipLv, BSLib::uint32 a_addLevel, BSLib::uint32 & a_num) const
{	
	if(1 <= a_addLevel && a_addLevel <= 6)
		a_num = 1;
	else if( 7 <= a_addLevel && a_addLevel <= 10)
		a_num = 2;
	else 
		a_num = 3;


	if(1 <= a_equipLv && a_equipLv <= 20)
		return EQUIP_LEVEL_GEM_1_20;
	else if( 21 <= a_equipLv && a_equipLv <= 30)
		return EQUIP_LEVEL_GEM_21_30;
	else if( 31 <= a_equipLv && a_equipLv <= 40)
		return EQUIP_LEVEL_GEM_31_40;
	else if( 41 <= a_equipLv && a_equipLv <= 50)
		return EQUIP_LEVEL_GEM_41_50;
	else if(51 <= a_equipLv && a_equipLv <= 60)
		return EQUIP_LEVEL_GEM_51_60;
	
	return EQUIP_LEVEL_GEM_51_60;
}

// 获取槽个数
BSLib::uint32 CEquipConfigGMMgr::getEquipSlotCount(EQualityID a_qualityID) const
{
    switch (a_qualityID)
    {
    case QUALITY_WHITE:    { return 1; } break;
    case QUALITY_GREEN:    { return 2; } break;
    case QUALITY_BLUE:     { return 2; } break;
    case QUALITY_PURPLE:   { return 3; } break;
    case QUALITY_ORANGE:   { return 4; } break;
        // case QUALITY_RED:      { return 4; } break;
    default:               { return 0; } break;
    }
}

//     ?	攻击：(装备等级^2+装备等级+38)*2*品质参数*主属性占比*random[0.98,1.02]  // 2
//     ?	防御：(装备等级^2+装备等级+38)*2/2*品质参数*主属性占比*random[0.98,1.02] // 2/2 =1
//     ?	血量：(装备等级^2+装备等级+38)*2*30*品质参数*主属性占比*random[0.98,1.02] // 2*30
//     ?	命中：(装备等级^2+装备等级+38)*2/2*品质参数*主属性占比*random[0.98,1.02] // 2/2
//     ?	闪避：(装备等级^2+装备等级+38)*2/2*品质参数*主属性占比*random[0.98,1.02]//2/2
//     ?	暴击：(装备等级^2+装备等级+38)*2/2*品质参数*主属性占比*random[0.98,1.02]//2/2
//     ?	暴击抗性：(装备等级^2+装备等级+38)*2/2*品质参数*主属性占比*random[0.98,1.02]  //2/2
BSLib::uint32 CEquipConfigGMMgr::getEquipBassAttrParam(EAttrID a_attributeID) const
{
    switch (a_attributeID)
    {
    case ATTR_ATK: { return 2; } break;
    case ATTR_DEF: { return 1; } break;
    case ATTR_MAXHP: { return 60; } break;
    case ATTR_HIT_RATE: { return 1; } break;
    case ATTR_MISS_RATE: { return 1; } break;
    case ATTR_ATK_CRIFT: { return 1; } break;
    case ATTR_DEF_CRIFT: { return 1; } break;
    default: { return 1; } break;
    }
}

BSLib::uint32 CEquipConfigGMMgr::equipGrade(BSLib::uint32 a_lv)
{	
	if(a_lv >= EQUIP_ADD_MAX_LEVEL)
		return a_lv;

// 	return ++ a_lv;
// 
// 	// 成功率改成100%
	BSLib::uint32 num = BSLib::Utility::CRandom::randomBetween(1, 100);
	BSLib::uint32 base = m_attrSusRate[a_lv + 1];
	if( num <= base)
		return a_lv + 1;

	if(0 == a_lv || 5 == a_lv || 10 == a_lv)
		return a_lv;

	return a_lv - 1;
}

float CEquipConfigGMMgr::getEquipUpgradeRatie(BSLib::uint32 a_lv) const
{
	if( a_lv > EQUIP_ADD_MAX_LEVEL)
		return 0.0;

	return m_attrRatie[a_lv];
}

// ?	攻击：2*（强化等级^1.5+攻击主属性/2/150*强化等级）
// ?	防御：强化等级^1.5+防御主属性/150*强化等级
// ?	血量：60*（强化等级^1.5+血量主属性/30/150*强化等级）
// ?	命中：强化等级^1.5+命中主属性/150*强化等级
// ?	闪避：强化等级^1.5+闪避主属性/150*强化等级
// ?	暴击：强化等级^1.5+暴击主属性/150*强化等级
// ?	暴击抗性：强化等级^1.5+抗暴主属性/150*强化等级

// 获取强化增加的属性值
BSLib::uint32 CEquipConfigGMMgr::getEquipUpgradeLevelAddAttr(EAttrID a_attrID,BSLib::uint32 a_curAddLevel,BSLib::uint32 a_attrValue) const
{	
	float f_value = (float)a_attrValue;
	f_value *= (getEquipUpgradeRatie(a_curAddLevel));
	f_value +=  2* a_curAddLevel;
	return (BSLib::uint32)f_value;

	//////////////////////////////////
    float level = (float)a_curAddLevel;
    float baseValue = pow(level,1.5f);
    switch (a_attrID)
    {
    case ATTR_ATK:
        { 
            //     攻击：2*（强化等级^1.5+攻击主属性/2/150*强化等级）
            // 
            float f_attr = 2*(baseValue+ ((float)a_attrValue)*0.5f/150.0f*a_curAddLevel); 
            BSLib::uint32 attr = (BSLib::uint32)f_attr;
            return attr;
        } 
    case ATTR_DEF:
        { 
            //     防御：强化等级^1.5+防御主属性/150*强化等级
            float f_attr = baseValue+ ((float)a_attrValue)/150.0f*a_curAddLevel; 
            BSLib::uint32 attr = (BSLib::uint32)f_attr;
            return attr;
        } 
    case ATTR_MAXHP:
        { 
            //     血量：60*（强化等级^1.5+血量主属性/60/150*强化等级）
            float f_attr = 60*(baseValue+ ((float)a_attrValue)/60/150.0f*a_curAddLevel); 
            BSLib::uint32 attr = (BSLib::uint32)f_attr;
            return attr; 
        } 
        break;
    case ATTR_HIT_RATE:
        { 
            //     命中：强化等级^1.5+命中主属性/150*强化等级
            float f_attr = (baseValue+ ((float)a_attrValue)/150.0f*a_curAddLevel); 
            BSLib::uint32 attr = (BSLib::uint32)f_attr;
            return attr;
        } 
    case ATTR_MISS_RATE:
        { 
            //     闪避：强化等级^1.5+闪避主属性/150*强化等级
            float f_attr = (baseValue+ ((float)a_attrValue)/150.0f*a_curAddLevel); 
            BSLib::uint32 attr = (BSLib::uint32)f_attr;
            return attr;
        } 
    case ATTR_ATK_CRIFT:
        { 
            //     暴击：强化等级^1.5+暴击主属性/150*强化等级
            float f_attr = (baseValue+ ((float)a_attrValue)/150.0f*a_curAddLevel); 
            BSLib::uint32 attr = (BSLib::uint32)f_attr;
            return attr; 
        } 
    case ATTR_DEF_CRIFT:
        { 
            //     暴击抗性：强化等级^1.5+抗暴主属性/150*强化等级
            float f_attr = (baseValue + ((float)a_attrValue)/150.0f*a_curAddLevel); 
            BSLib::uint32 attr = (BSLib::uint32)f_attr;
            return attr;
        } 
    default: { return 1; } 
    }
}

// 获取强化增加的属性价值 用来算消耗
float CEquipConfigGMMgr::getEquipUpgradeLevelAddAttrValue(EAttrID a_attrID,BSLib::uint32 a_attrValue) const
{
    float baseValue = 0.f;
    switch (a_attrID)
    {
    case ATTR_ATK:
        { 
            //     ?	攻击：属性强度值^2*0.00005+属性强度值*0.00002
            baseValue = (float)a_attrValue;
        } 
        break;
    case ATTR_DEF:
        { 
            //         ?	防御：（属性强度值^2*0.00005+属性强度值*0.00002）*2
            baseValue = (float)a_attrValue *2;
        } 
        break;
    case ATTR_MAXHP:
        { 
            //         ?	血量：（属性强度值^2*0.00005+属性强度值*0.00002）/30
            baseValue = (float)a_attrValue /30;
        } 
        break;
    case ATTR_HIT_RATE:
        { 
            //         ?	命中：（属性强度值^2*0.00005+属性强度值*0.00002）*2
            baseValue = (float)a_attrValue *2;
        } 
        break;
    case ATTR_MISS_RATE:
        { 
            //         ?	闪避：（属性强度值^2*0.00005+属性强度值*0.00002）*2
            baseValue = (float)a_attrValue *2;
        } 
        break;
    case ATTR_ATK_CRIFT:
        { 
            //         ?	暴击：（属性强度值^2*0.00005+属性强度值*0.00002）*2
            baseValue = (float)a_attrValue *2;
        } 
        break;
    case ATTR_DEF_CRIFT:
        { 
            //         ?	暴击抗性：（属性强度值^2*0.00005+属性强度值*0.00002）*2
            baseValue = (float)a_attrValue *2;
        } 
        break;
    default: { return 1; } 
    }

    float f_attr = (0.00005f*baseValue*baseValue+ ((float)baseValue)*0.00002f); 
    return f_attr;
}
//     ?	攻击属性=Q         // = Q * getEquipAttachAttrParam(i);
//     ?	防御属性=Q/2
//     ?	血量属性=Q*30
//     ?	命中属性=Q/2
//     ?	闪避属性=Q/2
//     ?	暴击属性=Q/2
//     ?	暴击抗性属性=Q/2
// 附加属性中间值转属性参数
float CEquipConfigGMMgr::getEquipAttachAttrParam(EAttrID a_attributeID) const
{
    switch (a_attributeID)
    {
    case ATTR_ATK: { return 1.0f; } break;
    case ATTR_DEF: { return 0.5f; } break;
    case ATTR_MAXHP: { return 30.0f; } break;
    case ATTR_HIT_RATE: { return 0.5f; } break;
    case ATTR_MISS_RATE: { return 0.5f; } break;
    case ATTR_ATK_CRIFT: { return 0.5f; } break;
    case ATTR_DEF_CRIFT: { return 0.5f; } break;
    default: { return 1.0f; } break;
    }
}

// 熔炼： 属性价值计算
float CEquipConfigGMMgr::getEquipUpgradeQualityAttrValue(EAttrID a_attrID,BSLib::uint32 a_attrValue) const
{
    switch (a_attrID)
    {
    case ATTR_ATK:
        { 
            //     ?	攻击价值=攻击属性值^2*0.00005+攻击属性值*0.00002
            float f_attr = 0.00005f*a_attrValue*a_attrValue+ ((float)a_attrValue)*0.00002f; 
            return f_attr;
        } 
    case ATTR_DEF:
        { 
            //     ?	防御价值=（防御属性值*2）^2*0.00005+（防御属性值*2）*0.00002
            float f_attr = 0.00005f*a_attrValue*a_attrValue*4+ ((float)a_attrValue*2)*0.00002f; 
            return f_attr;
        } 
    case ATTR_MAXHP:
        { 
            //     ?	血量价值=（血量属性值/30）^2*0.00005+（血量属性值/30）*0.00002
            float f_attr = 0.00005f*((float)a_attrValue/30)*((float)a_attrValue/30)+ ((float)a_attrValue/30)*0.00002f;  
            return f_attr; 
        } 
        break;
    case ATTR_HIT_RATE:
        { 
            //     ?	命中价值=（命中属性值*2）^2*0.00005+（命中属性值*2）*0.00002
            float f_attr = (0.00005f*((float)a_attrValue*2)*((float)a_attrValue*2)+ ((float)a_attrValue*2)*0.00002f)*1;
            return f_attr;
        } 
    case ATTR_MISS_RATE:
        { 
            //     ?	闪避价值=（闪避属性值*2）^2*0.00005+（闪避属性值*2）*0.00002
            float f_attr = (0.00005f*((float)a_attrValue*2)*((float)a_attrValue*2)+ ((float)a_attrValue*2)*0.00002f)*1;
            return f_attr;
        } 
    case ATTR_ATK_CRIFT:
        { 
            //     ?	暴击价值=（暴击属性值*2）^2*0.00005+（暴击属性值*2）*0.00002
            float f_attr = (0.00005f*((float)a_attrValue*2)*((float)a_attrValue*2)+ ((float)a_attrValue*2)*0.00002f)*1;
            return f_attr; 
        } 
    case ATTR_DEF_CRIFT:
        { 
            //     ?	暴击抗性价值=（暴击抗性属性值*2）^2*0.00005+（暴击抗性属性值*2）*0.00002
            float f_attr = (0.00005f*((float)a_attrValue*2)*((float)a_attrValue*2)+ ((float)a_attrValue*2)*0.00002f)*1;
            return f_attr;
        } 
    default: { return 1; } 
    }
}

//     ?	攻击属性=M
//     ?	防御属性=M/2
//     ?	血量属性=M*30
//     ?	命中属性=M/2
//     ?	闪避属性=M/2
//     ?	暴击属性=M/2
//     ?	暴击抗性属性=M/2

// 洗练: 属性计算参数
float CEquipConfigGMMgr::getEquipAttachResetAttrParam(EAttrID a_attributeID) const
{
    switch (a_attributeID)
    {
    case ATTR_ATK: { return 1.0f; } break;
    case ATTR_DEF: { return 0.5f; } break;
    case ATTR_MAXHP: { return 30.0f; } break;
    case ATTR_HIT_RATE: { return 0.5f; } break;
    case ATTR_MISS_RATE: { return 0.5f; } break;
    case ATTR_ATK_CRIFT: { return 0.5f; } break;
    case ATTR_DEF_CRIFT: { return 0.5f; } break;
    default: { return 1.0f; } break;
    }
}
ItemTPID CEquipConfigGMMgr::getGemsTPIDByIndex(BSLib::uint32 a_itemIndex) const
{
    switch(a_itemIndex){
        case 0: { return GEMS_COLOR_WHITE_TPID;  } break;
        case 1: { return GEMS_COLOR_GREEN_TPID;  } break;
        case 2: { return GEMS_COLOR_BLUE_TPID;   } break;
        case 3: { return GEMS_COLOR_PURPLE_TPID; } break;
        case 4: { return GEMS_COLOR_ORANGE_TPID; } break;
        default:{ return 0;                      } break;
    }
}

ItemTPID CEquipConfigGMMgr::getGemsTPIDByQualityID(EQualityID a_qualityID) const
{
    switch(a_qualityID){
        case QUALITY_WHITE:  { return GEMS_COLOR_WHITE_TPID;  } break;
        case QUALITY_GREEN:  { return GEMS_COLOR_GREEN_TPID;  } break;
        case QUALITY_BLUE:   { return GEMS_COLOR_BLUE_TPID;   } break;
        case QUALITY_PURPLE: { return GEMS_COLOR_PURPLE_TPID; } break;
        case QUALITY_ORANGE: { return GEMS_COLOR_ORANGE_TPID; } break;
        default:{ return 0;                      } break;
    }
}

BSLib::uint32 CEquipConfigGMMgr::getIndexByGemsTPID(ItemTPID a_tpid) const
{
    switch(a_tpid){
        case GEMS_COLOR_WHITE_TPID:  { return 0;  } break;
        case GEMS_COLOR_GREEN_TPID:  { return 1;  } break;
        case GEMS_COLOR_BLUE_TPID:   { return 2;  } break;
        case GEMS_COLOR_PURPLE_TPID: { return 3;  } break;
        case GEMS_COLOR_ORANGE_TPID: { return 4;  } break;
        default:{return EQUIP_COLOR_GEMS_COUNT;} break;
    }
}

BSLib::uint32 getQiangDuPrimaryBase(EQualityID a_quality)
{
	BSLib::uint32 num[MAX_QUALITY_INDEX] = {0, 120, 300, 600, 1000, 2000, 4400};
	return num[a_quality];
}

BSLib::uint32 getQiangDuPrimaryDelta(EQualityID a_quality)
{
	BSLib::uint32 num[MAX_QUALITY_INDEX] = {0, 100 ,120, 150, 180, 200, 220};
	return num[a_quality];
}

BSLib::uint32 getQiangDuViceBase(EQualityID a_quality)
{
	BSLib::uint32 num[MAX_QUALITY_INDEX] = {0, 10, 30, 60, 100, 200, 400};
	return num[a_quality];
}

BSLib::uint32 getQiangDuViceDelta(EQualityID a_quality)
{
	BSLib::uint32 num[MAX_QUALITY_INDEX] = {0, 10, 12, 15, 18, 20, 22};
	return num[a_quality];
}

BSLib::uint32 CEquipConfigGMMgr::getQiangDu(EAttrID a_attr, EQualityID a_quality, BSLib::uint32 lv, bool a_first)
{
	if( 0 == lv)
		return 0;

	BSLib::uint32 qd = 0;
	if(!a_first)
		qd =  getQiangDuViceBase(a_quality) + ( lv - 1) * getQiangDuViceDelta(a_quality);
	else
		qd = getQiangDuPrimaryBase(a_quality) + ( lv - 1) * getQiangDuPrimaryDelta(a_quality);

	float rate = 0.0;
	switch(a_attr)
	{
	case ATTR_ATK:
		rate = 1;
		break;

	case ATTR_DEF:
		rate = 0.8;
		break;

	case ATTR_MAXHP:
		rate = 8;
		break;

	default:
		break;
	}
	
	float sum = qd;
	sum *= rate;
	return sum;
}

BSLib::uint32 CEquipConfigGMMgr::randNengLiangQiuAttr(EQualityID a_quality, SBattleAttribute& a_battleAttr, BSLib::uint32 type)
{
	const std::vector<BSLib::uint32>& nums = m_nengLiangQiuGaiLv[a_quality];
	BSLib::uint32 Q = BSLib::Utility::CRandom::randomBetween(0, 99);
	BSLib::uint32 attrNum = nums[Q];
	std::vector<EAttrID> totalAttr;
	totalAttr.push_back((EAttrID)type);
	while(totalAttr.size() < attrNum)
	{
		BSLib::uint32 temp = BSLib::Utility::CRandom::randomBetween(0, m_nengLiangQiuAttr.size() - 1);
		if( type != m_nengLiangQiuAttr[temp])
		{
			totalAttr.push_back(m_nengLiangQiuAttr[temp]);
		}
	}
			
	for(std::vector<EAttrID>::iterator it = totalAttr.begin(); it != totalAttr.end(); ++it)
	{
		switch(*it)
		{
		case ATTR_ATK:
			a_battleAttr.m_atk = getQiangDu(*it, a_quality, 1,  it == totalAttr.begin());
			break;

		case ATTR_DEF:
			a_battleAttr.m_def = getQiangDu(*it, a_quality, 1,  it == totalAttr.begin());
			break;

		case ATTR_MAXHP:
			a_battleAttr.m_maxHP = getQiangDu(*it, a_quality, 1,  it == totalAttr.begin());
			break;
		}
	}

	return totalAttr.size();
}

BSLib::uint32 getGuangZiLiPrimaryBase(EQualityID a_quality)
{
	BSLib::uint32 num[MAX_QUALITY_INDEX] = {0, 40, 100, 270, 400, 500, 600};
	return num[a_quality];
}

BSLib::uint32 getGuangZiLiPrimaryDelta(EQualityID a_quality)
{
	BSLib::uint32 num[MAX_QUALITY_INDEX] = {0, 6, 10, 23, 34, 44, 55};
	return num[a_quality];
}

BSLib::uint32 getGuangZiLiViceBase(EQualityID a_quality)
{
	BSLib::uint32 num[MAX_QUALITY_INDEX] = {0, 0, 60, 150, 150, 150, 150};
	return num[a_quality];
}

BSLib::uint32 getGuangZiLiViceDelta(EQualityID a_quality)
{
	BSLib::uint32 num[MAX_QUALITY_INDEX] = {0, 0, 10, 10, 10, 10, 10};
	return num[a_quality];
}

BSLib::uint32 CEquipConfigGMMgr::getGuangZiLi(EQualityID a_quality, BSLib::uint32 lv, bool a_twoAttribute)
{
	if( 0 == lv)
		return 0;

	BSLib::uint32 base[MAX_QUALITY_INDEX] = {0, 300, 420, 540, 700, 840, 1140};
	BSLib::uint32 delta[MAX_QUALITY_INDEX] = {0, 9, 12, 16, 20, 25, 30};
	return base[a_quality] + lv * delta[a_quality];

/////////////////////////////////////////////
	if(a_twoAttribute)
		return getGuangZiLiPrimaryBase(a_quality) + getGuangZiLiViceBase(a_quality) + ( lv - 1) * (getGuangZiLiPrimaryDelta(a_quality) + getGuangZiLiViceDelta(a_quality));

	return getGuangZiLiPrimaryBase(a_quality) + ( lv - 1) * getGuangZiLiPrimaryDelta(a_quality);
}

bool CEquipConfigGMMgr::getEquipBaseAttr(BSLib::uint32 a_tpid,const BSLib::uint32 a_equipLevel,EQualityID a_quality,SBattleAttribute& a_battleAttr) const
{
    CItemDataGM* itemData = CItemGMMgr::singleton().getItem(a_tpid);
    if(itemData == NULL){
        return false;
    }
    for(BSLib::uint32 i=0;i<MAX_ATTR_INDEX;++i){
        BSLib::uint32 attrDiff = (BSLib::uint32)(itemData->getAttrValue((EAttrID)i)*1000);
        if(attrDiff != 0){
            float mainParam = itemData->getAttrValue((EAttrID)i);
            BSLib::uint32 attrValue = getEquipUpgradeMainAttr((EAttrID)i,a_equipLevel,a_quality,mainParam);
            a_battleAttr.setValue((EAttrID)i,attrValue);
        }
    }
    return true;
}

// 计算主属性
BSLib::uint32 CEquipConfigGMMgr::getEquipUpgradeMainAttr(EAttrID a_attrID,const BSLib::uint32 a_equipLevel,EQualityID a_quality,float a_mainAttrPercent) const
{
    float qualityParam = getEquipQualityParam(a_quality);
    float attrValue = (a_equipLevel*a_equipLevel + a_equipLevel + 38)*getEquipBassAttrParam(a_attrID)*qualityParam*a_mainAttrPercent; 
    return (BSLib::uint32)attrValue;
}

float GetQualityRatio(EQualityID a_id)
{
	float id[MAX_QUALITY_INDEX] = {0, 1, 1.08, 1.16, 1.33, 1.7, 2};
	return  id[a_id];
}


bool CEquipConfigGMMgr::getCurAddAttr(BSLib::uint32 a_addLevel,const SBattleAttribute&a_attr,SBattleAttribute& a_addAttr, EQualityID a_quality, EEquipType a_type)
{
    for(BSLib::uint32 i=0; i<MAX_ATTR_INDEX; ++i){
        if(a_attr.getValue((EAttrID)i) == 0){
            a_addAttr.setValue((EAttrID)i,0);
            continue;
        }
       // BSLib::uint32 attrValue = getEquipUpgradeLevelAddAttr((EAttrID)i,a_addLevel,a_attr.getValue((EAttrID)i));
		float nums[EQUIP_ADD_MAX_LEVEL + 1] = {0, 10, 26, 45 ,70, 104, 150, 200 ,260 ,340, 430, 550, 700, 900, 1100, 1400};
		float ratio = (a_type == EQUIP_WEAPONS) ? 2: 1;
		BSLib::uint32 attrValue = (BSLib::uint32)(nums[a_addLevel] * GetQualityRatio(a_quality) * ratio);
		if( i == ATTR_MAXHP)
		{
			attrValue *= 10;
		}
        a_addAttr.setValue((EAttrID)i,attrValue);
    }
    return true;
}

bool CEquipConfigGMMgr::getCurAddAttrValue(const SBattleAttribute&a_addAttr,SBattleAttribute& a_addAttrValue,float& a_addValue)
{
    a_addValue = 0;
    for(BSLib::uint32 i=0; i<MAX_ATTR_INDEX; ++i){
        float attrValue = getEquipUpgradeLevelAddAttrValue((EAttrID)i,a_addAttr.getValue((EAttrID)i));
        a_addAttrValue.setValue((EAttrID)i,(BSLib::uint32)attrValue);
        a_addValue += attrValue;
    }
    return true;
}

BSLib::uint32 CEquipConfigGMMgr::getQualityValue(float a_proValue,BSLib::uint32 a_attrValue)
{
    const float EPSINON = 0.00001f;
    float diffValue = (float)a_attrValue - 6*a_proValue;
    if((diffValue <= EPSINON)) {
        // (2*（（道具价值+金币价值）*1.2)*(（道具价值+金币价值）*0.8))/属性价值
        float f_value = 2.0f* 6.0f*a_proValue*1.2f*6.0f*a_proValue*0.8f/a_attrValue;
        return (BSLib::uint32)f_value;
    }
    else{
        return 2*a_attrValue*a_attrValue;
    }
}

float CEquipConfigGMMgr::getCurQualityAddAttrValue(const SBattleAttribute&a_addAttr)
{
    float addValue = 0;
    for(BSLib::uint32 i=0; i<MAX_ATTR_INDEX; ++i){
        float attrValue = getEquipUpgradeQualityAttrValue((EAttrID)i,a_addAttr.getValue((EAttrID)i));
        addValue += attrValue;
    }
    return addValue;
}

bool CEquipConfigGMMgr::getUpgradeEquipAddLevelCondition(BSLib::uint32 a_addLevel,SBattleAttribute a_baseAddAttr, CConditionData* a_conditionData,
	EQualityID a_quality, BSLib::uint32 a_lv, EEquipType a_type)
{
    SBattleAttribute oldAddAttr;
    BSLib::uint32 oldAddLevel = a_addLevel;

    getCurAddAttr(oldAddLevel,a_baseAddAttr,oldAddAttr, a_quality, a_type);
    SBattleAttribute addAttr;
    getCurAddAttr(oldAddLevel+1,a_baseAddAttr,addAttr, a_quality, a_type);

    SBattleAttribute oldAddAttrValue;
    SBattleAttribute addAttrValue;
    float valueB = 0;
    float valueA = 0;
    getCurAddAttrValue(oldAddAttr,oldAddAttrValue,valueB);
    getCurAddAttrValue(addAttr,addAttrValue,valueA);
    float f_diffValue = valueA - valueB;
    return getNeedItemsByAddLevel(oldAddLevel+1,f_diffValue,a_conditionData->m_itemArray, a_quality, a_lv, a_conditionData->m_gold, a_conditionData->m_diamond, a_conditionData->m_guangzili, a_type);
}


bool CEquipConfigGMMgr::getNeedItemsByAddLevel(BSLib::uint32 a_addLevel,float a_diffValue, std::vector<CPrizeItem>& a_itemArray,
											   EQualityID a_quality, BSLib::uint32 a_lv, BSLib::uint32& a_gold, BSLib::uint32& a_diamond, BSLib::uint32& a_guangzili
											   , EEquipType a_type)
{
    a_itemArray.clear();
	{	
		float nums[EQUIP_ADD_MAX_LEVEL + 1] = {0, 2, 3, 4 ,5, 6, 3, 4 ,5 ,6, 7, 4, 5, 6, 7, 8};
		

		CPrizeItem item;
		item.m_itemType = EITEM_TP_EQUIP_UPGRADE_MATERIAL;
		item.m_itemTPID = getEquipUpgradeMetarialByQuality(a_addLevel);
		float ratio = (a_type == EQUIP_WEAPONS) ? 2: 1;
		item.m_itemCount = (BSLib::uint32)(nums[a_addLevel] * GetQualityRatio(a_quality) * ratio);
		a_itemArray.push_back(item);
	}

// 	{
// 		CPrizeItem item;
// 		item.m_itemType = EITEM_TP_EQUIP_QUALITY_MATERIAL;
// 		item.m_itemTPID = getEquipUpgradeMetarialByEquipLevel(a_lv, a_addLevel, item.m_itemCount);
// 		a_itemArray.push_back(item);
// 	}

	{
		//double temp = 1 + a_lv / 17;
		BSLib::uint32 ratio = (a_type == EQUIP_WEAPONS) ? 2: 1;
		BSLib::uint64 needGold = 100 * ratio * a_addLevel * a_addLevel;
// 		needGold /= 10;
// 		needGold *= 10;
		a_gold = needGold;
	}
    
	return true;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    const float EPSINON = 0.00001f;
    if ((a_addLevel >=0) &&(a_addLevel <=20)){
        // （强化后属性对应价值-强化前属性对应价值）/白色强化石价值
        CPrizeItem item;
        item.m_itemType = EITEM_TP_EQUIP_UPGRADE_MATERIAL;
        item.m_itemTPID = getEquipUpgradeMetarialByQuality(QUALITY_WHITE); // 白色强化石
        float itemValue = CItemGMMgr::singleton().getItemValue(item.m_itemTPID);
        if((itemValue >= - EPSINON) && (itemValue <= EPSINON)){
            return false;
        }
        float count = a_diffValue/itemValue;
        item.m_itemCount = getRound(count);
        a_itemArray.push_back(item);
    }
    else if ((a_addLevel >=21) &&(a_addLevel <=40)){
        // （强化后属性对应价值-强化前属性对应价值）*0.5/白色强化石价值
        CPrizeItem item;
        item.m_itemType = EITEM_TP_EQUIP_UPGRADE_MATERIAL;
        item.m_itemTPID = getEquipUpgradeMetarialByQuality(QUALITY_WHITE); // 白色强化石
        float itemValue = CItemGMMgr::singleton().getItemValue(item.m_itemTPID);
        if((itemValue >= - EPSINON) && (itemValue <= EPSINON)){
            return false;
        }
        float count = a_diffValue*0.5f/itemValue;
        item.m_itemCount =getRound(count);
        a_itemArray.push_back(item);

        item.m_itemType = EITEM_TP_EQUIP_UPGRADE_MATERIAL;
        item.m_itemTPID = getEquipUpgradeMetarialByQuality(QUALITY_GREEN); // 绿色强化石
        itemValue = CItemGMMgr::singleton().getItemValue(item.m_itemTPID);
        if((itemValue >= - EPSINON) && (itemValue <= EPSINON)){
            return false;
        }
        // （强化后属性对应价值-强化前属性对应价值）*0.5/绿色强化石价值
        count = a_diffValue*0.5f/itemValue;
        item.m_itemCount =getRound(count);
        a_itemArray.push_back(item);
    }
    else if ((a_addLevel >=41) &&(a_addLevel <=60)){
        // （强化后属性对应价值-强化前属性对应价值）*0.5/绿色强化石价值
        CPrizeItem item;
        item.m_itemType = EITEM_TP_EQUIP_UPGRADE_MATERIAL;
        item.m_itemTPID = getEquipUpgradeMetarialByQuality(QUALITY_GREEN); // 绿色强化石
        float itemValue = CItemGMMgr::singleton().getItemValue(item.m_itemTPID);
        if((itemValue >= - EPSINON) && (itemValue <= EPSINON)){
            return false;
        }
        float count = a_diffValue*0.5f/itemValue;
        item.m_itemCount =getRound(count);
        a_itemArray.push_back(item);

        item.m_itemType = EITEM_TP_EQUIP_UPGRADE_MATERIAL;
		item.m_itemTPID = getEquipUpgradeMetarialByQuality(QUALITY_BLUE); // 蓝色强化石
        itemValue = CItemGMMgr::singleton().getItemValue(item.m_itemTPID);
        if((itemValue >= - EPSINON) && (itemValue <= EPSINON)){
            return false;
        }
       
        //（强化后属性对应价值-强化前属性对应价值）*0.5/蓝色强化石价值
        count = a_diffValue*0.5f/itemValue;
        item.m_itemCount =getRound(count);
        a_itemArray.push_back(item);
    }
    else if ((a_addLevel >=61) &&(a_addLevel <=80)){
        CPrizeItem item;
        item.m_itemType = EITEM_TP_EQUIP_UPGRADE_MATERIAL;
        item.m_itemTPID = getEquipUpgradeMetarialByQuality(QUALITY_BLUE); // 蓝色强化石
        float itemValue = CItemGMMgr::singleton().getItemValue(item.m_itemTPID);
        if((itemValue >= - EPSINON) && (itemValue <= EPSINON)){
            return false;
        }
        //（强化后属性对应价值-强化前属性对应价值）*0.5/蓝色强化石价值
        float count = a_diffValue*0.5f/itemValue;
        item.m_itemCount =getRound(count);
        a_itemArray.push_back(item);

        item.m_itemType = EITEM_TP_EQUIP_UPGRADE_MATERIAL;
        item.m_itemTPID = getEquipUpgradeMetarialByQuality(QUALITY_PURPLE); // 紫色强化石
        itemValue = CItemGMMgr::singleton().getItemValue(item.m_itemTPID);
        if((itemValue >= - EPSINON) && (itemValue <= EPSINON)){
            return false;
        }
       
        //（强化后属性对应价值-强化前属性对应价值）*0.5/紫色强化石价值
        count = a_diffValue*0.5f/itemValue;
        item.m_itemCount =getRound(count);
        a_itemArray.push_back(item);
    }
    else if ((a_addLevel >=81) &&(a_addLevel <=100)){
        CPrizeItem item;
        item.m_itemType = EITEM_TP_EQUIP_UPGRADE_MATERIAL;
        item.m_itemTPID = getEquipUpgradeMetarialByQuality(QUALITY_PURPLE); // 紫色强化石
        float itemValue = CItemGMMgr::singleton().getItemValue(item.m_itemTPID);
        if((itemValue >= - EPSINON) && (itemValue <= EPSINON)){
            return false;
        }
        // （强化后属性对应价值-强化前属性对应价值）*0.5/紫色强化石价值
        float count = a_diffValue*0.5f/itemValue;
        item.m_itemCount = getRound(count);
        a_itemArray.push_back(item);

        item.m_itemType = EITEM_TP_EQUIP_UPGRADE_MATERIAL;
        item.m_itemTPID = getEquipUpgradeMetarialByQuality(QUALITY_ORANGE); // 橙色强化石
        itemValue = CItemGMMgr::singleton().getItemValue(item.m_itemTPID);
        if((itemValue >= - EPSINON) && (itemValue <= EPSINON)){
            return false;
        }
      
        //(强化后属性对应价值-强化前属性对应价值）*0.5/橙色强化石价值
        count = a_diffValue*0.5f/itemValue;
        item.m_itemCount = getRound(count);
        a_itemArray.push_back(item);
    }

    // 最少消耗1
    for(BSLib::uint32 i=0;i< a_itemArray.size(); ++i){
        CPrizeItem& item = a_itemArray[i];
        if(item.m_itemCount == 0){
            item.m_itemCount = 1;
        }
    }

    return true;
}

bool CEquipConfigGMMgr::randNewEquip(BSLib::uint32 a_tpid,EItemType& a_itemType,EQualityID& a_quality,
									 BSLib::uint32& a_level,SBattleAttribute& a_battleAttr,CAttachAttr& a_attachAttrs, BSLib::uint32& a_specfun1)
{
    CItemDataGM* itemData = CItemGMMgr::singleton().getItem(a_tpid);
    if(itemData == NULL){
        return false;
    }

    if(CItemGMMgr::singleton().getMainType(a_tpid) != EMAIN_TP_EQUIP){
        return false;
    }
	
	a_specfun1 = itemData->getSpecfunc2();
    a_itemType = itemData->getType();
    a_quality = itemData->getQualityID();
    a_level = itemData->getLevel();
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[randNewEquip][a_tpid=%d][根据装备tpid读取基本信息][a_itemType=%d][a_quality=%d][a_level=%d]",a_tpid,a_itemType,a_quality,a_level);
	
    // 计算主属性
	if(EITEM_TP_EQUIP_NENGLIANGQIU == a_itemType)
	{
		randNengLiangQiuAttr(a_quality, a_battleAttr, itemData->getSpecfunc1());
		for(BSLib::uint32 i=0;i<MAX_ATTR_INDEX;++i){
			BSLib::uint32 attrValue = (BSLib::uint32)(itemData->getAttrValue((EAttrID)i));
			if(attrValue != 0){
				BSLib::uint32 mainParam = itemData->getAttrValue((EAttrID)i);
				a_battleAttr.setValue((EAttrID)i,attrValue + mainParam);
			}
		}
		return true;
	}
	else
	{
		for(BSLib::uint32 i=0;i<MAX_ATTR_INDEX;++i){
			BSLib::uint32 attrValue = (BSLib::uint32)(itemData->getAttrValue((EAttrID)i));
			if(attrValue != 0){
				// float mainParam = itemData->getAttrValue((EAttrID)i);
				// BSLib::uint32 level = itemData->getLevel();
				// EQualityID quality = itemData->getQualityID();
				// BSLib::uint32 attrValue = _getEquipBaseAttr((EAttrID)i,level,quality,mainParam);
				a_battleAttr.setValue((EAttrID)i,attrValue);
			}
		}
	}
    

// 	//     for(BSLib::uint32 i=0;i<MAX_ATTR_INDEX;++i){
// 	//         BSLib::uint32 attrDiff = (BSLib::uint32)(itemData->getAttrValue((EAttrID)i)*1000);
// 	//         if(attrDiff != 0){
// 	//             float mainParam = itemData->getAttrValue((EAttrID)i);
// 	//             BSLib::uint32 level = itemData->getLevel();
// 	//             EQualityID quality = itemData->getQualityID();
// 	//             BSLib::uint32 attrValue = _getEquipBaseAttr((EAttrID)i,level,quality,mainParam);
// 	//             a_battleAttr.setValue((EAttrID)i,attrValue);
// 	//         }
// 	//     }
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[randNewEquip][a_tpid=%d][生成装备基础战斗属性]a_battleAttr=%s",a_tpid,a_battleAttr.toLogString().c_str());
	
	//TODO: 重新计算附加属性
    return randEquipAttachAttr(a_tpid, a_quality,a_level,a_attachAttrs);
}

bool CEquipConfigGMMgr::randEquipAttachAttr(BSLib::uint32 a_tpid, EQualityID a_quality,BSLib::uint32 a_level,CAttachAttr& a_attachAttrs) const
{
    // 计算附加属性
	std::vector<EAttrID> attrs;
    BSLib::uint32 attrCount = getEquipAttachAttrCount(a_quality, attrs);	//获取附加属性的种类
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[randEquipAttachAttr][a_quality=%d][根据装备a_quality读取附加战斗属性个数][attrCount=%d]",a_quality,attrCount);
    BSLib::uint32 curAttrCount = 0;
    a_attachAttrs.m_attrArray.clear();
	std::vector<EQualityID> ids;
	if(0 != attrCount)
	{
		ids.push_back(a_quality);
		curAttrCount++;
		while(curAttrCount < attrCount)
		{
			ids.push_back(QUALITY_GREEN);
			curAttrCount++;
		}
	}
	
	BSLib::uint32 i = 0;
	for(std::vector<EQualityID>::iterator it = ids.begin(); it != ids.end(), i < attrCount; ++it, i++)
	{	
		EQualityID attQuality = *it;
        float attachPercent = (float)getEquipAttachAttr(attrs[i],a_level, attQuality); // 获得对应附加属性的, 颜色,和值
		attachPercent /= 100;
		
		float attachValue = attachPercent * CItemGMMgr::singleton().getSpecfunc1(a_tpid);
		if(attrs[i] == ATTR_MAXHP)
		{
			attachValue *= 10;
		}
		BSLib::uint32 uint32Value = (BSLib::uint32)attachValue;
		if( 0 == uint32Value)
			uint32Value = 1;

        CAttribute attr;
        attr.setAttrIndex(i);
        attr.setAttrID(attrs[i]);
        attr.setAttrValue(uint32Value);
		attr.setQuality(attQuality);
        a_attachAttrs.m_attrArray.push_back(attr);
    }
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[randEquipAttachAttr][a_quality=%d][a_level=%d][生成装备附加战斗属性]a_attachAttr=%s",a_quality,a_level,a_attachAttrs.toLogString().c_str());

    return true;
}

BSLib::uint32 CEquipConfigGMMgr::randEquipAttachAttrM(BSLib::uint32 a_equipLevel,float a_resetSum) const
{
    float f_equipLevel =((float)a_equipLevel) ;
    float baseValue = f_equipLevel * f_equipLevel + (f_equipLevel +38)*2/24;
    float minValue = 1.0f;
    const float EPSINON = 0.00001f;
    float fmin = 0.4f*baseValue;
    float diff = fmin -1.0f;
    if ((diff >= - EPSINON) && (diff <= EPSINON)){
        minValue = fmin;
    }
    else{
        minValue = 1.0f;
    }
    float f_equipLevelMax = f_equipLevel +30; 
    float maxValue = (f_equipLevelMax*f_equipLevelMax+ f_equipLevelMax+38)*2/24;
    float diffValue = maxValue - minValue;
    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "[equipLevel=%d][minValue=%f][maxValue=%f]",a_equipLevel,minValue,maxValue);
    // 10个点属性值
    BSLib::uint32 p[] = {0,0,0,0,0,0,0,0,0,0,0};
    p[0] = (BSLib::uint32)minValue;
    p[1] = getRound((float)p[0]+(float)diffValue*0.2f);
    p[2] = getRound((float)p[1]+(float)diffValue*0.18f);
    p[3] = getRound((float)p[2]+(float)diffValue*0.16f);

    p[4] = getRound((float)p[3]+(float)diffValue*0.13f);
    p[5] = getRound((float)p[4]+(float)diffValue*0.11f);
    p[6] = getRound((float)p[5]+(float)diffValue*0.09f);

    p[7] = getRound((float)p[6]+(float)diffValue*0.07f);
    p[8] = getRound((float)p[7]+(float)diffValue*0.04f);
    p[9] = getRound((float)p[8]+(float)diffValue*0.02f);

    // 点属性价值
    float pvalue[] = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
    for(BSLib::uint32 i=0;i<10; ++i){
        pvalue[i] = ((p[i]*24.0f)*(p[i]*24.0f)*0.00005f + (p[i]*24.0f) *0.00002f)/24;
        BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "点属性值[p%d=%d]点属性价值[pvalue%d=%f]",i,p[i],i,pvalue[i]);
    }
    // 区间价值
    float areaValue[] = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
    for(BSLib::uint32 i=0;i<9; ++i){
        areaValue[i] = pvalue[i+1]-pvalue[0];
        BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "区间价值[areaValue%d=%f]",i,areaValue[i]);
    }

    float S = a_resetSum;
    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "洗练累计价值[sum=%f]",S);
    // 区间过度价值
    float areaTempValue[] = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
    // 被除数为0校验
    if((BSLib::uint32)(areaValue[8]*1000) == 0){
        BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "数值错误[areaValue8=%f]",areaValue[8]);
        return ERESETATTR_RESULT_FAIL;
    }

    float TotalArea = 0;
    for(BSLib::uint32 i=0;i<9; ++i){
        areaTempValue[i] = (S-areaValue[8])*areaValue[i] + areaValue[i]*areaValue[i];
        TotalArea += areaTempValue[i];
        BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "区间过度价值[areaTempValue%d=%f]",i,areaTempValue[i]);
    }
    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "区间过度价值总和[TotalArea=%f]",TotalArea);
    float percentValue[] ={0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
    for(BSLib::uint32 i=0;i<9;++i){
        percentValue[i] = areaTempValue[i]*100000/TotalArea;
        BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "区间放大概率[percentValue%d=%f]",i,percentValue[i]);
    }

    BSLib::uint32 rateValue[] ={0,0,0,0,0,0,0,0,0,0};
    rateValue[0] = (BSLib::uint32)percentValue[0];
    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "条件判断概率[rateValue0=%d]",rateValue[0]);
    for(BSLib::uint32 i=1;i<9 ;++i){
        rateValue[i] = rateValue[i-1] + getRound(percentValue[i]);
        BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "条件判断概率[rateValue%d=%d]",i,rateValue[i]);
    }

    BSLib::uint32 Q = BSLib::Utility::CRandom::randomBetween(1,rateValue[8]);
    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "[Q=%d]",Q);
    BSLib::uint32 area = 0;
    BSLib::uint32 findIndex = 0;
    for(findIndex=0;findIndex<9; ++findIndex){
        if(Q < rateValue[findIndex]){
            area = findIndex;
            break;
        }
    }
    if(findIndex == 9){
        return ERESETATTR_RESULT_FAIL;
    }
    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "随机到的区间[findIndex=%d]",area);
    BSLib::uint32 begin = p[area];
    BSLib::uint32 end = p[area + 1];
    BSLib::uint32 M = BSLib::Utility::CRandom::randomBetween(begin,end);
    BSLIB_LOG_DEBUG(ETT_GSLIB_EQUIPSYSTEM, "随机范围[%d,%d]随机值[M=%d]",begin,end,M);

    return M;
}

bool CEquipConfigGMMgr::randNewEquipAttachAttr(EQualityID a_quality,BSLib::uint32 a_equipLevel,float a_resetSum,const std::vector<BSLib::uint32>& a_lockAttrIndexArray,CAttachAttr& a_attachAttrs) const
{
    // 计算附加属性
    BSLib::uint32 attrCount = getEquipAttachAttrCount(a_quality);
    const BSLib::uint32 lockCount = a_lockAttrIndexArray.size();
    if(attrCount <= lockCount){
        return true;
    }
    attrCount -= lockCount;
    BSLib::uint32 attrIndex[7]={0,0,0,0,0,0,0};
    for(BSLib::uint32 i=0; i < a_lockAttrIndexArray.size(); ++i){
        BSLib::uint32 index = a_lockAttrIndexArray[i];
        if ((index >=0)&&(index < 7)){
            attrIndex[index] = 1;
        }
    }
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[randEquipAttachAttr][a_quality=%d][根据装备a_quality读取附加战斗属性个数][attrCount=%d]",a_quality,attrCount);
    BSLib::uint32 curAttrCount = 0;
    while(curAttrCount<attrCount){
        BSLib::uint32 id = BSLib::Utility::CRandom::randomBetween(0,6);
        if(attrIndex[id] == 1){
            continue;
        }
        BSLib::uint32 attrID = id;
        curAttrCount++;
        float p = getEquipAttachAttrParam((EAttrID)attrID);
        BSLib::uint32 M = randEquipAttachAttrM(a_equipLevel,a_resetSum);
        BSLib::uint32 attrValue = (BSLib::uint32)(p * M); 
        CAttribute attr;
        BSLib::uint32 newIndex = 0;
        a_attachAttrs.getNextEmptyIndex(newIndex);
        attr.setAttrIndex(newIndex);
        attr.setAttrID((EAttrID)attrID);
        attr.setAttrValue(attrValue);
        a_attachAttrs.m_attrArray.push_back(attr);
    }
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[randEquipAttachAttr][a_quality=%d][a_level=%d][生成装备附加战斗属性]a_attachAttr=%s",a_quality,a_equipLevel,a_attachAttrs.toLogString().c_str());

    return true;
}

BSLib::uint32	CEquipConfigGMMgr::getResetRate(EQualityID a_id)
{
	switch(a_id)
	{
	case QUALITY_WHITE:
		return 50;

	case QUALITY_GREEN:
		return 40;

	case QUALITY_BLUE:
		return 30;

	case QUALITY_PURPLE:
		return 20;

	case QUALITY_ORANGE:
		return 10;

	default:
		return 0;
	}
}

// 计算基础属性用于计算属性
BSLib::uint32 CEquipConfigGMMgr::getEquipAttachAttr(EAttrID a_attrID,const BSLib::uint32 a_equipLevel, EQualityID &a_quality) const
{	
// 	std::vector<EQualityID> ids;
// 	for(BSLib::uint32 i = QUALITY_ORANGE; i > QUALITY_WHITE && ids.size() < 100; i--)
// 	{		
// 		BSLib::uint32 num = _getColorProb(100 - ids.size(), (EQualityID)i, a_equipLevel);
// 		ids.insert(ids.begin(), num, (EQualityID)i);
// 	}
// 	
// 	if( 100  >  ids.size())
// 	{
// 		ids.insert(ids.begin(), 100 - ids.size(), QUALITY_WHITE);
// 	}
// 
// 	std::random_shuffle(ids.begin(), ids.end());
// 	BSLib::uint32 Q = BSLib::Utility::CRandom::randomBetween(0,99);
// 	a_quality = ids[Q];
	
	
//     BSLib::uint32 max_value = _getEquipAttachAttrMaxValue(a_equipLevel);
//     BSLib::uint32 min_value = _getEquipAttachAttrMinValue(a_equipLevel);
//     BSLib::uint32 pointA = _getEquipPointA(a_equipLevel);
//     BSLib::uint32 pointB = _getEquipPointB(pointA,max_value,min_value);
//     BSLib::uint32 Q = BSLib::Utility::CRandom::randomBetween(pointA,pointB);
//     float p = getEquipAttachAttrParam(a_attrID);
//     BSLib::uint32 attr = (BSLib::uint32)(p * Q); 
//     BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "[getEquipAttachAttr][a_attrID=%d][a_equipLevel=%d][附加战斗属性值]"
// 		"[max_value=%d][min_value=%d][pointA=%d][pointB=%d][Q=%d][p=%f][attr=%d]",a_attrID,a_equipLevel,max_value,min_value,pointA,pointB,attr,p,attr);
	BSLib::uint32 attr = _getAttrValueProb(a_quality);
    return attr;
}

// ?	攻击：(装备等级^2+装备等级+38)*2*品质参数*主属性占比*random[0.98,1.02]
// ?	防御：(装备等级^2+装备等级+38)*2/2*品质参数*主属性占比*random[0.98,1.02]
// ?	血量：(装备等级^2+装备等级+38)*2*30*品质参数*主属性占比*random[0.98,1.02]
// ?	命中：(装备等级^2+装备等级+38)*2/2*品质参数*主属性占比*random[0.98,1.02]
// ?	闪避：(装备等级^2+装备等级+38)*2/2*品质参数*主属性占比*random[0.98,1.02]
// ?	暴击：(装备等级^2+装备等级+38)*2/2*品质参数*主属性占比*random[0.98,1.02]
// ?	暴击抗性：(装备等级^2+装备等级+38)*2/2*品质参数*主属性占比*random[0.98,1.02]
// 计算主属性
BSLib::uint32 CEquipConfigGMMgr::_getEquipBaseAttr(EAttrID a_attrID,const BSLib::uint32 a_equipLevel,EQualityID a_quality,float a_mainAttrPercent) const
{
    float qualityParam = getEquipQualityParam(a_quality);
    float attrValue = 0;
    BSLib::uint32 num = BSLib::Utility::CRandom::randomBetween(98,102);
    float fNum = (float)num/100;
    attrValue = (a_equipLevel*a_equipLevel + a_equipLevel + 38)*getEquipBassAttrParam(a_attrID)*qualityParam*a_mainAttrPercent*fNum; 
    return (BSLib::uint32)attrValue;
}

BSLib::uint32 CEquipConfigGMMgr::_getAttrValueProb(EQualityID a_id) const
{
	BSLib::uint32 x = 0; 
	BSLib::uint32 y = 0;
	switch(a_id)
	{
	case QUALITY_RED:
		x = 40;
		y = 60;
		break;

	case QUALITY_ORANGE:
		x = 20;
		y = 30;
		break;

	case QUALITY_PURPLE:
		x = 10;
		y = 15;
		break;

	case QUALITY_BLUE:
		x = 5;
		y = 7;
		break;

	case QUALITY_GREEN:
		x = 1;
		y = 3;
		break;

	case QUALITY_WHITE:
		return 0;
	}

	return BSLib::Utility::CRandom::randomBetween(x,y);	
}

BSLib::uint32 CEquipConfigGMMgr::_getColorProb(BSLib::uint32 a_left, EQualityID a_id, BSLib::uint32 a_level) const
{	
	BSLib::uint32 base = 0;
	switch(a_id)
	{
	case QUALITY_WHITE:
		base = a_left;
		break;

	case QUALITY_GREEN:
		base = 47;
		break;

	case QUALITY_BLUE:
		base = 28;
		break;

	case QUALITY_PURPLE:
		base = 18;
		break;

	case QUALITY_ORANGE:
		base = 10;
		break;
	}
	
	float x = base;
	float y = 0.7;
	float z = a_level / 10;
	float sum = pow(y,z);
	return sum * x; 
}

float CEquipConfigGMMgr::_getEquipAttachAttrBaseValue(BSLib::uint32 a_level) const
{
    return ((float)(a_level*a_level +a_level +38)*2)/24;

}

BSLib::uint32 CEquipConfigGMMgr::_getEquipAttachAttrMinValue(BSLib::uint32 a_level) const
{
    float base = _getEquipAttachAttrBaseValue(a_level);
    return (BSLib::uint32)(0.4 * base);
}

BSLib::uint32 CEquipConfigGMMgr::_getEquipPointA(BSLib::uint32 a_level) const
{
    BSLib::uint32 attr = _getEquipAttachAttrMinValue(a_level);
    if(attr > 1){
        return attr;
    }
    else{
        return 1;
    }
}

BSLib::uint32 CEquipConfigGMMgr::_getEquipAttachAttrMaxValue(BSLib::uint32 a_level) const
{
    return (BSLib::uint32)(((a_level+30)*(a_level+30) +(a_level+30) +38)*2)/24;
}

BSLib::uint32 CEquipConfigGMMgr::_getEquipPointB(BSLib::uint32 a_pointA,BSLib::uint32 a_max,BSLib::uint32 a_min) const
{
    float temp = (a_pointA + a_max - a_min)*0.2f;
    BSLib::uint32 baseValue = (BSLib::uint32)temp;
    BSLib::uint32 add = ((BSLib::uint32)(temp*10))%10;
    if(add > 4){
        baseValue += 1;
    }
    return baseValue;
}

}//GM

}//EquipSystem

}//GSLib

