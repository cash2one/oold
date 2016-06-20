
#include <GSLib/shopSystem/GM/roleShopModule.h>
#include <GSLib/shopSystem/msgShopSystem.h>
#include <GSLib/tracer.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/playerSystem/GM/playerGM.h>
#include <GSLib/shopSystem/DB/tableShopDB.h>
#include <GSLib/shopSystem/GM/shopSystemGM.h>
#include <GSLib/playerSystem/GM/playerGM.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <map>
#include <GSLib/shopSystem/DB/tableShopDB.h>
#include <GSLib/shopSystem/GM/shopConfig.h>
#include <algorithm>
#include <BSLib/utility/dateTime.h>
#include <GSLib/prizeSystem/GM/rolePrizeModule.h>
#include <GSLib/playerSystem/GM/roleBagModuleGM.h>
#include <GSLib/shopSystem//GM/cardConfig.h>

namespace GSLib
{

namespace ShopSystem
{

namespace GM
{

#define  ONE_DAY	(60 * 24)

#define FRIEND_GOLD1_RECORD			221
#define FRIEND_DIAMOND1_RECORD		222
#define GUANGZILI_GOLD1_RECORD		223
#define GUANGZILI_DIAMOND1_RECROD	224
#define GUANGZILI_EVENT				225

CRoleShopModule::CRoleShopModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType)
:  GSLib::PlayerSystem::GM::CRoleModuleGM(a_roleGM, a_moduleType)
{
}

CRoleShopModule::~CRoleShopModule()
{
	;
}

void CRoleShopModule::preInit(bool isFirst)
{	

}

void CRoleShopModule::postInit(bool isFirst)
{
	if(isFirst){
		_shopInit();
		PlayerSystem::GM::CRoleGM* role = getRoleGM();
		PrizeSystem::GM::CRolePrizeModule* prizeModule =  (PrizeSystem::GM::CRolePrizeModule*)role->getPlayerModuleGM(EMODULECTYPE_PRIZE);
		prizeModule->_prizeOnlyReg(GUANGZILI_EVENT);
	}
}

void CRoleShopModule::initToClient()
{	
}

void CRoleShopModule::final()
{
	;
}

void CRoleShopModule::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDShopSystemGC2GMReqShopOpen, &BSLib::Framework::CreateCMessage<CMsgShopSystemGC2GMReqShopOpen>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDShopSystemGC2GMReqShopOpen, &CRoleShopModule::_onMsgShopSystemGC2GMReqShopOpen, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDShopSystemGC2GMReqShopBuy, &BSLib::Framework::CreateCMessage<CMsgShopSystemGC2GMReqShopBuy>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDShopSystemGC2GMReqShopBuy, &CRoleShopModule::_onMsgShopSystemGC2GMReqShopBuy, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDShopSystemGC2GMReqShopRefresh, &BSLib::Framework::CreateCMessage<CMsgShopSystemGC2GMReqShopRefresh>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDShopSystemGC2GMReqShopRefresh, &CRoleShopModule::_onMsgShopSystemGC2GMReqShopRefresh, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDShopSystemGC2GMReqShopPaidRefresh,
		&BSLib::Framework::CreateCMessage<CMsgShopSystemGC2GMReqShopPaidRefresh>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDShopSystemGC2GMReqShopPaidRefresh, &CRoleShopModule::_onMsgShopSystemGC2GMReqShopPaidRefresh, this);
	//>>>>>>>>
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDCMsgShopSystemGC2GMReqOpenCard,
		&BSLib::Framework::CreateCMessage<CMsgShopSystemGC2GMReqOpenCard>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDCMsgShopSystemGC2GMReqOpenCard, &CRoleShopModule::_onMsgShopSystemGC2GMReqOpenCard, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDCMsgShopSystemGC2GMReqEventState,
		&BSLib::Framework::CreateCMessage<CMsgShopSystemGC2GMReqEventState>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDCMsgShopSystemGC2GMReqEventState, &CRoleShopModule::_onMsgShopSystemGC2GMReqEventState, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDCMsgShopSystemGC2GMReqClick,
		&BSLib::Framework::CreateCMessage<CMsgShopSystemGC2GMReqClick>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDCMsgShopSystemGC2GMReqClick, &CRoleShopModule::_onMsgShopSystemGC2GMReqClick, this);
}

void CRoleShopModule::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	a_msgExecMgr->delMsgExecPtr(msgIDShopSystemGC2GMReqShopOpen);
	a_msgExecMgr->delMsgExecPtr(msgIDShopSystemGC2GMReqShopBuy);
	a_msgExecMgr->delMsgExecPtr(msgIDShopSystemGC2GMReqShopRefresh);
	a_msgExecMgr->delMsgExecPtr(msgIDShopSystemGC2GMReqShopPaidRefresh);

	a_msgExecMgr->delMsgExecPtr(msgIDCMsgShopSystemGC2GMReqOpenCard);
	a_msgExecMgr->delMsgExecPtr(msgIDCMsgShopSystemGC2GMReqEventState);
	a_msgExecMgr->delMsgExecPtr(msgIDCMsgShopSystemGC2GMReqClick);
}

