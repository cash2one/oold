#ifndef __GSLIB_LOGINSYSTEM_LG_LOGINSYSTEMLG_H__
#define __GSLIB_LOGINSYSTEM_LG_LOGINSYSTEMLG_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/memory/objectMgr.h>
#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/loginSystem/msgLoginSystem.h>

namespace GSLib
{

namespace LoginSystem
{

namespace LG
{

class CLoginSystemLG : public GFLib::CommonServer::ICommonSystem
{
public:
	CLoginSystemLG();
	virtual ~CLoginSystemLG();

	BSLIB_SINGLETON_DECLARE(CLoginSystemLG);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_LOGINSYSTEM; }

	bool verifyAccountLogin(GFLib::StubID a_stubID, std::string& a_accountLoginIP, CMsgLoginSystemGC2LGReqAccountLogin& a_reqAccountLogin, CMsgLoginSystemLG2GCAckAccountLogin& a_ackAccountLogin);
	bool registerAccount(GFLib::StubID a_stubID, std::string& accountLoginIP, CMsgLoginSystemGC2LGReqRegisterAccount& a_reqRegisterAccount, CMsgLoginSystemLG2GCAckRegisterAccount& a_ackRegisterAccount);
	bool verifyGetAccountToken(GFLib::StubID a_stubID, std::string& accountLoginIP, CMsgLoginSystemGC2LGReqGetAccountToken& a_reqAccountLogin, CMsgLoginSystemLG2GCAckGetAccountToken& a_ackAccountLogin);

	bool isValidAccountLogin(GFLib::StubID a_stubID);
	void removeAccountLogin(GFLib::StubID a_stubID);

protected:
	bool _verifyNormalAccountLogin(GFLib::StubID a_stubID, std::string& a_accountLoginIP, CMsgLoginSystemGC2LGReqAccountLogin& a_reqAccountLogin, CMsgLoginSystemLG2GCAckAccountLogin& a_ackAccountLogin);
	bool _verifyFastAccountLogin(GFLib::StubID a_stubID, std::string& a_accountLoginIP, CMsgLoginSystemGC2LGReqAccountLogin& a_reqAccountLogin, CMsgLoginSystemLG2GCAckAccountLogin& a_ackAccountLogin);
    bool _verifyTokenAccountLogin(GFLib::StubID a_stubID, std::string& a_accountLoginIP, CMsgLoginSystemGC2LGReqAccountLogin& a_reqAccountLogin, CMsgLoginSystemLG2GCAckAccountLogin& a_ackAccountLogin);

    bool _fastRegisterAccount(CMsgLoginSystemGC2LGReqAccountLogin& a_reqAccountLogin);

    bool _verifyNormalGetAccountToken(GFLib::StubID a_stubID, std::string& a_accountLoginIP, CMsgLoginSystemGC2LGReqGetAccountToken& a_reqAccountLogin, CMsgLoginSystemLG2GCAckGetAccountToken& a_ackAccountLogin);
    bool _verifyFastGetAccountToken(GFLib::StubID a_stubID, std::string& a_accountLoginIP, CMsgLoginSystemGC2LGReqGetAccountToken& a_reqAccountLogin, CMsgLoginSystemLG2GCAckGetAccountToken& a_ackAccountLogin);
    bool _fastRegisterAccount(CMsgLoginSystemGC2LGReqGetAccountToken& a_reqAccountLogin);



protected:
	virtual bool _init();
	virtual void _final();
	virtual bool ICommonSystem_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);

private:
	void _onMsgLoginSystemCN2LGAckAccountLogin(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg);
	void _onMsgLoginSystemSP2LGAckRegisterToken(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg);
	void _onMsgLoginSystemSP2LGAckCheckToken(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg);

private:
	bool _registerNormalAccountToDB(const std::string& a_accountName, const std::string& a_accountPwd, BSLib::uint32 a_channelID, const std::string& a_platform, const std::string& a_activationCode, BSLib::uint64& a_accountID);
	bool _registerFastAccountToDB(const std::string& a_uniqueID, const std::string& a_uniqueKey, BSLib::uint32 a_channelID, const std::string& a_platform, BSLib::uint64& a_accountID);

private:
	BSLib::Utility::CMutex m_mutex;
	GFLib::SServerID m_superServerID;
    int m_codeFilterMode;  // ¼¤»îÂë×¢²á¿ª¹Ø
};

}//LG

}//LoginSystem

}//GSLib

#endif//__GSLIB_LOGINSYSTEM_LG_LOGINSYSTEMLG_H__
