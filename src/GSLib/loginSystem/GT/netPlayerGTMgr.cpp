#include <GSLib/loginSystem/GT/netPlayerGTMgr.h>

namespace GSLib
{

namespace LoginSystem
{

namespace GT
{

CNetPlayerGTMgr* CNetPlayerGTMgr::m_singleton = NULL;

CNetPlayerGTMgr::CNetPlayerGTMgr()
{
	m_singleton = this;
}

CNetPlayerGTMgr::~CNetPlayerGTMgr()
{
	m_singleton = NULL;
}

}//GT

}//LoginSystem

}//GSLib

