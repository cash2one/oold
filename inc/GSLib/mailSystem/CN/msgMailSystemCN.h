#ifndef msgMailSystemCN_h__
#define msgMailSystemCN_h__
#include <GSLib/serverType.h>
#include <GSLib/mailSystem/msgNumIDMailSystem.h>

namespace GSLib
{

	namespace MailSystem
	{

		const BSLib::uint32 msgIDMailSystemGM2CNReqUnreceivedMail =
			GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_MAILSYSTEM, EMSGID_MAILSYSTEM_GM2CN_REQ_UNRECEIVED_MAIL);
		class CMsgMailSystemGM2CNReqUnreceivedMail: public GFLib::CMessage
		{
		public:
			CMsgMailSystemGM2CNReqUnreceivedMail() : GFLib::CMessage(msgIDMailSystemGM2CNReqUnreceivedMail)
			{
			}

		protected:
			bool _serializeTo(BSLib::Utility::CStream& stream) const
			{
				return true;
			}

			bool _serializeFrom(BSLib::Utility::CStream& stream)
			{
				return true;
			}

		public:
			// 无消息体
		};

		const BSLib::uint32	msgIDMailSystemGM2CNNtfDelMail = 
			GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_MAILSYSTEM, EMSGID_MAILSYSTEM_GM2CN_NTF_DEL_MAIL);
		class CMsgMailSystemGM2CNNtfDelMail: public GFLib::CMessage
		{
		public:
			CMsgMailSystemGM2CNNtfDelMail() : GFLib::CMessage(msgIDMailSystemGM2CNNtfDelMail)
			{
			}

		protected:
			bool _serializeTo(BSLib::Utility::CStream& stream) const
			{	
				BSLib::uint32 size = m_mailIds.size();
				stream << size;
				for(BSLib::uint32 i = 0; i < size; i++){
					stream << m_mailIds[i];
				}

				return true;
			}

			bool _serializeFrom(BSLib::Utility::CStream& stream)
			{	
				BSLib::uint32 size = 0;
				stream >> size;
				for(BSLib::uint32 i = 0; i < size; i++){
					BSLib::uint64 mailId = 0;
					stream >> mailId;
					m_mailIds.push_back(mailId);
				}

				return true;
			}

		public:
			std::vector<BSLib::uint64> m_mailIds;
		};

	}
}

#endif // msgMailSystemCN_h__