void CRoleShopModule::updateDataToDB()
{
}

bool CRoleShopModule::cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
	if( a_tableID == EDBTABLEID_ROLE_SHOP_DATA){
		m_tablePtr = a_keyTable;
		m_tablePtr->traversal(*this);
	}

	return true;
}

bool CRoleShopModule::exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value)
{
	BSLib::Utility::CStream stream;
	a_value->serializeTo(stream);

	DB::SRoleShopData* shop = new DB::SRoleShopData;
	shop->serializeFrom(stream);
	m_shops.insert(std::make_pair((EShopType)shop->m_shopType, shop));

	return true;
}


void CRoleShopModule::_onMsgShopSystemGC2GMReqShopOpen(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgShopSystemGC2GMReqShopOpen *req = (CMsgShopSystemGC2GMReqShopOpen *)a_msg;
	
	CMsgShopSystemGM2GCAckShopOpen ack;
	ack.m_type = req->m_type;
	_shopOpen(req->m_type, ack.info, ack.m_refreshTime);
	ack.m_refreshTime = _shopGetLeftRefreshTime(ack.m_type);
	sendMsgToClient(ack);
}

BSLib::uint64 CRoleShopModule::_shopGetLeftRefreshTime(EShopType a_shopType)
{
	DB::SRoleShopData* shop = _shopGetShopData(a_shopType);
	if( NULL == shop)
		return 0;


	SShopConfigInfo* shopConfig = NULL;
	if( !CShopSystemGM::singleton().getConfig().getShopConfig(a_shopType, shopConfig)){
		return 0;
	}

	if( 0 == shopConfig->m_refreshPeriod){
		return 0;
	}
	
	using namespace  BSLib::Utility;
	CDateTime curTime = CDateTime::getCurrentTime();
	CDateTime preTime((time_t)shop->m_refreshTime);
	

	BSLib::int64 delta = curTime.getSeconds() - preTime.getSeconds();
	if( delta < 0)
		return 0;
	
	BSLib::uint64 diff = delta;
	BSLib::uint64 period = shopConfig->m_refreshPeriod * 60;
	return  diff >= period ? 0 : (period - diff);
}

void CRoleShopModule::_onMsgShopSystemGC2GMReqShopBuy(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgShopSystemGC2GMReqShopBuy *req = (CMsgShopSystemGC2GMReqShopBuy *)a_msg;

	CMsgShopSystemGM2GCAckShopBuy ack;
	ack.m_type = req->m_type;
	ack.m_id = req->m_id;
	ack.m_result = _shopBuy(req->m_type, req->m_id, req->m_num, ack.m_num);
	sendMsgToClient(ack);
}

void CRoleShopModule::_onMsgShopSystemGC2GMReqShopRefresh(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgShopSystemGC2GMReqShopRefresh *req = (CMsgShopSystemGC2GMReqShopRefresh *)a_msg;

	CMsgShopSystemGM2GCAckShopRefresh ack;
	ack.m_type = req->m_type;
	if( _shopCheckRefreshConditon(req->m_type)){
		ack.m_result =  _shopRefresh(req->m_type, ack.m_ids, ack.m_nums, ack.m_refreshTime);
	}
	ack.m_refreshTime = _shopGetLeftRefreshTime(ack.m_type);
	
	sendMsgToClient(ack);
}

void CRoleShopModule::_onMsgShopSystemGC2GMReqShopPaidRefresh(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgShopSystemGC2GMReqShopPaidRefresh *req = (CMsgShopSystemGC2GMReqShopPaidRefresh *)a_msg;


	CMsgShopSystemGM2GCAckShopPaidRefresh ack;
	ack.m_type = req->m_type;
	ack.m_result = _shopPaidRefresh(req->m_type, ack.m_ids, ack.m_nums);

	sendMsgToClient(ack);
}

DB::SRoleShopData* CRoleShopModule::_shopGetShopData(EShopType a_shopType)
{
	std::map<EShopType , DB::SRoleShopData *>::iterator it = m_shops.find(a_shopType);
	if( it == m_shops.end()){
		return NULL;
	}
	
	return it->second;
}


bool CRoleShopModule::_dbUpdateShop(DB::SRoleShopData* shop)
{
	BSLib::Utility::CStream dbStream;
	shop->serializeTo(dbStream);
	if(m_tablePtr == NULL){
		return false;
	}

	m_tablePtr->update(shop->getDBKey(), shop->getIndex(), dbStream);
	m_tablePtr->saveDataToDBServer(shop->getDBKey(), shop->getIndex(), true);
	return true;
}

