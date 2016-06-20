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

// ��ʼ�������Ϣ
void CPlayerGT::_cbInitPlayer()
{
	// ��ʼ����ɫ�б���Ϣ
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "CPlayerGT::_cbInitPlayer");
	GSLib::LoginSystem::GT::CNetPlayerGT::_finishInitPlayer(GSLib::LoginSystem::ELOGINRESULT_SUCCESS);
}
// �ײ����ʱ����
void CPlayerGT::_cbFinalPlayer()
{
     BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "CPlayerGT::_cbFinalPlayer");
}

// ������ߵ���
void CPlayerGT::_cbPlayerOnline()
{
   // ��������״̬
	BSLIB_LOG_DEBUG(ETT_GSLIB_PLAYERSYSTEM, "CPlayerGT::_cbPlayerOnline");
}

// �������ʱ����
void CPlayerGT::_cbPlayerOffline()
{
    // ��������״̬   
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
