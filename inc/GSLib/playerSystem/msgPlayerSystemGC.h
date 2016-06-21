#ifndef __GSLIB_PLAYERSYSTEM_MSGPLAYERSYSTEMGC_H__
#define __GSLIB_PLAYERSYSTEM_MSGPLAYERSYSTEMGC_H__

#include <GSLib/playerSystem/msgNumIDPlayerSystem.h>
#include <GSLib/sceneSystem/GM/sceneGMMgr.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/playerSystem/GM/roleBagModuleGM.h>
namespace GSLib
{

namespace PlayerSystem
{

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDPlayerSystemGM2GCAckPlayerData = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_PLAYERDATA);
class CMsgPlayerSystemGM2GCAckPlayerData: public GFLib::CMessage
{
public:
	CMsgPlayerSystemGM2GCAckPlayerData() : GFLib::CMessage(MsgIDPlayerSystemGM2GCAckPlayerData)
	{
		m_retCode = EINITPLAYERDATA_RESULT_FAIL;
		m_accountName = "";
		m_vipLevel = 0;
		m_roleCount = 0;
	}
protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_retCode;
		stream << m_accountName;
		stream << m_vipLevel;
		stream << m_roleCount;
		stream << m_stream;

		return true;
	}

public:
	void addRoleList(BSLib::Utility::CHashMap<RoleIndex, GSLib::PlayerSystem::GM::CRoleGM*>& roleList)
	{
		m_stream.reset();
		BSLib::Utility::CHashMap<RoleIndex, GSLib::PlayerSystem::GM::CRoleGM*> ::iterator it;
        for (it = roleList.begin(); it != roleList.end(); ++it){
			GSLib::PlayerSystem::GM::CRoleGM *role = it->second;
			if(role != NULL){
				m_stream << role->getRoleIndex();
				m_stream << role->getTPID();
				m_stream << role->getLevel();
				m_stream << role->getName();
			}
	   }
	}

public:
	BSLib::uint32 m_retCode;
	std::string m_accountName;
	BSLib::uint32 m_vipLevel;
	BSLib::uint32 m_roleCount;
	BSLib::Utility::CStream m_stream;
};

const BSLib::uint32 MsgIDPlayerSystemGM2GCAckCreateRole = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_CREATE_ROLE);
class CMsgPlayerSystemGM2GCAckCreateRole: public GFLib::CMessage
{
public:
	CMsgPlayerSystemGM2GCAckCreateRole() : GFLib::CMessage(MsgIDPlayerSystemGM2GCAckCreateRole)
	{
		m_retCode = ECREATEROLE_RESULT_FAIL;
		m_roleIndex = INVALID_ROLEINDEX;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_retCode;
		stream << m_roleIndex;
		stream << m_stream;

		return true;
	}

public:
	BSLib::uint32 m_retCode;
	BSLib::int32 m_roleIndex;
	BSLib::Utility::CStream m_stream;
};

 const BSLib::uint32 MsgIDPlayerSystemGM2GCNtfRoleBattleAttribute = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_UPDATE_ROLE_BATTLEATTRIBUTE);
 class CMsgPlayerSystemGM2GCNtfRoleBattleAttribute: public GFLib::CMessage
 {
 public:
     CMsgPlayerSystemGM2GCNtfRoleBattleAttribute() : GFLib::CMessage(MsgIDPlayerSystemGM2GCNtfRoleBattleAttribute)
     {
     }

 protected:
     bool _serializeTo(BSLib::Utility::CStream& stream) const
     {
         m_battleAttribute.serializeTo(stream);
         stream << m_combat;
		 stream << m_historyMaxCombatPower;
         return true;
     }

 public:
     SBattleAttribute m_battleAttribute;
     BSLib::uint32 m_combat;
	 BSLib::uint32 m_historyMaxCombatPower;
 };


