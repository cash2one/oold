#ifndef __SERVER_SERVER_CHANNELMGR_H__
#define __SERVER_SERVER_CHANNELMGR_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/framework/sysChannelMgr.h>
#include <BSLib/framework/message/msgExecMgr.h>
#include <GFLib/commonServer/message/msgSystemChannel.h>

struct SChannelInfor
{
	BSLib::Framework::CChannelID m_channelID;
	GFLib::SServerID m_serverID;
	std::string m_serverName;
};

class CChannelMgr : public BSLib::Framework::CSysChannelMgr
{
public:
	CChannelMgr();
	virtual ~CChannelMgr();

	BSLIB_SINGLETON_DECLARE(CChannelMgr);

	virtual bool init(BSLib::uint32 a_sysKey);
	virtual void final();
	void stopAll();
	void stop(BSLib::uint8 a_localNumber);

	SChannelInfor* getChannelInfor(const std::string& a_serverName);
	SChannelInfor* getChannelInfor(BSLib::uint8 a_localNumber);
	void showAllChannelInfor();

protected:
	virtual void _initChannel();
	virtual void _finalChannel();
	virtual void _parseSysMsg(BSLib::Framework::CChannelID& a_channelIDFrom, BSLib::Framework::ESysMsgType a_sysMsgType);
	virtual void _parseMsg(BSLib::Framework::SMessage* a_msg, BSLib::Framework::SSysMsgLabel* msgLabel); 

private:
	void _final();
	void _onSysChannelLC2LCResServerInfor(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework:: SMessage* msg);

private:
	std::vector<SChannelInfor*> m_localServerInfor;
	BSLib::Framework::CMsgExecMgr m_msgExecMgr;
};

#endif//__SERVER_SERVER_CHANNELMGR_H__

