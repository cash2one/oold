#ifndef __GSLIB_EQUIPSYSTEM_GM_ROLEQUIPGM_H__
#define __GSLIB_EQUIPSYSTEM_GM_ROLEQUIPGM_H__

#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/equipSystem/baseDef.h>
#include <GSLib/equipSystem/GM/equipAttributeGM.h>
#include <GSLib/equipSystem/DB/tableEquipDB.h>
#include <GSLib/itemSystem/GM/itemAttributeGM.h>
namespace GSLib
{

namespace EquipSystem
{

namespace GM
{

class CConditionData{
public:
    BSLib::uint32 m_gold;
    BSLib::uint32 m_diamond;
	BSLib::uint32 m_guangzili;
    std::vector<ItemSystem::GM::CPrizeItem> m_itemArray;

    CConditionData()
    {
        m_gold = 0;
        m_diamond = 0;
		m_guangzili = 0;
    };

    ~CConditionData()
    {
        m_gold = 0;
        m_diamond = 0;
    };

    bool serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_gold;
        stream << m_diamond;
		stream << m_guangzili;
        BSLib::uint32 itemCount = m_itemArray.size();
        stream << itemCount;
        for(BSLib::uint32 i=0;i < itemCount;++i){
            ItemSystem::GM::CPrizeItem item = m_itemArray[i];
            item.serializeTo(stream);
        }
        return true;
    }
};

class CRoleEquipGM
{
public:
    CRoleEquipGM(EEquipType a_equipType,
        BSLib::uint32 a_equipID,
        BSLib::uint32 a_equipTPID,
        BSLib::uint32 a_equipLevel,
        BSLib::uint32 a_equipAddLevel,
        float a_resetSum,
        BSLib::uint64 a_equipColorGemsCount[EQUIP_COLOR_GEMS_COUNT],
        EQualityID a_qualityID,
         const SBattleAttribute a_attr,const CAttachAttr& a_attachAttr,SBattleAttribute a_addAttr,EEquipStatus a_equipStatus);

    CRoleEquipGM(EEquipType a_equipType,const DB::SRoleEquipData& a_equipData);
    CRoleEquipGM();
	~CRoleEquipGM();

public:
	bool initGems(BSLib::uint32 slotCount,const BSLib::uint32 a_slotGemTPID[4]);
    void final();
	void setGemCount(BSLib::uint32 a_gemCount);
    bool setGemTPID(EGemSlot a_posIndex,ItemTPID a_gemTPID);

	BSLib::uint32 getGemCount() const;
	BSLib::uint32 getGemTPID(BSLib::uint32 a_gemIndex) const;
    bool getNextAddLevelData(BSLib::Utility::CStream& stream);
    bool getGemsData(BSLib::Utility::CStream& stream) const;

    bool serializeEquipOptionResultTo(EEquipOperation operate,EQualityID qualityID,const SBattleAttribute& a_battleAttr,BSLib::Utility::CStream& stream) const;
    bool serializeResetAttrResultTo(EEquipOperation operate,EQualityID qualityID,const CAttachAttr& a_battleAttr,BSLib::Utility::CStream& stream) const;

    bool serializeTo(BSLib::Utility::CStream& stream) const;
    bool getDataForBag(BSLib::Utility::CStream& stream) const;
	bool getEquipData(DB::SRoleEquipData& equipData) const;
    bool getEquipDetailData(CEquipData& equipData) const;
    bool getTotalBattleAttr(SBattleAttribute& a_equipBattleAttr) const;
    bool getAttachAttr(CAttachAttr& a_attachAttr) const;
    // 更新装备属性
    bool updateEquipBattleAttr();
    // 修改强化属性
    bool modifyBattleAddAttr();
	// 修改能量球强化属性
	bool modifyNengliangqiuBattleAddAttr(SBattleAttribute& a_addAttr);

