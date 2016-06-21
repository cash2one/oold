#include <BSLib/utility/stream.h>

namespace BSLib
{

namespace Utility
{

CStream::CStream()
{
	;
}

CStream::CStream(const CStream& a_stream)
{
	uint32 buffSize = a_stream.readSize();
	if (buffSize <= 0) {
		return ;
	}
	CBufferInt8::push(a_stream.readPtr(), buffSize);
}

CStream& CStream::read(char* pBuf, uint32 size) 
{
	if (!CBufferInt8::readReady()) {
		throw CException("数据长度不够");
	}
	uint32 buffSize = CBufferInt8::readSize();
	if (size <= buffSize){
		memcpy(pBuf, CBufferInt8::readPtr(), size);
		CBufferInt8::readFlip(size);
	} else {
		//memcpy(pBuf, CBufferInt8::readPtr(), buffSize);
		//CBufferInt8::readFlip(buffSize);
		throw CException("数据长度不够");
	}
	return *this;
}

CStream& CStream::write(const char* pBuf, uint32 size)
{
	CBufferInt8::push(pBuf, size);
	return *this;
}

bool CStream::copyTo(CStream& a_stream)
{
	uint32 buffSize = CBufferInt8::readSize();
	if (buffSize <= 0) {
		return true;
	}
	return a_stream.push(CBufferInt8::readPtr(), buffSize);
}

CStream& CStream::operator <<(const CStream& val)
{
	if (!val.readReady()) {
		return *this;
	}
	uint32 buffSize = val.readSize();
	CBufferInt8::push(val.readPtr(), buffSize);

	return *this;
}

CStream& CStream::operator <<(const char val[])
{
	uint32 buffSize = (uint32)strlen(val);
	CBufferInt8::push(val, buffSize);

	return *this;
}

CStream& CStream::operator >>(CStream& val)
{
	if (!CBufferInt8::readReady()) {
		return *this;
	}

	uint32 buffSize = CBufferInt8::readSize();
	val.push(CBufferInt8::readPtr(), buffSize);

	return *this;
}

CStream& CStream::operator =(const CStream& a_stream)
{
	uint32 buffSize = a_stream.readSize();
	if (buffSize <= 0) {
		return *this;
	}
	CBufferInt8::push(a_stream.readPtr(), buffSize);
	return *this;
}

}//Utility

}//BSLib

