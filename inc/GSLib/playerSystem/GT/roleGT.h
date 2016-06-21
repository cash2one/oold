#ifndef __GSLIB_PLAYERSYSTEM_GT_ROLE_H__
#define __GSLIB_PLAYERSYSTEM_GT_ROLE_H__

#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/baseDef.h>

namespace GSLib
{

namespace PlayerSystem
{

namespace GT
{

class CRoleGT
{
public:
	CRoleGT();
	CRoleGT(BSLib::uint32 a_RoleIndex,std::string a_roldName);
	virtual ~CRoleGT();

public:
	virtual bool _init();
	virtual void _final();

public:
	std::string  getName() const { return "test_name";}
	RoleIndex getRoleIndex() const {return INVALID_ROLEINDEX;}
};

}//GT

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_GT_ROLE_H__

