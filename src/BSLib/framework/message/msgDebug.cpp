#include <BSLib/framework/message/msgDebug.h>

namespace BSLib
{

namespace Framework
{

BSLIB_SINGLETON_DEFINE(CMsgDebug)

CMsgDebug::CMsgDebug()
{
	;
}

CMsgDebug::~CMsgDebug()
{
	;
}

void CMsgDebug::setPrompt(uint16 type, uint16 id, const std::string& strPrompt)
{
	m_hashMap.setValue(BSLIB_HI_SHIFT(type, 16) + id, strPrompt);
}

const std::string& CMsgDebug::getPrompt(uint16 type, uint16 id)
{
	static std::string temp("Unknow");
	BSLib::Utility::CHashMap<uint32, std::string>::iterator it = m_hashMap.find(BSLIB_HI_SHIFT(type, 16) + id);
	if (it == m_hashMap.end()) {
		return temp;
	}
	return it->second;
}

const std::string& CMsgDebug::getPrompt(SMessage* message)
{
	return getPrompt(message->getType(), message->getID());
}

const std::string& CMsgDebug::getPrompt(CMessage* message)
{
	return getPrompt(message->getType(), message->getID());
}

}//Framework

}//BSLib


