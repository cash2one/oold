#ifndef __GSLIB_SCENESYSTEM_GM_SCENEMGR_H__
#define __GSLIB_SCENESYSTEM_GM_SCENEMGR_H__ 

#include <BSLib/utility/baseDef.h>
#include <BSLib/utility/hashMap.h>
#include <GSLib/sceneSystem/GM/sceneDefine.h>
#include <BSLib/utility/singleton.h>

namespace GSLib
{
namespace SceneSystem
{


namespace GM
{

class CScene;
class CScenePool;

class CSceneMgr
{
public:
	CSceneMgr();
	~CSceneMgr();
	BSLIB_SINGLETON_DECLARE(CSceneMgr);
public:
	CScene * allocateScene(ESceneType a_sceneType, BSLib::uint32 a_sceneTPID);
public:
	BSLib::Utility::CHashMap<BSLib::uint32, CScenePool*> m_hashScenePool[ESCENE_TYPE_MAX];
};

}//GM

}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_GM_SCENE_H__

