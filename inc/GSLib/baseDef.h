#ifndef __GSLIB_BASEDEF_H__
#define __GSLIB_BASEDEF_H__

#include <GFLib/commonServer/baseDef.h>
#include <BSLib/utility/eventMgr.h>
#include <BSLib/utility/convert.h>

#define GSLIB_TEXT_MAX_ACCOUNT_NAME	64
#define GSLIB_TEXT_MAX_ACCOUNT_PASSWORD 64
#define GSLIB_TEXT_MAX_ACCOUNT_UNIQUEID 64
#define GSLIB_TEXT_MAX_ACCOUNT_UNIQUEKEY 64
#define GSLIB_TEXT_MAX_PLATFORM 64
#define GSLIB_TEXT_MAX_ROLE_NAME 64


#define GSLIB_SESSIONID_INIT_GLOBALDATA  1

#define GSLIB_SESSIONID_CHECK_ROLENAME      1       // 校验角色名
#define GSLIB_SESSIONID_GET_ROLEID          2       // 获取角色名
#define GSLIB_SESSIONID_CREATE_ROLE_FINISH  3       // 角色创建完成
#define GSLIB_SESSIONID_GET_ROLE_ALL_DATA   4       // 获取角色数据

#define MAX_ROLE_INDEX BSLIB_INT32_MAX              // 角色索引最大分配值
namespace GSLib
{
typedef BSLib::uint64 EntityID;
typedef BSLib::uint32 EntityTPID;

typedef BSLib::uint32 SceneTPID;
typedef BSLib::uint32 SceneID;

typedef BSLib::uint32 AttrIndex;

typedef BSLib::uint64 RoleID;
typedef BSLib::int32 RoleIndex;
const RoleIndex INVALID_ROLEINDEX = -1;

typedef BSLib::uint32 SkillID;
typedef BSLib::uint32 SkillTPID;
typedef BSLib::uint32 SkillLevel;

enum EEventID
{
    EEVENTID_ACHIEVE_ROLELEVEL = 1,      //等级成就
    EEVENTID_ACHIEVE_COMBAT = 2,         //战斗力成就
    EEVENTID_ACHIEVE_KILL_BOSS = 3,		 //击杀BOSS成就	
    EEVENTID_ACHIEVE_PASS_INSTANCE = 4,  //通关副本成就	
    EEVENTID_ACHIEVE_PVP = 5,			 //PVP成就	
    EEVENTID_ACHIEVE_DICE = 6,			 //骰子成就
    EEVENTID_ACHIEVE_PASS_STAGE = 7,	 //连续闯关成就
    EEVENTID_ACHIEVE_EQUIP = 8,	         //装备成就
    EEVENTID_ACHIEVE_GEM = 9,	         //宝石成就
    EEVENTID_ACHIEVE_SKILL = 10,	     //技能成就
    EEVENTID_ACHIEVE_PET = 11,	         //僚机成就
    EEVENTID_ACHIEVE_CHARGEPAY = 12,     //充值消费成就
    EEVENTID_ACHIEVE_MAXID = 13,   

    EEVENTID_HOTSPRING_PETEVENT_ACTIVE = 100,  // 温泉伙伴事件激活
    EEVENTID_HOTSPRING_BOSSEVENT_ACTIVE = 101, // 温泉老板娘事件激活

};

#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif

class CSkillID
{
public:
	CSkillID(SkillID a_skillID = 0) 
		: m_skillID(a_skillID) {}
	CSkillID(SkillTPID a_skillTPID, SkillLevel a_skillLevel) 
		: m_skillID(BSLIB_HI_SHIFT(a_skillTPID, 8) + (a_skillLevel & 0X000000FF))  {}
	CSkillID(const CSkillID& a_skillID)
		: m_skillID(a_skillID.m_skillID) {}

	SkillID getSkillID() const { return m_skillID; }
	SkillTPID getSkillTPID() const { return BSLIB_LO_SHIFT(m_skillID, 8); }
	SkillLevel getSkillLevel() const { return m_skillID & 0X000000FF; }

	bool isSameSkill(SkillID a_skillID) const
	{
		return getSkillTPID() == BSLIB_LO_SHIFT(m_skillID, 8);
	}

	bool isSameSkill(const CSkillID& a_skillID) const
	{
		return getSkillTPID() == a_skillID.getSkillTPID();
	}

	CSkillID& operator =(SkillID a_skillID) 
	{
		m_skillID = a_skillID;
		return *this;
	}

