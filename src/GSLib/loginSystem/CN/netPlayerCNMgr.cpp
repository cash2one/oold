//////////////////////////////////////////////////////////////////////
//	created:	2014/07/28
//	filename: 	GSLib\loginSystem\CN\netPlayerCNMgr.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/loginSystem/CN/netPlayerCNMgr.h>

namespace GSLib
{

namespace LoginSystem
{

namespace CN
{

CNetPlayerCNMgr* CNetPlayerCNMgr::m_singleton = NULL;

CNetPlayerCNMgr::CNetPlayerCNMgr()
{
	m_singleton = this;
}

CNetPlayerCNMgr::~CNetPlayerCNMgr()
{
	m_singleton = NULL;
}

}//CN

}//LoginSystem

}//GSLib
