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
    virtual ~ICodec() {}

    enum { eOK, eMoreData };

    virtual int ICodec_decoder(INetConnection* conn, BSLib::Utility::CStream& stream) = 0;
    virtual void ICodec_encoder(INetConnection* conn, const void* msgBuff, unsigned int buffSize, bool useBuffer = false) = 0;

};

} // Network

} // BSLib

