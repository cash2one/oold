#include <BSLib/utility/file/dirInfo.h>
#include <BSLib/utility/file/fileInfo.h>
#include <BSLib/framework/mainThread.h>

#ifdef WIN32
#include <dbghelp.h>
#endif

namespace BSLib
{

namespace Framework
{

#ifdef WIN32

	BOOL WINAPI CtrlCHandler(DWORD CtrlType)
	{
		CMainThread* mainThread = CMainThread::getMainThread();
		if (mainThread == NULL) {
			return FALSE;
		}
		mainThread->terminate();
		return TRUE;
	}

	LONG WINAPI UnhandledExceptionCallback(PEXCEPTION_POINTERS a_exceptionInfo)
	{
		std::string exeFile = BSLib::Utility::CDirInfo::getExeFile();
		std::string exeDir = BSLib::Utility::CDirInfo::getExeDirectory();
		std::string dumpFilePath = exeDir;
		dumpFilePath += "\\";
		dumpFilePath += exeFile;
		BSLib::Utility::CDirInfo::standardization(dumpFilePath);

		BSLib::Utility::CStringA dumpFilePathTemp;
		dumpFilePathTemp.format("%s.dmp", dumpFilePath.c_str());

		int i=0;
		while (BSLib::Utility::CFileInfo::isExist(dumpFilePathTemp)) {
			dumpFilePathTemp.format("%s.%d.dmp", dumpFilePath.c_str(), i);
			++i;
		}

		HANDLE hFile = ::CreateFile(dumpFilePathTemp.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFile != INVALID_HANDLE_VALUE) {
			MINIDUMP_EXCEPTION_INFORMATION info;
			info.ThreadId = ::GetCurrentThreadId();
			info.ExceptionPointers = a_exceptionInfo;
			info.ClientPointers = FALSE;
			
			::MiniDumpWriteDump(::GetCurrentProcess(), ::GetCurrentProcessId(), hFile, MiniDumpWithFullMemory, &info, NULL, NULL);

			::CloseHandle(hFile);
		}
		return EXCEPTION_EXECUTE_HANDLER;
	}

	void DisableSetUnhandledExceptionFilter()
	{
		void* addr = (void*)GetProcAddress(LoadLibrary("kernel32.dll"), "SetUnhandledExceptionFilter");

		if (addr != NULL) {
			BSLib::uint8 code[16];
			int size = 0;
			code[size++] = 0X33;
			code[size++] = 0XC0;
			code[size++] = 0XC2;
			code[size++] = 0X04;
			code[size++] = 0X00;

			DWORD dwOldFlag = 0;
			DWORD dwTempFlag = 0;

			VirtualProtect(addr, size, PAGE_READWRITE, &dwOldFlag);
			WriteProcessMemory(GetCurrentProcess(), addr, code, size, NULL);
			VirtualProtect(addr, size, dwOldFlag, &dwTempFlag);
		}
	}


#else

	void CtrlCHandler(int signum)
	{

		CMainThread* mainThread = CMainThread::getMainThread();
		if (mainThread == NULL) {
			return ;
		}
		mainThread->terminate();
	}

#endif


CMainThread* CMainThread::m_mainThread = NULL;

CMainThread::CMainThread()
{
#ifdef WIN32
	
	//DisableSetUnhandledExceptionFilter();
	SetUnhandledExceptionFilter(UnhandledExceptionCallback);

#endif

	if (m_mainThread == NULL) {
		m_mainThread = this;
	}
}

CMainThread::~CMainThread()
{
	;
}

bool CMainThread::_init()
{
#ifdef WIN32

	//::SetConsoleCtrlHandler(CtrlCHandler, TRUE);

#else

	struct sigaction sig;
	sig.sa_handler = CtrlCHandler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
	sigaction(SIGABRT, &sig, NULL);
	sigaction(SIGTERM, &sig, NULL);

#endif

	return IThreadFrame::_init();
}

}//Framework

}//BSLib