	CSkillID& operator =(const CSkillID& a_skillID) 
	{
		m_skillID = a_skillID.m_skillID;
		return *this;
	}

	bool operator ==(SkillID a_skillID) const
	{
		return m_skillID == a_skillID;
	}

	bool operator ==(const CSkillID& a_skillID) const 
	{
		return m_skillID == a_skillID.m_skillID;
	}

	bool operator !=(SkillID a_skillID) const
	{
		return m_skillID != a_skillID;
	}

	bool operator !=(const CSkillID& a_skillID) const 
	{
		return m_skillID != a_skillID.m_skillID;
	}

private:
	SkillID m_skillID;
};

class SRoleKey
{
public:
	SRoleKey()
		: m_index(INVALID_ROLEINDEX) {} 
	SRoleKey(const GFLib::SAccountKey& a_accountKey, GSLib::RoleIndex a_index)
		: m_accountKey(a_accountKey), m_index(a_index) {} 
	SRoleKey(GFLib::AccountID a_accountID, GFLib::ZoneID a_zoneID, GSLib::RoleIndex a_index)
		: m_accountKey(a_accountID, a_zoneID), m_index(a_index) {} 
	SRoleKey(const SRoleKey& a_roleKey)
		: m_accountKey(a_roleKey.m_accountKey), m_index(a_roleKey.m_index) {}  

	GFLib::AccountID getAccountID() const { return m_accountKey.getAccountID(); }
	GFLib::ZoneID getZoneID() const { return m_accountKey.getZoneID(); }
	GSLib::RoleIndex getIndex() const { return m_index; }

	const GFLib::SAccountKey& getAccountKey() const { return m_accountKey; }

	void setAccountID(GFLib::AccountID a_accountID)	{ m_accountKey.setAccountID(a_accountID); }
	void setZoneID(GFLib::ZoneID a_zoneID) { m_accountKey.setZoneID(a_zoneID); }
	void setIndex(GSLib::RoleIndex a_index) { m_index = a_index; }

	void setRoleKey(const GFLib::SAccountKey& a_accountKey, GSLib::RoleIndex a_index)
	{
		m_accountKey = a_accountKey;
		m_index = a_index;
	}

	void setRoleKey(GFLib::AccountID a_accountID, GFLib::ZoneID a_zoneID, GSLib::RoleIndex a_index)
	{
		m_accountKey.setKey(a_accountID, a_zoneID);
		m_index = a_index;
	}

	bool isValid() const 
	{
		return m_accountKey.getZoneID() != 0 && m_index != INVALID_ROLEINDEX;
	}

	SRoleKey& operator =(const SRoleKey& a_roleKey) 
	{
		m_accountKey = a_roleKey.m_accountKey;
		m_index = a_roleKey.m_index;
		return *this;
	}

	bool operator ==(const SRoleKey& a_roleKey) const 
	{
		return m_accountKey == a_roleKey.m_accountKey && m_index == a_roleKey.m_index;
	}

	bool operator !=(const SRoleKey& a_roleKey) const
	{
		return m_accountKey != a_roleKey.m_accountKey  || m_index != a_roleKey.m_index;
	}

	bool operator < (const SRoleKey& other) const
	{
		if( getZoneID() < other.getZoneID()){
			return true;
		}	
		else if(getZoneID() == other.getZoneID() && getAccountID() < other.getAccountID()){
			return true;
		}		
		else if( getZoneID() == other.getZoneID() && getAccountID() == other.getAccountID() 
			&& m_index < other.m_index){
				return true;
		}		

		return false;
	}

	std::string getDBKey() const 
	{
		std::string key = m_accountKey.getDBKey();
		key.append((char*)&m_index, sizeof(m_index));
		return key;
	}

    std::string getDBAccountKey() const 
    {
        return m_accountKey.getDBKey();
    }

	std::string getDBIndex() const 
	{
		std::string index;
		index.append((char*)&m_index, sizeof(m_index));
		return index;
	}
    
    bool serializeFrom(BSLib::Utility::CStream& stream)
    {
        BSLib::uint64 accountID = 0;
        BSLib::uint16 zoneID= 0;
        stream >> accountID; 
        stream >> zoneID;
        m_accountKey.setAccountID(accountID);
        m_accountKey.setZoneID(zoneID);
        stream >> m_index;
        return true;
    }

    bool serializeTo(BSLib::Utility::CStream& stream)const
    {
        stream << m_accountKey.getAccountID();
        stream << m_accountKey.getZoneID();
        stream << m_index;
        return true;
    }

