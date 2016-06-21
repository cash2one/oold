#include <GFLib/commonServer/account.h>
#include <GFLib/commonServer/message/msgServerLink.h>
#include <GFLib/commonServer/commonServer.h>
#include <GFLib/commonServer/serviceMgr.h>

namespace GFLib
{

namespace CommonServer
{

CAccount::CAccount(const GFLib::SAccountKey& a_accountKey)
: m_accountKey(a_accountKey)
, m_transferMsgCb(NULL)
{
	;
}

CAccount::CAccount(AccountID a_accountID, ZoneID a_zoneID)
: m_accountKey(a_accountID, a_zoneID)
, m_transferMsgCb(NULL)
{
	;
}

CAccount::~CAccount()
{
	m_transferMsgCb = NULL;
}

bool CAccount::sendMsgToServer(const GFLib::SServerID& a_serverID, GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
{
	return sendMsgToServer(a_serverID, a_serverID, a_msg, a_msgSize);
}

bool CAccount::sendMsgToServer(const GFLib::SServerID& a_serverID, GFLib::CMessage& a_msg)
{
	return sendMsgToServer(a_serverID, a_serverID, a_msg);
}

bool CAccount::sendMsgToClient(const GFLib::SServerID& a_gateServerID, GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
{
	GFLib::SServerID client(a_gateServerID.getZoneID(), GFLib::SRVTYPE_GAMECLIENT, 0);
	return sendMsgToServer(a_gateServerID, client, a_msg, a_msgSize);
}

bool CAccount::sendMsgToClient(const GFLib::SServerID& a_gateServerID, GFLib::CMessage& a_msg)
{
	GFLib::SServerID client(a_gateServerID.getZoneID(), GFLib::SRVTYPE_GAMECLIENT, 0);
	return sendMsgToServer(a_gateServerID, client, a_msg);
}

bool CAccount::sendMsgToServer(const GFLib::SServerID& a_serverID, const GFLib::SServerID& a_toServerID, GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize)
{
	GFLib::CommonServer::CCommonServer* server = GFLib::CommonServer::CCommonServer::getCommonServer();
	if (server == NULL) {
		return false;
	}

	BSLib::Utility::CStream stream;
	stream.writeReserve(a_msgSize + sizeof(SMsgServerLinkXX2XXNtfTransfer));

	SMsgServerLinkXX2XXNtfTransfer* ntTransfer = (SMsgServerLinkXX2XXNtfTransfer*)stream.writePtr();
	new (static_cast<void*>(ntTransfer)) SMsgServerLinkXX2XXNtfTransfer();
	ntTransfer->m_serverIDFrome = server->getServerID();
	ntTransfer->m_serverIDTo = a_toServerID;
	ntTransfer->m_accountKey = m_accountKey;
	ntTransfer->m_msgSize = 0;

	BSLib::uint32 headSize = ntTransfer->getSize();
	ntTransfer->m_msgSize = a_msgSize;

	stream.writeFlip(headSize);

	stream.push((char*)a_msg, a_msgSize);

	return GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_serverID, (GFLib::SMessage*)stream.readPtr(), stream.readSize());
}

bool CAccount::sendMsgToServer(const GFLib::SServerID& a_serverID, const GFLib::SServerID& a_toServerID, GFLib::CMessage& a_msg)
{
	GFLib::CommonServer::CCommonServer* server = GFLib::CommonServer::CCommonServer::getCommonServer();
	if (server == NULL) {
		return false;
	}

	BSLib::Utility::CStream stream;
	stream.writeReserve(sizeof(SMsgServerLinkXX2XXNtfTransfer));

	SMsgServerLinkXX2XXNtfTransfer* ntTransfer = (SMsgServerLinkXX2XXNtfTransfer*)stream.writePtr();
	new (static_cast<void*>(ntTransfer)) SMsgServerLinkXX2XXNtfTransfer();
	ntTransfer->m_serverIDFrome = server->getServerID();
	ntTransfer->m_serverIDTo = a_toServerID;
	ntTransfer->m_accountKey = m_accountKey;
	ntTransfer->m_msgSize = 0;

	BSLib::uint32 headSize = ntTransfer->getSize();
	stream.writeFlip(headSize);

	if (!a_msg.serializeTo(stream)){
		return false;
	}

	ntTransfer = (SMsgServerLinkXX2XXNtfTransfer*)stream.readPtr();
	ntTransfer->m_msgSize = stream.readSize() - headSize;

	return GFLib::CommonServer::CServiceMgr::singleton().sendMsgToServer(a_serverID, (GFLib::SMessage*)stream.readPtr(), stream.readSize());
}

bool CAccount::_transferMsg(const GFLib::ServerType& a_serverType, GFLib::SMessage* msg, BSLib::uint32 msgSize)
{
	if (m_transferMsgCb == NULL) {
		return false;
	}
	return m_transferMsgCb->_transferMsg(a_serverType, msg, msgSize);
}

}//CommonServer

}//GFLib

#ifdef __GNUC__


#else

namespace stdext
{

size_t hash_value(const GFLib::SAccountKey & v)
{
	GFLib::AccountID accountID = v.getAccountID();
	GFLib::ZoneID zoneID = v.getZoneID();
	if (sizeof(BSLib::uint64) == sizeof(size_t)){
		return (size_t)(accountID + ((BSLib::uint64)(zoneID) << 32));
	} else {
		return (size_t)((accountID >> 32) ^ (accountID & 0xFFFFFFFF) + ((BSLib::uint32)(zoneID) << 16));
	}
}

}

#endif//__GNUC__
