//////////////////////////////////////////////////////////////////////
//	created:	2014/12/18
//	filename: 	src\GSLib\loginSystem\SP\accountTokenInforMgr.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_LOGINSYSTEM_SP_ACCOUNTTOKENINFORMGR_H__
#define __GSLIB_LOGINSYSTEM_SP_ACCOUNTTOKENINFORMGR_H__

#include <BSLib/utility/memory/objectMgr.h>
#include <BSLib/utility/uniqueID.h>
#include <GFLib/commonServer/baseDef.h>
#include <GSLib/loginSystem/msgLoginSystem.h>

namespace GSLib
{

namespace LoginSystem
{

namespace SP
{

//////////////////////////////////////////////////////////////////////////
struct SAccountTokenInfor
{
	std::string m_token;
	std::string m_accountName;
	GFLib::SAccountKey m_accountKey;
};

//////////////////////////////////////////////////////////////////////////
class CAccountTokenInforMgr
{
public:
	CAccountTokenInforMgr();
	~CAccountTokenInforMgr();

	BSLIB_SINGLETON_DECLARE(CAccountTokenInforMgr);

public:
	bool registerAccountTokenInfor(SAccountTokenInfor& a_accountInfor);
	bool checkAccountTokenInfor(SAccountTokenInfor& a_accountInfor);
    //bool updateAccountTokenInfor(SAccountTokenInfor& a_accountInfor);

private:
	//BSLib::Utility::CHashMap<std::string, SAccountTokenInfor*> m_accountInforMgr;

	BSLib::Utility::CHashMap<GFLib::AccountID, SAccountTokenInfor*> m_accountInforMgr;
};

}//LG

}//LoginSystem

}//GSLib


#endif//__GSLIB_LOGINSYSTEM_SP_ACCOUNTTOKENINFORMGR_H__