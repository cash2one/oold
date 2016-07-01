#ifndef __BSLIB_FRAMEWORK_MAINTHREAD_H__
#define __BSLIB_FRAMEWORK_MAINTHREAD_H__

#include <BSLib/framework/sysConfig.h>
#include <BSLib/framework/threadFrame.h>
#include <BSLib/framework/message/msgFactory.h>

#ifdef _WINDOWS

	#define BSLIB_FRAMEWORK_MAIN(funMain) int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)\
			{\
				BSLib::Framework::CSysConfig::singleton().initMain(lpCmdLine);\
				return funMain();\
			}

#elif defined(_CONSOLE) || defined(_LINUX)

	#define BSLIB_FRAMEWORK_MAIN(funMain) int main(int argc, char* argv[])\
			{\
				BSLib::Framework::CSysConfig::singleton().initMain(argc, argv);\
				return funMain();\
			}

#endif

namespace BSLib
{

namespace Framework
{

class BSLIB_FRAMEWORK_API CMainThread : public IThread
{
public:
	CMainThread();
	virtual ~CMainThread();

protected:
	virtual bool _IThread_init();

public:
	static CMainThread* getMainThread() { return m_mainThread; }

private:
	static CMainThread* m_mainThread;
};

}//Framework

}//BSLib

#endif //__BSLIB_FRAMEWORK_MAINTHREAD_H__

