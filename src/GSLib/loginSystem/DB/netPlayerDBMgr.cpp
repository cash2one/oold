#include <GSLib/loginSystem/DB/netPlayerDBMgr.h>

namespace GSLib
{

namespace LoginSystem
{

namespace DB
{

CNetPlayerDBMgr* CNetPlayerDBMgr::m_singleton = NULL;

CNetPlayerDBMgr::CNetPlayerDBMgr()
{
	m_singleton = this;
}

CNetPlayerDBMgr::~CNetPlayerDBMgr()
{
	m_singleton = NULL;
}

}//DB

}//LoginSystem

}//GSLib

