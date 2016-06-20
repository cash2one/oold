//////////////////////////////////////////////////////////////////////
//	created:	2012/08/06
//	filename:	src\BSLib\utility\tracer.cpp
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#include <string.h>
#include <stdarg.h>
#include <BSLib/utility/string.h>
#include <BSLib/utility/tracer.h>

namespace BSLib
{

namespace Utility
{

static CTracer* g_tracer = NULL;
static STraceTypeName g_sysTypeName[] = {
	STraceTypeName(ETT_DEFAULT, "BSDEFAULT"),
	STraceTypeName(ETT_ASSERT, "BSASST"),
	STraceTypeName(ETT_BSLIB_UTILITY, "BSUTLT"),
	STraceTypeName(ETT_BSLIB_NETWORK, "BSNET"),
	STraceTypeName(ETT_BSLIB_DATABASE, "BSDB"),
	STraceTypeName(ETT_BSLIB_FRAMEWORK, "BSFRMW"),
	STraceTypeName(ETT_BSLIB_P2PCLIENT, "BSP2PC"),
	STraceTypeName(ETT_BSLIB_P2PSERVER, "BSP2PS"),
	STraceTypeName(ETT_BSLIB_BTREE, "BSBTREE"),
	STraceTypeName(ETT_BSLIB_FSM, "BSFSM"),
};

//////////////////////////////////////////////////////////////////////////

void stringFormat(std::string& a_str, const char* a_format, va_list ap)
{
#ifdef WIN32

	uint32 nLength = _vscprintf(a_format, ap);
	a_str.resize(nLength);
	_vsnprintf_s((char*)a_str.c_str(), nLength + 1, _TRUNCATE, a_format, ap);

#elif defined(_LINUX)

	va_list tmpAp;
	va_copy(tmpAp, ap);
	uint32 nLength = vsnprintf(NULL, 0, a_format, tmpAp);
	va_end(tmpAp);
	a_str.resize(nLength);
	va_copy(tmpAp, ap);
	vsnprintf((char*)a_str.c_str(), nLength + 1, a_format, tmpAp);
	va_end(tmpAp);

#else

#error "Unknown platform !!"  

#endif
}

//////////////////////////////////////////////////////////////////////////
// CSysTracer
//////////////////////////////////////////////////////////////////////////
CTracer::CTracer()
{
	setLevel(ETT_ALL, ETL_INFOR);
	setTypeON(ETT_ALL);
}

CTracer::~CTracer()
{
	;
}

CTracer::ETracerLevel CTracer::getLevel(uint16 type)
{
	if (type == ETT_ALL) {
		return ETL_ERROR;
	}
	return m_typeLevels[type - 1]; 
}

void CTracer::setLevel(uint16 type, ETracerLevel level) 
{
	if (type == ETT_ALL) {
		for (int i=0; i<BSLIB_TRACER_LEAVE_MAX; ++i){
			m_typeLevels[i] = level;
		}
		return ;
	}
	m_typeLevels[type - 1] = level; 
}

void CTracer::setLevel(uint16 type, const std::string& level)
{
	BSLib::Utility::CStringA strLevel = level;
	strLevel.toLower();
	const char* levelName[] = {"debug", "trace", "warn", "infor", "error", "fatal"};
	for (int i = 0; i < ETL_MAX; i++){
		if (strLevel == levelName[i]){
			setLevel(type, (CTracer::ETracerLevel)i);
			break;
		}
	}
}

void CTracer::setTypeON(uint16 type)
{
	if (type == ETT_ALL) {
		for (uint32 i=0; i<BSLIB_TRACER_TYPE_MAX; ++i){
			m_typeFlags[i] = 0XFFFFFFFF;
		}
		return ;
	}

	uint16 pos = BSLIB_TRACER_TYPE_POS(type);
	uint16 bits = BSLIB_TRACER_TYPE_BIT(type);
	
	m_typeFlags[pos] |= BSLIB_HI_SHIFT(1, bits);
}

void CTracer::setTypeOFF(uint16 type)
{
	if (type == ETT_ALL) {
		for (uint32 i=0; i<BSLIB_TRACER_TYPE_MAX; ++i){
			m_typeFlags[i] = 0;
		}
		return ;
	}

	uint16 pos = BSLIB_TRACER_TYPE_POS(type);
	uint16 bits = BSLIB_TRACER_TYPE_BIT(type);

	m_typeFlags[pos] &= ~BSLIB_HI_SHIFT(1, bits);
}

#define BSLIB_TRACER_OUTTRACE(t, l)\
	if (t == ETT_ALL){\
		return ;\
	}\
	if(l < getLevel(t)){\
		return;\
	}\
	if (!_checkType(t)) {\
		return;\
	}\
	va_list args;\
	va_start(args, format);\
	_outTrace(t, l, file, line, format, args);\
	va_end(args);

void CTracer::debug(uint16 type, const char* file, int line, const char* format, ...)
{
#ifdef _DEBUG

	BSLIB_TRACER_OUTTRACE(type, ETL_DEBUG);

#endif
}

void CTracer::trace(uint16 type, const char* file, int line, const char* format, ...)
{
	BSLIB_TRACER_OUTTRACE(type, ETL_TRACE);
}

void CTracer::warn(uint16 type, const char* file, int line, const char* format, ...)
{
	BSLIB_TRACER_OUTTRACE(type, ETL_WARN);
}

void CTracer::infor(uint16 type, const char* file, int line, const char* format, ...)
{
	BSLIB_TRACER_OUTTRACE(type, ETL_INFOR);
}

void CTracer::error(uint16 type, const char* file, int line, const char* format, ...)
{
	BSLIB_TRACER_OUTTRACE(type, ETL_ERROR);
}

void CTracer::fatal(uint16 type, const char* file, int line, const char* format, ...)
{
	BSLIB_TRACER_OUTTRACE(type, ETL_FATAL);
}

void CTracer::setTypeName(uint16 a_type, const std::string& a_typeName)
{
	if (a_type <= 0 || a_type > ETT_MAX) {
		return;
	}
	m_typeNames[a_type - 1] = a_typeName;
}

void CTracer::setTypeNames(const STraceTypeName a_typeNames[], BSLib::uint32 a_typeNameCount)
{
	for (BSLib::uint32 i=0; i<a_typeNameCount; ++i) {
		if (a_typeNames[i].m_type <= 0 || a_typeNames[i].m_type > ETT_MAX) {
			continue;
		}
		m_typeNames[a_typeNames[i].m_type - 1] = a_typeNames[i].m_name;
	}
}

void CTracer::setSysTracer(CTracer* tracer)
{
	g_tracer = tracer;
	if (g_tracer != NULL) {
		g_tracer->setTypeNames(g_sysTypeName, sizeof(g_sysTypeName)/sizeof(STraceTypeName));
	}
}

CTracer* CTracer::getSysTracer()
{
	return g_tracer;
}

#define BSLIB_TRACER_OUTTRACE_STATIC(t, l)\
	CTracer* tracer = g_tracer;\
	if(tracer == NULL){\
		return ;\
	}\
	if (t == 0){\
		return ;\
	}\
	if(l < tracer->getLevel(t)){\
		return;\
	}\
	if (!tracer->_checkType(t)) {\
		return;\
	}\
	va_list args;\
	va_start(args, format);\
	tracer->_outTrace(t, l, file, line, format, args);\
	va_end(args);

void CTracer::sysDebug(uint16 type, const char* file, int line, const char* format, ...)
{
#ifdef _DEBUG

	BSLIB_TRACER_OUTTRACE_STATIC(type, ETL_DEBUG);

#endif
}

void CTracer::sysTrace(uint16 type, const char* file, int line, const char* format, ...)
{
	BSLIB_TRACER_OUTTRACE_STATIC(type, ETL_TRACE);
}

void CTracer::sysWarn(uint16 type, const char* file, int line, const char* format, ...)
{
	BSLIB_TRACER_OUTTRACE_STATIC(type, ETL_WARN);
}

void CTracer::sysInfor(uint16 type, const char* file, int line, const char* format, ...)
{
	BSLIB_TRACER_OUTTRACE_STATIC(type, ETL_INFOR);
}

void CTracer::sysError(uint16 type, const char* file, int line, const char* format, ...)
{
	BSLIB_TRACER_OUTTRACE_STATIC(type, ETL_ERROR);
}

void CTracer::sysFatal(uint16 type, const char* file, int line, const char* format, ...)
{
	BSLIB_TRACER_OUTTRACE_STATIC(type, ETL_FATAL);
}

}//Utility

}//BSLib

