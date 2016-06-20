//////////////////////////////////////////////////////////////////////
//	created:	2015/1/13
//	filename: 	GSLib\sceneSystem\GM\sceneStage.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_SCENESYSTEM_GM_SCENE_IMPL_H__
#define __GSLIB_SCENESYSTEM_GM_SCENE_IMPL_H__ 

#include <BSLib/utility/baseDef.h>
#include <GSLib/sceneSystem/GM/scene.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

//////////////////////////////////////////////////////////////////////////////////////
class CSceneCity : public CScene
{
public:
	CSceneCity(ESceneType a_sceneType, const CSceneAttr * a_sceneAttr);
	~CSceneCity();
public:
	virtual EEnterSceneResult canEnterScene(CRoleSceneModule * a_sceneRole);
private:
	virtual void _enterScene(CRoleSceneModule * a_sceneRole);
	virtual void _exitScene(CRoleSceneModule * a_sceneRole);
};

////////////////////////////////////////////////////////////////////////////////////
class CSceneStage : public CScene
{
public:
	CSceneStage(ESceneType a_sceneType, const CSceneAttr * a_sceneAttr);
	~CSceneStage();
public:
	virtual EEnterSceneResult canEnterScene(CRoleSceneModule * a_sceneRole);
	virtual void reportStageResult(CRoleSceneModule & a_sceneRole, const CStageReportResult & a_result);
	virtual void clearStage(CRoleSceneModule& a_sceneRole, bool isBreakDownItem);
private:
	virtual void _enterScene(CRoleSceneModule * a_sceneRole);
	virtual void _exitScene(CRoleSceneModule * a_sceneRole);
};

/////////////////////////////////////////////////////////////////////////////////////////////
class CSceneArena : public CScene
{
public:
	CSceneArena(ESceneType a_sceneType, const CSceneAttr * a_sceneAttr);
	~CSceneArena();
public:
	virtual EEnterSceneResult canEnterScene(CRoleSceneModule * a_sceneRole);
private:
	virtual void _enterScene(CRoleSceneModule * a_sceneRole);
	virtual void _exitScene(CRoleSceneModule * a_sceneRole);
};

/////////////////////////////////////////////////////////////////////////////////////////////
class CSceneContinuousStage : public CScene
{
public:
	CSceneContinuousStage(ESceneType a_sceneType, const CSceneAttr * a_sceneAttr);
	~CSceneContinuousStage();
public:
	virtual EEnterSceneResult canEnterScene(CRoleSceneModule * a_sceneRole);
private:
	virtual void _enterScene(CRoleSceneModule * a_sceneRole);
	virtual void _exitScene(CRoleSceneModule * a_sceneRole);
};

/////////////////////////////////////////////////////////////////////////////////////////////
class CSceneRandomStage : public CScene
{
public:
	CSceneRandomStage(ESceneType a_sceneType, const CSceneAttr * a_sceneAttr);
	~CSceneRandomStage();
public:
	virtual EEnterSceneResult canEnterScene(CRoleSceneModule * a_sceneRole);
	virtual void reportStageResult(CRoleSceneModule & a_sceneRole, const CStageReportResult & a_result);
private:
	virtual void _enterScene(CRoleSceneModule * a_sceneRole);
	virtual void _exitScene(CRoleSceneModule * a_sceneRole);
};

/////////////////////////////////////////////////////////////////////////////////////////////
class CSceneGoldLandStage : public CScene
{
public:
	CSceneGoldLandStage(ESceneType a_sceneType, const CSceneAttr * a_sceneAttr);
	~CSceneGoldLandStage();
public:
	virtual EEnterSceneResult canEnterScene(CRoleSceneModule * a_sceneRole);
	virtual void reportStageResult(CRoleSceneModule & a_sceneRole, const CStageReportResult & a_result);
private:
	virtual void _enterScene(CRoleSceneModule * a_sceneRole);
	virtual void _exitScene(CRoleSceneModule * a_sceneRole);
};

/////////////////////////////////////////////////////////////////////////////////////////////
class CSceneExpLandStage : public CScene
{
public:
	CSceneExpLandStage(ESceneType a_sceneType, const CSceneAttr * a_sceneAttr);
	~CSceneExpLandStage();
public:
	virtual EEnterSceneResult canEnterScene(CRoleSceneModule * a_sceneRole);
	virtual void reportStageResult(CRoleSceneModule & a_sceneRole, const CStageReportResult & a_result);
private:
	virtual void _enterScene(CRoleSceneModule * a_sceneRole);
	virtual void _exitScene(CRoleSceneModule * a_sceneRole);
};











}//GM

}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_GM_SCENE_H__
