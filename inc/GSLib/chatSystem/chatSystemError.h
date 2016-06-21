#ifndef __GSLIB_CHATSYSTEM_CHATSYSTEMERROR_H__
#define __GSLIB_CHATSYSTEM_CHATSYSTEMERROR_H__

#include <GFLib/commonServer/message/message.h>
#include <GSLib/funType.h>
#include <GSLib/serverType.h>
#include <GSLib/baseDef.h>

namespace GSLib
{

namespace ChatSystem
{

enum EChatResult
{
	CHAT_RESULT_SUCCESS,									//�ɹ�
	CHAT_RESULT_FAIL,										//ʧ��
	CHAT_RESULT_NOT_ONLINE,									//������Ҳ�����
	CHAT_RESULT_CAN_NOT_TALK_TO_SELF,						//�޷�˽���Լ�
	CHAT_RESULT_NOT_ENOUGH_ITEM,							//û������������Ʒ
	CHAT_RESULT_TALK_TOO_FREQUENTLY,						//���Թ���Ƶ��
	CHAT_RESULT_NOT_IN_MAIN_CITY,							//��������
	CHAT_RESULT_NOT_FRIEND,									//�Ǻ���
};


}//ChatSystem

}//GSLib

#endif//__GSLIB_CHATSYSTEM_MSGNUMIDCHATSYSTEM_H__

