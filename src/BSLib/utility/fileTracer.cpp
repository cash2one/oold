#include <stdarg.h>
#include <time.h>
#include <BSLib/utility/fileTracer.h>
#include <BSLib/utility/file/fileInfo.h>
#include <BSLib/utility/string.h>
#include <BSLib/utility/ptrQueue.h>
#include <BSLib/utility/thread/threadData.h>
#include <BSLib/utility/thread/mutex.h>
#include <BSLib/utility/thread/event.h>
#include <BSLib/utility/thread/thread.h>

#ifdef WIN32

#include "win32/ConsoleAdapter.h"

ConsoleAdapter g_ConsoleAdapter;

#endif

#define TRACE_BUFF_MAX (1024 * 512)

namespace BSLib
{

namespace Utility
{

struct STracerItem
{
	int m_fileTracerPos;
	uint16 m_type;
	CTracer::ETracerLevel m_level;
	std::string m_file;
	int m_line;
	std::string m_text;
};

struct STracerChannel
{
	CPtrQueue<STracerItem*> m_tracerQueue;
	CPtrQueue<STracerItem*> m_recycleQueue;
};

CThreadData g_thdDataTracerChannel;

class CTracerThread : public BSLib::Utility::CThread
{
public:
	CTracerThread() : m_isRunning(false)
	{
		;
	}

	~CTracerThread()
	{
		std::vector<STracerChannel*>::iterator it = m_tracerChannels.begin();
		for (; it != m_tracerChannels.end(); ++it) {
			STracerChannel* channel = *it;
			if (channel == NULL){
				continue;
			}
			STracerItem* item = NULL;
			while (channel->m_tracerQueue.pop(item)){
				if (item != NULL) {
					BSLIB_SAFE_DELETE(item);
				}
			}
			channel->m_tracerQueue.clear();
			while (channel->m_recycleQueue.pop(item)){
				if (item != NULL) {
					BSLIB_SAFE_DELETE(item);
				}
			}
			channel->m_recycleQueue.clear();
			BSLIB_SAFE_DELETE(channel);
		}
		m_tracerChannels.clear();
	}
	
// 	int addFileTracer(CFileTracer* fileTracer)
// 	{
// 		m_mutex.lock();
// 
// 		int pos = addFileTracer(fileTracer);
// 
// 		m_mutex.unlock();
// 
// 		return pos - 1;
// 	}

	void delFileTracer(int pos)
	{
		m_mutex.lock();
		if (pos < 0 || pos >= (int)m_fileTracers.size()) {
			m_mutex.unlock();
			return;
		}
		
		_outAllTracer(false);
		
		m_fileTracers[pos] = NULL;

		for (int i=0; i<(int)m_fileTracers.size(); ++i){
			if (m_fileTracers[i] != NULL){
				m_mutex.unlock();
				return ;
			}
		}
		m_isRunning = false;
		m_mutex.unlock();

		m_event.set();

		BSLib::Utility::CThread::join();
	}

	void notify()
	{
		m_event.set();
	}

	STracerChannel* getCurrentThreadTracerChannel()
	{
		STracerChannel* tracerChannel = (STracerChannel*)g_thdDataTracerChannel.get();
		if (tracerChannel != NULL) {
			return tracerChannel;
		}
		tracerChannel = new STracerChannel();
		if (tracerChannel == NULL) {
			return NULL;
		}

		m_mutex.lock();
		m_tracerChannels.push_back(tracerChannel);
		m_mutex.unlock();
		
		g_thdDataTracerChannel.set(tracerChannel);

		return tracerChannel;
	}

	CRealTime& getRealTimer() { return m_realTime; }

	void outAllTracer()
	{
		m_mutex.lock();
		_outAllTracer(false);
		m_mutex.unlock();
	}

	bool setOutFile(CFileTracer* fileTracer, const char* fileName, ELogFileSplitType splitType)
	{
		BSLib::Utility::CMutexFun fun(&m_mutex);

		if (fileTracer->m_fileTracer != NULL) {
			_outAllTracer(false);

			fclose(fileTracer->m_fileTracer);
			fileTracer->m_fileTracer = NULL;
		}

		std::string strFileName = fileName;
		CFileInfo::standardization(strFileName);
		FILE* fp = fopen(strFileName.c_str(), "a+");
		if (fp == NULL){
			printf("%s\n", strerror(errno));
			return false;
		}

		fileTracer->m_fileName = strFileName;
		fileTracer->m_fileTracer = fp;
		fileTracer->m_splitType = splitType;
		fileTracer->m_fileMaxSize = 0;

		long fileSize = CFileInfo::getLength(fileTracer->m_fileName);
		if (fileSize > 0) {
			CDateTime dateTime;
			CFileInfo::getLastModifyTime(fileTracer->m_fileName, dateTime);
			fileTracer->_splitFileByTime(ELFST_SECOND, dateTime);
		}
		fileTracer->_setDelayTime();

		fileTracer->m_tracerID = _addFileTracer(fileTracer);

		return true;
	}

