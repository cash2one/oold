#ifndef mail_h__
#define mail_h__
#include <string>

namespace GSLib
{

namespace MailSystem
{

	enum EMailType
	{
		EMailTypeSelf	= 1, // 个人邮件
		EMailTypeSystem	= 2, // 系统邮件
		EMailTypeDeduct = 3, // 扣减邮件
	};

	struct SRoleGuid
	{	
		SRoleGuid(BSLib::uint64 account , BSLib::uint32 zone, BSLib::uint32 role)
			:m_accountId(account)
			,m_zoneId(zone)
			,m_roleIndex(role)
		{

		}

		SRoleGuid()
			:m_accountId(0)
			,m_zoneId(0)
			,m_roleIndex(0)
		{

		}

		SRoleGuid(const SRoleKey& roleKey)
		{
			m_accountId = roleKey.getAccountID();
			m_zoneId = roleKey.getZoneID();
			m_roleIndex = roleKey.getIndex();
		}

		SRoleGuid(const SRoleGuid& other)
		{
			m_accountId = other.m_accountId;
			m_zoneId = other.m_zoneId;
			m_roleIndex = other.m_roleIndex;
		}

		bool operator == (const SRoleGuid& other) const
		{
			return m_zoneId == other.m_zoneId 
				&& m_accountId == other.m_accountId
				&& m_roleIndex == other.m_roleIndex;
		}

		bool operator != (const SRoleGuid& other) const
		{
			return !(*this == other);
		}

		bool operator < (const SRoleGuid& other) const
		{
			if( m_zoneId < other.m_zoneId){
				return true;
			}	
			else if(m_zoneId == other.m_zoneId && m_accountId < other.m_accountId){
				return true;
			}		
			else if( m_zoneId == other.m_zoneId && m_accountId == other.m_accountId 
				&& m_roleIndex < other.m_roleIndex){
					return true;
			}		

			return false;
		}

		std::string getDBKey() const
		{
			std::string key;
			key.append((char*)&m_accountId, sizeof(m_accountId));
			key.append((char*)&m_zoneId, sizeof(m_zoneId));
			key.append((char*)&m_roleIndex, sizeof(m_roleIndex));
			return key;
		}

		bool serializeTo(BSLib::Utility::CStream& stream) const 
		{
			stream << m_accountId;
			stream << m_zoneId;
			stream << m_roleIndex;
			return true;

		}

		 bool serializeFrom(BSLib::Utility::CStream& stream)
		{	
			stream >> m_accountId;
			stream >> m_zoneId;
			stream >> m_roleIndex;
			return true;
		}

		BSLib::uint64 m_accountId;
		BSLib::uint16 m_zoneId;
		BSLib::uint32 m_roleIndex;
	};



	struct SelfMailst
	{
		SelfMailst(SRoleGuid& a_receiver, BSLib::uint32 a_mailType, BSLib::uint64 a_uniqueMail, BSLib::uint64 a_timeStamp)
		{
			m_receiver = a_receiver;
			m_mailType = a_mailType;
			m_uniqueMail = a_uniqueMail;
			m_timeStamp = a_timeStamp;
		}

		SelfMailst(SRoleGuid& a_receiver, BSLib::uint32 a_mailType, BSLib::uint64 a_uniqueMail, BSLib::uint64 a_timeStamp,
			std::string a_title, std::string a_content, std::string a_sender, 
			std::vector<BSLib::uint32>& a_types, std::vector<BSLib::uint32>& a_ids, std::vector<BSLib::uint32>& a_nums)
		{
			m_receiver = a_receiver;
			m_mailType = a_mailType;
			m_uniqueMail = a_uniqueMail;
			m_timeStamp = a_timeStamp;

			m_title = a_title;
			m_content = a_content;
			m_sender = a_sender;

			m_types = a_types;
			m_ids = a_ids;
			m_nums = a_nums;
		}

		SelfMailst()
		{
			m_mailType = 0;
			m_uniqueMail = 0;
			m_timeStamp = 0;
		}

		SRoleGuid m_receiver;
		BSLib::uint32 m_mailType;
		BSLib::uint64 m_uniqueMail;
		BSLib::uint64 m_timeStamp;
		std::string	 m_title;
		std::string	 m_content;
		std::string  m_sender;
		std::vector<BSLib::uint32> m_types;
		std::vector<BSLib::uint32> m_ids;
		std::vector<BSLib::uint32> m_nums;
	};


	struct SMail
		: public SRoleGuid 
	{

		SMail()
			:m_mailId(0)
			,m_mailType(EMailTypeSelf)
			,m_systemMail(0)
			,m_isRead(0)
			,m_isGet(0)
			,m_timeStamp(0)
		{

		}

		SMail(const SRoleGuid &other)
			:SRoleGuid(other)
			,m_mailId(0)
			,m_mailType(EMailTypeSelf)
			,m_systemMail(0)
			,m_isRead(0)
			,m_isGet(0)
			,m_timeStamp(0)
		{

		}

		virtual bool serializeTo(BSLib::Utility::CStream& stream) const 
		{	
			SRoleGuid::serializeTo(stream);
			stream << m_mailId;
			stream << m_mailType;
			stream << m_systemMail;
			stream << m_isRead;
			stream << m_isGet;
			stream << m_timeStamp;
			stream << m_title;
			stream << m_content;
			stream << m_sender;
			stream << m_types;
			stream << m_ids;
			stream << m_nums;
			return true;
			
		}

		virtual bool serializeFrom(BSLib::Utility::CStream& stream)
		{	
			SRoleGuid::serializeFrom(stream);
			stream >> m_mailId;
			stream >> m_mailType;
			stream >> m_systemMail;
			stream >> m_isRead;
			stream >> m_isGet;
			stream >> m_timeStamp;
			stream >> m_title;
			stream >> m_content;
			stream >> m_sender;
			stream >> m_types;
			stream >> m_ids;
			stream >> m_nums;
			return true;
		}

		std::string getIndexKey() const
		{
			std::string key;
			key.append((char*)&m_mailId, sizeof(m_mailId));
			return key;
		}

		BSLib::uint64				m_mailId;		// 邮件id
		BSLib::uint32				m_mailType;		// 1:个人邮件， 2：系统邮件
		BSLib::uint64				m_systemMail;	// 是否为系统全体邮件,是则邮件实体存在系统邮件里, 系统邮件id
		BSLib::uint32				m_isRead;		// 是否已读  0：未读， 1：已读
		BSLib::uint32				m_isGet;		// 附件是否被领取, 0: 未领取,  1:已领取
		BSLib::uint64				m_timeStamp;	// 发信时间

		std::string					m_title;		// 标题
		std::string					m_content;		// 内容
		std::string					m_sender;		// 发送者, 显示之用
		std::vector<BSLib::uint32>	m_types;		// item 类型
		std::vector<BSLib::uint32>	m_ids;			// 附件item id列表
		std::vector<BSLib::uint32>	m_nums;			// 附件item num
	};

	
	typedef std::map<BSLib::uint64, SMail *> TMailContainerMap;
	typedef std::map<SRoleGuid, TMailContainerMap *> TRoleMailContainerMap;


#define CREATE_NEW_MAILID(server_type, server_id, time, index) \
	( ((BSLib::uint64(server_type) << 60) & 0xF000000000000000) | ((BSLib::uint64(server_id) << 52) & 0x0FF0000000000000) | ((BSLib::uint64(time) << 20) & 0x000FFFFFFFF00000) | (BSLib::uint64(index) & 0x00000000000FFFFF))
	
}
}

#endif // mail_h__
