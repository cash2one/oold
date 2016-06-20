//////////////////////////////////////////////////////////////////////
//	created:	2015/07/02
//	filename: 	BSLib\utility\file\gameData.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UTILITY_GAMEDATA_H__
#define __BSLIB_UTILITY_GAMEDATA_H__

#include <BSLib/utility/stream.h>

namespace BSLib
{

namespace Utility
{

class CGameData
{
public:
	virtual ~CGameData(){}

protected:
	virtual bool _parseGameData(const std::string& a_name, int a_size, BSLib::Utility::CStream& a_stream) = 0;

	friend class CGameDataMgr;
};

class CGameDataMgr
{
public:
	CGameDataMgr();
	~CGameDataMgr();

	bool loadBINFile(const std::string& a_filePath);

protected:
	virtual CGameData* _createGameData() = 0;
	virtual bool _addGameData(CGameData* a_data) = 0;

};

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_GAMEDATA_H__
