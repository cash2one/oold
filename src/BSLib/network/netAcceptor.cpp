#include <BSLib/network/netAcceptor.h>

namespace BSLib
{

namespace Network
{

bool INetAcceptor::addAcceptor(CSockAddr& addrAcceptor, CNetAcceptorCallbackPtr& cbNewConnection, void* tempData)
{
	for (uint32 i=0; i<m_accepteorList.size(); ++i){
		if (m_accepteorList[i]->m_addrAcceptor == addrAcceptor) {
			return false;
		}
	}

	SAcceptorItemPtr item = new SAcceptorItem();
	if (item == NULL){
		return false;
	}
	item->m_addrAcceptor = addrAcceptor;
	item->m_cbNewConnection = cbNewConnection;
	item->m_sockID = INVALID_SOCKET;
	item->m_tempData = tempData;

	if (!_INetAcceptor_addAcceptor(item)){
		return false;
	}
	m_accepteorList.push_back(item);
	return true;
}

bool INetAcceptor::delAcceptor(CSockAddr& addrAcceptor)
{
	std::vector<SAcceptorItemPtr>::iterator it = m_accepteorList.begin();
	for (; it != m_accepteorList.end(); ){
		SAcceptorItemPtr& item = *it;
		if (item == NULL){
			it = m_accepteorList.erase(it);
			continue;
		}
		if (item->m_addrAcceptor != addrAcceptor){
			++it;
			continue;
		}

		_INetAcceptor_delAcceptor(item);
		m_accepteorList.erase(it);
		return true;
	}
	return false;
}

}//Network

}//BSLib

