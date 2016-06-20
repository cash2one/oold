#ifndef __GSLIB_RANKSYSTEM_CN_RANK_H__
#define __GSLIB_RANKSYSTEM_CN_RANK_H__
#include <GSLib/baseDef.h>
#include <GSLib/rankSystem/cmmhdr.h>
#include <BSLib/utility/dateTime.h>

namespace GSLib
{
namespace RankSystem
{
namespace CN
{

class Rank
{
public:
	Rank(BSLib::uint64 a_id, BSLib::uint32 a_size) :m_id(a_id),m_capacity(a_size),m_needSave(true)
			{ m_refreshTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();}
	Rank() :m_id(0),m_capacity(0),m_needSave(false),m_refreshTime(0)
		{ m_refreshTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();}
	
	virtual ERankType getType()										= 0;
	virtual void update(SRoleKey& a_key, BSLib::int32 a_param)		= 0;
	virtual void update(SRoleKey& a_key, SRoleKey& a_other)			= 0;
	virtual void update(SRoleKey& a_key, BSLib::int32 a_preParam, BSLib::int32 a_curParam) = 0;

	virtual bool getParam(SRoleKey& a_key, BSLib::int32 &a_param)	= 0;
	virtual BSLib::uint32 getPlace(SRoleKey& a_key)					= 0;
	virtual BSLib::uint32 getPlace(SRoleKey& a_key, BSLib::int32 a_curParam)				= 0;
	virtual bool getRole(BSLib::uint32 a_place, SRoleKey& a_key)	= 0;

	virtual bool serializeTo(BSLib::Utility::CStream& a_stream)		= 0;
	virtual bool serializeFrom(BSLib::Utility::CStream& a_stream)	= 0;
	virtual void getState(SRoleKey& a_key, std::vector<SRankCell>& a_states, BSLib::int32 a_curParam)	= 0;
	virtual void reset() {  m_refreshTime = BSLib::Utility::CDateTime::getCurrentTime().getSeconds(); save();}
	virtual BSLib::uint32 getSize() const	= 0;

	BSLib::uint64 getRefreshTime() { return m_refreshTime;}
	void setRefreshTime(BSLib::uint64 a_time) { m_refreshTime = a_time; }
	std::string getDBKey()
	{
		std::string key;
		key.append((char*)&m_id, sizeof(m_id));
		BSLib::uint16 zoneId(0);
		key.append((char*)&zoneId, sizeof(zoneId));
		BSLib::uint32 type = getType();
		key.append((char*)&type, sizeof(type));
		return key;
	}
	BSLib::uint64 getId() { return m_id; }
	bool isNeedSave() { return m_needSave;}

protected:
	void saveReset() { m_needSave = false;};
	void save() {m_needSave = true;}

protected:
	BSLib::uint64 m_id;
	BSLib::uint32 m_capacity;
	bool		  m_needSave;
	BSLib::uint64 m_refreshTime;
};


} // CN
} // RankSystem
} // GSLib


#endif // __GSLIB_RANKSYSTEM_CN_RANK_H__
