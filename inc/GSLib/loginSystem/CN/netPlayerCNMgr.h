#ifndef __GSLIB_LOGINSYSTEM_CN_NETPLAYERCNMGR_H__
#define __GSLIB_LOGINSYSTEM_CN_NETPLAYERCNMGR_H__

#include <GSLib/loginSystem/CN/netPlayerCN.h>

namespace GSLib
{

namespace LoginSystem
{

namespace CN
{

class CNetPlayerCNMgr
{
public:
	CNetPlayerCNMgr();
	virtual ~CNetPlayerCNMgr();

	virtual CNetPlayerCN* createNetPlayerCN(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName) = 0;
	virtual CNetPlayerCN* getNetPlayerCN(const GFLib::SAccountKey& a_accountKey) = 0;
	virtual void removeNetPlayerCN(const GFLib::SAccountKey& a_accountKey) = 0;

public:
	static CNetPlayerCNMgr* getSingleton() { return m_singleton; }

private:
	static CNetPlayerCNMgr* m_singleton;
};

}//CN

}//LoginSystem

}//GSLib

#endif//__GSLIB_LOGINSYSTEM_CN_NETPLAYERCNMGR_H__

