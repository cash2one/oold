#ifndef __GFLIB_COMMONSERVER_UNIQUEIDMGR_H__
#define __GFLIB_COMMONSERVER_UNIQUEIDMGR_H__

#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/baseDef.h>

namespace GFLib
{

namespace CommonServer
{

struct SUniqueIDInfor;

class GFLIB_COMMONSERVER_API CUniqueIDMgr
{
public:
	CUniqueIDMgr();
	~CUniqueIDMgr();

	BSLIB_SINGLETON_DECLARE(CUniqueIDMgr);

	bool init();
	void final();

public:
	BSLib::int64 getInt64GlobleUniqueID(BSLib::uint32 a_type);
	BSLib::int64 getInt64ZoneUniqueID(BSLib::uint32 a_type);

private:
	bool _getInt64UniqueID(BSLib::uint32 a_type, BSLib::uint64* a_uniqueID);
	bool _createUniqueID(BSLib::uint32 a_type, bool a_isGloble);
	bool _createUniqueID(SUniqueIDInfor* a_uniqueIDInfor, bool a_isGloble);
	bool _loadUniqueIDFile(SUniqueIDInfor* a_uniqueIDInfor);
	bool _saveUniqueIDFile(BSLib::uint32 a_type, bool isEnd = false);
	bool _saveUniqueIDFile(SUniqueIDInfor* a_uniqueIDInfor);


private:
	BSLib::Utility::CHashMap<BSLib::uint32, SUniqueIDInfor*> m_uniqueIDSeed;
};

}//CommonServer

}//GFLib

#endif//__GFLIB_COMMONSERVER_SYSCHANNELMGR_H__


