//////////////////////////////////////////////////////////////////////
//	created:	2012/08/06
//	filename: 	BSLib\utility\fileTracer.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UTILITY_FILETRACER_H__
#define __BSLIB_UTILITY_FILETRACER_H__

#include <BSLib/utility/tracer.h>
#include <BSLib/utility/dateTime.h>
#include <BSLib/utility/stream.h>
#include <BSLib/utility/functionEvent.h>

namespace BSLib
{

namespace Utility
{

struct STracerItem;
class CTracerThread;

enum ELogFileSplitType
{
	ELFST_ERROR			= -1,
	ELFST_SECOND		= 0,
	ELFST_MINUTE		= 1,
	ELFST_HOUR			= 2,
	ELFST_DAY			= 3,
};

class BSLIB_UTILITY_API CFileTracer : public CTracer
{
public:
	CFileTracer();
	virtual ~CFileTracer();

	void setOutConsole(bool outToConsole = true, ETracerLevel outConsoleLevel = CTracer::ETL_DEBUG);
	void setOutConsole(bool outToConsole, const char* outConsoleLevel);

	bool setOutFile(const char* fileName, ELogFileSplitType splitType = ELFST_HOUR);
	bool setOutFile(const char* fileName, BSLib::int32 fileMaxSize);

	void close();

	/// @brief  getFilterEvent 设置过滤函数
	///		过滤函数定义 bool filterFun(CDateTime&, CTracer::ETracerLevel, std::string&, std::string&, int);
	///			CDateTime& 输出时间，
	///			CTracer::ETracerLevel 输出等级,
	///			std::string& 输出内容，
	///			std::string& 打印输出内容的文件,
	///			int 打印输出内容的文件行号
	/// @return BSLib::Utility::CFunctionEvent<bool, CDateTime&, CTracer::ETracerLevel, std::string&, std::string&, int>*
	BSLib::Utility::CFunctionEvent<bool, CDateTime&, CTracer::ETracerLevel, std::string&, std::string&, int>*
		getFilterEvent() { return &m_filter; }

protected:
	virtual void _outTrace(uint16 type, CTracer::ETracerLevel level, const char* file, int line, const char* format, va_list ap);

private:
	void _outTrace(STracerItem* item);
	void _splitFileBySize();
	void _splitFileByTime(ELogFileSplitType splitType, CDateTime& dateTime);
	void _setDelayTime();

	void _writeToFile();
	void _writeToConsole();

private:
	FILE* m_fileTracer;
	bool m_outToConsole;
	int m_tracerID;
	std::string m_fileName;
	long m_fileMaxSize;
	ELogFileSplitType m_splitType;
	CDelayTimer m_splitDelayTime;
	ETracerLevel m_outConsoleLevel;

	BSLib::Utility::CStream m_writeBuffToFile;
	BSLib::Utility::CStream m_writeBuffToConsole;

private:
	class TracerFilter : public BSLib::Utility::CFunctionEventResult<bool>
	{
	public:
		virtual bool operator()(bool a_result) 
		{
			return !a_result;
		}

		virtual void getFunctionResult(bool& a_result)
		{
			;
		}
	};
	TracerFilter m_filterResult;
	BSLib::Utility::CFunctionEvent<bool, CDateTime&, CTracer::ETracerLevel, std::string&, std::string&, int> m_filter;

private:
	static int m_fileMaxCount;
	friend class CTracerThread;
};

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_FILETRACER_H__
