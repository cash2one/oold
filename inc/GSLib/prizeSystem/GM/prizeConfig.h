#ifndef __GSLIB_PRIZESYSTEM_GM_PRIZECONFIG_H__
#define __GSLIB_PRIZESYSTEM_GM_PRIZECONFIG_H__

#include <BSLib/utility/hashMap.h>

namespace GSLib
{

namespace PrizeSystem
{

namespace GM
{


	enum EPrizePeriodType
	{
		EPRIZEPERIODTYPE_NOLIMIT	=1,	// 无限制
		EPRIZEPERIODTYPE_ONCE,			// 期间只有一次
		EPRIZEPERIODTYPE_DAYLY,			// 每天
		EPRIZEPERIODTYPE_MONTHLY,		// 每月
		EPRIZEPERIODTYPE_DAYLY_ACC,		// 每天, 领取总次数不清空,每日累加
	};

	enum EPrizeRequestType
	{
		EPRIZEREQUESTTYPE_BAG		=1, // 放进背包
		EPRIZEREQUESTTYPE_MAIL,			// 以邮件发送
		EPRIZEREQUESTTYPE_BAGMAIL,		// 先尝试放进背包,失败,则以邮件发送
		EPRIZEREQUESTTYPE_NOTSEND,		// 不发送
	};

struct StateMachineSt{
	StateMachineSt()
		:type(0)
		,key(0)
		,value(0)
	{

	}
	BSLib::int32 type;
	BSLib::int32 key;
	BSLib::int32 value;
};

struct SPrizeItemInfo
{	
	SPrizeItemInfo()
		:m_id(0)
		,m_startTime(0)
		,m_endTime(0)
		,m_periodType(0)
		,m_periodNum(0)
		,m_sendType(0)
		,m_limitNum(0)
		,m_stateSwitch(0)
	{

	}

	BSLib::uint32				m_id;
	BSLib::uint64				m_startTime;
	BSLib::uint64				m_endTime;
	BSLib::uint32				m_periodType;
	BSLib::uint32				m_periodNum; // new
	std::vector<BSLib::uint32>	m_itemTypes;
	std::vector<BSLib::uint32>	m_itemIds;
	std::vector<BSLib::uint32>	m_itemNums;
	BSLib::uint32				m_sendType;
	BSLib::uint32				m_limitNum;
	std::string					m_sender;
	std::string					m_title;
	std::string					m_content;

	BSLib::uint32				m_stateSwitch;	// new
	std::vector<StateMachineSt> m_stateM;	// new
};

class CPrizeConfig
{
public:
	CPrizeConfig();
	~CPrizeConfig();
	BSLIB_SINGLETON_DECLARE(CPrizeConfig);

	bool loadConfigFile(const std::string& a_configFile);

	bool getPrize(BSLib::int32 a_prizeID, SPrizeItemInfo*& a_prizeItemList);

private:
	BSLib::Utility::CHashMap<BSLib::int32, SPrizeItemInfo* > m_prizesHashMap;
};

}//GM

}//PrizeSystem

}//GSLib

#endif//__GSLIB_PRIZESYSTEM_GM_PRIZECONFIG_H__
