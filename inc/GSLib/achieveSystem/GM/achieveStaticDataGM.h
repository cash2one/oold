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
#include <GSLib/itemSystem/GM/itemAttributeGMMgr.h>
#include <BSLib/utility/table.h>

namespace GSLib
{

namespace AchieveSystem
{

namespace GM
{


class CItemStaticDataGM
{
public:
	CItemStaticDataGM();
	virtual ~CItemStaticDataGM();

	CItemAttributeGMMgr*getAttributeMgr() const{return m_attributeMgr;}

	bool isItemData(const BSLib::uint32 a_itemTPID,GSLib::AchieveSystem::GM::EItemType a_itemType);

    bool loadData(BSLib::Utility::CTableRow& a_tableRow);
    const BSLib::uint64 CItemStaticDataGM::getUniqueID()const;
private:
	CItemAttributeGMMgr* m_attributeMgr;

};

}//GM

}//AchieveSystem

}//GSLib

#endif//__GSLIB_ITEMSYSTEM_GM_ITEMSYSTEMGM_H__