bool CRoleShopModule::_dbUpudateBought(EShopType a_shopType, BSLib::int32 a_itemId, BSLib::int32 a_itemNum)
{
	DB::SRoleShopData* shop = _shopGetShopData(a_shopType);
	if(NULL == shop){
		return false;
	}
	
	// 无记录
	if(std::find(shop->m_boughtIds.begin(), shop->m_boughtIds.end(), a_itemId)
		== shop->m_boughtIds.end()){
		shop->m_boughtIds.push_back(a_itemId);
		shop->m_boughtNums.push_back(a_itemNum);
		_dbUpdateShop(shop);
		return true;
	}
	
	// 已存在
	for(BSLib::uint32 i = 0; i < shop->m_boughtIds.size(); i++){
		if( a_itemId == shop->m_boughtIds[i]){
			BSLib::int32 &oldNum = shop->m_boughtNums[i];
			oldNum += a_itemNum;
			_dbUpdateShop(shop);
			return true;
		}
	}

	return false;
}

bool CRoleShopModule::_shopOpen(EShopType a_shopType, ShopSystemAllItemsInfo& a_info, BSLib::uint64& a_timestamp)
{	
	std::map<EShopType , DB::SRoleShopData *>::iterator it = m_shops.find(a_shopType);
	if( it == m_shops.end())
		return false;

	DB::SRoleShopData *shop = it->second;
	for(std::vector<BSLib::int32>::iterator it = shop->m_refreshIds.begin();
		it != shop->m_refreshIds.end(); ++it)
	{	
		SShopItemInfo *info = NULL;
		if( !CShopSystemGM::singleton().getConfig().getShopItem(a_shopType, *it, info))
			continue;
		
		::GSLib::ShopSystem::ShopSystemItemInfo itemInfo;
		itemInfo.id = info->m_id;
		itemInfo.type = info->m_itemType;
		itemInfo.item_id = info->m_itemId;
		itemInfo.item_num = _shopGetLeft(a_shopType, info->m_id);
		itemInfo.pay_type = info->m_payType;
		itemInfo.pay_num = info->m_price;
		a_info.info.push_back(itemInfo);
	}

	a_timestamp = shop->m_refreshTime;

	return true;
}

bool CRoleShopModule::_pay(BSLib::int32 type, BSLib::int32 price)
{	
	if(0 == type)
		return true;

	using namespace PlayerSystem::GM;
	CRoleGM* role = getRoleGM();
	CRoleBagModuleGM* bagM = (CRoleBagModuleGM*)role->getPlayerModuleGM(EMODULECTYPE_BAG);
	EUseResult result = bagM->useItem(ItemSystem::GM::CPrizeItem(type, ItemSystem::GM::EITEM_TP_IVALID, price));
	return result == EUSEITEM_SUCCESS; 
}

EShopSystemResult CRoleShopModule::_shopBuy(EShopType a_shopType, BSLib::int32 a_id, BSLib::int32 a_num, BSLib::int32& a_left)
{	
	BSLib::int32 leftTime = _shopGetLeft(a_shopType, a_id);
	if( 0 == leftTime){
		return ESHOPSYSTEMRESULT_FAILED;
	}
	
	if( leftTime > 0 && leftTime < a_num){
		return ESHOPSYSTEMRESULT_FAILED;
	}

	SShopItemInfo *shopItem = NULL;
	if( !CShopSystemGM::singleton().getConfig().getShopItem(a_shopType, a_id, shopItem)){
		return ESHOPSYSTEMRESULT_FAILED;
	}

	BSLib::int32 price = shopItem->m_price * a_num;
	price *= shopItem->m_discount;
	price /= 100;
	
	//todo 玩家的vip等级待修改..
	BSLib::int32 shopDiscount =  CShopSystemGM::singleton().getConfig().getDiscount(a_shopType, 0);
	price *= shopDiscount;
	price /= 100;
	if( !_pay(shopItem->m_payType, price)){
		return ESHOPSYSTEMRESULT_FAILED;
	}
	
	// 发放物品
	PlayerSystem::GM::CRoleGM* role = getRoleGM();
	PrizeSystem::GM::CRolePrizeModule* prizeModule =  (PrizeSystem::GM::CRolePrizeModule*)role->getPlayerModuleGM(EMODULECTYPE_PRIZE);
	prizeModule->prizeRequestToBag(ItemSystem::GM::CPrizeItem(shopItem->m_itemId, ItemSystem::GM::EITEM_TP_IVALID, shopItem->m_itemNum * a_num), true, "shop");

	// 只保存有数量限制的
	if( -1 != leftTime){
		_dbUpudateBought(a_shopType, a_id, a_num);
	}

	
	a_left = _shopGetLeft(a_shopType, a_id);
	
	return ESHOPSYSTEMRESULT_SUCCESS;
}

