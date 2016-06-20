//////////////////////////////////////////////////////////////////////
//	created:	2014/10/09
//	filename: 	GSLib\mailSystem\msgMailSystemGC.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_MAILSYSTEM_MSGMAILSYSTEMGC_H__
#define __GSLIB_MAILSYSTEM_MSGMAILSYSTEMGC_H__

#include <GSLib/mailSystem/msgNumIDMailSystem.h>

namespace GSLib
{

namespace MailSystem
{	
	const BSLib::uint32 msgIDMailSystemGM2GCNtfPushMail = 
		GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_MAILSYSTEM, EMSGID_MAILSYSTEM_GM2GC_NTF_PUSH_MAIL);
	class CMsgMailSystemGM2GCAckPushMail: public GFLib::CMessage
	{
	public:
		CMsgMailSystemGM2GCAckPushMail() : GFLib::CMessage(msgIDMailSystemGM2GCNtfPushMail)
			,m_mailCount(0)
		{

		}

	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{	
			stream << m_type;
			stream << m_mailCount;
			stream << m_stream;
			return true;
		}

	public:
		BSLib::uint32 m_type;
		BSLib::uint32 m_mailCount;
		BSLib::Utility::CStream m_stream;
	};

	const BSLib::uint32 msgIDMailSystemGM2GCAckGetAttach = 
		GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_MAILSYSTEM, EMSGID_MAILSYSTEM_GM2GC_ACK_GET_ATTACH);
	class CMsgMailSystemGM2GCAckGetAttach: public GFLib::CMessage
	{
	public:
		CMsgMailSystemGM2GCAckGetAttach() : GFLib::CMessage(msgIDMailSystemGM2GCAckGetAttach)
		{
		}

	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream << m_mailCount;
			stream << m_mail_stream;
			stream << m_bonus_count;
			stream << m_bonus_stream;
			return true;
		}

	public:
		BSLib::uint32 m_mailCount;
		BSLib::uint32 m_bonus_count;
		BSLib::Utility::CStream m_mail_stream;
		BSLib::Utility::CStream m_bonus_stream;
	};

	const BSLib::uint32 msgIdMailSystemGM2GCAckOPMail = 
		GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_MAILSYSTEM, EMSGID_MAILSYSTEM_GM2GC_ACK_OPERATE_MAIL);
	class CMsgMailSystemGM2GCAckOperateMail: public GFLib::CMessage
	{
	public:
		CMsgMailSystemGM2GCAckOperateMail() : GFLib::CMessage(msgIdMailSystemGM2GCAckOPMail)
		{
			m_op_type = 0;
		}

	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{	
			stream << m_op_type;
			stream << m_mailCount;
			stream << m_stream;
			return true;
		}

	public:
		BSLib::uint32 m_op_type;
		BSLib::uint32 m_mailCount;
		BSLib::Utility::CStream m_stream;
	};
	

}//MailSystem

}//GSLib

#endif//__GSLIB_MAILSYSTEM_MSGMAILSYSTEMGC_H__
