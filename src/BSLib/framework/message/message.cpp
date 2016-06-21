#include <BSLib/utility/tracer.h>
#include <BSLib/framework/message/message.h>

namespace BSLib
{

namespace Framework
{
CMessage::CMessage(uint32 msgID)
: SMessage(msgID)
{
	;
}

CMessage::CMessage(uint16 type, uint16 id)
: SMessage(type, id)
{
	;
}

bool CMessage::serializeTo(BSLib::Utility::CStream& stream) const
{
	stream << SMessage::getUniqueID();
	return _serializeTo(stream);
}

bool CMessage::serializeFrom(BSLib::Utility::CStream& stream)
{
	uint32 size = stream.readSize();
	if (size < (int)sizeof(SMessage)){
		BSLIB_LOG_ERROR(ETT_BSLIB_FRAMEWORK, "序列化消息失败");
		return false;
	}

	uint32 msgID = 0;
	stream >> msgID;

	if (msgID != SMessage::getUniqueID()){
		BSLIB_LOG_ERROR(ETT_BSLIB_FRAMEWORK, "序列化不一致消息[%d][%d]", msgID, SMessage::getUniqueID());
		return false;
	}

	try {
		return _serializeFrom(stream);
	} catch (...) {
		BSLIB_LOG_ERROR(ETT_BSLIB_FRAMEWORK, "序列化消息[%s]失败", SMessage::toString().c_str());
		return false;
	} 
}


bool CMessage::serializeFrom(const SMessage* msg, int size)
{
	if (size < (int)sizeof(SMessage)){
		BSLIB_LOG_ERROR(ETT_BSLIB_FRAMEWORK, "序列化消息失败");
		return false;
	}

	uint32 msgID = 0;
	BSLib::Utility::CStream stream;

	stream.push((char*)msg, size);
	stream >> msgID;

	if (msgID != SMessage::getUniqueID()){
		BSLIB_LOG_ERROR(ETT_BSLIB_FRAMEWORK, "序列化不一致消息[%d][%d]", msgID, SMessage::getUniqueID());
		return false;
	}

	try {
		return _serializeFrom(stream);
	} catch (...) {
		BSLIB_LOG_ERROR(ETT_BSLIB_FRAMEWORK, "序列化消息[%s]失败", SMessage::toString().c_str());
		return false;
	} 
}


}//Framework

}//BSLib

