#ifndef gm_proto_h_header_define
#define gm_proto_h_header_define

#include <GFLib/commonServer/message/message.h>
#include <GSLib/funType.h>
#include <GSLib/serverType.h>
#include <GSLib/baseDef.h>

namespace GSLib {namespace MasterSystem {
  const BSLib::uint32 msgIDCMsgMasterSystemXX2XSReqLogin =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANYSERVER, EFUNCTYPE_MASTERSYSTEM, 0);
  struct CMsgMasterSystemXX2XSReqLogin :public GFLib::CMessage
  {
    ::std::string user;
    ::std::string pwd;

    CMsgMasterSystemXX2XSReqLogin(): GFLib::CMessage(msgIDCMsgMasterSystemXX2XSReqLogin)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> user;
      stream >> pwd;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << user;
      stream << pwd;
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgMasterSystemXS2XXAckLogin =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANY, EFUNCTYPE_MASTERSYSTEM, 1);
  struct CMsgMasterSystemXS2XXAckLogin :public GFLib::CMessage
  {
    BSLib::uint32 result;

    CMsgMasterSystemXS2XXAckLogin(): GFLib::CMessage(msgIDCMsgMasterSystemXS2XXAckLogin)
    ,result(0)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> result;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << result;
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgMasterSystemXX2XSReqOnlineZone =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANYSERVER, EFUNCTYPE_MASTERSYSTEM, 2);
  struct CMsgMasterSystemXX2XSReqOnlineZone :public GFLib::CMessage
  {

    CMsgMasterSystemXX2XSReqOnlineZone(): GFLib::CMessage(msgIDCMsgMasterSystemXX2XSReqOnlineZone)
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

  const BSLib::uint32 msgIDCMsgMasterSystemXS2XXAckOnlineZone =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANY, EFUNCTYPE_MASTERSYSTEM, 3);
  struct CMsgMasterSystemXS2XXAckOnlineZone :public GFLib::CMessage
  {
    ::std::vector< ::std::string> keys;

    CMsgMasterSystemXS2XXAckOnlineZone(): GFLib::CMessage(msgIDCMsgMasterSystemXS2XXAckOnlineZone)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      {
        BSLib::uint32 len = 0; stream >> len;
        keys.resize(len);
        for (std::size_t i = 0 ; i < len ; ++i)
        {
          stream >> keys[i];
        }
      }
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      {
        BSLib::uint32 len = (BSLib::uint32)(keys).size();
        stream << len;
        for (::std::vector< ::std::string>::const_iterator i = keys.begin() ; i != keys.end() ; ++i)
        {
          stream << *i;
        }
      }
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgMasterSystemXX2XSReqAccountSearch =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANYSERVER, EFUNCTYPE_MASTERSYSTEM, 4);
  struct CMsgMasterSystemXX2XSReqAccountSearch :public GFLib::CMessage
  {
    BSLib::uint32 stubId;
    ::std::string zone;
    ::std::string accountName;

    CMsgMasterSystemXX2XSReqAccountSearch(): GFLib::CMessage(msgIDCMsgMasterSystemXX2XSReqAccountSearch)
    ,stubId(0)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> stubId;
      stream >> zone;
      stream >> accountName;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << stubId;
      stream << zone;
      stream << accountName;
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgMasterSystemXS2XXAckAccountSearch =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANY, EFUNCTYPE_MASTERSYSTEM, 5);
  struct CMsgMasterSystemXS2XXAckAccountSearch :public GFLib::CMessage
  {
    BSLib::uint32 stubId;
    BSLib::uint32 result;
    BSLib::uint32 channel;
    BSLib::uint32 state;
    BSLib::uint64 accountID;
    BSLib::uint64 regTime;
    ::std::string zone;
    ::std::string accountName;
    ::std::vector< ::std::string> roles;