const BSLib::uint32 MsgIDPlayerSystemGM2GCNtfInitRoleData= GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_INIT_ROLEDATA);
class CMsgPlayerSystemGM2GCNtfInitRoleData: public GFLib::CMessage
{
public:
    CMsgPlayerSystemGM2GCNtfInitRoleData() : GFLib::CMessage(MsgIDPlayerSystemGM2GCNtfInitRoleData)
    {
        m_retCode = EINITROLEDATA_RESULT_FAIL;
        m_roleIndex = INVALID_ROLEINDEX;
        m_sceneTpID = DEFAULT_SCENE_TYPEID;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_roleIndex;
        stream << m_sceneTpID;
        stream << m_stream;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::int32 m_roleIndex;
    BSLib::uint32 m_sceneTpID;
    BSLib::Utility::CStream m_stream;
};

const BSLib::uint32 MsgIDPlayerSystemGM2GCAckGetRoleData= GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_GET_ROLEDATA);
class CMsgPlayerSystemGM2GCAckGetRoleData: public GFLib::CMessage
{
public:
    CMsgPlayerSystemGM2GCAckGetRoleData() : GFLib::CMessage(MsgIDPlayerSystemGM2GCAckGetRoleData)
    {
        m_retCode = EGETROLEDATA_RESULT_FAIL;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_stream;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::Utility::CStream m_stream;
};

const BSLib::uint32 MsgIDPlayerSystemGM2GCNtfAddRoleBuf= GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_ADD_ROLEBUF);
class CMsgPlayerSystemGM2GCNtfAddRoleBuf: public GFLib::CMessage
{
public:
    CMsgPlayerSystemGM2GCNtfAddRoleBuf() : GFLib::CMessage(MsgIDPlayerSystemGM2GCNtfAddRoleBuf)
    {
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_stream;
        return true;
    }

public:
    BSLib::Utility::CStream m_stream;
};

const BSLib::uint32 MsgIDPlayerSystemGM2GCAckSelectRole = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_SELECT_ROLE);
class CMsgPlayerSystemGM2GCAckSelectRole: public GFLib::CMessage
{
public:
	CMsgPlayerSystemGM2GCAckSelectRole() : GFLib::CMessage(MsgIDPlayerSystemGM2GCAckSelectRole)
	{
		m_retCode = ESELECTROLE_RESULT_FAIL;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_retCode;
		return true;
	}

public:
	BSLib::uint32 m_retCode;
};

const BSLib::uint32 MsgIDPlayerSystemGM2GCNtfInitBagData = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_INIT_BAGDATA);
class CMsgPlayerSystemGM2GCNtfBagData: public GFLib::CMessage
{
public:
    CMsgPlayerSystemGM2GCNtfBagData() : GFLib::CMessage(MsgIDPlayerSystemGM2GCNtfInitBagData)
    {
        m_bagSize = 0;
        m_usedBagPosCount = 0;
        m_stream.reset();
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_bagSize;
        stream << m_usedBagPosCount;
        stream << m_stream;
        return true;
    }

public:
    BSLib::uint32 m_bagSize;
    BSLib::uint32 m_usedBagPosCount;
    BSLib::Utility::CStream m_stream;
};

const BSLib::uint32 MsgIDPlayerSystemGM2GCAckGetBagData = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_GETBAGDATA);
class CMsgPlayerSystemGM2GCAckGetBagData: public GFLib::CMessage
{
public:
	CMsgPlayerSystemGM2GCAckGetBagData() : GFLib::CMessage(MsgIDPlayerSystemGM2GCAckGetBagData)
	{
		m_retCode = EINITBAGDATA_RESULT_FAIL;
        m_bagSize = 0;
        m_usedBagPosCount = 0;
        m_stream.reset();
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_retCode;
		stream << m_bagSize;
		stream << m_usedBagPosCount;
		stream << m_stream;
		return true;
	}

public:
	BSLib::uint32 m_retCode;
	BSLib::uint32 m_bagSize;
	BSLib::uint32 m_usedBagPosCount;
	BSLib::Utility::CStream m_stream;
};

const BSLib::uint32 MsgIDPlayerSystemGM2GCAckSoldBagItemData = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_SOLDITEM_BAGDATA);
class CMsgPlayerSystemGM2GCAckSoldBagItemData: public GFLib::CMessage
{
public:
	CMsgPlayerSystemGM2GCAckSoldBagItemData() : GFLib::CMessage(MsgIDPlayerSystemGM2GCAckSoldBagItemData)
	{
		m_retCode = ESOLDBAGITEMDATA_RESULT_FAIL;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream <<m_retCode;

		return true;
	}

public:
	BSLib::uint32 m_retCode;
};


