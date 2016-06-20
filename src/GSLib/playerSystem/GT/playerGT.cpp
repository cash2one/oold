//////////////////////////////////////////////////////////////////////
//	created:	2014/07/27
//	filename: 	src\GSLib\playerSystem\GT\playerSystemGT.cpp
//	author:		zhangping
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/tracer.h>
#include <GSLib/playerSystem/GT/playerGT.h>


namespace GSLib
{

namespace PlayerSystem
{	

namespace GT
{


CPlayerGT::CPlayerGT(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName)
: GSLib::LoginSystem::GT::CNetPlayerGT(a_accountKey, a_accountName)
{
	;
}

CPlayerGT::~CPlayerGT()
{
	;
}

bool CPlayerGT::init()
{
	return true;
}

void CPlayerGT::final()
{
	;
}

// 初始化玩家信息
void CPlayerGT::_cbInitPlayer()
{
	// 初始化角色列表信息
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "CPlayerGT::_cbInitPlayer");
	GSLib::LoginSystem::GT::CNetPlayerGT::_finishInitPlayer(GSLib::LoginSystem::ELOGINRESULT_SUCCESS);
}
// 底层结束时调用
void CPlayerGT::_cbFinalPlayer()
{
     BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "CPlayerGT::_cbFinalPlayer");
}

// 玩家上线调用
void CPlayerGT::_cbPlayerOnline()
{
   // 设置上线状态
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "CPlayerGT::_cbPlayerOnline");
}

// 玩家下线时调用
void CPlayerGT::_cbPlayerOffline()
{
    // 设置下线状态   
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "CPlayerGT::_cbPlayerOffline");
}

CRoleGT * CPlayerGT::getCurRole()
{
	CRoleGT * role = NULL;
	m_roleHashMap.getValue(0, role);
	return role;
}

}//GT

}//PlayerSystem

}//GSLib
