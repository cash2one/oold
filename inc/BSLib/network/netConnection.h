#ifndef __BSLIB_NETWORK_NETCONNECTION_H__
#define __BSLIB_NETWORK_NETCONNECTION_H__

#include <BSLib/utility/pointer.h>
#include <BSLib/utility/buffer.h>
#include <BSLib/utility/thread/mutex.h>
#include <BSLib/utility/stream.h>
#include <BSLib/network/sockAddr.h>

namespace BSLib
{

namespace Network
{

class CEncrypt
{
public:
	virtual ~CEncrypt(){}
	virtual int encrypt(const void* inData, unsigned int inSize, void* outBuff, unsigned int& outSize, bool isEncrypt) = 0;
};

class CCompress
{
public:
	virtual ~CCompress(){}
	virtual int compress(const void* inData, unsigned int inSize, void* outBuff, unsigned int& outSize, bool isCompress) = 0;
};

struct SNetConnectionBytesInfor 
{
	BSLib::uint64 m_recvBytes;
	BSLib::uint64 m_sendBytes;
};

class INetConnectionMgr;

class BSLIB_NETWORK_API CNetConnection
{
public:
	CNetConnection(CEncrypt* ptrEncrypt, CCompress* ptrCompress);
	virtual ~CNetConnection();

	virtual bool recvToBuffFromNet();
	virtual bool sendToNetFromBuff() = 0;

	virtual bool isEmptyOfSendBuff() = 0;

	void setEncrypt(CEncrypt* ptrEncrypt) { m_encrypt = ptrEncrypt; }
	void setCompress(CCompress* ptrCompress) { m_compress = ptrCompress; }

	int send(BSLib::Utility::CStream& stream, bool useBuffer = false);
	int send(const void* msgBuff, unsigned int buffSize, bool useBuffer = false);
	int recv(BSLib::Utility::CStream& stream);
	int recvBlock(BSLib::Utility::CStream& stream, int countMax = 0);

	virtual bool connect(CSockAddr& addrServer, int connMax = 0) = 0;
	virtual bool connect(CSockAddr& addrLocal, CSockAddr& addrServer, int connMax = 0) = 0;
	
	virtual int getSockect() = 0;
	virtual ENetType getSockectType() = 0;
	virtual void close();
	virtual bool isValid() = 0;

	const CSockAddr& getLocalAddr() { return m_localAddr; }
	const CSockAddr& getPeerAddr() { return m_peerAddr; }

	void setNetConnectionMgr(INetConnectionMgr* connMgr) { m_netConnectMgr = connMgr; }
	INetConnectionMgr* getNetConnectionMgr() { return m_netConnectMgr; }

	void getNetConnectionInfor(SNetConnectionBytesInfor& a_connectionInfor);

protected:
	virtual int _send(const void* dataBuff, int buffSize) = 0;
	virtual int _recv(void* dataBuff, int buffSize) = 0;
	virtual void _waitForSend();
	virtual void _waitForRecv();
	virtual void _postSend() {}

	virtual BSLib::uint64 _getSendBytes() { return 0; }
	virtual BSLib::uint64 _getRecvBytes() { return 0; }

	void _setLocalAddr(const CSockAddr& addr) { m_localAddr = addr; }
	void _setPeerAddr(const CSockAddr& addr) { m_peerAddr = addr; }

	virtual int _writeToBuff(const void* data, unsigned int len, unsigned int sign) = 0;
	virtual int _sendToNet(const void* data, unsigned int len, unsigned int sign) = 0;

	int _encrypt(const char* inData, unsigned int inLen, Utility::CBufferInt8& outBuff);
	int _decrypt(const char* inData, unsigned int inLen, Utility::CBufferInt8& outBuff);
	int _compress(const char* inData, unsigned int inLen, Utility::CBufferInt8& outBuff);
	int _uncompress(const char* inData, unsigned int inLen, Utility::CBufferInt8& outBuff);

	unsigned int _mergerPacket(Utility::CBufferInt8& inBuff, Utility::CBufferInt8& outBuff);

	void _clearBuff();

private:
	CEncrypt* m_encrypt;
	CCompress* m_compress;
	CSockAddr m_localAddr;
	CSockAddr m_peerAddr;
	Utility::CBufferInt8 m_recvBuff;
	INetConnectionMgr* m_netConnectMgr;
};
typedef BSLib::Utility::CPointer<CNetConnection> CNetConnectionPtr;

class BSLIB_NETWORK_API CNetConnectionCallback
{
public:
	virtual ~CNetConnectionCallback(){}
	virtual bool recvMsg(CNetConnectionPtr& connection) = 0;
	virtual void terminate(CNetConnectionPtr& connection) = 0;
};
typedef BSLib::Utility::CPointer<CNetConnectionCallback> CNetConnectionCallbackPtr;

}//Network

}//BSLib

#endif//__BSLIB_NETWORK_NETCONNECTION_H__

