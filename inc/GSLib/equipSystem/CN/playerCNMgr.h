#ifndef __GSLIB_PLAYERSYSTEM_CN_CPLAYERCNMGR_H__
#define __GSLIB_PLAYERSYSTEM_CN_CPLAYERCNMGR_H__

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

class CPlayerCNMgr
{
public:

	CPlayerCNMgr();
	virtual ~CPlayerCNMgr();

	BSLIB_SINGLETON_DECLARE(CPlayerCNMgr);

	bool init();
	void final();

public:
	LoginSystem::CN::CNetPlayerCN* createNetPlayerCN(const GFLib::AccountID& a_accountID, const std::string& a_accountName);
	LoginSystem::CN::CNetPlayerCN* getNetPlayerCN(const GFLib::AccountID& a_accountID);
	void removeNetPlayerCN(const GFLib::AccountID& a_accountID);

public:
	void removeAllPlayer();

private:
	BSLib::Utility::CHashMap<GFLib::AccountID, CPlayerCN*> m_AccountHashMap;
};

}//CN

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_CN_CPLAYERCNMGR_H__

