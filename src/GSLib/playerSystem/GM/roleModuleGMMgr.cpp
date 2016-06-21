#include <GSLib/playerSystem/GM/roleModuleGMMgr.h>

namespace GSLib
{

namespace PlayerSystem
{	

namespace GM
{

BSLIB_SINGLETON_DEFINE(CRoleModuleGMMgr);

CRoleModuleGMMgr::CRoleModuleGMMgr()
{
	;
}

CRoleModuleGMMgr::~CRoleModuleGMMgr()
{
	;
}

CRoleModuleGM* CRoleModuleGMMgr::createRoleModule(CRoleGM* a_roleGM, EModuleType a_moduleType)
{
	
	BSLib::Utility::CFunction<CRoleModuleGM*, CRoleGM*, EModuleType>* createRoleModuleFun = NULL;
	m_createPlayerModule.getValue(a_moduleType, createRoleModuleFun);
	if (createRoleModuleFun == NULL) {
		return NULL;
	}
	CRoleModuleGM* roleModule = (*createRoleModuleFun)(a_roleGM, a_moduleType);
	if (roleModule == NULL) {
		;
	}
	return roleModule;
}

bool CRoleModuleGMMgr::addCreateRoleModuleFun(EModuleType a_moduleType, CRoleModuleGM*(*a_fun)(CRoleGM*, EModuleType))
{
	if (a_fun == NULL){
		return false;
	}
	BSLib::Utility::CFunction<CRoleModuleGM*, CRoleGM*, EModuleType> fun(a_fun);
	return addCreateRoleModuleFun(a_moduleType, fun);
}

bool CRoleModuleGMMgr::addCreateRoleModuleFun(EModuleType a_moduleType, const BSLib::Utility::CFunction<CRoleModuleGM*, CRoleGM*, EModuleType>& a_fun)
{
	if (m_createPlayerModule.find(a_moduleType) != m_createPlayerModule.end()) {
		return false;
	}
	m_createPlayerModule.setValue(a_moduleType, a_fun.clone());
	return true;
}

}//GM

}//PlayerSystem

}//GSLib

