
#ifndef __GSLIB_SHOPSYSTEM_MSGSHOPSYSTEMGM_H__
#define __GSLIB_SHOPSYSTEM_MSGSHOPSYSTEMGM_H__

#include <GSLib/shopSystem/msgNumIDShopSystem.h>

namespace GSLib
{

namespace ShopSystem
{	

const BSLib::uint32 msgIDShopSystemGC2GMReqShopOpen = 
	GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SHOPSYSTEM, EMSGID_SHOPSYSTEM_GC2GM_REQ_SHOP_OPEN);
class CMsgShopSystemGC2GMReqShopOpen: public GFLib::CMessage
{
public:
	CMsgShopSystemGC2GMReqShopOpen() : GFLib::CMessage(msgIDShopSystemGC2GMReqShopOpen)
		,m_type(ESHOPTYPE_PROP)
	{

	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{	
		stream >> m_type;
		return true;
	}

public:
	EShopType m_type;
};

const BSLib::uint32 msgIDShopSystemGC2GMReqShopBuy = 
	GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SHOPSYSTEM, EMSGID_SHOPSYSTEM_GC2GM_REQ_SHOP_BUY);
class CMsgShopSystemGC2GMReqShopBuy: public GFLib::CMessage
{
public:
	CMsgShopSystemGC2GMReqShopBuy() : GFLib::CMessage(msgIDShopSystemGC2GMReqShopBuy)
		,m_type(ESHOPTYPE_PROP)
		,m_id(0)
		,m_num(0)
	{

	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{	
		stream >> m_type;
		stream >> m_id;
		stream >> m_num;
		return true;
	}

public:
	EShopType m_type;
	BSLib::int32 m_id;
	BSLib::int32 m_num;
};

const BSLib::uint32 msgIDShopSystemGC2GMReqShopRefresh = 
	GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SHOPSYSTEM, EMSGID_SHOPSYSTEM_GC2GM_REQ_SHOP_REFRESH);
class CMsgShopSystemGC2GMReqShopRefresh: public GFLib::CMessage
{
public:
	CMsgShopSystemGC2GMReqShopRefresh() : GFLib::CMessage(msgIDShopSystemGC2GMReqShopRefresh)
		,m_type(ESHOPTYPE_PROP)
	{

	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{	
		stream >> m_type;
		return true;
	}

public:
	EShopType m_type;
};


const BSLib::uint32 msgIDShopSystemGC2GMReqShopPaidRefresh = 
	GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SHOPSYSTEM, EMSGID_SHOPSYSTEM_GC2GM_REQ_SHOP_PAID_REFRESH);
class CMsgShopSystemGC2GMReqShopPaidRefresh: public GFLib::CMessage
{
public:
	CMsgShopSystemGC2GMReqShopPaidRefresh() : GFLib::CMessage(msgIDShopSystemGC2GMReqShopPaidRefresh)
		,m_type(ESHOPTYPE_PROP)
	{

	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{	
		stream >> m_type;
		return true;
	}

public:
	EShopType m_type;
};

}

}//GSLib

#endif
