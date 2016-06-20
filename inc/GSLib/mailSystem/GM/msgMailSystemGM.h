//////////////////////////////////////////////////////////////////////
//	created:	2014/10/09
//	filename:   GSLib\mailSystem\GM\msgMailSystemGM.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_MAILSYSTEM_MSGMAILSYSTEMGM_H__
#define __GSLIB_MAILSYSTEM_MSGMAILSYSTEMGM_H__

#include <GSLib/mailSystem/msgNumIDMailSystem.h>

namespace GSLib
{

namespace MailSystem
{	
	const BSLib::uint32 msgIDMailSystemGC2GMReqGetAttach = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_MAILSYSTEM, EMSGID_MAILSYSTEM_GC2GM_REQ_GET_ATTACH);
	class CMsgMailSystemGC2GMReqGetAttach: public GFLib::CMessage
	{
	public:
		CMsgMailSystemGC2GMReqGetAttach() : GFLib::CMessage(msgIDMailSystemGC2GMReqGetAttach)
		{
		}

	protected:

		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{	
			BSLib::uint32 size = 0;
			stream >> size;
			for(BSLib::uint32 i = 0; i < size; i++)
			{
				BSLib::uint64 temp = 0;
				stream >> temp;
				mail_ids.push_back(temp);
			}

			return true;
		}

	public:
		std::vector<BSLib::uint64> mail_ids;
	};


	const BSLib::uint32 MsgIDMailSystemGC2GMReqGetOpMail = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_MAILSYSTEM, EMSGID_MAILSYSTEM_GC2GM_REQ_OPERATE_MAIL);
	class CMsgMailSystemGC2GMReqOperateMail: public GFLib::CMessage
	{
	public:
		CMsgMailSystemGC2GMReqOperateMail() : GFLib::CMessage(MsgIDMailSystemGC2GMReqGetOpMail)
		{
		}

	protected:

		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{	
			stream >> op_type;
			stream >> mail_count;
			for(BSLib::uint32 i = 0; i < mail_count; i++)
			{	
				BSLib::uint64 temp = 0;
				stream >> temp;
				mail_ids.push_back(temp);
			}

			return true;
		}
		

	public:
		BSLib::uint32 op_type;
		BSLib::uint32 mail_count;
		std::vector<BSLib::uint64> mail_ids;
	};


	const BSLib::uint32 msgIDMailSystemCN2GMAckUnreceivedMail = 
		GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_MAILSYSTEM, EMSGID_MAILSYSTEM_CN2GM_ACK_UNRECEIVED_MAIL);
	class CMsgMailSystemCN2GMAckUnreceivedMail: public GFLib::CMessage
	{
	public:
		CMsgMailSystemCN2GMAckUnreceivedMail() : GFLib::CMessage(msgIDMailSystemCN2GMAckUnreceivedMail)
			,m_mailCount(0)
		{
		}

	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{	
			stream << m_mailCount;
			stream << m_MailStream;

			return true;
		}

		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{	
			stream >> m_mailCount;
			stream >> m_MailStream;

			return true;
		}

	public:
		BSLib::uint32 m_type;
		BSLib::uint32 m_mailCount;
		BSLib::Utility::CStream m_MailStream;
	};


	const BSLib::uint32 msgIDMailSystemCN2GMNtfNewSystemMail = 
		GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_MAILSYSTEM, EMSGID_MAILSYSTEM_CN2GM_NTF_NEW_SYSTEM_MAIL);
	class CMsgMailSystemCN2GMNtfNewSystemMail: public GFLib::CMessage
	{
	public:
		CMsgMailSystemCN2GMNtfNewSystemMail() : GFLib::CMessage(msgIDMailSystemCN2GMNtfNewSystemMail)
		{
		}

	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{	
			stream << m_MailStream;

			return true;
		}

		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{	
			stream >> m_MailStream;
			return true;
		}

	public:
		BSLib::Utility::CStream m_MailStream;
	};


	const BSLib::uint32 msgIDMailSystemCN2GMNtfNewRoleMail = 
		GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_MAILSYSTEM, EMSGID_MAILSYSTEM_CM2GM_NTF_NEW_ROLE_MAIL);
	class CMsgMailSystemCN2GMNtfNewRoleMail: public GFLib::CMessage
	{
	public:
		CMsgMailSystemCN2GMNtfNewRoleMail() : GFLib::CMessage(msgIDMailSystemCN2GMNtfNewRoleMail)
			,m_mailCount(0)
		{
		}

	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{	
			stream << m_mailCount;
			stream << m_MailStream;

			return true;
		}

		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{	
			stream >> m_mailCount;
			stream >> m_MailStream;

			return true;
		}

	public:
		BSLib::uint32 m_mailCount;
		BSLib::Utility::CStream m_MailStream;
	};


}//MailSystem

}//GSLib

#endif//__GSLIB_MAILSYSTEM_MSGMAILSYSTEMGM_H__
