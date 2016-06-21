#ifndef __GSLIB_LOGINSYSTEM_LG_ACCOUNTLOGINLGINFORMGR_H__
#define __GSLIB_LOGINSYSTEM_LG_ACCOUNTLOGINLGINFORMGR_H__

#include <BSLib/utility/memory/objectMgr.h>
#include <BSLib/utility/uniqueID.h>
#include <GFLib/commonServer/baseDef.h>
#include <GSLib/loginSystem/msgLoginSystem.h>

namespace GSLib
{

namespace LoginSystem
{

namespace LG
{

//////////////////////////////////////////////////////////////////////////
struct SAccountLoginLGInfor
{
	BSLib::uint32 m_sessionID;
	GFLib::StubID m_stubID;
	std::string m_accountName;
	BSLib::uint32 m_channelID;
	std::string m_accountLoginIP;
	GFLib::SAccountKey m_accountKey;

	BSLib::uint32 getLGSessionID() { return m_sessionID; }
	GFLib::StubID getStubID() { return m_stubID; }
};

BSLIB_UTILITY_OBJECTMGR_KEY2(CObjectAccountLoginLGInforMgr, LGSessionID, StubID);

//////////////////////////////////////////////////////////////////////////
class CAccountLoginLGInforMgr : public BSLib::Utility::CUniqueIDMgr<BSLib::uint32>
{
public:
	CAccountLoginLGInforMgr();
	~CAccountLoginLGInforMgr();

	BSLIB_SINGLETON_DECLARE(CAccountLoginLGInforMgr);

public:
	bool registerAccountLoginInfor(SAccountLoginLGInfor& a_accountInfor);
	bool isValidAccountLogin(GFLib::StubID& a_stubID);
	void removeAccountLoginInfor(GFLib::StubID& a_stubID);

	void checkCN2LGAckAccountLogin(CMsgLoginSystemCN2LGAckAccountLogin& a_ackAccountLogin);

	void checkSP2LGAckRegisterToken(CMsgLoginSystemSP2LGAckRegisterToken& a_ackRegisterToken);
	void checkSP2LGAckCheckToken(CMsgLoginSystemSP2LGAckCheckToken& a_ackCheckToken);

private:
	virtual bool checkUniqueID(BSLib::uint32 a_id);

private:
	CObjectAccountLoginLGInforMgr<BSLib::uint32, GFLib::StubID, SAccountLoginLGInfor> m_accountInforMgr;
	BSLib::Utility::CUniqueID32 m_sessionAllocator;
};

}//LG

}//LoginSystem

}//GSLib


#endif//__GSLIB_LOGINSYSTEM_LG_ACCOUNTLOGINLGINFORMGR_H__
