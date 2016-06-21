#include <GSLib/sceneSystem/GM/sceneGMMgr.h>
#include <GSLib/tracer.h>
#include "GM/originalSceneMgr.h"

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

BSLIB_SINGLETON_DEFINE(CSceneGMMgr);

CSceneGMMgr::CSceneGMMgr()
{
	m_uniqueID.setUniqueIDMgr(this);
}

CSceneGMMgr::~CSceneGMMgr()
{
	;
}


bool CSceneGMMgr::init()
{
	return true;
}

void CSceneGMMgr::final()
{
	BSLib::Utility::CHashMap<SceneID, CSceneGM*>::iterator it =  m_sceneHashMap.begin();
	for (; it != m_sceneHashMap.end(); ++it) {
		CSceneGM* sceneGM = it->second;
		if (sceneGM == NULL) {
			continue;
		}
		sceneGM->final();
		BSLIB_SAFE_DELETE(sceneGM);
	}
	m_sceneHashMap.clear();
}

void CSceneGMMgr::update(BSLib::uint64 a_delayMilliseconds)
{
	BSLib::Utility::CHashMap<SceneID, CSceneGM*>::iterator it = m_sceneHashMap.begin();
	while (it != m_sceneHashMap.end()) {
		CSceneGM* scene = it->second;
		if (scene == NULL) {
			it = m_sceneHashMap.erase(it);
			continue;
		}
		scene->update(a_delayMilliseconds);
		++it;
	}
}

CSceneGM* CSceneGMMgr::createScene(COriginalScene* a_originalScene)
{
	SceneID sceneID = m_uniqueID.allocateID();
	if (sceneID == m_uniqueID.invalidID()) {
		return NULL;
	}
	CSceneGM* sceneGM = new CSceneGM(sceneID, a_originalScene);
	if (sceneGM == NULL) {
		return false;
	}
	if (!sceneGM->init()) {
		BSLIB_SAFE_DELETE(sceneGM);
		return false;
	}
	m_sceneHashMap.setValue(sceneID, sceneGM);
	return sceneGM;
}

CSceneGM* CSceneGMMgr::allocateScene(SceneTPID a_sceneTPID)
{
	COriginalScene* originalScene = COriginalSceneMgr::singleton().getOriginalScene(a_sceneTPID);
	if (originalScene == NULL) {
		return NULL;
	}
	CSceneGM* sceneGM = NULL;
	originalScene->createSecene(&sceneGM);
	if (sceneGM == NULL) {
		return NULL;;
	}
	return sceneGM;
}

bool CSceneGMMgr::checkUniqueID(SceneID a_sceneID)
{
	return m_sceneHashMap.find(a_sceneID) != m_sceneHashMap.end();
}

}//GM

}//SceneSystem

}//GSLib
