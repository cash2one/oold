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

