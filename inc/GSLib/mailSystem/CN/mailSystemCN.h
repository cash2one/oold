#ifndef __GSLIB_MAILSYSTEM_GM_MAILSYSTEMGM_H__
#define __GSLIB_MAILSYSTEM_GM_MAILSYSTEMGM_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>
#include <GSLib/mailSystem/mail.h>
#include <GSLib/dbSystem/keyTable.h>
#include <GSLib/dbSystem/keyIndexTable.h>

namespace GSLib
{

namespace MailSystem
{

namespace CN
{

class CMailSystemCN : public GSLib::DBSystem::CDBCommonSystem
					, BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::CCallback
{
public:
	CMailSystemCN();
	virtual ~CMailSystemCN();

	BSLIB_SINGLETON_DECLARE(CMailSystemCN);

	virtual BSLib::uint16 ICommonSystem_getFuncType() { return GSLib::EFUNCTYPE_MAILSYSTEM; }

	void update(BSLib::uint64 a_delayMilliseconds);

public:
	virtual bool _init();	// test
	virtual void _final();
	virtual bool ICommonSystem_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _ICommonSystem_startSystem();
	virtual void ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);


	

public:
	TMailContainerMap*	mailOpenBox(SRoleGuid &a_mailer);
	SMail*			mailOpen(SRoleGuid &a_mailer, BSLib::uint64 a_mailId);
	bool			mailDelete(SRoleGuid &a_mailer, BSLib::uint64 a_mailId);
	bool			mailSend(const std::string& a_sender, std::vector<SRoleGuid> &a_receiver, EMailType a_mailType, std::string &a_title,
							std::string &a_content, std::vector<BSLib::uint32> &a_types, std::vector<BSLib::uint32> &a_ids, std::vector<BSLib::uint32> &a_nums);
	bool			mailGetSelf(SRoleGuid& a_mailer, TMailContainerMap& a_container);	// 获取未发送的私人邮件

	SRoleGuid		getUniqueRoleGuid();

private:
	BSLib::uint64	_newMailId();	//产生唯一的id
	BSLib::uint64	_currentTime();
	SMail*			_createSelfMail(SelfMailst& a_st, bool a_save);

	SMail*			_createUniqueMail(const std::string& a_title, const std::string& a_content, const std::string& a_sender,
						BSLib::uint64 a_timeStamp, std::vector<BSLib::uint32> &a_types, std::vector<BSLib::uint32>& a_ids, std::vector<BSLib::uint32>& a_nums);

	bool			_notifyRoleNewMail(SRoleGuid &a_receiver, SMail *a_obj);	// 通知在线玩家的新邮件 
	bool			_notifySystemNewMail(SMail *a_obj);	// 推送给所有GM, 有新的系统邮件

	virtual bool	exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value);
	virtual bool	_cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, DBSystem::CKeyTablePtr& a_keyTable,
											EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
	virtual bool	_cbSelectKeyIndexTableData(const GSLib::SRoleKey& a_roleKey, DBSystem::CKeyIndexTablePtr& a_keyTable,
											EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);

	void			_dbUpdateRoleMail(SMail *mail);
	void			_dbDelRoleMail(SMail *mail);
	bool			_cbTimerSendSystemMailTest(BSLib::uint64, void* a_para);

private:
	TRoleMailContainerMap	m_outputBox;		// 发件箱
	BSLib::uint64			m_mailIdBase;		// 时间
	BSLib::uint32			m_mailIdSeed;		// 自增
	BSLib::uint8			m_serverNO;			// ServerID 的 number

	SRoleGuid				m_uniqueMailer;		// 全体邮件标示
	DBSystem::CKeyIndexTablePtr m_outputTablePtr;


	bool					m_gmReady;
	bool					m_dataReady;
	
};

}//GM

}//MailSystem

}//GSLib

#endif//__GSLIB_MAILSYSTEM_GM_MAILSYSTEMGM_H__

