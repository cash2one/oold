#ifndef __GSLIB_SCENESYSTEM_GM_SCENEGM_H__
#define __GSLIB_SCENESYSTEM_GM_SCENEGM_H__ 

#include <list>
#include <map>
#include <GSLib/sceneSystem/GM/sceneErrorGM.h>
#include <GSLib/baseDef.h>
#include <GSLib/sceneSystem/GM/sceneDefine.h>
#include <GSLib/sceneSystem/GM/scenePrize.h>
#include <GSLib/sceneSystem/GM/roleSceneModule.h>
#include <GSLib/sceneSystem/msgSceneSystem.h>

namespace BSLib
{
	namespace Math
	{
		class CVector3;
	}
}

namespace GFLib
{
	struct SMessage;
	class CMessage;
}

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

class COriginalScene;
class CSceneScriptGM;

typedef std::list<CScenePrize> ScenePrizeContainer;

class CSceneGM
{
public:
	CSceneGM(SceneID a_sceneID, COriginalScene* a_originalScene);
	~CSceneGM();

	bool init();
	void final();

	void update(BSLib::uint64 a_delayMilliseconds);

	bool isFullOfPlayer();


	void enterScene(CRoleSceneModule* a_sceneEntity);

	void leaveScene(CRoleSceneModule* a_sceneEntity);

	void roleMove(CRoleSceneModule* a_sceneEntity, CMsgSceneSystemGC2GMReqRoleMove* a_reqRoleMove);

public:
	EEnterSceneResult canEnterScene(const CRoleSceneModule*  a_sceneEntity) const;

	SceneID getSceneID();

	SceneTPID getSceneTPID() const;

	ESceneType getSceneType() const;

	COriginalScene* getOriginalScene();

	void sendToAllRoles(GFLib::SMessage *message, BSLib::uint32 msgSize);

	void sendToAllRoles(GFLib::CMessage &message);

	void getAllSceneRoles(std::list<CRoleSceneModule*> & listSceneRoles) const;

	const ScenePrizeContainer& getPrize() const;
	
private:
	EEnterSceneResult _canEnterScene(const CRoleSceneModule*  a_sceneEntity) const;
	bool _initSceneController();
	bool _canMove(const CRoleSceneModule &sceneEntity ,const BSLib::Math::CVector3& newPlace) const;
private:
	COriginalScene* m_originalScene;
	CSceneScriptGM* m_sceneController;

	SceneID m_sceneID;

	//普通玩家数量
	BSLib::uint32 m_playerCount;
	BSLib::uint32 m_playerCountMax;
	ScenePrizeContainer m_scenePrize;

	BSLib::Utility::CHashMap<std::string, CRoleSceneModule*> m_sceneRoles;
};

}//GM

}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_GM_SCENEGM_H__