    CMsgMasterSystemXS2XXAckAccountSearch(): GFLib::CMessage(msgIDCMsgMasterSystemXS2XXAckAccountSearch)
    ,stubId(0)
    ,result(0)
    ,channel(0)
    ,state(0)
    ,accountID(0ULL)
    ,regTime(0ULL)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> stubId;
      stream >> zone;
      stream >> result;
      stream >> accountID;
      stream >> accountName;
      stream >> regTime;
      stream >> channel;
      stream >> state;
      {
        BSLib::uint32 len = 0; stream >> len;
        roles.resize(len);
        for (std::size_t i = 0 ; i < len ; ++i)
        {
          stream >> roles[i];
        }
      }
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << stubId;
      stream << zone;
      stream << result;
      stream << accountID;
      stream << accountName;
      stream << regTime;
      stream << channel;
      stream << state;
      {
        BSLib::uint32 len = (BSLib::uint32)(roles).size();
        stream << len;
        for (::std::vector< ::std::string>::const_iterator i = roles.begin() ; i != roles.end() ; ++i)
        {
          stream << *i;
        }
      }
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgMasterSystemXX2XSReqRoleInfo =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANYSERVER, EFUNCTYPE_MASTERSYSTEM, 6);
  struct CMsgMasterSystemXX2XSReqRoleInfo :public GFLib::CMessage
  {
    BSLib::uint32 stubId;
    ::std::string zone;
    ::std::string role;

    CMsgMasterSystemXX2XSReqRoleInfo(): GFLib::CMessage(msgIDCMsgMasterSystemXX2XSReqRoleInfo)
    ,stubId(0)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> stubId;
      stream >> zone;
      stream >> role;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << stubId;
      stream << zone;
      stream << role;
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgMasterSystemXS2XXAckRoleInfo =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANY, EFUNCTYPE_MASTERSYSTEM, 7);
  struct CMsgMasterSystemXS2XXAckRoleInfo :public GFLib::CMessage
  {
    BSLib::uint32 stubId;
    BSLib::uint32 result;
    BSLib::uint32 roleIndex;
    BSLib::uint32 tpID;
    BSLib::uint32 level;
    BSLib::uint32 diamond;
    BSLib::uint64 accountID;
    BSLib::uint64 exp;
    BSLib::uint64 gold;
    ::std::string zone;
    ::std::string name;
    ::std::vector< ::std::string> friends;

    CMsgMasterSystemXS2XXAckRoleInfo(): GFLib::CMessage(msgIDCMsgMasterSystemXS2XXAckRoleInfo)
    ,stubId(0)
    ,result(0)
    ,roleIndex(0)
    ,tpID(0)
    ,level(0)
    ,diamond(0)
    ,accountID(0ULL)
    ,exp(0ULL)
    ,gold(0ULL)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> stubId;
      stream >> zone;
      stream >> result;
      stream >> accountID;
      stream >> roleIndex;
      stream >> name;
      stream >> tpID;
      stream >> level;
      stream >> exp;
      stream >> gold;
      stream >> diamond;
      {
        BSLib::uint32 len = 0; stream >> len;
        friends.resize(len);
        for (std::size_t i = 0 ; i < len ; ++i)
        {
          stream >> friends[i];
        }
      }
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << stubId;
      stream << zone;
      stream << result;
      stream << accountID;
      stream << roleIndex;
      stream << name;
      stream << tpID;
      stream << level;
      stream << exp;
      stream << gold;
      stream << diamond;
      {
        BSLib::uint32 len = (BSLib::uint32)(friends).size();
        stream << len;
        for (::std::vector< ::std::string>::const_iterator i = friends.begin() ; i != friends.end() ; ++i)
        {
          stream << *i;
        }
      }
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgMasterSystemXX2XSReqAccountForbid =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANYSERVER, EFUNCTYPE_MASTERSYSTEM, 8);
  struct CMsgMasterSystemXX2XSReqAccountForbid :public GFLib::CMessage
  {
    BSLib::uint32 stubId;
    BSLib::uint32 setState;
    ::std::string zone;
    ::std::string accountName;

