#ifndef __BSLIB_UTILITY_BUFFER_H__
#define __BSLIB_UTILITY_BUFFER_H__

#include <BSLib/utility/baseDef.h>

namespace BSLib
{

namespace Utility
{

//  缓冲区，现在支持 typedef CBuffer< std::vector<char>, char> CBufferInt8;
//  如果要支持其他类型的缓冲区，需要自行实现init、writeReserve 

template<typename BUFFTYPE, typename ITEMTYPE = unsigned char>
class CBuffer
{
public:
	CBuffer() : m_bufferMaxSize(0), m_readPosition(0), m_writePosition(0)
	{
		init();
	}
	
	virtual ~CBuffer() {}

	// 初始化
	inline void init();

	// 申请空间
	inline bool writeReserve(uint32 size);

	// 写入数据
	// return 写入是否成功
	bool push(const ITEMTYPE* data, uint32 size)
	{
		if (data == NULL) {
			return false;
		}
		if (size <=0 ) {
			return false;
		}
		if (!writeReserve(size)){
			return false;
		}
		memcpy(&m_buffer[m_writePosition], data, size);
		writeFlip(size);
		return true;
	}

	// 读出所有的可读的数据
	// return 实际读取的长度
	uint32 pop(ITEMTYPE* buff, uint32 buffSize)
	{
		if (buff == NULL) {
			return 0;
		}
		uint32 size = readSize();
		if (size <= 0){
			return 0;
		}
		if (buffSize < size){
			size = buffSize;
		}
		memcpy(buff, &m_buffer[m_readPosition], size);
		readFlip(size);
		return size;
	}

	// 可写地址
	ITEMTYPE* writePtr()
	{
		uint32 tmp = m_writePosition - m_readPosition;
		if (m_readPosition >= tmp){
			memmove(&m_buffer[0], &m_buffer[m_readPosition], tmp);
			m_readPosition = 0;
			m_writePosition = tmp;
		}

		return &m_buffer[m_writePosition];
	}

	// 可读地址
	const ITEMTYPE* readPtr() const
	{
		return &m_buffer[m_readPosition];
	}

	// 是否可读
	bool readReady() const
	{
		return m_writePosition - m_readPosition > 0;
	}

	// 可读空间大小
	uint32 readSize() const
	{
		return m_writePosition - m_readPosition;
	}

	// 可写空间大小
	uint32 writeSize() const
	{
		return m_bufferMaxSize - m_writePosition;
	}

	void reset()
	{
		m_readPosition = 0;
		m_writePosition = 0;
	}

	void readFlip(uint32 size)
	{
		m_readPosition += size;
		if (m_readPosition >= m_writePosition) {
			m_readPosition = 0;
			m_writePosition = 0;
		}
	}

	bool writeFlip(uint32 size)
	{
		if (m_writePosition + size > m_bufferMaxSize){
			return false;
		}
		m_writePosition += size;

		uint32 tmp = m_writePosition - m_readPosition;
		if (m_readPosition >= tmp){
			memmove(&m_buffer[0], &m_buffer[m_readPosition], tmp);
			m_readPosition = 0;
			m_writePosition = tmp;
		}

		return true;
	}

	uint32 getBuffMaxSize() { return m_bufferMaxSize; }
	uint32 getReadPosition() { return m_readPosition; }
	uint32 getWritePosition() { return m_writePosition; }

private:
	//缓冲区当前大小
	uint32 m_bufferMaxSize;
	uint32 m_readPosition;
	uint32 m_writePosition;
	BUFFTYPE m_buffer;
};

typedef CBuffer< std::vector<char>, char> CBufferInt8;

template <>
inline void CBufferInt8::init()
{
	m_bufferMaxSize = 8;
	m_buffer.resize(m_bufferMaxSize);
}

template <> 
inline bool CBufferInt8::writeReserve(uint32 reserveSize)
{
	if (writeSize() < reserveSize) {
		uint64 bufferMaxSize = (m_bufferMaxSize + reserveSize) * 2;
		if (bufferMaxSize >= BSLIB_UINT32_MAX) {
			return false;
		}
		m_bufferMaxSize = (m_bufferMaxSize + reserveSize) * 2;
		m_buffer.resize(m_bufferMaxSize);
	}
	return true;
}

}//Utility

}//BSLib

#endif // __BSLIB_UTILITY_BUFFER_H__

