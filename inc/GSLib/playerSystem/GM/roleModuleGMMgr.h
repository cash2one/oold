//////////////////////////////////////////////////////////////////////
//	created:	2014/07/25
//	filename: 	GSLib\playerSystem\GM\roleModuleGMMgr.h
//	author:	     zhangping	
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PLAYERSYSTEM_GM_ROLEMODULEGMMGR_H__
#define __GSLIB_PLAYERSYSTEM_GM_ROLEMODULEGMMGR_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/playerSystem/GM/roleModuleGM.h>
#include <GSLib/moduleType.h>

namespace GSLib
{

namespace PlayerSystem
{

namespace GM
{

template <class T>
CRoleModuleGM* createRoleModuleFun(CRoleGM* a_roleGM, EModuleType a_moduleType)
{
	return new T(a_roleGM, a_moduleType);
}

class CRoleModuleGMMgr
{
public:
	CRoleModuleGMMgr();
	virtual ~CRoleModuleGMMgr();

	BSLIB_SINGLETON_DECLARE(CRoleModuleGMMgr);

public:
	CRoleModuleGM* createRoleModule(CRoleGM* a_roleGM, EModuleType a_moduleType);

	bool addCreateRoleModuleFun(EModuleType a_moduleType, CRoleModuleGM*(*a_fun)(CRoleGM*, EModuleType));

	bool addCreateRoleModuleFun(EModuleType a_moduleType, const BSLib::Utility::CFunction<CRoleModuleGM*, CRoleGM*, EModuleType>& a_fun);

	template<class NAME>
	bool addCreateRoleModuleFun(EModuleType a_moduleType, CRoleModuleGM*(NAME::*a_fun)(CRoleGM*, EModuleType), NAME* object)
	{
		BSLib::Utility::CFunctionObject<CRoleModuleGM*, NAME, CRoleGM*, EModuleType> fun(a_fun, object);
		return addCreateRoleModuleFun(a_moduleType, fun);
	}

private:
	BSLib::Utility::CHashMap<EModuleType, BSLib::Utility::CFunction<CRoleModuleGM*, CRoleGM*, EModuleType>* > m_createPlayerModule;
};


}//GM

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_GM_ROLEMODULEGMMGR_H__
