//////////////////////////////////////////////////////////////////////
//	created:	2012/07/20
//	filename:	BSLib\framework\baseDef.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_FRAMEWORK_BASEDEF_H__
#define __BSLIB_FRAMEWORK_BASEDEF_H__

#include <BSLib/utility/baseDef.h>

#ifdef BSLIB_FRAMEWORK_EXPORTS
	#define BSLIB_FRAMEWORK_API _declspec(dllexport)
#elif defined(BSLIB_FRAMEWORK_IMPORTS)
	#define BSLIB_FRAMEWORK_API _declspec(dllimport)
#else
	#define BSLIB_FRAMEWORK_API 
#endif

namespace BSLib
{

namespace Framework
{

typedef BSLib::uint32 ChannelID;
const ChannelID INVALID_CHANNELID = 0XFFFFFFFF; 

#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif

struct CChannelID
{
public:
	CChannelID(ChannelID a_channelID = INVALID_CHANNELID) : m_channelID(a_channelID) {}
	CChannelID(BSLib::uint8 a_localNumber, BSLib::uint32 a_mappingNumber) : m_channelID((a_mappingNumber << 8) + a_localNumber){}
	CChannelID(const CChannelID& a_channelID) : m_channelID(a_channelID.m_channelID) {}

	BSLib::uint8 getLocalNumber() const { return (BSLib::uint8)(m_channelID & 0X000000FF); }
	BSLib::uint32 getMappingNumber() const { return (BSLib::uint32)((m_channelID & 0XFFFFFF00) >> 8); }
	ChannelID getID() { return m_channelID; }

	void setChannelID(ChannelID a_channelID = INVALID_CHANNELID) { m_channelID = a_channelID; }
	void setChannelID(BSLib::uint8 a_localNumber, BSLib::uint32 a_mappingNumber) { m_channelID = (a_mappingNumber << 8) + a_localNumber; }
	void setChannelID(BSLib::uint8 a_localNumber) { m_channelID = a_localNumber; }
	void setChannelID(const CChannelID& a_channelID) { m_channelID = a_channelID.m_channelID; }

	bool isValid() const { return m_channelID != INVALID_CHANNELID; }
	bool isLocal() const { return (m_channelID != INVALID_CHANNELID) && ((m_channelID & 0XFFFFFF00) == 0); }
	bool isMapping() const { return (m_channelID != INVALID_CHANNELID) && ((m_channelID & 0XFFFFFF00) != 0); }

	CChannelID& operator =(ChannelID a_channelID) 
	{
		m_channelID = a_channelID;
		return *this;
	}

	CChannelID& operator =(const CChannelID& a_channelID) 
	{
		m_channelID = a_channelID.m_channelID;
		return *this;
	}

	bool operator ==(ChannelID a_channelID) const
	{
		return m_channelID == a_channelID;
	}

	bool operator ==(const CChannelID& a_channelID) const 
	{
		return m_channelID == a_channelID.m_channelID;
	}

	bool operator !=(ChannelID a_channelID) const
	{
		return m_channelID != a_channelID;
	}

	bool operator !=(const CChannelID& a_channelID) const 
	{
		return m_channelID != a_channelID.m_channelID;
	}

private:
	ChannelID m_channelID;
};

#ifdef WIN32
#pragma pack (pop)
#else
#pragma pack ()
#endif

}//Framework

}//BSLib

#endif //__BSLIB_FRAMEWORK_BASEDEF_H__



