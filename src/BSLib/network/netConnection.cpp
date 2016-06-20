//////////////////////////////////////////////////////////////////////
//	created:	2012/07/24
//	filename:	src\BSLib\network\netConnection.cpp
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/thread/thread.h>
#include <BSLib/network/netConnection.h>
#include <BSLib/network/tcpConnectionMgr.h>
#include "netinit.h"

namespace BSLib
{

namespace Network
{

	//数据包标志
#define GNET_PACKET_FLAG		0X80000000
	//数据包压缩
#define GNET_PACKET_COMPRESS	0X40000000
	//数据包加密
#define GNET_PACKET_ENCRYPT		0X20000000
	//数据包连包
#define GNET_PACKET_NEXT		0X10000000
	//数据控制标志
#define GNET_PACKET_SIGN		0XFF000000
	//数据包长度
#define GNET_PACKET_LEN			0X00FFFFFF

CNetConnection::CNetConnection(CEncrypt* ptrEncrypt, CCompress* ptrCompress)
: m_encrypt(ptrEncrypt)
, m_compress(ptrCompress)
, m_netConnectMgr(NULL)
{
	;
}

CNetConnection::~CNetConnection()
{
	;
}

bool CNetConnection::recvToBuffFromNet()
{
 	int len = 0;
	
	do {
		if (!m_recvBuff.writeReserve(RECV_BUFF)){
			return false;
		}
		len = _recv(m_recvBuff.writePtr(), RECV_BUFF);
		if (len < 0) {
			return false;
		}
		if (len == 0) {
			return true;
		}
		m_recvBuff.writeFlip(len);
	} while(len == RECV_BUFF);

	return true;
}

void CNetConnection::getNetConnectionInfor(SNetConnectionBytesInfor& a_connectionInfor)
{
	a_connectionInfor.m_recvBytes = _getRecvBytes();
	a_connectionInfor.m_sendBytes = _getSendBytes();
}

void CNetConnection::_waitForSend()
{
	Utility::CThread::msleep(100);
}

void CNetConnection::_waitForRecv()
{
	Utility::CThread::msleep(100);
}

int CNetConnection::send(Utility::CStream& stream, bool useBuffer)
{
	if (!isValid()){
		return -1;
	}
	int sendSize = send(stream.readPtr(), stream.readSize(), useBuffer);
	if (sendSize > 0) {
		stream.readFlip(sendSize);
	}
	return sendSize;
}

int CNetConnection::send(const void* msgBuff, unsigned int buffSize, bool useBuffer)
{
	if (!isValid()){
		return -1;
	}
	unsigned int flag = GNET_PACKET_FLAG;
	if (m_compress != NULL && buffSize >= 32) {
		Utility::CBufferInt8 compressBuff;
		if (_compress((char*)msgBuff, buffSize, compressBuff) < 0){
			return -1;
		}
		flag |= GNET_PACKET_COMPRESS;
		if (m_encrypt != NULL) {
			Utility::CBufferInt8 encryptBuff;
			if (_encrypt(compressBuff.readPtr(), compressBuff.readSize(), encryptBuff) < 0){
				return -1;
			}
			flag |= GNET_PACKET_ENCRYPT;
			if (useBuffer){
				return _writeToBuff(encryptBuff.readPtr(), encryptBuff.readSize(), flag);
			}
			return _sendToNet(encryptBuff.readPtr(), encryptBuff.readSize(), flag);
		}

		if (useBuffer){
			return _writeToBuff(compressBuff.readPtr(), compressBuff.readSize(), flag);
		}
		return _sendToNet(compressBuff.readPtr(), compressBuff.readSize(), flag);
	}
	if (m_encrypt != NULL) {
		Utility::CBufferInt8 encryptBuff;
		if (_encrypt((char*)msgBuff, buffSize, encryptBuff) < 0){
			return -1;
		}
		flag |= GNET_PACKET_ENCRYPT;
		if (useBuffer){
			return _writeToBuff(encryptBuff.readPtr(), encryptBuff.readSize(), flag);
		}
		return _sendToNet(encryptBuff.readPtr(), encryptBuff.readSize(), flag);
	}
	if (useBuffer){
		return _writeToBuff(msgBuff, buffSize, flag);
	}
	return _sendToNet(msgBuff, buffSize, flag);
}

int CNetConnection::recv(BSLib::Utility::CStream& stream)
{
	unsigned int buffLen = m_recvBuff.readSize();
	if (buffLen < sizeof(unsigned int)){
		return 0;
	}

	Utility::CBufferInt8 recvBuff;
	int res = _mergerPacket(m_recvBuff, recvBuff);
	if (res <= 0) {
		return res;
	}

	unsigned int cmdFlag = *((unsigned int*)recvBuff.readPtr());
	unsigned int len = recvBuff.readSize() - sizeof(unsigned int);
	unsigned int flag = cmdFlag & GNET_PACKET_SIGN;
	const char* buff = recvBuff.readPtr();
	
	if (!(flag & GNET_PACKET_FLAG)){
		return -1;
	}
	
	if (flag & GNET_PACKET_ENCRYPT) {
		if (m_encrypt == NULL){
			return -1;
		}
		Utility::CBufferInt8 encryptBuff;
		if (_decrypt(&buff[sizeof(unsigned int)], len, encryptBuff) < 0) {
			return -1;
		}
		if (m_compress != NULL && (flag & GNET_PACKET_COMPRESS)){
			Utility::CBufferInt8 compressBuff;
			if (_uncompress(encryptBuff.readPtr(), encryptBuff.readSize(), compressBuff) < 0) {
				return -1;
			}
			stream.push(compressBuff.readPtr(), compressBuff.readSize());
			return compressBuff.readSize();
		}
		stream.push(encryptBuff.readPtr(), encryptBuff.readSize());
		return encryptBuff.readSize();
	}

	if (m_compress != NULL && (flag & GNET_PACKET_COMPRESS)){
		Utility::CBufferInt8 compressBuff;
		if (_uncompress(&buff[sizeof(unsigned int)], len, compressBuff) < 0) {
			return -1;
		}
		stream.push(compressBuff.readPtr(), compressBuff.readSize());
		return compressBuff.readSize();
	}

	stream.push(&buff[sizeof(unsigned int)], len);
	return len;
}

int CNetConnection::recvBlock(BSLib::Utility::CStream& stream, int countMax)
{
	int recvSize = 0;
	int count = 0;
	do{
		++count;
		if(!recvToBuffFromNet()) {
			return -1;
		}
		if ((recvSize = recv(stream)) != 0){
			break;
		}
		if (countMax != 0 && count >= countMax){
			return -1;
		}
		_waitForRecv();
	} while (recvSize == 0);
	return recvSize;
}

void CNetConnection::close()
{
	_clearBuff();
}

int CNetConnection::_encrypt(const char* inData, unsigned int inLen, Utility::CBufferInt8& outBuff)
{
	if (!outBuff.writeReserve(inLen * 2 + sizeof(unsigned int))){
		return -1;
	}

	if (!outBuff.push((char*)&inLen, sizeof(inLen))) {
		return -1;
	}
	unsigned int outSize = outBuff.writeSize();
	int resEncrypt = m_encrypt->encrypt(inData, inLen, outBuff.writePtr(), outSize, true);
	if (resEncrypt < 0) {
		outBuff.reset();
		return -1;
	}
	outBuff.writeFlip(outSize);

	return resEncrypt;
}

int CNetConnection::_decrypt(const char* inData, unsigned int inLen, Utility::CBufferInt8& outBuff)
{
	if (inLen < sizeof(unsigned int)){
		return -1;
	}
	unsigned int outLen = *((unsigned int*)inData);
	if (!outBuff.writeReserve(outLen * 2)){
		return -1;
	}
	unsigned int encryptInLen = inLen - sizeof(unsigned int);
	unsigned int outSize = outBuff.writeSize();
	int resEncrypt = m_encrypt->encrypt(&inData[sizeof(unsigned int)], encryptInLen, outBuff.writePtr(), outSize, false);
	if (resEncrypt < 0) {
		outBuff.reset();
		return -1;
	}
	if (outSize != outLen){
		outBuff.reset();
		return -1;
	}
	outBuff.writeFlip(outSize);

	return resEncrypt;
}

int CNetConnection::_compress(const char* inData, unsigned int inLen, Utility::CBufferInt8& outBuff)
{
	if (!outBuff.writeReserve(inLen * 2 + sizeof(unsigned int))){
		return -1;
	}
	if (!outBuff.push((char*)&inLen, sizeof(inLen))) {
		return -1;
	}
	unsigned int outSize = outBuff.writeSize();
	int resCompress = m_compress->compress(inData, inLen, outBuff.writePtr(), outSize, true);
	if (resCompress < 0) {
		outBuff.reset();
		return -1;
	}
	outBuff.writeFlip(outSize);

	return resCompress;
}

int CNetConnection::_uncompress(const char* inData, unsigned int inLen, Utility::CBufferInt8& outBuff)
{
	if (inLen < sizeof(unsigned int)){
		return -1;
	}
	unsigned int outLen = *((unsigned int*)inData);
	if (!outBuff.writeReserve(outLen * 2)){
		return -1;
	}
	unsigned int outSize = outBuff.writeSize();
	int compressInLen = inLen - sizeof(unsigned int);
	int resCompress = m_compress->compress(&inData[sizeof(unsigned int)], compressInLen, outBuff.writePtr(), outSize, false);
	if (resCompress < 0) {
		outBuff.reset();
		return -1;
	}
	if (outSize != outLen){
		outBuff.reset();
		return -1;
	}
	outBuff.writeFlip(outSize);

	return resCompress;
}

unsigned int CNetConnection::_mergerPacket(Utility::CBufferInt8& inBuff, Utility::CBufferInt8& outBuff)
{
	//验证数据包是否完成
	unsigned int cmdFlag = *((unsigned int*)inBuff.readPtr());
	unsigned int len = cmdFlag & GNET_PACKET_LEN;
	unsigned int flag = cmdFlag & GNET_PACKET_SIGN;
	const char* buff = inBuff.readPtr();
	unsigned int dataSize = len + sizeof(unsigned int);
	
	while (flag & GNET_PACKET_NEXT) {
		if (dataSize + sizeof(unsigned int) > inBuff.readSize()) {
			return 0;
		}

		cmdFlag = *((unsigned int*) &buff[dataSize]);
		len = cmdFlag & GNET_PACKET_LEN;
		flag = cmdFlag & GNET_PACKET_SIGN;
		dataSize += len + sizeof(unsigned int);
	}
	if (dataSize > inBuff.readSize()) {
		return 0;
	}

	//组装数据包
	cmdFlag = *((unsigned int*)inBuff.readPtr());
	len = cmdFlag & GNET_PACKET_LEN;
	flag = cmdFlag & GNET_PACKET_SIGN;
	buff = inBuff.readPtr();
	dataSize = len + sizeof(unsigned int);
	
	outBuff.push((char*)&flag, sizeof(unsigned int));
	unsigned int readPos = sizeof(unsigned int);

	while (flag & GNET_PACKET_NEXT) {
		outBuff.push(&buff[readPos], len);
		readPos += len;

		cmdFlag = *((unsigned int*) &buff[dataSize]);
		len = cmdFlag & GNET_PACKET_LEN;
		flag = cmdFlag & GNET_PACKET_SIGN;
		dataSize += len + sizeof(unsigned int);
		readPos += sizeof(unsigned int);
	}
	outBuff.push(&buff[readPos], len);
	inBuff.readFlip(dataSize);

	return outBuff.readSize();
}

void CNetConnection::_clearBuff()
{
	m_recvBuff.reset();
}

}//Network

}//BSLib

