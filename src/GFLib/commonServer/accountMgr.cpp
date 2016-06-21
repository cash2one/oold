#include <GFLib/commonServer/accountMgr.h>

namespace GFLib
{

namespace CommonServer
{

BSLIB_SINGLETON_DEFINE(CAccountMgr);

CAccountMgr::CAccountMgr()
{
	;
}

CAccountMgr::~CAccountMgr()
{
	;
}

bool CAccountMgr::addAccount(const CAccountPtr& a_accountPtr)
{
	if (a_accountPtr == NULL) {
		return false;
	}
	const SAccountKey& key = a_accountPtr->getAccountKey();

	BSLib::Utility::CMutexFun fun(&m_mutex);
	if (m_accountHashMap.find(key) != m_accountHashMap.end()) {
		return false;
	}
	m_accountHashMap.setValue(key, a_accountPtr);
	return true;
}

void CAccountMgr::delAccount(const SAccountKey& a_accountKey)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);

	m_accountHashMap.remove(a_accountKey);
}

CAccountPtr CAccountMgr::getAccount(const SAccountKey& a_accountKey)
{
	BSLib::Utility::CMutexFun fun(&m_mutex);
	if (m_accountHashMap.find(a_accountKey) == m_accountHashMap.end()) {
		return CAccountPtr(NULL);
	}
	return m_accountHashMap.getValue(a_accountKey);
}

}//CommonServer

}//GFLib
