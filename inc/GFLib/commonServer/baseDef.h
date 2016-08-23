#ifndef __GFLIB_COMMONSERVER_BASEDEF_H__
#define __GFLIB_COMMONSERVER_BASEDEF_H__

#include <BSLib/framework/channelID.h>
#include <BSLib/network/netStub.h>
#include <BSLib/framework/message/msgDebug.h>

#ifdef GFLIB_COMMONSERVER_EXPORTS
#define GFLIB_COMMONSERVER_API _declspec(dllexport)
#elif defined(GFLIB_COMMONSERVER_IMPORTS)
#define GFLIB_COMMONSERVER_API _declspec(dllimport)
#else
#define GFLIB_COMMONSERVER_API 
#endif

namespace GFLib
{

typedef BSLib::uint16 ZoneID;
const ZoneID GLOBAL_ZONEID = 0;

typedef BSLib::uint32 ServerID;
const ServerID INVALID_SERVERID = 0;

typedef BSLib::Network::StubID StubID;
const StubID INVALID_STUBID = BSLib::Network::INVALID_STUBID;

typedef BSLib::uint64 AccountID;

typedef BSLib::uint8 ServerType;

const ServerType SRVTYPE_NULL = 0;	//拸虴
const ServerType SRVTYPE_LOCAL = 1;	//潠備'LC'
const ServerType SRVTYPE_ANY = 2;	//潠備'XX'
const ServerType SRVTYPE_ANYSERVER = 3;	//潠備'XS'

const ServerType SRVTYPE_GAMECLIENT = 8;			//潠備'GC'

#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif

struct SServerID
{
public:
	SServerID(const ServerID a_serverID = INVALID_SERVERID) 
		: m_serverID(a_serverID) {}
	SServerID(ZoneID a_zoneID, ServerType a_type, BSLib::uint8 a_number) 
		: m_number(a_number), m_type(a_type), m_zoneID(a_zoneID)  {}
	SServerID(const SServerID& a_serverID)
		: m_serverID(a_serverID.m_serverID) {}

	ZoneID getZoneID() const { return m_zoneID; }
	ServerType getServerType() const { return (ServerType)m_type; }
	BSLib::uint8 getServerNumber() const { return m_number; }
	ServerID getServerID() const { return m_serverID; }

	void setServerID(const ServerID& a_serverID) { m_serverID = a_serverID; }
	void setServerID(const SServerID& a_serverID) { m_serverID = a_serverID.m_serverID; }
	void setServerID(const ZoneID& a_zoneID, const ServerType& a_type, const BSLib::uint8& a_number) { m_zoneID = a_zoneID; m_type = a_type; m_number = a_number; }
 
	std::string toString()
	{
		BSLib::Utility::CStringA temp;
		temp.format("(%d,%d,%d)", m_zoneID, m_type, m_number);
		return temp;
	}	
	
	bool isValid()
	{
		return m_serverID != 0;
	}

	SServerID& operator =(ServerID a_serverID) 
	{
		m_serverID = a_serverID;
		return *this;
	}

	SServerID& operator =(const SServerID& a_serverID) 
	{
		m_serverID = a_serverID.m_serverID;
		return *this;
	}

	bool operator ==(ServerID a_serverID) const
	{
		return m_serverID == a_serverID;
	}

	bool operator ==(const SServerID& a_serverID) const 
	{
		return m_serverID == a_serverID.m_serverID;
	}

	bool operator !=(ServerID a_serverID) const
	{
		return m_serverID != a_serverID;
	}

	bool operator !=(const SServerID& a_serverID) const 
	{
		return m_serverID != a_serverID.m_serverID;
	}

private:
	union
	{
		struct
		{
			BSLib::uint8 m_number;
			ServerType m_type;	
			ZoneID m_zoneID;	
		};
		ServerID m_serverID;
	};
};

class SAccountKey
{
public:
	SAccountKey()
		: m_accountID(0), m_zoneID(0) {} 
	SAccountKey(GFLib::AccountID a_accountID, GFLib::ZoneID a_zoneID)
		: m_accountID(a_accountID), m_zoneID(a_zoneID){} 
	SAccountKey(const SAccountKey& a_roleKey)
		: m_accountID(a_roleKey.m_accountID), m_zoneID(a_roleKey.m_zoneID) {}  