	bool setOutFile(CFileTracer* fileTrace, const char* fileName, BSLib::int32 fileMaxSize)
	{
		BSLib::Utility::CMutexFun fun(&m_mutex);

		if (fileTrace->m_fileTracer != NULL) {
			_outAllTracer(false);

			fclose(fileTrace->m_fileTracer);
			fileTrace->m_fileTracer = NULL;
		}

		std::string strFileName = fileName;
		CFileInfo::standardization(strFileName);
		FILE* fp = fopen(strFileName.c_str(), "a+");
		if (fp == NULL){
			return false;
		}

		fileTrace->m_fileName = fileName;
		CFileInfo::standardization(fileTrace->m_fileName);

		fileTrace->m_fileTracer = fp;
		fileTrace->m_splitType = ELFST_ERROR;
		fileTrace->m_fileMaxSize = fileMaxSize * 1024;

		fileTrace->m_tracerID = _addFileTracer(fileTrace);

		return true;
	}

protected:
	virtual void _run()
	{
		m_delayTime.reset(200, m_realTime);

		while (m_isRunning) {
			m_realTime.now();

			int res = m_event.wait(1);
			if (res == -2) {
				break;
			} else if (res == -1) {
				m_mutex.lock();
				_writeTracer(true);
				m_mutex.unlock();
				continue;
			}
			m_event.reset();

			m_mutex.lock();
			_outAllTracer(true);
			m_mutex.unlock();
		}
		m_isRunning = false;
	}

private:

	void _outAllTracer(bool a_needDelay)
	{
		bool flag = false;
		do {
			flag = false;
			std::vector<STracerChannel*>::iterator it = m_tracerChannels.begin();
			for (; it != m_tracerChannels.end(); ++it) {
				STracerChannel* channel = *it;
				if (channel == NULL){
					continue;
				}
				int count = 0;
				STracerItem* item = NULL;
				while (channel->m_tracerQueue.pop(item)){
					if (item == NULL) {
						continue;
					}
					if (item->m_fileTracerPos < 0 || item->m_fileTracerPos >= (int)m_fileTracers.size()) {
						item->m_fileTracerPos = -1;
						channel->m_recycleQueue.push(item);
						continue;
					}
					CFileTracer* fileTracer = m_fileTracers[item->m_fileTracerPos];
 					if (fileTracer != NULL) {
 						fileTracer->_outTrace(item);
							if (fileTracer->m_writeBuffToFile.readSize() > TRACE_BUFF_MAX) {
								fileTracer->_writeToFile();
							}
							if (fileTracer->m_writeBuffToConsole.readSize() > TRACE_BUFF_MAX) {
								fileTracer->_writeToConsole();
							}
 					}
					item->m_fileTracerPos = -1;
					channel->m_recycleQueue.push(item);

					count++;
					if (count > 100000) {
						flag = true;
						break;
					}
				}
			}
		} while (flag);
		
		_writeTracer(a_needDelay);
	}

	void _writeTracer(bool a_needDelay)
	{
		if (a_needDelay) {
			if (m_delayTime(m_realTime, 200)) {
				for (BSLib::uint32 i=0; i<m_fileTracers.size(); ++i)	{
					CFileTracer* fileTracer = m_fileTracers[i];
					if (fileTracer == NULL) {
						continue;
					}
					fileTracer->_writeToFile();
					fileTracer->_writeToConsole();
				}
			}
		} else {
			for (BSLib::uint32 i=0; i<m_fileTracers.size(); ++i)	{
				CFileTracer* fileTracer = m_fileTracers[i];
				if (fileTracer == NULL) {
					continue;
				}
				fileTracer->_writeToFile();
				fileTracer->_writeToConsole();
			}
		}
	}