const BSLib::uint32 MsgIDPlayerSystemGM2GCAckUseBagItemData = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_USEITEM_BAGDATA);
class CMsgPlayerSystemGM2GCAckUseBagItemData: public GFLib::CMessage
{
public:
	CMsgPlayerSystemGM2GCAckUseBagItemData() : GFLib::CMessage(MsgIDPlayerSystemGM2GCAckUseBagItemData)
	{
		m_retCode = ESOLDBAGITEMDATA_RESULT_FAIL;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream <<m_retCode;
		return true;
	}

public:
	BSLib::uint32 m_retCode;
};

const BSLib::uint32 MsgIDPlayerSystemGM2GCNNtfExpandBagSize = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_EXPAND_BAGSIZE);
class CMsgPlayerSystemGM2GCNtfExpandBagSize: public GFLib::CMessage
{
public:
    CMsgPlayerSystemGM2GCNtfExpandBagSize() : GFLib::CMessage(MsgIDPlayerSystemGM2GCNNtfExpandBagSize)
    {
        m_bagSize = 0;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_bagSize;
        return true;
    }

public:
    BSLib::uint32 m_bagSize;
};

const BSLib::uint32 MsgIDPlayerSystemGM2GCNtfUpdateBagItemData = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_UPDATEITEM_BAGDATA);
class CMsgPlayerSystemGM2GCNtfUpdateBagItemData: public GFLib::CMessage
{
public:
	CMsgPlayerSystemGM2GCNtfUpdateBagItemData() : GFLib::CMessage(MsgIDPlayerSystemGM2GCNtfUpdateBagItemData)
	{
		m_retCode = EUPDATEBAGITEMDATA_RESULT_FAIL;
        m_stream.reset();
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_retCode;
		stream << m_bagItemPositin;
		stream << m_usedBagPositionCount;
		stream << m_bagItemTPID;
		stream << m_itemType;
        stream << m_stream;
		return true;
	}

public:
	BSLib::uint32 m_retCode;
	BSLib::uint32 m_itemType;
	BSLib::uint32 m_bagItemTPID;
	BSLib::uint32 m_bagItemPositin;
	BSLib::uint32 m_usedBagPositionCount;
    BSLib::Utility::CStream m_stream;
};

const BSLib::uint32 MsgIDPlayerSystemGM2GCNtfUpdateUInt32Attribute = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_UPDATE_UINT32ATTRIBUTE);
class CMsgPlayerSystemGM2GCNtfUpdateUInt32Attribute: public GFLib::CMessage
{
public:
	CMsgPlayerSystemGM2GCNtfUpdateUInt32Attribute() : GFLib::CMessage(MsgIDPlayerSystemGM2GCNtfUpdateUInt32Attribute)
	{
		m_reason = EUPDATEATTRIBUTE_REASON_NORMAL;
		m_resID = 0;
		m_value = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream <<m_reason;
		stream <<m_resID;
		stream <<m_value;
		return true;
	}

public:
	BSLib::uint32 m_reason;
	BSLib::uint32 m_resID;
	BSLib::uint32 m_value;
};

const BSLib::uint32 MsgIDPlayerSystemGM2GCNtfUpdateUInt64Attribute = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_UPDATE_UINT64ATTRIBUTE);
class CMsgPlayerSystemGM2GCNtfUpdateUInt64Attribute: public GFLib::CMessage
{
public:
	CMsgPlayerSystemGM2GCNtfUpdateUInt64Attribute() : GFLib::CMessage(MsgIDPlayerSystemGM2GCNtfUpdateUInt64Attribute)
	{
		m_reason = EUPDATEATTRIBUTE_REASON_NORMAL;
        m_resID = 0;
        m_value = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream <<m_reason;
		stream <<m_resID;
		stream <<m_value;
		return true;
	}

public:
    BSLib::uint32 m_reason;
    BSLib::uint32 m_resID;
	BSLib::uint64 m_value;
};


