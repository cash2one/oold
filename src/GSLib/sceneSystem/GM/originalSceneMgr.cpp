#include <BSLib/utility/file/dirInfo.h>
#include <BSLib/utility/file/fileInfo.h>
#include <BSLib/utility/table.h>
#include <GFLib/commonServer/commonServer.h>
#include <GSLib/tracer.h>
#include <BSLib/utility/string.h>
#include "GM/originalSceneMgr.h"
#include "GM/fsm/sceneGMFSMMgr.h"
#include "GM/btree/sceneGMBTMgr.h"

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{


BSLIB_SINGLETON_DEFINE(COriginalSceneMgr);

COriginalSceneMgr::COriginalSceneMgr()
{
	;
}

COriginalSceneMgr::~COriginalSceneMgr()
{
	;
}

bool COriginalSceneMgr::init()
{
	return true;
}

void COriginalSceneMgr::final()
{
	BSLib::Utility::CHashMap<SceneTPID, COriginalScene*>::iterator it =  m_originalSceneHashMap.begin();
	for (; it != m_originalSceneHashMap.end(); ++it) {
		COriginalScene* scene = it->second;
		if (scene == NULL) {
			it = m_originalSceneHashMap.erase(it);
			continue;
		}
		scene->final();
		BSLIB_SAFE_DELETE(scene);
	}
	m_originalSceneHashMap.clear();
}

bool COriginalSceneMgr::loadGameConfig(const std::string& a_configPath)
{
	BSLib::Utility::CStringA configPath = a_configPath;
	configPath += "\\scene\\";
	BSLib::Utility::CDirInfo::standardization(configPath);

	if (!_loadSceneConfig(configPath)) {
		return false;
	}
	if (!_loadSceneScript(configPath)) {
		return false;
	}
	if (!_initOriginalScene(configPath)) {
		return false;
	}
	return true;
}

COriginalScene* COriginalSceneMgr::getOriginalScene(SceneTPID a_sceneTPID)
{
	COriginalScene* originalScene = NULL;
	m_originalSceneHashMap.getValue(a_sceneTPID, originalScene);
	return originalScene;
}

bool COriginalSceneMgr::_loadSceneConfig(const std::string& a_configPath)
{
	BSLib::Utility::CStringA scenePath = a_configPath;
	scenePath += "gameScene.xml";
	BSLib::Utility::CDirInfo::standardization(scenePath);

	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(scenePath)) {
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载场景配置失败[%s]", scenePath.c_str());
		return false;
	}
	GFLib::CommonServer::ICommonServer* commonServer = GFLib::CommonServer::ICommonServer::getCommonServer();
	if (commonServer == NULL) {
		return false;
	}
	std::string serverKey = commonServer->getServerKey();
	try {
		BSLib::Utility::CTable& table = tableSheet["scene"];
		for (BSLib::uint32 i=0; i < table.getRowCount(); ++i) {
			std::string serverName;
			std::string sceneName;
			SceneTPID sceneTPID = 0;
			BSLib::uint32 sceneType = 0;
			BSLib::int32 sceneWidth = 0;
			BSLib::int32 sceneHeight = 0;
			BSLib::int32 maxPlayers = 0;
			std::string enterCondition;
			std::string strBirthPoint;
			SkillTPID skillTPID;
			
			table[i]["name"] >> sceneName;
			table[i]["id"] >> sceneTPID;
			table[i]["server"] >> serverName;
			table[i]["type"] >> sceneType;
			table[i]["maxPlayers"] >> maxPlayers;
			table[i]["enterCondition"] >> enterCondition;
			table[i]["birth"] >> strBirthPoint;
			table[i]["autoLearnSkillID"] >> skillTPID;

			if (!serverName.empty()) {
				if (serverName != serverKey) {
					continue;
				}
			}

			if (m_originalSceneHashMap.find(sceneTPID) != m_originalSceneHashMap.end()) {
				BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "SceneTPID重复[%d]", sceneTPID);
				return false;
			}
			COriginalScene* originalScene  = new COriginalScene(sceneTPID, sceneName, (ESceneType)sceneType);
			originalScene->setSceneWidth(sceneWidth);
			originalScene->setSceneHeight(sceneHeight);
			originalScene->setMaxPlayers(maxPlayers);
			originalScene->setEnterCondition(enterCondition);
			originalScene->setAutoLearnSkillTPID(skillTPID);
			std::vector<std::string> vecStr;
			BSLib::Utility::CStringA cstrBirth(strBirthPoint);
			std::string separator(",");
			cstrBirth.split(vecStr, ',');
			if (vecStr.size() == 3) {
				BSLib::Math::CVector3 vector3;
				vector3.setX(static_cast<float>(atof(vecStr[0].c_str())));
				vector3.setY(static_cast<float>(atof(vecStr[1].c_str())));
				vector3.setZ(static_cast<float>(atof(vecStr[2].c_str())));
				originalScene->setSceneBirthPoint(vector3);
			}

			m_originalSceneHashMap.setValue(sceneTPID, originalScene);
		}
	} catch (...){
		BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载场景文件失败[%s]", scenePath.c_str());
		return false;
	}
	return true;
}

bool COriginalSceneMgr::_loadSceneScript(const std::string& a_configPath)
{
	BSLib::Utility::CHashMap<SceneTPID, COriginalScene*>::iterator it =  m_originalSceneHashMap.begin();
	for (; it != m_originalSceneHashMap.end(); ++it) {
		COriginalScene* scene = it->second;
		if (scene == NULL) {
			return false;
		}
		BSLib::Utility::CStringA scenePath = a_configPath;
		scenePath += scene->getSceneName();
		scenePath += "\\";

		BSLib::Utility::CStringA fsmFile = scenePath;
		fsmFile += "fsmScene.xml";
		BSLib::Utility::CDirInfo::standardization(fsmFile);
		if (BSLib::Utility::CFileInfo::isExist(fsmFile)) {
			if (!CSceneGMFSMMgr::singleton().loadFSMFile(fsmFile)) {
				BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载场景文件失败[%s]", fsmFile.c_str());
				return false;
			}
		}
		BSLib::Utility::CStringA btFile = scenePath;
		btFile += "btScene.xml";
		BSLib::Utility::CDirInfo::standardization(btFile);
		if (BSLib::Utility::CFileInfo::isExist(btFile)) {
			if (!CSceneGMBTMgr::singleton().loadBTFromFile(btFile)) {
				BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载场景文件失败[%s]", btFile.c_str());
				return false;
			}
		}
	}

	return true;
}

bool COriginalSceneMgr::_initOriginalScene(const std::string& a_configPath)
{
	BSLib::Utility::CHashMap<SceneTPID, COriginalScene*>::iterator it =  m_originalSceneHashMap.begin();
	for (; it != m_originalSceneHashMap.end(); ++it) {
		COriginalScene* scene = it->second;
		if (scene == NULL) {
			return false;
		}
		//std::string fileName = a_configPath + "sceneConfig.xml";
		//BSLib::Utility::CTableSheet tableSheet;
		//if (!tableSheet.loadXmlFile(a_configPath)) {
		//	BSLIB_LOG_INFO(ETT_GSLIB_SCENESYSTEM, "加载场景配置失败[%s]", a_configPath.c_str());
		//	return false;
		//}
		//if (!scene->init()) {
		//	return false;
		//}
	}
	return true;
}

}//GM

}//SceneSystem

}//GSLib