EShopSystemResult CRoleShopModule::_shopPaidRefresh(EShopType a_shopType, std::vector<BSLib::int32>& a_ids, std::vector<BSLib::int32>& a_nums)
{
	DB::SRoleShopData* shop = _shopGetShopData(a_shopType);
	if(NULL == shop){
		return ESHOPSYSTEMRESULT_FAILED;
	}

	std::vector<BSLib::int32> outputIds;
	if(ESHOPTYPE_PVP != a_shopType){
		return ESHOPSYSTEMRESULT_FAILED;
	}
	
	SShopConfigInfo *shopConfig = NULL;
	if( !CShopSystemGM::singleton().getConfig().getShopConfig(a_shopType, shopConfig)){
		return ESHOPSYSTEMRESULT_FAILED;
	}

	if( 0 == shopConfig->m_manualRefresh){
		return ESHOPSYSTEMRESULT_FAILED;
	}
	
	// 请付费
	BSLib::int32 price = shopConfig->m_price;
	if( !_pay(shopConfig->m_payType, price)){
		return ESHOPSYSTEMRESULT_FAILED;
	}

	shop->m_paidRefreshCount++;
	if( !CShopSystemGM::singleton().getConfig().getPVPShopShowItem(a_shopType, true, shop->m_paidRefreshCount, outputIds)){
		return ESHOPSYSTEMRESULT_FAILED;
	}

	shop->m_refreshIds = outputIds;
	shop->m_boughtIds.clear();
	shop->m_boughtNums.clear();
	_dbUpdateShop(shop);

	a_ids = shop->m_refreshIds;
	for(BSLib::uint32 i = 0; i < a_ids.size(); i++){
		a_nums.push_back(_shopGetLeft(a_shopType, a_ids[i]));
	}

	return ESHOPSYSTEMRESULT_SUCCESS;
}

BSLib::int32 CRoleShopModule::_shopGetLeft(EShopType a_shopType, BSLib::int32 a_id)
{
	SShopItemInfo *shopItem = NULL;
	if( !CShopSystemGM::singleton().getConfig().getShopItem(a_shopType, a_id, shopItem)){
		return -1;
	}

	if( shopItem->m_limitNum > 0){
		return shopItem->m_limitNum - _shopGetbought(a_shopType, a_id);
	}
	
	return -1;
}

BSLib::int32 CRoleShopModule::_shopGetbought(EShopType a_shopType, BSLib::int32 a_id)
{	
	DB::SRoleShopData* dbShop = _shopGetShopData(a_shopType);
	if(NULL == dbShop){
		return 0;
	}
	
	for(BSLib::uint32 i = 0; i < dbShop->m_boughtIds.size(); i++){
		if( a_id == dbShop->m_boughtIds[i]){
			return dbShop->m_boughtNums[i];
		}
	}
	
	return 0;
}
bool CRoleShopModule::_timeIsSameDay(BSLib::uint64 a_timeStamp)
{	
	using namespace  BSLib::Utility;
	CDateTime curTime = CDateTime::getCurrentTime();
	CDateTime preTime((time_t)a_timeStamp);

	return curTime.getYear() == preTime.getYear() 
		&& curTime.getMonth() == preTime.getMonth() 
		&& curTime.getDay() == preTime.getDay(); 
}

bool CRoleShopModule::_timeIsSameMonth(BSLib::uint64 a_timeStamp)
{
	using namespace  BSLib::Utility;
	CDateTime curTime = CDateTime::getCurrentTime();
	CDateTime preTime((time_t)a_timeStamp);

	return curTime.getYear() == preTime.getYear() 
		&& curTime.getMonth() == preTime.getMonth();
}

BSLib::int64 CRoleShopModule::_timeDiff(BSLib::int64 a_timeStamp)
{
	using namespace  BSLib::Utility;
	CDateTime curTime = CDateTime::getCurrentTime();
	CDateTime preTime((time_t)a_timeStamp);
	
	BSLib::int64 delta = curTime.getSeconds() - preTime.getSeconds();
	return delta / 60;
}

bool CRoleShopModule::_shopInit()
{	
	PlayerSystem::GM::CRoleGM* role = getRoleGM();
	for(BSLib::uint32 i = ESHOPTYPE_PROP; i <= ESHOPTYPE_DAILY; i++){
		DB::SRoleShopData * newShop = new DB::SRoleShopData(role->getRoleKey());
		newShop->m_shopType = i;
		m_shops.insert(std::make_pair((EShopType)i, newShop));
		std::vector<BSLib::int32> dummyIds;
		std::vector<BSLib::int32> dummyNums;
		BSLib::uint64 dummyTime = 0;
		_shopRefresh((EShopType)i, dummyIds, dummyNums, dummyTime);
	}

	return true;
}

bool CRoleShopModule::_shopCheckRefreshConditon(EShopType a_shopType)
{
	DB::SRoleShopData* shop = _shopGetShopData(a_shopType);
	if( NULL == shop)
		return false;

	
	SShopConfigInfo* shopConfig = NULL;
	if( !CShopSystemGM::singleton().getConfig().getShopConfig(a_shopType, shopConfig)){
		return false;
	}
	
	if( 0 == shopConfig->m_refreshPeriod){
		return false;
	}
	else if( ONE_DAY == shopConfig->m_refreshPeriod){
		return !_timeIsSameDay(shop->m_refreshTime);
	}
	else{
		return _timeDiff(shop->m_refreshTime) >= shopConfig->m_refreshPeriod;
	}
	
	return false;
}

