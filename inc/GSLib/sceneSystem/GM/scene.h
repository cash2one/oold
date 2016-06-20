//////////////////////////////////////////////////////////////////////
//	created:	2015/1/8
//	filename: 	GSLib\sceneSystem\GM\scene.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_SCENESYSTEM_GM_SCENE_H__
#define __GSLIB_SCENESYSTEM_GM_SCENE_H__ 

#include <BSLib/utility/baseDef.h>
#include <GSLib/sceneSystem/GM/sceneDefine.h>
#include <GSLib/sceneSystem/GM/sceneErrorGM.h>
#include <BSLib/utility/hashMap.h>
#include <GSLib/sceneSystem/GM/sceneSystemData.h>
#include <set>

namespace GFLib
{
	class CMessage;
}

namespace GSLib
{
namespace SceneSystem
{

namespace GM
{

class CSceneAttr;
class CRoleSceneModule;
class CStageReportResult;

class CScene
{
public:
	CScene(ESceneType a_sceneType, const CSceneAttr * a_sceneAttr);
	virtual ~CScene();
public:
	ESceneType getSceneType() const;
	
	void setSceneID(BSLib::uint32 a_sceneID);
	BSLib::uint32 getSceneID() const;
	
	BSLib::uint32 getSceneTPID() const;

	const CSceneAttr *getSceneAttr() const;

	BSLib::uint32 getScenePlayerCount() const;

	void enterScene(CRoleSceneModule * a_sceneRole);

	void exitScene(CRoleSceneModule * a_sceneRole);

	void sendToAllRoles(GFLib::CMessage &message);

	void genStagePrize();

	CStageMonster & getStageMonsterPrize();

	void updateRandomMonsterPrize(const std::vector<BSLib::uint32> &a_clearedRandomMonster);

	void determineStagePrizeItem(CRoleSceneModule& a_sceneRole, const std::vector<BSLib::uint32>& a_receiveItems);

public:
	virtual EEnterSceneResult canEnterScene(CRoleSceneModule * a_sceneRole) = 0;

	virtual void genMonster(CRoleSceneModule * a_sceneRole);

	virtual void reportStageResult(CRoleSceneModule &a_sceneRole, const CStageReportResult & a_result);

	virtual void clearStage(CRoleSceneModule& a_sceneRole, bool isBreakDownItem);
private:
	virtual void _enterScene(CRoleSceneModule * a_sceneRole) = 0;
	virtual void _exitScene(CRoleSceneModule * a_sceneRole) = 0;
protected:
	void _genMonster(CStageMonster & a_stageMonster, const CStageUnitAttr & a_stageUnitAttr, const CStagePrizeAttr & a_stagePrizeAttr, BSLib::uint32 &a_curIndex);
	void _getMonster(const CDropMonsterAttr& a_monsterAttr, const CStagePrizeAttr& a_stagePrizeAttr, CMonster& a_monster);
	void _genStagePrizeAttr(CRoleSceneModule& a_sceneRole, CStagePrizeAttr & a_stagePrize) const;
	bool _getPetTaskPrizeAttr(CRoleSceneModule& a_sceneRole, CStagePrizeAttr & a_stagePrizeAttr) const;
private:
	void _genRandomStageMonster(CRoleSceneModule * a_sceneRole);
public:
	BSLib::uint32 m_sceneID;
	ESceneType m_sceneType;
	const CSceneAttr *m_sceneAttr;	
	std::set<SRoleKey> m_setSceneRole;
	CStageMonster m_stagePrize;	//创建关卡的玩家的奖励
	CStageMonster m_stageMonster;
	BSLib::uint32 m_reviveCount;
};

}//GM

}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_GM_SCENE_H__
