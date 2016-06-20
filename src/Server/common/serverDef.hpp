//////////////////////////////////////////////////////////////////////
//	created:	2014/07/06
//	filename:	src\Server\common\serverDef.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __SERVER_COMMON_SERVERDEF_HPP__
#define __SERVER_COMMON_SERVERDEF_HPP__

#include <GSLib/serverType.h>
#include <GSLib/tracer.h>

namespace Server
{

void initServerType()
{
	GFLib::CommonServer::CServerTypeMgr::singleton().setServerType(GFLib::SRVTYPE_GAMECLIENT, "GameClient", "GC");
	GFLib::CommonServer::CServerTypeMgr::singleton().setServerType(GSLib::SRVTYPE_GATESERVER, "GateServer", "GT");
	GFLib::CommonServer::CServerTypeMgr::singleton().setServerType(GSLib::SRVTYPE_GAMESERVER, "GameServer", "GM");
	GFLib::CommonServer::CServerTypeMgr::singleton().setServerType(GSLib::SRVTYPE_CENTERSERVER, "CenterServer", "CS");
	GFLib::CommonServer::CServerTypeMgr::singleton().setServerType(GSLib::SRVTYPE_LOGINSERVER, "LoginServer", "LG");
	GFLib::CommonServer::CServerTypeMgr::singleton().setServerType(GSLib::SRVTYPE_DATASERVER, "DataServer", "DB");
	GFLib::CommonServer::CServerTypeMgr::singleton().setServerType(GSLib::SRVTYPE_SUPERSERVER, "SuperServer", "SP");
	GFLib::CommonServer::CServerTypeMgr::singleton().setServerType(GSLib::SRVTYPE_CHARGESERVER, "ChargeServer", "CH");
	GFLib::CommonServer::CServerTypeMgr::singleton().setServerType(GSLib::SRVTYPE_AUTHCODESERVER, "AuthCodeServer", "AC");
}

void initTraceType()
{
	BSLib::Utility::CTracer* tracer = BSLib::Utility::CTracer::getSysTracer();
	if (tracer != NULL) {
		tracer->setTypeName(GSLib::ETT_GSLIB_LOGINSYSTEM, "LOGINSYS");
		tracer->setTypeName(GSLib::ETT_GSLIB_DBSYSTEM, "DBSYS");
		tracer->setTypeName(GSLib::ETT_GSLIB_PLAYERSYSTEM, "PLAYERSYS");
		tracer->setTypeName(GSLib::ETT_GSLIB_SCENESYSTEM, "SCENESYS");
		tracer->setTypeName(GSLib::ETT_GSLIB_ITEMSYSTEM, "ITEMSYS");
		tracer->setTypeName(GSLib::ETT_GSLIB_SKILLPSYSTEM, "SKILLSYS");
		tracer->setTypeName(GSLib::ETT_GSLIB_NPCSYSTEM, "NPCSYS");
		tracer->setTypeName(GSLib::ETT_GSLIB_PETSYSTEM, "PETSYS");
		tracer->setTypeName(GSLib::ETT_GSLIB_PRIZESYSTEM, "PRIZESYS");
		tracer->setTypeName(GSLib::ETT_GSLIB_EQUIPSYSTEM, "EQUIPSYS");
		tracer->setTypeName(GSLib::ETT_GSLIB_TASKSYSTEM, "TASKSYS");
		tracer->setTypeName(GSLib::ETT_GSLIB_CHATSYSTEM, "CHATSYS");
		tracer->setTypeName(GSLib::ETT_GSLIB_MAILSYSTEM, "MAILSYS");
		tracer->setTypeName(GSLib::ETT_GSLIB_MAILSYSTEM, "RANKSYS");

		tracer->setTypeName(GSLib::ETT_GSLIB_GAME, "GAME");
	}
}

}//Server

#endif//__SERVER_COMMON_SERVERDEF_HPP__