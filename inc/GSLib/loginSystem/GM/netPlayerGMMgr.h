#ifndef __GSLIB_LOGINSYSTEM_GM_NETPLAYERGMMGR_H__
#define __GSLIB_LOGINSYSTEM_GM_NETPLAYERGMMGR_H__

#include <GSLib/loginSystem/GM/netPlayerGM.h>

namespace GSLib
{

namespace LoginSystem
{

namespace GM
{

class CNetPlayerGMMgr
{
public:
	CNetPlayerGMMgr();
	virtual ~CNetPlayerGMMgr();

	virtual CNetPlayerGM* createNetPlayerGM(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName) = 0;
	virtual CNetPlayerGM* getNetPlayerGM(const GFLib::SAccountKey& a_accountKey) = 0;
	virtual void removeNetPlayerGM(const GFLib::SAccountKey& a_accountKey) = 0;

public:
	static CNetPlayerGMMgr* getSingleton() { return m_singleton; }

private:
	static CNetPlayerGMMgr* m_singleton;
};

}//GM

}//LoginSystem

}//GSLib

#endif//__GSLIB_LOGINSYSTEM_GM_NETPLAYERGMMGR_H__

