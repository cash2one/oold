//////////////////////////////////////////////////////////////////////
//	created:	2014/08/19
//	filename: 	src\GSLib\sceneSystem\GM\sceneGM.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/sceneSystem/GM/sceneGM.h>
#include <GSLib/sceneSystem/GM/roleSceneModule.h>
#include <BSLib/framework/message/message.h>
#include "GM/originalScene.h"
#include <GSLib/sceneSystem/GM/sceneScriptGM.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/playerSystem/GM/playerGM.h>
#include <GSLib/skillSystem/GM/roleSkillModule.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

CSceneGM::CSceneGM(SceneID a_sceneID, COriginalScene* a_originalScene)
: m_originalScene(a_originalScene)
, m_sceneController(NULL)
, m_sceneID(a_sceneID)
,m_playerCount(0)
,m_playerCountMax(0)
{
}

CSceneGM::~CSceneGM()
{
	;
}

bool CSceneGM::init()
{
	//if (!_initSceneController()) {
	//	return false;
	//}
	return true;
}

void CSceneGM::final()
{
	if (m_sceneController != NULL) {
		m_sceneController->final();
		BSLIB_SAFE_DELETE(m_sceneController);
	}
}

void CSceneGM::update(BSLib::uint64 a_delayMilliseconds)
{
	if (m_sceneController != NULL) {
		m_sceneController->update(a_delayMilliseconds);
	}
}

bool CSceneGM::isFullOfPlayer()
{
	if (m_originalScene != NULL) {
		return m_playerCount >= (BSLib::uint32)m_originalScene->getMaxPlayers();
	}

	return true;
}

EEnterSceneResult CSceneGM::canEnterScene(const CRoleSceneModule*  a_sceneEntity) const
{
	return _canEnterScene(a_sceneEntity);
}

GSLib::SceneID CSceneGM::getSceneID()
{
	return m_sceneID;
}

SceneTPID CSceneGM::getSceneTPID() const
{
	if (m_originalScene != NULL) {
		return m_originalScene->getSceneTPID();
	}

	return 0;
}

ESceneType CSceneGM::getSceneType() const
{
	if (m_originalScene != NULL) {
		return m_originalScene->getSceneType();
	}

	return ESCENE_TYPE_NONE;
}

COriginalScene* CSceneGM::getOriginalScene()
{
	return m_originalScene;
}

void CSceneGM::sendToAllRoles(GFLib::SMessage *message, BSLib::uint32 msgSize)
{
	if (message == NULL) {
		return;
	}
	for (BSLib::Utility::CHashMap<std::string, CRoleSceneModule*>::iterator itr = m_sceneRoles.begin(); itr != m_sceneRoles.end(); ++itr) {
		if (itr->second != NULL) {
			itr->second->sendMsgToClient(message, msgSize);
		}
	}
}

void CSceneGM::sendToAllRoles(GFLib::CMessage &message)
{
	for (BSLib::Utility::CHashMap<std::string, CRoleSceneModule*>::iterator itr = m_sceneRoles.begin(); itr != m_sceneRoles.end(); ++itr) {
		if (itr->second != NULL) {
			itr->second->sendMsgToClient(message);
		}
	}
}

void CSceneGM::getAllSceneRoles(std::list<CRoleSceneModule*> & listSceneRoles) const
{
	for (BSLib::Utility::CHashMap<std::string, CRoleSceneModule*>::const_iterator itr = m_sceneRoles.begin(); itr != m_sceneRoles.end(); ++itr) {
		if (itr->second != NULL) {
			listSceneRoles.push_back(itr->second);
		}
	}
}

const ScenePrizeContainer& CSceneGM::getPrize() const
{
	// temporary data
	//if (getSceneType() == ESCENE_TYPE_INSTANCE) {
	//	for (BSLib::int32 i = 0; i < 9; ++i) {
	//		CScenePrize scenePrize(1000 + i);
	//		m_scenePrize.push_back(scenePrize);
	//	}
	//}

	return m_scenePrize;
}


