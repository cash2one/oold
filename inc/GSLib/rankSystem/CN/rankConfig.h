#ifndef SHOSYSTEM_GM_SHOPCONFIG_H__
#define SHOSYSTEM_GM_SHOPCONFIG_H__
#include <BSLib/utility/singleton.h>
#include <map>
#include <BSLib/utility/baseDef.h>

namespace GSLib
{
namespace RankSystem
{
namespace CN
{

struct SRankPosInfo
{	
	SRankPosInfo()
		:m_posStart(0)
		,m_posEnd(0)
	{}

	BSLib::int32				m_posStart;
	BSLib::int32				m_posEnd;
	std::vector<BSLib::uint32> m_ids;
	std::vector<BSLib::uint32> m_nums;
};

struct SRankMailInfo
{	
	SRankMailInfo():m_maxSize(0),m_prizeSize(0) {}
	std::string		m_sender;
	std::string		m_title;
	std::string		m_content;
	BSLib::int32	m_maxSize;
	BSLib::int32	m_prizeSize;
};


class CRankConfig
{
	BSLIB_SINGLETON_DECLARE(CRankConfig)
public:
	CRankConfig();
	~CRankConfig();

	bool loadConfigFile(const std::string& a_configFile);
	bool getRankPrize(BSLib::int32 a_rankId, BSLib::int32 a_pos, SRankPosInfo*& a_Item);
	bool getRankMail(BSLib::int32 a_rankId, SRankMailInfo*& a_rankConfig);

private:
	std::map<BSLib::int32, std::vector<SRankPosInfo*> > m_rankItemsHashMap;
	std::map<BSLib::int32, SRankMailInfo* > m_rankMailHashMap;
};

 
} // GM
} // RankSystem
} // BSLib

#endif // SHOSYSTEM_GM_SHOPCONFIG_H__
