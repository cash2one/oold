#include <GSLib/sceneSystem/GM/sceneAttr.h>

namespace GSLib
{

namespace SceneSystem
{	

namespace GM
{

CSceneAttr::CSceneAttr(ESceneType a_sceneType)
:m_name("")
,m_sceneType(a_sceneType )
,m_sceneTPID(0)
,m_maxPlayers(1)
,m_enterLevel(0)
{

}

CSceneAttr::~CSceneAttr()
{

}

std::string CSceneAttr::getName() const
{
	return m_name;
}

ESceneType CSceneAttr::getSceneType() const
{
	return m_sceneType;
}

BSLib::uint32 CSceneAttr::getSceneTPID() const
{
	return m_sceneTPID;
}

BSLib::uint32 CSceneAttr::getMaxPlayers() const
{
	return m_maxPlayers;
}

BSLib::uint32 CSceneAttr::getEnterLevel() const
{
	return m_enterLevel;
}

}//GM

}//SceneSystem

}//GSLib

