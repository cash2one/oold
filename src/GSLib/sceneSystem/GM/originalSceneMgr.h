#ifndef __GSLIB_SCENESYSTEM_GM_ORIGINALSCENEMGR_H__
#define __GSLIB_SCENESYSTEM_GM_ORIGINALSCENEMGR_H__ 

#include <BSLib/utility/singleton.h>
#include <BSLib/fsm/fsmMgr.h>
#include <BSLib/behaviorTree/behaviorTreeMgr.h>
#include "GM/originalScene.h"

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

class COriginalSceneMgr
{
public:
	COriginalSceneMgr();
	~COriginalSceneMgr();

	BSLIB_SINGLETON_DECLARE(COriginalSceneMgr);

	bool init();
	void final();

	bool loadGameConfig(const std::string& a_configPath);

	COriginalScene* getOriginalScene(SceneTPID a_sceneTPID);

private:
	bool _loadSceneConfig(const std::string& a_configPath);
	bool _loadSceneScript(const std::string& a_configPath);
	bool _initOriginalScene(const std::string& a_configPath);
private:
	BSLib::Utility::CHashMap<SceneTPID, COriginalScene*> m_originalSceneHashMap;
};

}//GM

}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_GM_ORIGINALSCENEMGR_H__
