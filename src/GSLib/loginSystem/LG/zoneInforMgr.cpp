#include <GSLib/tracer.h>
#include "LG/zoneInforMgr.h"

namespace GSLib
{

namespace LoginSystem
{

namespace LG
{

class CServiceMgrCallback : public BSLib::Utility::CHashMap<GFLib::ServerID, GFLib::CommonServer::SServiceInfo*>::CCallback
{
public:
	CServiceMgrCallback(BSLib::Utility::CHashMap<GFLib::ZoneID, SZoneInfor*>* zoneOnlineInforHashMap)
		: m_zoneOnlineInforHashMap(zoneOnlineInforHashMap)
	{
		;
	}
	virtual bool exec(const GFLib::ServerID& _key, GFLib::CommonServer::SServiceInfo*& _value)
	{
		GFLib::SServerID serverID(_key);

		if (serverID.getZoneID() == 0) {
			return true;
		}
		if (serverID.ICommonServer_getServerType() != SRVTYPE_CENTERSERVER) {
			return true;
		}

		SZoneInfor* zoneInfor = NULL;
		m_zoneOnlineInforHashMap->getValue(serverID.getZoneID(), zoneInfor);
		if (zoneInfor != NULL) {
			return true;
		}
		zoneInfor = new SZoneInfor;
		if (zoneInfor == NULL) {
			return false;
		}
		zoneInfor->m_zone  = serverID;
		zoneInfor->m_isRunning = false;
		m_zoneOnlineInforHashMap->setValue(serverID.getZoneID(), zoneInfor);
		return true;
	}

private:
	BSLib::Utility::CHashMap<GFLib::ZoneID, SZoneInfor*>* m_zoneOnlineInforHashMap;
};

//////////////////////////////////////////////////////////////////////////
BSLIB_SINGLETON_DEFINE(CZoneInforMgr);

CZoneInforMgr::CZoneInforMgr()
{
	;
}

CZoneInforMgr::~CZoneInforMgr()
{
	;
}

void CZoneInforMgr::init()
{
	CServiceMgrCallback serviceMgrCb(&m_zoneOnlineInforHashMap);

	GFLib::CommonServer::CServiceMgr::singleton().traversal(serviceMgrCb);
}

void CZoneInforMgr::final()
{
	BSLib::Utility::CHashMap<GFLib::ZoneID, SZoneInfor*>::iterator it = m_zoneOnlineInforHashMap.begin();
	for (; it != m_zoneOnlineInforHashMap.end(); ++it) {
		SZoneInfor* zoneOnlineInfor = it->second;
		if (zoneOnlineInfor == NULL) {
			continue;
		}
		BSLIB_SAFE_DELETE(zoneOnlineInfor);
	}
	m_zoneOnlineInforHashMap.clear();
}

void CZoneInforMgr::centerServerEnter(const GFLib::SServerID& a_serverID)
{
	SZoneInfor* zoneInfor = NULL;
	m_zoneOnlineInforHashMap.getValue(a_serverID.getZoneID(), zoneInfor);
	if (zoneInfor == NULL) {
		return ;
	}
	zoneInfor->m_isRunning = true;
}

void CZoneInforMgr::centerServerLeave(const GFLib::SServerID& a_serverID)
{
	SZoneInfor* zoneInfor = NULL;
	m_zoneOnlineInforHashMap.getValue(a_serverID.getZoneID(), zoneInfor);
	if (zoneInfor == NULL) {
		return ;
	}
	zoneInfor->m_isRunning = false;
}

bool CZoneInforMgr::verifyZone(GFLib::ZoneID zoneID, CMsgLoginSystemLG2GCAckAccountLogin& ackAccountLogin, GFLib::SServerID& centerServerID)
{
	SZoneInfor* zoneInfor = NULL;
	m_zoneOnlineInforHashMap.getValue(zoneID, zoneInfor);
	if (zoneInfor == NULL) {
		ackAccountLogin.m_state = ELOGINRESULT_ZONEID_NOTEXIST;
		return false;
	}
	if (!zoneInfor->m_isRunning) {
		ackAccountLogin.m_state = ELOGINRESULT_ZONEID_STOP;
		return false;
	}
	centerServerID = zoneInfor->m_zone;
	return true;
}

}//LG

}//LoginSystem

}//GSLib
