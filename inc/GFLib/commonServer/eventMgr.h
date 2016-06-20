//////////////////////////////////////////////////////////////////////
//	created:	2014/11/20
//	filename: 	GFLib\commonServer\eventMgr.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GFLIB_COMMONSERVER_EVENTMGR_H__
#define __GFLIB_COMMONSERVER_EVENTMGR_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/eventMgr.h>
#include <GFLib/commonServer/baseDef.h>

namespace GFLib
{

namespace CommonServer
{

class GFLIB_COMMONSERVER_API CEventMgr : public BSLib::Utility::CEventMgr
{
public:
	CEventMgr();
	~CEventMgr();

	BSLIB_SINGLETON_DECLARE(CEventMgr);
};

}//CommonServer

}//GFLib

#endif//__GFLIB_COMMONSERVER_EVENTMGR_H__