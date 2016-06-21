
#ifndef __GSLIB_LOGINSYSTEM_LG_ZONEINFORMGR_H__
#define __GSLIB_LOGINSYSTEM_LG_ZONEINFORMGR_H__

#include <GFLib/commonServer/serviceMgr.h>
#include <GSLib/loginSystem/msgLoginSystem.h>

namespace GSLib
{

namespace LoginSystem
{

namespace LG
{

struct SZoneInfor
{
	GFLib::SServerID m_zone;
	bool m_isRunning;
};

class CZoneInforMgr
{
public:
	CZoneInforMgr();
	~CZoneInforMgr();

	BSLIB_SINGLETON_DECLARE(CZoneInforMgr);

	void init();
	void final();

	void centerServerEnter(const GFLib::SServerID& a_serverID);
	void centerServerLeave(const GFLib::SServerID& a_serverID);

	void superServerEnter(const GFLib::SServerID& a_serverID);
	void superServerLeave(const GFLib::SServerID& a_serverID);

	bool verifyZone(GFLib::ZoneID zoneID, CMsgLoginSystemLG2GCAckAccountLogin& ackAccountLogin, GFLib::SServerID& centerServerID);

private:
	BSLib::Utility::CHashMap<GFLib::ZoneID, SZoneInfor*> m_zoneOnlineInforHashMap;
};

}//LG

}//LoginSystem

}//GSLib


#endif//__GSLIB_LOGINSYSTEM_LG_ZONEINFORMGR_H__
