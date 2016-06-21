#include "GM/btree/sceneGMBTMgr.h"

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

BSLIB_SINGLETON_DEFINE(CSceneGMBTMgr);

CSceneGMBTMgr::CSceneGMBTMgr()
{
	;
}

CSceneGMBTMgr::~CSceneGMBTMgr()
{
	;
}

bool CSceneGMBTMgr::init()
{
	BSLib::BehaviorTree::CBehaviorTreeMgr::init();
	return true;
}

void CSceneGMBTMgr::final()
{
	BSLib::BehaviorTree::CBehaviorTreeMgr::final();
}

}//GM

}//SceneSystem

}//GSLib
