//////////////////////////////////////////////////////////////////////
//	created:	2014/07/25
//	filename: 	GSLib\itemSystem\GM\CItemGM.h
//	author:	     zhangping	
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_ITEMSYSTEM_GM_ITEMDATAGM_H__
#define __GSLIB_ITEMSYSTEM_GM_ITEMDATAGM_H__

#include <GFLib/commonServer/commonSystem.h>
#include <BSLib/utility/table.h>
#include <GSLib/itemSystem/GM/itemAttributeGM.h>
#include <GSLib/baseDef.h>
namespace GSLib
{

namespace ItemSystem
{

namespace GM
{


class CItemDataGM
{
public:
	CItemDataGM();
	virtual ~CItemDataGM();

public:
	bool loadData(BSLib::Utility::CTableRow& a_tableRow);

	std::string getName() const;
    const std::vector<ItemTPID>& getPetLovelyItems() const;
    const std::vector<CPrizeItem>& getSynthesisArray() const;
	bool isItemData(ItemTPID a_itemTPID,GSLib::ItemSystem::GM::EItemType a_itemType) const;
    bool isValid(ItemTPID a_itemTPID) const;
	bool isSell() const;
	bool isUse() const;

    BSLib::uint32 getPrice() const;
	BSLib::uint32 getStackCount() const;
	BSLib::uint32 getLevel() const;

	EItemType getType() const;
    EMainType getMainType() const;
    BSLib::uint32 getProLimit() const;
    ItemTPID getTPID() const;
    EQualityID getQualityID() const;

    void getGemAttr(SBattleAttribute& a_battleAttr) const;
    BSLib::uint32 getPetAttrCount(std::vector<EAttrID>& a_attrIDs) const;
    bool getPetBaseAttrs(SBattleAttribute& a_petBaseAttrs) const;
    bool getPetUpgradeAttrs(SBattleAttribute& a_petUpgradeAttrs) const;

    float getAtk() const;
    float getDef() const;
    float getHP() const;
    float getHitRate()const;
    float getMissRate() const;
    float getAtkCrift() const;
    float getDefCrift() const;

    float getItemValue() const;
    BSLib::uint32 getSpecfunc1() const;
    BSLib::uint32 getSpecfunc2() const;
    std::string getSpecfunc3() const;
    std::string getSpecfunc4() const;
    float getAttrValue(EAttrID a_attrID) const;
    std::string getSynthesis() const;
	bool enableAnnounce() const;

	BSLib::uint32 getTimeLimit() const;
	
private:
    bool _initPetAttr();
    bool _initPetLovelyItems();
private:
	std::string m_name;
    bool m_isSell;
    bool m_isUse;
    BSLib::uint32 m_price;
    BSLib::uint32 m_countLimit;
    BSLib::uint32 m_itemTPID;
    EItemType m_itemType;

    BSLib::uint32 m_specfunc1;
    BSLib::uint32 m_specfunc2;
    std::string m_specfunc3;
    std::string m_specfunc4;
    BSLib::uint32 m_level;
    float  m_value;

    float m_atk;
    float m_def;
    float m_hp;
    float m_hitRate;
    float m_missRate;
    float m_atkCrift;
    float m_defCrift;

    BSLib::uint32 m_proLimit;
    EQualityID m_quality;

    BSLib::uint32 m_useLevel;
    BSLib::uint32 m_timeLimit;
    std::string m_synthesis;
	bool m_announce;
    std::vector<CPrizeItem> m_synthesisArray;
    std::vector<ItemTPID> m_petLovelyItemArray;
    SBattleAttribute m_petBaseAttr;
    SBattleAttribute m_petUpgradeAttr;
};

}//GM

}//ItemSystem

}//GSLib

#endif//__GSLIB_ITEMSYSTEM_GM_ITEMSYSTEMGM_H__
