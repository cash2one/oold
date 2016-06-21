#include <GSLib/playerSystem/CN/roleModuleCNMgr.h>

namespace GSLib
{

namespace PlayerSystem
{	

namespace CN
{

BSLIB_SINGLETON_DEFINE(CRoleModuleCNMgr);

CRoleModuleCNMgr::CRoleModuleCNMgr()
{
	;
}

CRoleModuleCNMgr::~CRoleModuleCNMgr()
{
	;
}

CRoleModuleCN* CRoleModuleCNMgr::createRoleModule(CRoleCN* a_roleCN, EModuleType a_moduleType)
{
	
	BSLib::Utility::CFunction<CRoleModuleCN*, CRoleCN*, EModuleType>* createRoleModuleFun = NULL;
	m_createPlayerModule.getValue(a_moduleType, createRoleModuleFun);
	if (createRoleModuleFun == NULL) {
		return NULL;
	}
	CRoleModuleCN* roleModule = (*createRoleModuleFun)(a_roleCN, a_moduleType);
	if (roleModule == NULL) {
		;
	}
	return roleModule;
}

bool CRoleModuleCNMgr::addCreateRoleModuleFun(EModuleType a_moduleType, CRoleModuleCN*(*a_fun)(CRoleCN*, EModuleType))
{
	if (a_fun == NULL){
		return false;
	}
	BSLib::Utility::CFunction<CRoleModuleCN*, CRoleCN*, EModuleType> fun(a_fun);
	return addCreateRoleModuleFun(a_moduleType, fun);
}

bool CRoleModuleCNMgr::addCreateRoleModuleFun(EModuleType a_moduleType, const BSLib::Utility::CFunction<CRoleModuleCN*, CRoleCN*, EModuleType>& a_fun)
{
	if (m_createPlayerModule.find(a_moduleType) != m_createPlayerModule.end()) {
		return false;
	}
	m_createPlayerModule.setValue(a_moduleType, a_fun.clone());
	return true;
}


}//CN

}//PlayerSystem

}//GSLib

