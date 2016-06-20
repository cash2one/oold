//////////////////////////////////////////////////////////////////////
//	created:	2014/11/12
//	filename: 	src\GFLib\commonServer\uniqueIDMgr.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/file/binFile.h>
#include <BSLib/utility/file/dirInfo.h>
#include <BSLib/utility/file/fileInfo.h>
#include <GFLib/commonServer/commonServer.h>
#include <GFLib/commonServer/tracer.h>
#include <GFLib/commonServer/uniqueIDMgr.h>

#define GFLIB_UNIQUE_ID_NUM_MAX BSLIB_UINT8_MAX

namespace GFLib
{

namespace CommonServer
{

BSLIB_SINGLETON_DEFINE(CUniqueIDMgr);

struct SUniqueIDInfor
{
	BSLib::uint32 m_uniqueIDType;
	BSLib::uint64 m_currectUniqueID;
	BSLib::uint64 m_nextGroupUniqueID;
	std::string m_binFileName;

	//BSLib::Utility::CBinFile m_binFile;

	SUniqueIDInfor()
	{
		m_uniqueIDType = 0;
		m_currectUniqueID = 0;
		m_nextGroupUniqueID = 0;
	}
};

CUniqueIDMgr::CUniqueIDMgr()
{
	;
}

CUniqueIDMgr::~CUniqueIDMgr()
{
	;
}

bool CUniqueIDMgr::init()
{
	CCommonServer* server = GFLib::CommonServer::CCommonServer::getCommonServer();
	if (server == NULL) {
		return false;
	}
	std::string workPath = BSLib::Framework::CSysConfig::singleton().getValueStr("WorkPath");
	if (workPath.empty()) {
		return false;
	}
	std::string dataPath = BSLib::Framework::CSysConfig::singleton().getValueStr("DataPath");
	if (dataPath.empty()) {
		dataPath = workPath + "\\data";
		BSLib::Utility::CDirInfo::standardization(dataPath);
		if (!BSLib::Utility::CDirInfo::isExist(dataPath)) {
			BSLib::Utility::CDirInfo::makeDir(dataPath);
		}
		BSLib::Framework::CSysConfig::singleton().setValue("DataPath", dataPath);
	}
	std::string uniqueIDPath = BSLib::Framework::CSysConfig::singleton().getValueStr("UniqueIDPath");
	if (uniqueIDPath.empty()) {
		uniqueIDPath = dataPath + "\\";
		uniqueIDPath += server->getServerKey();
		BSLib::Utility::CDirInfo::standardization(uniqueIDPath);
		if (!BSLib::Utility::CDirInfo::isExist(uniqueIDPath)) {
			BSLib::Utility::CDirInfo::makeDir(uniqueIDPath);
		}
		BSLib::Framework::CSysConfig::singleton().setValue("UniqueIDPath", uniqueIDPath);
	}
	return true;
}

void CUniqueIDMgr::final()
{
	BSLib::Utility::CHashMap<BSLib::uint32, SUniqueIDInfor*>::iterator it = m_uniqueIDSeed.begin();
	for (; it != m_uniqueIDSeed.end(); ++it) {
		SUniqueIDInfor* uniqueIDInfor = it->second;
		if (uniqueIDInfor == NULL) {
			continue;
		}
		_saveUniqueIDFile(uniqueIDInfor->m_uniqueIDType, true);
		//uniqueIDInfor->m_binFile.close();
		BSLIB_SAFE_DELETE(uniqueIDInfor);
	}
	m_uniqueIDSeed.clear();
}

BSLib::int64 CUniqueIDMgr::getInt64GlobleUniqueID(BSLib::uint32 a_type)
{
	BSLib::uint64 uniqueID = 0;
	if (_getInt64UniqueID(a_type, &uniqueID)) {
		BSLIB_LOG_DEBUG(GFLib::ETT_GFLIB_COMMON, "·ÖÅäGlobleUniqueID[%d][%llX]", a_type, uniqueID);
		return uniqueID;
	}
	if (!_createUniqueID(a_type, true)){
		BSLIB_LOG_ERROR(GFLib::ETT_GFLIB_COMMON, "·ÖÅäÊ§°ÜGlobleUniqueID[%d]", a_type);
		return 0;
	}
	if (_getInt64UniqueID(a_type, &uniqueID)) {
		BSLIB_LOG_DEBUG(GFLib::ETT_GFLIB_COMMON, "·ÖÅäGlobleUniqueID[%d][%llX]", a_type, uniqueID);
		return uniqueID;
	}
	BSLIB_LOG_ERROR(GFLib::ETT_GFLIB_COMMON, "·ÖÅäÊ§°ÜGlobleUniqueID[%d]", a_type);
	return 0;
}

BSLib::int64 CUniqueIDMgr::getInt64ZoneUniqueID(BSLib::uint32 a_type)
{
	CCommonServer* server = GFLib::CommonServer::CCommonServer::getCommonServer();
	if (server == NULL) {
		return 0;
	}
	BSLib::uint8 serverNum = server->getServerID().getServerNumber();
	BSLib::uint64 uniqueID = 0;
	if (_getInt64UniqueID(a_type, &uniqueID)) {
		uniqueID = (uniqueID << 8) + serverNum;
		BSLIB_LOG_DEBUG(GFLib::ETT_GFLIB_COMMON, "·ÖÅäZoneUniqueID[%d][%llX]", a_type, uniqueID);
		return  uniqueID;
	}
	if (!_createUniqueID(a_type, false)){
		BSLIB_LOG_ERROR(GFLib::ETT_GFLIB_COMMON, "·ÖÅäÊ§°ÜZoneUniqueID[%d]", a_type);
		return 0;
	}
	if (_getInt64UniqueID(a_type, &uniqueID)) {
		uniqueID = (uniqueID << 8) + serverNum;
		BSLIB_LOG_DEBUG(GFLib::ETT_GFLIB_COMMON, "·ÖÅäZoneUniqueID[%d][%llX]", a_type, uniqueID);
		return  uniqueID;
	}
	BSLIB_LOG_ERROR(GFLib::ETT_GFLIB_COMMON, "·ÖÅäÊ§°ÜZoneUniqueID[%d]", a_type);
	return 0;
}

bool CUniqueIDMgr::_getInt64UniqueID(BSLib::uint32 a_type, BSLib::uint64* a_uniqueID)
{
	SUniqueIDInfor* uniqueIDInfor = NULL;
	m_uniqueIDSeed.getValue(a_type, uniqueIDInfor);
	if (uniqueIDInfor == NULL) {
		return false;
	}
	if (uniqueIDInfor->m_currectUniqueID >= uniqueIDInfor->m_nextGroupUniqueID) {
		uniqueIDInfor->m_nextGroupUniqueID += GFLIB_UNIQUE_ID_NUM_MAX + 1;
		_saveUniqueIDFile(a_type);
	}
	*a_uniqueID = uniqueIDInfor->m_currectUniqueID;
	uniqueIDInfor->m_currectUniqueID += 1;
	return true;
}

bool CUniqueIDMgr::_createUniqueID(BSLib::uint32 a_type, bool a_isGloble)
{
	std::string uniqueIDPath = BSLib::Framework::CSysConfig::singleton().getValueStr("UniqueIDPath");
	if (uniqueIDPath.empty()) {
		return false;
	}
	BSLib::Utility::CStringA uniqueIDFile;
	uniqueIDFile.format("%s\\%d.data", uniqueIDPath.c_str(), a_type);
	BSLib::Utility::CDirInfo::standardization(uniqueIDFile);

	SUniqueIDInfor* uniqueIDInfor = new SUniqueIDInfor();
	if (uniqueIDInfor == NULL) {
		return false;
	}
	uniqueIDInfor->m_uniqueIDType = a_type;
	uniqueIDInfor->m_binFileName = uniqueIDFile;

	if (_loadUniqueIDFile(uniqueIDInfor)) {
		m_uniqueIDSeed.setValue(a_type, uniqueIDInfor);
		return true;
	}
	if (_createUniqueID(uniqueIDInfor, a_isGloble)) {
		_saveUniqueIDFile(uniqueIDInfor);
		m_uniqueIDSeed.setValue(a_type, uniqueIDInfor);
		return true;
	}
	BSLIB_SAFE_DELETE(uniqueIDInfor);
	return false;
}

bool CUniqueIDMgr::_createUniqueID(SUniqueIDInfor* a_uniqueIDInfor, bool a_isGloble)
{
	CCommonServer* server = GFLib::CommonServer::CCommonServer::getCommonServer();
	if (server == NULL) {
		return false;
	}
	if (a_isGloble) {
		ZoneID serverZoneID = server->getServerID().getZoneID();
		BSLib::uint8 serverNum = server->getServerID().getServerNumber();
		BSLib::uint64 currentSeconds = BSLib::Utility::CDateTime::getCurrentTime().getSeconds();
		a_uniqueIDInfor->m_currectUniqueID = ((BSLib::uint64)serverZoneID << 48) + ((BSLib::uint64)serverNum << 40) + (currentSeconds << 8);
		a_uniqueIDInfor->m_nextGroupUniqueID = a_uniqueIDInfor->m_currectUniqueID;
		a_uniqueIDInfor->m_nextGroupUniqueID += GFLIB_UNIQUE_ID_NUM_MAX + 1;
	} else {
		a_uniqueIDInfor->m_currectUniqueID = 0;
		a_uniqueIDInfor->m_nextGroupUniqueID = a_uniqueIDInfor->m_currectUniqueID;
		a_uniqueIDInfor->m_nextGroupUniqueID += GFLIB_UNIQUE_ID_NUM_MAX + 1;
	}
	
	return true;
}


bool CUniqueIDMgr::_loadUniqueIDFile(SUniqueIDInfor* a_uniqueIDInfor)
{
	BSLib::Utility::CBinFile binFile;
	if (!binFile.open(a_uniqueIDInfor->m_binFileName)) {
		return false;
	}
	BSLib::int32 readSize = binFile.read(&a_uniqueIDInfor->m_nextGroupUniqueID, sizeof(a_uniqueIDInfor->m_nextGroupUniqueID));
	if (readSize != sizeof(a_uniqueIDInfor->m_nextGroupUniqueID)) {
		binFile.close();
		return false;
	}
	readSize = binFile.read(&a_uniqueIDInfor->m_currectUniqueID, sizeof(a_uniqueIDInfor->m_currectUniqueID));
	if (readSize != sizeof(a_uniqueIDInfor->m_currectUniqueID)) {
		binFile.close();
		return false;
	}
	if (a_uniqueIDInfor->m_currectUniqueID == 0) {
		a_uniqueIDInfor->m_currectUniqueID = a_uniqueIDInfor->m_nextGroupUniqueID;
	}
	binFile.close();
	return true;
}

bool CUniqueIDMgr::_saveUniqueIDFile(BSLib::uint32 a_type, bool a_isEnd)
{
	SUniqueIDInfor* uniqueIDInfor = NULL;
	m_uniqueIDSeed.getValue(a_type, uniqueIDInfor);
	if (uniqueIDInfor == NULL) {
		return false;
	}
	BSLib::Utility::CBinFile binFile;
	if (!binFile.open(uniqueIDInfor->m_binFileName)) {
		return false;
	}
	BSLib::uint64 currentUniqueID = 0;
	if (a_isEnd) {
		currentUniqueID = uniqueIDInfor->m_currectUniqueID;
	}
	binFile.write(&uniqueIDInfor->m_nextGroupUniqueID, sizeof(uniqueIDInfor->m_nextGroupUniqueID));
	binFile.write(&currentUniqueID, sizeof(currentUniqueID));
	binFile.close();
	return true;
}

bool CUniqueIDMgr::_saveUniqueIDFile(SUniqueIDInfor* a_uniqueIDInfor)
{
	BSLib::Utility::CBinFile binFile;
	if (!binFile.create(a_uniqueIDInfor->m_binFileName)) {
		return false;
	}
	BSLib::uint64 currentUniqueID = 0;
	binFile.write(&a_uniqueIDInfor->m_nextGroupUniqueID, sizeof(a_uniqueIDInfor->m_nextGroupUniqueID));
	binFile.write(&currentUniqueID, sizeof(currentUniqueID));
	binFile.close();
	return true;
}

}//CommonServer

}//GFLib