#ifndef __SERVER_SERVER_MAINSERVER_H__
#define __SERVER_SERVER_MAINSERVER_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/framework/mainThread.h>

class CMainServer : public BSLib::Framework::CMainThread
{
public:
	CMainServer();
	virtual ~CMainServer();

	BSLIB_SINGLETON_DECLARE(CMainServer);

public:
	static int main();

protected:
	virtual bool _IThread_init();
	virtual int _IThread__final(); 

private:
};

#endif//__SERVER_SERVER_MAINSERVER_H__





