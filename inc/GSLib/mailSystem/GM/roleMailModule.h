#ifndef __GSLIB_MAILSYSTEM_GM_ROLEMAILMODULE_H__
#define __GSLIB_MAILSYSTEM_GM_ROLEMAILMODULE_H__

#include <GSLib/playerSystem/GM/roleModuleGM.h>
#include <GSLib/mailSystem/mail.h>
#include <BSLib/database/dbTableRow.h>
#include <GSLib/mailSystem/DB/tableMailDB.h>

namespace GSLib
{

namespace MailSystem
{

namespace GM
{


	class CRoleMailModule : public GSLib::PlayerSystem::GM::CRoleModuleGM
		, BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::CCallback
{
public:
	CRoleMailModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType);
	virtual ~CRoleMailModule();

	virtual void preInit(bool isFirst);
	virtual void postInit(bool isFirst);
	virtual void initToClient();
	virtual void final();

	virtual void initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual void freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	virtual void updateDataToDB();
	virtual bool cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
	virtual bool cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
	virtual bool exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value);


	void onlinePushMail();						// 上线推送
	bool cbNewMailNotify(SMail* SMail);			// 新邮件
	SRoleGuid getRoleGuid();

	SMail*			mailOpen(BSLib::uint64 a_mailId);
	bool			mailRead(BSLib::uint64 a_mailId);
	bool			mailDelete(BSLib::uint64 a_mailId);
	bool			mailGetAttach(BSLib::uint64 a_mailId, std::vector<BSLib::uint32> &a_ids, std::vector<BSLib::uint32> &a_nums); 

private:
	void _onMsgMailSystemGC2GMReqGetAttach(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg); // todo 奖励
	void _onMsgMailSystemGC2GMReqOperateMail(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	void _onMsgMailSystemCN2GMAckUnreceivedMail(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgMailSystemCN2GMNtfNewRoleMail(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	bool _GM2CNReqUnreceivedMail();	// 向GC发送未接收的个人邮件
	bool _GM2CNReqDelMail(std::vector<BSLib::uint64> & a_mailIds);	// 请求删除已获得的个人邮件

	bool _serializeTo(const SMail* a_mail, BSLib::Utility::CStream& a_stream);
	bool _checkOneKeyDel(SMail *a_mail);	// 检测是否可一键删除
	BSLib::uint64 _getLeftTime(BSLib::uint32 a_type, BSLib::uint64 a_timeStamp);

	bool _mergeContainer(std::vector<BSLib::uint32>& a_fromIds, std::vector<BSLib::uint32>& a_fromNums,
		std::vector<BSLib::uint32>& a_toIds, std::vector<BSLib::uint32>& a_toNums);

	void _dbUpdateRoleMailConfig();
	void _dbUpdateRoleMail(SMail *mail);
	void _dbDelRoleMail(SMail *mail);

	void _onDeductMail(SMail * mail); 

	void _onDelExpiredMail();

private:
	TMailContainerMap	m_inputBox;			// 个人收件箱
	SRoleGuid			m_roleGuid;			// 本角色

	// db 相关
	EDBTableID			m_tableId;			// 当前加载的table id
	GSLib::DBSystem::CKeyTablePtr				m_mailConfigTablePtr;
	GSLib::MailSystem::DB::SRoleMailConfigData	m_roleMailConfig;
	GSLib::DBSystem::CKeyIndexTablePtr			m_inputBoxTablePtr;
};

}//GM

}//MailSystem

}//GSLib

#endif//__GSLIB_MAILSYSTEM_GM_ROLEMAILMODULE_H__