EEnterSceneResult CSceneGM::_canEnterScene(const CRoleSceneModule* a_sceneEntity) const
{
	if (a_sceneEntity == NULL) {
		return EENTER_SCENE_RESULT_SYSTEM_ERROR ;
	}

	if (m_originalScene == NULL) {
		return EENTER_SCENE_RESULT_SYSTEM_ERROR ;
	}

	//CSceneGM *curScene = a_sceneEntity->getScene();
	//if (curScene != NULL) {
	//	if (curScene->getSceneTPID() == m_originalScene->getSceneTPID()) {
	//		return EENTERSCENE_RESULT_ALREADY_IN_SCENE;
	//	}
		//if (curScene->getSceneType() == ESCENE_TYPE_STAGE) {
		//	return EENTERSCENE_RESULT_ALREADY_IN_INSTANCE;
		//}
	//}


	//TODO
	//主城与副本对应关系
	//进入该场景的限制判断
	//等级 体力 当天次数 VIP等等

	return EENTER_SCENE_RESULT_SUCCESS ;
}

bool CSceneGM::_initSceneController()
{
	if (m_sceneController != NULL) {
		return false;
	}
	m_sceneController = new CSceneScriptGM(this);
	if (m_sceneController == NULL) {
		return false;
	}
	return m_sceneController->init();
}

bool CSceneGM::_canMove(const CRoleSceneModule &sceneEntity, const BSLib::Math::CVector3 & newPlace) const
{
	if (m_originalScene == NULL) {
		return false;
	}

	return m_originalScene->canMove(newPlace);
}

void CSceneGM::enterScene(CRoleSceneModule* a_sceneEntity)
{	
	m_sceneRoles.setValue(a_sceneEntity->getRoleGM()->getName(), a_sceneEntity);
	++m_playerCount;

	if (getSceneType() == ESCENE_TYPE_CITY) {
		//if (getSceneTPID() == a_sceneEntity->getLastEnteredCity()) {
		//	a_sceneEntity->setCurrentPosition(a_sceneEntity->getLastEnteredCityPos());
		//} else {
		//	BSLib::Math::CVector3 birthPlace = m_originalScene->getSceneBirthPoint();
		//	a_sceneEntity->setCurrentPosition(birthPlace);
		//	a_sceneEntity->setLastEnteredCity(getSceneTPID());
		//}
		//a_sceneEntity->setLastEnteredCity(getSceneTPID());
	} 

	if (m_originalScene->getAutoLearnSkillTPID() != 0) {
		GSLib::PlayerSystem::GM::CRoleGM* role = a_sceneEntity->getRoleGM();
		if (role != NULL) {
			GSLib::SkillSystem::GM::CRoleSkillModule *skillModule = (GSLib::SkillSystem::GM::CRoleSkillModule*)(role->getPlayerModuleGM(EMODULECTYPE_SKILL));
			if (skillModule != NULL) {
				//skillModule->getSkill(m_originalScene->getAutoLearnSkillTPID());
			}
		}
	}

	//a_sceneEntity->setCurScene(this);
}

void CSceneGM::leaveScene(CRoleSceneModule* a_sceneEntity)
{
	if (m_sceneRoles.find(a_sceneEntity->getRoleGM()->getName()) == m_sceneRoles.end()) {
		return;
	}

	m_sceneRoles.remove(a_sceneEntity->getRoleGM()->getName());
	--m_playerCount;

	if (getSceneType() == ESCENE_TYPE_CITY) {
		//BSLib::Math::CVector3 lastPos = a_sceneEntity->getCurrentPosition();
		//a_sceneEntity->setLastEnteredCityPos(lastPos);
	}
	a_sceneEntity->setCurScene(NULL);
}

void CSceneGM::roleMove(CRoleSceneModule* a_sceneEntity, CMsgSceneSystemGC2GMReqRoleMove* a_reqRoleMove)
{
	;
}

}//GM

}//SceneSystem

}//GSLib
