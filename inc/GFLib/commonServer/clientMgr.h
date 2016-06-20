//////////////////////////////////////////////////////////////////////
//	created:	2012/10/05
//	filename: 	GFLib\commonServer\clientMgr.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GFLIB_COMMONSERVER_CLIENTTHREAD_H__
#define __GFLIB_COMMONSERVER_CLIENTTHREAD_H__

#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonClient.h>

namespace GFLib
{

namespace CommonServer
{

class GFLIB_COMMONSERVER_API CClientMgr
{
public:
	CClientMgr();
	~CClientMgr();

	BSLIB_SINGLETON_DECLARE(CClientMgr);

	void addCommonClient(SServerID a_serverID, CCommonClientPtr& a_commonClient);
	void delCommonClient(SServerID a_serverID);
	CCommonClientPtr getCommonClient(SServerID a_serverID);
	
	void final();

private:
	BSLib::Utility::CHashMap<ServerID, CCommonClientPtr> m_clientHashMap;
	BSLib::Utility::CMutex m_mutex;
};

}//CommonServer

}//GFLib

#endif//__GFLIB_COMMONSERVER_CLIENTTHREAD_H__


