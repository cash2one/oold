//////////////////////////////////////////////////////////////////////
//	created:	2014/07/28
//	filename: 	GSLib\loginSystem\GM\netPlayerGMMgr.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_LOGINSYSTEM_GM_NETPLAYERGMMGR_H__
#define __GSLIB_LOGINSYSTEM_GM_NETPLAYERGMMGR_H__

#include <GSLib/loginSystem/GM/netPlayerGM.h>

namespace GSLib
{

namespace PlayerSystem
{

namespace GM
{

class GNetPlayerGMMgr
{
public:
	GNetPlayerGMMgr();
	virtual ~GNetPlayerGMMgr();

	virtual GNetPlayerGM* createNetPlayerGM(const BSLib::uint64 a_accountID, const std::string& a_accountName) = 0;
	virtual GNetPlayerGM* getNetPlayerGM(BSLib::uint64 a_accountID) = 0;

public:
	static GNetPlayerGMMgr* getSingleton() { return m_singleton; }

private:
	static GNetPlayerGMMgr* m_singleton;
};

}//GM

}//LoginSystem

}//GSLib

#endif//__GSLIB_LOGINSYSTEM_GM_NETPLAYERGMMGR_H__