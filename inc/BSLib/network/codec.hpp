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
    virtual int ICodec_encoder(INetConnection* conn, const void* msgBuff, unsigned int buffSize, BSLib::Utility::CStream& stream) = 0;

};

} // Network

} // BSLib