	std::string toLogString() const
	{
		BSLib::Utility::CStringA log;
		log.format("[AccountID=%lld][ZoneID=%d][RoleIndex=%d]", m_accountKey.getAccountID(), m_accountKey.getZoneID(), m_index);
		return log;
	}

private:
	GFLib::SAccountKey m_accountKey;
	GSLib::RoleIndex m_index;
};

typedef enum
{
    ATTR_ATK =0,            // 物理攻击   
    ATTR_DEF=1,             // 物理防御
    ATTR_MAXHP=2,           // maxhp
    ATTR_HIT_RATE=3,        // 命中几率(1/10000)
    ATTR_MISS_RATE=4,       // 避闪几率(1/10000)
    ATTR_ATK_CRIFT=5,       // 暴击(1/10000)
    ATTR_DEF_CRIFT=6,       // 暴击抗性
    MAX_ATTR_INDEX=7,
    ATTR_INVALID = 8,
}EAttrID;

typedef enum
{
    QUALITY_INVALID =0,     // 无效品级 
    QUALITY_WHITE =1,       // 白
    QUALITY_GREEN =2,       // 绿
    QUALITY_BLUE =3,        // 蓝
    QUALITY_PURPLE=4,       // 紫
    QUALITY_ORANGE=5,       // 黄
    QUALITY_RED=6,        // 红
    MAX_QUALITY_INDEX,
}EQualityID;

struct SBattleAttribute{
    BSLib::uint32 m_atk;
    BSLib::uint32 m_def;

    BSLib::uint32 m_atkCrift;
    BSLib::uint32 m_defCrift;

    BSLib::uint32 m_hitRate;
    BSLib::uint32 m_missRate;
    BSLib::uint32 m_maxHP;

    SBattleAttribute()
    {
        cleanAttr();
    } 

    SBattleAttribute& operator =(const SBattleAttribute& a_battleAttr)
    {
        m_atk = a_battleAttr.m_atk;
        m_def = a_battleAttr.m_def;
        m_atkCrift = a_battleAttr.m_atkCrift;
        m_defCrift = a_battleAttr.m_defCrift;
        m_hitRate = a_battleAttr.m_hitRate;
        m_missRate = a_battleAttr.m_missRate;
        m_maxHP = a_battleAttr.m_maxHP;
        return *this;
    }

    const BSLib::uint32 getValue(EAttrID a_attrID) const
    {
        switch (a_attrID)
        {
        case ATTR_ATK: { return m_atk; } break;
        case ATTR_DEF: { return m_def; } break;

        case ATTR_ATK_CRIFT: { return m_atkCrift; } break;
        case ATTR_DEF_CRIFT: { return m_defCrift; } break;

        case ATTR_HIT_RATE: { return m_hitRate; } break;
        case ATTR_MISS_RATE: { return m_missRate; } break;
        case ATTR_MAXHP: { return m_maxHP; } break;
        default: { return 0; } break;
        }
    }

    bool setValue(EAttrID a_attrID,BSLib::uint32 a_value)
    {
        switch (a_attrID)
        {
        case ATTR_ATK: { m_atk = a_value; } break;
        case ATTR_DEF: { m_def = a_value; } break;

        case ATTR_ATK_CRIFT: { m_atkCrift = a_value; } break;
        case ATTR_DEF_CRIFT: { m_defCrift = a_value; } break;

        case ATTR_HIT_RATE: { m_hitRate = a_value; } break;
        case ATTR_MISS_RATE: { m_missRate = a_value; } break;
        case ATTR_MAXHP: { m_maxHP = a_value; } break;
        default: { return false; } break;
        }
        return true;
    }


    bool addValue(EAttrID a_attrID,BSLib::uint32 a_value)
    {
        switch (a_attrID)
        {
        case ATTR_ATK: { m_atk += a_value; } break;
        case ATTR_DEF: { m_def += a_value; } break;

        case ATTR_ATK_CRIFT: { m_atkCrift += a_value; } break;
        case ATTR_DEF_CRIFT: { m_defCrift += a_value; } break;

        case ATTR_HIT_RATE: { m_hitRate += a_value; } break;
        case ATTR_MISS_RATE: { m_missRate += a_value; } break;
        case ATTR_MAXHP: { m_maxHP = a_value; } break;
        default: { return false; } break;
        }
        return true;
    }

