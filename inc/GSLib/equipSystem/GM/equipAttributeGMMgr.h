//////////////////////////////////////////////////////////////////////
//	created:	2014/07/28
//	filename: 	GSLib\loginSystem\GM\netPlayerGMMgr.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_EQUIPSYSTEM_GM_EQUIPATTRIBUTEGMMGR_H__
#define __GSLIB_EQUIPSYSTEM_GM_EQUIPATTRIBUTEGMMGR_H__

#include <GSLib/equipSystem/GM/equipAttributeGM.h>
#include <GSLib/baseDef.h>
namespace GSLib
{

namespace EquipSystem
{

namespace GM
{

class CEquipAttributeGMMgr
{
public:
	CEquipAttributeGMMgr();
	CEquipAttributeGMMgr(CEquipAttributeGMMgr& a_equipAttributeGMMgr);
	virtual ~CEquipAttributeGMMgr();

	void init();
	void final();

public:
    bool initBaseBattleVaule(EBattleAttributeID m_attributeIndex,const std::string& valueAarry);
	BSLib::uint32 getBattleBaseValue(EBattleAttributeID a_attributeIndex);
	BSLib::uint32 getBattleFixValue(EBattleAttributeID a_attributeIndex);
	BSLib::uint32 getBattleValue(EBattleAttributeID a_attributeIndex);
	BSLib::uint32 getEquipValue(EBattleAttributeID a_attributeIndex);
	void setBattleBaseValue(EBattleAttributeID a_attributeIndex,BSLib::uint32 value);
	void setBattleFixValue(EBattleAttributeID a_attributeIndex,BSLib::uint32 value);
	void setEquipBaseValue(EBattleAttributeID a_attributeIndex,BSLib::uint32 value);
    bool _getAttrValue(const std::string& srcAttr,BSLib::uint32& value) const;



private:
	std::vector<CEquipBattleAttribute> m_roleUInt32Attribute;
	std::vector<CBaseAttribute> m_baseAttribute;
};

}//GM

}//PlayerSystem

}//GSLib

#endif//__GSLIB_EQUIPSYSTEM_GM_EQUIPATTRIBUTEGMMGR_H__