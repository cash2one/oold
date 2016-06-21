#ifndef __GSLIB_SCENESYSTEM_GM_SCENEATTR_H__
#define __GSLIB_SCENESYSTEM_GM_SCENEATTR_H__ 

#include <BSLib/utility/baseDef.h>
#include <BSLib/utility/hashMap.h>
#include <GSLib/sceneSystem/GM/sceneDefine.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

class CSceneAttr
{
public:
	CSceneAttr(ESceneType a_sceneType);
	virtual ~CSceneAttr();
public:
	std::string getName() const;
	ESceneType getSceneType() const;
	BSLib::uint32 getSceneTPID() const;
	BSLib::uint32 getMaxPlayers() const;
	BSLib::uint32 getEnterLevel() const;
public:
	std::string m_name;
	ESceneType m_sceneType;
	BSLib::uint32 m_sceneTPID;
	BSLib::uint32 m_maxPlayers;
	BSLib::uint32 m_enterLevel;
	std::set<BSLib::uint32> m_instances;//主城用到的字段
};


}//GM

}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_GM_SCENEATTR_H__

