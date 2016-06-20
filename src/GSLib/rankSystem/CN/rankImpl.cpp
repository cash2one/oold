#include <GSLib/rankSystem/CN/rankImpl.h>
#include <GSLib/playerSystem/CN/playerCNMgr.h>
#include <GSLib/playerSystem/CN/roleBaseInfoCNMgr.h>
#include <algorithm>
#include <GSLib/playerSystem/CN/playerCN.h>
#include <GSLib/playerSystem/CN/playerCNMgr.h>
#include <GSLib/playerSystem/CN/roleModuleCNMgr.h>
#include <GSLib/rankSystem/CN/roleRankModuleCN.h>

namespace GSLib
{
namespace RankSystem
{
namespace CN
{

ERankType OrderedRank::getType()
{
	return ERANKTYPE_ORDERED;
}

void OrderedRank::update(SRoleKey& a_key, BSLib::int32 a_param)
{
	if(_update(a_key, a_param))
		save();
}

bool OrderedRank::_update(SRoleKey& a_key, BSLib::int32 a_param)
{	
	BSLib::int32 oldParam = a_param;
	BSLib::int32 newParam = a_param;

	std::map<SRoleKey, BSLib::int32>::iterator searchIt = m_search.find(a_key);
	if( searchIt != m_search.end())
	{	// 存在, 但新旧值相等
		oldParam = searchIt->second;
		if( oldParam == newParam)
			return false;

		searchIt->second = newParam;
	}
	else
	{
		// 不存在, 检测大小
		if(m_search.size() >= m_capacity)
			return false;

		m_search.insert(std::make_pair(a_key, newParam));
	}
	
	typedef std::map<BSLib::int32, std::list<SRoleKey>, std::greater<BSLib::int32> >  ContainerType;
	ContainerType::iterator containerIt = m_list.find(oldParam);
	if( containerIt == m_list.end())
	{	// 容器不存在创建个..
		std::pair<ContainerType::iterator, bool> resultPair;
		resultPair = m_list.insert(std::make_pair(oldParam, std::list<SRoleKey>()));
		containerIt = resultPair.first;
	}
	
	// new
	if(oldParam == newParam)
	{
		containerIt->second.push_back(a_key);
		return false;
	}
	
	// 移除旧的
	std::list<SRoleKey>& oldKeys = containerIt->second;
	std::list<SRoleKey>::iterator delIt = std::find(oldKeys.begin(), oldKeys.end(), a_key);
	if( delIt != oldKeys.end())
		oldKeys.erase(delIt);

	// 添加新的
	containerIt = m_list.find(newParam);
	if(containerIt == m_list.end())
	{
		// 容器不存在创建个..
		std::pair<ContainerType::iterator, bool> resultPair;
		resultPair = m_list.insert(std::make_pair(newParam, std::list<SRoleKey>()));
		containerIt = resultPair.first;
	}
	containerIt->second.push_back(a_key);

	return true;
}

bool OrderedRank::getParam(SRoleKey& a_key, BSLib::int32 &a_param)
{
	std::map<SRoleKey, BSLib::int32>::iterator searchIt = m_search.find(a_key);
	if( searchIt != m_search.end())
	{	
		a_param =  searchIt->second;
		return true;
	}

	return false;
}

BSLib::uint32 OrderedRank::getPlace(SRoleKey& a_key)
{	
	std::map<SRoleKey, BSLib::int32>::iterator searchIt = m_search.find(a_key);
	if( searchIt == m_search.end())
	{	
		return 0;
	}
	
	BSLib::int32 param = searchIt->second;
	typedef std::map<BSLib::int32, std::list<SRoleKey>, std::greater<BSLib::int32> >  ContainerType;
	BSLib::int32 count = 0;
	for(ContainerType::iterator it = m_list.begin(); it != m_list.end(); ++it)
	{
		if( param != it->first)
			count += it->second.size();
		else
		{
			std::list<SRoleKey>& q = it->second;
			for(std::list<SRoleKey>::iterator subIt = q.begin(); subIt != q.end(); ++subIt)
			{	
				count++;
				if(*subIt == a_key)
					break;
			}

			break;
		}
	}

	return count;
}

bool OrderedRank::getRole(BSLib::uint32 a_place, SRoleKey& a_key)
{	
	if( 0 == a_place)
		return false;
	
	if( a_place > m_search.size())
		return false;

	typedef std::map<BSLib::int32, std::list<SRoleKey>, std::greater<BSLib::int32> >  ContainerType;
	BSLib::uint32 count = 0;
	for(ContainerType::iterator it = m_list.begin(); it != m_list.end(); ++it)
	{	
		count += it->second.size();
		if( a_place > count)
			continue;
		
		BSLib::int32 delta = a_place - (count - it->second.size());
		std::list<SRoleKey>& q = it->second;
		for(std::list<SRoleKey>::iterator subIt = q.begin(); subIt != q.end(); ++subIt)
		{	
			delta--;
			if(0 == delta)
			{
				a_key = *subIt;
				return true;
			}
		}
	}

	return false;
}

bool OrderedRank::serializeTo(BSLib::Utility::CStream& a_stream)
{
	a_stream << m_id;
	a_stream << BSLib::int16(0);
	BSLib::uint32 type = getType();
	a_stream << type;

	BSLib::Utility::CStream bufExact;
	bufExact << m_search.size();
	std::map<SRoleKey, BSLib::int32>::iterator it = m_search.begin();
	for(; it != m_search.end(); ++it)
	{
		bufExact << it->first;
		bufExact << it->second;
	}
	
	std::vector<char> sExact;
	sExact.resize(bufExact.getWritePosition());
	bufExact.read(&sExact[0], bufExact.getWritePosition());
	a_stream << sExact;

	
	std::vector<char> sAppr;
	a_stream << sAppr;
	a_stream << m_refreshTime;
	saveReset();
	return true;
}

void OrderedRank::reset()
{	
	Rank::reset();
	m_list.clear();
	m_search.clear();
}

BSLib::uint32 OrderedRank::getSize() const
{
	return m_list.size();
}

void OrderedRank::getState(SRoleKey& a_key, std::vector<SRankCell>& a_states, BSLib::int32 a_curParam)
{	
	using namespace PlayerSystem::CN;
	if( 0 != a_key.getAccountID() ||
		0 != a_key.getZoneID() || 
		0 != a_key.getIndex())
	{	// 获取指定玩家的信息
		CRoleBaseInfoCN * base = 
			CRoleBaseInfoCNMgr::singleton().getRoleBaseInfoCNByRoleKey(a_key.getDBKey());
		SRankCell info;
		info.m_role = a_key;
		if(NULL != base)
		{	
			info.m_pos = getPlace(a_key);
			info.m_name = base->getRoleName();
			info.m_level = base->getRoleLevel();
			info.m_vip = 0; // todo
			info.m_job = base->getRoleTPID();
			info.m_power = base->getCombat();
			getParam(a_key, info.m_param);
		}
		a_states.push_back(info);

		return;
	}

	
	BSLib::uint32 minSize = m_search.size();
	BSLib::uint32 maxLen = m_capacity;
	minSize = std::min<BSLib::uint32>(minSize, maxLen);
	typedef std::map<BSLib::int32, std::list<SRoleKey>, std::greater<BSLib::int32> >  ContainerType;
	BSLib::uint32 count = 0;
	for(ContainerType::iterator it = m_list.begin(); it != m_list.end(); ++it)
	{
		std::list<SRoleKey>& q = it->second;
		for(std::list<SRoleKey>::iterator subIt = q.begin(); subIt != q.end(); ++subIt)
		{	
			count++; 
			if( count > minSize)
				break;

			CRoleBaseInfoCN * base = 
				CRoleBaseInfoCNMgr::singleton().getRoleBaseInfoCNByRoleKey(subIt->getDBKey());
			SRankCell info;
			info.m_role = *subIt;
			if(NULL != base)
			{	
				info.m_pos = count;
				info.m_name = base->getRoleName();
				info.m_level = base->getRoleLevel();
				info.m_vip = 0; // todo
				info.m_job = base->getRoleTPID();
				info.m_power = base->getCombat();
				info.m_param = it->first;
			}
			a_states.push_back(info);
		}
	}	
}

bool OrderedRank::serializeFrom(BSLib::Utility::CStream& a_stream)
{
	a_stream >> m_id;
	BSLib::uint16 dummy;
	a_stream >> dummy;
	BSLib::uint32 type;
	a_stream >> type;

	std::vector<char> sExact;
	a_stream >> sExact;

	BSLib::Utility::CStream exactStream;
	exactStream.write(&sExact[0], sExact.size());

	BSLib::uint32 size  = 0;
	exactStream >> size;
	for(BSLib::uint32 i = 0; i < size; i++)
	{
		SRoleKey key;
		BSLib::int32 v = 0;

		exactStream >> key;
		exactStream >> v;

		_update(key, v);
	}

	std::vector<char> sAppr;
	a_stream >> sAppr;
	a_stream >> m_refreshTime;
	saveReset();
	return true;
}





ERankType TranspositionRank::getType()
{	
	return ERANKTYPE_TRANSPOSITION;
}

void TranspositionRank::update(SRoleKey& a_key, SRoleKey& a_other)
{	
	/*
	 if  first enter
		check capacity
		insert
	 else
	  a  in , b out   transpositon
	  a  out, b in    transpositon
	  a  in  b  in    transpositon 
	*/
	if	(
		0 == a_key.getAccountID() &&
		0 == a_key.getZoneID() &&
		0 == a_key.getIndex()
		)
	{
		return;
	}

	do 
	{	
		std::map<SRoleKey, BSLib::int32>::iterator firstIt = m_search.find(a_key);

		if	(
			0 == a_other.getAccountID() &&
			0 == a_other.getZoneID() &&
			0 == a_other.getIndex()
			)
		{	// 首次进入
			if(m_search.size() >= m_capacity)
				return;
			
			if( firstIt  != m_search.end())
				return;

			m_list.push_back(a_key);
			m_search.insert(std::make_pair(a_key, m_list.size() - 1));	//  0 based ,方便调用
			break;
		}

		std::map<SRoleKey, BSLib::int32>::iterator secondIt = m_search.find(a_other);
		if( firstIt != m_search.end() && secondIt == m_search.end())
		{	
			BSLib::int32 oldPos = firstIt->second;
			m_list[oldPos] = a_other;
			m_search.erase(firstIt);
			m_search.insert(std::make_pair(a_other, oldPos));
			break;

		}
		else if( firstIt == m_search.end() && secondIt != m_search.end())
		{
			BSLib::int32 oldPos = secondIt->second;
			m_list[oldPos] = a_key;
			m_search.erase(secondIt);
			m_search.insert(std::make_pair(a_key, oldPos));
			break;
		}
		else if(firstIt != m_search.end() && secondIt != m_search.end())
		{
			BSLib::int32 firstPos = firstIt->second;
			BSLib::int32 secondPos = secondIt->second;

			firstIt->second = secondPos;
			secondIt->second = firstPos;
			m_list[firstPos] = a_other;
			m_list[secondPos] = a_key;
			break;
		}
		else
		{
			return; // 退出
		}

	} while (false);
	
	synPlace(a_key);
	synPlace(a_other);
	save();
}

BSLib::uint32 TranspositionRank::getPlace(SRoleKey& a_key)
{	
	std::map<SRoleKey, BSLib::int32>::iterator it = m_search.find(a_key);
	if( it == m_search.end())
		return 0;
	
	return it->second + 1;
}

bool TranspositionRank::getRole(BSLib::uint32 a_place, SRoleKey& a_key)
{	

	if( 0 == a_place)
		return false;

	if( a_place > m_search.size())
		return false;

	a_key = m_list[a_place - 1];
	return true;
}

bool TranspositionRank::serializeTo(BSLib::Utility::CStream& a_stream)
{
	a_stream << m_id;
	a_stream << BSLib::int16(0);
	BSLib::uint32 type = getType();
	a_stream << type;

	BSLib::Utility::CStream bufExact;
	bufExact << m_list.size();
	std::vector<SRoleKey>::iterator it = m_list.begin();
	for(; it != m_list.end(); ++it)
	{
		bufExact << *it;
	}

	std::vector<char> sExact;
	sExact.resize(bufExact.getWritePosition());
	bufExact.read(&sExact[0], bufExact.getWritePosition());
	a_stream << sExact;


	std::vector<char> sAppr;
	a_stream << sAppr;
	a_stream << m_refreshTime;
	saveReset();
	return true;
}

void TranspositionRank::reset()
{	
	Rank::reset();
	m_list.clear();
	m_search.clear();
}

void TranspositionRank::synPlace(SRoleKey &a_key)
{
	using namespace GSLib::PlayerSystem::CN;
	CPlayerCN *player = CPlayerCNMgr::singleton().getPlayerCN(GFLib::SAccountKey(a_key.getAccountID(), a_key.getZoneID()));
	if(NULL == player)
		return;

	if(player->getCurRoleIndex() != a_key.getIndex())
		return;

	CRoleCN * role = player->getCurRole();
	CRoleRankModuleCN* rankModule = (CRoleRankModuleCN*)role->getPlayerModuleCN(EMODULECTYPE_RANK);
	rankModule->synPlaceToGM(getId());
}

BSLib::uint32 TranspositionRank::getSize() const
{
	return m_list.size();
}

void TranspositionRank::getState(SRoleKey& a_key, std::vector<SRankCell>& a_states, BSLib::int32 a_curParam)
{
	using namespace PlayerSystem::CN;
	if( 0 != a_key.getAccountID() ||
		0 != a_key.getZoneID() || 
		0 != a_key.getIndex())
	{	// 获取指定玩家的信息
		CRoleBaseInfoCN * base = 
			CRoleBaseInfoCNMgr::singleton().getRoleBaseInfoCNByRoleKey(a_key.getDBKey());
		SRankCell info;
		info.m_role = a_key;
		if(NULL != base)
		{	
			info.m_pos = getPlace(a_key);
			info.m_name = base->getRoleName();
			info.m_level = base->getRoleLevel();
			info.m_vip = 0; // todo
			info.m_job = base->getRoleTPID();
			info.m_power = base->getCombat();
			info.m_param = 0;
		}
		a_states.push_back(info);

		return;
	}


	BSLib::uint32 minSize = m_search.size();
	BSLib::uint32 maxLen = m_capacity;
	minSize = std::min<BSLib::uint32>(minSize, maxLen);
	BSLib::uint32 count = 0;
	for(std::vector<SRoleKey>::iterator it = m_list.begin(); it != m_list.end(); ++it)
	{
		count++; 
		if( count > minSize)
			break;

		CRoleBaseInfoCN * base = 
			CRoleBaseInfoCNMgr::singleton().getRoleBaseInfoCNByRoleKey(it->getDBKey());
		SRankCell info;
		info.m_role = *it;
		if(NULL != base)
		{	
			info.m_pos = count;
			info.m_name = base->getRoleName();
			info.m_level = base->getRoleLevel();
			info.m_vip = 0; // todo
			info.m_job = base->getRoleTPID();
			info.m_power = base->getCombat();
			info.m_param = 0;
		}
		a_states.push_back(info);
	}
}

bool TranspositionRank::serializeFrom(BSLib::Utility::CStream& a_stream)
{
	a_stream >> m_id;
	BSLib::uint16 dummy;
	a_stream >> dummy;
	BSLib::uint32 type;
	a_stream >> type;

	std::vector<char> sExact;
	a_stream >> sExact;

	BSLib::Utility::CStream exactStream;
	exactStream.write(&sExact[0], sExact.size());

	BSLib::uint32 size  = 0;
	exactStream >> size;
	for(BSLib::uint32 i = 0; i < size; i++)
	{
		SRoleKey key;
		exactStream >> key;
		m_list.push_back(key);
		m_search.insert(std::make_pair(key, i));
	}

	std::vector<char> sAppr;
	a_stream >> sAppr;
	a_stream >> m_refreshTime;
	saveReset();
	return true;
}



ERankType BucketRank::getType()
{
	return ERANKTYPE_BUCKET;
}

void BucketRank::update(SRoleKey& a_key, BSLib::int32 a_preParam, BSLib::int32 a_curParam)
{

	if( 0 == a_curParam)
		return;

	OrderedRank::update(a_key, a_curParam);
	typedef std::map<BSLib::int32, BSLib::int32, std::greater<BSLib::int32> > StatMap;
	if( 0 != a_preParam)
	{
		StatMap::iterator preIt = m_statistics.find(a_preParam);
		if(preIt != m_statistics.end())
			preIt->second--;
	}
		
	StatMap::iterator curIt = m_statistics.find(a_curParam);
	if(curIt != m_statistics.end())
		curIt->second++;
	else
	{
		m_statistics.insert(std::make_pair(a_curParam, 1));
	}
	
	save();
}

bool BucketRank::getParam(SRoleKey& a_key, BSLib::int32 &a_param)
{
	return OrderedRank::getParam(a_key, a_param);
}

BSLib::uint32 BucketRank::getPlace(SRoleKey& a_key, BSLib::int32 a_curParam)
{	
	BSLib::uint32 pos = OrderedRank::getPlace(a_key);
	if(0 != pos)
		return pos;
	
	typedef std::map<BSLib::int32, BSLib::int32, std::greater<BSLib::int32> > StatMap;
	StatMap::iterator searchIt = m_statistics.find(a_curParam);
	if( searchIt == m_statistics.end())
		return 0;
	
	BSLib::uint32 count = 0;
	for(StatMap::iterator it = m_statistics.begin(); it != m_statistics.end(); ++it)
	{
		if( it != searchIt)
			count += it->second;
		else
			return ++count;
	}

	return 0;
}

bool BucketRank::getRole(BSLib::uint32 a_place, SRoleKey& a_key)
{
	return OrderedRank::getRole(a_place, a_key);
}

bool BucketRank::serializeTo(BSLib::Utility::CStream& a_stream)
{	
	a_stream << m_id;
	a_stream << BSLib::int16(0);
	BSLib::uint32 type = getType();
	a_stream << type;

	BSLib::Utility::CStream bufExact;
	bufExact << m_search.size();
	std::map<SRoleKey, BSLib::int32>::iterator it = m_search.begin();
	for(; it != m_search.end(); ++it)
	{
		bufExact << it->first;
		bufExact << it->second;
	}

	std::vector<char> sExact;
	sExact.resize(bufExact.getWritePosition());
	bufExact.read(&sExact[0], bufExact.getWritePosition());
	a_stream << sExact;


	BSLib::Utility::CStream buffAPPr;
	buffAPPr << m_statistics.size();
	typedef std::map<BSLib::int32, BSLib::int32, std::greater<BSLib::int32> > StatMap;
	for(StatMap::iterator statIt = m_statistics.begin(); statIt != m_statistics.end(); ++statIt)
	{
		buffAPPr << statIt->first;
		buffAPPr << statIt->second;
	}
	std::vector<char> v;
	v.resize(buffAPPr.getWritePosition());
	buffAPPr.read(&v[0], buffAPPr.getWritePosition());
	a_stream << v;
	a_stream << m_refreshTime;
	saveReset();
	return true;
}

void BucketRank::reset()
{
	OrderedRank::reset();
	m_statistics.clear();
}

BSLib::uint32 BucketRank::getSize() const
{
	return m_list.size();
}

void BucketRank::getState(SRoleKey& a_key, std::vector<SRankCell>& a_states, BSLib::int32 a_curParam)
{
	using namespace PlayerSystem::CN;
	if( 0 != a_key.getAccountID() ||
		0 != a_key.getZoneID() || 
		0 != a_key.getIndex())
	{	// 获取指定玩家的信息
		CRoleBaseInfoCN * base = 
			CRoleBaseInfoCNMgr::singleton().getRoleBaseInfoCNByRoleKey(a_key.getDBKey());
		SRankCell info;
		info.m_role = a_key;
		if(NULL != base)
		{	
			info.m_pos = getPlace(a_key, a_curParam);
			info.m_name = base->getRoleName();
			info.m_level = base->getRoleLevel();
			info.m_vip = 0; // todo
			info.m_job = base->getRoleTPID();
			info.m_power = base->getCombat();
			if(!getParam(a_key, info.m_param))
				info.m_param = a_curParam;
		}
		a_states.push_back(info);

		return;
	}


	BSLib::uint32 minSize = m_search.size();
	BSLib::uint32 maxLen = m_capacity;
	minSize = std::min<BSLib::uint32>(minSize, maxLen);
	typedef std::map<BSLib::int32, std::list<SRoleKey>, std::greater<BSLib::int32> >  ContainerType;
	BSLib::uint32 count = 0;
	for(ContainerType::iterator it = m_list.begin(); it != m_list.end(); ++it)
	{
		std::list<SRoleKey>& q = it->second;
		for(std::list<SRoleKey>::iterator subIt = q.begin(); subIt != q.end(); ++subIt)
		{	
			count++; 
			if( count > minSize)
				break;

			CRoleBaseInfoCN * base = 
				CRoleBaseInfoCNMgr::singleton().getRoleBaseInfoCNByRoleKey(subIt->getDBKey());
			SRankCell info;
			info.m_role = *subIt;
			if(NULL != base)
			{	
				info.m_pos = count;
				info.m_name = base->getRoleName();
				info.m_level = base->getRoleLevel();
				info.m_vip = 0; // todo
				info.m_job = base->getRoleTPID();
				info.m_power = base->getCombat();
				info.m_param = it->first;
			}
			a_states.push_back(info);
		}
	}	
}

bool BucketRank::serializeFrom(BSLib::Utility::CStream& a_stream)
{
	a_stream >> m_id;
	BSLib::uint16 dummy;
	a_stream >> dummy;
	BSLib::uint32 type;
	a_stream >> type;

	std::vector<char> sExact;
	a_stream >> sExact;

	BSLib::Utility::CStream exactStream;
	exactStream.write(&sExact[0], sExact.size());

	BSLib::uint32 size  = 0;
	exactStream >> size;
	for(BSLib::uint32 i = 0; i < size; i++)
	{
		SRoleKey key;
		BSLib::int32 v = 0;

		exactStream >> key;
		exactStream >> v;

		OrderedRank::update(key, v);
	}

	std::vector<char> v;
	a_stream >> v;

	BSLib::Utility::CStream appr;
	appr.write(&v[0], v.size());

	appr >> size;
	for(BSLib::uint32 i = 0; i < size; i++)
	{
		BSLib::int32  statK = 0;
		BSLib::int32  statV = 0;
		appr >> statK;
		appr >> statV;

		m_statistics.insert(std::make_pair(statK, statV));
	}
	a_stream >> m_refreshTime;
	saveReset();
	return true;
}

/////////////////////////////////////////////////////////////

ERankType OrderedRankLess::getType()
{
	return ERANKTYPE_ORDEREDLESS;
}

void OrderedRankLess::update(SRoleKey& a_key, BSLib::int32 a_param)
{
	if(_update(a_key, a_param))
		save();
}

bool OrderedRankLess::_update(SRoleKey& a_key, BSLib::int32 a_param)
{	
	BSLib::int32 oldParam = a_param;
	BSLib::int32 newParam = a_param;
	// 先插入后删除多余的,这样逻辑比较清晰
	typedef std::map<BSLib::int32, std::list<SRoleKey>, std::less<BSLib::int32> >  ContainerType;
	std::map<SRoleKey, BSLib::int32>::iterator searchIt = m_search.find(a_key);
	if( searchIt != m_search.end())
	{	// 存在, old value is less
		oldParam = searchIt->second;
		if( oldParam <= newParam)
			return false;

		searchIt->second = newParam;

		// 移除旧的
		ContainerType::iterator containerIt = m_list.find(oldParam);
		if(containerIt != m_list.end())
		{
			std::list<SRoleKey>& oldKeys = containerIt->second;
			std::list<SRoleKey>::iterator delIt = std::find(oldKeys.begin(), oldKeys.end(), a_key);
			if( delIt != oldKeys.end())
				oldKeys.erase(delIt);

			if(oldKeys.empty())
				m_list.erase(containerIt);
		}
		
		// 添加新的
		containerIt = m_list.find(newParam);
		if(containerIt != m_list.end())
		{
			containerIt->second.push_back(a_key);
		}
		else	// new, 创建 rolekey 容器
		{
			std::pair<ContainerType::iterator, bool> resultPair;
			resultPair = m_list.insert(std::make_pair(newParam, std::list<SRoleKey>()));
			containerIt = resultPair.first;
			containerIt->second.push_back(a_key);
		}
	}
	else // 新增的 player
	{	
		m_search.insert(std::make_pair(a_key, newParam));

		ContainerType::iterator containerIt = m_list.find(newParam);
		if(containerIt != m_list.end())
		{
			containerIt->second.push_back(a_key);
		}
		else	// new, 创建 rolekey 容器
		{
			std::pair<ContainerType::iterator, bool> resultPair;
			resultPair = m_list.insert(std::make_pair(oldParam, std::list<SRoleKey>()));
			containerIt = resultPair.first;
			containerIt->second.push_back(a_key);
		}

	}
	
	// 从后端删除

	if(m_search.size() <= m_capacity)
	{
		return true;
	}

	BSLib::uint32 left = m_search.size() - m_capacity;
	while(left--)
	{
		ContainerType::reverse_iterator rit = m_list.rbegin();
		if(rit == m_list.rend())
			continue;
		
		BSLib::uint32 toDel = rit->first;
		ContainerType::iterator it = m_list.find(toDel);
		std::list<SRoleKey>& lastKeys = it->second;
		SRoleKey toDelKey = lastKeys.back();
		lastKeys.pop_back();
		if( lastKeys.empty())
			m_list.erase(it);
		
		std::map<SRoleKey, BSLib::int32>::iterator searchIt = m_search.find(a_key);
		if( searchIt != m_search.end())
		{
			m_search.erase(searchIt);
		}

	}

	return true;
}

bool OrderedRankLess::getParam(SRoleKey& a_key, BSLib::int32 &a_param)
{
	std::map<SRoleKey, BSLib::int32>::iterator searchIt = m_search.find(a_key);
	if( searchIt != m_search.end())
	{	
		a_param =  searchIt->second;
		return true;
	}

	return false;
}

BSLib::uint32 OrderedRankLess::getPlace(SRoleKey& a_key)
{	
	std::map<SRoleKey, BSLib::int32>::iterator searchIt = m_search.find(a_key);
	if( searchIt == m_search.end())
	{	
		return 0;
	}

	BSLib::int32 param = searchIt->second;
	typedef std::map<BSLib::int32, std::list<SRoleKey>, std::less<BSLib::int32> >  ContainerType;
	BSLib::int32 count = 0;
	for(ContainerType::iterator it = m_list.begin(); it != m_list.end(); ++it)
	{
		if( param != it->first)
			count += it->second.size();
		else
		{
			std::list<SRoleKey>& q = it->second;
			for(std::list<SRoleKey>::iterator subIt = q.begin(); subIt != q.end(); ++subIt)
			{	
				count++;
				if(*subIt == a_key)
					break;
			}

			break;
		}
	}

	return count;
}

bool OrderedRankLess::getRole(BSLib::uint32 a_place, SRoleKey& a_key)
{	
	if( 0 == a_place)
		return false;

	if( a_place > m_search.size())
		return false;

	typedef std::map<BSLib::int32, std::list<SRoleKey>, std::less<BSLib::int32> >  ContainerType;
	BSLib::uint32 count = 0;
	for(ContainerType::iterator it = m_list.begin(); it != m_list.end(); ++it)
	{	
		count += it->second.size();
		if( a_place > count)
			continue;

		BSLib::int32 delta = a_place - (count - it->second.size());
		std::list<SRoleKey>& q = it->second;
		for(std::list<SRoleKey>::iterator subIt = q.begin(); subIt != q.end(); ++subIt)
		{	
			delta--;
			if(0 == delta)
			{
				a_key = *subIt;
				return true;
			}
		}
	}

	return false;
}

bool OrderedRankLess::serializeTo(BSLib::Utility::CStream& a_stream)
{
	a_stream << m_id;
	a_stream << BSLib::int16(0);
	BSLib::uint32 type = getType();
	a_stream << type;

	BSLib::Utility::CStream bufExact;
	bufExact << m_search.size();
	std::map<SRoleKey, BSLib::int32>::iterator it = m_search.begin();
	for(; it != m_search.end(); ++it)
	{
		bufExact << it->first;
		bufExact << it->second;
	}

	std::vector<char> sExact;
	sExact.resize(bufExact.getWritePosition());
	bufExact.read(&sExact[0], bufExact.getWritePosition());
	a_stream << sExact;


	std::vector<char> sAppr;
	a_stream << sAppr;
	a_stream << m_refreshTime;
	saveReset();
	return true;
}

void OrderedRankLess::reset()
{	
	Rank::reset();
	m_list.clear();
	m_search.clear();
}

BSLib::uint32 OrderedRankLess::getSize() const
{
	return m_list.size();
}

void OrderedRankLess::getState(SRoleKey& a_key, std::vector<SRankCell>& a_states, BSLib::int32 a_curParam)
{	
	using namespace PlayerSystem::CN;
	if( 0 != a_key.getAccountID() ||
		0 != a_key.getZoneID() || 
		0 != a_key.getIndex())
	{	// 获取指定玩家的信息
		CRoleBaseInfoCN * base = 
			CRoleBaseInfoCNMgr::singleton().getRoleBaseInfoCNByRoleKey(a_key.getDBKey());
		SRankCell info;
		info.m_role = a_key;
		if(NULL != base)
		{	
			info.m_pos = getPlace(a_key);
			info.m_name = base->getRoleName();
			info.m_level = base->getRoleLevel();
			info.m_vip = 0; // todo
			info.m_job = base->getRoleTPID();
			info.m_power = base->getCombat();
			getParam(a_key, info.m_param);
		}
		a_states.push_back(info);

		return;
	}


	BSLib::uint32 minSize = m_search.size();
	BSLib::uint32 maxLen = m_capacity;
	minSize = std::min<BSLib::uint32>(minSize, maxLen);
	typedef std::map<BSLib::int32, std::list<SRoleKey>, std::less<BSLib::int32> >  ContainerType;
	BSLib::uint32 count = 0;
	for(ContainerType::iterator it = m_list.begin(); it != m_list.end(); ++it)
	{
		std::list<SRoleKey>& q = it->second;
		for(std::list<SRoleKey>::iterator subIt = q.begin(); subIt != q.end(); ++subIt)
		{	
			count++; 
			if( count > minSize)
				break;

			CRoleBaseInfoCN * base = 
				CRoleBaseInfoCNMgr::singleton().getRoleBaseInfoCNByRoleKey(subIt->getDBKey());
			SRankCell info;
			info.m_role = *subIt;
			if(NULL != base)
			{	
				info.m_pos = count;
				info.m_name = base->getRoleName();
				info.m_level = base->getRoleLevel();
				info.m_vip = 0; // todo
				info.m_job = base->getRoleTPID();
				info.m_power = base->getCombat();
				info.m_param = it->first;
			}
			a_states.push_back(info);
		}
	}	
}

bool OrderedRankLess::serializeFrom(BSLib::Utility::CStream& a_stream)
{
	a_stream >> m_id;
	BSLib::uint16 dummy;
	a_stream >> dummy;
	BSLib::uint32 type;
	a_stream >> type;

	std::vector<char> sExact;
	a_stream >> sExact;

	BSLib::Utility::CStream exactStream;
	exactStream.write(&sExact[0], sExact.size());

	BSLib::uint32 size  = 0;
	exactStream >> size;
	for(BSLib::uint32 i = 0; i < size; i++)
	{
		SRoleKey key;
		BSLib::int32 v = 0;

		exactStream >> key;
		exactStream >> v;

		_update(key, v);
	}

	std::vector<char> sAppr;
	a_stream >> sAppr;
	a_stream >> m_refreshTime;
	saveReset();
	return true;
}

} // CN
} // RankSystem
} // GSLib