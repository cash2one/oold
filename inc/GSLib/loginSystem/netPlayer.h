#ifndef __GSLIB_LOGINSYSTEM_NETPLAYER_H__
#define __GSLIB_LOGINSYSTEM_NETPLAYER_H__

#include <BSLib/framework/message/msgExecMgr.h>
#include <GFLib/commonServer/message/message.h>
#include <GFLib/commonServer/account.h>
#include <GSLib/dbTableID.h>
#include <GSLib/moduleType.h>

namespace GSLib
{

namespace LoginSystem
{

class CNetPlayer
{
public:
	CNetPlayer(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName);
	virtual ~CNetPlayer();

	const std::string& getAccountName() const { return m_accountName; }
	GFLib::AccountID getAccountID() const { return m_accountKey.getAccountID(); }
	GFLib::ZoneID getZoneID() const { return m_accountKey.getZoneID(); }
	const GFLib::SAccountKey& getAccountKey() { return m_accountKey; }

	virtual bool broadcastMsgToClient(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	virtual bool broadcastMsgToClient(GFLib::CMessage& msg);

	bool executeMessage(BSLib::Framework::SMsgLabel* a_msgLabel, BSLib::Framework::SMessage* a_msg);

	void outputGameLog(const std::string& a_gameLable, const char* a_format, ...);

protected:
	virtual void _cbInitMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

protected:
	void _initMsg();

protected:
	BSLib::Framework::CMsgExecMgr* _getMsgExecMgr() { return  &m_msgExecMgr; }

private:
	GFLib::SAccountKey m_accountKey;
	const std::string m_accountName;
	BSLib::Framework::CMsgExecMgr m_msgExecMgr;
};

}//LoginSystem

}//GSLib

#endif//__GSLIB_LOGINSYSTEM_NETPLAYER_H__
