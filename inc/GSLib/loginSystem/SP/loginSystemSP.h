#ifndef __GSLIB_LOGINSYSTEM_SP_LOGINSYSTEMSP_H__
#define __GSLIB_LOGINSYSTEM_SP_LOGINSYSTEMSP_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/memory/objectMgr.h>
#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/loginSystem/msgLoginSystem.h>

namespace GSLib
{

namespace LoginSystem
{

namespace SP
{

class CLoginSystemSP : public GFLib::CommonServer::ICommonSystem
{
public:
	CLoginSystemSP();
	virtual ~CLoginSystemSP();

	BSLIB_SINGLETON_DECLARE(CLoginSystemSP);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_LOGINSYSTEM; }

protected:
	virtual bool _init();
	virtual void _final();
	virtual bool ICommonSystem_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);

private:
	void _onMsgLoginSystemLG2SPReqRegisterToken(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemLG2SPReqCheckToken(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgLoginSystemAC2SPAckCheckToken(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);

private:
	GFLib::SServerID m_authCodeServerID;
};

}//SP

}//LoginSystem

}//GSLib

#endif//__GSLIB_LOGINSYSTEM_SP_LOGINSYSTEMSP_H__
