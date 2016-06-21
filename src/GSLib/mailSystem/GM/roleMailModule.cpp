#include <GSLib/mailSystem/GM/roleMailModule.h>
#include <GSLib/mailSystem/msgMailSystem.h>
#include <GSLib/tracer.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/playerSystem/GM/playerGM.h>
#include <GSLib/mailSystem/DB/tableMailDB.h>
#include <GSLib/mailSystem/GM/mailSystemGM.h>
#include <GSLib/playerSystem/GM/playerGM.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <map>
#include <GSLib/prizeSystem/GM/rolePrizeModule.h>


namespace GSLib
{

namespace MailSystem
{

namespace GM
{

CRoleMailModule::CRoleMailModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType)
:  GSLib::PlayerSystem::GM::CRoleModuleGM(a_roleGM, a_moduleType)
{
	m_tableId = EDBTABLEID_NULL;
}

CRoleMailModule::~CRoleMailModule()
{
	;
}

void CRoleMailModule::preInit(bool isFirst)
{	
	using namespace GSLib::PlayerSystem::GM;
	CRoleGM* roleGM = getRoleGM();
	CPlayerGM *playerGm = roleGM->getPlayerGM();
	// 初始化本角色guid
	m_roleGuid.m_accountId = playerGm->getAccountID();
	m_roleGuid.m_zoneId = playerGm->getZoneID();
	m_roleGuid.m_roleIndex = roleGM->getRoleIndex();
	
	CMailSystemGM& mailSystem = CMailSystemGM::singleton();
	// 用于第一次保存数据用..
	m_roleMailConfig.m_accountID = m_roleGuid.m_accountId;
	m_roleMailConfig.m_zoneID = m_roleGuid.m_zoneId;
	m_roleMailConfig.m_roleIndex = m_roleGuid.m_roleIndex;
	// 第一次初始化...
	if(isFirst){
		m_roleMailConfig.m_lastestSystemMailID = mailSystem.getLastestSystemMailId();
	}
	
	// 个人邮件需要向center请求
// 	TMailContainerMap self_container;
// 	if(mail_system.mailGetSelf(m_roleGuid, self_container))
// 	{
// 		m_inputBox.insert(self_container.begin(), self_container.end());
// 	}
	
	// todo 保存
}

void CRoleMailModule::postInit(bool isFirst)
{

}

void CRoleMailModule::initToClient()
{	
	// 加载发件箱中全体邮件
	CMailSystemGM& mailSystem = CMailSystemGM::singleton();
	TMailContainerMap unique_container;
	if(mailSystem.mailGetSystem(m_roleGuid, m_roleMailConfig.m_lastestSystemMailID, unique_container))
	{
		for(TMailContainerMap::iterator it = unique_container.begin(); it != unique_container.end(); ++it){
			SMail *newMail = it->second;
			TMailContainerMap::iterator find_it = m_inputBox.find(newMail->m_mailId);
			if( find_it != m_inputBox.end()){
				delete newMail;
				continue;
			}
			m_inputBox.insert(std::make_pair(newMail->m_mailId, newMail));
			_dbUpdateRoleMail(newMail);
		}

	}
	m_roleMailConfig.m_lastestSystemMailID = mailSystem.getLastestSystemMailId();
	
	// 向center请求未收到的个人邮件
	_GM2CNReqUnreceivedMail();
}

void CRoleMailModule::final()
{
	;
}

void CRoleMailModule::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDMailSystemGC2GMReqGetAttach, &BSLib::Framework::CreateCMessage<CMsgMailSystemGC2GMReqGetAttach>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDMailSystemGC2GMReqGetAttach, &CRoleMailModule::_onMsgMailSystemGC2GMReqGetAttach, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDMailSystemGC2GMReqGetOpMail, &BSLib::Framework::CreateCMessage<CMsgMailSystemGC2GMReqOperateMail>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDMailSystemGC2GMReqGetOpMail, &CRoleMailModule::_onMsgMailSystemGC2GMReqOperateMail, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDMailSystemCN2GMAckUnreceivedMail,
		&BSLib::Framework::CreateCMessage<CMsgMailSystemCN2GMAckUnreceivedMail>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDMailSystemCN2GMAckUnreceivedMail, &CRoleMailModule::_onMsgMailSystemCN2GMAckUnreceivedMail, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgIDMailSystemCN2GMNtfNewRoleMail,
		&BSLib::Framework::CreateCMessage<CMsgMailSystemCN2GMNtfNewRoleMail>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgIDMailSystemCN2GMNtfNewRoleMail, &CRoleMailModule::_onMsgMailSystemCN2GMNtfNewRoleMail, this);
}

