#ifndef __GSLIB_PLAYERSYSTEM_GM_MSGPLAYERSYSTEMGM_H__
#define __GSLIB_PLAYERSYSTEM_GM_MSGPLAYERSYSTEMGM_H__


#include <GSLib/playerSystem/msgNumIDPlayerSystem.h>
namespace GSLib
{

namespace PlayerSystem
{

//////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDPlayerSystemGC2GMReqPlayerData= GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_PLAYERDATA);
class CMsgPlayerSystemGC2GMReqPlayerData: public GFLib::CMessage
{
public:
	CMsgPlayerSystemGC2GMReqPlayerData() : GFLib::CMessage(MsgIDPlayerSystemGC2GMReqPlayerData)
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

const BSLib::uint32 MsgIDPlayerSystemGC2GMReqGetBagData = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_GETBAGDATA);
class CMsgPlayerSystemGC2GMReqGetBagData: public GFLib::CMessage
{
public:
    CMsgPlayerSystemGC2GMReqGetBagData() : GFLib::CMessage(MsgIDPlayerSystemGC2GMReqGetBagData)
    {
		m_type = 0;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {	

        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {	
		stream >> m_type;
        return true;
    }

public:
	BSLib::uint32 m_type;
};


const BSLib::uint32 MsgIDPlayerSystemGC2GMReqGetVitality = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_GET_VITALITY);
class CMsgPlayerSystemGC2GMReqGetVitality: public GFLib::CMessage
{
public:
    CMsgPlayerSystemGC2GMReqGetVitality() : GFLib::CMessage(MsgIDPlayerSystemGC2GMReqGetVitality)
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

const BSLib::uint32 MsgIDPlayerSystemGC2GMReqBuyVitality = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_BUY_VITALITY);
class CMsgPlayerSystemGC2GMReqBuyVitality: public GFLib::CMessage
{
public:
    CMsgPlayerSystemGC2GMReqBuyVitality() : GFLib::CMessage(MsgIDPlayerSystemGC2GMReqBuyVitality)
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

const BSLib::uint32 MsgIDPlayerSystemGC2GMReqBuyVitalityDiamond = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_GET_BUY_VITALITY_DIAMOND);
class CMsgPlayerSystemGC2GMReqBuyVitalityDiamond: public GFLib::CMessage
{
public:
    CMsgPlayerSystemGC2GMReqBuyVitalityDiamond() : GFLib::CMessage(MsgIDPlayerSystemGC2GMReqBuyVitalityDiamond)
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

const BSLib::uint32 MsgIDPlayerSystemGC2GMReqCreateRole = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_CREATE_ROLE);
class CMsgPlayerSystemGC2GMReqCreateRole: public GFLib::CMessage
{
public:
	CMsgPlayerSystemGC2GMReqCreateRole() : GFLib::CMessage(MsgIDPlayerSystemGC2GMReqCreateRole)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_roleType;
		stream << m_roleName;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_roleType;
		stream >> m_roleName;
		return true;
	}

public:
	std::string m_roleName;
	BSLib::uint32 m_roleType;
};


const BSLib::uint32 MsgIDPlayerSystemGC2GMReqSelectRole = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_SELECT_ROLE);
class CMsgPlayerSystemGC2GMReqSelectRole: public GFLib::CMessage
{
public:
	CMsgPlayerSystemGC2GMReqSelectRole() : GFLib::CMessage(MsgIDPlayerSystemGC2GMReqSelectRole)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_roleIndex;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_roleIndex;
		return true;
	}

public:
	BSLib::uint32 m_roleIndex;
};

const BSLib::uint32 MsgIDPlayerSystemGC2GMReqSoldBagItemData= GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_SOLDITEM_BAGDATA);
class CMsgPlayerSystemGC2GMReqSoldBagItemData : public GFLib::CMessage
{
public:
	CMsgPlayerSystemGC2GMReqSoldBagItemData() : GFLib::CMessage(MsgIDPlayerSystemGC2GMReqSoldBagItemData)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_itemType;
		stream << m_index;
		stream << m_itemCount;

		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_itemType;
		stream >> m_index;
		stream >> m_itemCount;