EShopSystemResult CRoleShopModule::_shopRefresh(EShopType a_shopType, std::vector<BSLib::int32>& a_ids, std::vector<BSLib::int32>& a_nums, BSLib::uint64& a_timestamp)
{	

	DB::SRoleShopData* shop = _shopGetShopData(a_shopType);
	if(NULL == shop){
		return ESHOPSYSTEMRESULT_FAILED;
	}

	std::vector<BSLib::int32> outputIds;
	if(ESHOPTYPE_PVP == a_shopType){
		if( !CShopSystemGM::singleton().getConfig().getPVPShopShowItem(a_shopType, false, shop->m_paidRefreshCount, outputIds)){
			return ESHOPSYSTEMRESULT_FAILED;
		}
	}
	else{
		if( !CShopSystemGM::singleton().getConfig().getShopShowItem(a_shopType, outputIds)){
			return ESHOPSYSTEMRESULT_FAILED;
		}
	}

	shop->m_refreshIds = outputIds;
	shop->m_boughtIds.clear();
	shop->m_boughtNums.clear();
	BSLib::Utility::CDateTime now = BSLib::Utility::CDateTime::getCurrentTime();
	shop->m_refreshTime = now.getSeconds();
	_dbUpdateShop(shop);
	
	a_ids = shop->m_refreshIds;
	for(BSLib::uint32 i = 0; i < a_ids.size(); i++){
		a_nums.push_back(_shopGetLeft(a_shopType, a_ids[i]));
	}
	a_timestamp = shop->m_refreshTime;

	return ESHOPSYSTEMRESULT_SUCCESS;
}

