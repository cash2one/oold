//////////////////////////////////////////////////////////////////////
//	created:	2014/07/28
//	filename: 	GSLib\loginSystem\GT\netPlayerGTMgr.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_LOGINSYSTEM_GT_NETPLAYERGTMGR_H__
#define __GSLIB_LOGINSYSTEM_GT_NETPLAYERGTMGR_H__

#include <GSLib/loginSystem/GT/netPlayerGT.h>

namespace GSLib
{

namespace LoginSystem
{

namespace GT
{

class CNetPlayerGTMgr
{
public:
	CNetPlayerGTMgr();
	virtual ~CNetPlayerGTMgr();

	virtual CNetPlayerGT* createNetPlayerGT(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName) = 0;
	virtual CNetPlayerGT* getNetPlayerGT(const GFLib::SAccountKey& a_accountID) = 0;
	virtual void removeNetPlayerGT(const GFLib::SAccountKey& a_accountID) = 0;

public:
	static CNetPlayerGTMgr* getSingleton() { return m_singleton; }

private:
	static CNetPlayerGTMgr* m_singleton;
};

}//GT

}//LoginSystem

}//GSLib

#endif//__GSLIB_LOGINSYSTEM_GT_NETPLAYERGTMGR_H__
