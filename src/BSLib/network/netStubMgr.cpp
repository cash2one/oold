#include <BSLib/network/netStubMgr.h>

namespace BSLib
{

namespace Network
{

CNetStubMgr::CNetStubMgr()
{
	m_uniqueStubID.setUniqueIDMgr(this);
}

CNetStubMgr::~CNetStubMgr()
{
	m_stubHashMap.clear();
}

bool CNetStubMgr::addStub(CNetStubPtr& stub)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);

	uint32 stubID = stub->getStubID();
	if (stubID != INVALID_STUBID){
		return false;
	}
	stubID = m_uniqueStubID.allocateID();
	stub->_setStubID(stubID);
	m_stubHashMap.setValue(stubID, stub);
	return true;
}

bool CNetStubMgr::delStub(CNetStubPtr& stub)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);
	uint32 stubID = stub->getStubID();
	if (stubID == 0){
		return false;
	}
	m_stubHashMap.remove(stubID);
	return true;
}

void CNetStubMgr::clear()
{
	BSLib::Utility::CMutexFun fun(&m_mutex);
	m_stubHashMap.clear();
}

CNetStubPtr CNetStubMgr::getNetStubByStubID(StubID stubID)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);
	if (m_stubHashMap.find(stubID) == m_stubHashMap.end()) {
		return CNetStubPtr(NULL);
	}
	return m_stubHashMap.getValue(stubID);
}

bool CNetStubMgr::_INetConnection_send(StubID stubID, BSLib::Utility::CStream& stream)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);
	CNetStubPtr& stub = m_stubHashMap.getValue(stubID);
	if (stub == NULL){
		return false;
	}
	return stub->send(stream) > 0;
}

bool CNetStubMgr::_INetConnection_send(StubID stubID, const void* msgBuff, uint32 buffSize)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);
	CNetStubPtr& stub = m_stubHashMap.getValue(stubID);
	if (stub == NULL){
		return false;
	}
	return stub->send(msgBuff, buffSize) > 0;
}

bool CNetStubMgr::checkUniqueID(StubID a_stubID)
{
	CNetStubPtr& stub = m_stubHashMap.getValue(a_stubID);
	return stub != NULL;
}

}//Network

}//BSLib


