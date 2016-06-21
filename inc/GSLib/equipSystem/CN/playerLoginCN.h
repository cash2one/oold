#ifndef __GSLIB_PLAYERSYSTEM_CN_PLAYERLOGINCN_H__
#define __GSLIB_PLAYERSYSTEM_CN_PLAYERLOGINCN_H__

#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonSystem.h>
#include "GSLib/playerSystem/CN/playerCN.h"
#include "GSLib/loginSystem/CN/netPlayerCNMgr.h"
#include "GSLib/loginSystem/CN/netPlayerCN.h"

namespace GSLib
{

namespace PlayerSystem
{

namespace CN
{

class CPlayLoginCN :public GSLib::LoginSystem::CN::CNetPlayerCNMgr
{
	BSLIB_SINGLETON_DECLARE(CPlayLoginCN);
public:
	CPlayLoginCN();
	virtual ~CPlayLoginCN();

public:
	bool init();
	void final();

	virtual GSLib::LoginSystem::CN::CNetPlayerCN* createNetPlayerCN(const GFLib::AccountID& a_accountID, const std::string& a_accountName);
	virtual GSLib::LoginSystem::CN::CNetPlayerCN* getNetPlayerCN(const GFLib::AccountID& a_accountID);
	virtual void removeNetPlayerCN(const GFLib::AccountID& a_accountID);
};

}//CN

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_CN_PLAYERLOGINCN_H__