    const SBattleAttribute& getBattleAttr() const;
    bool getUpgradeCondition(CConditionData& a_conditionData) const;
	bool getUpgradeNengLiangQiuCond(CConditionData& a_conditionData); // ***
	bool getNengLiangQiuAttr(EAttrID& mainId, EAttrID& viceId);		//***
	BSLib::uint32 getBaseAttr(EAttrID a_id);		// 获取基础属性

public:
    BSLib::uint32 getTPID() const { return m_equipTPID; }
    BSLib::uint32 getEquipID() const { return m_equipID; }
    BSLib::uint32 getLevel() const { return m_equipLevel; }
    BSLib::uint32 getEquipAddLevel() const { return m_equipAddLevel; }
    BSLib::uint32 getSlotCount() const { return m_slotCount; }
    BSLib::uint32 getCombat() const { return m_combat; }

    EQualityID getQuality() const { return m_quality; }
    EEquipType getType() const { return m_equipType; }
    EEquipStatus getEquipStatus() const { return m_equipStatus; }
    float getResetSum() const { return m_resetSum; }

    bool isStatusOn() const;
    bool getDisassemblyEquipResult(std::vector<ItemSystem::GM::CPrizeItem>& a_itemArray);

public:
    void setEquipType(EEquipType a_equipType){ m_equipType = a_equipType; }
    void setEquipLevel(BSLib::uint32 a_equipLevel){ m_equipLevel = a_equipLevel; }
    void setEquipAddLevel(BSLib::uint32 a_equipAddLevel){ m_equipAddLevel = a_equipAddLevel; }
    void setEquipTPID(BSLib::uint32 a_equipTPID){ m_equipTPID = a_equipTPID; }
    void setQuality(EQualityID a_quality){ m_quality= a_quality; }
    void setResetSum(float a_resetSum){ m_resetSum= a_resetSum; }

    void setEquipStatus(EEquipStatus a_status){ m_equipStatus = a_status; }
    void setBattleAttr(const SBattleAttribute& a_battleAttr){ m_baseBattleAttr = a_battleAttr; }
    void setAttachAttr(const CAttachAttr& a_attachAttr){ m_attachAttr = a_attachAttr; }
    void addUseGemsCount(const std::vector<ItemSystem::GM::CPrizeItem>& a_itemArray);
    void serializeDisassemblyEquipResultTo(BSLib::Utility::CStream& stream);
    bool updateTotalAttr();
    bool updateEquipStatus();

private:
    void _addUseGems(ItemTPID a_tpid);
    bool _getUseGemsItem(BSLib::uint32 a_itemIndex,ItemSystem::GM::CPrizeItem& a_item) const;

private:
	bool _updateFixAttr();
    void _updateCombat();

private:
    BSLib::uint32 m_equipID;
    BSLib::uint32 m_equipTPID;

    EQualityID m_quality;
    BSLib::uint32 m_equipLevel;
    BSLib::uint32 m_equipAddLevel;
    EEquipType m_equipType;
    EEquipStatus m_equipStatus;

    float m_resetSum;
public:
    BSLib::uint64 m_equipColorGemsCount[EQUIP_COLOR_GEMS_COUNT];

private:
    SBattleAttribute m_totalBattleAttr;    // 属性总和
    SBattleAttribute m_baseBattleAttr;     // 基础属性
    CAttachAttr m_attachAttr;              // 附加属性
    //SBattleAttribute m_attachBattleAttr;   // 附加属性
    SBattleAttribute m_addBattleAttr;      // 强化属性
    SBattleAttribute m_fixBattleAttr;      // 宝石属性
    BSLib::uint32 m_combat;                // 战斗力
private:
    BSLib::uint32 m_slotCount;
    BSLib::uint32 m_gemCount;
    BSLib::uint32 m_slotGemTPID[EQUIP_GEM_MAXCOUNT];

public:
	bool m_canUndo;
	CAttachAttr m_oldAttach;
};

}//GM

}//EquipSystem

}//GSLib

#endif//__GSLIB_EQUIPSYSTEM_GM_ROLEQUIPGM_H__

