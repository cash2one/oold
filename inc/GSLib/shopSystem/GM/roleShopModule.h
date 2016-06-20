
#ifndef __GSLIB_SHOPSYSTEM_GM_ROLESHOPMODULE_H__
#define __GSLIB_SHOPSYSTEM_GM_ROLESHOPMODULE_H__

#include <GSLib/playerSystem/GM/roleModuleGM.h>
#include <BSLib/database/dbTableRow.h>
#include <GSLib/shopSystem/DB/tableShopDB.h>
#include <GSLib/shopSystem/msgNumIDShopSystem.h>
#include <GSLib/shopSystem/GM/shop.proto.h>
#include <GSLib/shopSystem/GM/cardConfig.h>
#include <GSLib/shopSystem/GM/shop.proto.h>

namespace GSLib
{

namespace ShopSystem
{

namespace GM
{


class CRoleShopModule : public GSLib::PlayerSystem::GM::CRoleModuleGM
	, BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::CCallback
{
public:
	CRoleShopModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType);
	virtual ~CRoleShopModule();

	virtual void preInit(bool isFirst);
	virtual void postInit(bool isFirst);
	virtual void initToClient();
	virtual void final();

	virtual void initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual void freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	virtual void updateDataToDB();
	virtual bool cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
	virtual bool exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value);


private:
	void _onMsgShopSystemGC2GMReqShopOpen(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgShopSystemGC2GMReqShopBuy(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgShopSystemGC2GMReqShopRefresh(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgShopSystemGC2GMReqShopPaidRefresh(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	void _onMsgShopSystemGC2GMReqOpenCard(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgShopSystemGC2GMReqEventState(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgShopSystemGC2GMReqClick(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	bool				_shopOpen(EShopType a_shopType, ShopSystemAllItemsInfo& a_info, BSLib::uint64& a_timestamp);
	EShopSystemResult	_shopBuy(EShopType a_shopType, BSLib::int32 a_id, BSLib::int32 a_num, BSLib::int32& a_left);
	EShopSystemResult	_shopPaidRefresh(EShopType a_shopType, std::vector<BSLib::int32>& a_ids, std::vector<BSLib::int32>& a_nums);
	EShopSystemResult	_shopRefresh(EShopType a_shopType, std::vector<BSLib::int32>& a_ids, std::vector<BSLib::int32>& a_nums, BSLib::uint64& a_timestamp);
	BSLib::uint64		_shopGetLeftRefreshTime(EShopType a_shopType);
	DB::SRoleShopData*	_shopGetShopData(EShopType a_shopType);
	BSLib::int32		_shopGetLeft(EShopType a_shopType, BSLib::int32 a_id);
	BSLib::int32		_shopGetbought(EShopType a_shopType, BSLib::int32 a_id);
	bool				_shopCheckRefreshConditon(EShopType a_shopType);
	bool				_shopInit();

	bool				_pay(BSLib::int32 type, BSLib::int32 price);

	bool				_dbUpdateShop(DB::SRoleShopData* shop);
	bool				_dbUpudateBought(EShopType a_shopType, BSLib::int32 a_itemId, BSLib::int32 a_itemNum);
	
	bool				_timeIsSameDay(BSLib::uint64 a_timeStamp);
	bool				_timeIsSameMonth(BSLib::uint64 a_timeStamp);
	BSLib::int64		_timeDiff(BSLib::int64 a_timeStamp);

	bool				_checkCardCondition(BSLib::uint32 a_funType, BSLib::uint32 a_costType, BSLib::uint32& a_itemId, BSLib::uint32& a_itemNum);
	BSLib::uint32		_getCardTypeId(BSLib::uint32 a_funType, BSLib::uint32 a_costType);
	bool				_rollCard(BSLib::uint32 a_funType, BSLib::uint32 a_costType,
									std::vector< BSLib::uint32>& a_itemIds, std::vector< BSLib::uint32>& a_ItemNums, BSLib::uint32& a_eventId);
	bool				_updateEvent(BSLib::int32 a_prizeId, BSLib::uint32 a_eventId);
	bool				_eventIsFull(BSLib::int32 a_eventId);
	void				_doEvent(BSLib::int32 a_eventId);
	void				_getCardInfo(BSLib::uint32 a_funType, CMsgShopSystemGM2GCAckOpenCard& a_ack);
private:
	GSLib::DBSystem::CKeyIndexTablePtr			m_tablePtr;
	std::map<EShopType , DB::SRoleShopData *>	m_shops;
};

}//GM

}

}//GSLib

#endif