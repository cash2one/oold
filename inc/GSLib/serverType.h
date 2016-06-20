//////////////////////////////////////////////////////////////////////
//	created:	2014/07/19
//	filename:	GSLib\serverType.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////

#ifndef __GSLIB_SERVERDEF_H__
#define __GSLIB_SERVERDEF_H__

#include <GFLib/commonServer/baseDef.h>

namespace GSLib
{
	const GFLib::ServerType SRVTYPE_GATESERVER = 9;			//潠備'GT'
	const GFLib::ServerType SRVTYPE_GAMESERVER = 10;		//潠備'GM'
	const GFLib::ServerType SRVTYPE_CENTERSERVER = 11;		//潠備'CN'
	const GFLib::ServerType SRVTYPE_LOGINSERVER = 12;		//潠備'LG'
	const GFLib::ServerType SRVTYPE_DATASERVER = 13;		//潠備'DB'
	const GFLib::ServerType SRVTYPE_SUPERSERVER = 14;		//潠備'SP'
	const GFLib::ServerType SRVTYPE_CHARGESERVER = 15;		//潠備'CH'
	const GFLib::ServerType SRVTYPE_AUTHCODESERVER = 16;	//潠備'AC'
}

#endif//__GSLIB_SERVERDEF_H__