    CMsgMasterSystemXX2XSReqAccountForbid(): GFLib::CMessage(msgIDCMsgMasterSystemXX2XSReqAccountForbid)
    ,stubId(0)
    ,setState(0)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> stubId;
      stream >> zone;
      stream >> accountName;
      stream >> setState;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << stubId;
      stream << zone;
      stream << accountName;
      stream << setState;
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgMasterSystemXS2XXAckAccountForbid =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANY, EFUNCTYPE_MASTERSYSTEM, 9);
  struct CMsgMasterSystemXS2XXAckAccountForbid :public GFLib::CMessage
  {
    BSLib::uint32 stubId;
    BSLib::uint32 state;
    ::std::string zone;
    ::std::string accountName;

    CMsgMasterSystemXS2XXAckAccountForbid(): GFLib::CMessage(msgIDCMsgMasterSystemXS2XXAckAccountForbid)
    ,stubId(0)
    ,state(0)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> stubId;
      stream >> zone;
      stream >> accountName;
      stream >> state;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << stubId;
      stream << zone;
      stream << accountName;
      stream << state;
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgMasterSystemXX2XSReqAccountPwd =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANYSERVER, EFUNCTYPE_MASTERSYSTEM, 10);
  struct CMsgMasterSystemXX2XSReqAccountPwd :public GFLib::CMessage
  {
    BSLib::uint32 stubId;
    ::std::string zone;
    ::std::string accountName;
    ::std::string pwd;

    CMsgMasterSystemXX2XSReqAccountPwd(): GFLib::CMessage(msgIDCMsgMasterSystemXX2XSReqAccountPwd)
    ,stubId(0)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> stubId;
      stream >> zone;
      stream >> accountName;
      stream >> pwd;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << stubId;
      stream << zone;
      stream << accountName;
      stream << pwd;
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgMasterSystemXS2XXAckAccountPwd =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANY, EFUNCTYPE_MASTERSYSTEM, 11);
  struct CMsgMasterSystemXS2XXAckAccountPwd :public GFLib::CMessage
  {
    BSLib::uint32 stubId;
    BSLib::uint32 result;
    ::std::string zone;
    ::std::string accountName;

    CMsgMasterSystemXS2XXAckAccountPwd(): GFLib::CMessage(msgIDCMsgMasterSystemXS2XXAckAccountPwd)
    ,stubId(0)
    ,result(0)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> stubId;
      stream >> zone;
      stream >> accountName;
      stream >> result;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << stubId;
      stream << zone;
      stream << accountName;
      stream << result;
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgMasterSystemXX2XSReqRoleItemDeduct =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANYSERVER, EFUNCTYPE_MASTERSYSTEM, 12);
  struct CMsgMasterSystemXX2XSReqRoleItemDeduct :public GFLib::CMessage
  {
    BSLib::uint32 stubId;
    BSLib::uint32 itemId;
    BSLib::uint32 itemNum;
    ::std::string zone;
    ::std::string name;

    CMsgMasterSystemXX2XSReqRoleItemDeduct(): GFLib::CMessage(msgIDCMsgMasterSystemXX2XSReqRoleItemDeduct)
    ,stubId(0)
    ,itemId(0)
    ,itemNum(0)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> stubId;
      stream >> zone;
      stream >> name;
      stream >> itemId;
      stream >> itemNum;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << stubId;
      stream << zone;
      stream << name;
      stream << itemId;
      stream << itemNum;
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgMasterSystemXS2XXAckRoleItemDeduct =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANY, EFUNCTYPE_MASTERSYSTEM, 13);
  struct CMsgMasterSystemXS2XXAckRoleItemDeduct :public GFLib::CMessage
  {
    BSLib::uint32 stubId;
    BSLib::uint32 result;
    ::std::string zone;

    CMsgMasterSystemXS2XXAckRoleItemDeduct(): GFLib::CMessage(msgIDCMsgMasterSystemXS2XXAckRoleItemDeduct)
    ,stubId(0)
    ,result(0)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> stubId;
      stream >> zone;
      stream >> result;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << stubId;
      stream << zone;
      stream << result;
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgMasterSystemXX2XSReqMail =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANYSERVER, EFUNCTYPE_MASTERSYSTEM, 14);
  struct CMsgMasterSystemXX2XSReqMail :public GFLib::CMessage
  {
    BSLib::uint32 stubId;
    BSLib::uint32 type;
    ::std::string zone;
    ::std::string sender;
    ::std::vector< ::std::string> roles;
    ::std::string title;
    ::std::string content;
    ::std::vector< BSLib::uint32> itemIds;
    ::std::vector< BSLib::uint32> itemNums;

