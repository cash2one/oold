#include <GSLib/prizeSystem/GM/rolePrizeModule.h>
#include <GSLib/tracer.h>
#include <GSLib/mailSystem/GM/mailSystemGM.h>
#include <GSLib/mailSystem/GM/roleMailModule.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/mailSystem/mail.h>
#include <GSLib/playerSystem/GM/roleBagModuleGM.h>
#include <GSLib/prizeSystem/lexical.h>

#define		CHARGE_ERCORD_BASE_ID	100
#define		CHARGE_PRIZE_BASE_ID	200
#define		CHARGE_EVENT_5			220

namespace GSLib
{

namespace PrizeSystem
{

namespace GM
{

CRolePrizeModule::CRolePrizeModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType)
:  GSLib::PlayerSystem::GM::CRoleModuleGM(a_roleGM, a_moduleType)
{
	;
}

CRolePrizeModule::~CRolePrizeModule()
{
	;
}

void CRolePrizeModule::preInit(bool isFirst)
{
	;
}

void CRolePrizeModule::postInit(bool isFirst)
{	
	if( !isFirst)
		return;

	for(BSLib::uint32 i = CHARGE_PRIZE_BASE_ID + 3; i <= CHARGE_PRIZE_BASE_ID + 8; i++)
	{
		_prizeOnlyReg(i);
	}
}

void CRolePrizeModule::initToClient()
{	
	// 测试
#ifdef  BIANJIANTEST1
		bool success = true;
		for(int i = 1; i <= 20; i++){
			//success = PrizeIsValid(i) && success;
			success = prizeRequest(2, "sender", "title", "content");
			if(success){
				BSLIB_LOG_DEBUG(ETT_GSLIB_PRIZESYSTEM, "prize 发送通过%d", i);
			}
			else{
				BSLIB_LOG_DEBUG(ETT_GSLIB_PRIZESYSTEM, "prize 发送失败%d", i);
			}
		}

		
#endif
		
		BSLib::uint32 totalNUm = 0;
		for(BSLib::uint32 i = CHARGE_ERCORD_BASE_ID + 3; i <= CHARGE_ERCORD_BASE_ID + 8; i++)
		{
			totalNUm += prizeNum(i);
		}
	
		if( 1 == totalNUm)
		{	// 发送卡牌通知
			if(prizeIsValid(CHARGE_EVENT_5))
			{
				CMsgPrizeSystemGM2GCNtfCharge ack;
				ack.id = CHARGE_EVENT_5;
				BSLib::Utility::CDateTime now = BSLib::Utility::CDateTime::getCurrentTime();
				ack.time = now.getSeconds();
				sendMsgToClient(ack);
			}
		}
		
		// 周卡 ,月卡工资
		if(_prizeIsExist(201))
		{
			for(; true == prizeRequest(201, "activity"); );
		}

		if(_prizeIsExist(202))
		{
			for(; true == prizeRequest(202, "activity"); );
		}
		
}

void CRolePrizeModule::final()
{
	;
}

void CRolePrizeModule::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{	
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDCMsgPrizeSystemGC2GMReqState, &BSLib::Framework::CreateCMessage<CMsgPrizeSystemGC2GMReqState>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDCMsgPrizeSystemGC2GMReqState, &CRolePrizeModule::_onMsgPrizeSystemGC2GMReqState, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDCMsgPrizeSystemGC2GMReq, &BSLib::Framework::CreateCMessage<CMsgPrizeSystemGC2GMReq>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDCMsgPrizeSystemGC2GMReq, &CRolePrizeModule::_onMsgPrizeSystemGC2GMReq, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDCMsgPrizeSystemGC2GMReqTime, &BSLib::Framework::CreateCMessage<CMsgPrizeSystemGC2GMReqTime>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDCMsgPrizeSystemGC2GMReqTime, &CRolePrizeModule::_onMsgPrizeSystemGC2GMReqTime, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDCMsgPrizeSystemGC2GMReqChargeInfo, &BSLib::Framework::CreateCMessage<CMsgPrizeSystemGC2GMReqChargeInfo>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDCMsgPrizeSystemGC2GMReqChargeInfo, &CRolePrizeModule::_onMsgPrizeSystemGC2GMReqChargeInfo, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDCMsgPrizeSystemGC2GMNtfAction, &BSLib::Framework::CreateCMessage<CMsgPrizeSystemGC2GMNtfAction>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDCMsgPrizeSystemGC2GMNtfAction, &CRolePrizeModule::_onMsgPrizeSystemGC2GMNtfAction, this);
	;
}

void CRolePrizeModule::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	a_msgExecMgr->delMsgExecPtr(msgIDCMsgPrizeSystemGC2GMReqState);
	a_msgExecMgr->delMsgExecPtr(msgIDCMsgPrizeSystemGC2GMReq);
	a_msgExecMgr->delMsgExecPtr(msgIDCMsgPrizeSystemGC2GMReqTime);
	a_msgExecMgr->delMsgExecPtr(msgIDCMsgPrizeSystemGC2GMReqChargeInfo);
	a_msgExecMgr->delMsgExecPtr(msgIDCMsgPrizeSystemGC2GMNtfAction);
	;
}

void CRolePrizeModule::_onMsgPrizeSystemGC2GMNtfAction(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	_prizeReg(CHARGE_EVENT_5, _timeGetCurrentStamp());
}

void CRolePrizeModule::updateDataToDB()
{
	;
}

bool CRolePrizeModule::exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value)
{	
	BSLib::Utility::CStream stream;
	a_value->serializeTo(stream);
	
	DB::SRolePrizeData *prize = new DB::SRolePrizeData;
	prize->serializeFrom(stream);
	m_prizesMap.insert(std::make_pair(prize->m_prizeID, prize));
	return true;
}