void CRoleShopModule::_onMsgShopSystemGC2GMReqOpenCard(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{	
	CMsgShopSystemGC2GMReqOpenCard *req = (CMsgShopSystemGC2GMReqOpenCard *)a_msg;
	CMsgShopSystemGM2GCAckOpenCard ack;
	ack.fun_type = req->fun_type;
	_getCardInfo(ack.fun_type, ack);
	sendMsgToClient(ack);
}

void CRoleShopModule::_getCardInfo(BSLib::uint32 a_funType, CMsgShopSystemGM2GCAckOpenCard& ack)
{	
	PlayerSystem::GM::CRoleGM* role = getRoleGM();
	PrizeSystem::GM::CRolePrizeModule* prizeModule =  (PrizeSystem::GM::CRolePrizeModule*)role->getPlayerModuleGM(EMODULECTYPE_PRIZE);
	
	BSLib::uint32 gold1 = GUANGZILI_GOLD1_RECORD;
	BSLib::uint32 diamond1 = GUANGZILI_DIAMOND1_RECROD;
	if( 1 == a_funType)
	{
		gold1 = FRIEND_GOLD1_RECORD;
		diamond1 = FRIEND_DIAMOND1_RECORD;
	}

	SCardConfigInfo * info = NULL;
	{	
		CShopSystemGM::singleton().getCardConfig().getShopConfig(a_funType, info);
		{	
			ack.glod1_free = info->m_free_gold - prizeModule->prizeNum(gold1);
			if(prizeModule->prizeIsValid(gold1))
			{	
				if(prizeModule->_prizeGetTimeStamp(gold1) + info->m_free_gold_cd <= prizeModule->_timeGetCurrentStamp())
				{	// 在cd内
					ack.gold1_next_cost = 0;
					ack.gold1_next_secs = 0;
				}
				else
				{	// 不在cd内
					ack.gold1_next_cost = info->m_gold1_cost;
					BSLib::uint64 left = info->m_free_gold_cd;
					left += prizeModule->_prizeGetTimeStamp(gold1);
					left -= prizeModule->_timeGetCurrentStamp();
					ack.gold1_next_secs = left;
				}
				
			}
			else
			{	// 没有免费次数了
				ack.gold1_next_cost = info->m_gold1_cost;
				ack.gold1_next_secs = 0; //??? 这个值无效了,假如需要花钱的话
			}
		}

		ack.gold10_next_cost = info->m_gold10_cost;

		{	
			ack.diamond1_free = info->m_free_diamond - prizeModule->prizeNum(diamond1);
			if(prizeModule->prizeIsValid(diamond1))
			{	
				if(prizeModule->_prizeGetTimeStamp(diamond1) +  info->m_free_diamond_cd <= prizeModule->_timeGetCurrentStamp())
				{
					ack.diamond1_next_cost = 0;
					ack.diamond1_next_secs = 0;
				}
				else
				{
					ack.diamond1_next_cost = info->m_diamond1_cost;

					BSLib::uint64 left = info->m_free_gold_cd;
					left += prizeModule->_prizeGetTimeStamp(diamond1);
					left -= prizeModule->_timeGetCurrentStamp();
					ack.diamond1_next_secs = left;
				}
				
			}
			else
			{
				ack.diamond1_next_cost = info->m_diamond1_cost;
			}
		}
		
		ack.diamond10_next_cost = info->m_diamond10_cost;

	}

}

void CRoleShopModule::_onMsgShopSystemGC2GMReqEventState(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgShopSystemGC2GMReqEventState* req = (CMsgShopSystemGC2GMReqEventState *)a_msg;

	CMsgShopSystemGM2GCAckEventState ack;
	ack.update_type = 1;
	
	PlayerSystem::GM::CRoleGM* role = getRoleGM();
	PrizeSystem::GM::CRolePrizeModule* prizeModule =  (PrizeSystem::GM::CRolePrizeModule*)role->getPlayerModuleGM(EMODULECTYPE_PRIZE);
	std::vector<PrizeSystem::GM::StateMachineSt> st;
	if(prizeModule->_getCardState(GUANGZILI_EVENT, st))
	{
		for(std::vector<PrizeSystem::GM::StateMachineSt>::iterator it = st.begin();
			it != st.end(); ++it)
		{
			ack.event_names.push_back(it->type);
		}
	}
		
	sendMsgToClient(ack);
}

void CRoleShopModule::_doEvent(BSLib::int32 a_eventId)
{	
	CMsgShopSystemGM2GCAckEventState ack;
	ack.update_type = 2;
	ack.event_names.push_back(a_eventId);
	_updateEvent(GUANGZILI_EVENT, a_eventId);
	BSLib::uint32 itemId = 0;
	if( _eventIsFull(GUANGZILI_EVENT))
	{
		ack.triggered = 1;
		CShopSystemGM::singleton().getCardConfig().getTriggerItem(itemId);
		ack.item_id = itemId;
		PlayerSystem::GM::CRoleGM* role = getRoleGM();
		PrizeSystem::GM::CRolePrizeModule* prizeModule =  (PrizeSystem::GM::CRolePrizeModule*)role->getPlayerModuleGM(EMODULECTYPE_PRIZE);
		prizeModule->prizeRequestToBag(ItemSystem::GM::CPrizeItem(itemId, ItemSystem::GM::EITEM_TP_IVALID, 1), false, "shop");
		_updateEvent(GUANGZILI_EVENT, 0); //重置
	}

	sendMsgToClient(ack);
}

bool CRoleShopModule::_eventIsFull(BSLib::int32 a_prizeId)
{
	PlayerSystem::GM::CRoleGM* role = getRoleGM();
	PrizeSystem::GM::CRolePrizeModule* prizeModule =  (PrizeSystem::GM::CRolePrizeModule*)role->getPlayerModuleGM(EMODULECTYPE_PRIZE);
	std::vector<PrizeSystem::GM::StateMachineSt> st;
	if( !prizeModule->_getCardState(a_prizeId, st))
		return false;
	
	SCardConfigInfo *info = NULL;
	CShopSystemGM::singleton().getCardConfig().getConfig(eCardSumTypeGuangZiLi, info);
	return st.size() == info->m_event_names.size();
}

bool CRoleShopModule::_updateEvent(BSLib::int32 a_prizeId, BSLib::uint32 a_eventId)
{
	PlayerSystem::GM::CRoleGM* role = getRoleGM();
	PrizeSystem::GM::CRolePrizeModule* prizeModule =  (PrizeSystem::GM::CRolePrizeModule*)role->getPlayerModuleGM(EMODULECTYPE_PRIZE);
	std::vector<PrizeSystem::GM::StateMachineSt> st;
	if( 0 == a_eventId) // 重置
	{
		return prizeModule->_setCardState(a_prizeId, st);
	}


	prizeModule->_getCardState(a_prizeId, st);

	
	for (std::vector<PrizeSystem::GM::StateMachineSt>::iterator it = st.begin(); it != st.end(); ++it)
	{
		if( a_eventId != it->type)
			continue;

		if( 1 != it->value)
			it->value = 1;

		return true;
	}

	PrizeSystem::GM::StateMachineSt newState;
	newState.type = a_prizeId;
	newState.value = 1;
	st.push_back(newState);
	return prizeModule->_setCardState(a_prizeId, st);
}

void CRoleShopModule::_onMsgShopSystemGC2GMReqClick(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{	
	PlayerSystem::GM::CRoleGM* role = getRoleGM();
	PrizeSystem::GM::CRolePrizeModule* prizeModule =  (PrizeSystem::GM::CRolePrizeModule*)role->getPlayerModuleGM(EMODULECTYPE_PRIZE);

	CMsgShopSystemGC2GMReqClick *req = (CMsgShopSystemGC2GMReqClick *)a_msg;
	CMsgShopSystemGM2GCAckClick ack;
	ack.fun_type = req->fun_type;
	ack.cost_type = req->cost_type;
	ack.result = 2;
	// 1. check times conditon
	// 2. roll
	// 3. reduct cost
	// 4. reply msg;
	// 5. update event
	// 6. update prize
	do 
	{
		BSLib::uint32 itemId = 0;
		BSLib::uint32 itemNum = 0;
		if( !_checkCardCondition(req->fun_type, req->cost_type, itemId, itemNum))
			break;

		BSLib::uint32 eventId = 0;
		_rollCard(req->fun_type, req->cost_type, ack.item_ids, ack.item_nums, eventId);

		if( !_pay(itemId, itemNum))
			break;
		
		std::vector<ItemSystem::GM::CPrizeItem> items;
		for(BSLib::uint32 i = 0; i < ack.item_ids.size(); i++)
		{
			ItemSystem::GM::CPrizeItem item(ack.item_ids[i], GSLib::ItemSystem::GM::EITEM_TP_IVALID, ack.item_nums[i]);
			items.push_back(item);
		}
		BSLib::uint32 prizeId = _getCardTypeId(req->fun_type, req->cost_type);
		if( 0 != prizeId)
		{
			prizeModule->prizeRequest(prizeId, items, "", "", "", "shop");
		}
		else
		{
			prizeModule->prizeRequestToBag(items, false, "shop");
		}

		ack.result = 1;
		// 成功返回
		sendMsgToClient(ack);

		CMsgShopSystemGM2GCAckOpenCard openAck;
		openAck.fun_type = req->fun_type;
		_getCardInfo(req->fun_type, openAck);
		sendMsgToClient(openAck);


		if( 0 != eventId)
		{
			_doEvent(eventId);
		}
		
		return; // 返回了

	} while (false);


	// 失败返回
	sendMsgToClient(ack);
}



bool CRoleShopModule::_rollCard(BSLib::uint32 a_funType, BSLib::uint32 a_costType,
								std::vector< BSLib::uint32>& a_itemIds, std::vector< BSLib::uint32>& a_ItemNums, BSLib::uint32& a_eventId)
{
	BSLib::uint32 eventId = 0;
	switch (a_funType)
	{
	case eCardSumTypeFriend:
		{
			switch(a_costType)
			{
			case 1: // 金币单抽
				CShopSystemGM::singleton().getCardConfig().oneClick(eCardTypeFriendGold, a_itemIds, a_ItemNums);
				break;

			case 2: // 金币10连抽
				CShopSystemGM::singleton().getCardConfig().tenClick(eCardTypeFriendGold, a_itemIds, a_ItemNums, a_eventId);
				break;

			case 3: // 钻石单抽
				CShopSystemGM::singleton().getCardConfig().oneClick(eCardTypeFriendDiamond, a_itemIds, a_ItemNums);
				break;

			case 4: // 钻石10连抽
				CShopSystemGM::singleton().getCardConfig().tenClick(eCardTypeFriendDiamond, a_itemIds, a_ItemNums, a_eventId);
				break;
			}
		}
		break;

	case eCardSumTypeGuangZiLi:
		{
			switch(a_costType)
			{
			case 1: // 金币单抽
				CShopSystemGM::singleton().getCardConfig().oneClick(eCardTypeGuangZiLiGold, a_itemIds, a_ItemNums);
				break;

			case 2: // 金币10连抽
				CShopSystemGM::singleton().getCardConfig().tenClick(eCardTypeGuangZiLiGold, a_itemIds, a_ItemNums, a_eventId);
				break;

			case 3: // 钻石单抽
				CShopSystemGM::singleton().getCardConfig().oneClick(eCardTypeGuangZiLiDiamond, a_itemIds, a_ItemNums);
				break;

			case 4: // 钻石10连抽
				CShopSystemGM::singleton().getCardConfig().tenClick(eCardTypeGuangZiLiDiamond, a_itemIds, a_ItemNums, a_eventId);
				break;
			}
		}
		break;
	}

	return true;
}

BSLib::uint32 CRoleShopModule::_getCardTypeId(BSLib::uint32 a_funType, BSLib::uint32 a_costType)
{	

	PlayerSystem::GM::CRoleGM* role = getRoleGM();
	PrizeSystem::GM::CRolePrizeModule* prizeModule =  (PrizeSystem::GM::CRolePrizeModule*)role->getPlayerModuleGM(EMODULECTYPE_PRIZE);

	SCardConfigInfo * info = NULL;
	if( !CShopSystemGM::singleton().getCardConfig().getShopConfig(a_funType, info))
		return 0;

	switch(a_funType)
	{
	case eCardSumTypeFriend:
		{
			switch(a_costType)
			{
			case 1: // 金币单抽
				{
					if(prizeModule->prizeIsValid(FRIEND_GOLD1_RECORD)
						&& prizeModule->_prizeGetTimeStamp(FRIEND_GOLD1_RECORD) + info->m_free_gold_cd <= prizeModule->_timeGetCurrentStamp())
					{
						return FRIEND_GOLD1_RECORD;
					}
					else
					{
						
					}
				}
				break; 

			case 2: // 金币10抽

				break;

			case 3:	// 钻石单抽
				{
					if(prizeModule->prizeIsValid(FRIEND_DIAMOND1_RECORD)
						&& prizeModule->_prizeGetTimeStamp(FRIEND_DIAMOND1_RECORD) + info->m_free_diamond_cd <= prizeModule->_timeGetCurrentStamp())
					{
						return FRIEND_DIAMOND1_RECORD;
					}
					else
					{
					}
				}
				break;

			case 4:	// 钻石10抽
				break;
			}

		}
		break;

	case eCardSumTypeGuangZiLi:
		{
			switch(a_costType)
			{
			case 1: // 金币单抽
				{
					if(prizeModule->prizeIsValid(GUANGZILI_GOLD1_RECORD)
						&& prizeModule->_prizeGetTimeStamp(GUANGZILI_GOLD1_RECORD) + info->m_free_gold_cd <= prizeModule->_timeGetCurrentStamp())
					{
						return GUANGZILI_GOLD1_RECORD;
					}
					else
					{
					}
				}
				break; 

			case 2: // 金币10抽
				break;

			case 3:	// 钻石单抽
				{
					if(prizeModule->prizeIsValid(GUANGZILI_DIAMOND1_RECROD)
						&& prizeModule->_prizeGetTimeStamp(GUANGZILI_DIAMOND1_RECROD) + info->m_free_diamond_cd <= prizeModule->_timeGetCurrentStamp())
					{
						return GUANGZILI_DIAMOND1_RECROD;
					}
					else
					{

					}
				}
				break;

			case 4:	// 钻石10抽
				break;
			}

		}
		break;

	}

	return 0;
}

bool CRoleShopModule::_checkCardCondition(BSLib::uint32 a_funType, BSLib::uint32 a_costType, BSLib::uint32& a_itemId, BSLib::uint32& a_itemNum)
{	
	SCardConfigInfo * info = NULL;
	if( !CShopSystemGM::singleton().getCardConfig().getShopConfig(a_funType, info))
		return false;
	
	PlayerSystem::GM::CRoleGM* role = getRoleGM();
	PrizeSystem::GM::CRolePrizeModule* prizeModule =  (PrizeSystem::GM::CRolePrizeModule*)role->getPlayerModuleGM(EMODULECTYPE_PRIZE);
	switch(a_funType)
	{
	case eCardSumTypeFriend:
		{	

			switch(a_costType)
			{
			case 1: // 金币单抽
				{
					if(prizeModule->prizeIsValid(FRIEND_GOLD1_RECORD)
						&& prizeModule->_prizeGetTimeStamp(FRIEND_GOLD1_RECORD) + info->m_free_gold_cd  <= prizeModule->_timeGetCurrentStamp())
					{
						a_itemId = 0;
						a_itemNum = 0;
					}
					else
					{
						a_itemId = 101;
						a_itemNum = info->m_gold1_cost;
					}
				}
				break; 

			case 2: // 金币10抽
				a_itemId = 101;
				a_itemNum = info->m_gold10_cost;
				break;

			case 3:	// 钻石单抽
				{
					if(prizeModule->prizeIsValid(FRIEND_DIAMOND1_RECORD)
						&& prizeModule->_prizeGetTimeStamp(FRIEND_DIAMOND1_RECORD) + info->m_free_diamond_cd <= prizeModule->_timeGetCurrentStamp())
					{
						a_itemId = 0;
						a_itemNum = 0;
					}
					else
					{
						a_itemId = 102;
						a_itemNum = info->m_diamond1_cost;
					}
				}
				break;

			case 4:	// 钻石10抽
				a_itemId = 102;
				a_itemNum = info->m_diamond10_cost;
				break;
			}

		}
		break;

	case eCardSumTypeGuangZiLi:
		{	
			BSLib::uint32 cd = info->m_free_gold_cd ;
			switch(a_costType)
			{
			case 1: // 金币单抽
				{
					if(prizeModule->prizeIsValid(GUANGZILI_GOLD1_RECORD)
						&& prizeModule->_prizeGetTimeStamp(GUANGZILI_GOLD1_RECORD) + info->m_free_gold_cd <= prizeModule->_timeGetCurrentStamp())
					{
						a_itemId = 0;
						a_itemNum = 0;
					}
					else
					{
						a_itemId = 101;
						a_itemNum = info->m_gold1_cost;
					}
				}
				break; 

			case 2: // 金币10抽
				a_itemId = 101;
				a_itemNum = info->m_gold10_cost;
				break;

			case 3:	// 钻石单抽
				{
					if(prizeModule->prizeIsValid(GUANGZILI_DIAMOND1_RECROD)
						&& prizeModule->_prizeGetTimeStamp(GUANGZILI_DIAMOND1_RECROD) + info->m_free_diamond_cd <= prizeModule->_timeGetCurrentStamp())
					{
						a_itemId = 0;
						a_itemNum = 0;
					}
					else
					{
						a_itemId = 102;
						a_itemNum = info->m_diamond1_cost;
					}
				}
				break;

			case 4:	// 钻石10抽
				a_itemId = 102;
				a_itemNum = info->m_diamond10_cost;
				break;
			}

		}
		break;

	}

	return true;
}




}//GM

}

}//GSLib