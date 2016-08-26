#ifndef __BSLIB_NETWORK_NETSTUBMGR_H__
#define __BSLIB_NETWORK_NETSTUBMGR_H__

#include <BSLib/utility/thread/mutex.h>
#include <BSLib/utility/hashMap.h>
#include <BSLib/utility/uniqueID.h>
#include <BSLib/network/netStub.h>

namespace BSLib
{

namespace Network
{

class BSLIB_NETWORK_API CNetStubMgr 
    : public BSLib::Utility::CUniqueIDMgr<StubID>
{
public:
	CNetStubMgr();
	virtual ~CNetStubMgr();

	bool addStub(CNetStubPtr& stub);
	bool delStub(CNetStubPtr& stub);
	void clear();

	CNetStubPtr getNetStubByStubID(StubID stubID);

protected:
	bool _INetConnection_os_send(StubID stubID, BSLib::Utility::CStream& stream);
	bool _INetConnection_os_send(StubID stubID, const void* msgBuff, uint32 buffSize);

private:
	virtual bool checkUniqueID(StubID id) override;

protected:
	BSLib::Utility::CMutex m_mutex;
	BSLib::Utility::CHashMap<StubID, CNetStubPtr> m_stubHashMap;
	BSLib::Utility::CUniqueID<StubID> m_uniqueStubID;

};

}//Network

}//BSLib

#endif//__BSLIB_NETWORK_NETSTUBMGR_H__


