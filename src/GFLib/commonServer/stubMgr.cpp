//////////////////////////////////////////////////////////////////////
//	created:	2012/09/18
//	filename:	src\GFLib\commonServer\stubMgr.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GFLib/commonServer/stubMgr.h>

namespace GFLib
{

namespace CommonServer
{

BSLIB_SINGLETON_DEFINE(CStubMgr);

CStubMgr::CStubMgr()
{
	;
}

CStubMgr::~CStubMgr()
{
	;
}

CStubPtr CStubMgr::getCommonStubByStubID(StubID a_stubID)
{
	BSLib::Network::CNetStubPtr netStubPtr = BSLib::Network::CNetStubMgr::getNetStubByStubID(a_stubID);
	CStubPtr commonStubPtr = (CStubPtr)netStubPtr;
	return commonStubPtr;
}

}//CommonServer

}//GFLib

