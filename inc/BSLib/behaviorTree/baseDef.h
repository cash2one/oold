//////////////////////////////////////////////////////////////////////
//	created:	2012/10/20
//	filename:	BSLib\behaviorTree\baseDef.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_BEHAVIORTREE_BASEDEF_H__
#define __BSLIB_BEHAVIORTREE_BASEDEF_H__

#include <BSLib/utility/baseDef.h>

#ifdef BSLIB_BEHAVIORTREE_EXPORTS
#define BSLIB_BEHAVIORTREE_API _declspec(dllexport)
#elif defined(BSLIB_BEHAVIORTREE_IMPORTS)
#define BSLIB_BEHAVIORTREE_API _declspec(dllimport)
#else
#define BSLIB_BEHAVIORTREE_API 
#endif

#endif //__BSLIB_BEHAVIORTREE_BASEDEF_H__