	GFLib::AccountID getAccountID() const { return m_accountID; }
	GFLib::ZoneID getZoneID() const { return m_zoneID; }

	void setAccountID(GFLib::AccountID a_accountID)	{ m_accountID = a_accountID; }
	void setZoneID(GFLib::ZoneID a_zoneID) { m_zoneID = a_zoneID; }

	void setKey(GFLib::AccountID a_accountID, GFLib::ZoneID a_zoneID)
	{
		m_accountID = a_accountID;
		m_zoneID = a_zoneID;
	}

	SAccountKey& operator =(const SAccountKey& a_accountKey)
	{
		m_accountID = a_accountKey.m_accountID;
		m_zoneID = a_accountKey.m_zoneID;
		return *this;
	}

	bool operator ==(const SAccountKey& a_accountKey) const 
	{
		return m_accountID == a_accountKey.m_accountID && m_zoneID == a_accountKey.m_zoneID;
	}

	bool operator !=(const SAccountKey& a_accountKey) const
	{
		return m_accountID != a_accountKey.m_accountID || m_zoneID != a_accountKey.m_zoneID;
	}

	std::string getDBKey() const
	{
		std::string key;
		key.append((char*)&m_accountID, sizeof(m_accountID));
		key.append((char*)&m_zoneID, sizeof(m_zoneID));
		return key;
	}

	std::string toLogString() const 
	{
		BSLib::Utility::CStringA log;
		log.format("[AccountID=%lld][ZoneID=%d]", m_accountID, m_zoneID);
		return log;
	}
private:
	AccountID m_accountID;
	ZoneID m_zoneID;
};

#ifdef WIN32
#pragma pack (pop)
#else
#pragma pack ()
#endif

#define GFLIB_MSG_TYPE(server, func) (BSLIB_HI_SHIFT(server, 8) + func)
#define GFLIB_MSG_DEBUG(server, func, num) BSLIB_MSG_DEBUG(GFLIB_MSG_TYPE(server, func), num)

#define GFLIB_MSGID_DEBUG(server, func, num) \
	( (BSLIB_HI_SHIFT(num, 16) & 0XFFFF0000) + (BSLIB_HI_SHIFT(server, 8) & 0X0000FF00) + (func & 0X000000FF) );\
	GFLIB_MSG_DEBUG(server, func, num)

#define GFLIB_EVENT_ID_MAX		1024

}//GFLib


#ifdef __GNUC__

namespace __gnu_cxx
{

template< > struct hash< GFLib::SAccountKey >
{
	size_t operator()(const GFLib::SAccountKey& x) const
	{
		GFLib::AccountID accountID = x.getAccountID();
		GFLib::ZoneID zoneID = x.getZoneID();
		if (sizeof(GFLib::AccountID) == sizeof(size_t)){
			return accountID + (zoneID << 16);
		} else {
			return (accountID >> 32) + (accountID & 0xFFFFFFFF) + (zoneID << 16);
		}
	}
};

}//__gnu_cxx

namespace std
{
	template < > struct equal_to< GFLib::SAccountKey >
	{
		bool operator()(const GFLib::SAccountKey& _Left,const GFLib::SAccountKey& _Right) const 
		{
			if (_Left.getZoneID() == _Right.getZoneID()) {
				return _Left.getAccountID() == _Right.getAccountID();
			}
			return false;
		}
	}; 
}


#else

namespace std
{

template<>
struct less<GFLib::SAccountKey>
{
	bool operator ()(const GFLib::SAccountKey& _Left,const GFLib::SAccountKey& _Right) const
	{
		if (_Left.getZoneID() == _Right.getZoneID()) {
			return _Left.getAccountID() < _Right.getAccountID();
		}
		return _Left.getZoneID() < _Right.getZoneID();
	}
};

}//std

namespace stdext
{

size_t hash_value(const GFLib::SAccountKey & v);

}//stdext

#endif//__GNUC__

#endif //__GFLIB_COMMONSERVER_BASEDEF_H__



