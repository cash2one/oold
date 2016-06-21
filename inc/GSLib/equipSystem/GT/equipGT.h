#ifndef __GSLIB_PLAYERSYSTEM_GT_PLAYERGT_H__
#define __GSLIB_PLAYERSYSTEM_GT_PLAYERGT_H__

#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonSystem.h>
#include "GSLib/playerSystem/GT/roleGT.h"
#include "GSLib/loginSystem/GT/netPlayerGT.h"

namespace GSLib
{

namespace PlayerSystem
{

namespace GT
{

class CPlayerGT : public GSLib::LoginSystem::GT::CNetPlayerGT
{
public:
	CPlayerGT(const BSLib::uint64 a_accountID, const std::string& a_accountName);
	virtual ~CPlayerGT();

public:
	virtual bool init();
	virtual void final();

protected:
	virtual void _cbInitPlayer();
	virtual void _cbFinalPlayer();

	virtual void _cbPlayerOnline();
	virtual void _cbPlayerOffline();

};

}//GT

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_GT_PLAYERSYSTEMGT_H__

