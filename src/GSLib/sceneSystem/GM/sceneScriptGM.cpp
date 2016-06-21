#include <GSLib/tracer.h>
#include "GM/originalScene.h"
#include "GM/fsm/sceneGMFSMMgr.h"
#include <GSLib/sceneSystem/GM/sceneScriptGM.h>
#include <GSLib/sceneSystem/GM/sceneScriptEnv.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

CSceneScriptGM::CSceneScriptGM(CSceneGM* a_sceneGM)
: m_sceneGM(a_sceneGM)
, m_fsm(NULL)
{
	;
}

CSceneScriptGM::~CSceneScriptGM()
{
	;
}

bool CSceneScriptGM::init()
{
	if (m_fsm != NULL) {
		return false;
	}
	if (m_sceneGM == NULL) {
		return false;
	}
	COriginalScene* originalScene = m_sceneGM->getOriginalScene();
	if (originalScene == NULL) {
		return false;
	}
	std::string sceneName = originalScene->getSceneName();
	
	//CSceneGMFSMMgr::singleton().createFSM(sceneName, this, &m_fsm);
	//if (m_fsm == NULL) {
	//	BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "����FSM[FSMName=%s]ʧ��", sceneName.c_str());
	//	return false;
	//}
	//if (!m_fsm->initFSM()) {
	//	BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "��ʼ��FSM[FSMName=%s]ʧ��", sceneName.c_str());
	//	CSceneGMFSMMgr::singleton().removeFSM(&m_fsm);
	//	return false;
	//}
	return true;
}

void CSceneScriptGM::final()
{
	if (m_fsm != NULL) {
		m_fsm->finalFSM();
		CSceneGMFSMMgr::singleton().removeFSM(&m_fsm);
	}
}

void CSceneScriptGM::update(BSLib::uint64 a_delayMilliseconds)
{
	if (m_fsm != NULL) {
		m_fsm->updateFSM();
	}
}

bool CSceneScriptGM::getVariation(BSLib::uint32 a_variableIndex, BSLib::Utility::CScriptData* a_scriptData)
{
	if (a_variableIndex < BSLib::Utility::ESCRIPT_VARIABLE_EXTEND) {
		return CSceneScriptEnv::singleton().getVariation(a_variableIndex, a_scriptData);
	}
// 	switch (a_variableIndex)
// 	{
// 	}
	return false;
}

bool CSceneScriptGM::executeFunction(BSLib::uint32 a_functionIndex, std::vector<BSLib::Utility::CScriptData>& a_functionParamenterList, BSLib::Utility::CScriptData* a_functionResult)
{
	if (a_functionIndex < BSLib::Utility::ESCRIPT_VARIABLE_EXTEND) {
		return CSceneScriptEnv::singleton().executeFunction(a_functionIndex, a_functionParamenterList, a_functionResult);
	}
 	switch (a_functionIndex)
 	{
	case ESCRIPT_FUNCINDEX_SCENE_GETVARIATION:
		return _executeFunctionSceneGetVariation(a_functionParamenterList, a_functionResult);
	case ESCRIPT_FUNCINDEX_SCENE_SETVARIATION:
		return _executeFunctionSceneSetVariation(a_functionParamenterList, a_functionResult);
	default:
		BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "�ű�����������[FunctionIndex=%d]", a_functionIndex);
 	}
	return false;
}

bool CSceneScriptGM::_executeFunctionSceneGetVariation(std::vector<BSLib::Utility::CScriptData>& a_functionParamenterList, BSLib::Utility::CScriptData* a_functionResult)
{
	if (a_functionParamenterList.size() != 1) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "����[Scene.GetVariation]��������ȷ");
		return false;
	}
	std::string name = "";
	if (!a_functionParamenterList[0].isText()) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "����[Scene.GetVariation]�������Ǳ�����");
		return false;
	}
	if (!a_functionParamenterList[0].getString(name)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "����[Scene.GetVariation]��ȡ������ʧ��");
		return false;
	}
	if (m_defineVariation.find(name) != m_defineVariation.end()) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "����[Scene.GetVariation]����������");
		return false;
	}
	if (!m_defineVariation.getValue(name, *a_functionResult)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "����[Scene.GetVariation]��ȡ����ʧ��");
		return false;
	}
	return true;
}

bool CSceneScriptGM::_executeFunctionSceneSetVariation(std::vector<BSLib::Utility::CScriptData>& a_functionParamenterList, BSLib::Utility::CScriptData* a_functionResult)
{
	if (a_functionParamenterList.size() != 2) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "����[Scene.SetVariation]��������ȷ");
		return false;
	}
	std::string name = "";
	if (!a_functionParamenterList[0].isText()) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "����[Scene.SetVariation]����1���Ǳ�����");
		return false;
	}
	if (!a_functionParamenterList[0].getString(name)) {
		BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "����[Scene.SetVariation]��ȡ������ʧ��");
		return false;
	}
// 	if (m_defineVariation.find(name) != m_defineVariation.end()) {
// 		BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "����[Scene.SetVariation]����������");
// 		return false;
// 	}
	m_defineVariation.setValue(name, a_functionParamenterList[1]);
	*a_functionResult =  a_functionParamenterList[1];
	return true;
}

}//GM

}//SceneSystem

}//GSLib

