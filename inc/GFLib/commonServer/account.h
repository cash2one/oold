#ifndef __GFLIB_COMMONSERVER_ACCOUNT_H__
#define __GFLIB_COMMONSERVER_ACCOUNT_H__

#include <BSLib/utility/pointer.h>
#include <GFLib/commonServer/baseDef.h>
#include <GFLib/commonServer/message/message.h>

namespace GFLib
{

namespace CommonServer
{

class CAccountTransferMsgCallback
{
protected:
	virtual bool _transferMsg(const GFLib::ServerType& a_serverType, GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize) = 0;

private:
	friend class CAccount;;
};

class GFLIB_COMMONSERVER_API CAccount
{
public:
	CAccount(const GFLib::SAccountKey& a_accountKey);
	CAccount(AccountID a_accountID, ZoneID a_zoneID);
	virtual ~CAccount();

	AccountID getAccountID() const { return m_accountKey.getAccountID(); }
	ZoneID getZoneID() const { return m_accountKey.getZoneID(); }
	const GFLib::SAccountKey& getAccountKey() const { return m_accountKey; }

	bool sendMsgToServer(const GFLib::SServerID& a_serverID, GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize);
	bool sendMsgToServer(const GFLib::SServerID& a_serverID, GFLib::CMessage& a_msg);

	bool sendMsgToClient(const GFLib::SServerID& a_gateServerID, GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize);
	bool sendMsgToClient(const GFLib::SServerID& a_gateServerID, GFLib::CMessage& a_msg);

	bool sendMsgToServer(const GFLib::SServerID& a_serverID, const GFLib::SServerID& a_toServerID, GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize);
	bool sendMsgToServer(const GFLib::SServerID& a_serverID, const GFLib::SServerID& a_toServerID, GFLib::CMessage& a_msg);

	void setTransferMsgCB(CAccountTransferMsgCallback* cb) { m_transferMsgCb = cb; }

private:
	bool _transferMsg(const GFLib::ServerType& a_serverType, GFLib::SMessage* msg, BSLib::uint32 msgSize);

private:
	GFLib::SAccountKey m_accountKey;
	CAccountTransferMsgCallback* m_transferMsgCb;

	friend class IService;
};
typedef BSLib::Utility::CPointer<CAccount> CAccountPtr;

}//CommonServer

}//GFLib

#endif//__GFLIB_COMMONSERVER_ACCOUNT_H__

