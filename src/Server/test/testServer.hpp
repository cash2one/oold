#pragma  once
#include <BSLib/network/netServer.h>
#include <BSLib/network/netStub.h>

using namespace BSLib::Network;

class MyStub
    :public INetStub
{   
public:
    MyStub(CNetConnectionPtr& netConnection)
        :INetStub(netConnection)
    {
    }

    virtual void INetStub_initStub() override
    {
    }

    virtual void INetStub_finalStub() override
    {
    }

    virtual void INetStub_cbNotifyPing() override
    {
    }

    virtual bool INetStub_cbParseMsg(void* msgBuff, uint32_t msgSize) override
    {
        return true;
    }

    virtual void INetStub_cbTerminate() override
    {

    }
};


class MyServer
    :public BSLib::Network::INetServer
{
public:
    MyServer()
    {   
        _addTcpAccpetor("127.0.0.1", 1001, 0);
        _setTcpStubPool(10, 2, 5);
        _INetServer_init();

    }

    virtual CNetStubMgr* _INetServer_cbNetStubMgr() override
    {
        return new CNetStubMgr;
    }

    virtual CNetStubPtr _INetServer_cbNewTcpStub(BSLib::Network::CNetConnectionPtr& netConnPtr, void* tempData) override
    {
        return new MyStub(netConnPtr);
    }

    virtual CNetStubPtr _INetServer_cbNewUdpStub(BSLib::Network::CNetConnectionPtr& netConnPtr, void* tempData) override
    {
        return nullptr;
    }

};

#include <conio.h>
class  TestServer
{
public:
    static void run()
    {
        MyServer server;
        _getch();
    }
};