bool CRolePrizeModule::cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{	
	if( a_tableID == EDBABLEID_ROLE_PRIZE_DATA){
		m_tablePtr = a_keyTable;
		m_tablePtr->traversal(*this);
	}

	return true;
}

bool CRolePrizeModule::_prizeNolimitIsValid(SPrizeItemInfo *info)
{
	return _prizeIsInPeriodOfValidity(info);
}

bool CRolePrizeModule::_prizeOnceIsValid(SPrizeItemInfo *info)
{	
	// 已过期
	if(!_prizeIsInPeriodOfValidity(info)){
		// 清理
		if(_prizeIsExist(info->m_id)){
			_prizeDel(info->m_id);
		}

		return false;
	}
	
	return !_prizeIsExist(info->m_id);
}

bool CRolePrizeModule::_prizeDayAcclyIsValid(SPrizeItemInfo *info)
{
	// 已过期, 过期的话,先检查有无领取吧
	if(!_prizeIsInPeriodOfValidity(info) && !_prizeDayAccNumIsValid(info->m_id))
	{
		// 清理
		if(_prizeIsExist(info->m_id)){
			_prizeDel(info->m_id);
		}

		return false;
	}

	// 有效期内

	// 没有记录
	if(!_prizeIsExist(info->m_id))
		return true;

	if(_prizeDayAccNumIsValid(info->m_id))
	{
		typedef std::map<BSLib::uint64, DB::SRolePrizeData* > PrizeMap;
		PrizeMap::iterator it = m_prizesMap.find(info->m_id);
		if( it != m_prizesMap.end())
		{
			//BSLib::uint64 delta = _timeGetCurrentStamp() - it->second->m_startTime; // 流逝了多少秒
			BSLib::uint32 dayLeft = it->second->m_startTime % (24 * 60 * 60); // 开始的那天还剩多少秒到24点
			BSLib::uint64 prizePeriod = _timeGetCurrentStamp() - it->second->m_startTime;
			if(prizePeriod > dayLeft)
			{
				BSLib::uint64 numSeconds = prizePeriod - dayLeft;
				BSLib::uint64 couldUseDay = numSeconds / (24 * 60 * 60);
				if(numSeconds % (24 * 60 * 60) )
					couldUseDay += 1;

				if( couldUseDay > it->second->m_num)
					return true;
			}
			
		}
	}
	
	return false;
}

bool CRolePrizeModule::_prizeDaylyIsValid(SPrizeItemInfo *info)
{
	// 已过期
	if(!_prizeIsInPeriodOfValidity(info)){
		// 清理
		if(_prizeIsExist(info->m_id)){
			_prizeDel(info->m_id);
		}

		return false;
	}
	
	// 有效期内

	// 没有记录
	if(!_prizeIsExist(info->m_id))
		return true;

	// 有记录,可刷新了
	if(!_timeIsSameDay(_prizeGetTimeStamp(info->m_id))){
		// 清理
		_prizeDel(info->m_id);
		return true;
	}
	else
	{
		if(_prizeNumIsValid(info->m_id, info->m_limitNum))
			return true;
	}

	return false;
}

bool CRolePrizeModule::_prizeMonthlyIsValid(SPrizeItemInfo *info)
{
	// 已过期
	if(!_prizeIsInPeriodOfValidity(info)){
		// 清理
		if(_prizeIsExist(info->m_id)){
			_prizeDel(info->m_id);
		}

		return false;
	}

	// 有效期内

	// 没有记录
	if(!_prizeIsExist(info->m_id))
		return true;

	// 有记录,可刷新了
	if(!_timeIsSameMonth(_prizeGetTimeStamp(info->m_id))){
		// 清理
		_prizeDel(info->m_id);
		return true;
	}
	else
	{
		if(_prizeNumIsValid(info->m_id, info->m_limitNum))
			return true;
	}

	return false;
}

BSLib::uint64 CRolePrizeModule::_prizeGetTimeStamp(BSLib::uint32 a_prize)
{
	typedef std::map<BSLib::uint64, DB::SRolePrizeData* > UINT64Map;
	UINT64Map::iterator it = m_prizesMap.find(a_prize);
	if( it == m_prizesMap.end())
		return 0;

	return it->second->m_timestamp;
}

bool CRolePrizeModule::_prizeIsNeedReg(BSLib::uint32 a_prize)
{
	SPrizeItemInfo *info = NULL;
	if( !CPrizeConfig::singleton().getPrize(a_prize, info))
		return false;


	switch(info->m_periodType)
	{
	case EPRIZEPERIODTYPE_NOLIMIT:
		return true; // 没有限制的也记录

	case EPRIZEPERIODTYPE_DAYLY:
		return true;

	case EPRIZEPERIODTYPE_MONTHLY:
		return true;

	case EPRIZEPERIODTYPE_ONCE:
		return true;

	case EPRIZEPERIODTYPE_DAYLY_ACC:
		return true;
	}

	return false;
}

bool CRolePrizeModule::_prizeGetParam(BSLib::uint32 a_prize, std::vector<char>& a_buf)
{
	typedef std::map<BSLib::uint64, DB::SRolePrizeData* > PrizeMap;
	PrizeMap::iterator it = m_prizesMap.find(a_prize);
	if( it == m_prizesMap.end())
		return false;

	a_buf = it->second->m_param;
	return true;
}