    bool addAttr(const SBattleAttribute& a_battleAttr) 
    {
        for(BSLib::uint32 attributeID = ATTR_ATK; attributeID < MAX_ATTR_INDEX; ++ attributeID){
            EAttrID keyID = (EAttrID)attributeID;
            BSLib::uint32 fixValue = getValue(keyID) + a_battleAttr.getValue(keyID);
            setValue(keyID,fixValue);
        }

        return true;
    }

    bool addBattleAttrByPoint(BSLib::uint32 a_point) 
    {
        for(BSLib::uint32 attributeID = ATTR_ATK; attributeID < MAX_ATTR_INDEX; ++ attributeID){
            EAttrID keyID = (EAttrID)attributeID;
            BSLib::uint32 addValue = (getValue(keyID)* a_point)/100;
            if(addValue <= 0){
                continue;
            }
            BSLib::uint32 fixValue = getValue(keyID) + addValue;
            setValue(keyID,fixValue);
        }

        return true;
    }

    void cleanAttr() 
    {
        m_atk = 0;
        m_def = 0;

        m_atkCrift = 0;
        m_defCrift = 0;

        m_hitRate = 0;
        m_missRate = 0;
        m_maxHP = 0;
    }

    std::string toLogString() const 
    {
        BSLib::Utility::CStringA log;
        BSLib::Utility::CStringA logtemp;
        if(m_atk != 0){
            logtemp.format("[m_atk=%d]",m_atk);
            log.append(logtemp.c_str());
        } 
        if(m_def != 0){
            logtemp.format("[m_def=%d]",m_def);
            log.append(logtemp.c_str());
        } 

        if(m_atkCrift != 0){
            logtemp.format("[m_atkCrift=%d]",m_atkCrift);
            log.append(logtemp.c_str());
        } 
        if(m_defCrift != 0){
            logtemp.format("[m_defCrift=%d]",m_defCrift);
            log.append(logtemp.c_str());
        }

        if(m_hitRate != 0){
            logtemp.format("[m_hitRate=%d]",m_hitRate);
            log.append(logtemp.c_str());
        } 
        if(m_missRate != 0){
            logtemp.format("[m_missRate=%d]",m_missRate);
            log.append(logtemp.c_str());
        } 
       
        if(m_maxHP != 0){
            logtemp.format("[m_maxHP=%d]",m_maxHP);
            log.append(logtemp.c_str());
        } 
        return log;
    }

    bool  serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_atk;
        stream << m_def;

        stream << m_atkCrift;
        stream << m_defCrift;

        stream << m_hitRate;
        stream << m_missRate;
        stream << m_maxHP;

        return true;
    }

    bool serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_atk;
        stream >> m_def;

        stream >> m_atkCrift;
        stream >> m_defCrift;

        stream >> m_hitRate;
        stream >> m_missRate;
        stream >> m_maxHP;

        return true;
    }
};


struct CAttrFriendly{
    BSLib::uint32 m_atk;
    BSLib::uint32 m_def;

    BSLib::uint32 m_atkCrift;
    BSLib::uint32 m_defCrift;

    BSLib::uint32 m_hitRate;
    BSLib::uint32 m_missRate;
    BSLib::uint32 m_maxHP;

    CAttrFriendly()
    {
        cleanAttrFriendly();
    } 

    const BSLib::uint32 getValue(EAttrID a_attrID) const
    {
        switch (a_attrID)
        {
        case ATTR_ATK: { return m_atk; } break;
        case ATTR_DEF: { return m_def; } break;

        case ATTR_ATK_CRIFT: { return m_atkCrift; } break;
        case ATTR_DEF_CRIFT: { return m_defCrift; } break;

        case ATTR_HIT_RATE:  { return m_hitRate; } break;
        case ATTR_MISS_RATE: { return m_missRate; } break;
        case ATTR_MAXHP:     { return m_maxHP; } break;
        default: { return 0; } break;
        }
    }

    bool setValue(EAttrID a_attrID,BSLib::uint32 a_value)
    {
        switch (a_attrID)
        {
        case ATTR_ATK: { m_atk = a_value; } break;
        case ATTR_DEF: { m_def = a_value; } break;

        case ATTR_ATK_CRIFT: { m_atkCrift = a_value; } break;
        case ATTR_DEF_CRIFT: { m_defCrift = a_value; } break;

        case ATTR_HIT_RATE: { m_hitRate = a_value; } break;
        case ATTR_MISS_RATE: { m_missRate = a_value; } break;
        case ATTR_MAXHP: { m_maxHP = a_value; } break;
        default: { return false; } break;
        }
        return true;
    }

