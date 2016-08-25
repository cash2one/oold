#ifndef __BSLIB_NETWORK_NETCONNECTION_H__
#define __BSLIB_NETWORK_NETCONNECTION_H__

#include <BSLib/utility/pointer.h>
#include <BSLib/utility/buffer.h>
#include <BSLib/utility/thread/mutex.h>
#include <BSLib/utility/stream.h>
#include <BSLib/network/sockAddr.h>
#include <BSLib/network/codec.hpp>

namespace BSLib
{

namespace Network
{

class IEncrypt
{
public:
	virtual ~IEncrypt(){}
	virtual int encrypt(const void* inData, unsigned int inSize, void* outBuff, unsigned int& outSize, bool isEncrypt) = 0;
};

class ICompress
{
public:
	virtual ~ICompress(){}
	virtual int compress(const void* inData, unsigned int inSize, void* outBuff, unsigned int& outSize, bool isCompress) = 0;
};

struct SNetConnectionBytesInfo 
{
	BSLib::uint64 m_recvBytes;
	BSLib::uint64 m_sendBytes;
};

class INetConnectionMgr;

class BSLIB_NETWORK_API INetConnection
{
public:
	INetConnection(IEncrypt* ptrEncrypt, ICompress* ptrCompress, ICodec* ptrCodec);
	virtual ~INetConnection();

	virtual bool INetConnection_recvToBuffFromNet();
	virtual bool INetConnection_sendToNetFromBuff() = 0;

	virtual bool INetConnection_isEmptyOfSendBuff() = 0;

	void setEncrypt(IEncrypt* ptrEncrypt) { m_encrypt = ptrEncrypt; }
	void setCompress(ICompress* ptrCompress) { m_compress = ptrCompress; }

	int send(BSLib::Utility::CStream& stream, bool useBuffer = false);
	int send(const void* msgBuff, unsigned int buffSize, bool useBuffer = false);
	int recv(BSLib::Utility::CStream& stream);
	int recvBlock(BSLib::Utility::CStream& stream, int countMax = 0);

	virtual bool INetConnection_connect(CSockAddr& addrServer, int connMax = 0) = 0;
	virtual bool INetConnection_connect(CSockAddr& addrLocal, CSockAddr& addrServer, int connMax = 0) = 0;
	
	virtual int INetConnection_getSockect() = 0;
	virtual ENetType INetConnection_getSockectType() = 0;
	virtual void INetConnection_close();
	virtual bool INetConnection_isValid() = 0;

	const CSockAddr& getLocalAddr() { return m_localAddr; }
	const CSockAddr& getPeerAddr() { return m_peerAddr; }

	void setNetConnectionMgr(INetConnectionMgr* connMgr) { m_netConnectMgr = connMgr; }
	INetConnectionMgr* getNetConnectionMgr() { return m_netConnectMgr; }

	void getNetConnectionInfo(SNetConnectionBytesInfo& a_connectionInfo);

protected:
	virtual int _INetConnection_send(const void* dataBuff, int buffSize) = 0; // 系统级调用 tcp udp api
	virtual int _INetConnection_recv(void* dataBuff, int buffSize) = 0;       // 同上
	virtual void _INetConnection_waitForSend();
	virtual void _INetConnection_waitForRecv();
	virtual void _INetConnection_postSend() {}

	virtual BSLib::uint64 _INetConnection_getSendBytes() { return 0; }
	virtual BSLib::uint64 _INetConnection_getRecvBytes() { return 0; }

	void _setLocalAddr(const CSockAddr& addr) { m_localAddr = addr; }
	void _setPeerAddr(const CSockAddr& addr) { m_peerAddr = addr; }

    // 接口在这里...
	virtual int _INetConnection_writeToBuff(const void* data, unsigned int len, unsigned int sign) = 0; 
	virtual int _INetConnection_sendToNet(const void* data, unsigned int len, unsigned int sign) = 0;

	int _encrypt(const char* inData, unsigned int inLen, Utility::CBufferInt8& outBuff);
	int _decrypt(const char* inData, unsigned int inLen, Utility::CBufferInt8& outBuff);
	int _compress(const char* inData, unsigned int inLen, Utility::CBufferInt8& outBuff);
	int _uncompress(const char* inData, unsigned int inLen, Utility::CBufferInt8& outBuff);

	unsigned int _mergeRecvPacket(Utility::CBufferInt8& inBuff, Utility::CBufferInt8& outBuff);

	void _clearBuff();

private:
	IEncrypt* m_encrypt;
	ICompress* m_compress;
    ICodec*    m_codec;
	CSockAddr m_localAddr;
	CSockAddr m_peerAddr;
	Utility::CBufferInt8 m_recvBuff;
	INetConnectionMgr* m_netConnectMgr;
};
typedef BSLib::Utility::CPointer<INetConnection> CNetConnectionPtr;

class BSLIB_NETWORK_API INetConnectionCallback
{
public:
	virtual ~INetConnectionCallback(){}
	virtual bool recvMsg(CNetConnectionPtr& connection) = 0;
	virtual void terminate(CNetConnectionPtr& connection) = 0;
};
typedef BSLib::Utility::CPointer<INetConnectionCallback> INetConnectionCallbackPtr;

}//Network

}//BSLib

#endif//__BSLIB_NETWORK_NETCONNECTION_H__

