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
	LEARN_SKILL_ERROR_SUCCESS,                                       //ѧϰ���ܳɹ�
	LEARN_SKILL_ERROR_FAIL,                                              //ѧϰ����ʧ��
	LEARN_SKILL_ERROR_ALREADY_LEARN,                            //�����Ѿ�ѧϰ
	LEARN_SKILL_ERROR_INVALID_SKILLTPID,                        //�Ƿ�����ID
	LEARN_SKILL_ERROR_NOT_ENOUGH_LEVEL,                     //ѧϰ���������ɫ�ȼ�����
	LEARN_SKILL_ERROR_INCORRECT_ROLETPID,					//��ɫTPID����
	LEARN_SKILL_ERROR_NOT_ENOUGH_GOLD,                     //ѧϰ��������Ľ�Ҳ���
	LEARN_SKILL_ERROR_NOT_ENOUGH_PVPCOIN,                //ѧϰ���������PVP�Ҳ���
	LEARN_SKILL_ERROR_NOT_ENOUGH_DIAMOND,              //ѧϰ�����������ʯ����
	LEARN_SKILL_ERROR_NOT_ENOUGH_SKILL_POINT,           //ѧϰ��������ļ��ܵ㲻��
};

enum EUpgradeSkillError
{
	UPGRADE_SKILL_ERROR_SUCCESS,                                  //�������ܳɹ�
	UPGRADE_SKILL_ERROR_FAIL,                                         //��������ʧ��
	UPGRADE_SKILL_ERROR_NOT_LEARN,                             //�ü�����δѧϰ
	UPGRADE_SKILL_ERROR_INVALID_SKILLTPID,                   //�Ƿ�����ID
	UPGRADE_SKILL_ERROR_MAX_SKILL_LEVEL,                      //�Ѿ��ﵽ��߼��ܵȼ�
	UPGRADE_SKILL_ERROR_NOT_ENOUGH_ROLE_LEVEL,       //��ɫ�ȼ�����   
	UPGRADE_SKILL_ERROR_NOT_ENOUGH_GOLD,                //������������Ľ�Ҳ���
	UPGRADE_SKILL_ERROR_NOT_ENOUGH_PVPCOIN,           //�������������PVP�Ҳ���
	UPGRADE_SKILL_ERROR_NOT_ENOUGH_DIAMOND,         //���������������ʯ����
	UPGRADE_SKILL_ERROR_NOT_ENOUGH_SKILL_POINT,      //������������ļ��ܵ㲻��
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
