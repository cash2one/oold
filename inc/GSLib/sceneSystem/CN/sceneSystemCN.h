#ifndef __GSLIB_SCENESYSTEM_CN_SCENESYSTEMCN_H__
#define __GSLIB_SCENESYSTEM_CN_SCENESYSTEMCN_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>

namespace GSLib
{

namespace SceneSystem
{

namespace CN
{

class CSceneSystemCN : public GSLib::DBSystem::CDBCommonSystem
{
public:
	CSceneSystemCN();
	virtual ~CSceneSystemCN();

	BSLIB_SINGLETON_DECLARE(CSceneSystemCN);

	virtual BSLib::uint16 ICommonSystem_getFuncType() { return GSLib::EFUNCTYPE_SCENESYSTEM; }

public:
	virtual bool _init();
	virtual void _final();
	virtual bool ICommonSystem_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _ICommonSystem_startSystem();
	virtual void ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);

};

}//CN

}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_CN_SCENESYSTEMCN_H__

