#include <BSLib/network/sockAddr.h>

#ifndef _WIN32

#include <netdb.h>

void closesocket(SOCKET sock)
{
	::shutdown(sock, SHUT_RDWR);
	::close(sock);
};

#endif


namespace BSLib
{

namespace Network
{

CSockAddr::CSockAddr(const char *szIP, uint16 uPort)
{
	m_addr.sin_family = AF_INET;

	setIP(szIP);
	setPort(uPort);
}

CSockAddr::CSockAddr(const CSockAddr &rhs)
{
	m_addr = rhs.m_addr;
	m_strIP = rhs.m_strIP;
}

CSockAddr::CSockAddr(sockaddr& addr)
{
	m_addr = *((sockaddr_in*)&addr);
}

CSockAddr::CSockAddr(sockaddr_in& addr)
{
	m_addr = addr;
}

void CSockAddr::setPort(uint16 uPort)
{
	m_addr.sin_port = htons(uPort);
	setIP();
}

void CSockAddr::setIP(uint32 a_ip)
{
	m_addr.sin_addr.s_addr = a_ip;
	m_strIP = inet_ntoa(m_addr.sin_addr);
}

void CSockAddr::setIP(const char *szIP)
{
	if (szIP != NULL) {
		m_addr.sin_addr.s_addr = inet_addr(szIP);
	} else {
		m_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	m_strIP = inet_ntoa(m_addr.sin_addr);
}

void CSockAddr::setIP()
{
	m_strIP = inet_ntoa(m_addr.sin_addr);
}

void CSockAddr::setIPAndPort(const char *szIP, uint16 uPort)
{
	m_addr.sin_port = htons(uPort);
	setIP(szIP);
}

void CSockAddr::setIPAndPort(uint32 a_ip, uint16 uPort)
{
	m_addr.sin_port = htons(uPort);
	setIP(a_ip);
}

const std::string& CSockAddr::getIP() const 
{ 
	m_strIP = inet_ntoa(m_addr.sin_addr);
	return m_strIP; 
}

uint32 CSockAddr::getNetIP() const 
{
	return m_addr.sin_addr.s_addr; 
}

uint16 CSockAddr::getPort() const
{
	return ntohs(m_addr.sin_port);
}

CSockAddr& CSockAddr::operator =(const CSockAddr& rhs)
{
	m_addr = rhs.m_addr;
	m_strIP = rhs.m_strIP;
	return *this;
}

bool CSockAddr::operator ==(const CSockAddr& rhs)
{
	if (getPort() != rhs.getPort()){
		return false;
	}
	if (getIP() != rhs.getIP())	{
		return false;
	}
	return true;
}

bool CSockAddr::operator !=(const CSockAddr& rhs)
{
	if (getPort() != rhs.getPort()){
		return true;
	}
	if (getIP() != rhs.getIP())	{
		return true;
	}
	return false;
}

int CSockAddr::getLocalIP(std::vector<std::string>& ipList)
{
	std::vector<uint32> ips;
	if (getLocalIP(ips) <= 0) {
		return 0;
	}

	ipList.clear();

	for (uint32 i=0; i > ips.size(); ++i) {
		in_addr ip;
		ip.s_addr = ips[i];
		ipList.push_back(::inet_ntoa(ip));
	}
	return (int)ipList.size();
}

int CSockAddr::getLocalIP(std::vector<uint32>& ipList)
{
	char szHost[256] = {0};
	::gethostname(szHost, 256);
	hostent* pHost = ::gethostbyname(szHost);

	if (pHost == NULL){
		return 0;
	}
	ipList.clear();
	char *pIP;
	for (uint32 i=0; NULL != (pIP = pHost->h_addr_list[i]); ++i) {
		uint32 ip = 0;
		memcpy(&ip, pIP, pHost->h_length);
		ipList.push_back(ip);
	}
	return (int)ipList.size();
}

}//Network

}//BSLib


