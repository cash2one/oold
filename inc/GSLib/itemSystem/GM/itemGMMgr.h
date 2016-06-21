
#ifndef __GSLIB_ITEMSYSTEM_GM_ITEMGMMGR_H__
#define __GSLIB_ITEMSYSTEM_GM_ITEMGMMGR_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/memory/objectMgr.h>
#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/itemSystem/GM/itemDataGM.h>
#include <GSLib/itemSystem/GM/itemGMMgr.h>
namespace GSLib
{

namespace ItemSystem
{

namespace GM
{

class CItemGMMgr
{
public:
	CItemGMMgr();
	virtual ~CItemGMMgr();

    BSLIB_SINGLETON_DECLARE(CItemGMMgr);
	void init();
	void final();
	bool loadGameConfig(const std::string& a_configPath);

public:
	CItemDataGM* getItem(ItemTPID a_itemTPID) const;

    // 角色相关
public:
    BSLib::uint32 getAddVitality(ItemTPID a_tpid) const;
    BSLib::uint32 getBuyVitalityMaxTimes(BSLib::uint32 vipLevel) const;
    BSLib::uint32 getBuyVitalityNeedDiamond(BSLib::uint32 a_buyTimes) const;

public:
    bool getCombineGemTPID(ItemTPID a_itemTPID,ItemTPID& a_newGemTPID) const;

public:
    // 伙伴相关
    BSLib::uint32 getPetAddFriendlyValue(bool isFavorite, ItemTPID a_tpid) const;
    BSLib::uint32 getPetMaxLevel(ItemTPID a_tpid) const;
    bool getPetAttrB(ItemTPID a_tpid,EAttrID a_attrID,float& a_b) const;
    bool getPetTPIDArray(std::vector<ItemTPID>& a_petTPIDArrays) const;
    bool getPetBaseAttrs(ItemTPID a_tpid,SBattleAttribute& a_petBaseAttrs) const;
    bool getPetUpgradeAttrs(ItemTPID a_tpid,SBattleAttribute& a_petUpgradeAttrs) const;
public:
    // 宝石相关
    bool getGemAttr(ItemTPID a_tpid,SBattleAttribute& a_battleAttr) const;

public:
    bool isValid(ItemTPID a_itemTPID) const;
	bool isUse(ItemTPID a_itemTPID) const;
    bool isSell(ItemTPID a_itemTPID) const;
	bool isRepeated(ItemTPID a_itemTPID) const;

    bool isTPResource(ItemTPID a_itemTPID) const;
    bool isTPItem(ItemTPID a_itemTPID) const;

public:
    float getItemValue(ItemTPID a_tpid) const;
    BSLib::uint32 getPrice(ItemTPID a_itemTPID) const;
	BSLib::uint32 getStackCount(ItemTPID a_itemTPID) const;

	EItemType getType(ItemTPID a_itemTPID) const;
	EMainType getMainType(ItemTPID a_itemTPID) const;
    EQualityID getQualityID(ItemTPID a_tpid) const;

    BSLib::uint32 getProLimit(ItemTPID a_tpid) const;
    BSLib::uint32 getLevelLimit(ItemTPID a_tpid) const;
    BSLib::uint32 getSpecfunc1(ItemTPID a_tpid) const;
    BSLib::uint32 getSpecfunc2(ItemTPID a_tpid) const;
    std::string getSpecfunc3(ItemTPID a_tpid) const;
    std::string getSpecfunc4(ItemTPID a_tpid) const;

    bool isPetLovelyItems(ItemTPID a_tpid,ItemTPID a_lovelyItemTPID) const;
    bool getPetLovelyItems(ItemTPID a_tpid,std::vector<ItemTPID>& a_itemTPIDArray) const;
    bool getSynthesisArray(ItemTPID a_tpid,std::vector<CPrizeItem>& a_itemArray) const;

private:
    void _removeAllItem();
	bool _loadItemConfig(const std::string& a_configPath);

private:
	BSLib::Utility::CHashMap<ItemTPID, CItemDataGM*> m_itemHashMap;
    std::vector<ItemTPID> m_petTPIDArray;
};

}//GM

}//ItemSystem

}//GSLib

#endif//__GSLIB_ITEMSYSTEM_GM_ITEMGMMGR_H__

