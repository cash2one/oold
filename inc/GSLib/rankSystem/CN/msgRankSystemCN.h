#ifndef __GSLIB_RANKSYSTEM_CN_MSGRANKSYSTEMCN_H__
#define __GSLIB_RANKSYSTEM_CN_MSGRANKSYSTEMCN_H__

#include <GSLib/rankSystem/msgNumIDRankSystem.h>

namespace GSLib
{

namespace RankSystem
{

const BSLib::uint32 MsgIDRankSystemGC2CNReqRankList = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_RANKSYSTEM, EMSGNUMID_RANKSYSTEM_GC2CN_REQ_GET_RANK_LIST);
class CMsgRankSystemGC2CNReqRankList: public GFLib::CMessage
{
public:
	CMsgRankSystemGC2CNReqRankList()
	:GFLib::CMessage(MsgIDRankSystemGC2CNReqRankList)
	,m_id(0)
	,m_type(0)
	,m_param(0)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{	
		stream >> m_id;
		stream >> m_type;
		stream >> m_param;
		return true;
	}

public:
	BSLib::uint32 m_id;		// 排行榜id
	BSLib::uint32 m_type;	// 1: 获取排行榜列表, 2:获取自己的位置
	BSLib::int32  m_param;  // 在 m_type == 2 时, 有可能需要此参数, 此参数代表自己的战斗力,积分之类的.
};


const BSLib::uint32 MsgIDRankSystemGM2CNNtfUpdate = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_RANKSYSTEM, EMSGNUMID_RANKSYSTEM_GM2CN_NTF_UPDATE);
class CMsgRankSystemGM2CNNtfUpdate: public GFLib::CMessage
{
public:
	CMsgRankSystemGM2CNNtfUpdate()
		:GFLib::CMessage(MsgIDRankSystemGM2CNNtfUpdate)
		,m_id(0)
		,m_Param(0)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{	
		stream << m_id;
		stream << m_Param;
		m_key.serializeTo(stream);
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{	
		stream >> m_id;
		stream >> m_Param;
		m_key.serializeFrom(stream);
		return true;
	}

public:
	BSLib::uint32	m_id;		// 排行榜id
	BSLib::int32	m_Param;
	SRoleKey		m_key;

};


const BSLib::uint32 MsgIDRankSystemGM2CNNtfInitFinish = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_RANKSYSTEM, EMSGNUMID_RANKSYSTEM_GM2CN_NTF_INIT_FINISH);
class CMsgRankSystemGM2CNNtfInitFinish: public GFLib::CMessage
{
public:
	CMsgRankSystemGM2CNNtfInitFinish()
		:GFLib::CMessage(MsgIDRankSystemGM2CNNtfInitFinish)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{	
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{	
		return true;
	}	
};



}//RankSystem

}//GSLib

#endif//__GSLIB_RANKSYSTEM_CN_MSGRANKSYSTEMCN_H__