    CMsgMasterSystemXX2XSReqMail(): GFLib::CMessage(msgIDCMsgMasterSystemXX2XSReqMail)
    ,stubId(0)
    ,type(0)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> stubId;
      stream >> zone;
      stream >> type;
      stream >> sender;
      {
        BSLib::uint32 len = 0; stream >> len;
        roles.resize(len);
        for (std::size_t i = 0 ; i < len ; ++i)
        {
          stream >> roles[i];
        }
      }
      stream >> title;
      stream >> content;
      {
        BSLib::uint32 len = 0; stream >> len;
        itemIds.resize(len);
        for (std::size_t i = 0 ; i < len ; ++i)
        {
          stream >> itemIds[i];
        }
      }
      {
        BSLib::uint32 len = 0; stream >> len;
        itemNums.resize(len);
        for (std::size_t i = 0 ; i < len ; ++i)
        {
          stream >> itemNums[i];
        }
      }
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << stubId;
      stream << zone;
      stream << type;
      stream << sender;
      {
        BSLib::uint32 len = (BSLib::uint32)(roles).size();
        stream << len;
        for (::std::vector< ::std::string>::const_iterator i = roles.begin() ; i != roles.end() ; ++i)
        {
          stream << *i;
        }
      }
      stream << title;
      stream << content;
      {
        BSLib::uint32 len = (BSLib::uint32)(itemIds).size();
        stream << len;
        for (::std::vector< BSLib::uint32>::const_iterator i = itemIds.begin() ; i != itemIds.end() ; ++i)
        {
          stream << *i;
        }
      }
      {
        BSLib::uint32 len = (BSLib::uint32)(itemNums).size();
        stream << len;
        for (::std::vector< BSLib::uint32>::const_iterator i = itemNums.begin() ; i != itemNums.end() ; ++i)
        {
          stream << *i;
        }
      }
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgMasterSystemXS2XXAckMail =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANY, EFUNCTYPE_MASTERSYSTEM, 15);
  struct CMsgMasterSystemXS2XXAckMail :public GFLib::CMessage
  {
    BSLib::uint32 stubId;
    BSLib::uint32 result;
    ::std::string zone;

    CMsgMasterSystemXS2XXAckMail(): GFLib::CMessage(msgIDCMsgMasterSystemXS2XXAckMail)
    ,stubId(0)
    ,result(0)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> stubId;
      stream >> zone;
      stream >> result;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << stubId;
      stream << zone;
      stream << result;
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgMasterSystemXX2XSReqBroadcast =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANYSERVER, EFUNCTYPE_MASTERSYSTEM, 16);
  struct CMsgMasterSystemXX2XSReqBroadcast :public GFLib::CMessage
  {
    BSLib::uint32 stubId;
    ::std::string zone;
    ::std::string content;

    CMsgMasterSystemXX2XSReqBroadcast(): GFLib::CMessage(msgIDCMsgMasterSystemXX2XSReqBroadcast)
    ,stubId(0)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> stubId;
      stream >> zone;
      stream >> content;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << stubId;
      stream << zone;
      stream << content;
      return true;
    }

  };

  const BSLib::uint32 msgIDCMsgMasterSystemXS2XXAckBroadcast =
    GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANY, EFUNCTYPE_MASTERSYSTEM, 17);
  struct CMsgMasterSystemXS2XXAckBroadcast :public GFLib::CMessage
  {
    BSLib::uint32 stubId;
    BSLib::uint32 result;
    ::std::string zone;

    CMsgMasterSystemXS2XXAckBroadcast(): GFLib::CMessage(msgIDCMsgMasterSystemXS2XXAckBroadcast)
    ,stubId(0)
    ,result(0)
    {}

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
      stream >> stubId;
      stream >> zone;
      stream >> result;
      return true;
    }

    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
      stream << stubId;
      stream << zone;
      stream << result;
      return true;
    }

  };

}}

#endif
