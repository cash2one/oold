#ifndef __BSLIB_UTILITY_TRACER_H__
#define __BSLIB_UTILITY_TRACER_H__

//#include <cstdio>
//#include <cstdlib>
#include <BSLib/utility/baseDef.h>

#define BSLIB_TRACER_BIT_MAX		(sizeof(uint32) * 8)
#define BSLIB_TRACER_TYPE_BIT_MAX	(5)
#define BSLIB_TRACER_LEAVE_MAX		(ETT_MAX - 1)
#define BSLIB_TRACER_TYPE_MAX		(ETT_MAX / BSLIB_TRACER_BIT_MAX)
#define BSLIB_TRACER_TYPE_POS_MASK	(0XFFE0)
#define BSLIB_TRACER_TYPE_BIT_MASK	(0X001F)
#define BSLIB_TRACER_TYPE_POS(type)	(BSLIB_LO_SHIFT((type - 1) & BSLIB_TRACER_TYPE_POS_MASK, BSLIB_TRACER_TYPE_BIT_MAX))
#define BSLIB_TRACER_TYPE_BIT(type)	((type - 1) & BSLIB_TRACER_TYPE_BIT_MASK)

namespace BSLib
{

enum ETraceType
{
	//特殊功能
	ETT_ALL = 0,
	ETT_DEFAULT,
	ETT_ASSERT,

	//BSLib 使用
	ETT_BSLIB_UTILITY = 8,
	ETT_BSLIB_NETWORK,
	ETT_BSLIB_DATABASE,
	ETT_BSLIB_FRAMEWORK,
	ETT_BSLIB_P2PCLIENT,
	ETT_BSLIB_P2PSERVER,
	ETT_BSLIB_BTREE,
	ETT_BSLIB_FSM,

	//BSLib 以外的使用
	ETT_BSLIB_EXTEND = 32,

	ETT_MAX = 4096,
};

struct STraceTypeName
{
	STraceTypeName(BSLib::uint16 a_type, const std::string& a_name) : m_type(a_type), m_name(a_name) {};

	BSLib::uint16 m_type;
	std::string m_name;
};

namespace Utility
{

void stringFormat(std::string& a_str, const char* a_format, va_list ap);

class BSLIB_UTILITY_API CTracer
{
public:
	enum ETracerLevel
	{
		ETL_DEBUG = 0,	//调试, 测试日志
		ETL_TRACE,		//跟踪, 逻辑跟踪日志，可以忽略
		ETL_WARN,		//逻辑警告, 不会出现逻辑混乱
		ETL_INFO,		//日志, 必须备案，不可以忽略
		ETL_ERROR,		//严重错误, 可能会产生逻辑混乱，但不会宕机
		ETL_FATAL,		//致命错误, 可能会产生宕机
		ETL_MAX
	};

public:
	CTracer();
	virtual ~CTracer();

	ETracerLevel getLevel(uint16 type);
	
	void setLevel(uint16 type, ETracerLevel level);
	void setLevel(uint16 type, const std::string& level);
	
	void setTypeON(uint16 type);
	void setTypeOFF(uint16 type);
	
	void debug(uint16 type, const char* file, int line, const char* format, ...);
	void trace(uint16 type, const char* file, int line, const char* format, ...);
	void warn(uint16 type, const char* file, int line, const char* format, ...);
	void info(uint16 type, const char* file, int line, const char* format, ...);
	void error(uint16 type, const char* file, int line, const char* format, ...);
	void fatal(uint16 type, const char* file, int line, const char* format, ...);

	void setTypeName(uint16 a_type, const std::string& a_typeName);
	void setTypeNames(const STraceTypeName a_typeNames[], BSLib::uint32 a_typeNameCount);

public:
	static void setSysTracer(CTracer* tracer);
	static CTracer* getSysTracer();

	static void sysDebug(uint16 type, const char* file, int line, const char* format, ...);
	static void sysTrace(uint16 type, const char* file, int line, const char* format, ...);
	static void sysWarn(uint16 type, const char* file, int line, const char* format, ...);
	static void sysInfo(uint16 type, const char* file, int line, const char* format, ...);
	static void sysError(uint16 type, const char* file, int line, const char* format, ...);
	static void sysFatal(uint16 type, const char* file, int line, const char* format, ...);

protected:
	virtual void _outTrace(uint16 type, ETracerLevel level, const char* file, int line, const char* format, va_list ap) = 0;

	const std::string& _getTypeName(uint16 type)
	{
		static std::string tempName = "";
		if (type <= 0 || type > ETT_MAX) {
			return tempName;
		}
		return m_typeNames[type - 1];
	}

private:
	bool _checkType(uint16 type)
	{
		uint16 pos = BSLIB_TRACER_TYPE_POS(type);
		uint16 bits = BSLIB_TRACER_TYPE_BIT(type);

		return (m_typeFlags[pos] & BSLIB_HI_SHIFT(1, bits)) != 0;
	}

	
	CTracer::ETracerLevel m_typeLevels[ETT_MAX];
	uint32 m_typeFlags[BSLIB_TRACER_TYPE_MAX];
	std::string m_typeNames[ETT_MAX];
};

}//Utility

}//BSLib

#ifdef _DEBUG

	#define BSLIB_LOG_DEBUG(type, format, ...)\
		BSLib::Utility::CTracer::sysDebug(type, __FILE__, __LINE__, format, ## __VA_ARGS__);

#else

	#define BSLIB_LOG_DEBUG(type, format, ...)

#endif

#define BSLIB_LOG_TRACE(type, format, ...)\
	BSLib::Utility::CTracer::sysTrace(type, __FILE__, __LINE__, format, ## __VA_ARGS__);

#define BSLIB_LOG_WARN(type, format, ...)\
	BSLib::Utility::CTracer::sysWarn(type, __FILE__, __LINE__, format, ## __VA_ARGS__);

#define BSLIB_LOG_INFO(type, format, ...)\
	BSLib::Utility::CTracer::sysInfo(type, __FILE__, __LINE__, format, ## __VA_ARGS__);

#define BSLIB_LOG_ERROR(type, format, ...)\
	BSLib::Utility::CTracer::sysError(type, __FILE__, __LINE__, format, ## __VA_ARGS__);

#define BSLIB_LOG_FATAL(type, format, ...)\
	BSLib::Utility::CTracer::sysFatal(type, __FILE__, __LINE__, format, ## __VA_ARGS__);

#define BSLIB_LOG_SET_TYPE_ON(type)\
	do {\
		BSLib::Utility::CTracer* tracer = BSLib::Utility::CTracer::getSysTracer();\
		if (tracer != NULL) {\
			tracer->setTypeON(type);\
		}\
	} while(false);

#define BSLIB_LOG_SET_TYPE_OFF(type)\
	do {\
		BSLib::Utility::CTracer* tracer = BSLib::Utility::CTracer::getSysTracer();\
		if (tracer != NULL) {\
			tracer->setTypeOFF(type);\
		}\
	} while(false);

#define BSLIB_LOG_SET_LEVEL(type, level)\
	do {\
		BSLib::Utility::CTracer* tracer = BSLib::Utility::CTracer::getSysTracer();\
		if (tracer != NULL) {\
			tracer->setLevel(type, level);\
		}\
	} while(false);

#endif//__BSLIB_UTILITY_TRACER_H__

