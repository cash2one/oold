#pragma once
#include <BSLib/network/tcpConnection.h>

namespace BSLib
{

namespace Network
{
    class BSLIB_NETWORK_API CRawTcpConnection 
        :public CTcpConnection
    {
    public:
        CRawTcpConnection(SOCKET sock = INVALID_SOCKET, IEncrypt* ptrEncrypt = NULL, ICompress* ptrCompress = NULL, ICodec* ptrCodec = NULL)
            :CTcpConnection(sock, ptrEncrypt, ptrCompress, ptrCodec)
        {
        }

        virtual ~CRawTcpConnection();


    protected:
        virtual int _writeToBuff(const void* data, unsigned int len, unsigned int sign, Utility::CBufferInt8& sendBuff) override
        {
            // push data
            if (!sendBuff.push((char*)data, len))
            {
                return -1;
            }

            return len;
        }

    };
}

}