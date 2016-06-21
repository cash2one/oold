#ifndef __GSLIB_PLAYERSYSTEM_CN_ROLEMODULECNMGR_H__
#define __GSLIB_PLAYERSYSTEM_CN_ROLEMODULECNMGR_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/playerSystem/CN/roleModuleCN.h>
#include <GSLib/moduleType.h>

namespace GSLib
{

namespace PlayerSystem
{

namespace CN
{

template <class T>
CRoleModuleCN* createRoleModuleFun(CRoleCN* a_roleCN, EModuleType a_moduleType)
{
	return new T(a_roleCN, a_moduleType);
}

class CRoleModuleCNMgr
{
public:
	CRoleModuleCNMgr();
	virtual ~CRoleModuleCNMgr();

	BSLIB_SINGLETON_DECLARE(CRoleModuleCNMgr);

public:
	CRoleModuleCN* createRoleModule(CRoleCN* a_roleCN, EModuleType a_moduleType);

	bool addCreateRoleModuleFun(EModuleType a_moduleType, CRoleModuleCN*(*a_fun)(CRoleCN*, EModuleType));

	bool addCreateRoleModuleFun(EModuleType a_moduleType, const BSLib::Utility::CFunction<CRoleModuleCN*, CRoleCN*, EModuleType>& a_fun);

	template<class NAME>
	bool addCreateRoleModuleFun(EModuleType a_moduleType, CRoleModuleCN*(NAME::*a_fun)(CRoleCN*, EModuleType), NAME* object)
	{
		BSLib::Utility::CFunctionObject<CRoleModuleCN*, NAME, CRoleCN*, EModuleType> fun(a_fun, object);
		return addCreateRoleModuleFun(a_moduleType, fun);
	}

private:
	BSLib::Utility::CHashMap<EModuleType, BSLib::Utility::CFunction<CRoleModuleCN*, CRoleCN*, EModuleType>* > m_createPlayerModule;
};


}//CN

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_CN_ROLEMODULECNMGR_H__