    bool addAttrFriendly(const CAttrFriendly& a_attrFriendly) 
    {
        for(BSLib::uint32 attributeID = ATTR_ATK; attributeID < MAX_ATTR_INDEX; ++ attributeID){
            EAttrID keyID = (EAttrID)attributeID;
            BSLib::uint32 fixValue = getValue(keyID) + a_attrFriendly.getValue(keyID);
            setValue(keyID,fixValue);
        }

        return true;
    }

    bool addBattleAttrByPoint(BSLib::uint32 a_point) 
    {
        for(BSLib::uint32 attributeID = ATTR_ATK; attributeID < MAX_ATTR_INDEX; ++ attributeID){
            EAttrID keyID = (EAttrID)attributeID;
            BSLib::uint32 addValue = (getValue(keyID)* a_point)/100;
            if(addValue <= 0){
                continue;
            }
            BSLib::uint32 fixValue = getValue(keyID) + addValue;
            setValue(keyID,fixValue);
        }

        return true;
    }

    void cleanAttrFriendly() 
    {
        m_atk = 0;
        m_def = 0;

        m_atkCrift = 0;
        m_defCrift = 0;

        m_hitRate = 0;
        m_missRate = 0;
        m_maxHP = 0;
    }

    std::string toLogString() const 
    {
        BSLib::Utility::CStringA log;
        log.format("m_physicalAtk=%d][m_physicalDef=%d]m_atkCrift=%d][m_defCrift=%d]\r\n"             \
            "[m_hitRate=%d][m_missRate=%d][m_maxHP=%d]\r\n"        \
            "==============================================================\r\n",
            m_atk, m_def, m_atkCrift, m_defCrift, m_hitRate, m_missRate, m_maxHP);
        return log;
    }

    bool  serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_atk;
        stream << m_def;

        stream << m_atkCrift;
        stream << m_defCrift;

        stream << m_hitRate;
        stream << m_missRate;
        stream << m_maxHP;

        return true;
    }

    bool serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_atk;
        stream >> m_def;

        stream >> m_atkCrift;
        stream >> m_defCrift;

        stream >> m_hitRate;
        stream >> m_missRate;
        stream >> m_maxHP;

        return true;
    }
};

struct CAttribute
{
    BSLib::uint32 m_attrIndex;
    EAttrID m_attrID;
    BSLib::uint32 m_attrValue;
	EQualityID m_quality;
    CAttribute()
    {
        m_attrIndex = 0;
        m_attrID = ATTR_INVALID;
        m_attrValue = 0;
		m_quality = QUALITY_WHITE;
    }
public:
    BSLib::uint32 getAttrIndex() const{ return m_attrIndex; }
    EAttrID getAttrID() const{ return m_attrID; }
    BSLib::uint32 getAttrValue() const{ return m_attrValue; }
	EQualityID getQuality() const { return m_quality; }

    void setAttrIndex(BSLib::uint32 a_attrIndex) { m_attrIndex= a_attrIndex; }
    void setAttrID(EAttrID AttrID) { m_attrID = AttrID; }
    void setAttrValue(BSLib::uint32 a_attrValue) { m_attrValue = a_attrValue; }
	void setQuality(EQualityID a_color) { m_quality = a_color; }

    bool serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_attrIndex;
        BSLib::uint32 attrID =  (BSLib::uint32)m_attrID;
        stream << attrID;
        stream << m_attrValue;
		stream << (BSLib::uint32)m_quality;
        return true;
    }

    bool serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_attrIndex;
        BSLib::uint32 attrID =  0;
        stream >> attrID;
        stream >> m_attrValue;
        m_attrID = (EAttrID)attrID;
		stream >> attrID;
		m_quality = (EQualityID)attrID;
        return true;
    }
};

class CAttachAttr{
public:
    std::vector<CAttribute> m_attrArray;
    CAttachAttr() {;}
    CAttachAttr(const CAttachAttr& a_attachAttr) {
        m_attrArray.clear();
        std::vector<CAttribute>::const_iterator it = a_attachAttr.m_attrArray.begin();
        for(; it != a_attachAttr.m_attrArray.end();++it){
            CAttribute attr = *it;
            m_attrArray.push_back(attr);
        }
    }
    ~CAttachAttr() {;} 

    CAttachAttr& operator =(const CAttachAttr& a_attachAttr)
    {
        m_attrArray.clear();
        std::vector<CAttribute>::const_iterator it = a_attachAttr.m_attrArray.begin();
        for(; it != a_attachAttr.m_attrArray.end();++it){
            CAttribute attr = *it;
            m_attrArray.push_back(attr);
        }
        return *this;
    }

