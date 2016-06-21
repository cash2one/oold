#include "udpThreadMgr.h"

namespace BSLib
{

namespace UDM
{

BSLIB_SINGLETON_DEFINE(CUdpThreadMgr);

CUdpThreadMgr::CUdpThreadMgr()
: m_udpThreadCount(0)
{
	for (int i=0; i<BSLIB_NETWORK_UDPTHREAD_MAX; ++i) {
		m_udpThreads[i] = NULL;
	}
}

CUdpThreadMgr::~CUdpThreadMgr()
{
	clearAll();
}

int CUdpThreadMgr::getUdpThreadID(const struct sockaddr* name, int namelen)
{
	for (int i=0; i<m_udpThreadCount; ++i){
		if (m_udpThreads[i] == NULL) {
			continue;
		}
		if (m_udpThreads[i]->compareLocalAddr(name, namelen)) {
			return i + 1;
		}
	}
	return -1;
}

bool CUdpThreadMgr::bind(int& udpThreadID, const struct sockaddr* name, int namelen)
{
	int threadPos = -1;

	m_mutex.lock();
	for (int i=0; i<m_udpThreadCount; ++i){
		if (m_udpThreads[i] == NULL) {
			if (threadPos == -1) {
				threadPos = i;
			}
			continue;
		}
		if (m_udpThreads[i]->compareLocalAddr(name, namelen)) {
			udpThreadID = i + 1;
			m_mutex.unlock();
			return true;
		}
	}
	if (m_udpThreadCount >= BSLIB_NETWORK_UDPTHREAD_MAX) {
		if (threadPos == -1) {
			m_mutex.unlock();
			return false;
		}
	} else {
		threadPos = m_udpThreadCount;
		++m_udpThreadCount;
	}
	m_mutex.unlock();

	CUdpThread* udpThread = new CUdpThread(threadPos + 1);
	if (udpThread == NULL) {
		return false;
	}
	if (!udpThread->socket(name, namelen)) {
		BSLIB_SAFE_DELETE(udpThread);
		return false;
	}
	m_udpThreads[threadPos] = udpThread;
	udpThreadID = threadPos + 1;
	return true;
}

bool CUdpThreadMgr::bind(int& udpThreadID)
{
	int threadPos = -1;
	m_mutex.lock();
	for (int i=0; i<m_udpThreadCount; ++i){
		if (m_udpThreads[i] == NULL) {
			threadPos = i;
			break;
		}
	}
	if (m_udpThreadCount >= BSLIB_NETWORK_UDPTHREAD_MAX) {
		if (threadPos == -1) {
			m_mutex.unlock();
			return false;
		}
	} else {
		threadPos = m_udpThreadCount;
		++m_udpThreadCount;
	}
	m_mutex.unlock();

	CUdpThread* udpThread = new CUdpThread(threadPos + 1);
	if (udpThread == NULL) {
		return false;
	}
	if (!udpThread->socket()) {
		BSLIB_SAFE_DELETE(udpThread);
		return false;
	}
	m_udpThreads[threadPos] = udpThread;
	udpThreadID = threadPos + 1;
	return true;
}

CUdpThread* CUdpThreadMgr::getUdpThread(int udpThreadID)
{
	if (udpThreadID < 0 || udpThreadID >= BSLIB_NETWORK_UDPTHREAD_MAX) {
		return NULL;
	}
	int threadPos = udpThreadID - 1;
	return m_udpThreads[threadPos];
}

void CUdpThreadMgr::clearAll()
{
	for (int i=0; i<BSLIB_NETWORK_UDPTHREAD_MAX; ++i) {
		if (m_udpThreads[i] != NULL) {
			if (m_udpThreads[i]->isRunning()) {
				m_udpThreads[i]->terminate();
			}
			m_udpThreads[i]->join();
			BSLIB_SAFE_DELETE(m_udpThreads[i]);
		}
	}
}

}//UDM

}//BSLib


