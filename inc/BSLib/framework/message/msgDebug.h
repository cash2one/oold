#ifndef __BSLIB_FRAMEWORK_MESSAGE_MSGDEBUG_H__
#define __BSLIB_FRAMEWORK_MESSAGE_MSGDEBUG_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/hashMap.h>
#include <BSLib/framework/channelID.h>
#include <BSLib/framework/message/message.h>

namespace BSLib
{

namespace Framework
{

class BSLIB_FRAMEWORK_API CMsgDebug
{
public:
	BSLIB_SINGLETON_DECLARE(CMsgDebug)

public:
	CMsgDebug();
	virtual ~CMsgDebug();

	void setPrompt(uint16 type, uint16 id, const std::string& strPrompt);
	const std::string& getPrompt(uint16 type, uint16 id);

	const std::string& getPrompt(SMessage* message);
	const std::string& getPrompt(CMessage* message);

	void clear() { m_hashMap.clear(); }
private:
	BSLib::Utility::CHashMap<uint32, std::string> m_hashMap;
};

#define BSLIB_MSG_DEBUG(type, id) \
	class CMsgDebug_ ## id\
	{\
	public:\
		CMsgDebug_ ## id()\
		{\
			BSLib::Framework::CMsgDebug::singleton().setPrompt(type, id, #id);\
		}\
	};\
	static CMsgDebug_ ## id g_msgDebug_ ## id;


}//Framework

}//BSLib


#endif // __BSLIB_FRAMEWORK_MESSAGE_MSGDEBUG_H__

