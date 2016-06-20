//////////////////////////////////////////////////////////////////////
//	created:	2014/08/18
//	filename: 	src\GSLib\sceneSystem\GM\originalScene.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_SCENESYSTEM_GM_ORIGINALSCENE_H__
#define __GSLIB_SCENESYSTEM_GM_ORIGINALSCENE_H__ 

#include <GSLib/sceneSystem/GM/sceneGM.h>
#include <BSLib/math/vector3.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

class COriginalScene
{
public:
	COriginalScene(SceneTPID a_sceneTPID, const std::string& a_sceneName, ESceneType  a_sceneType);
	~COriginalScene();

public:
	bool init();
	void final();

	SceneTPID getSceneTPID() const;

	std::string getSceneName() const;

	ESceneType getSceneType() const;

	void setSceneWidth(BSLib::int32 a_width);
	BSLib::int32 getSceneWidth() const;

	void setSceneHeight(BSLib::int32 a_height);
	BSLib::int32 getSceneHeight() const;

	void setSceneBirthPoint(BSLib::Math::CVector3 & a_birthPoint);
	const BSLib::Math::CVector3& getSceneBirthPoint() const;

	void setMaxPlayers(BSLib::int32 a_maxPlayers);
	BSLib::int32 getMaxPlayers() const;

	void setEnterCondition(std::string &a_enterCondition);
	const std::string &getEnterCondition()const;

	void setAutoLearnSkillTPID(SkillTPID a_skillTPID);
	SkillTPID getAutoLearnSkillTPID() const;

	bool createSecene(CSceneGM** a_sceneGM);

public:
	bool canMove(const BSLib::Math::CVector3 & a_newPlace) const;

private:
	SceneTPID m_sceneTPID;
	std::string m_sceneName;
	ESceneType m_sceneType;
	BSLib::int32 m_sceneWidth;
	BSLib::int32 m_sceneHeight;
	BSLib::Math::CVector3 m_birthPoint;
	BSLib::int32 m_maxPlayers;
	std::string m_enterCondition;
	SkillTPID m_autoLearnSkillTPID;

	BSLib::Utility::CHashMap<SceneID, CSceneGM*> m_sceneHashMap;
};

}//GM

}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_GM_ORIGINALSCENE_H__

