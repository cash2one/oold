//////////////////////////////////////////////////////////////////////
//	created:	2012/07/20
//	filename: 	BSLib\utility\stream.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UTILITY_STREAM_H__
#define __BSLIB_UTILITY_STREAM_H__

#include <BSLib/utility/string.h>
#include <BSLib/utility/buffer.h>
#include <BSLib/utility/exception.h>

namespace BSLib
{

namespace Utility
{

class BSLIB_UTILITY_API CStream : public CBufferInt8
{
public:
	CStream();
	CStream(const CStream& a_stream);

	CStream& read(char* pBuf, uint32 size);
	CStream& write(const char* pBuf, uint32 size);


	bool copyTo(CStream& a_stream);

	template<typename TYPE>
	CStream& operator <<(const TYPE& val) { return write((char*)&val, sizeof(val)); }

	template<typename TYPE>
	CStream& operator <<(const std::vector<TYPE>& val) { return _writeVector(val); }

	/// @brief 把val的内容追加到后面，但不改变val的内容
	/// @return CStream&
	/// @param val
	CStream& operator <<(const CStream& val);
	CStream& operator <<(const char val[]);

	CStream& operator <<(const std::string& val)  { return _writeString(val); }
	CStream& operator <<(const std::wstring& val) { return _writeString(val); }
	CStream& operator <<(const CStringA& val)  { return _writeString(val); }
	CStream& operator <<(const CStringW& val) { return _writeString(val); }

	template<typename TYPE>
	CStream& operator >>(TYPE& val) { return read((char*)&val, sizeof(val)); }

	template<typename TYPE>
	CStream& operator >>(std::vector<TYPE>& val) { return _readVector(val); }

	CStream& operator >>(CStream& val);
	CStream& operator >>(std::string& val) { return _readString(val); }
	CStream& operator >>(std::wstring& val) { return _readString(val); }
	CStream& operator >>(CStringA& val) { return _readString(val); }
	CStream& operator >>(CStringW& val) { return _readString(val); }

	CStream& operator =(const CStream& a_stream);

private:
	template<typename T> 
	CStream& _readString(T& str);

	template<typename T> 
	CStream& _writeString(const T& str);

	template<typename T> 
	CStream& _readVector(std::vector<T>& val);

	template<typename T> 
	CStream& _writeVector(const std::vector<T>& val);
};

template<typename T> 
CStream& CStream::_readString(T& str)
{
	typedef typename T::value_type ValueType;
	typedef typename T::size_type SizeType;

	unsigned int sizeBytes = 0;
	CBufferInt8::pop((char*)&sizeBytes, sizeof(sizeBytes));
	if (sizeBytes <= 0){
		return *this;
	}
	unsigned int buffSize = CBufferInt8::readSize();
	SizeType size = sizeBytes / sizeof(ValueType);

	if (sizeBytes <= buffSize){
		ValueType* pData = (ValueType*)CBufferInt8::readPtr();
		str.assign(pData, size);
		CBufferInt8::readFlip(sizeBytes);
	} else {
		throw CException("数据长度不够");
	}
	return *this;
}

template<typename T> 
CStream& CStream::_writeString(const T& str)
{
	typedef typename T::value_type ValueType;

	unsigned int sizeBytes = (unsigned int)str.size() * sizeof(ValueType);
	CBufferInt8::push((char*)&sizeBytes, sizeof(sizeBytes));
	if (sizeBytes > 0) {
		CBufferInt8::push((char*)str.c_str(), sizeBytes);
	}
	return *this;
}

template<typename T> 
CStream& CStream::_readVector(std::vector<T>& val)
{
	typedef typename std::vector< T >::value_type ValueType;
	typedef typename std::vector< T >::size_type SizeType;

	unsigned int sizeBytes = 0;
	CBufferInt8::pop((char*)&sizeBytes, sizeof(sizeBytes));
	if (sizeBytes <= 0){
		return *this;
	}
	unsigned int buffSize = CBufferInt8::readSize();
	SizeType size = sizeBytes / sizeof(ValueType);

	if (sizeBytes <= buffSize){
		val.resize(size);
		CBufferInt8::pop((char*)&val[0], sizeBytes);
	} else {
		throw CException("数据长度不够");
	}
	return *this;
}

template<typename T> 
CStream& CStream::_writeVector(const std::vector<T>& val)
{
	typedef typename std::vector< T >::value_type ValueType;

	unsigned int sizeBytes = (unsigned int)val.size() * sizeof(ValueType);
	CBufferInt8::push((char*)&sizeBytes, sizeof(sizeBytes));
	if (sizeBytes > 0) {
		CBufferInt8::push((char*)&val[0], sizeBytes);
	}
	return *this;
}

}//Utility

}//BSLib

#endif // __BSLIB_UTILITY_STREAM_H__
