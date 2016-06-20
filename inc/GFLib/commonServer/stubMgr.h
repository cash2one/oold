//////////////////////////////////////////////////////////////////////
//	created:	2012/09/17
//	filename: 	GFLib\commonServer\stubMgr.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GFLIB_COMMONSERVER_STUBMGR_H__
#define __GFLIB_COMMONSERVER_STUBMGR_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/network/netStubMgr.h>
#include <GFLib/commonServer/stub.h>


namespace GFLib
{

namespace CommonServer
{

class GFLIB_COMMONSERVER_API CStubMgr : public BSLib::Network::CNetStubMgr
{
public:
	CStubMgr();
	virtual ~CStubMgr();

	BSLIB_SINGLETON_DECLARE(CStubMgr);

	CStubPtr getCommonStubByStubID(StubID stubID);

};

}//CommonServer

}//GFLib

#endif//__GFLIB_COMMONSERVER_STUB_H__
