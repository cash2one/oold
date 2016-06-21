#ifndef __GSLIB_ACHIEVESYSTEM_BASEDEF_H__
#define __GSLIB_ACHIEVESYSTEM_BASEDEF_H__

typedef BSLib::uint32 AchieveID;
enum EAchieveType
{
    ACHIEVE_INVALID = 0,
    ACHIEVE_LEVEL = 1,		    //�ȼ��ɾ�
    ACHIEVE_COMBAT = 2,         //ս�����ɾ�
    ACHIEVE_KILL_BOSS = 3,		//��ɱBOSS�ɾ�	
    ACHIEVE_PASS_INSTANCE = 4,  //ͨ�ظ����ɾ�	
    ACHIEVE_PVP = 5,			//PVP�ɾ�	
    ACHIEVE_DICE = 6,			//���ӳɾ�
    ACHIEVE_PASS_STAGE = 7,	    //�������سɾ�
    ACHIEVE_EQUIP = 8,	        //װ���ɾ�
    ACHIEVE_GEM = 9,	        //��ʯ�ɾ�
    ACHIEVE_SKILL = 10,	        //���ܳɾ�
    ACHIEVE_PET = 11,	        //�Ż��ɾ�
    ACHIEVE_CHARGEPAY = 12,    	//��ֵ���ѳɾ�
};

enum ESubAchieveType
{
    SUB_ACHIEVE_INVALID = 0,
    SUB_ACHIEVE_LEVEL = 100,		    //�ȼ��ӳɾ�
    SUB_ACHIEVE_COMBAT = 200,           //ս�����ӳɾ�
    SUB_ACHIEVE_KILL_BOSS = 300,		//��ɱBOSS�ӳɾ�	
    SUB_ACHIEVE_PASS_INSTANCE = 400,    //ͨ�ظ����ӳɾ�	
    SUB_ACHIEVE_PVP_WINCOUNT = 500,			    //PVP��������ʤ�ɾ� ʧ�����0	
    SUB_ACHIEVE_PVP_RANK = 501,			//PVP���������гɾ�	
    SUB_ACHIEVE_DICE = 600,			    //�����ӳɾ�
    SUB_ACHIEVE_PASS_STAGE = 700,	    //���������ӳɾ�
    SUB_ACHIEVE_EQUIP_COLOR = 800,	    //װ���ӳɾ�  ��װ
    SUB_ACHIEVE_EQUIP_ONE_LEVEL = 801,	//װ���ӳɾ� һ���ռ� 
    SUB_ACHIEVE_EQUIP_FOUR_LEVEL = 802,	//װ���ӳɾ� �ļ��ռ� 
    SUB_ACHIEVE_EQUIP_SIX_LEVEL = 803,	//װ���ӳɾ� �����ռ� 

    SUB_ACHIEVE_GEM = 900,	            //��ʯ�ӳɾ�
    SUB_ACHIEVE_SKILL = 1000,	        //�����ӳɾ� ����

    SUB_ACHIEVE_PET_COLOR_PURPLE = 1100,//�Ż��ӳɾ� ��ɫ�ż�����
    SUB_ACHIEVE_PET_COLOR_YELLOW = 1101,//�Ż��ӳɾ� ��ɫ�ż�����
    SUB_ACHIEVE_PET_COLOR_STARLEVEL = 1102,//�Ż��ӳɾ� 5�Ǽ��ż�����

    SUB_ACHIEVE_VIPLEVEL = 1200,    	//��ֵ�����ӳɾ� vip�ȼ�
    SUB_ACHIEVE_CHARGE = 1201,    	    //��ֵ�����ӳɾ� ��ֵ��ʯ����
    SUB_ACHIEVE_BUY_VIALITY = 1202,    	//��ֵ�����ӳɾ� ������������
};

enum EAchieveStatus
{
    ACHIEVE_STATUS_DOING,     //������
    EACHIEVE_STATUS_FINISHED, //�����
    ACHIEVE_STATUS_PRIZED,    //����ȡ����
};

#endif//__GSLIB_ACHIEVESYSTEM_BASEDEF_H__
