//////////////////////////////////////////////////////////////////////
//	created:	2012/08/04
//	filename: 	GFLib\commonServer\message\message.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GFLIB_COMMONSERVER_MESSAGE_MESSAGE_H__
#define __GFLIB_COMMONSERVER_MESSAGE_MESSAGE_H__

#include <BSLib/framework/message/message.h>
#include <GFLib/commonServer/baseDef.h>

namespace GFLib
{

#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif


struct GFLIB_COMMONSERVER_API SMessage :public BSLib::Framework::SMessage
{
public:
	SMessage(BSLib::uint32 a_msgID) : BSLib::Framework::SMessage(a_msgID){}
	SMessage(BSLib::uint8 a_server, BSLib::uint8 a_func, BSLib::uint16 a_id)
		: BSLib::Framework::SMessage(BSLIB_HI_SHIFT(a_server, 8) + a_func, a_id) {}

	BSLib::uint8 getServerType()
	{
		return BSLIB_LO_SHIFT(BSLib::Framework::SMessage::getType() & 0XFF00, 8); 
	}

	BSLib::uint8 getFunctionType() 
	{
		return BSLib::Framework::SMessage::getType() & 0X00FF; 
	}
};

#ifdef WIN32
#pragma pack (pop)
#else
#pragma pack ()
#endif

class GFLIB_COMMONSERVER_API CMessage :public BSLib::Framework::CMessage
{
public:
	CMessage(BSLib::uint32 msgID) : BSLib::Framework::CMessage(msgID){}
	CMessage(BSLib::uint8 server, BSLib::uint8 func, BSLib::uint16 id)
		: BSLib::Framework::CMessage(BSLIB_HI_SHIFT(server, 8) + func, id) {}

	BSLib::uint8 getServerType() 
	{ 
		return BSLIB_LO_SHIFT(BSLib::Framework::SMessage::getType() & 0XFF00, 8); 
	}

	BSLib::uint8 getFunctionType() 
	{
		return BSLib::Framework::CMessage::getType() & 0X00FF; 
	}
};

}//GFLib

#endif//__GFLIB_COMMONSERVER_MESSAGE_MESSAGE_H__


