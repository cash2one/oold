//////////////////////////////////////////////////////////////////////
//	created:	2013/06/09
//	filename:	GFLib\commonServer\sysChannelMgr.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GFLIB_COMMONSERVER_SYSCHANNELMGR_H__
#define __GFLIB_COMMONSERVER_SYSCHANNELMGR_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/framework/sysChannelMgr.h>
#include <GFLib/commonServer/baseDef.h>

namespace GFLib
{

namespace CommonServer
{

class GFLIB_COMMONSERVER_API CSysChannelMgr : public BSLib::Framework::CSysChannelMgr
{
public:
	CSysChannelMgr();
	~CSysChannelMgr();

	BSLIB_SINGLETON_DECLARE(CSysChannelMgr);

protected:
	virtual void _initChannel();
	virtual void _finalChannel();
	virtual void _parseSysMsg(BSLib::Framework::CChannelID& a_channelIDFrom, BSLib::Framework::ESysMsgType a_sysMsgType);
	virtual void _parseMsg(BSLib::Framework::SMessage* a_msg, BSLib::Framework::SSysMsgLabel* msgLabel); 

private:
	virtual void _onSysMsgTerminate();
};

}//CommonServer

}//GFLib

#endif//__GFLIB_COMMONSERVER_SYSCHANNELMGR_H__

