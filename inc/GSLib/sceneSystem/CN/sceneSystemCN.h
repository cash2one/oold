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

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_SCENESYSTEM; }

public:
	virtual bool _init();
	virtual void _final();
	virtual bool ICommonServer_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void ICommonServer_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonServer_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);

};

}//CN

}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_CN_SCENESYSTEMCN_H__