    bool serializeTo(BSLib::Utility::CStream& stream) const
    {
        BSLib::uint32 itemCount = m_attrArray.size();
        stream << itemCount;
        for(BSLib::uint32 i=0;i < itemCount;++i){
            CAttribute attr = m_attrArray[i];
            attr.serializeTo(stream);
        }
        return true;
    }

    bool serializeToDB(BSLib::Utility::CStream& stream) const
    {
        BSLib::uint32 itemCount = m_attrArray.size();
        BSLib::uint32 buffSize = sizeof(CAttribute)*itemCount;
        stream << buffSize; 
        for(BSLib::uint32 i=0;i < itemCount;++i){
            CAttribute attr = m_attrArray[i];
            attr.serializeTo(stream);
        }
        return true;
    }

    bool serializeFromDB(BSLib::Utility::CStream& stream)
    {
        BSLib::uint32 buffSize = 0;
        stream >> buffSize;
        if (buffSize > stream.readSize()) {
            return false;
        }
        BSLib::uint32 itemCount = buffSize/sizeof(CAttribute);
        for(BSLib::uint32 i=0;i < itemCount;++i){
            CAttribute attr;
            attr.serializeFrom(stream);
            m_attrArray.push_back(attr);
        }
        return true;
    }

    bool getBattleAttr(SBattleAttribute& attrs){
        attrs.cleanAttr();
        BSLib::uint32 itemCount = m_attrArray.size();
        for(BSLib::uint32 i=0;i < itemCount;++i){
            CAttribute attr = m_attrArray[i];
            attrs.addValue(attr.getAttrID(),attr.getAttrValue()); 
        }
        return true;
    }

    bool getNextEmptyIndex(BSLib::uint32& a_newIndex){
        BSLib::uint32 a[7]={0,0,0,0,0,0,0};
        BSLib::uint32 itemCount = m_attrArray.size();
        for(BSLib::uint32 i=0;i < itemCount;++i){
            CAttribute attr = m_attrArray[i];
            const BSLib::uint32 index = attr.getAttrIndex(); 
            if ((index >=0 )&&(index < 7)){
                a[index] = 1;
            }
        }
        for(BSLib::uint32 i=0;i < 7;++i){
            BSLib::uint32 bUse = a[i];
            if (bUse == 0){
                a_newIndex = i;
                return true;
            }
        }
        return false;
    }

    bool setAttr(AttrIndex a_attrIndex,const CAttribute& a_newAttr){
        BSLib::uint32 itemCount = m_attrArray.size();
        for(BSLib::uint32 i=0;i < itemCount;++i){
            
            CAttribute attr = m_attrArray[i];
            if(attr.getAttrIndex() == a_attrIndex){
               m_attrArray[i] = a_newAttr;
               return true;
            }
        }
        return false;
    }

    bool getAttr(AttrIndex a_attrIndex,CAttribute& a_newAttr) const{
        BSLib::uint32 itemCount = m_attrArray.size();
        for(BSLib::uint32 i=0;i < itemCount;++i){

            CAttribute attr = m_attrArray[i];
            if(attr.getAttrIndex() == a_attrIndex){
                a_newAttr = attr;
                return true;
            }
        }
        return false;
    }

    BSLib::uint32 getAttrCount() const{
       return m_attrArray.size();
    }

    std::string toLogString() const 
    {
        BSLib::Utility::CStringA log;
        BSLib::Utility::CStringA logtemp;
        BSLib::uint32 itemCount = m_attrArray.size();
        for(BSLib::uint32 i=0;i < itemCount;++i){
            CAttribute attr = m_attrArray[i];
            logtemp.format("[AttrID=%d][AttrValue=%d]",attr.getAttrID(),attr.getAttrValue());
            log.append(logtemp.c_str());
        }
        return log;
    }

    void cleanAttr() 
    {
        m_attrArray.clear();
    }
};


struct SChargeList
{
	BSLib::int64 m_chargeID;//充值ID
	int m_type;				//商品类型
	int m_money;			//充值金额
};

}//


#ifdef WIN32
#pragma pack (pop)
#else
#pragma pack ()
#endif


static std::string toMailString(const std::string& a_string)
{
    std::string outUTF8String = "";
#if defined(WIN32)
    BSLib::Utility::CConvert::gb2312ToUTF8(outUTF8String,a_string);
#else
    outUTF8String = a_string;
#endif
    return outUTF8String;
}
#endif//__GSLIB_BASEDEF_H__

