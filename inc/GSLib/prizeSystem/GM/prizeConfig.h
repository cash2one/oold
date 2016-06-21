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
		EPRIZEPERIODTYPE_NOLIMIT	=1,	// ������
		EPRIZEPERIODTYPE_ONCE,			// �ڼ�ֻ��һ��
		EPRIZEPERIODTYPE_DAYLY,			// ÿ��
		EPRIZEPERIODTYPE_MONTHLY,		// ÿ��
		EPRIZEPERIODTYPE_DAYLY_ACC,		// ÿ��, ��ȡ�ܴ��������,ÿ���ۼ�
	};

	enum EPrizeRequestType
	{
		EPRIZEREQUESTTYPE_BAG		=1, // �Ž�����
		EPRIZEREQUESTTYPE_MAIL,			// ���ʼ�����
		EPRIZEREQUESTTYPE_BAGMAIL,		// �ȳ��ԷŽ�����,ʧ��,�����ʼ�����
		EPRIZEREQUESTTYPE_NOTSEND,		// ������
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
