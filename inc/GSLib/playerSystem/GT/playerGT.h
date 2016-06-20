//////////////////////////////////////////////////////////////////////
//	created:	2014/07/25
//	filename: 	GSLib\playerSystem\GT\CPlayerGT.h
//	author:	     zhangping	
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
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
	CPlayerGT(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName);
	virtual ~CPlayerGT();

public:
	virtual bool init();
	virtual void final();

protected:
	virtual void _cbInitPlayer();
	virtual void _cbFinalPlayer();

	virtual void _cbPlayerOnline();
	virtual void _cbPlayerOffline();
public:
	void setCurRoleIndex(BSLib::uint64 a_curRoleIndex){ m_nCurRoleIndex = a_curRoleIndex; }
	void setPlayerID(BSLib::uint64 a_playerID){ m_playerID = a_playerID; }

	//角色相关接口
public:
	BSLib::uint64 getCurRoleIndex(){ return m_nCurRoleIndex; }
	BSLib::uint64 getPlayerID(){ return m_playerID; }

	CRoleGT * getCurRole();

private:
	BSLib::uint64 m_playerID;
	BSLib::uint64 m_nCurRoleIndex;
	BSLib::Utility::CHashMap<BSLib::uint64, CRoleGT*> m_roleHashMap;
};

}//GT

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_GT_PLAYERSYSTEMGT_H__