		return true;
	}

public:
	BSLib::uint32 m_itemCount;
	BSLib::uint32 m_index;
	BSLib::uint32 m_itemType;
};

const BSLib::uint32 MsgIDPlayerSystemGC2GMReqUseBagItemData= GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_USEITEM_BAGDATA);
class CMsgPlayerSystemGC2GMReqUseBagItemData : public GFLib::CMessage
{
public:
	CMsgPlayerSystemGC2GMReqUseBagItemData() : GFLib::CMessage(MsgIDPlayerSystemGC2GMReqUseBagItemData)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_itemType;
		stream << m_index;

		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_itemType;
		stream >> m_index;

		return true;
	}

public:
	BSLib::uint32 m_index;
	BSLib::uint32 m_itemType;

};

const BSLib::uint32 MsgIDPlayerSystemGC2GMReqUpdateSkillPoint = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_UPDATE_SKILLPOINT);
class CMsgPlayerSystemGC2GMReqUpdateSkillPoint : public GFLib::CMessage
{
public:
	CMsgPlayerSystemGC2GMReqUpdateSkillPoint() : GFLib::CMessage(MsgIDPlayerSystemGC2GMReqUpdateSkillPoint)
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

const BSLib::uint32 MsgIDPlayerSystemGM2CNReqCreateRole = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2CN_REQ_CREATE_ROLE);
class CMsgPlayerSystemGM2CNReqCreateRole: public GFLib::CMessage
{
public:
	CMsgPlayerSystemGM2CNReqCreateRole() : GFLib::CMessage(MsgIDPlayerSystemGM2CNReqCreateRole)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_accountKey;
        stream << m_stream;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_accountKey;
        stream >> m_stream;
		return true;
	}

public:	
	GFLib::SAccountKey m_accountKey;
    BSLib::Utility::CStream m_stream;

};

const BSLib::uint32 MsgIDPlayerSystemGM2CNNtfUpdateRoleData = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2CN_NTF_UPDATE_ROLEDATA);
class CMsgPlayerSystemGM2CNNtfUpdateRoleData: public GFLib::CMessage
{
public:
    CMsgPlayerSystemGM2CNNtfUpdateRoleData() : GFLib::CMessage(MsgIDPlayerSystemGM2CNNtfUpdateRoleData)
    {
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_stream;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_stream;
        return true;
    }

public:	
    BSLib::Utility::CStream m_stream;

};

const BSLib::uint32 MsgIDPlayerSystemGM2CNReqGetRoleData = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2CN_REQ_GET_ROLEDATA);
class CMsgPlayerSystemGM2CNReqGetRoleData: public GFLib::CMessage
{
public:
    CMsgPlayerSystemGM2CNReqGetRoleData() : GFLib::CMessage(MsgIDPlayerSystemGM2CNReqGetRoleData)
    {
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_roleKey;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_roleKey;
        return true;
    }

public:	
    GSLib::SRoleKey m_roleKey;

};

const BSLib::uint32 MsgIDPlayerSystemGM2CNReqInitPlayerData = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2CN_REQ_INIT_PLAYERDATA);
class CMsgPlayerSystemGM2CNReqInitPlayerData: public GFLib::CMessage
{
public:
	CMsgPlayerSystemGM2CNReqInitPlayerData() : GFLib::CMessage(MsgIDPlayerSystemGM2CNReqInitPlayerData)
	{
		m_vipLevel = 0;
		m_roleCount = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_accountKey;
		stream << m_vipLevel;
		stream << m_roleCount;
		stream << m_stream;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_accountKey;
		stream >> m_vipLevel;
		stream >> m_roleCount;
		stream >> m_stream;
		return true;
	}


public:
	GFLib::SAccountKey m_accountKey;
	BSLib::uint32 m_vipLevel;
	BSLib::uint32 m_roleCount;
	BSLib::Utility::CStream m_stream;
};


