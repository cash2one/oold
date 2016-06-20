
#ifndef __GSLIB_SHOPSYSTEM_MSGSHOPSYSTEMGC_H__
#define __GSLIB_SHOPSYSTEM_MSGSHOPSYSTEMGC_H__

#include <GSLib/shopSystem/msgNumIDShopSystem.h>
#include <GSLib/shopSystem/GM/shop.proto.h>

namespace GSLib
{

namespace ShopSystem
{	
	// 打开窗口返回
	const BSLib::uint32 msgIDShopSystemGM2GCAckShopOpen = 
		GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SHOPSYSTEM, EMSGID_SHOPSYSTEM_GM2GC_ACK_SHOP_OPEN);
	class CMsgShopSystemGM2GCAckShopOpen: public GFLib::CMessage
	{
	public:
		CMsgShopSystemGM2GCAckShopOpen() : GFLib::CMessage(msgIDShopSystemGM2GCAckShopOpen)
			,m_type(ESHOPTYPE_PROP)
			,m_refreshTime(0)
		{

		}

	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{	
			stream << m_type;
			info._serializeTo(stream);
			stream << m_refreshTime;
			return true;
		}

	public:
		EShopType m_type;
		ShopSystemAllItemsInfo info;
		BSLib::uint64 m_refreshTime;
	};



	const BSLib::uint32 msgIDShopSystemGM2GCAckShopBuy = 
		GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SHOPSYSTEM, EMSGID_SHOPSYSTEM_GM2GC_ACK_SHOP_BUY);
	class CMsgShopSystemGM2GCAckShopBuy: public GFLib::CMessage
	{
	public:
		CMsgShopSystemGM2GCAckShopBuy() : GFLib::CMessage(msgIDShopSystemGM2GCAckShopBuy)
			,m_type(ESHOPTYPE_PROP)
			,m_id(0)
			,m_num(0)
			,m_result(ESHOPSYSTEMRESULT_FAILED)
		{

		}

	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{	
			stream << m_type;
			stream << m_id;
			stream << m_num;
			stream << m_result;
			
			return true;
		}

	public:
		EShopType m_type;
		BSLib::int32 m_id;
		BSLib::int32 m_num;		// 剩余购买次数
		EShopSystemResult m_result;
	};



	const BSLib::uint32 msgIDShopSystemGM2GCAckShopRefresh = 
		GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SHOPSYSTEM, EMSGID_SHOPSYSTEM_GM2GC_ACK_SHOP_REFRESH);
	class CMsgShopSystemGM2GCAckShopRefresh: public GFLib::CMessage
	{
	public:
		CMsgShopSystemGM2GCAckShopRefresh() : GFLib::CMessage(msgIDShopSystemGM2GCAckShopRefresh)
			,m_type(ESHOPTYPE_PROP)
			,m_result(ESHOPSYSTEMRESULT_FAILED)
			,m_refreshTime(0)
		{

		}

	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{	
			stream << m_type;
			BSLib::uint32 size = m_ids.size();
			stream << size;
			for(BSLib::uint32 i = 0; i < size; i++){
				stream << m_ids[i];
				stream << m_nums[i];
			}
			stream << m_result;
			stream << m_refreshTime;
			return true;
		}

	public:
		EShopType m_type;
		std::vector<BSLib::int32> m_ids;
		std::vector<BSLib::int32> m_nums;
		EShopSystemResult m_result;
		BSLib::uint64 m_refreshTime;
	};



	const BSLib::uint32 msgIDShopSystemGM2GCAckShopPaidRefresh = 
		GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SHOPSYSTEM, EMSGID_SHOPSYSTEM_GM2GC_ACK_SHOP_PAID_REFRESH);
	class CMsgShopSystemGM2GCAckShopPaidRefresh: public GFLib::CMessage
	{
	public:
		CMsgShopSystemGM2GCAckShopPaidRefresh() : GFLib::CMessage(msgIDShopSystemGM2GCAckShopPaidRefresh)
			,m_type(ESHOPTYPE_PROP)
			,m_result(ESHOPSYSTEMRESULT_FAILED)
		{

		}

	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{	
			stream << m_type;
			BSLib::uint32 size = m_ids.size();
			stream << size;
			for(BSLib::uint32 i = 0; i < size; i++){
				stream << m_ids[i];
				stream << m_nums[i];
			}
			stream << m_result;
			return true;
		}

	public:
		EShopType m_type;
		std::vector<BSLib::int32> m_ids;
		std::vector<BSLib::int32> m_nums;
		EShopSystemResult m_result;
	};




}

}//GSLib

#endif