const BSLib::uint32 MsgIDPlayerSystemGM2GCAckUpdateSkillPoint = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_UPDATE_SKILLPOINT);
class CMsgPlayerSystemGM2GCAckUpdateSkillPoint: public GFLib::CMessage
{
public:
	CMsgPlayerSystemGM2GCAckUpdateSkillPoint() : GFLib::CMessage(MsgIDPlayerSystemGM2GCAckUpdateSkillPoint)
	{
		m_retCode = EUPDATESKILLPOINT_RESULT_FAIL;
		m_skillPoint = 0;
		m_updateTime = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_retCode;
		stream << m_skillPoint;
		stream << m_updateTime;
		return true;
	}

public:
	BSLib::uint32 m_retCode;
	BSLib::uint32 m_skillPoint;
	BSLib::uint64 m_updateTime;
};

const BSLib::uint32 MsgIDPlayerSystemGM2GCAckRoleQuit = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_ROLE_QUIT);
class CMsgPlayerSystemGM2GCAckRoleQuit: public GFLib::CMessage
{
public:
	CMsgPlayerSystemGM2GCAckRoleQuit() : GFLib::CMessage(MsgIDPlayerSystemGM2GCAckRoleQuit)
	{
		m_retCode = EROLEQUIT_RESULT_FAIL;
	}
protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_retCode;
		return true;
	}

public:
	BSLib::uint32 m_retCode;
};


const BSLib::uint32 MsgIDPlayerSystemGM2GCAckDeleteRole = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_DELETE_ROLE);
class CMsgPlayerSystemGM2GCAckDeleteRole: public GFLib::CMessage
{
public:
    CMsgPlayerSystemGM2GCAckDeleteRole() : GFLib::CMessage(MsgIDPlayerSystemGM2GCAckDeleteRole)
    {
        m_retCode = EDELETEROLE_RESULT_FAIL;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_roleIndex;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::uint32 m_roleIndex;
};

const BSLib::uint32 MsgIDPlayerSystemGM2GCAckGetVipLevelGift = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_GET_VIPLEVELGIFT);
class CMsgPlayerSystemGM2GCAckGetVipLevelGift: public GFLib::CMessage
{
public:
    CMsgPlayerSystemGM2GCAckGetVipLevelGift() : GFLib::CMessage(MsgIDPlayerSystemGM2GCAckGetVipLevelGift)
    {
        m_retCode = EGETVIPLEVELGIFT_RESULT_FAIL;
        m_vipLevel = 0;
        m_nextVipLevel = -1;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_vipLevel;
        stream << m_nextVipLevel;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::uint32 m_vipLevel;
    BSLib::int32 m_nextVipLevel;
};

const BSLib::uint32 MsgIDPlayerSystemGM2GCAckVipLevelGiftStatus = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_VIPLEVELGIFT_STATUS);
class CMsgPlayerSystemGM2GCAckVipLevelGiftStatus: public GFLib::CMessage
{
public:
    CMsgPlayerSystemGM2GCAckVipLevelGiftStatus() : GFLib::CMessage(MsgIDPlayerSystemGM2GCAckVipLevelGiftStatus)
    {
        m_retCode = EVIPLEVEL_GIFT_STATUS_RESULT_FAIL;
        m_vipLevel = 0;
        m_getStatus = EGETVIPGIFT_STATUS_NO;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_vipLevel;
        stream << m_getStatus;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::uint32 m_vipLevel;
    BSLib::uint32 m_getStatus;
};

const BSLib::uint32 MsgIDPlayerSystemGM2GCNNtfUpdatePlayerVipScore= GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_NTF_UPDATE_PLAYERVIPSCORE);
class CMsgPlayerSystemGM2GCNtfUpdatePlayerVipScore: public GFLib::CMessage
{
public:
    CMsgPlayerSystemGM2GCNtfUpdatePlayerVipScore() : GFLib::CMessage(MsgIDPlayerSystemGM2GCNNtfUpdatePlayerVipScore)
    {
        m_vipScore = 0;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_vipScore;
        return true;
    }

public:
    BSLib::uint32 m_vipScore;
};


