//////////////////////////////////////////////////////////////////////
//	created:	2015/07/03
//	filename: 	src\BSLib\utility\file\gameData.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/file/gameData.h>
#include <BSLib/utility/stream.h>
#include <BSLib/utility/file/binFile.h>
#include <BSLib/utility/tracer.h>

#define BUFF_MAX (1024 *4)

namespace BSLib
{

namespace Utility
{

enum EDataType
{
	EDT_NULL,
	EDT_INT8,
	EDT_INT16,
	EDT_INT32,
	EDT_INT64,
	EDT_UINT8,
	EDT_UINT16,
	EDT_UINT32,
	EDT_UINT64,
	EDT_FLOAT,
	EDT_DOUBLE,
	EDT_STRING,
	EDT_INT8S,
	EDT_INT16S,
	EDT_INT32S,
	EDT_INT64S,
	EDT_UINT8S,
	EDT_UINT16S,
	EDT_UINT32S,
	EDT_UINT64S,
	EDT_FLOATS,
	EDT_DOUBLES,
	EDT_STRINGS,
};

//////////////////////////////////////////////////////////////////////////

struct SGameDataItem
{
	std::string m_name;
	EDataType m_type;
	int32 m_size;
};

//////////////////////////////////////////////////////////////////////////
CGameDataMgr::CGameDataMgr()
{
	;
}

CGameDataMgr::~CGameDataMgr()
{
	;
}

bool CGameDataMgr::loadBINFile(const std::string& a_filePath)
{
	CBinFile binFile;
	if (!binFile.open(a_filePath)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "打开文件[%s]失败", a_filePath.c_str());
		return false;
	}
	CStream stream;
	int8 buff[BUFF_MAX];
	BSLib::int32 readSize = 0;
	do {
		readSize = binFile.read(buff, BUFF_MAX);
		if (readSize <= 0) {
			break;
		}
		stream.write(buff, readSize);
	} while (readSize >= BUFF_MAX);
	binFile.close();

	std::vector<SGameDataItem> head;
	int count = 0;
	try {
		stream >> count;
		for (int i=0; i<count; ++i) {
			SGameDataItem item;
			stream >> item.m_name;
			stream >> item.m_type;
			stream >> item.m_size;
			head.push_back(item);
		}
	} catch (CException) {
		BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "解析文件[%s]失败", a_filePath.c_str());
		return false;
	}

	while (stream.readReady()) {
		CGameData* data = _createGameData();
		if (data == NULL) {
			return false;
		}
		for (int i=0; i<count; ++i) {
			const SGameDataItem& headItem = head[i];
			try {
				if (!data->_parseGameData(headItem.m_name, headItem.m_size, stream)) {
					BSLIB_SAFE_DELETE(data);
					return false;
				}
			} catch (CException) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "解析文件[%s]失败", a_filePath.c_str());
				BSLIB_SAFE_DELETE(data);
				return false;
			}
		}
		_addGameData(data);
	}
	return true;
}

}//Utility

}//BSLib
