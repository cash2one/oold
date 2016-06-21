#include <GFLib/commonServer/clientMgr.h>

namespace GFLib
{

namespace CommonServer
{

BSLIB_SINGLETON_DEFINE(CClientMgr);

CClientMgr::CClientMgr()
{
	;
}

CClientMgr::~CClientMgr()
{
   ;
}

void CClientMgr::addCommonClient(SServerID a_serverID, CCommonClientPtr& a_commonClient)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);

	m_clientHashMap.setValue(a_serverID.getServerID(), a_commonClient);
}

void CClientMgr::delCommonClient(SServerID a_serverID)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);

	m_clientHashMap.remove(a_serverID.getServerID());
}

CCommonClientPtr CClientMgr::getCommonClient(SServerID a_serverID)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);
	
	BSLib::Utility::CHashMap<ServerID, CCommonClientPtr>::iterator it = m_clientHashMap.find(a_serverID.getServerID());
	if (it == m_clientHashMap.end()) {
		return CCommonClientPtr(NULL);
	}
	return it->second;
}

void CClientMgr::final()
{
	std::vector<CCommonClientPtr> tmpList;
	m_mutex.lock();
	BSLib::Utility::CHashMap<ServerID, CCommonClientPtr>::iterator it = m_clientHashMap.begin();
	for (; it != m_clientHashMap.end(); ++it) {
		CCommonClientPtr& commonClient = it->second;
		if (commonClient != NULL) {
			tmpList.push_back(commonClient);
		}
	}
	m_mutex.unlock();

	for (BSLib::uint32 i=0; i<tmpList.size(); ++i){
		if (tmpList[i]->isValid()) {
			tmpList[i]->terminate();
			tmpList[i]->join();
		}
	}
	tmpList.clear();
	m_clientHashMap.clear();
}

}//CommonServer

}//GFLib



