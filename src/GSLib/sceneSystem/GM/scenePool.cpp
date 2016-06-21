#include <GSLib/sceneSystem/GM/scenePool.h>
#include <GSLib/sceneSystem/GM/scene.h>
#include <GSLib/sceneSystem/GM/roleSceneModule.h>
#include <GSLib/sceneSystem/GM/sceneImpl.h>
#include <GSLib/sceneSystem/GM/sceneSystemDataMgr.h>

namespace GSLib
{

namespace SceneSystem
{	

namespace GM
{


////////////////////////////////////////////////////////////////////////////////////////////////
CScenePool::CScenePool(ESceneType a_type, const CSceneAttr *a_sceneAttr)
:m_sceneType(ESCENE_TYPE_NONE)
,m_sceneAttr(a_sceneAttr)
{
	m_uniqueID.setUniqueIDMgr(this);
}

CScenePool::~CScenePool()
{
	for (BSLib::Utility::CHashMap<BSLib::uint32, CScene* >::iterator itr = m_hashScene.begin(); itr != m_hashScene.end(); ++itr) {
		if (itr->second != NULL) {
			delete itr->second, itr->second = NULL;
		}
	}
	m_hashScene.clear();
}

bool CScenePool::checkUniqueID(BSLib::uint32 a_sceneID)
{
	return m_hashScene.find(a_sceneID) != m_hashScene.end();
}

CScene * CScenePool::allocateScene()
{
	if (m_sceneAttr != NULL) {
		for (BSLib::Utility::CHashMap<BSLib::uint32, CScene* >::iterator itr = m_hashScene.begin(); itr != m_hashScene.end(); ++itr) {
			CScene *scene = itr->second;
			if (scene != NULL) {
				if (scene->getScenePlayerCount() < m_sceneAttr->getMaxPlayers()) {
					return scene;
				}
			}
		}
		BSLib::uint32 sceneID = m_uniqueID.allocateID();
		if (sceneID == m_uniqueID.invalidID()) {
			return NULL;
		}
		CScene * newScene = createScene(m_sceneAttr->getSceneType(), m_sceneAttr->getSceneTPID());
		newScene->setSceneID(sceneID);
		if (newScene != NULL) {
			m_hashScene.setValue(sceneID ,newScene);
			return newScene;
		}
	}
	return NULL;
}

CScene * CScenePool::createScene(ESceneType a_sceneType, BSLib::uint32 a_sceneTPID)
{
	CScene *scene = NULL;
	const CSceneAttr *sceneAttr =  CSceneSystemDataMgr::singleton().getSceneAttr(a_sceneType, a_sceneTPID);
	if (sceneAttr != NULL) {
		switch (a_sceneType)
		{
		case ESCENE_TYPE_ARENA:
			{
				scene = new CSceneArena(a_sceneType, sceneAttr);
			}
			break;
		case ESCENE_TYPE_STAGE:
			{
				scene = new CSceneStage(a_sceneType, sceneAttr);
			}
			break;
		case ESCENE_TYPE_CITY:
			{
				scene = new CSceneCity(a_sceneType, sceneAttr);
			}
			break;
		case ESCENE_TYPE_CONTINUOUS_STAGE:
			{
				scene = new CSceneContinuousStage(a_sceneType, sceneAttr);
			}
			break;
		case ESCENE_TYPE_RANDOM_STAGE:
			{
				scene = new CSceneRandomStage(a_sceneType, sceneAttr);
			}
			break;
		case ESCENE_TYPE_RANDOM_GOLD_STAGE:
			{
				scene = new CSceneGoldLandStage(a_sceneType, sceneAttr);
			}
			break;
		case ESCENE_TYPE_RANDOM_EXP_STAGE:
			{
				scene = new CSceneExpLandStage(a_sceneType, sceneAttr);
			}
			break;
		default:
			{
				;
			}
			break;
		}
	}
	return scene;
}


}//GM

}//SceneSystem

}//GSLib

