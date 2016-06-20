//////////////////////////////////////////////////////////////////////
//	created:	2014/08/03
//	filename:	GSLib\itemSystem\GM\playerGMMgr.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////

#ifndef __GSLIB_ITEMSYSTEM_GM_ITEMGMMGR_H__
#define __GSLIB_ITEMSYSTEM_GM_ITEMGMMGR_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/memory/objectMgr.h>
#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/itemSystem/GM/itemStaticDataGM.h>
#include <GSLib/itemSystem/GM/itemstaticdatagmmgr.h>
namespace GSLib
{

namespace AchieveSystem
{

namespace GM
{

struct SItemUseConfig{

	BSLib::uint32 m_id;
	BSLib::uint32 m_useHP;
	BSLib::uint32 m_useSP;
	BSLib::int64 m_useExp;

	SItemUseConfig(){
		m_id = 0;
		m_useHP = 0;
		m_useSP = 0;
		m_useExp = 0;
	};
	bool loadData(BSLib::Utility::CTableRow& a_tableRow)
	{
		a_tableRow["f_id"] >> m_id;
		a_tableRow["f_hp"] >> m_useHP;
		a_tableRow["f_sp"] >> m_useSP;
		a_tableRow["f_exp"] >> m_useExp;

		return true;
	}
};


struct SItemSellConfig{

	BSLib::uint32 m_id;
	BSLib::int64 m_gold;

	SItemSellConfig(){
		m_id = 0;
		m_gold = 0;
	};
	bool loadData(BSLib::Utility::CTableRow& a_tableRow)
	{
		a_tableRow["f_id"] >> m_id;
		a_tableRow["f_gold"] >> m_gold;

		return true;
	}
};

class CItemStaticDataGMMgr:public BSLib::Utility::CUniqueIDMgr<BSLib::uint32>
{
public:
	CItemStaticDataGMMgr();
	virtual ~CItemStaticDataGMMgr();

    BSLIB_SINGLETON_DECLARE(CItemStaticDataGMMgr);
	void init();
	void final();
	bool loadGameConfig(const std::string& a_configPath);
	bool _loadItemConfig(const std::string& a_configPath);
	bool _loadItemUseConfig(const std::string& a_configPath);
	bool _loadItemSellConfig(const std::string& a_configPath);

private:
    virtual bool checkUniqueID(BSLib::uint32 id);

public:
	CItemStaticDataGM* getItemStaticDataGM(const BSLib::uint32 a_itemTPID,GSLib::AchieveSystem::GM::EItemType a_ItemType);
	void removeAllItemDataGM();

	SItemUseConfig* getItemUseConfigGM(const BSLib::uint32 a_itemTPID);
	void removeAllItemUseConfigGM();

	SItemSellConfig* getItemSellConfigGM(const BSLib::uint32 a_itemTPID);
	void removeAllItemSellConfigGM();
    
	BSLib::uint64 _makeUInt64Key(BSLib::uint32 a_left,BSLib::uint32 a_right);
private:
	BSLib::Utility::CHashMap<BSLib::uint32, SItemSellConfig*> m_itemSellDataHashMap;
	BSLib::Utility::CHashMap<BSLib::uint32, SItemUseConfig*> m_itemUseDataHashMap;
	BSLib::Utility::CHashMap<BSLib::uint64, CItemStaticDataGM*> m_ItemDataHashMap;
	BSLib::Utility::CUniqueID<BSLib::uint32> m_uniqueIDByItemIndex;
};

}//GM

}//AchieveSystem

}//GSLib

#endif//__GSLIB_ITEMSYSTEM_GM_ITEMGMMGR_H__