const BSLib::uint32 MsgIDPlayerSystemCN2GMAckInitPlayerData = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_CN2GM_ACK_INIT_PLAYERDATA);
class CMsgPlayerSystemCN2GMAckInitPlayerData: public GFLib::CMessage
{
public:
	CMsgPlayerSystemCN2GMAckInitPlayerData() : GFLib::CMessage(MsgIDPlayerSystemCN2GMAckInitPlayerData)
	{
		m_state = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_state;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_state;
		return true;
	}

public:	
	BSLib::uint32 m_state;
};


const BSLib::uint32 MsgIDPlayerSystemCN2GMAckCreateRole = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_CN2GM_ACK_CREATE_ROLE);
class CMsgPlayerSystemCN2GMAckCreateRole: public GFLib::CMessage
{
public:
    CMsgPlayerSystemCN2GMAckCreateRole() : GFLib::CMessage(MsgIDPlayerSystemCN2GMAckCreateRole)
    {
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_state;
        stream << m_roleIndex;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_state;
        stream >> m_roleIndex;
        return true;
    }

public:
    BSLib::uint32 m_state;
    BSLib::int32 m_roleIndex;
};


const BSLib::uint32 MsgIDPlayerSystemCN2GMAckGetRoleData = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_CN2GM_ACK_GET_ROLEDATA);
class CMsgPlayerSystemCN2GMAckGetRoleData: public GFLib::CMessage
{
public:
    CMsgPlayerSystemCN2GMAckGetRoleData() : GFLib::CMessage(MsgIDPlayerSystemCN2GMAckGetRoleData)
    {
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_state;
        stream << m_stream;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_state;
        stream >> m_stream;
        return true;
    }

public:
    BSLib::uint32 m_state;
    BSLib::Utility::CStream m_stream;
};

const BSLib::uint32 MsgIDPlayerSystemGM2CNReqSelectRole = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2CN_REQ_SELECT_ROLE);
class CMsgPlayerSystemGM2CNReqSelectRole: public GFLib::CMessage
{
public:
	CMsgPlayerSystemGM2CNReqSelectRole() : GFLib::CMessage(MsgIDPlayerSystemGM2CNReqSelectRole)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_roleIndex;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_roleIndex;
		return true;
	}

public:
	BSLib::uint32 m_roleIndex;
};

const BSLib::uint32 MsgIDPlayerSystemCN2GMAckSelectRole = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_CN2GM_ACK_SELECT_ROLE);
class CMsgPlayerSystemCN2GMAckSelectRole: public GFLib::CMessage
{
public:
	CMsgPlayerSystemCN2GMAckSelectRole() : GFLib::CMessage(MsgIDPlayerSystemCN2GMAckSelectRole)
	{
		m_state = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_state;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_state;
		return true;
	}

public:	
	BSLib::uint32 m_state;
};


const BSLib::uint32 MsgIDPlayerSystemGM2CNReqRoleQuit = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2CN_REQ_ROLE_QUIT);
class CMsgPlayerSystemGM2CNReqRoleQuit: public GFLib::CMessage
{
public:
	CMsgPlayerSystemGM2CNReqRoleQuit() : GFLib::CMessage(MsgIDPlayerSystemGM2CNReqRoleQuit)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_roleIndex;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_roleIndex;
		return true;
	}

public:
	BSLib::uint32 m_roleIndex;
};

const BSLib::uint32 MsgIDPlayerSystemCN2GMAckRoleQuit = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_CN2GM_ACK_ROLE_QUIT);
class CMsgPlayerSystemCN2GMAckRoleQuit: public GFLib::CMessage
{
public:
	CMsgPlayerSystemCN2GMAckRoleQuit() : GFLib::CMessage(MsgIDPlayerSystemCN2GMAckRoleQuit)
	{
		m_state = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_state;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_state;
		return true;
	}

public:	
	BSLib::uint32 m_state;
};


const BSLib::uint32 MsgIDPlayerSystemGC2GMReqRoleQuit = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_ROLE_QUIT);
class CMsgPlayerSystemGC2GMReqRoleQuit: public GFLib::CMessage
{
public:
	CMsgPlayerSystemGC2GMReqRoleQuit() : GFLib::CMessage(MsgIDPlayerSystemGC2GMReqRoleQuit)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_roleIndex;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_roleIndex;
		return true;
	}

