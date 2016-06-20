//////////////////////////////////////////////////////////////////////
//	created:	2014/07/31
//	filename: 	GFLib\commonServer\accountMgr.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GFLIB_COMMONSERVER_ACCOUNTMGR_H__
#define __GFLIB_COMMONSERVER_ACCOUNTMGR_H__

#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/account.h>

namespace GFLib
{

namespace CommonServer
{

class GFLIB_COMMONSERVER_API CAccountMgr
{
public:
	CAccountMgr();
	~CAccountMgr();

	BSLIB_SINGLETON_DECLARE(CAccountMgr);

public:
	bool addAccount(const CAccountPtr& a_accountPtr);
	void delAccount(const SAccountKey& a_accountKey);
	CAccountPtr getAccount(const SAccountKey& a_accountKey);

private:
	BSLib::Utility::CMutex m_mutex;
	BSLib::Utility::CHashMap<SAccountKey, CAccountPtr> m_accountHashMap;
};

}//CommonServer

}//GFLib

#endif//__GFLIB_COMMONSERVER_ACCOUNTMGR_H__