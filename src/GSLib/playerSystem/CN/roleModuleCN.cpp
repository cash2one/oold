#include <GSLib/tracer.h>
#include <GSLib/playerSystem/CN/playerCNMgr.h>
#include <GSLib/playerSystem/CN/playerCN.h>
#include <GSLib/playerSystem/CN/roleModuleCN.h>

namespace GSLib
{

namespace PlayerSystem
{	

namespace CN
{


CRoleModuleCN::CRoleModuleCN(CRoleCN* a_roleCN, EModuleType a_moduleType)
: m_roleCN(a_roleCN)
, m_moduleType(a_moduleType)
{
	;
}

CRoleModuleCN::~CRoleModuleCN()
{
	m_roleCN = NULL;
}

void CRoleModuleCN::onRoleActive()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "CRoleModuleCN::onRoleActive();");
}

void  CRoleModuleCN::onRoleInactive()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "CRoleModuleCN::onRoleInactive();");
}

void  CRoleModuleCN::cbPlayerOnline()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "CRoleModuleCN::cbPlayerOnline();");
}


void  CRoleModuleCN::cbPlayerOffline()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "CRoleModuleCN::cbPlayerOffline();");
}

bool CRoleModuleCN::sendMsgToClient(GFLib::SMessage* msg, BSLib::uint32 msgSize)
{
	if (m_roleCN == NULL) {
		return false;
	}
	LoginSystem::CN::CNetPlayerCN *player = m_roleCN->getPlayerCN();
	if(player != NULL){
		return player->sendMsgToClient(msg,msgSize);
	}
	return false;
}

bool CRoleModuleCN::sendMsgToClient(GFLib::CMessage& msg)
{
	if (m_roleCN == NULL) {
		return false;
	}
	LoginSystem::CN::CNetPlayerCN *player = m_roleCN->getPlayerCN();
	if(player != NULL){
		return player->sendMsgToClient(msg);
	}
	return false;
}

bool CRoleModuleCN::sendMsgToGateServer(GFLib::SMessage* msg, BSLib::uint32 msgSize)
{
	if (m_roleCN == NULL) {
		return false;
	}
	LoginSystem::CN::CNetPlayerCN *player = m_roleCN->getPlayerCN();
	if(player != NULL){
		return player->sendMsgToGateServer(msg,msgSize);
	}
	return false;
}

bool CRoleModuleCN::sendMsgToGateServer(GFLib::CMessage& msg)
{
	if (m_roleCN == NULL) {
		return false;
	}
	LoginSystem::CN::CNetPlayerCN *player = m_roleCN->getPlayerCN();
	if(player != NULL){
		return player->sendMsgToGateServer(msg);
	}
	return false;
}

bool CRoleModuleCN::sendMsgToDataServer(GFLib::SMessage* msg, BSLib::uint32 msgSize)
{
	if (m_roleCN == NULL) {
		return false;
	}
	LoginSystem::CN::CNetPlayerCN *player = m_roleCN->getPlayerCN();
	if(player != NULL){
		return player->sendMsgToDataServer(msg,msgSize);
	}
	return false;
}

bool CRoleModuleCN::sendMsgToDataServer(GFLib::CMessage& msg)
{
	if (m_roleCN == NULL) {
		return false;
	}
	LoginSystem::CN::CNetPlayerCN *player = m_roleCN->getPlayerCN();
	if(player != NULL){
		return player->sendMsgToDataServer(msg);
	}
	return false;
}

bool CRoleModuleCN::sendMsgToGameServer(GFLib::SMessage* msg, BSLib::uint32 msgSize)
{
	if (m_roleCN == NULL) {
		return false;
	}
	LoginSystem::CN::CNetPlayerCN *player = m_roleCN->getPlayerCN();
	if(player != NULL){
		return player->sendMsgToGameServer(msg,msgSize);
	}
	return false;
}

bool CRoleModuleCN::sendMsgToGameServer(GFLib::CMessage& msg)
{
	if (m_roleCN == NULL) {
		return false;
	}
	LoginSystem::CN::CNetPlayerCN *player = m_roleCN->getPlayerCN();
	if(player != NULL){
		return player->sendMsgToGameServer(msg);
	}
	return false;
}

}//CN

}//PlayerSystem

}//GSLib