const BSLib::uint32 MsgIDPlayerSystemGM2GCAckGetVitality = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_GET_VITALITY);
class CMsgPlayerSystemGM2GCAckGetVitality: public GFLib::CMessage
{
public:
    CMsgPlayerSystemGM2GCAckGetVitality() : GFLib::CMessage(MsgIDPlayerSystemGM2GCAckGetVitality)
    {
        m_retCode = EGETVITALITY_RESULT_FAIL;
        m_vitality = 0;
        m_updateTime = 0;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_vitality;
        stream << m_updateTime;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::uint32 m_vitality;
    BSLib::uint32 m_updateTime;
};


const BSLib::uint32 MsgIDPlayerSystemGM2GCAckBuyVitality = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_BUY_VITALITY);
class CMsgPlayerSystemGM2GCAckBuyVitality: public GFLib::CMessage
{
public:
    CMsgPlayerSystemGM2GCAckBuyVitality() : GFLib::CMessage(MsgIDPlayerSystemGM2GCAckBuyVitality)
    {
        m_retCode = EBUYVITALITY_RESULT_FAIL;
        m_vitality = 0;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_vitality;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::uint32 m_vitality;
};

const BSLib::uint32 MsgIDPlayerSystemGM2GCAckBuyVitalityDiamond = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_GET_BUY_VITALITY_DIAMOND);
class CMsgPlayerSystemGM2GCAckBuyVitalityDiamond: public GFLib::CMessage
{
public:
    CMsgPlayerSystemGM2GCAckBuyVitalityDiamond() : GFLib::CMessage(MsgIDPlayerSystemGM2GCAckBuyVitalityDiamond)
    {
        m_retCode = EGETNEEDDIAMOND_RESULT_FAIL;
        m_diamond = 0;
        m_maxBuyCount = 0;
        m_curBuyCount = 0;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_retCode;
        stream << m_diamond;
        stream << m_maxBuyCount;
        stream << m_curBuyCount;
        return true;
    }

public:
    BSLib::uint32 m_retCode;
    BSLib::uint32 m_diamond;
    BSLib::uint32 m_maxBuyCount;
    BSLib::uint32 m_curBuyCount;
};

const BSLib::uint32 MsgIDPlayerSystemGM2GCAckPurchaseGold = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_PURCHASE_GOLD);
class CMsgPlayerSystemGM2GCAckPurchaseGold: public GFLib::CMessage
{
public:
	CMsgPlayerSystemGM2GCAckPurchaseGold() 
	:GFLib::CMessage(MsgIDPlayerSystemGM2GCAckPurchaseGold)
	,m_result(EPURCHASE_GOLD_RESULT_SUCCESS)
	,m_remainTimes(0)
	,m_maxTimes(0)
	{
	}
protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << (BSLib::uint8)m_result;
		stream << m_remainTimes;
		stream << m_maxTimes;
		return true;
	}
public:
	EPurchaseGoldResult m_result;
	BSLib::uint32 m_remainTimes;
	BSLib::uint32 m_maxTimes;
};               

const BSLib::uint32 MsgIDPlayerSystemGM2GCAckGetPurchaseGoldInfo = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_PLAYERSYSTEM, EMSGNUMID_PLAYERSYSTEM_GM2GC_ACK_GET_PURCHASE_GOLD_INFO);
class CMsgPlayerSystemGM2GCAckGetPurchaseGoldInfo: public GFLib::CMessage
{
public:
	CMsgPlayerSystemGM2GCAckGetPurchaseGoldInfo() 
	:GFLib::CMessage(MsgIDPlayerSystemGM2GCAckGetPurchaseGoldInfo)
	,m_result(EGET_PURCHASE_GOLD_INFO_RESULT_SUCCESS)
	,m_remainTimes(0)
	,m_maxTimes(0)
	{
	}
protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << (BSLib::uint8)m_result;
		stream << m_remainTimes;
		stream << m_maxTimes;
		return true;
	}
public:
	EGetPurchaseGoldInfoResult m_result;
	BSLib::uint32 m_remainTimes;
	BSLib::uint32 m_maxTimes;
};               










}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_MSGPLAYERSYSTEMGC_H__

