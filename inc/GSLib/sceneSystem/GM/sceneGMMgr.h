#ifndef __GSLIB_SCENESYSTEM_GM_SCENEGMMGR_H__
#define __GSLIB_SCENESYSTEM_GM_SCENEGMMGR_H__ 

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/hashMap.h>
#include <BSLib/utility/uniqueID.h>
#include <GSLib/sceneSystem/GM/sceneGM.h>
#include <GSLib/baseDef.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

class CSceneGMMgr : public BSLib::Utility::CUniqueIDMgr<SceneID>
{
public:
	CSceneGMMgr();
	~CSceneGMMgr();

	BSLIB_SINGLETON_DECLARE(CSceneGMMgr);

	bool init();
	void final();

	void update(BSLib::uint64 a_delayMilliseconds);

	// for scene system
	CSceneGM* createScene(COriginalScene* a_originalScene);

public:
	// for other system
	CSceneGM* allocateScene(SceneTPID a_sceneTPID);
	
private:
	virtual bool checkUniqueID(SceneID a_sceneID);

private:
	BSLib::Utility::CHashMap<SceneID, CSceneGM*> m_sceneHashMap;
	BSLib::Utility::CUniqueID<SceneID> m_uniqueID;
};

}//GM

}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_GM_SCENEGMMGR_H__

