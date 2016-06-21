
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
class CPlayerGTMgr: public BSLib::Utility::CObjectKey2Mgr<BSLib::uint64, GFLib::AccountID, CPlayerGT>
{
	public:
		CPlayerGTMgr();
		virtual ~CPlayerGTMgr();
		BSLIB_SINGLETON_DECLARE(CPlayerGTMgr);

		bool init();
		void final();
	public:
		LoginSystem::GT::CNetPlayerGT* createNetPlayerGT(const GFLib::AccountID& a_accountID, const std::string& a_accountName);
		LoginSystem::GT::CNetPlayerGT* getNetPlayerGT(const GFLib::AccountID& a_accountID);
		void removeNetPlayerGT(const GFLib::AccountID& a_accountID);
    	void removeAllPlayer();
	private:
		BSLib::Utility::CHashMap<GFLib::AccountID, CPlayerGT*> m_AccountHashMap;

};
}//GT

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_GT_PLAYERGTMGR_H__

