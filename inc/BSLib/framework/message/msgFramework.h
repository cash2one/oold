//////////////////////////////////////////////////////////////////////
//	created:	2012/09/09
//	filename: 	BSLib\framework\message\msgFramework.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_FRAMEWORK_MESSAGE_MSGFRAMEWORK_H__
#define __BSLIB_FRAMEWORK_MESSAGE_MSGFRAMEWORK_H__

#include <BSLib/framework/message/msgType.h>
#include <BSLib/framework/message/msgDebug.h>

namespace BSLib
{

namespace Framework
{

enum EMsgIDFramework
{
	EMID_FRAMEWORK_NTF_TERMINATE = 1,
	EMID_FRAMEWORK_EXTEND,
};

#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif

BSLIB_MSG_DEBUG(EMT_FRAMEWORK, EMID_FRAMEWORK_NTF_TERMINATE);
struct SMsgFrameworkNtfTerminate: public SMessage
{
	SMsgFrameworkNtfTerminate() : SMessage(EMT_FRAMEWORK, EMID_FRAMEWORK_NTF_TERMINATE){}
};

#ifdef WIN32
#pragma pack (pop)
#else
#pragma pack ()
#endif
}//Framework

}//BSLib

#endif//__BSLIB_FRAMEWORK_MESSAGE_MSGFRAMEWORK_H__
