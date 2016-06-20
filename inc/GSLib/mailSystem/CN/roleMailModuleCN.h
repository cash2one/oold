#ifndef __GSLIB_MAILSYSTEM_CN_ROLEMAILMODULECN_H__
#define __GSLIB_MAILSYSTEM_CN_ROLEMAILMODULECN_H__

#include <GSLib/playerSystem/CN/roleModuleCN.h>
#include <GSLib/mailSystem/mail.h>

namespace GSLib
{

namespace MailSystem
{

namespace CN
{
	class CRoleMailModuleCN : public GSLib::PlayerSystem::CN::CRoleModuleCN
	{
	public:
		CRoleMailModuleCN(GSLib::PlayerSystem::CN::CRoleCN* a_roleCN, EModuleType a_moduleType);
		virtual ~CRoleMailModuleCN();

		virtual void preInit(bool isFirst);
		virtual void postInit(bool isFirst);
		virtual void init(bool isFirst);
		virtual void initToClient();
		virtual void final();

		virtual void initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
		virtual void freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

		virtual void updateDataToDB();
		virtual void cbSelectTableData(BSLib::uint32 a_sessionID, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream);
		
		// 通知玩家 有新邮件
		bool		cbNewRoleMail(SMail *mail);

	private:
		void _onMsgMailSystemGM2CNReqUnreceivedMail(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
		void _onMsgMailSystemGM2CNNtfDelMail(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

	private:
		SRoleGuid m_roleGuid;
	};
}


}

}



#endif // __GSLIB_MAILSYSTEM_CN_ROLEMAILMODULECN_H__
