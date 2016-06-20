//////////////////////////////////////////////////////////////////////
//	created:	2015/1/13
//	filename: 	src\GSLib\sceneSystem\GM\sceneCity.cpp
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
/*#include <GSLib/sceneSystem/GM/sceneStage.h>
#include <GSLib/sceneSystem/GM/roleSceneModule.h>
#include <GSLib/sceneSystem/GM/sceneSystemDataMgr.h>
#include <GSLib/playerSystem/GM/roleGM.h>

namespace GSLib
{

namespace SceneSystem
{	

namespace GM
{

CSceneStage::CSceneStage(ESceneType a_sceneType, const CSceneAttr * a_sceneAttr)
:CScene(a_sceneType, a_sceneAttr)
{

}

CSceneStage::~CSceneStage()
{

}

EEnterSceneResult CSceneStage::canEnterScene(CRoleSceneModule * a_sceneRole)
{
	if (a_sceneRole == NULL) {
		return EENTER_STAGE_RESULT_FAIL;
	}
	const CStageAttr *stageAttr = static_cast<const CStageAttr*>(m_sceneAttr);
	if (stageAttr == NULL) {
		return EENTER_STAGE_RESULT_FAIL;
	}
	if (a_sceneRole->m_curScene != NULL) {
		if (a_sceneRole->m_curScene->getSceneType() != ESCENE_TYPE_CITY) {
			return EENTER_SCENE_RESULT_ALREADY_IN_OTHER_INSTANCE;
		}
	}
	if (a_sceneRole->getRoleGM() == NULL) {
		return EENTER_STAGE_RESULT_FAIL;
	}
	if (a_sceneRole->getRoleGM()->getVitality() < stageAttr->m_costVitality) {
		return EENTER_STAGE_RESULT_NOT_ENOUGH_VATALITY;
	}
	const CInstanceAttr * instanceAttr = CSceneSystemDataMgr::singleton().getInstanceAttr(stageAttr->getInstanceTPID());
	if (instanceAttr == NULL) {
		return EENTER_STAGE_RESULT_NOT_SUCH_INSTANCE ;
	}
	if (stageAttr->getStageIndex() >= (BSLib::uint32)instanceAttr->stageSize() || instanceAttr->m_vecStage[stageAttr->getStageIndex()] == NULL) {
		return EENTER_STAGE_RESULT_NO_SUCH_STAGE_INDEX ;
	}
	CRoleInstanceData & roleInstanceData = a_sceneRole->getRoleInstanceData();
	if (instanceAttr->getInstanceType() == EINSTANCE_TYPE_STORY) {
		if (stageAttr->getInstanceTPID() * C_MAX_STAGES_PER_INSTANCE + stageAttr->getStageIndex()  > 
			roleInstanceData.getProgressInstanceTPID() * C_MAX_STAGES_PER_INSTANCE + roleInstanceData.getProgressStageIndex()) {
				return EENTER_STAGE_RESULT_STORY_STAGE_NOT_OPEN;
		}
	} else if (instanceAttr->getInstanceType() == EINSTANCE_TYPE_ADVANCE) {
		if(!roleInstanceData.hasFinishInstance(instanceAttr->m_unlockInstanceTPID)) {
			return EENTER_STAGE_RESULT_INSTANCE_NOT_OPEN;
		}
	} 
	if (stageAttr->m_dailyEnterCount != -1) {
		const CFinishStage * finishStage = roleInstanceData.getStage(stageAttr->getSceneTPID(), stageAttr->m_stageIndex);
		if (finishStage != NULL) {
			if (finishStage->m_dailyEnteredTimes > stageAttr->m_dailyEnterCount) {
				return EENTER_STAGE_RESULT_REACH_DAILY_ENTER_TIMES_LIMIT;
			}
		}
	}
	return EENTER_SCENE_RESULT_SUCCESS;
}

void CSceneStage::_enterScene(CRoleSceneModule * a_sceneRole)
{
}

void CSceneStage::_exitScene(CRoleSceneModule * a_sceneRole)
{
	a_sceneRole->m_roleInstanceData.exitScene();
}

}//GM

}//SceneSystem

}//GSLib
*/
