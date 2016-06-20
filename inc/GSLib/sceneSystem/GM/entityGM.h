//////////////////////////////////////////////////////////////////////
//	created:	2014/08/19
//	filename: 	GSLib\sceneSystem\GM\entityGM.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_SCENESYSTEM_GM_ENTITYGM_H__
#define __GSLIB_SCENESYSTEM_GM_ENTITYGM_H__ 

#include <GSLib/baseDef.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

enum EEntityType
{
	ESCENENTITY_PLAYER = 0,
	ESCENENTITY_NPC,
	ESCENENTITY_PET,
	ESCENENTITY_MAX,
};

class CEntityGM
{
public:
	CEntityGM(){};
	virtual ~CEntityGM(){};

	virtual EntityID getEntityID() const = 0;
	virtual EntityTPID getTPID() const = 0;
	virtual std::string getName() const = 0;
	virtual EEntityType getType() const = 0;
};

}//GM

}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_GM_ENTITYGM_H__
