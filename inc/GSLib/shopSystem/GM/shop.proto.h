#ifndef shop_proto_h_header_define
#define shop_proto_h_header_define

#include <GFLib/commonServer/message/message.h>
#include <GSLib/funType.h>
#include <GSLib/serverType.h>
#include <GSLib/baseDef.h>

namespace GSLib {namespace ShopSystem {
  const BSLib::uint32 msgIDShopSystemItemInfo =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_NULL, EFUNCTYPE_SHOPSYSTEM, 10);
  struct ShopSystemItemInfo :public GFLib::CMessage
  {
    BSLib::uint32 id;
    BSLib::uint32 type;
    BSLib::uint32 item_id;
    BSLib::int32 item_num;
    BSLib::uint32 pay_type;
    BSLib::uint32 pay_num;

    ShopSystemItemInfo(): GFLib::CMessage(msgIDShopSystemItemInfo)
    ,id(0)
    ,type(0)
    ,item_id(0)
    ,item_num(0)
    ,pay_type(0)
    ,pay_num(0)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> id;
      stream >> type;
      stream >> item_id;
      stream >> item_num;
      stream >> pay_type;
      stream >> pay_num;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << id;
      stream << type;
      stream << item_id;
      stream << item_num;
      stream << pay_type;
      stream << pay_num;
      return true;
    }

  };

  const BSLib::uint32 msgIDShopSystemAllItemsInfo =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_NULL, EFUNCTYPE_SHOPSYSTEM, 11);
  struct ShopSystemAllItemsInfo :public GFLib::CMessage
  {
    ::std::vector< ::GSLib::ShopSystem::ShopSystemItemInfo> info;

    ShopSystemAllItemsInfo(): GFLib::CMessage(msgIDShopSystemAllItemsInfo)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      {
        BSLib::uint32 len = 0; stream >> len;
        info.resize(len);
        for (std::size_t i = 0 ; i < len ; ++i)
        {
          info[i]._serializeFrom(stream);
        }
      }
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      {
        BSLib::uint32 len = (BSLib::uint32)(info).size();
        stream << len;
        for (::std::vector< ::GSLib::ShopSystem::ShopSystemItemInfo>::const_iterator i = info.begin() ; i != info.end() ; ++i)
        {
          (*i)._serializeTo(stream);
        }
      }
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgShopSystemGC2GMReqOpenCard =
    GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SHOPSYSTEM, 12);
  struct CMsgShopSystemGC2GMReqOpenCard :public GFLib::CMessage
  {
    BSLib::uint32 fun_type;

    CMsgShopSystemGC2GMReqOpenCard(): GFLib::CMessage(msgIDCMsgShopSystemGC2GMReqOpenCard)
    ,fun_type(0)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> fun_type;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << fun_type;
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgShopSystemGM2GCAckOpenCard =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SHOPSYSTEM, 13);
  struct CMsgShopSystemGM2GCAckOpenCard :public GFLib::CMessage
  {
    BSLib::uint32 fun_type;
    BSLib::uint32 glod1_free;
    BSLib::uint32 gold1_next_cost;
    BSLib::uint32 gold10_next_cost;
    BSLib::uint32 diamond1_free;
    BSLib::uint32 diamond1_next_cost;
    BSLib::uint32 diamond10_next_cost;
    BSLib::uint64 gold1_next_secs;
    BSLib::uint64 diamond1_next_secs;

    CMsgShopSystemGM2GCAckOpenCard(): GFLib::CMessage(msgIDCMsgShopSystemGM2GCAckOpenCard)
    ,fun_type(0)
    ,glod1_free(0)
    ,gold1_next_cost(0)
    ,gold10_next_cost(0)
    ,diamond1_free(0)
    ,diamond1_next_cost(0)
    ,diamond10_next_cost(0)
    ,gold1_next_secs(0ULL)
    ,diamond1_next_secs(0ULL)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> fun_type;
      stream >> glod1_free;
      stream >> gold1_next_cost;
      stream >> gold1_next_secs;
      stream >> gold10_next_cost;
      stream >> diamond1_free;
      stream >> diamond1_next_cost;
      stream >> diamond1_next_secs;
      stream >> diamond10_next_cost;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << fun_type;
      stream << glod1_free;
      stream << gold1_next_cost;
      stream << gold1_next_secs;
      stream << gold10_next_cost;
      stream << diamond1_free;
      stream << diamond1_next_cost;
      stream << diamond1_next_secs;
      stream << diamond10_next_cost;
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgShopSystemGC2GMReqEventState =
    GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SHOPSYSTEM, 14);
  struct CMsgShopSystemGC2GMReqEventState :public GFLib::CMessage
  {

    CMsgShopSystemGC2GMReqEventState(): GFLib::CMessage(msgIDCMsgShopSystemGC2GMReqEventState)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgShopSystemGM2GCAckEventState =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SHOPSYSTEM, 15);
  struct CMsgShopSystemGM2GCAckEventState :public GFLib::CMessage
  {
    BSLib::uint32 update_type;
    BSLib::uint32 triggered;
    BSLib::uint32 item_id;
    ::std::vector< BSLib::uint32> event_names;

    CMsgShopSystemGM2GCAckEventState(): GFLib::CMessage(msgIDCMsgShopSystemGM2GCAckEventState)
    ,update_type(0)
    ,triggered(0)
    ,item_id(0)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> update_type;
      {
        BSLib::uint32 len = 0; stream >> len;
        event_names.resize(len);
        for (std::size_t i = 0 ; i < len ; ++i)
        {
          stream >> event_names[i];
        }
      }
      stream >> triggered;
      stream >> item_id;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << update_type;
      {
        BSLib::uint32 len = (BSLib::uint32)(event_names).size();
        stream << len;
        for (::std::vector< BSLib::uint32>::const_iterator i = event_names.begin() ; i != event_names.end() ; ++i)
        {
          stream << *i;
        }
      }
      stream << triggered;
      stream << item_id;
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgShopSystemGC2GMReqClick =
    GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_SHOPSYSTEM, 16);
  struct CMsgShopSystemGC2GMReqClick :public GFLib::CMessage
  {
    BSLib::uint32 fun_type;
    BSLib::uint32 cost_type;

    CMsgShopSystemGC2GMReqClick(): GFLib::CMessage(msgIDCMsgShopSystemGC2GMReqClick)
    ,fun_type(0)
    ,cost_type(0)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> fun_type;
      stream >> cost_type;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << fun_type;
      stream << cost_type;
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgShopSystemGM2GCAckClick =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_SHOPSYSTEM, 17);
  struct CMsgShopSystemGM2GCAckClick :public GFLib::CMessage
  {
    BSLib::uint32 fun_type;
    BSLib::uint32 cost_type;
    BSLib::uint32 result;
    ::std::vector< BSLib::uint32> item_ids;
    ::std::vector< BSLib::uint32> item_nums;

    CMsgShopSystemGM2GCAckClick(): GFLib::CMessage(msgIDCMsgShopSystemGM2GCAckClick)
    ,fun_type(0)
    ,cost_type(0)
    ,result(0)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> fun_type;
      stream >> cost_type;
      stream >> result;
      {
        BSLib::uint32 len = 0; stream >> len;
        item_ids.resize(len);
        for (std::size_t i = 0 ; i < len ; ++i)
        {
          stream >> item_ids[i];
        }
      }
      {
        BSLib::uint32 len = 0; stream >> len;
        item_nums.resize(len);
        for (std::size_t i = 0 ; i < len ; ++i)
        {
          stream >> item_nums[i];
        }
      }
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << fun_type;
      stream << cost_type;
      stream << result;
      {
        BSLib::uint32 len = (BSLib::uint32)(item_ids).size();
        stream << len;
        for (::std::vector< BSLib::uint32>::const_iterator i = item_ids.begin() ; i != item_ids.end() ; ++i)
        {
          stream << *i;
        }
      }
      {
        BSLib::uint32 len = (BSLib::uint32)(item_nums).size();
        stream << len;
        for (::std::vector< BSLib::uint32>::const_iterator i = item_nums.begin() ; i != item_nums.end() ; ++i)
        {
          stream << *i;
        }
      }
      return true;
    }

  };

}}

#endif
