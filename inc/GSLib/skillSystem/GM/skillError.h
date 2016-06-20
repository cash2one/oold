//////////////////////////////////////////////////////////////////////
//	created:	2014/09/12
//	filename: 	GSLib\skillSystem\GM\skillError.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////

#ifndef		__GSLIB_SKILLSYSTEM_GM_SKILLERROR_H__
#define		__GSLIB_SKILLSYSTEM_GM_SKILLERROR_H__


namespace GSLib
{
namespace SkillSystem
{
namespace GM
{

enum ELearnSkillError
{
	LEARN_SKILL_ERROR_SUCCESS,                                       //学习技能成功
	LEARN_SKILL_ERROR_FAIL,                                              //学习技能失败
	LEARN_SKILL_ERROR_ALREADY_LEARN,                            //技能已经学习
	LEARN_SKILL_ERROR_INVALID_SKILLTPID,                        //非法技能ID
	LEARN_SKILL_ERROR_NOT_ENOUGH_LEVEL,                     //学习技能所需角色等级不够
	LEARN_SKILL_ERROR_INCORRECT_ROLETPID,					//角色TPID不符
	LEARN_SKILL_ERROR_NOT_ENOUGH_GOLD,                     //学习技能所需的金币不足
	LEARN_SKILL_ERROR_NOT_ENOUGH_PVPCOIN,                //学习技能所需的PVP币不足
	LEARN_SKILL_ERROR_NOT_ENOUGH_DIAMOND,              //学习技能所需的钻石不足
	LEARN_SKILL_ERROR_NOT_ENOUGH_SKILL_POINT,           //学习技能所需的技能点不足
};

enum EUpgradeSkillError
{
	UPGRADE_SKILL_ERROR_SUCCESS,                                  //升级技能成功
	UPGRADE_SKILL_ERROR_FAIL,                                         //升级技能失败
	UPGRADE_SKILL_ERROR_NOT_LEARN,                             //该技能尚未学习
	UPGRADE_SKILL_ERROR_INVALID_SKILLTPID,                   //非法技能ID
	UPGRADE_SKILL_ERROR_MAX_SKILL_LEVEL,                      //已经达到最高技能等级
	UPGRADE_SKILL_ERROR_NOT_ENOUGH_ROLE_LEVEL,       //角色等级不足   
	UPGRADE_SKILL_ERROR_NOT_ENOUGH_GOLD,                //升级技能所需的金币不足
	UPGRADE_SKILL_ERROR_NOT_ENOUGH_PVPCOIN,           //升级技能所需的PVP币不足
	UPGRADE_SKILL_ERROR_NOT_ENOUGH_DIAMOND,         //升级技能所需的钻石不足
	UPGRADE_SKILL_ERROR_NOT_ENOUGH_SKILL_POINT,      //升级技能所需的技能点不足
};

enum ESetSkillButtonError
{
	SET_SKILL_BUTTON_SUCCESS,	
	SET_SKILL_BUTTON_FAIL,
	SET_SKILL_BUTTON_NOT_SUCH_SKILL,	
};
		
}//GM
}//SKillSystem
}//GSLib


#endif