public:
	BSLib::int32 m_roleIndex;
};


const BSLib::uint32 MsgIDPlayerSystemGC2GMReqGetRoleData = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_GET_ROLEDATA);
class CMsgPlayerSystemGC2GMReqRoleGetRoleData: public GFLib::CMessage
{
public:
    CMsgPlayerSystemGC2GMReqRoleGetRoleData() : GFLib::CMessage(MsgIDPlayerSystemGC2GMReqGetRoleData)
    {
    }
protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_roleKey;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_roleKey;
        return true;
    }

public:	
    GSLib::SRoleKey m_roleKey;

};



const BSLib::uint32 MsgIDPlayerSystemGC2GMReqDeleteRole = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_DELETE_ROLE);
class CMsgPlayerSystemGC2GMReqDeleteRole: public GFLib::CMessage
{
public:
    CMsgPlayerSystemGC2GMReqDeleteRole() : GFLib::CMessage(MsgIDPlayerSystemGC2GMReqDeleteRole)
    {
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_roleIndex;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_roleIndex;
        return true;
    }

public:
    BSLib::uint32 m_roleIndex;
};

const BSLib::uint32 MsgIDPlayerSystemGC2GMReqGetVipLevelGift = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_GET_VIPLEVELGIFT);
class CMsgPlayerSystemGC2GMReqGetVipLevelGift: public GFLib::CMessage
{
public:
    CMsgPlayerSystemGC2GMReqGetVipLevelGift() : GFLib::CMessage(MsgIDPlayerSystemGC2GMReqGetVipLevelGift)
    {
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_vipLevel;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_vipLevel;
        return true;
    }

public:
    BSLib::uint32 m_vipLevel;
};

const BSLib::uint32 MsgIDPlayerSystemGC2GMReqVipLevelGiftStatus = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_VIPLEVELGIFT_STATUS);
class CMsgPlayerSystemGC2GMReqVipLevelGiftStatus: public GFLib::CMessage
{
public:
    CMsgPlayerSystemGC2GMReqVipLevelGiftStatus() : GFLib::CMessage(MsgIDPlayerSystemGC2GMReqVipLevelGiftStatus)
    {
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_vipLevel;
        return true;
    }

    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_vipLevel;
        return true;
    }

public:
    BSLib::uint32 m_vipLevel;
};



const BSLib::uint32 MsgIDPlayerSystemGC2GMReqPurchaseGold = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_PURCHASE_GOLD);
class CMsgPlayerSystemGC2GMReqPurchaseGold : public GFLib::CMessage
{
public:
	CMsgPlayerSystemGC2GMReqPurchaseGold() : GFLib::CMessage(MsgIDPlayerSystemGC2GMReqPurchaseGold)
	{
	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		return true;
	}

};                     


const BSLib::uint32 MsgIDPlayerSystemGC2GMReqGetPurchaseGoldInfo = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GC2GM_REQ_GET_PURCHASE_GOLD_INFO);
class CMsgPlayerSystemGC2GMReqGetPurchaseGoldInfo : public GFLib::CMessage
{
public:
	CMsgPlayerSystemGC2GMReqGetPurchaseGoldInfo() : GFLib::CMessage(MsgIDPlayerSystemGC2GMReqGetPurchaseGoldInfo)
	{
	}
protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		return true;
	}

};                     

const BSLib::uint32 MsgIDPlayerSystemDB2GMNtfChargeList = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_DB2GM_NTF_CHARGE_LIST);
class CMsgPlayerSystemDB2GMNtfChargeList: public GFLib::CMessage
{
public:
	CMsgPlayerSystemDB2GMNtfChargeList() : GFLib::CMessage(MsgIDPlayerSystemDB2GMNtfChargeList)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_roleKey;
		stream << m_chargeList;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_roleKey;
		stream >> m_chargeList;
		return true;
	}

public:
	SRoleKey m_roleKey;
	std::vector<SChargeList> m_chargeList;
};

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_GM_MSGPLAYERSYSTEMGM_H__