bool CRolePrizeModule::_prizeSetParam(BSLib::uint32 a_prize, std::vector<char>& a_buf)
{
	typedef std::map<BSLib::uint64, DB::SRolePrizeData* > PrizeMap;
	PrizeMap::iterator it = m_prizesMap.find(a_prize);
	if( it == m_prizesMap.end())
		return false;

	it->second->m_param = a_buf;
	_dbPrizeUpdate(a_prize);
	return true;
}

bool CRolePrizeModule::_getCardState(BSLib::uint32 a_prize, std::vector<StateMachineSt>& a_st)
{
	std::vector<char> sExact;
	if( !_prizeGetParam(a_prize, sExact))
		return false;

	if( sExact.empty())
		return false;
	
	BSLib::Utility::CStream exactStream;
	exactStream.write(&sExact[0], sExact.size());

	BSLib::uint32 size  = 0;
	exactStream >> size;
	for(BSLib::uint32 i = 0; i < size; i++)
	{
		GM::StateMachineSt st;

		exactStream >> st.type;
		exactStream >> st.key;
		exactStream >> st.value;
		a_st.push_back(st);
	}

	return true;
}

bool CRolePrizeModule::_setCardState(BSLib::uint32 a_Prize, std::vector<StateMachineSt>& a_st)
{
	BSLib::Utility::CStream bufExact;
	bufExact << a_st.size();
	std::vector<GM::StateMachineSt>::iterator it = a_st.begin();
	for(; it != a_st.end(); ++it)
	{
		bufExact << it->type;
		bufExact << it->key;
		bufExact << it->value;
	}

	std::vector<char> sExact;
	sExact.resize(bufExact.getWritePosition());
	bufExact.read(&sExact[0], bufExact.getWritePosition());
	return _prizeSetParam(a_Prize, sExact);
}

bool CRolePrizeModule::prizeIsValid(BSLib::uint32 a_prize)
{	
	SPrizeItemInfo *info = NULL;
	if( !CPrizeConfig::singleton().getPrize(a_prize, info))
		return false;

	
	switch(info->m_periodType)
	{
	case EPRIZEPERIODTYPE_NOLIMIT:
		return _prizeNolimitIsValid(info);

	case EPRIZEPERIODTYPE_DAYLY:
		return _prizeDaylyIsValid(info);

	case EPRIZEPERIODTYPE_MONTHLY:
		return _prizeMonthlyIsValid(info);

	case EPRIZEPERIODTYPE_ONCE:
		return _prizeOnceIsValid(info);

	case EPRIZEPERIODTYPE_DAYLY_ACC:
		return _prizeDayAcclyIsValid(info);
	}

	return false;
}

bool CRolePrizeModule::prizeRequestToBag(const std::vector<ItemSystem::GM::CPrizeItem>& a_items, bool forced, std::string a_reason)
{	
	using namespace PlayerSystem::GM;
	CRoleGM* role = getRoleGM();
	CRoleBagModuleGM* bagM = (CRoleBagModuleGM*)role->getPlayerModuleGM(EMODULECTYPE_BAG);
	EAddResult result = bagM->addItem(a_items, forced, true, a_reason);
	return result == EADDITEM_SUCCESS; 
}

BSLib::uint32 CRolePrizeModule::prizeNum(BSLib::uint32 a_prize)
{
	prizeIsValid(a_prize);
	return _prizeNum(a_prize);
}

bool CRolePrizeModule::updatePrizeState(BSLib::uint32 a_prize, int a_type, int a_value)
{
	typedef std::map<BSLib::uint64, DB::SRolePrizeData* > PrizeMap;
	PrizeMap::iterator it = m_prizesMap.find(a_prize);
	if( it == m_prizesMap.end())
		return false;

	std::vector<GM::StateMachineSt>& states = it->second->m_states;
	for(std::vector<GM::StateMachineSt>::iterator smIt = states.begin(); smIt != states.end(); ++smIt)
	{
		GM::StateMachineSt& st = *smIt;
		if( a_type == st.type)
		{
			if( -1 != st.value)
			{
				st.value += a_value;
				if( st.value < 0)
					st.value = 0;
			}

			return true;
		}
	}

	return false;
}

void CRolePrizeModule::chargeUpdate(BSLib::int64 a_chargeID, int a_type, int a_money)
{	
	// 记录
	BSLib::uint32 regId = a_type + CHARGE_ERCORD_BASE_ID;
	if(prizeIsValid(regId) && _prizeIsNeedReg(regId))
	{
		_prizeReg(a_type + CHARGE_ERCORD_BASE_ID, _timeGetCurrentStamp());
	}
	
	BSLib::uint32 prizeId = a_type + CHARGE_PRIZE_BASE_ID;
	if( 1 == a_type)
	{
		prizeRequest(120, "activity");
		_prizeOnlyReg(prizeId);
	}
	else if( 2 == a_type)
	{
		prizeRequest(121, "activity");
		_prizeOnlyReg(prizeId);
	}
	else
	{
		prizeRequest(prizeId, "activity");
	}

	
	BSLib::uint32 totalNUm = 0;
	for(BSLib::uint32 i = CHARGE_ERCORD_BASE_ID + 3; i <= CHARGE_ERCORD_BASE_ID + 8; i++)
	{
		totalNUm += prizeNum(i);
	}

	// 触发事件
	if( 1 == totalNUm)
	{
		for(BSLib::uint32 i = CHARGE_PRIZE_BASE_ID + 3; i <= CHARGE_PRIZE_BASE_ID + 8; i++)
		{
			updatePrizeState(i, 2, 1);
			updatePrizeState(i, 4, -1);
		}

		// 通知
		CMsgPrizeSystemGM2GCNtfCharge ack;
		ack.id = a_type;
		BSLib::Utility::CDateTime now = BSLib::Utility::CDateTime::getCurrentTime();
		ack.time = now.getSeconds();
		sendMsgToClient(ack);

		_prizeOnlyReg(CHARGE_EVENT_5);
	}
	
	
}

