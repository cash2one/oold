#ifndef prize_proto_h_header_define
#define prize_proto_h_header_define

#include <GFLib/commonServer/message/message.h>
#include <GSLib/funType.h>
#include <GSLib/serverType.h>
#include <GSLib/baseDef.h>

namespace GSLib {namespace PrizeSystem {
  const BSLib::uint32 msgIDCMsgPrizeSystemGC2GMReqState =
    GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PRIZESYSTEM, 0);
  struct CMsgPrizeSystemGC2GMReqState :public GFLib::CMessage
  {

    CMsgPrizeSystemGC2GMReqState(): GFLib::CMessage(msgIDCMsgPrizeSystemGC2GMReqState)
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

  const BSLib::uint32 msgIDCMsgPrizeSystemGM2GCAckState =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PRIZESYSTEM, 1);
  struct CMsgPrizeSystemGM2GCAckState :public GFLib::CMessage
  {
    ::std::map< BSLib::uint32,BSLib::int32> states;

    CMsgPrizeSystemGM2GCAckState(): GFLib::CMessage(msgIDCMsgPrizeSystemGM2GCAckState)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      {
        BSLib::uint32 len = 0; stream >> len;
        for (std::size_t i = 0 ; i < len ; ++i)
        {
          BSLib::uint32 first_element;
          BSLib::int32 second_element;
          stream >> first_element;
          stream >> second_element;
          states.insert(::std::make_pair(first_element,second_element));
        }
      }
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      {
        BSLib::uint32 len = (BSLib::uint32)(states).size();
        stream << len;
        for (::std::map< BSLib::uint32,BSLib::int32>::const_iterator i = states.begin() ; i != states.end() ; ++i)
        {
          stream << i->first;
          stream << i->second;
        }
      }
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgPrizeSystemGC2GMReq =
    GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PRIZESYSTEM, 2);
  struct CMsgPrizeSystemGC2GMReq :public GFLib::CMessage
  {
    BSLib::uint32 vip;

    CMsgPrizeSystemGC2GMReq(): GFLib::CMessage(msgIDCMsgPrizeSystemGC2GMReq)
    ,vip(0)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> vip;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << vip;
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgPrizeSystemGM2GCAck =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PRIZESYSTEM, 3);
  struct CMsgPrizeSystemGM2GCAck :public GFLib::CMessage
  {
    BSLib::uint32 vip;
    BSLib::uint32 result;

    CMsgPrizeSystemGM2GCAck(): GFLib::CMessage(msgIDCMsgPrizeSystemGM2GCAck)
    ,vip(0)
    ,result(0)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> vip;
      stream >> result;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << vip;
      stream << result;
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgPrizeSystemGM2GCNtfCharge =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PRIZESYSTEM, 4);
  struct CMsgPrizeSystemGM2GCNtfCharge :public GFLib::CMessage
  {
    BSLib::uint32 id;
    BSLib::int64 time;

    CMsgPrizeSystemGM2GCNtfCharge(): GFLib::CMessage(msgIDCMsgPrizeSystemGM2GCNtfCharge)
    ,id(0)
    ,time(0LL)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> id;
      stream >> time;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << id;
      stream << time;
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgPrizeSystemGC2GMReqTime =
    GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PRIZESYSTEM, 5);
  struct CMsgPrizeSystemGC2GMReqTime :public GFLib::CMessage
  {

    CMsgPrizeSystemGC2GMReqTime(): GFLib::CMessage(msgIDCMsgPrizeSystemGC2GMReqTime)
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

  const BSLib::uint32 msgIDCMsgPrizeSystemGM2GCAckTime =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PRIZESYSTEM, 6);
  struct CMsgPrizeSystemGM2GCAckTime :public GFLib::CMessage
  {
    BSLib::int64 time;

    CMsgPrizeSystemGM2GCAckTime(): GFLib::CMessage(msgIDCMsgPrizeSystemGM2GCAckTime)
    ,time(0LL)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> time;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << time;
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgPrizeSystemGC2GMReqChargeInfo =
    GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PRIZESYSTEM, 7);
  struct CMsgPrizeSystemGC2GMReqChargeInfo :public GFLib::CMessage
  {
    BSLib::uint32 id;

    CMsgPrizeSystemGC2GMReqChargeInfo(): GFLib::CMessage(msgIDCMsgPrizeSystemGC2GMReqChargeInfo)
    ,id(0)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> id;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << id;
      return true;
    }

  };

  const BSLib::uint32 msgIDPrizeSystemState =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_NULL, EFUNCTYPE_PRIZESYSTEM, 8);
  struct PrizeSystemState :public GFLib::CMessage
  {
    BSLib::int32 type;
    BSLib::int32 key;
    BSLib::int32 value;

    PrizeSystemState(): GFLib::CMessage(msgIDPrizeSystemState)
    ,type(0)
    ,key(0)
    ,value(0)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> type;
      stream >> key;
      stream >> value;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << type;
      stream << key;
      stream << value;
      return true;
    }

  };

  const BSLib::uint32 msgIDPrizeSystemChargeInfo =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_NULL, EFUNCTYPE_PRIZESYSTEM, 9);
  struct PrizeSystemChargeInfo :public GFLib::CMessage
  {
    BSLib::uint32 id;
    BSLib::int64 start_time;
    BSLib::int64 end_time;
    ::std::vector< ::GSLib::PrizeSystem::PrizeSystemState> states;

    PrizeSystemChargeInfo(): GFLib::CMessage(msgIDPrizeSystemChargeInfo)
    ,id(0)
    ,start_time(0LL)
    ,end_time(0LL)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> id;
      stream >> start_time;
      stream >> end_time;
      {
        BSLib::uint32 len = 0; stream >> len;
        states.resize(len);
        for (std::size_t i = 0 ; i < len ; ++i)
        {
          states[i]._serializeFrom(stream);
        }
      }
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << id;
      stream << start_time;
      stream << end_time;
      {
        BSLib::uint32 len = (BSLib::uint32)(states).size();
        stream << len;
        for (::std::vector< ::GSLib::PrizeSystem::PrizeSystemState>::const_iterator i = states.begin() ; i != states.end() ; ++i)
        {
          (*i)._serializeTo(stream);
        }
      }
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgPrizeSystemGM2GCAckChargeInfo =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PRIZESYSTEM, 10);
  struct CMsgPrizeSystemGM2GCAckChargeInfo :public GFLib::CMessage
  {
    ::std::vector< ::GSLib::PrizeSystem::PrizeSystemChargeInfo> info;

    CMsgPrizeSystemGM2GCAckChargeInfo(): GFLib::CMessage(msgIDCMsgPrizeSystemGM2GCAckChargeInfo)
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
        for (::std::vector< ::GSLib::PrizeSystem::PrizeSystemChargeInfo>::const_iterator i = info.begin() ; i != info.end() ; ++i)
        {
          (*i)._serializeTo(stream);
        }
      }
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgPrizeSystemGC2GMNtfAction =
    GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PRIZESYSTEM, 11);
  struct CMsgPrizeSystemGC2GMNtfAction :public GFLib::CMessage
  {
    BSLib::uint32 id;

    CMsgPrizeSystemGC2GMNtfAction(): GFLib::CMessage(msgIDCMsgPrizeSystemGC2GMNtfAction)
    ,id(0)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> id;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << id;
      return true;
    }

  };

}}

#endif
