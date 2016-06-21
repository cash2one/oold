#include <GSLib/loginSystem/GM/netPlayerGMMgr.h>

namespace GSLib
{

namespace LoginSystem
{

namespace GM
{

CNetPlayerGMMgr* CNetPlayerGMMgr::m_singleton = NULL;

CNetPlayerGMMgr::CNetPlayerGMMgr()
{
	m_singleton = this;
}

CNetPlayerGMMgr::~CNetPlayerGMMgr()
{
	m_singleton = NULL;
}

}//GM

}//LoginSystem

}//GSLib

