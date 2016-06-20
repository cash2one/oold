//////////////////////////////////////////////////////////////////////
//	created:	2014/08/19
//	filename: 	src\GSLib\sceneSystem\GM\originalScene.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/sceneSystem/GM/sceneGMMgr.h>
#include <BSLib/math/vector3.h>
#include "GM/originalScene.h"


namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

COriginalScene::COriginalScene(SceneTPID a_sceneTPID, const std::string& a_sceneName, ESceneType a_sceneType)
:m_sceneTPID(a_sceneTPID)
,m_sceneName(a_sceneName)
,m_sceneType(a_sceneType)
,m_sceneWidth(0)
,m_sceneHeight(0)
,m_birthPoint(0,0,0)
,m_maxPlayers(0)
,m_enterCondition("")
,m_autoLearnSkillTPID(0)
{
}

COriginalScene::~COriginalScene()
{
}

bool COriginalScene::init()
{
	return true;
}

void COriginalScene::final()
{
	m_sceneHashMap.clear();
}

GSLib::SceneTPID COriginalScene::getSceneTPID() const
{
	return m_sceneTPID;
}

std::string COriginalScene::getSceneName() const
{
	return m_sceneName;
}

ESceneType COriginalScene::getSceneType() const
{
	return m_sceneType;
}

void COriginalScene::setSceneWidth(BSLib::int32 a_width)
{
	m_sceneWidth = a_width;
}

BSLib::int32 COriginalScene::getSceneWidth() const
{
	return m_sceneWidth;
}

void COriginalScene::setSceneHeight(BSLib::int32 a_height)
{
	m_sceneHeight = a_height;
}

BSLib::int32 COriginalScene::getSceneHeight() const
{
	return m_sceneHeight;
}

void COriginalScene::setSceneBirthPoint(BSLib::Math::CVector3 &a_birthPoint)
{
	m_birthPoint = a_birthPoint;
}

const BSLib::Math::CVector3& COriginalScene::getSceneBirthPoint() const
{
	return m_birthPoint;
}

void COriginalScene::setMaxPlayers(BSLib::int32 a_maxPlayers)
{
	m_maxPlayers = a_maxPlayers;
}

BSLib::int32 COriginalScene::getMaxPlayers() const
{
	return m_maxPlayers;
}

void COriginalScene::setEnterCondition(std::string &a_enterCondition)
{
	m_enterCondition = a_enterCondition;
}

const std::string & COriginalScene::getEnterCondition() const
{
	return m_enterCondition;
}

void COriginalScene::setAutoLearnSkillTPID(SkillTPID a_skillTPID)
{
	m_autoLearnSkillTPID = a_skillTPID;
}

SkillTPID COriginalScene::getAutoLearnSkillTPID() const
{
	return m_autoLearnSkillTPID;
}

bool COriginalScene::createSecene(CSceneGM** a_sceneGM)
{
	CSceneGM* sceneGM = NULL;
	BSLib::Utility::CHashMap<SceneID, CSceneGM*>::iterator it = m_sceneHashMap.begin();
	for (; it != m_sceneHashMap.end(); ++it) {
		sceneGM = it->second;
		if (sceneGM == NULL) {
			continue;
		}
		if (sceneGM->isFullOfPlayer()) {
			continue;
		}
		*a_sceneGM = sceneGM;
		return true;
	}
	sceneGM = CSceneGMMgr::singleton().createScene(this);
	if (sceneGM == NULL) {
		return false;
	}
	m_sceneHashMap.setValue(sceneGM->getSceneID(), sceneGM);
	*a_sceneGM = sceneGM;
	return false;
}

bool COriginalScene::canMove(const BSLib::Math::CVector3 & a_newPlace) const
{
	return true;
}




}//GM

}//SceneSystem

}//GSLib