	int _addFileTracer(CFileTracer* fileTracer)
	{
		if (m_fileTracers.empty()) {
			m_isRunning = true;
			BSLib::Utility::CThread::start();
		}

		m_fileTracers.push_back(fileTracer);
		int pos = (int)m_fileTracers.size();

		return pos - 1;
	}

private:
	bool m_isRunning;
	CEvent m_event;
	CMutex m_mutex;
	std::vector<STracerChannel*> m_tracerChannels;
	std::vector<CFileTracer*> m_fileTracers;
	CRealTime m_realTime;
	CDelayTimer m_delayTime;
};

CTracerThread g_tracerThread;

//////////////////////////////////////////////////////////////////////////

int CFileTracer::m_fileMaxCount = 13;

CFileTracer::CFileTracer() 
: m_fileTracer(NULL)
, m_outToConsole(false)
, m_tracerID(-1)
, m_fileMaxSize(0)
, m_splitType(ELFST_ERROR)
, m_splitDelayTime(0)
, m_outConsoleLevel(CTracer::ETL_DEBUG)
, m_filter(&m_filterResult, false)
{
	;
}

CFileTracer::~CFileTracer()
{
	;
}

void CFileTracer::setOutConsole(bool outToConsole, ETracerLevel outConsoleLevel)
{
#ifdef WIN32

	if (!m_outToConsole && outToConsole){
		if (g_ConsoleAdapter.CreateConsole(BOTH)) {
			m_outToConsole = true;
		}
	}
	if (m_outToConsole && !outToConsole){
		g_ConsoleAdapter.DestroyConsole();
		m_outToConsole = false;
	}

#elif defined(_LINUX)

	m_outToConsole = outToConsole;

#else

#error "Unknown platform !!"  

#endif

	m_outConsoleLevel = outConsoleLevel;
}

void CFileTracer::setOutConsole(bool outToConsole, const char* outConsoleLevel)
{
	const char* levelName[] = {"debug", "trace", "warn", "infor", "error", "fatal"};
	for (int i = 0; i < ETL_MAX; i++){
		if (strcmp(levelName[i], outConsoleLevel) == 0){
			setOutConsole(outToConsole, (CTracer::ETracerLevel)i);
			break;
		}
	}
}

bool CFileTracer::setOutFile(const char* fileName, ELogFileSplitType splitType)
{
	if (fileName == NULL) {
		return false;
	}
	int tracerID = m_tracerID;
	if (!g_tracerThread.setOutFile(this, fileName, splitType)) {
		return false;
	}
	if (tracerID != -1) {
		g_tracerThread.delFileTracer(tracerID);
	}
	return true;
}

bool CFileTracer::setOutFile(const char* fileName, BSLib::int32 fileMaxSize)
{
	if (fileName == NULL) {
		return false;
	}
	int tracerID = m_tracerID;
	if (!g_tracerThread.setOutFile(this, fileName, fileMaxSize)) {
		return false;
	}
	if (tracerID != -1) {
		g_tracerThread.delFileTracer(tracerID);
	}
	return true;
}

void CFileTracer::close()
{
	if (m_fileTracer != NULL) {
		g_tracerThread.delFileTracer(m_tracerID);
		
		fclose(m_fileTracer);
		m_fileTracer = NULL;
		m_tracerID = -1;
	}
#ifdef WIN32
	if (m_outToConsole) {
		g_ConsoleAdapter.DestroyConsole();
	}
#endif
	m_outToConsole = false;
}

void CFileTracer::_outTrace(uint16 type, CTracer::ETracerLevel level, const char* file, int line, const char* format, va_list ap)
{
	if (m_tracerID < 0) {
		return ;
	}
	STracerChannel* tracerChannel = g_tracerThread.getCurrentThreadTracerChannel();
	if (tracerChannel == NULL) {
		return ;
	}
	STracerItem* item = NULL;
	tracerChannel->m_recycleQueue.pop(item);
	if (item == NULL){
		item = new STracerItem();
		if (item == NULL){
			return ;
		}	
	}
	item->m_type = type;
	item->m_file = file;
	item->m_level = level;
	item->m_line = line;
	item->m_fileTracerPos = m_tracerID;

	stringFormat(item->m_text, format, ap);

	tracerChannel->m_tracerQueue.push(item);
	g_tracerThread.notify();
}

void CFileTracer::_outTrace(STracerItem* item)
{
	const char* levelName[] = {"DEBUG", "TRACE", "WARN", "INFOR", "ERROR", "FATAL"};

	CDateTime dateTime = CDateTime::getCurrentTime();
	const std::string& typeName = CTracer::_getTypeName(item->m_type);
	if (!m_filter.empty()) {
		bool res = m_filter(dateTime, item->m_level, item->m_text, item->m_file, item->m_line);
		if (res) {
			return;
		}
	}
	if (m_fileMaxSize != 0) {
		long fileSize = ::ftell(m_fileTracer);
		if (fileSize > m_fileMaxSize) {
			_splitFileBySize();
		}
	} else if (m_splitType != ELFST_ERROR) {
		if (m_splitDelayTime(g_tracerThread.getRealTimer())) {
			time_t spanTime;
			switch (m_splitType){
			case ELFST_SECOND:
				{
					spanTime = 1;
					break;
				}
			case ELFST_MINUTE:
				{
					spanTime = 60;
					break;
				}
			case ELFST_DAY:
				{
					spanTime = 60 * 60 * 24;
					break;
				}
			case ELFST_HOUR:
			default:
				{
					spanTime = 60 * 60;
					break;
				}
			}
			CDateTime tmp = dateTime - spanTime;
			_splitFileByTime(m_splitType, tmp);
		}
	}

	if (item->m_level >= CTracer::ETL_MAX)	{
		item->m_level = CTracer::ETL_ERROR;
	}
	if (m_fileTracer != NULL) {
		CStringA tempString;
//#ifdef _WIN32
//
		tempString.format("[%04d-%02d-%02d %02d:%02d:%02d][%s][%s]%s[%s(%d)]\n",
			dateTime.getYear(),
			dateTime.getMonth(),
			dateTime.getDay(),
			dateTime.getHour(),
			dateTime.getMinute(),
			dateTime.getSecond(),
			levelName[item->m_level],
			typeName.c_str(),
			item->m_text.c_str(),
			item->m_file.c_str(),
			item->m_line);

// #else
// 
// 		tempString.format("[%04d-%02d-%02d %02d:%02d:%02d][%s][%s]%s[%s(%d)]\n",
// 			dateTime.getYear(),
// 			dateTime.getMonth(),
// 			dateTime.getDay(),
// 			dateTime.getHour(),
// 			dateTime.getMinute(),
// 			dateTime.getSecond(),
// 			levelName[item->m_level],
// 			typeName.c_str(),
// 			item->m_text.c_str(),
// 			item->m_file.c_str(),
// 			item->m_line);
// 
// #endif
		m_writeBuffToFile.push(tempString.c_str(), (uint32)tempString.size());
	}

	if (m_outToConsole && item->m_level >= m_outConsoleLevel){
		CStringA tempString;
		tempString.format("[%s]%s\n", levelName[item->m_level], item->m_text.c_str());

		m_writeBuffToConsole.push(tempString.c_str(), (uint32)tempString.size());
	}	
}

void CFileTracer::_splitFileBySize()
{
	std::string filePath = CFileInfo::getFullPath(m_fileName);
	std::string fileName = CFileInfo::getName(m_fileName);
	std::string fileExtension = CFileInfo::getExtension(m_fileName);

	std::string pathFileNameTmp = filePath + "\\" + fileName + "_";
	CFileInfo::standardization(pathFileNameTmp);

	int i_index = 1;
	for(; i_index < m_fileMaxCount; ++i_index) {
		CStringA pathFileName;
		pathFileName.format("%s%d.%s", pathFileNameTmp.c_str(), i_index, fileExtension.c_str());

		if(!CFileInfo::isExist(pathFileName)) {
			break;
		}
	}
	if(i_index >= m_fileMaxCount) {
		i_index = 1;
	}

	CStringA newPathFileName;
	newPathFileName.format("%s%d.%s", pathFileNameTmp.c_str(), i_index, fileExtension.c_str());

	::fflush(m_fileTracer);
	::fclose(m_fileTracer);
	if (CFileInfo::isExist(newPathFileName)) {
		CFileInfo::deleteFile(newPathFileName);
	}
	CFileInfo::renameFile(newPathFileName, m_fileName);

	int i_index_next = (i_index + 1) % m_fileMaxCount;
	if(i_index != i_index_next) {
		CStringA delPathFileName;
		delPathFileName.format("%s%d.%s", pathFileNameTmp.c_str(), i_index_next, fileExtension.c_str());
		if (CFileInfo::isExist(delPathFileName)) {
			CFileInfo::deleteFile(delPathFileName);
		}
	}
	m_fileTracer = fopen(m_fileName.c_str(), "a+");
}

void CFileTracer::_splitFileByTime(ELogFileSplitType splitType, CDateTime& dateTime)
{
	std::string filePath = CFileInfo::getFullPath(m_fileName);
	std::string fileName = CFileInfo::getName(m_fileName);
	std::string fileExtension = CFileInfo::getExtension(m_fileName);

	std::string pathFileNameTmp = filePath + "\\" + fileName + "_";
	CFileInfo::standardization(pathFileNameTmp);

	CStringA newPathFileName;
	switch (splitType){
	case ELFST_SECOND:
		{
			newPathFileName.format("%s%04d_%02d_%02d_%02d_%02d_%02d.%s", 
				pathFileNameTmp.c_str(), 
				dateTime.getYear(),
				dateTime.getMonth(),
				dateTime.getDay(),
				dateTime.getHour(),
				dateTime.getMinute(),
				dateTime.getSecond(),
				fileExtension.c_str());
			break;
		}
	case ELFST_MINUTE:
		{
			newPathFileName.format("%s%04d_%02d_%02d_%02d_%02d.%s", 
				pathFileNameTmp.c_str(), 
				dateTime.getYear(),
				dateTime.getMonth(),
				dateTime.getDay(),
				dateTime.getHour(),
				dateTime.getMinute(),
				fileExtension.c_str());
			break;
		}
	case ELFST_DAY:
		{
			newPathFileName.format("%s%04d_%02d_%02d.%s", 
				pathFileNameTmp.c_str(), 
				dateTime.getYear(),
				dateTime.getMonth(),
				dateTime.getDay(),
				fileExtension.c_str());
			break;
		}
	case ELFST_HOUR:
	default:
		{
			newPathFileName.format("%s%04d_%02d_%02d_%02d.%s", 
				pathFileNameTmp.c_str(), 
				dateTime.getYear(),
				dateTime.getMonth(),
				dateTime.getDay(),
				dateTime.getHour(),
				fileExtension.c_str());
			break;
		}
	}

	::fflush(m_fileTracer);
	::fclose(m_fileTracer);
	if (CFileInfo::isExist(newPathFileName)) {
		CFileInfo::deleteFile(newPathFileName);
	}
	CFileInfo::renameFile(newPathFileName, m_fileName);

	m_fileTracer = fopen(m_fileName.c_str(), "a+");

	_setDelayTime();
}

void CFileTracer::_setDelayTime()
{
	CDateTime dateTime = CDateTime::getCurrentTime();
	switch (m_splitType){
	case ELFST_SECOND:
		{
			int period = 1000;
			int dueTime = period - (g_tracerThread.getRealTimer().milliseconds() % 1000);
			m_splitDelayTime.reset(dueTime, g_tracerThread.getRealTimer());
			break;
		}
	case ELFST_MINUTE:
		{
			int period = 1000 * 60;
			int dueTime = period - dateTime.getSecond() * 1000;
			m_splitDelayTime.reset(dueTime, g_tracerThread.getRealTimer());
			break;
		}
	case ELFST_DAY:
		{
			int period = 1000 * 60 * 60 * 24;
			int dueTime = period - (dateTime.getHour() * 60 * 60 * 1000 + dateTime.getMinute() * 60 * 1000 + dateTime.getSecond() * 1000);
			m_splitDelayTime.reset(dueTime, g_tracerThread.getRealTimer());
			break;
		}
	case ELFST_HOUR:
	default:
		{
			int period = 1000 * 60 * 60;
			int dueTime = period - (dateTime.getMinute() * 60 * 1000 + dateTime.getSecond() * 1000);
			m_splitDelayTime.reset(dueTime, g_tracerThread.getRealTimer());
			break;
		}
	}
}

void CFileTracer::_writeToFile()
{
	if (m_fileTracer != NULL) {
		BSLib::uint32 readSize = m_writeBuffToFile.readSize();
		if (readSize > 0) {
			BSLib::uint32 writeSize = (BSLib::uint32)fwrite(m_writeBuffToFile.readPtr(), 1, readSize, m_fileTracer);
			if (writeSize > 0) {
				m_writeBuffToFile.readFlip(writeSize);
			}
			fflush(m_fileTracer);
		}
	}
}

void CFileTracer::_writeToConsole()
{
	if (m_outToConsole) {
		BSLib::uint32 readSize = m_writeBuffToConsole.readSize();
		if (readSize > 0) {
			char ch = 0;
			m_writeBuffToConsole.push(&ch, sizeof(ch));
			printf("%s", m_writeBuffToConsole.readPtr());
			m_writeBuffToConsole.readFlip(m_writeBuffToConsole.readSize());
		}
	}
}

}//Utility

}//BSLib

