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
	std::map< EQualityID, std::vector<BSLib::uint32> > m_attNumProb; // ���������������
	std::vector<EAttrID> m_attIDProb;	// ��ȡָ��������
	std::vector<float> m_attrRatie;  // װ��������
	std::vector<BSLib::uint32> m_attrSusRate;
public:
    BSLib::uint32 getRound(float a_value) const;
    // װ�����
public:
    // ��ȡװ����ʼƷ�ʲ�����
	BSLib::uint32 getEquipAttachAttrCount(EQualityID a_qualityID, std::vector<EAttrID>& a_attrs) const;
	BSLib::uint32 getEquipAttachAttrCount(EQualityID a_qualityID) const;

    // ��ȡװ����ʼƷ�ʲ�����
    float getEquipQualityParam(EQualityID a_qualityID) const;

    // ǿ������ȡװ��ǿ���ȼ�����
    BSLib::uint32 getEquipUpgradeMaxLevelByQuality(EEquipType a_type, EQualityID a_qualityID) const;

    // ǿ��, ��ȡǿ���������
    ItemTPID getEquipUpgradeMetarialByQuality(BSLib::uint32  a_lv) const;

	ItemTPID getEquipUpgradeMetarialByEquipLevel(BSLib::uint32  a_equipLv, BSLib::uint32 a_addLevel, BSLib::uint32 & a_num) const ;

    // ��ʯ����ȡ�۸���
    BSLib::uint32 getEquipSlotCount(EQualityID a_qualityID) const;
    BSLib::uint32 getEquipBassAttrParam(EAttrID a_attributeID) const;

    // ǿ������ȡǿ�����ӵ�����ֵ
    BSLib::uint32 getEquipUpgradeLevelAddAttr(EAttrID a_attrID,BSLib::uint32 a_curAddLevel,BSLib::uint32 a_attrValue) const;

	// ǿ�� : ���װ��������
	float	getEquipUpgradeRatie(BSLib::uint32 a_lv) const;
	// ����ǿ���ɹ��ĵȼ�
	BSLib::uint32 equipGrade(BSLib::uint32 a_lv);

    // ǿ������ȡǿ�����ӵ����Լ�ֵ ����������
    float getEquipUpgradeLevelAddAttrValue(EAttrID a_attrID,BSLib::uint32 a_attrValue) const;

    // ���������м�ֵת���Բ���
    float getEquipAttachAttrParam(EAttrID a_attributeID) const;

    // ������ ���Լ�ֵ����
    float getEquipUpgradeQualityAttrValue(EAttrID a_attrID,BSLib::uint32 a_attrValue) const;

    // ϴ��: ���Լ������
    float getEquipAttachResetAttrParam(EAttrID a_attributeID) const;
public:
    ItemTPID getGemsTPIDByIndex(BSLib::uint32 a_itemIndex) const;
    ItemTPID getGemsTPIDByQualityID(EQualityID a_qualityID) const;
    BSLib::uint32 getIndexByGemsTPID(ItemTPID a_tpid) const;


	//** ��Ҫ�Ĺ�����
	BSLib::uint32 getGuangZiLi(EQualityID a_quality, BSLib::uint32 lv, bool a_twoAttribute);

	//** ��õ�ǿ��
	BSLib::uint32 getQiangDu(EAttrID a_attr, EQualityID a_quality, BSLib::uint32 lv, bool a_first);
	
	// **�漴�������������
	BSLib::uint32 randNengLiangQiuAttr(EQualityID a_quality, SBattleAttribute& a_battleAttr, BSLib::uint32 type);

	std::vector<std::vector<BSLib::uint32> > m_nengLiangQiuGaiLv;
	std::vector<EAttrID> m_nengLiangQiuAttr;

    // ǿ�����
public:
    // ��ȡ��ǰǿ���ȼ���Ӧ�Ļ�������ֵ
    bool getEquipBaseAttr(BSLib::uint32 a_tpid,const BSLib::uint32 a_equipLevel,EQualityID a_quality,SBattleAttribute& a_battleAttr) const;
    BSLib::uint32 getEquipUpgradeMainAttr(EAttrID a_attrID,const BSLib::uint32 a_equipLevel,EQualityID a_quality,float a_mainAttrPercent) const;
    // ��ȡ��ǰǿ���ȼ���Ӧ��ǿ������ֵ
    bool getCurAddAttr(BSLib::uint32 a_addLevel,const SBattleAttribute&a_attr,SBattleAttribute& a_addAttr, EQualityID a_quality, EEquipType a_type);
    // ��ȡ��ǰǿ���ȼ���Ӧ��ǿ�����Լ�ֵ
    bool getCurAddAttrValue(const SBattleAttribute&a_addAttr,SBattleAttribute& a_addAttrValue,float& a_addValue);

    // �������
public:
    // װ����������
    BSLib::uint32 getQualityValue(float a_proValue,BSLib::uint32 a_attrValue);
    // װ���������Լ�ֵ
    float getCurQualityAddAttrValue(const SBattleAttribute& a_addAttr);

    // ǿ�����
public:
    // ǿ�����ļ���
    bool getUpgradeEquipAddLevelCondition(BSLib::uint32 a_addLevel,SBattleAttribute a_baseAddAttr, CConditionData* a_conditionData,
		EQualityID a_quality, BSLib::uint32 a_lv, EEquipType a_type);
    // ǿ�����ļ���
	bool getNeedItemsByAddLevel(BSLib::uint32 a_addLevel,float a_diffValue, std::vector<ItemSystem::GM::CPrizeItem>& a_itemArray,
		EQualityID a_quality, BSLib::uint32 a_lv, BSLib::uint32& a_gold, BSLib::uint32& a_diamond, BSLib::uint32& a_guangzili, EEquipType a_type);

    // ����װ��
public:
    bool randNewEquip(BSLib::uint32 a_tpid,ItemSystem::GM::EItemType& a_itemType,EQualityID& a_quality,
		BSLib::uint32& a_level,SBattleAttribute& a_battleAttr,CAttachAttr& a_attachAttrs, BSLib::uint32& a_specfun1);
    bool randEquipAttachAttr(BSLib::uint32 a_tpid, EQualityID a_quality,BSLib::uint32 a_level,CAttachAttr& a_attachAttrs) const;
    BSLib::uint32 randEquipAttachAttrM(BSLib::uint32 a_equipLevel,float a_resetSum) const;
    bool randNewEquipAttachAttr(EQualityID a_quality,BSLib::uint32 a_equipLevel,float a_resetSum,const std::vector<BSLib::uint32>& a_lockAttrIndexArray,CAttachAttr& a_attachAttrs) const;
    // ��������������ڼ�������
    BSLib::uint32 getEquipAttachAttr(EAttrID a_attrID,const BSLib::uint32 a_equipLevel, EQualityID &a_quality) const;

	BSLib::uint32 getResetRate(EQualityID a_id); // ��ȡϴ���ĸ���

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
