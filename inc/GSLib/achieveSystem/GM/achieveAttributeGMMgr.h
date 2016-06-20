//////////////////////////////////////////////////////////////////////
//	created:	2014/07/28
//	filename: 	GSLib\loginSystem\GM\netPlayerGMMgr.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_ITEMSYSTEM_GM_ITEMATTRIBUTEGMMGR_H__
#define __GSLIB_ITEMSYSTEM_GM_ITEMATTRIBUTEGMMGR_H__

#include <GSLib/itemSystem/GM/itemAttributeGM.h>

namespace GSLib
{

namespace AchieveSystem
{

namespace GM
{

class CItemAttributeGMMgr
{
public:
	CItemAttributeGMMgr();
	virtual ~CItemAttributeGMMgr();

	void init();
	void final();

public:
	BSLib::uint32  getAttribute(EItemUInt32Attribute m_attributeIndex);
	void setAttribute(EItemUInt32Attribute m_attributeIndex,BSLib::uint32 value);
private:
	std::vector<CItemUInt32Attribute> m_itemUInt32Attribute;
};

}//GM

}//PlayerSystem

}//GSLib

#endif//__GSLIB_ITEMSYSTEM_GM_ITEMATTRIBUTEGMMGR_H__
