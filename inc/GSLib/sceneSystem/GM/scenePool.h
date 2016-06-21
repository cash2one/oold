#ifndef __GSLIB_SCENESYSTEM_GM_SCENE_POOL_H__
#define __GSLIB_SCENESYSTEM_GM_SCENE_POOL_H__ 

#include <BSLib/utility/baseDef.h>
#include <BSLib/utility/hashMap.h>
#include <BSLib/utility/uniqueID.h>
#include <GSLib/sceneSystem/GM/sceneDefine.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

class CSceneAttr;
class CScene;

class CScenePool:public BSLib::Utility::CUniqueIDMgr<BSLib::uint32>
{
public:
	CScenePool(ESceneType a_type, const CSceneAttr *a_sceneAttr);
	~CScenePool();
public:
	virtual bool checkUniqueID(BSLib::uint32 a_sceneID);
	CScene *allocateScene();
	CScene *createScene(ESceneType a_sceneType, BSLib::uint32 a_sceneTPID);
public:
	ESceneType m_sceneType;
	const CSceneAttr * m_sceneAttr;
	BSLib::Utility::CHashMap<BSLib::uint32, CScene* > m_hashScene;
	BSLib::Utility::CUniqueID<BSLib::uint32> m_uniqueID;
};

}//GM

}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_GM_SCENE_H__