void CRoleMailModule::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	a_msgExecMgr->delMsgExecPtr(msgIDMailSystemGC2GMReqGetAttach);
	a_msgExecMgr->delMsgExecPtr(MsgIDMailSystemGC2GMReqGetOpMail);
	a_msgExecMgr->delMsgExecPtr(msgIDMailSystemCN2GMAckUnreceivedMail);
	a_msgExecMgr->delMsgExecPtr(msgIDMailSystemCN2GMNtfNewRoleMail);
}

bool CRoleMailModule::_GM2CNReqUnreceivedMail()
{	
	CMsgMailSystemGM2CNReqUnreceivedMail req;
	return sendMsgToCenterServer(req);
}

bool CRoleMailModule::_GM2CNReqDelMail(std::vector<BSLib::uint64> & a_mailIds)
{	
	CMsgMailSystemGM2CNNtfDelMail req;
	req.m_mailIds = a_mailIds;
	return sendMsgToCenterServer(req);
}

void CRoleMailModule::_onMsgMailSystemCN2GMAckUnreceivedMail(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{	
	std::vector<BSLib::uint64> mailIds;
	CMsgMailSystemCN2GMAckUnreceivedMail *ack = (CMsgMailSystemCN2GMAckUnreceivedMail *)a_msg;
	for(BSLib::uint32 i = 0; i < ack->m_mailCount; i++)
	{
		SMail * newMail = new SMail;
		ack->m_MailStream >> newMail->m_accountId;
		ack->m_MailStream >> newMail->m_zoneId;
		ack->m_MailStream >> newMail->m_roleIndex;
		ack->m_MailStream >> newMail->m_mailId;
		ack->m_MailStream >> newMail->m_mailType;
		ack->m_MailStream >> newMail->m_systemMail;
		ack->m_MailStream >> newMail->m_isRead;
		ack->m_MailStream >> newMail->m_isGet;
		ack->m_MailStream >> newMail->m_timeStamp;
		ack->m_MailStream >> newMail->m_title;
		ack->m_MailStream >> newMail->m_content;
		ack->m_MailStream >> newMail->m_sender;
		ack->m_MailStream >> newMail->m_types;
		ack->m_MailStream >> newMail->m_ids;
		ack->m_MailStream >> newMail->m_nums;
		
		mailIds.push_back(newMail->m_mailId);
		if(newMail->m_mailId <= m_roleMailConfig.m_lastestSelfMailID)
		{
			delete newMail;
			continue;
		}
		
		// 记录已收取的最大mail id
		m_roleMailConfig.m_lastestSelfMailID = newMail->m_mailId;
		if(newMail->m_mailType == EMailTypeDeduct)
		{
			_onDeductMail(newMail);
			delete newMail;
			continue;
		}
		else
		{
			m_inputBox.insert(std::make_pair(newMail->m_mailId, newMail));
			_dbUpdateRoleMail(newMail);
		}
	}
	
	if( !mailIds.empty()){
		_GM2CNReqDelMail(mailIds);
	}

	_dbUpdateRoleMailConfig();
	
	_onDelExpiredMail();

	// 消息返回后,通知客户端
	onlinePushMail();
}

void CRoleMailModule::_onMsgMailSystemCN2GMNtfNewRoleMail(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	CMsgMailSystemCN2GMNtfNewRoleMail *req = (CMsgMailSystemCN2GMNtfNewRoleMail *)a_msg;
	SMail *newMail = new SMail;
	newMail->serializeFrom(req->m_MailStream);

	std::vector<BSLib::uint64> mailIds;
	mailIds.push_back(newMail->m_mailId);
	do 
	{
		if(newMail->m_mailId <= m_roleMailConfig.m_lastestSelfMailID)
		{
			delete newMail;
			break;
		}

		m_roleMailConfig.m_lastestSelfMailID = newMail->m_mailId;
		_dbUpdateRoleMailConfig();

		if(newMail->m_mailType == EMailTypeDeduct)
		{
			_onDeductMail(newMail);
			delete newMail;
			break;
		}
		
		m_inputBox.insert(std::make_pair(newMail->m_mailId, newMail));
		_dbUpdateRoleMail(newMail);

		// 新邮件通知
		CMsgMailSystemGM2GCAckPushMail ack;
		ack.m_type = EMAILSYSTEM_UPDATE_DELTA;
		if(_serializeTo(newMail, ack.m_stream)){
			ack.m_mailCount++;
			sendMsgToClient(ack);
		}

	} while (false);
	
	// 请求删除...
	_GM2CNReqDelMail(mailIds);	
}

void CRoleMailModule::_dbUpdateRoleMailConfig()
{
	BSLib::Utility::CStream db_stream;
	m_roleMailConfig.serializeTo(db_stream);
	if(m_mailConfigTablePtr == NULL)
		return;
	m_mailConfigTablePtr->update(db_stream);
	m_mailConfigTablePtr->saveDataToDBServer(m_roleMailConfig.getDBKey(), false);
}

void CRoleMailModule::_dbUpdateRoleMail(SMail *mail)
{
	BSLib::Utility::CStream db_stream;
	mail->serializeTo(db_stream);
	if(m_inputBoxTablePtr == NULL)
		return;
	m_inputBoxTablePtr->update(mail->getDBKey(), mail->getIndexKey(), db_stream);
	m_inputBoxTablePtr->saveDataToDBServer(mail->getDBKey(), mail->getIndexKey(), false);
}

void CRoleMailModule::_dbDelRoleMail(SMail *mail)
{
	BSLib::Utility::CStream db_stream;
	mail->serializeTo(db_stream);
	if(m_inputBoxTablePtr == NULL)
		return;
	m_inputBoxTablePtr->remove(mail->getDBKey(), mail->getIndexKey());
	m_inputBoxTablePtr->saveDataToDBServer(mail->getDBKey(), mail->getIndexKey(), false);
}


bool CRoleMailModule::_mergeContainer(std::vector<BSLib::uint32>& a_fromIds, std::vector<BSLib::uint32>& a_fromNums,
									  std::vector<BSLib::uint32>& a_toIds, std::vector<BSLib::uint32>& a_toNums)
{
	if( a_fromIds.size() != a_fromNums.size())
		return false;

	if( a_toIds.size() != a_toNums.size())
		return false;

	std::map<BSLib::uint32, BSLib::uint32> bonusMap;
	for(BSLib::uint32 i = 0; i < a_fromIds.size(); i++)
	{
		std::map<BSLib::uint32, BSLib::uint32>::iterator it = bonusMap.find(a_fromIds[i]);
		if( it != bonusMap.end())
		{
			it->second = it->second + a_fromNums[i];
		}
		else
		{
			bonusMap.insert( std::make_pair(a_fromIds[i], a_fromNums[i]));
		}
	}

	for(BSLib::uint32 i = 0; i < a_toIds.size(); i++)
	{
		std::map<BSLib::uint32, BSLib::uint32>::iterator it = bonusMap.find(a_toIds[i]);
		if( it != bonusMap.end())
		{
			it->second = it->second + a_toNums[i];
		}
		else
		{
			bonusMap.insert( std::make_pair(a_toIds[i], a_toNums[i]));
		}

	}

	std::map<BSLib::uint32, BSLib::uint32>::iterator it = bonusMap.begin();
	a_toIds.clear();
	a_toNums.clear();
	for( ; it != bonusMap.end(); ++it)
	{
		a_toIds.push_back(it->first);
		a_toNums.push_back(it->second);
	}

	return true;
}

void CRoleMailModule::_onMsgMailSystemGC2GMReqGetAttach(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{	
	_onDelExpiredMail();

	using namespace GSLib::PlayerSystem::GM;
	//CMailSystemGM& mail_system = CMailSystemGM::singleton();
	SRoleGuid mailer(m_roleGuid);

	CMsgMailSystemGC2GMReqGetAttach *req = (CMsgMailSystemGC2GMReqGetAttach *)a_msg;
	std::vector<BSLib::uint64> success_ids;
	
	std::vector<BSLib::uint32> total_ids;
	std::vector<BSLib::uint32> total_nums;

	// 一键提取
	if( 0 == req->mail_ids.size())
	{
		TMailContainerMap& container = m_inputBox;
		for(TMailContainerMap::iterator it = container.begin(); it != container.end(); ++it)
		{
			SMail *self_obj = it->second;
			std::vector<BSLib::uint32> ids;
			std::vector<BSLib::uint32> nums;
			if( !mailGetAttach(self_obj->m_mailId, ids, nums))
				continue;

			_mergeContainer(ids, nums, total_ids, total_nums);
			success_ids.push_back(self_obj->m_mailId);
		}

	}	
	else
	{
		for(BSLib::uint32 i = 0; i < req->mail_ids.size(); i++)
		{
			std::vector<BSLib::uint32> ids;
			std::vector<BSLib::uint32> nums;
			if( !mailGetAttach(req->mail_ids[i], ids, nums))
				continue;

			_mergeContainer(ids, nums, total_ids, total_nums);
			success_ids.push_back(req->mail_ids[i]);
		}
	}

	// 提取成功的删除邮件
// 	for(BSLib::uint32 i = 0; i < success_ids.size(); i++)
// 	{
// 		mailDelete(success_ids[i]);
// 	}

	CMsgMailSystemGM2GCAckGetAttach ack;
	ack.m_mailCount = success_ids.size();
	for(BSLib::uint32 i = 0; i < success_ids.size(); i++)
		ack.m_mail_stream << success_ids[i];

	ack.m_bonus_count = total_ids.size();
	for(BSLib::uint32 i = 0; i < total_ids.size(); i++)
	{
		ack.m_bonus_stream << total_ids[i];
		ack.m_bonus_stream << total_nums[i];
	}

	// todo 奖励发放
	
	sendMsgToClient(ack);
}

bool CRoleMailModule::_serializeTo(const SMail* a_mail, BSLib::Utility::CStream& a_stream)
{
	using namespace GSLib::PlayerSystem::GM;
	CMailSystemGM& mail_system = CMailSystemGM::singleton();

	const SMail *self_obj = a_mail;

	const SMail *unique_obj = NULL;
	if(0 != self_obj->m_systemMail)
	{
		SRoleGuid roleGuid = mail_system.getUniqueRoleGuid();
		unique_obj = mail_system.mailOpen(roleGuid, self_obj->m_systemMail);
		if( NULL == unique_obj)
			return false;

	}

	a_stream << self_obj->m_mailId;
	a_stream << self_obj->m_mailType;
	a_stream << self_obj->m_isRead;
	a_stream << self_obj->m_isGet;
	a_stream << _getLeftTime(self_obj->m_mailType, self_obj->m_timeStamp);

	if( NULL != unique_obj)
		self_obj = unique_obj;

	a_stream << self_obj->m_title;
	a_stream << self_obj->m_content;
	a_stream << self_obj->m_sender;
	BSLib::uint32 size = self_obj->m_ids.size();
	a_stream << size;
	for(BSLib::uint32 i = 0; i < self_obj->m_ids.size(); i++)
	{
		a_stream << self_obj->m_ids[i];
		a_stream << self_obj->m_nums[i];
	}

	return true;
}

void CRoleMailModule::_onDelExpiredMail()
{	
	std::vector<BSLib::uint64> toDel;
	for(TMailContainerMap::iterator it = m_inputBox.begin(); it != m_inputBox.end(); ++it)
	{
		SMail *self_obj = it->second;
		if( 0 == _getLeftTime(self_obj->m_mailType, self_obj->m_timeStamp))
		{
			toDel.push_back(it->first);
		}
	}

	for(std::vector<BSLib::uint64>::iterator it = toDel.begin(); it != toDel.end(); ++it)
	{
		mailDelete(*it);
	}

	toDel.clear();
	BSLib::uint32 toDelNum = 0;
	BSLib::uint32 maxNum = 100;
	if( m_inputBox.size() > maxNum)
		toDelNum = m_inputBox.size() - maxNum;

	if(!toDelNum)
		return;
	
	for(TMailContainerMap::iterator it = m_inputBox.begin(); it != m_inputBox.end() && toDelNum != 0; ++it, --toDelNum)
	{
		toDel.push_back(it->first);
	}

	for(std::vector<BSLib::uint64>::iterator it = toDel.begin(); it != toDel.end(); ++it)
	{
		mailDelete(*it);
	}
}

void CRoleMailModule::onlinePushMail()
{
	using namespace GSLib::PlayerSystem::GM;
	//CMailSystemGM& mail_system = CMailSystemGM::singleton();

	CMsgMailSystemGM2GCAckPushMail ack;
	ack.m_type = EMAILSYSTEM_UPDATE_TOTAL;
	if( m_inputBox.empty())
	{
		sendMsgToClient(ack);
		return;
	}

	for(TMailContainerMap::iterator it = m_inputBox.begin(); it != m_inputBox.end(); ++it)
	{
		SMail *self_obj = it->second;
		if(_serializeTo(self_obj, ack.m_stream))
			ack.m_mailCount++;
	}

	sendMsgToClient(ack);
}

SRoleGuid CRoleMailModule::getRoleGuid()
{
	return m_roleGuid;
}

bool CRoleMailModule::cbNewMailNotify(SMail* a_obj)
{	
	TMailContainerMap::iterator it = m_inputBox.find(a_obj->m_mailId);
	if( it != m_inputBox.end())
		return false;

	m_inputBox.insert(std::make_pair(a_obj->m_mailId, a_obj));
	if(a_obj->m_systemMail){
		m_roleMailConfig.m_lastestSystemMailID = a_obj->m_systemMail;
		_dbUpdateRoleMailConfig();
	}

	_dbUpdateRoleMail(a_obj);

	CMsgMailSystemGM2GCAckPushMail ack;
	ack.m_type = EMAILSYSTEM_UPDATE_DELTA;
	if(_serializeTo(a_obj, ack.m_stream))
		ack.m_mailCount++;

	sendMsgToClient(ack);

	return true;
}

SMail* CRoleMailModule::mailOpen(BSLib::uint64 a_mailId)
{
	TMailContainerMap::iterator it = m_inputBox.find(a_mailId);
	if( it == m_inputBox.end())
		return NULL;

	return it->second;
}

bool CRoleMailModule::mailRead(BSLib::uint64 a_mailId)
{
	SMail *obj = mailOpen(a_mailId);
	if( NULL == obj)
		return false;

	obj->m_isRead = 1;
	_dbUpdateRoleMail(obj);

	return true;
}

bool CRoleMailModule::mailDelete(BSLib::uint64 a_mailId)
{
	TMailContainerMap::iterator it = m_inputBox.find(a_mailId);
	if( it == m_inputBox.end())
		return false;
	
	_dbDelRoleMail(it->second);
	delete it->second;
	m_inputBox.erase(it);
	
	return true;
}

bool CRoleMailModule::mailGetAttach(BSLib::uint64 a_mailId, std::vector<BSLib::uint32> &a_ids, std::vector<BSLib::uint32> &a_nums)
{	

	SMail *obj = mailOpen(a_mailId);
	if( NULL == obj)
		return  false;

	// 已领取
	if(0 != obj->m_isGet)
		return false;


	// 个人邮件
	if( 0 == obj->m_systemMail)
	{
		if(0 != obj->m_ids.size())
		{	
			a_ids = obj->m_ids;
			a_nums = obj->m_nums;

			PrizeSystem::GM::CRolePrizeModule* prizeM = (PrizeSystem::GM::CRolePrizeModule*)getRoleGM()->getPlayerModuleGM(EMODULECTYPE_PRIZE);
			std::vector<BSLib::uint32> types;
			bool success = prizeM->prizeRequestToBag(types, a_ids, a_nums, false, "mail");
			if(success){
				obj->m_isRead = 1;
				obj->m_isGet = 1;
				_dbUpdateRoleMail(obj);
			}
			return success;
		}
	}
	else
	{	
		using namespace GSLib::PlayerSystem::GM;
		CMailSystemGM& mail_system = CMailSystemGM::singleton();

		SRoleGuid roleGuid = mail_system.getUniqueRoleGuid();
		SMail *unique_obj = mail_system.mailOpen(roleGuid, obj->m_systemMail);
		if( NULL != unique_obj)
		{
			if( 0 != unique_obj->m_ids.size())
			{
				a_ids = unique_obj->m_ids;
				a_nums = unique_obj->m_nums;
		
				PrizeSystem::GM::CRolePrizeModule* prizeM = (PrizeSystem::GM::CRolePrizeModule*)getRoleGM()->getPlayerModuleGM(EMODULECTYPE_PRIZE);
				std::vector<BSLib::uint32> types;
				bool success = prizeM->prizeRequestToBag(types, a_ids, a_nums, false, "mail");
				if(success){
					obj->m_isRead = 1;
					obj->m_isGet = 1;
					_dbUpdateRoleMail(obj);
				}
				return success;
			}
		}
	}

	return false;
}

void CRoleMailModule::_onDeductMail(SMail * mail)
{
	using namespace PlayerSystem::GM;
	CRoleGM* role = getRoleGM();
	CRoleBagModuleGM* bagM = (CRoleBagModuleGM*)role->getPlayerModuleGM(EMODULECTYPE_BAG);
	
	std::vector<ItemSystem::GM::CPrizeItem> items;
	for(BSLib::uint32 i = 0; i < mail->m_ids.size(); i++)
	{
		bagM->removeItemCount(mail->m_ids[i], GSLib::ItemSystem::GM::EITEM_TP_IVALID, mail->m_nums[i], "mail", true);
		//bool res = bagM->removeItemCount(mail->m_ids[i], GSLib::ItemSystem::GM::EITEM_TP_IVALID, mail->m_nums[i], "mail", true);
	}

}

void CRoleMailModule::_onMsgMailSystemGC2GMReqOperateMail(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{	
	_onDelExpiredMail();

	using namespace GSLib::PlayerSystem::GM;
	//CMailSystemGM& mail_system = CMailSystemGM::singleton();
	SRoleGuid mailer(m_roleGuid);		

	CMsgMailSystemGC2GMReqOperateMail *req = (CMsgMailSystemGC2GMReqOperateMail *)a_msg;
	std::vector<BSLib::uint64> success_ids;
	if( EMAILSYSTEM_OP_READ == req->op_type)
	{	
		// 一键读取
		if( 0 == req->mail_count){
			TMailContainerMap &container = m_inputBox;
			for(TMailContainerMap::iterator it = container.begin(); it != container.end(); ++it)
			{
				SMail *obj = it->second;
				if(mailRead(obj->m_mailId))
					success_ids.push_back(obj->m_mailId);
			}
		}
		else{
			
			for(BSLib::uint32 i = 0; i < req->mail_count; i++)
			{
				if(mailRead(req->mail_ids[i]))
					success_ids.push_back(req->mail_ids[i]);
			}
		}
		
	}
	else if(EMAILSYSTEM_OP_DEL == req->op_type)
	{	
		std::vector<BSLib::uint64> to_del_ids;

		// 一键删除
		if( 0 == req->mail_count)
		{
			TMailContainerMap &container = m_inputBox;
			for(TMailContainerMap::iterator it = container.begin(); it != container.end(); ++it)
			{
				SMail *obj = it->second;
				if(_checkOneKeyDel(obj))
					to_del_ids.push_back(obj->m_mailId);
			}

		}
		else
		{	// 多个删除
			to_del_ids = req->mail_ids;
		}

		for(BSLib::uint32 i = 0; i < to_del_ids.size(); i++)
		{
			if(mailDelete(to_del_ids[i]))
				success_ids.push_back(to_del_ids[i]);
		}

	}
	else
	{	// 消息复用
		onlinePushMail();
	}

	CMsgMailSystemGM2GCAckOperateMail ack;
	ack.m_op_type = req->op_type;
	ack.m_mailCount = success_ids.size();
	for(BSLib::uint32 i = 0; i < success_ids.size(); i++)
		ack.m_stream << success_ids[i];
	
	sendMsgToClient(ack);
}

BSLib::uint64 CRoleMailModule::_getLeftTime(BSLib::uint32 a_type, BSLib::uint64 a_timeStamp)
{
	BSLib::Utility::CDateTime t = BSLib::Utility::CDateTime::getCurrentTime();
	BSLib::uint64 now = t.getSeconds();
	BSLib::uint64 day = 24 * 60 * 60;
	BSLib::uint64 halfDay = 12 * 60 * 60;
	BSLib::uint64 expiredDay = 0;
	if(a_type == EMailTypeSelf)
	{
		expiredDay = halfDay;	
	}
	else if( a_type == EMailTypeSystem)
	{
		expiredDay = day;
	}

	if( now >= expiredDay + a_timeStamp)
		return 0;

	return expiredDay - now + a_timeStamp;
}

bool CRoleMailModule::_checkOneKeyDel(SMail *a_mail)
{
	using namespace GSLib::PlayerSystem::GM;
	CMailSystemGM& mail_system = CMailSystemGM::singleton();
	
	// 可以删除的条件
	// 已读的
	if(1 == a_mail->m_isRead)
	{
		if( 0 != a_mail->m_systemMail)
		{	
			SRoleGuid roleGuid = mail_system.getUniqueRoleGuid();
			SMail *unique_obj = mail_system.mailOpen(roleGuid, a_mail->m_systemMail);
			if( NULL == unique_obj)
				return true;
			
			// 无奖励, 或有奖励 已领取
			if( 0 == unique_obj->m_ids.size() || (0 != unique_obj->m_ids.size() && 1 == a_mail->m_isGet))
				return true;
		}
		else
		{
			// 无奖励, 或有奖励 已领取
			if( 0 == a_mail->m_ids.size() || (0 != a_mail->m_ids.size() && 1 == a_mail->m_isGet))
				return true;	
		}
	}
	
	return false;	
}

void CRoleMailModule::updateDataToDB()
{
	_dbUpdateRoleMailConfig();
}

bool CRoleMailModule::cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{	
	if(EDBTABLEID_ROLE_MAIL_CONFIG_DATA == a_tableID){
		m_tableId = a_tableID;
		a_keyTable->traversal(*this);
		m_mailConfigTablePtr = a_keyTable;
	}

	return true;
}

bool CRoleMailModule::cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{	
	if(EDBTABLEID_ROLE_MAIL_INPUTBOX_DATA == a_tableID){
		m_tableId = a_tableID;
		a_keyTable->traversal(*this);
		m_inputBoxTablePtr = a_keyTable;
	}
	return true;
}

bool CRoleMailModule::exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value)
{	
	using namespace BSLib::Database;
	if( EDBTABLEID_ROLE_MAIL_CONFIG_DATA == m_tableId){
		BSLib::Utility::CStream stream;
		a_value->serializeTo(stream);
		m_roleMailConfig.serializeFrom(stream);
	}
	else if(EDBTABLEID_ROLE_MAIL_INPUTBOX_DATA == m_tableId){
		BSLib::Utility::CStream stream;
		a_value->serializeTo(stream);
		SMail *selfMail = new SMail;
		selfMail->serializeFrom(stream);
		m_inputBox.insert(std::make_pair(selfMail->m_mailId, selfMail));
	}

	return true;
}



}//GM

}//MailSystem

}//GSLib
