#pragma  once
#include <BSLib/utility/stream.h>

namespace BSLib
{
namespace Network
{

class INetConnection;

class ICodec
{
public:
    virtual void ICodec_onMessage(INetConnection* conn) = 0;
    virtual void ICodec_send(INetConnection* conn, BSLib::Utility::CStream& stream, bool useBuffer = false) = 0;
    virtual void ICodec_send(INetConnection* conn, const void* msgBuff, unsigned int buffSize, bool useBuffer = false) = 0;

};

} // Network

} // BSLib

