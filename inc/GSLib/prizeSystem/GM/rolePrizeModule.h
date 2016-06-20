//////////////////////////////////////////////////////////////////////
//	created:	2014/09/13
//	filename: 	GSLib\prizeSystem\GM\rolePrizeModule.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PRIZESYSTEM_GM_ROLEPRIZEMODULE_H__
#define __GSLIB_PRIZESYSTEM_GM_ROLEPRIZEMODULE_H__

#include <GSLib/playerSystem/GM/roleModuleGM.h>
#include <GSLib/baseDef.h>
#include <BSLib/database/dbTableRow.h>
#include <GSLib/dbSystem/keyIndexTable.h>
#include <GSLib/prizeSystem/GM/prizeConfig.h>
#include <GSLib/itemSystem/GM/itemAttributeGM.h>
#include <GSLib/prizeSystem/DB/tablePrizeDB.h>
#include <GSLib/prizeSystem/GM/prize.proto.h>

namespace GSLib
{

namespace PrizeSystem
{

namespace GM
{

class CRolePrizeModule : public GSLib::PlayerSystem::GM::CRoleModuleGM
	, BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::CCallback
{
public:
	CRolePrizeModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType);
	virtual ~CRolePrizeModule();

	virtual void		preInit(bool isFirst);
	virtual void		postInit(bool isFirst);
	virtual void		initToClient();
	virtual void		final();
	virtual void		initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual void		freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool		exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value);
	virtual void		updateDataToDB();
	virtual bool		cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);

	// 通过prize id 发放奖励
	bool				prizeIsValid(BSLib::uint32 a_prize);
	bool				prizeRequest(BSLib::uint32 a_prize, const std::string a_reason);
	bool				prizeRequest(BSLib::uint32 a_prize, const std::string a_sender, const std::string a_title, const std::string a_content, std::string a_reason);
	bool				prizeRequest(BSLib::uint32 a_prize, std::vector<ItemSystem::GM::CPrizeItem>& a_items,
									const std::string a_sender, const std::string a_title, const std::string a_content, std::string a_reason);
	
	bool				prizeRequest(const std::string& a_prizeList, bool forced, std::string a_reason); // 奖励格式 x_x|x_x
	bool				prizeRequest(const std::vector<ItemSystem::GM::CPrizeItem>& a_items,	// 先尝试放进背包, 失败则走邮件	
									const std::string a_sender, const std::string a_title, const std::string a_content, std::string a_reason);
	bool				prizeRequestToBag(const std::vector<ItemSystem::GM::CPrizeItem>& a_items, bool forced, std::string a_reason);	// 直接发放资源物品
	bool				prizeRequestToBag(const ItemSystem::GM::CPrizeItem& a_item, bool forced, std::string a_reason);
	bool				prizeRequestToBag(std::vector<BSLib::uint32>& a_types, std::vector<BSLib::uint32>& a_ids, std::vector<BSLib::uint32>& a_nums,
											bool forced, std::string a_reason);

	BSLib::uint32		prizeNum(BSLib::uint32 a_prize);

	void				chargeUpdate(BSLib::int64 a_chargeID, int a_type, int a_money);
	bool				updatePrizeState(BSLib::uint32 a_prize, int a_type, int a_value);
	bool				_prizeOnlyReg(BSLib::uint32 a_prize);
	BSLib::uint64		_prizeGetTimeStamp(BSLib::uint32 a_prize);
	BSLib::uint64		_timeGetCurrentStamp();

	// 自定义的状态
	bool				_getCardState(BSLib::uint32 a_prize, std::vector<StateMachineSt>& a_st);
	bool				_setCardState(BSLib::uint32 a_Prize, std::vector<StateMachineSt>& a_st);


private:
	void _onMsgPrizeSystemGC2GMReqState(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgPrizeSystemGC2GMReq(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgPrizeSystemGC2GMReqTime(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgPrizeSystemGC2GMReqChargeInfo(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgPrizeSystemGC2GMNtfAction(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);


	void _updateVipPrize(); // todo
	
private:
	bool				_getPrizeInfo(BSLib::uint32 a_prizeId, ::GSLib::PrizeSystem::PrizeSystemChargeInfo &a_info);
	bool				_dbPrizeUpdate(BSLib::uint32 a_prize);
	bool				_dbPrizeDel(BSLib::uint32 a_prize);

	bool				_timeIsSameDay(BSLib::uint64 a_timeStamp);
	bool				_timeIsSameMonth(BSLib::uint64 a_timeStamp);
	
	bool				_timeCheck(BSLib::uint32 a_prize);

	BSLib::uint32		_prizeReg(BSLib::uint32 a_prize, BSLib::uint64 a_timeStamp);
	void				_prizeDataInit(BSLib::uint32 a_prize, DB::SRolePrizeData* a_data);
	bool				_prizeDataInitCheckRelet(BSLib::uint32 a_prize, DB::SRolePrizeData* a_data); // 续签
	void				_prizeDel(BSLib::uint32 a_prize);
	bool				_prizeIsExist(BSLib::uint32 a_prize);
	BSLib::uint32		_prizeNum(BSLib::uint32 a_prize);
	bool				_prizeNumIsValid(BSLib::uint32 a_prize, BSLib::uint32 a_limitNum);
	bool				_prizeDayAccNumIsValid(BSLib::uint32 a_prize);
	bool				_prizeIsInPeriodOfValidity(SPrizeItemInfo *info);
	bool				_prizeNolimitIsValid(SPrizeItemInfo *info);
	bool				_prizeOnceIsValid(SPrizeItemInfo *info);
	bool				_prizeDaylyIsValid(SPrizeItemInfo *info);
	bool				_prizeMonthlyIsValid(SPrizeItemInfo *info);
	bool				_prizeDayAcclyIsValid(SPrizeItemInfo *info);

	bool				_prizeIsNeedReg(BSLib::uint32 a_prize);
	
	// 抽卡存在自定义格式里
	bool				_prizeGetParam(BSLib::uint32 a_prize, std::vector<char>& a_buf);
	bool				_prizeSetParam(BSLib::uint32 a_prize, std::vector<char>& a_buf);


private:
	std::map<BSLib::uint64, DB::SRolePrizeData* >	m_prizesMap;
	GSLib::DBSystem::CKeyIndexTablePtr		m_tablePtr;
	
};

}//GM

}//PrizeSystem

}//GSLib

#endif//__GSLIB_PRIZESYSTEM_GM_ROLEPRIZEMODULE_H__