#ifndef __BSLIB_FRAMEWORK_MESSAGE_MESSAGE_H__
#define __BSLIB_FRAMEWORK_MESSAGE_MESSAGE_H__

#include <BSLib/utility/stream.h>
#include <BSLib/framework/channelID.h>

namespace BSLib
{

namespace Framework
{

#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif

struct BSLIB_FRAMEWORK_API SMessage
{
public:
	SMessage(uint32 msgID) : m_msgID(msgID) {}
	SMessage(uint16 type, uint16 id) : m_type(type), m_id(id) {}

	uint16 getType() const { return m_type; }
	uint16 getID() const { return m_id; }

	uint32 getUniqueID() const { return  m_msgID; }

	std::string toString()
	{
		BSLib::Utility::CStringA strMsgID;
		strMsgID.format("(%d-%d,%d)", BSLIB_LO_SHIFT(getType() & 0XFF00, 8), getType() & 0X00FF, getID());
		return strMsgID;
	}

private:
	union
	{
		struct
		{
			BSLib::uint16 m_type;
			BSLib::uint16 m_id;
		};
		BSLib::uint32 m_msgID;
	};
	
};

#ifdef WIN32
#pragma pack (pop)
#else
#pragma pack ()
#endif

class BSLIB_FRAMEWORK_API CMessage : public SMessage
{
public:
	CMessage(uint32 msgID);
	CMessage(uint16 type, uint16 id);
	virtual ~CMessage() {}

	bool serializeTo(BSLib::Utility::CStream& stream) const;
	bool serializeFrom(BSLib::Utility::CStream& stream);
	bool serializeFrom(const SMessage* msg, int size);

protected:
	virtual bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		return true;
	}

	virtual bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		return true;
	}
};

}//Framework

}//BSLib

#endif//__BSLIB_FRAMEWORK_MESSAGE_MESSAGE_H__

