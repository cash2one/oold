//////////////////////////////////////////////////////////////////////
//	created:	2014/07/29
//	filename: 	GSLib\playerSystem\GM\role.h
//	author:		zhangping
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PLAYERSYSTEM_GM_ROLE_H__
#define __GSLIB_PLAYERSYSTEM_GM_ROLE_H__

#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonSystem.h>

namespace GSLib
{

namespace PlayerSystem
{

namespace GM
{

class CRole
{
public:
	CRole();
	CRole(BSLib::uint64 a_roleID,std::string a_roldName);
	virtual ~CRole();

public:
	virtual bool _init();
	virtual void _final();
	
public:
	void inline setRoleID(BSLib::uint64 a_RoleID){ m_nRoleId = a_RoleID;}
	void inline setRoleName(std::string a_strRoleName){ m_strRoleName = a_strRoleName;}

	BSLib::uint64 inline getRoleID(){ return m_nRoleId;}
	std::string inline getRoleName(){ return m_strRoleName;}

	//��ɫ��������(һ������)
	enum CHAR_ATTR_LEVEL1
	{
		CATTR_LEVEL1_STR			=0, //����  1����=4������
		CATTR_LEVEL1_CON			=1,	//����  1����=100����ֵ+4�������+4���ܷ���
		CATTR_LEVEL1_INT			=2,	//����  1����=4���ܹ���
		CATTR_LEVEL1_DEX			=3,	//����  1����=4����+4����

		CATTR_LEVEL1_NUMBER, //��ɫ������������
	};



	//��ɫ��������
	enum CHAR_ATTR_LEVEL2
	{
		CATTR_LEVEL2_ATTACKRATE_P =0,	//������
		CATTR_LEVEL2_DEFENCE_P,			//�������
		CATTR_LEVEL2_ATTACKRATE_M,		//���ܹ���
		CATTR_LEVEL2_DEFENCE_M,			//���ܷ���

		CATTR_LEVEL2_ATTCAK_CRIT,       //����
		CATTR_LEVEL2_DEFENCE_CRIT,      //��������
		CATTR_LEVEL2_DAMAGE_CRIT,       //�����˺�

		CATTR_LEVEL2_DAMAGE_REDUCE,     //�����˺�

		CATTR_LEVEL2_HIT,				//���л���
		CATTR_LEVEL2_MISS,				//���ܻ���

		CATTR_LEVEL2_MAXHP,				//HP����
		CATTR_LEVEL2_MAXMP,				//MP����
		CATTR_LEVEL2_RESTOREHP,			//HP�ظ�
		CATTR_LEVEL2_RESTOREMP,			//MP�ظ�


		CATTR_LEVEL2_PHOTONFORCE ,		//������

		CATTR_LEVEL2_NUMBER,			//������������

	};
	// ��ɫ����
public:
    // һ������
	
	// ��������

private:
	BSLib::uint64 m_nRoleId;
	std::string   m_strRoleName;

};

}//GM

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_GM_ROLE_H__
