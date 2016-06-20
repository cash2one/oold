//////////////////////////////////////////////////////////////////////
//	created:	2014/07/29
//	filename: 	GSLib\playerSystem\CN\role.h
//	author:		zhangping
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PLAYERSYSTEM_CN_ROLE_H__
#define __GSLIB_PLAYERSYSTEM_CN_ROLE_H__

#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonSystem.h>
#include "GSLib/playerSystem/attribute.h"
namespace GSLib
{

namespace PlayerSystem
{

namespace CN
{

class CRoleCN
{
public:
	CRoleCN();
	CRoleCN(BSLib::uint32 a_RoleIndex,std::string a_roldName);
	virtual ~CRoleCN();

};

}//CN

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_CN_ROLE_H__
