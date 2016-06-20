//////////////////////////////////////////////////////////////////////
//	created:	2014/08/19
//	filename: 	src\GSLib\sceneSystem\GM\btree\sceneGMBTMgr.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_SCENESYSTEM_GM_FSM_SCENEGMBTMGR_H__
#define __GSLIB_SCENESYSTEM_GM_FSM_SCENEGMBTMGR_H__ 

#include <BSLib/utility/singleton.h>
#include <BSLib/behaviorTree/behaviorTreeMgr.h>
#include "GM/originalScene.h"

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

class CSceneGMBTMgr : public BSLib::BehaviorTree::CBehaviorTreeMgr
{
public:
	CSceneGMBTMgr();
	~CSceneGMBTMgr();

	BSLIB_SINGLETON_DECLARE(CSceneGMBTMgr);

	bool init();
	void final();
};

}//GM

}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_GM_FSM_SCENEGMBTMGR_H__