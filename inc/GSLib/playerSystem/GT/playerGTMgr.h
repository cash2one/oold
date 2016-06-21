
#ifndef __GSLIB_PLAYERSYSTEM_GT_PLAYERGTMGR_H__
#define __GSLIB_PLAYERSYSTEM_GT_PLAYERGTMGR_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/memory/objectMgr.h>
#include <GFLib/commonServer/commonSystem.h>
#include "GSLib/playerSystem/GT/playerGT.h"
#include "GSLib/loginSystem/GT/netPlayerGTMgr.h"
#include "GSLib/loginSystem/GT/netPlayerGT.h"

namespace GSLib
{

namespace PlayerSystem
{

namespace GT
{
class CPlayerGTMgr : public GSLib::LoginSystem::GT::CNetPlayerGTMgr
{
public:
	CPlayerGTMgr();
	virtual ~CPlayerGTMgr();
	BSLIB_SINGLETON_DECLARE(CPlayerGTMgr);

	bool init();
	void final();
public:
	virtual GSLib::LoginSystem::GT::CNetPlayerGT* createNetPlayerGT(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName);
	virtual GSLib::LoginSystem::GT::CNetPlayerGT* getNetPlayerGT(const GFLib::SAccountKey& a_accountKey);
	virtual void removeNetPlayerGT(const GFLib::SAccountKey& a_accountKey);


public:
	CPlayerGT* getPlayerGT(const GFLib::SAccountKey& a_accountKey);
	CRoleGT* getCurRoleGT(const GFLib::SAccountKey& a_accountKey);

	void removeAllPlayer();

private:
	BSLib::Utility::CHashMap<GFLib::SAccountKey, CPlayerGT*> m_accountHashMap;

};
}//GT

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_GT_PLAYERGTMGR_H__

