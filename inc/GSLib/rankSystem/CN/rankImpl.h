#ifndef __GSLIB_RANKSYSTEM_CN_RANKIMPL_H__
#define __GSLIB_RANKSYSTEM_CN_RANKIMPL_H__
#include <GSLib/rankSystem/CN/rank.h>
#include <xfunctional>

namespace GSLib
{
namespace RankSystem
{
namespace CN
{

class OrderedRank
	:public Rank
{	
public:
	OrderedRank(BSLib::uint64 a_id, BSLib::uint32 a_size) :Rank(a_id, a_size) {}
	virtual ERankType getType();
	virtual void update(SRoleKey& a_key, BSLib::int32 a_param);
	virtual void update(SRoleKey& a_key, SRoleKey& a_other) {}
	virtual void update(SRoleKey& a_key, BSLib::int32 a_preParam, BSLib::int32 a_curParam) {}
	virtual bool getParam(SRoleKey& a_key, BSLib::int32 &a_param);
	virtual BSLib::uint32 getPlace(SRoleKey& a_key, BSLib::int32 a_curParam) {return 0;}
	virtual BSLib::uint32 getPlace(SRoleKey& a_key);
	virtual bool getRole(BSLib::uint32 a_place, SRoleKey& a_key);
	virtual bool serializeTo(BSLib::Utility::CStream& a_stream);
	virtual bool serializeFrom(BSLib::Utility::CStream& a_stream);
	virtual void getState(SRoleKey& a_key, std::vector<SRankCell>& a_states, BSLib::int32 a_curParam);
	virtual void reset();
	virtual BSLib::uint32 getSize() const;

	
private:
	bool _update(SRoleKey& a_key, BSLib::int32 a_param);

protected:
	std::map<BSLib::int32, std::list<SRoleKey>, std::greater<BSLib::int32> > m_list;
	std::map<SRoleKey, BSLib::int32> m_search;
};


class BucketRank
	:public OrderedRank
{	
public:
	BucketRank(BSLib::uint64 a_id, BSLib::uint32 a_size): OrderedRank(a_id, a_size) {}
	virtual ERankType getType();
	virtual void update(SRoleKey& a_key, BSLib::int32 a_param) {}
	virtual void update(SRoleKey& a_key, SRoleKey& a_other) {}
	virtual void update(SRoleKey& a_key, BSLib::int32 a_preParam, BSLib::int32 a_curParam);
	virtual bool getParam(SRoleKey& a_key, BSLib::int32 &a_param);
	virtual BSLib::uint32 getPlace(SRoleKey& a_key) {return 0;}
	virtual BSLib::uint32 getPlace(SRoleKey& a_key, BSLib::int32 a_curParam);
	virtual bool getRole(BSLib::uint32 a_place, SRoleKey& a_key);
	virtual bool serializeTo(BSLib::Utility::CStream& a_stream);
	virtual bool serializeFrom(BSLib::Utility::CStream& a_stream);
	virtual void getState(SRoleKey& a_key, std::vector<SRankCell>& a_states, BSLib::int32 a_curParam);
	virtual void reset();
	virtual BSLib::uint32 getSize() const;

protected:
	std::map<BSLib::int32, BSLib::int32, std::greater<BSLib::int32> > m_statistics;
};


class TranspositionRank
	:public Rank
{	
public:
	TranspositionRank(BSLib::uint64 a_id, BSLib::uint32 a_size) :Rank(a_id, a_size) { m_list.reserve(a_size);}
	virtual ERankType getType();
	virtual void update(SRoleKey& a_key, BSLib::int32 a_param){}
	virtual void update(SRoleKey& a_key, SRoleKey& a_other); // a_other 值为0 代表首次进入
	virtual void update(SRoleKey& a_key, BSLib::int32 a_preParam, BSLib::int32 a_curParam) {}
	virtual bool getParam(SRoleKey& a_key, BSLib::int32 &a_param) { return false;}
	virtual BSLib::uint32 getPlace(SRoleKey& a_key);
	virtual BSLib::uint32 getPlace(SRoleKey& a_key, BSLib::int32 a_curParam) {return 0;}
	virtual bool getRole(BSLib::uint32 a_place, SRoleKey& a_key);
	virtual bool serializeTo(BSLib::Utility::CStream& a_stream);
	virtual bool serializeFrom(BSLib::Utility::CStream& a_stream);
	virtual void getState(SRoleKey& a_key, std::vector<SRankCell>& a_states, BSLib::int32 a_curParam);
	virtual void reset();
	virtual BSLib::uint32 getSize() const;

	void synPlace(SRoleKey &a_key);

protected:
	std::map<SRoleKey, BSLib::int32> m_search;
	std::vector<SRoleKey> m_list;
};


class OrderedRankLess
	:public Rank
{	
public:
	OrderedRankLess(BSLib::uint64 a_id, BSLib::uint32 a_size) :Rank(a_id, a_size) {}
	virtual ERankType getType();
	virtual void update(SRoleKey& a_key, BSLib::int32 a_param);
	virtual void update(SRoleKey& a_key, SRoleKey& a_other) {}
	virtual void update(SRoleKey& a_key, BSLib::int32 a_preParam, BSLib::int32 a_curParam) {}
	virtual bool getParam(SRoleKey& a_key, BSLib::int32 &a_param);
	virtual BSLib::uint32 getPlace(SRoleKey& a_key, BSLib::int32 a_curParam) {return 0;}
	virtual BSLib::uint32 getPlace(SRoleKey& a_key);
	virtual bool getRole(BSLib::uint32 a_place, SRoleKey& a_key);
	virtual bool serializeTo(BSLib::Utility::CStream& a_stream);
	virtual bool serializeFrom(BSLib::Utility::CStream& a_stream);
	virtual void getState(SRoleKey& a_key, std::vector<SRankCell>& a_states, BSLib::int32 a_curParam);
	virtual void reset();
	virtual BSLib::uint32 getSize() const;


private:
	bool _update(SRoleKey& a_key, BSLib::int32 a_param);

protected:
	std::map<BSLib::int32, std::list<SRoleKey>, std::less<BSLib::int32> > m_list;
	std::map<SRoleKey, BSLib::int32> m_search;
};



} // CN
} // RankSystem
} // GSLib


#endif // __GSLIB_RANKSYSTEM_CN_RANKIMPL_H__
