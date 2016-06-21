#ifndef __GFLIB_COMMONSERVER_MESSAGE_MSGLABEL_H__
#define __GFLIB_COMMONSERVER_MESSAGE_MSGLABEL_H__

#include <BSLib/framework/message/msgLabel.h>
#include <GFLib/commonServer/baseDef.h>

namespace GFLib
{

struct GFLIB_COMMONSERVER_API SNetMsgLabel : public BSLib::Framework::SMsgLabel 
{
public:
	SServerID m_serverIDFrome;
	SServerID m_serverIDSender;
	GFLib::StubID m_stubIDsender;
	SServerID m_serverIDTo;
	SAccountKey m_acountKey;

	SNetMsgLabel() : BSLib::Framework::SMsgLabel(sizeof(SNetMsgLabel))
	{
		m_serverIDFrome = INVALID_SERVERID;
		m_serverIDSender = INVALID_SERVERID;
		m_stubIDsender = INVALID_STUBID;
		m_serverIDTo = INVALID_SERVERID;
		m_labelType = BSLib::Framework::ELABELTYPE_NET;
	}
};

}//GFLib

#endif//__GFLIB_COMMONSERVER_MESSAGE_MSGLABEL_H__



