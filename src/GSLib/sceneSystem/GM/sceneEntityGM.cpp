//////////////////////////////////////////////////////////////////////
//	created:	2014/08/21
//	filename: 	src\GSLib\sceneSystem\GM\sceneEntityGM.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
/*
#include <GSLib/sceneSystem/GM/SceneEntityGM.h>
#include <GSLib/sceneSystem/GM/sceneData.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

CSceneEntityGM::CSceneEntityGM()
:m_lastEnteredCity(0)
,m_curScene(NULL)
{
	;
}

void CSceneEntityGM::init()
{
	
}

CSceneEntityGM::~CSceneEntityGM()
{
	;
}

void CSceneEntityGM::update(BSLib::uint64 a_delayMilliseconds)
{
	;
}

void CSceneEntityGM::setLastEnteredCity(SceneTPID a_sceneTPID)
{
	m_lastEnteredCity = a_sceneTPID;
}

SceneTPID CSceneEntityGM::getLastEnteredCity() const
{
	return m_lastEnteredCity;
}

void CSceneEntityGM::setScene(CSceneGM* a_scene)
{
	m_curScene = a_scene;;
}

CSceneGM *CSceneEntityGM::getScene() const
{
	return m_curScene;
}

void CSceneEntityGM::setCurrentPosition(const BSLib::Math::CVector3 & a_newPos)
{
	m_currentPosition = a_newPos;
}

const BSLib::Math::CVector3& CSceneEntityGM::getCurrentPosition() const
{
	return m_currentPosition;
}

void CSceneEntityGM::setLastEnteredCityPos(BSLib::Math::CVector3 & a_pos)
{
	m_lastEnteredCityPos = a_pos;
}

const BSLib::Math::CVector3 & CSceneEntityGM::getLastEnteredCityPos() const
{
	return m_lastEnteredCityPos;
}

SceneTPID CSceneEntityGM::getLatestFinishedScene() const
{
	SceneTPID TPID = 0;
	//for (BSLib::Utility::CHashMap<BSLib::uint32, CSceneData*>::const_iterator itr = m_hashSceneData.begin(); itr != m_hashSceneData.end(); ++itr) {
	//	if (itr->second->m_TPID > TPID) {
	//		TPID = itr->second->m_TPID;
	//	}
	//}

	return TPID;
}





}//GM

}//SceneSystem

}//GSLib
*/