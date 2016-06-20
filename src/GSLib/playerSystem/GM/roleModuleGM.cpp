//////////////////////////////////////////////////////////////////////
//	created:	2014/07/25
//	filename: 	src\GSLib\playerSystem\GM\roleModuleGM.cpp
//	author:		zhangping
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/tracer.h>
#include <GSLib/playerSystem/GM/playerGMMgr.h>
#include <GSLib/playerSystem/GM/playerGM.h>
#include <GSLib/playerSystem/GM/roleModuleGM.h>

namespace GSLib
{

namespace PlayerSystem
{	

namespace GM
{


CRoleModuleGM::CRoleModuleGM(CRoleGM* a_roleGM, EModuleType a_moduleType)
: m_roleGM(a_roleGM)
, m_moduleType(a_moduleType)
{
	;
}

CRoleModuleGM::~CRoleModuleGM()
{
	m_roleGM = NULL;
}

void CRoleModuleGM::onRoleActive()
{
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "CRoleModuleGM::onRoleActive()[EModuleType=%d]",getModuleType());
}

void  CRoleModuleGM::onRoleInactive()
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "CRoleModuleGM::onRoleInactive()[EModuleType=%d]",getModuleType());
}

void  CRoleModuleGM::onRoleDelete()
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "CRoleModuleGM::onRoleDelete()[EModuleType=%d]",getModuleType());
}

bool CRoleModuleGM::cbSelectGetTableData(const GSLib::SRoleKey& a_roleKey,GSLib::DBSystem::ETableKeyType a_TableKeyType,GSLib::DBSystem::CKeyIndexTablePtr& a_keyIndexTable, GSLib::DBSystem::CKeyTablePtr& a_keyTable,EDBTableID a_tableID, BSLib::uint32 a_sessionID,BSLib::Utility::CStream& a_stream)
{
    BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "CRoleModuleGM::cbSelectGetTableData()[EModuleType=%d][模块数据未解析]",getModuleType());
    a_stream.reset();
    return false;
}

bool CRoleModuleGM::cbSelectMultiTableData(bool a_success,BSLib::uint32 a_sessionID,void* a_ptr,CRoleAllData& a_roleAllData){
     BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "CRoleModuleGM::cbSelectMultiTableData()[EModuleType=%d][a_sessionID=%d][模块数据未处理的返回数据]",getModuleType(),a_sessionID);
     return false;
}

bool CRoleModuleGM::sendMsgToClient(GFLib::SMessage* msg, BSLib::uint32 msgSize)
{
	if (m_roleGM == NULL) {
		return false;
	}
	LoginSystem::GM::CNetPlayerGM *player = m_roleGM->getPlayerGM();
	if(player != NULL){
		return player->sendMsgToClient(msg,msgSize);
	}
	return false;
}

bool CRoleModuleGM::sendMsgToClient(GFLib::CMessage& msg)
{
	if (m_roleGM == NULL) {
		return false;
	}
	LoginSystem::GM::CNetPlayerGM *player = m_roleGM->getPlayerGM();
	if(player != NULL){
		return player->sendMsgToClient(msg);
	}
	return false;
}

bool CRoleModuleGM::sendMsgToGateServer(GFLib::SMessage* msg, BSLib::uint32 msgSize)
{
	if (m_roleGM == NULL) {
		return false;
	}
	LoginSystem::GM::CNetPlayerGM *player = m_roleGM->getPlayerGM();
	if(player != NULL){
		return player->sendMsgToGateServer(msg,msgSize);
	}
	return false;
}

bool CRoleModuleGM::sendMsgToGateServer(GFLib::CMessage& msg)
{
	if (m_roleGM == NULL) {
		return false;
	}
	LoginSystem::GM::CNetPlayerGM *player = m_roleGM->getPlayerGM();
	if(player != NULL){
		return player->sendMsgToGateServer(msg);
	}
	return false;
}

bool CRoleModuleGM::sendMsgToDataServer(GFLib::SMessage* msg, BSLib::uint32 msgSize)
{
	if (m_roleGM == NULL) {
		return false;
	}
	LoginSystem::GM::CNetPlayerGM *player = m_roleGM->getPlayerGM();
	if(player != NULL){
		return player->sendMsgToDataServer(msg,msgSize);
	}
	return false;
}

bool CRoleModuleGM::sendMsgToDataServer(GFLib::CMessage& msg)
{
	if (m_roleGM == NULL) {
		return false;
	}
	LoginSystem::GM::CNetPlayerGM *player = m_roleGM->getPlayerGM();
	if(player != NULL){
		return player->sendMsgToDataServer(msg);
	}
	return false;
}

bool CRoleModuleGM::sendMsgToCenterServer(GFLib::SMessage* msg, BSLib::uint32 msgSize)
{
	if (m_roleGM == NULL) {
		return false;
	}
	LoginSystem::GM::CNetPlayerGM *player = m_roleGM->getPlayerGM();
	if(player != NULL){
		return player->sendMsgToCenterServer(msg,msgSize);
	}
	return false;
}

bool CRoleModuleGM::sendMsgToCenterServer(GFLib::CMessage& msg)
{
	if (m_roleGM == NULL) {
		return false;
	}
	LoginSystem::GM::CNetPlayerGM *player = m_roleGM->getPlayerGM();
	if(player != NULL){
		return player->sendMsgToCenterServer(msg);
	}
	return false;
}

}//GM

}//PlayerSystem

}//GSLib
