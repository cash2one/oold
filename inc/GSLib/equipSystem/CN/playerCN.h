#ifndef __GSLIB_PLAYERSYSTEM_CN_PLAYERCN_H__
#define __GSLIB_PLAYERSYSTEM_CN_PLAYERCN_H__

#include <BSLib/utility/memory/objectMgr.h>
#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonSystem.h>
#include "GSLib/playerSystem/CN/roleCN.h"
#include "GSLib/loginSystem/CN/netPlayerCN.h"

namespace GSLib
{

namespace PlayerSystem
{

namespace CN
{

class CPlayerCN :public GSLib::LoginSystem::CN::CNetPlayerCN
{
public:
	CPlayerCN(const BSLib::uint64 a_accountID, const std::string& a_accountName);
	virtual ~CPlayerCN();

public:
	virtual bool init();
	virtual void final();

	// 继承方法
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

private:
	BSLib::uint64 m_playerID;
	BSLib::uint64 m_nCurRoleIndex;
	BSLib::Utility::CHashMap<BSLib::uint64, CRoleCN*> m_roleHashMap;
};

}//CN

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_CN_PLAYERSYSTEMCN_H__

