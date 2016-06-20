//////////////////////////////////////////////////////////////////////
//	created:	2014/08/19
//	filename: 	GSLib\sceneSystem\GM\sceneEntityGM.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
/*
#ifndef __GSLIB_SCENESYSTEM_GM_SCENEENTITYGM_H__
#define __GSLIB_SCENESYSTEM_GM_SCENEENTITYGM_H__ 

#include <BSLib/math/vector3.h>
#include <GSLib/sceneSystem/GM/entityGM.h>

namespace BSLib
{
	namespace Math
	{
		class CVector3;
	};
};

namespace GFLib
{
	struct SMessage;
	class CMessage;
};

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

class CSceneGM;
class CSceneData;

class CSceneEntityGM : public CEntityGM
{
public:
	CSceneEntityGM();
	virtual ~CSceneEntityGM();

	void init();
	void update(BSLib::uint64 a_delayMilliseconds);
public:
	void setLastEnteredCity(SceneTPID a_sceneTPID);
	SceneTPID getLastEnteredCity() const;

	void setScene(CSceneGM *a_scene);
	CSceneGM *getScene() const;

	void setCurrentPosition(const BSLib::Math::CVector3 &a_newPos);
	const BSLib::Math::CVector3& getCurrentPosition() const;

	void setLastEnteredCityPos(BSLib::Math::CVector3 & a_pos);
	const BSLib::Math::CVector3 & getLastEnteredCityPos() const;

	virtual bool sendSceneMsgToClient(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize) = 0;
	virtual bool sendSceneMsgToClient(GFLib::CMessage& a_msg) = 0;
	virtual BSLib::uint32 getVIPLevel() = 0;

	SceneTPID getLatestFinishedScene() const;
private:
	SceneTPID m_lastEnteredCity;
	BSLib::Math::CVector3	 m_lastEnteredCityPos;
	CSceneGM* m_curScene;
	BSLib::Math::CVector3 m_currentPosition;
	//BSLib::Utility::CHashMap<BSLib::uint32, CSceneData*> m_hashSceneData;
};

}//GM

}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_GM_SCENEENTITYGM_H__
*/
