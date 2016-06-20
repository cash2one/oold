//////////////////////////////////////////////////////////////////////
//	created:	2015/1/8
//	filename: 	src\GSLib\sceneSystem\GM\sceneMgr.cpp
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/sceneSystem/GM/sceneMgr.h>
#include <GSLib/sceneSystem/GM/scene.h>
#include <GSLib/sceneSystem/GM/sceneSystemData.h>
#include <GSLib/sceneSystem/GM/sceneSystemDataMgr.h>
#include <GSLib/sceneSystem/GM/scenePool.h>

namespace GSLib
{

namespace SceneSystem
{	

namespace GM
{

CSceneMgr::CSceneMgr()
{

}

CSceneMgr::~CSceneMgr()
{
	for (BSLib::uint32 i = 0; i < ESCENE_TYPE_MAX; ++i) {
		for (BSLib::Utility::CHashMap<BSLib::uint32, CScenePool *>::iterator itr = m_hashScenePool[i].begin(); itr != m_hashScenePool[i].end(); ++itr) {
			if (itr->second != NULL) {
				delete itr->second, itr->second = NULL;
			}
		}
		m_hashScenePool[i].clear();
	}
}

BSLIB_SINGLETON_DEFINE(CSceneMgr);

CScene * CSceneMgr::allocateScene(ESceneType a_sceneType, BSLib::uint32 a_sceneTPID)
{
	if (a_sceneType > ESCENE_TYPE_NONE && a_sceneType < ESCENE_TYPE_MAX) {
		const CSceneAttr *sceneAttr = CSceneSystemDataMgr::singleton().getSceneAttr(a_sceneType, a_sceneTPID);
		if (sceneAttr != NULL) {
			BSLib::Utility::CHashMap<BSLib::uint32, CScenePool *>::iterator itr = m_hashScenePool[a_sceneType].find(a_sceneTPID);		
			if (itr != m_hashScenePool[a_sceneType].end()) {
				return itr->second->allocateScene();
			} else {
				CScenePool *scenePool = new CScenePool(a_sceneType, sceneAttr);
				if (scenePool != NULL) {
					m_hashScenePool[a_sceneType].setValue(a_sceneTPID, scenePool);
					return scenePool->allocateScene();
				}
			}
		}
	}
	return NULL;		
}



}//GM

}//SceneSystem

}//GSLib
