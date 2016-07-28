#ifndef __SERVER_SERVER_MAINCOMMAND_H__
#define __SERVER_SERVER_MAINCOMMAND_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/thread/thread.h>
#include <BSLib/utility/cmdExecMgr.h>

class CMainCommand : public BSLib::Utility::CThread
{
public:
	CMainCommand();
	virtual ~CMainCommand();

	BSLIB_SINGLETON_DECLARE(CMainCommand);

public:
	void init(bool a_needInput);
	void final();
	int parseCommand(const std::string& cmdLine);

protected:
	virtual void _run();

private:
	int _onCmdExit(BSLib::Utility::CProperties& a_properties, void* a_para);
	int _onCmdStop(BSLib::Utility::CProperties& a_properties, void* a_para);
	int _onCmdList(BSLib::Utility::CProperties& a_properties, void* a_para);
	int _onCmdHelp(BSLib::Utility::CProperties& a_properties, void* a_para);
	int _onCmdUse(BSLib::Utility::CProperties& a_properties, void* a_para);

private:
	bool notifyCommandToServer(const std::string& a_command);
	
private:
	bool m_isRunning;
	bool m_needInput;
	BSLib::Utility::CCmdExecMgr m_cmdExecMgr;
	std::string m_cmdShow;
	BSLib::int32 m_localNumber;
};

#endif//__SERVER_SERVER_MAINCOMMAND_H__