void CRolePrizeModule::_onMsgPrizeSystemGC2GMReqState(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{		
	CMsgPrizeSystemGM2GCAckState ack;
	BSLib::uint32 lv = getRoleGM()->getVipLevel();
	BSLib::uint32 temp_vips[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	std::vector<BSLib::uint32> vips(temp_vips, temp_vips + 11);
	BSLib::uint32 temp_ids[11] = {0, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
	std::vector<BSLib::uint32> ids(temp_ids, temp_ids + 11);
	for(int i = 1; i <= 10; i++)
	{
		if( lv >= i)
		{
			if(prizeIsValid(ids[i]))
				ack.states.insert(std::make_pair(i, 0));
			else
				ack.states.insert(std::make_pair(i, 1));
		}
		else
		{
			ack.states.insert(std::make_pair(i , -1));
		}
	}
	sendMsgToClient(ack);
}

void CRolePrizeModule::_onMsgPrizeSystemGC2GMReq(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgPrizeSystemGC2GMReq * req = (CMsgPrizeSystemGC2GMReq *)a_msg;
	CMsgPrizeSystemGM2GCAck ack;
	ack.vip = req->vip;
	ack.result = 1;
	BSLib::uint32 lv = getRoleGM()->getVipLevel();
	BSLib::uint32 temp_ids[11] = {0, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
	std::vector<BSLib::uint32> ids(temp_ids, temp_ids + 11);
	if( req->vip >= 1 && req->vip <= 10 && lv >= req->vip &&prizeIsValid(ids[req->vip]))
	{
		ack.result = prizeRequest(ids[req->vip], "vip") ? 0: 1;
	}
	sendMsgToClient(ack);
}

void CRolePrizeModule::_onMsgPrizeSystemGC2GMReqTime(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgPrizeSystemGM2GCAckTime ack;
	BSLib::Utility::CDateTime now = BSLib::Utility::CDateTime::getCurrentTime();
	ack.time = now.getSeconds();
	sendMsgToClient(ack);
}

bool CRolePrizeModule::_getPrizeInfo(BSLib::uint32 a_prizeId, ::GSLib::PrizeSystem::PrizeSystemChargeInfo &a_info)
{
	typedef std::map<BSLib::uint64, DB::SRolePrizeData* > PrizeMap;
	PrizeMap::iterator it = m_prizesMap.find(a_prizeId);
	if( it == m_prizesMap.end())
		return false;

	DB::SRolePrizeData* data = it->second;
	a_info.id = data->m_prizeID;
	a_info.start_time = data->m_startTime;
	a_info.end_time = data->m_endTime;
	for(std::vector<GM::StateMachineSt>::iterator it = data->m_states.begin();
		it != data->m_states.end(); ++it)
	{
		::GSLib::PrizeSystem::PrizeSystemState st;
		GM::StateMachineSt& sm = *it;
		st.type = sm.type;
		st.key = sm.key;
		st.value = sm.value;
		a_info.states.push_back(st);
	}
	
	return true;
}

void CRolePrizeModule::_onMsgPrizeSystemGC2GMReqChargeInfo(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgPrizeSystemGC2GMReqChargeInfo * req = (CMsgPrizeSystemGC2GMReqChargeInfo *)a_msg;
	CMsgPrizeSystemGM2GCAckChargeInfo ack;
	BSLib::uint32 id = req->id;
	if( 0 == id)
	{ // 全体
		for(BSLib::uint32 i = 1; i <= 8; i++)
		{
			BSLib::uint32 prizeId = i + CHARGE_PRIZE_BASE_ID;
			::GSLib::PrizeSystem::PrizeSystemChargeInfo cell;
			if(_getPrizeInfo(prizeId, cell))
			{	
				cell.id -= CHARGE_PRIZE_BASE_ID;
				ack.info.push_back(cell);
			}
		}
	}
	else if( 1 <= id && id <= 8)
	{
		BSLib::uint32 prizeId = id + CHARGE_PRIZE_BASE_ID;
		::GSLib::PrizeSystem::PrizeSystemChargeInfo cell;
		if(_getPrizeInfo(prizeId, cell))
		{	
			cell.id -= CHARGE_PRIZE_BASE_ID;
			ack.info.push_back(cell);
		}
	}

	
	sendMsgToClient(ack);
}


void CRolePrizeModule::_updateVipPrize()
{
	
}

bool CRolePrizeModule::prizeRequestToBag(const ItemSystem::GM::CPrizeItem& a_item, bool forced, std::string a_reason)
{
	std::vector<ItemSystem::GM::CPrizeItem> items;
	items.push_back(a_item);
	return prizeRequestToBag(items, forced, a_reason);
}

bool CRolePrizeModule::prizeRequestToBag(std::vector<BSLib::uint32>& a_types, std::vector<BSLib::uint32>& a_ids,
										 std::vector<BSLib::uint32>& a_nums, bool forced, std::string a_reason)
{	
	if( a_ids.size() != a_nums.size() || a_ids.empty())
		return false;

	std::vector<ItemSystem::GM::CPrizeItem> items;
	for(BSLib::uint32 i = 0; i < a_ids.size(); i++){
		items.push_back(ItemSystem::GM::CPrizeItem(a_ids[i], ItemSystem::GM::EITEM_TP_IVALID, a_nums[i]));
	}
	
	return prizeRequestToBag(items, forced, a_reason);
}

bool CRolePrizeModule::prizeRequest(const std::string& a_prizeList, bool forced, std::string a_reason)
{
	// 奖励
	// 格式 x_x|x_x
	std::vector<std::string> itemsVec;
	if( !lexicalCast<std::string>(a_prizeList, itemsVec, "|")){
		return false;
	}
	
	std::vector<BSLib::uint32> types;
	std::vector<BSLib::uint32> ids;
	std::vector<BSLib::uint32> nums;

	if( 1 == itemsVec.size())
	{
		std::vector<BSLib::uint32> item;
		if(!lexicalCast<BSLib::uint32>(itemsVec[0], item, "_")){
			return false;
		}
		
		if( 2 != item.size()){
			return false;
		}

		if( 0 != item[0] && 0 != item[1]){
			types.push_back(0);
			ids.push_back(item[0]);
			nums.push_back(item[1]);
		}
	}
	else
	{
		for(BSLib::uint32 i = 0; i < itemsVec.size(); i++){
			std::vector<BSLib::uint32> item;
			if(!lexicalCast<BSLib::uint32>(itemsVec[i], item, "_")){
				return false;
			}

			if( 2 != item.size()){
				return false;
			}

			if( 0 != item[0] && 0 != item[1]){
				types.push_back(0);
				ids.push_back(item[0]);
				nums.push_back(item[1]);
			}
		}

	}
	
	if( types.empty())
		return false;

	return prizeRequestToBag(types, ids, nums, forced, a_reason);
}

bool CRolePrizeModule::prizeRequest(BSLib::uint32 a_prize, std::vector<ItemSystem::GM::CPrizeItem>& a_items,
									const std::string a_sender, const std::string a_title, const std::string a_content, std::string a_reason)
{
	SPrizeItemInfo *info = NULL;
	if( !CPrizeConfig::singleton().getPrize(a_prize, info))
		return false;

	if(!prizeIsValid(a_prize))
		return false;

	bool needReg = _prizeIsNeedReg(a_prize);

	bool success = false;
	switch(info->m_sendType)
	{
	case EPRIZEREQUESTTYPE_BAG:
		if(prizeRequestToBag(a_items, false, a_reason)){
			success = true;
		}
		break;

	case EPRIZEREQUESTTYPE_MAIL:
		{	
			std::vector<BSLib::uint32> types;
			std::vector<BSLib::uint32> ids;
			std::vector<BSLib::uint32> nums;
			for(std::vector<ItemSystem::GM::CPrizeItem>::iterator it = a_items.begin();
				 it != a_items.end(); ++it)
			{
				ids.push_back(it->m_itemTPID);
				nums.push_back(it->m_itemCount);
			}

			PlayerSystem::GM::CRoleGM* role = getRoleGM();
			const GSLib::SRoleKey roleKey = role->getRoleKey();
			std::vector<MailSystem::SRoleGuid> roleGuids;
			roleGuids.push_back(MailSystem::SRoleGuid(roleKey));
			success = MailSystem::GM::CMailSystemGM::singleton().mailSend(a_sender, roleGuids, a_title,
				a_content, types, ids, nums);
		}
		break;

	case EPRIZEREQUESTTYPE_BAGMAIL:
		{
			if(prizeRequestToBag(a_items, false, a_reason)){
				success = true;
			}
			else{
				PlayerSystem::GM::CRoleGM* role = getRoleGM();
				const SRoleKey roleKey = role->getRoleKey();
				std::vector<MailSystem::SRoleGuid> roleGuids;
				roleGuids.push_back(MailSystem::SRoleGuid(roleKey));
				success = MailSystem::GM::CMailSystemGM::singleton().mailSend(a_sender, roleGuids, a_title, a_content, 
					info->m_itemTypes, info->m_itemIds, info->m_itemNums);
			}
		}

		break;
	}

	if(success && needReg){
		_prizeReg(a_prize, _timeGetCurrentStamp());
	}

	return success;
}

bool CRolePrizeModule::prizeRequest(BSLib::uint32 a_prize, const std::string a_reason)
{
	SPrizeItemInfo *info = NULL;
	if( !CPrizeConfig::singleton().getPrize(a_prize, info))
		return false;

	if(!prizeIsValid(a_prize))
		return false;

	bool needReg = _prizeIsNeedReg(a_prize);

	bool success = false;
	std::vector<ItemSystem::GM::CPrizeItem> items;
	for(BSLib::uint32 i = 0; i < info->m_itemTypes.size(); i++){
		items.push_back(ItemSystem::GM::CPrizeItem(info->m_itemIds[i], (ItemSystem::GM::EItemType)info->m_itemTypes[i], info->m_itemNums[i]));
	}

	switch(info->m_sendType)
	{
	case EPRIZEREQUESTTYPE_BAG:
		if(prizeRequestToBag(items, false, a_reason)){
			success = true;
		}
		break;

	case EPRIZEREQUESTTYPE_MAIL:
		{
			PlayerSystem::GM::CRoleGM* role = getRoleGM();
			const GSLib::SRoleKey roleKey = role->getRoleKey();
			std::vector<MailSystem::SRoleGuid> roleGuids;
			roleGuids.push_back(MailSystem::SRoleGuid(roleKey));
			success = MailSystem::GM::CMailSystemGM::singleton().mailSend(info->m_sender, roleGuids, info->m_title,
				info->m_content, info->m_itemTypes, info->m_itemIds, info->m_itemNums);
		}
		break;

	case EPRIZEREQUESTTYPE_BAGMAIL:
		{
			if(prizeRequestToBag(items, false, a_reason)){
				success = true;
			}
			else{
				PlayerSystem::GM::CRoleGM* role = getRoleGM();
				const SRoleKey roleKey = role->getRoleKey();
				std::vector<MailSystem::SRoleGuid> roleGuids;
				roleGuids.push_back(MailSystem::SRoleGuid(roleKey));
				success = MailSystem::GM::CMailSystemGM::singleton().mailSend(info->m_sender, roleGuids, info->m_title, info->m_content, 
					info->m_itemTypes, info->m_itemIds, info->m_itemNums);
			}
		}

		break;
	}

	if(success && needReg){
		BSLib::uint32 ratio = _prizeReg(a_prize, _timeGetCurrentStamp());
		if( 0 != ratio)
		{
			std::vector<ItemSystem::GM::CPrizeItem> items;
			for(BSLib::uint32 i = 0; i < info->m_itemTypes.size(); i++){
				items.push_back(ItemSystem::GM::CPrizeItem(info->m_itemIds[i], (ItemSystem::GM::EItemType)info->m_itemTypes[i], info->m_itemNums[i] * ratio));
			}

			switch(info->m_sendType)
			{
			case EPRIZEREQUESTTYPE_BAG:
				if(prizeRequestToBag(items, false, a_reason)){
					success = true;
				}
				break;

			case EPRIZEREQUESTTYPE_MAIL:
				{
					PlayerSystem::GM::CRoleGM* role = getRoleGM();
					const GSLib::SRoleKey roleKey = role->getRoleKey();
					std::vector<MailSystem::SRoleGuid> roleGuids;
					roleGuids.push_back(MailSystem::SRoleGuid(roleKey));
					success = MailSystem::GM::CMailSystemGM::singleton().mailSend(info->m_sender, roleGuids, info->m_title,
						info->m_content, info->m_itemTypes, info->m_itemIds, info->m_itemNums);
				}
				break;

			case EPRIZEREQUESTTYPE_BAGMAIL:
				{
					if(prizeRequestToBag(items, false, a_reason)){
						success = true;
					}
					else{
						PlayerSystem::GM::CRoleGM* role = getRoleGM();
						const SRoleKey roleKey = role->getRoleKey();
						std::vector<MailSystem::SRoleGuid> roleGuids;
						roleGuids.push_back(MailSystem::SRoleGuid(roleKey));
						success = MailSystem::GM::CMailSystemGM::singleton().mailSend(info->m_sender, roleGuids, info->m_title, info->m_content, 
							info->m_itemTypes, info->m_itemIds, info->m_itemNums);
					}
				}

				break;
			}
		}

	}

	return success;
}

bool CRolePrizeModule::prizeRequest(BSLib::uint32 a_prize, const std::string a_sender, const std::string a_title, const std::string a_content, std::string a_reason)
{	
	SPrizeItemInfo *info = NULL;
	if( !CPrizeConfig::singleton().getPrize(a_prize, info))
		return false;

	if(!prizeIsValid(a_prize))
		return false;

	bool needReg = _prizeIsNeedReg(a_prize);
	
	bool success = false;
	std::vector<ItemSystem::GM::CPrizeItem> items;
	for(BSLib::uint32 i = 0; i < info->m_itemTypes.size(); i++){
		items.push_back(ItemSystem::GM::CPrizeItem(info->m_itemIds[i], (ItemSystem::GM::EItemType)info->m_itemTypes[i], info->m_itemNums[i]));
	}

	switch(info->m_sendType)
	{
	case EPRIZEREQUESTTYPE_BAG:
		if(prizeRequestToBag(items, false, a_reason)){
			success = true;
		}
		break;

	case EPRIZEREQUESTTYPE_MAIL:
		{
			PlayerSystem::GM::CRoleGM* role = getRoleGM();
			const GSLib::SRoleKey roleKey = role->getRoleKey();
			std::vector<MailSystem::SRoleGuid> roleGuids;
			roleGuids.push_back(MailSystem::SRoleGuid(roleKey));
			success = MailSystem::GM::CMailSystemGM::singleton().mailSend(a_sender, roleGuids, a_title,
					a_content, info->m_itemTypes, info->m_itemIds, info->m_itemNums);
		}
		break;

	case EPRIZEREQUESTTYPE_BAGMAIL:
		{
			if(prizeRequestToBag(items, false, a_reason)){
				success = true;
			}
			else{
				PlayerSystem::GM::CRoleGM* role = getRoleGM();
				const SRoleKey roleKey = role->getRoleKey();
				std::vector<MailSystem::SRoleGuid> roleGuids;
				roleGuids.push_back(MailSystem::SRoleGuid(roleKey));
				success = MailSystem::GM::CMailSystemGM::singleton().mailSend(a_sender, roleGuids, a_title, a_content, 
					info->m_itemTypes, info->m_itemIds, info->m_itemNums);
			}
		}

		break;
	}

	if(success && needReg){
		_prizeReg(a_prize, _timeGetCurrentStamp());
	}

	return success;
}

bool CRolePrizeModule::prizeRequest(const std::vector<ItemSystem::GM::CPrizeItem>& a_items,
									const std::string a_sender, const std::string a_title, const std::string a_content, std::string a_reason)
{
	if(prizeRequestToBag(a_items, false, a_reason)){
		return true;
	}
	
	PlayerSystem::GM::CRoleGM* role = getRoleGM();
	const SRoleKey roleKey = role->getRoleKey();
	std::vector<MailSystem::SRoleGuid> roleGuids;
	roleGuids.push_back(MailSystem::SRoleGuid(roleKey));

	std::vector<BSLib::uint32> ItemTypes;
	std::vector<BSLib::uint32> itemIds;
	std::vector<BSLib::uint32> itemNums;
	for(std::vector<ItemSystem::GM::CPrizeItem>::const_iterator it = a_items.begin();
		it != a_items.end(); ++it){
			ItemTypes.push_back(it->m_itemType);
			itemIds.push_back(it->m_itemTPID);
			itemNums.push_back(it->m_itemCount);
	}
	
	return MailSystem::GM::CMailSystemGM::singleton().mailSend(a_sender, roleGuids, a_title, a_content, 
													ItemTypes, itemIds, itemNums);
}

bool CRolePrizeModule::_dbPrizeUpdate(BSLib::uint32 a_prize)
{
	typedef std::map<BSLib::uint64, DB::SRolePrizeData* > PrizeMap;
	PrizeMap::iterator it = m_prizesMap.find(a_prize);
	if( it == m_prizesMap.end())
		return false;

	DB::SRolePrizeData& data = *(it->second);

	BSLib::Utility::CStream dbStream;
	data.serializeTo(dbStream);
	if(m_tablePtr == NULL)
		return false;

	m_tablePtr->update(data.getDBKey(), data.getIndex(), dbStream);
	m_tablePtr->saveDataToDBServer(data.getDBKey(), data.getIndex(), true);

	return true;
}

bool CRolePrizeModule::_dbPrizeDel(BSLib::uint32 a_prize)
{	
	typedef std::map<BSLib::uint64, DB::SRolePrizeData* > PrizeMap;
	PrizeMap::iterator it = m_prizesMap.find(a_prize);
	if( it == m_prizesMap.end())
		return false;

	DB::SRolePrizeData& data = *(it->second);

	BSLib::Utility::CStream dbStream;
	data.serializeTo(dbStream);
	if(m_tablePtr == NULL)
		return false;

	m_tablePtr->remove(data.getDBKey(), data.getIndex());
	m_tablePtr->saveDataToDBServer(data.getDBKey(), data.getIndex(), true);

	return true;
}


bool CRolePrizeModule::_timeIsSameDay(BSLib::uint64 a_timeStamp)
{	
	using namespace  BSLib::Utility;
	CDateTime curTime = CDateTime::getCurrentTime();
	CDateTime preTime((time_t)a_timeStamp);
	
	return curTime.getYear() == preTime.getYear() 
		&& curTime.getMonth() == preTime.getMonth() 
		&& curTime.getDay() == preTime.getDay(); 
}

bool CRolePrizeModule::_timeIsSameMonth(BSLib::uint64 a_timeStamp)
{
	using namespace  BSLib::Utility;
	CDateTime curTime = CDateTime::getCurrentTime();
	CDateTime preTime((time_t)a_timeStamp);

	return curTime.getYear() == preTime.getYear() 
		&& curTime.getMonth() == preTime.getMonth();
}

BSLib::uint64 CRolePrizeModule::_timeGetCurrentStamp()
{
	using namespace  BSLib::Utility;
	CDateTime curTime = CDateTime::getCurrentTime();
	return curTime.getSeconds();
}

bool CRolePrizeModule::_prizeDataInitCheckRelet(BSLib::uint32 a_prize, DB::SRolePrizeData* a_data)
{
	SPrizeItemInfo *info = NULL;
	if( !CPrizeConfig::singleton().getPrize(a_prize, info))
		return false;

	if(1 != info->m_startTime && 1 != info->m_endTime)
		return false;

	BSLib::uint64 now = _timeGetCurrentStamp();
	if( 1 == info->m_endTime)
	{
		if( EPRIZEPERIODTYPE_DAYLY == info->m_periodType
			|| EPRIZEPERIODTYPE_DAYLY_ACC == info->m_periodType)
		{
			a_data->m_endTime = a_data->m_endTime  + info->m_periodNum * 24 * 60 * 60;
		}
		else if(EPRIZEPERIODTYPE_MONTHLY == info->m_periodType)
		{
			a_data->m_endTime = a_data->m_endTime + info->m_periodNum * 30 * 24 * 60 * 60;
		}
	}

	// todo 状态机
	if(info->m_stateSwitch)
	{
		a_data->m_states = info->m_stateM;
	}

	return true;
}

void CRolePrizeModule::_prizeDataInit(BSLib::uint32 a_prize, DB::SRolePrizeData* a_data)
{
	SPrizeItemInfo *info = NULL;
	if( !CPrizeConfig::singleton().getPrize(a_prize, info))
		return;
	
	PlayerSystem::GM::CRoleGM* role = getRoleGM();
	const GSLib::SRoleKey roleKey = role->getRoleKey();
	
	a_data->m_accountID = roleKey.getAccountID();
	a_data->m_zoneID = roleKey.getZoneID();
	a_data->m_roleIndex = roleKey.getIndex();
	a_data->m_prizeID = a_prize;
	
	BSLib::uint64 now = _timeGetCurrentStamp();
	if( 1 == info->m_startTime)
	{
		a_data->m_startTime = now;
	}

	if( 1 == info->m_endTime)
	{
		if( EPRIZEPERIODTYPE_DAYLY == info->m_periodType
			|| EPRIZEPERIODTYPE_DAYLY_ACC == info->m_periodType)
		{
			a_data->m_endTime = now  + info->m_periodNum * 24 * 60 * 60;
		}
		else if(EPRIZEPERIODTYPE_MONTHLY == info->m_periodType)
		{
			a_data->m_endTime = now + info->m_periodNum * 30 * 24 * 60 * 60;
		}
	}
	
	// todo 状态机
	if(info->m_stateSwitch)
	{
		a_data->m_states = info->m_stateM;
	}
}	

bool CRolePrizeModule::_prizeOnlyReg(BSLib::uint32 a_prize)
{	
	prizeIsValid(a_prize); // del 过期

	typedef std::map<BSLib::uint64, DB::SRolePrizeData* > PrizeMap;
	PrizeMap::iterator it = m_prizesMap.find(a_prize);
	if( it != m_prizesMap.end())
	{	// 不适合续租
		if( !_prizeDataInitCheckRelet(a_prize, it->second))
			return false;
	}
	else
	{
		DB::SRolePrizeData* prize = new DB::SRolePrizeData;
		_prizeDataInit(a_prize, prize);
		m_prizesMap.insert(std::make_pair(a_prize, prize));
	}
	
	

	_dbPrizeUpdate(a_prize);

	return true;
}

BSLib::uint32 CRolePrizeModule::_prizeReg(BSLib::uint32 a_prize, BSLib::uint64 a_timeStamp)
{	
	typedef std::map<BSLib::uint64, DB::SRolePrizeData* > PrizeMap;
	PrizeMap::iterator it = m_prizesMap.find(a_prize);
	DB::SRolePrizeData* prize  = NULL;
	if( it == m_prizesMap.end())
	{
		 prize = new DB::SRolePrizeData;
		 _prizeDataInit(a_prize, prize);
		 m_prizesMap.insert(std::make_pair(a_prize, prize));
	}
	else
	{
		prize = it->second;
	}

	prize->m_num++;
	prize->m_timestamp = a_timeStamp;
	
	BSLib::uint32 res = 0;
	std::vector<GM::StateMachineSt>::iterator smIt = prize->m_states.begin();
	for(; smIt != prize->m_states.end(); ++smIt)
	{
		GM::StateMachineSt& st = *smIt;
		if( 0 != st.value)
		{
			if( -1 != st.value)
				st.value--;

			res =  st.key;
			break;
		}	
	}

	_dbPrizeUpdate(a_prize);

	return res;
}

void CRolePrizeModule::_prizeDel(BSLib::uint32 a_prize)
{	
	_dbPrizeDel(a_prize);
	
	typedef std::map<BSLib::uint64, DB::SRolePrizeData* > PrizeMap;
	PrizeMap::iterator it = m_prizesMap.find(a_prize);
	if( it == m_prizesMap.end())
		return;

	delete it->second;
	m_prizesMap.erase(it);
}

bool CRolePrizeModule::_prizeIsExist(BSLib::uint32 a_prize)
{
	return m_prizesMap.find(a_prize) != m_prizesMap.end();
}

BSLib::uint32 CRolePrizeModule::_prizeNum(BSLib::uint32 a_prize)
{
	typedef std::map<BSLib::uint64, DB::SRolePrizeData* > PrizeMap;
	PrizeMap::iterator it = m_prizesMap.find(a_prize);
	if( it == m_prizesMap.end())
		return 0;

	return it->second->m_num;
}

bool CRolePrizeModule::_prizeNumIsValid(BSLib::uint32 a_prize, BSLib::uint32 a_limitNum)
{
	if( 0 == a_limitNum)
		return true;

	return a_limitNum > _prizeNum(a_prize);
}

// 因为可以叠加..
bool CRolePrizeModule::_prizeDayAccNumIsValid(BSLib::uint32 a_prize)
{
	typedef std::map<BSLib::uint64, DB::SRolePrizeData* > PrizeMap;
	PrizeMap::iterator it = m_prizesMap.find(a_prize);
	if( it == m_prizesMap.end())
		return false;

	//BSLib::uint64 delta = _timeGetCurrentStamp() - it->second->m_startTime; // 流逝了多少秒
	BSLib::uint32 dayLeft = it->second->m_startTime % (24 * 60 * 60); // 开始的那天还剩多少秒到24点
	BSLib::uint64 prizePeriod = it->second->m_endTime - it->second->m_startTime;
	if(prizePeriod > dayLeft)
	{
		BSLib::uint64 numSeconds = prizePeriod - dayLeft;
		BSLib::uint64 couldUseDay = numSeconds / (24 * 60 * 60);
		if(numSeconds % (24 * 60 * 60) )
			couldUseDay += 1;

		if( couldUseDay > it->second->m_num)
			return true;
	}

	return false;
}

bool CRolePrizeModule::_timeCheck(BSLib::uint32 a_prize)
{	
	SPrizeItemInfo *info = NULL;
	if( !CPrizeConfig::singleton().getPrize(a_prize, info))
		return false;

	using namespace  BSLib::Utility;
	CDateTime curTime = CDateTime::getCurrentTime();
	BSLib::uint64 curSec = curTime.getSeconds();
	
	// 检测开始时间
	BSLib::uint64 startTime = info->m_startTime;
	do 
	{	
		if( 0 == startTime)
			break;

		if( 1 == startTime)
		{
			typedef std::map<BSLib::uint64, DB::SRolePrizeData* > UINT64Map;
			UINT64Map::iterator it = m_prizesMap.find(a_prize);
			if( it == m_prizesMap.end())
				break;

			if( curSec >= it->second->m_startTime)
				break;
		}

		if( curSec >= startTime)
			break;
		
		return false;

	} while (false);

	// 检测结束时间
	BSLib::uint64 endTime = info->m_endTime;
	do 
	{	
		if( 0 == endTime)
			break;

		if( 1 == endTime)
		{
			typedef std::map<BSLib::uint64, DB::SRolePrizeData* > UINT64Map;
			UINT64Map::iterator it = m_prizesMap.find(a_prize);
			if( it == m_prizesMap.end())
				break;

			if( curSec < it->second->m_endTime)
				break;
		}

		if( curSec < endTime)
			break;

		return false;

	} while (false);

	return true;
}

bool CRolePrizeModule::_prizeIsInPeriodOfValidity(SPrizeItemInfo *info)
{	
	return _timeCheck(info->m_id);
}




}//GM

}//PrizeSystem

}//GSLib
