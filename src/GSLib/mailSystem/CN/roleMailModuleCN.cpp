#include <GSLib/mailSystem/CN/roleMailModuleCN.h>
#include <GSLib/mailSystem/CN/msgMailSystemCN.h>
#include <GSLib/playerSystem/CN/playerCN.h>
#include <GSLib/mailSystem/CN/mailSystemCN.h>
#include <GSLib/mailSystem/GM/msgMailSystemGM.h>

namespace GSLib
{
namespace MailSystem
{

namespace CN
{

	CRoleMailModuleCN::CRoleMailModuleCN(GSLib::PlayerSystem::CN::CRoleCN* a_roleCN, EModuleType a_moduleType)
		:GSLib::PlayerSystem::CN::CRoleModuleCN(a_roleCN, a_moduleType)
	{

	}

	CRoleMailModuleCN::~CRoleMailModuleCN()
	{

	}

	void CRoleMailModuleCN::preInit(bool isFirst)
	{
		using namespace GSLib::PlayerSystem::CN;
		CRoleCN* roleCN = getRoleCN();
		CPlayerCN *playerCN = roleCN->getPlayerCN();
		// 初始化本角色guid
		m_roleGuid.m_accountId = playerCN->getAccountID();
		m_roleGuid.m_zoneId = playerCN->getZoneID();
		m_roleGuid.m_roleIndex = roleCN->getRoleIndex();
	}

	void CRoleMailModuleCN::postInit(bool isFirst)
	{

	}

	void CRoleMailModuleCN::initToClient()
	{

	}

	void CRoleMailModuleCN::init(bool isFirst)
	{

	}

	void CRoleMailModuleCN::final()
	{

	}

	void CRoleMailModuleCN::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
	{
		BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDMailSystemGM2CNReqUnreceivedMail, &BSLib::Framework::CreateCMessage<CMsgMailSystemGM2CNReqUnreceivedMail>);
		GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDMailSystemGM2CNReqUnreceivedMail, &CRoleMailModuleCN::_onMsgMailSystemGM2CNReqUnreceivedMail, this);

		BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDMailSystemGM2CNNtfDelMail, &BSLib::Framework::CreateCMessage<CMsgMailSystemGM2CNNtfDelMail>);
		GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDMailSystemGM2CNNtfDelMail, &CRoleMailModuleCN::_onMsgMailSystemGM2CNNtfDelMail, this);
	}

	void CRoleMailModuleCN::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
	{
		a_msgExecMgr->delMsgExecPtr(msgIDMailSystemGM2CNReqUnreceivedMail);
		a_msgExecMgr->delMsgExecPtr(msgIDMailSystemGM2CNNtfDelMail);
	}

	void CRoleMailModuleCN::updateDataToDB()
	{

	}

	void CRoleMailModuleCN::cbSelectTableData(BSLib::uint32 a_sessionID, EDBTableID a_tableID, BSLib::Utility::CStream& a_stream)
	{

	}

	void CRoleMailModuleCN::_onMsgMailSystemGM2CNReqUnreceivedMail(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
	{	
		TMailContainerMap mailContainer;
		CMsgMailSystemCN2GMAckUnreceivedMail ack;
		if(CMailSystemCN::singleton().mailGetSelf(m_roleGuid, mailContainer))
		{
			for(TMailContainerMap::iterator it = mailContainer.begin(); it != mailContainer.end(); ++it){
				SMail *mail = it->second;
				mail->serializeTo(ack.m_MailStream);
				ack.m_mailCount++;
			}
		}

		sendMsgToGameServer(ack);
	}

	void CRoleMailModuleCN::_onMsgMailSystemGM2CNNtfDelMail(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
	{
		CMsgMailSystemGM2CNNtfDelMail *req = (CMsgMailSystemGM2CNNtfDelMail *)a_msg;
		for(BSLib::uint32 i = 0; i < req->m_mailIds.size(); i++){
			CMailSystemCN::singleton().mailDelete(m_roleGuid, req->m_mailIds[i]);
		}
	}

	bool CRoleMailModuleCN::cbNewRoleMail(SMail *mail)
	{	
		CMsgMailSystemCN2GMNtfNewRoleMail ack;
		mail->serializeTo(ack.m_MailStream);
		ack.m_mailCount = 1;
		return sendMsgToGameServer(ack);	
	}
}


}
}