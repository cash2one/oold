#include "CN/gateInforMgr.h"

namespace GSLib
{

namespace LoginSystem
{

namespace CN
{

class CGateServiceMgrCallback : public BSLib::Utility::CHashMap<GFLib::ServerID, GFLib::CommonServer::SServiceInfor*>::CCallback
{
public:
	CGateServiceMgrCallback(std::vector<SGateInfor>* gateOnlineInforHashMap)
		: m_gateOnlineInforHashMap(gateOnlineInforHashMap)
	{
		;
	}
	virtual bool exec(const GFLib::ServerID& _key, GFLib::CommonServer::SServiceInfor*& _value)
	{
		GFLib::SServerID serverID(_key);

		if (serverID.getZoneID() == 0) {
			return true;
		}
		if (serverID.getServerType() != SRVTYPE_GATESERVER) {
			return true;
		}

		SGateInfor gateInfor;
		gateInfor.m_gateServerID = serverID;
		gateInfor.m_connectAddr = _value->m_netInfor.m_outerAddr;
		gateInfor.m_isRunning = false;
		gateInfor.m_onlineCount = 0;
		gateInfor.m_waitCount = 0;

		m_gateOnlineInforHashMap->push_back(gateInfor);
		return true;
	}

private:
	std::vector<SGateInfor>* m_gateOnlineInforHashMap;
};

//////////////////////////////////////////////////////////////////////////
BSLIB_SINGLETON_DEFINE(CGateInforMgr);

CGateInforMgr::CGateInforMgr()
{
	;
}

CGateInforMgr::~CGateInforMgr()
{
	;
}

void CGateInforMgr::init()
{
	CGateServiceMgrCallback serviceMgrCb(&m_gateOnlineInforHashMap);

	GFLib::CommonServer::CServiceMgr::singleton().traversal(serviceMgrCb);
}

void CGateInforMgr::final()
{
	m_gateOnlineInforHashMap.clear();
}

void CGateInforMgr::gateServerEnter(const GFLib::SServerID& a_serverID)
{
	std::vector<SGateInfor>::iterator it = m_gateOnlineInforHashMap.begin();
	for (; it != m_gateOnlineInforHashMap.end(); ++it) {
		SGateInfor& gateInfor = *it;
		if (gateInfor.m_gateServerID == a_serverID) {
			gateInfor.m_isRunning = true;
			return;
		}
	}
}

void CGateInforMgr::gateServerLeave(const GFLib::SServerID& a_serverID)
{
	std::vector<SGateInfor>::iterator it = m_gateOnlineInforHashMap.begin();
	for (; it != m_gateOnlineInforHashMap.end(); ++it) {
		SGateInfor& gateInfor = *it;
		if (gateInfor.m_gateServerID == a_serverID) {
			gateInfor.m_isRunning = false;
			gateInfor.m_onlineCount = 0;
			gateInfor.m_waitCount = 0;
			return;
		}
	}
}

BSLib::Network::CSockAddr& CGateInforMgr::getGateConnectAddr(GFLib::SServerID& a_gateServerID)
{
	static BSLib::Network::CSockAddr temp;

	std::vector<SGateInfor>::iterator it = m_gateOnlineInforHashMap.begin();
	for (; it != m_gateOnlineInforHashMap.end(); ++it) {
		SGateInfor& gateInfor = *it;
		if (gateInfor.m_gateServerID == a_gateServerID) {
			return gateInfor.m_connectAddr;
		}
	}
	return temp;
}

bool CGateInforMgr::increaseAccountToGateServer(GFLib::SServerID& a_gateServerID)
{
	BSLib::uint32 count = BSLIB_UINT32_MAX;
	a_gateServerID.setServerID(GFLib::INVALID_SERVERID);

	std::vector<SGateInfor>::iterator it = m_gateOnlineInforHashMap.begin();
	for (; it != m_gateOnlineInforHashMap.end(); ++it) {
		SGateInfor& gateInfor = *it;
		if (!gateInfor.m_isRunning) {
			continue;
		}
		if (gateInfor.m_onlineCount + gateInfor.m_waitCount < count){
			count = gateInfor.m_onlineCount + gateInfor.m_waitCount;
			a_gateServerID = gateInfor.m_gateServerID;
		}
	}
	return a_gateServerID.isValid();
}

void CGateInforMgr::increaseOnlineAccountFromGateServer(GFLib::SServerID& a_gateServerID)
{
	std::vector<SGateInfor>::iterator it = m_gateOnlineInforHashMap.begin();
	for (; it != m_gateOnlineInforHashMap.end(); ++it) {
		SGateInfor& gateInfor = *it;
		if (!gateInfor.m_isRunning) {
			continue;
		}
		if (gateInfor.m_gateServerID != a_gateServerID) {
			continue;
		}
		if (gateInfor.m_onlineCount >= 0) {
			gateInfor.m_onlineCount += 1;
		}
		return ;
	}
}

void CGateInforMgr::increaseWaitAccountFromGateServer(GFLib::SServerID& a_gateServerID)
{
	std::vector<SGateInfor>::iterator it = m_gateOnlineInforHashMap.begin();
	for (; it != m_gateOnlineInforHashMap.end(); ++it) {
		SGateInfor& gateInfor = *it;
		if (!gateInfor.m_isRunning) {
			continue;
		}
		if (gateInfor.m_gateServerID != a_gateServerID) {
			continue;
		}
		if (gateInfor.m_waitCount >= 0) {
			gateInfor.m_waitCount += 1;
		}
		return;
	}
}

void CGateInforMgr::decreaseOnlineAccountFromGateServer(GFLib::SServerID& a_gateServerID)
{
	std::vector<SGateInfor>::iterator it = m_gateOnlineInforHashMap.begin();
	for (; it != m_gateOnlineInforHashMap.end(); ++it) {
		SGateInfor& gateInfor = *it;
		if (!gateInfor.m_isRunning) {
			continue;
		}
		if (gateInfor.m_gateServerID != a_gateServerID) {
			continue;
		}
		if (gateInfor.m_onlineCount > 0) {
			gateInfor.m_onlineCount -= 1;
		}
		return ;
	}
}

void CGateInforMgr::decreaseWaitAccountFromGateServer(GFLib::SServerID& a_gateServerID)
{
	std::vector<SGateInfor>::iterator it = m_gateOnlineInforHashMap.begin();
	for (; it != m_gateOnlineInforHashMap.end(); ++it) {
		SGateInfor& gateInfor = *it;
		if (!gateInfor.m_isRunning) {
			continue;
		}
		if (gateInfor.m_gateServerID != a_gateServerID) {
			continue;
		}
		if (gateInfor.m_waitCount > 0) {
			gateInfor.m_waitCount -= 1;
		}
		return;
	}
}

}//CN

}//LoginSystem

}//GSLib
