//////////////////////////////////////////////////////////////////////
//	created:	2012/07/24
//	filename:	BSLib\network\sockAddr.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_NETWOKD_SOCKADDR_H__
#define __BSLIB_NETWOKD_SOCKADDR_H__

#include <string>
#include <vector>
#include <BSLib/network/baseDef.h>

namespace BSLib
{

namespace Network
{

class BSLIB_NETWORK_API CSockAddr
{
public:
	CSockAddr(const char *szIP = NULL, uint16 uPort = 0);
	CSockAddr(const CSockAddr &rhs);
	CSockAddr(sockaddr& addr);
	CSockAddr(sockaddr_in& addr);

	void setPort(uint16 uPort);
	void setIP(uint32 a_ip);
	void setIP(const char *szIP);
	void setIP();
	void setIPAndPort(const char *szIP, uint16 uPort);
	void setIPAndPort(uint32 a_ip, uint16 uPort);

	const std::string& getIP() const;
	uint32 getNetIP() const;

	uint16 getPort() const;
	
	CSockAddr& operator =(const CSockAddr& rhs);

	bool operator ==(const CSockAddr& rhs);
	bool operator !=(const CSockAddr& rhs);

	operator sockaddr*() { return (sockaddr *)&m_addr; }
	operator sockaddr_in*() { return &m_addr; }
	
public:
	static int getLocalIP(std::vector<std::string>& ipList);
	static int getLocalIP(std::vector<uint32>& ipList);

protected:
	struct sockaddr_in   m_addr;
	mutable std::string  m_strIP;
};

}//Network

}//BSLib

#endif//__BSLIB_NETWOKD_SOCKADDR_H__
