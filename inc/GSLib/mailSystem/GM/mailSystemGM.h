#ifndef __GSLIB_MAILSYSTEM_GM_MAILSYSTEMGM_H__
#define __GSLIB_MAILSYSTEM_GM_MAILSYSTEMGM_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>
#include <GSLib/mailSystem/mail.h>
#include <GSLib/dbSystem/keyTable.h>
#include <BSLib/database/dbTableRow.h>

namespace GSLib
{

namespace MailSystem
{

namespace GM
{


class CMailSystemGM : public GSLib::DBSystem::CDBCommonSystem
	, BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::CCallback
{
public:
	CMailSystemGM();
	virtual ~CMailSystemGM();

	BSLIB_SINGLETON_DECLARE(CMailSystemGM);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_MAILSYSTEM; }

	void update(BSLib::uint64 a_delayMilliseconds);

public:
	virtual bool _init();	// test
	virtual void _final();
	virtual bool _loadGameConfig(const std::string& a_configPath);
	virtual bool _initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void _cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void _cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);


	

public:
	TMailContainerMap*	
					mailOpenBox(SRoleGuid &a_mailer);
	SMail*			mailOpen(SRoleGuid &a_mailer, BSLib::uint64 a_mailId);
	bool			mailSend(const std::string& a_sender, std::vector<SRoleGuid> &a_receiver, const std::string &a_title,			// ���͸����˵�ϵͳ�ʼ�
							const std::string &a_content, std::vector<BSLib::uint32> &a_types, std::vector<BSLib::uint32> &a_ids, std::vector<BSLib::uint32> &a_nums);
	bool			mailGetSystem(SRoleGuid& a_mailer, BSLib::uint64 a_roleLastuniqueId, TMailContainerMap& a_container); // ��ȡ���δ��ȡ��ȫ���ʼ�
	SRoleGuid		getUniqueRoleGuid();
	BSLib::uint64	getLastestSystemMailId();

private:
	BSLib::uint64	_newMailId();	//����Ψһ��id
	BSLib::uint64	_currentTime();
	SMail*			_createSelfMail(SelfMailst &a_st);

	bool			_notifyRoleNewMail(SRoleGuid &a_receiver, SMail *a_obj);	// ֪ͨ������ҵ����ʼ�
	std::vector<SRoleGuid>&	
					_getOnlineRoles();	
	BSLib::uint64	_getMaxSystemMailId();

	void			_onMsgMailSystemCN2GMNtfNewSystemMail(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	virtual bool exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value);

	virtual bool _cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
	virtual bool _cbSelectKeyIndexTableData(const GSLib::SRoleKey& a_roleKey, DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
	
	bool		_cbTimerSendSystemMailTest(BSLib::uint64, void* a_para);

private:
	TRoleMailContainerMap	m_systemOutputBox;	// ϵͳ�ʼ�, ��ʼ����ʱ���db��ȡ, ������ϵͳ�ʼ���center����, ������db
	BSLib::uint64			m_mailIdBase;		// ʱ��
	BSLib::uint32			m_mailIdSeed;		// ����
	BSLib::uint8			m_serverNO;			// ServerID �� number

	BSLib::uint64			m_lastestSystemMailId;	// ���µ�ȫ���ʼ�id	
	std::vector<SRoleGuid>	m_totaoRoles;
	SRoleGuid				m_uniqueMailer;		// ȫ���ʼ���ɫ
	
};

}//GM

}//MailSystem

}//GSLib

#endif//__GSLIB_MAILSYSTEM_GM_MAILSYSTEMGM_H__

