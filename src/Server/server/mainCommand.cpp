#include "mainCommand.h"
#include "mainServer.h"
#include "channelMgr.h"

#ifdef WIN32

#include <conio.h>

#else

#include <curses.h>
#include <unistd.h>

#endif

BSLIB_SINGLETON_DEFINE(CMainCommand);
//////////////////////////////////////////////////////////////////////////
int checkInput()
{
#ifdef WIN32

	return _kbhit();

#else

	return 0;

#endif
}

//////////////////////////////////////////////////////////////////////////
CMainCommand::CMainCommand()
: m_isRunning(false)
, m_needInput(false)
, m_localNumber(-1)
{
	;
}

CMainCommand::~CMainCommand()
{
	;
}

void CMainCommand::init(bool a_needInput)
{
	m_needInput = a_needInput;
	m_cmdExecMgr.addCmdExecPtr("exit", &CMainCommand::_onCmdExit, this);
	m_cmdExecMgr.addCmdExecPtr("stop", &CMainCommand::_onCmdStop, this);
	m_cmdExecMgr.addCmdExecPtr("list", &CMainCommand::_onCmdList, this);
	m_cmdExecMgr.addCmdExecPtr("help", &CMainCommand::_onCmdHelp, this);
	m_cmdExecMgr.addCmdExecPtr("use", &CMainCommand::_onCmdUse, this);
	//m_cmdExecMgr.addCmdExecPtr("send", &CMainCommand::_onCmdUse, this);

	if (m_needInput) {
		m_isRunning = true;
		BSLib::Utility::CThread::start();
	}
}

void CMainCommand::final()
{
	if (m_needInput) {
		if (BSLib::Utility::CThread::isValid()) {
			if (m_isRunning) {
				m_isRunning = false;
			}
			BSLib::Utility::CThread::join();
		}
	}
}

int CMainCommand::parseCommand(const std::string& cmdLine)
{
	int res = m_cmdExecMgr.parseCommand(cmdLine, NULL);
	if (res <= 0) {
		printf("\n\r解析命令失败\n");
	}
	return res;
}

#ifdef WIN32

void CMainCommand::_run()
{
	std::vector<BSLib::Utility::CStringA> commandList;
	int posCommandList = -1;
	BSLib::Utility::CStringA command;
	
	m_cmdShow = "";

	printf("\r>");

	while (m_isRunning) {
		if (!checkInput()) {
			BSLib::Utility::CThread::msleep(15);
			continue;
		}
		

		int ch = getch();
		if (ch >= ' ' && ch < 128) {
			command.push_back(ch);
			printf("\r%s>%s", m_cmdShow.c_str(), command.c_str());
			continue;
		}
		switch (ch)
		{
		case '\r':
			command.trimRight();
			if (!command.empty()) {

				int res = m_cmdExecMgr.parseCommand(command, NULL);
				if (res < 0) {
					printf("\n解析命令失败\n");
				} else if (res == 0) {
					if(notifyCommandToServer(command)) {
						printf("\n投递命令完成\n");
					}else {
						printf("\n执行命令失败\n");
					}
				}
				commandList.push_back(command);
				posCommandList = commandList.size() - 1;
				command = "";
			}
			printf("\n%s>", m_cmdShow.c_str());
			break;
		case '\b':
			if (!command.empty()) {
				command[command.length() -1] = ' ';
				printf("\r%s>%s", m_cmdShow.c_str(), command.c_str());
				command.erase(command.length() -1, 1);
				printf("\r%s>%s", m_cmdShow.c_str(), command.c_str());	
			}
			break;
		case 224:
			ch = getch();
			if (ch == 72 || ch == 75) {//up || left
				if (posCommandList + 1 >= (int)commandList.size()) {
					break;
				}
				posCommandList += 1;
				if (posCommandList < 0) {
					break;
				}
				BSLib::Utility::CStringA tmp;
				for (BSLib::uint32 i=0; i<command.size(); ++i){
					tmp.push_back(' ');
				}
				printf("\r%s>%s", m_cmdShow.c_str(), tmp.c_str());
				command = commandList[posCommandList];
				printf("\r%s>%s", m_cmdShow.c_str(), command.c_str());
			} else if (ch == 80 || ch == 77) {//down || right
				if (posCommandList - 1 < 0) {
					break;
				}
				posCommandList -= 1;
				if (posCommandList  >= (int)commandList.size()) {
					break;
				}
				BSLib::Utility::CStringA tmp;
				for (BSLib::uint32 i=0; i<command.size(); ++i){
					tmp.push_back(' ');
				}
				printf("\r%s>%s", m_cmdShow.c_str(), tmp.c_str());
				command = commandList[posCommandList];
				printf("\r%s>%s", m_cmdShow.c_str(), command.c_str());
			} 
		}
		
	}
}

#else

enum EInputType
{
	EINPUTTYPE_NULL = 0,
	EINPUTTYPE_ENTER = 1,
	EINPUTTYPE_BACK = 2,
	EINPUTTYPE_UP = 3,
	EINPUTTYPE_DOWN = 4,
	EINPUTTYPE_RIGHT = 5,
	EINPUTTYPE_LEFT = 6,
	EINPUTTYPE_CHAR = 7,
};

EInputType waitCommand(int index, std::string& a_command)
{
	int ch = 0;
	ch = getch();
	if (ch >= ' ' && ch < 128) {
		if (index >= (int)a_command.size()) {
			a_command.push_back((char)ch);
		} else {
			a_command[index] = ch;
		}
		return EINPUTTYPE_CHAR;
	}
	switch(ch) {
	case '\n':	//回车
		return EINPUTTYPE_ENTER;
		break;
	case '\b':	//回退
		return EINPUTTYPE_BACK;
		break;
	case 27:
		ch = getch();
		if (ch != 19) {
			return EINPUTTYPE_NULL;
		}
		ch = getch();
		if(ch == 65) {			//up
			return EINPUTTYPE_UP;
		} else if (ch == 66) {	//down
			return EINPUTTYPE_DOWN;
		} else if (ch == 67) {	//right
			return EINPUTTYPE_RIGHT;
		} else if (ch == 68) {	//left
			return EINPUTTYPE_LEFT;
		}
		break;
	default:
		;
	}

	return EINPUTTYPE_NULL;
}

void CMainCommand::_run()
{
	initscr();
	noecho();

	std::vector<BSLib::Utility::CStringA> commandList;
	int posCommandList = -1;
	BSLib::Utility::CStringA command;

	m_cmdShow = "";
	int y = 1;
	mvaddch(LINES-3, 0, '>');
	move(LINES-3, y);
	refresh();

	while (m_isRunning) {
		EInputType type = waitCommand(y - 1, command);
			switch(type) {
				case EINPUTTYPE_ENTER:
					for (; y >= 1; y--) {
						mvaddch(LINES-3, y, ' ');
					}
					y = 1;
					mvaddch(LINES-3, 0, '>');
					move(LINES-3, y);
					
					command.trimRight();
					if (!command.empty()) {
						int res = m_cmdExecMgr.parseCommand(command, NULL);
						if (res < 0) {
							printf("\n\r解析命令失败");
						} else if (res == 0) {
							if(notifyCommandToServer(command)) {
								printf("\n\r投递命令完成");
							}else {
								printf("\n\r执行命令失败");
							}
						}
						commandList.push_back(command);
						posCommandList = commandList.size() - 1;
						command = "";
					}
					break;
				case EINPUTTYPE_BACK:
					if (!command.empty()) {
						command.erase(command.length() -1, 1);
						mvaddstr(LINES-3, 1, command.c_str());
						y = y - 1;
						mvaddch(LINES-3, y, ' ');
						move(LINES-3, y);
					}
					break;
				case EINPUTTYPE_UP:
				case EINPUTTYPE_DOWN:
				case EINPUTTYPE_RIGHT:
				case EINPUTTYPE_LEFT:
				case EINPUTTYPE_CHAR:
					mvaddstr(LINES-3, 1, command.c_str());
					if (y - 1 >= (int)command.size() && y < COLS - 2){
						y = command.size();
					} else {
						y = y + 1;
					}
					break;
				case EINPUTTYPE_NULL:
					break;
			}
	}
	endwin();
}

#endif

int CMainCommand::_onCmdExit(BSLib::Utility::CProperties& a_properties, void* a_para)
{
	m_isRunning = false;
	CMainServer::singleton().terminate();
	return 1;
}

int CMainCommand::_onCmdStop(BSLib::Utility::CProperties& a_properties, void* a_para)
{
	std::string stopValue;
	a_properties.getValueString("1", stopValue);
	if (stopValue == "all") {
		CChannelMgr::singleton().stopAll();
		return 1;
	}
	return 0;
}

int CMainCommand::_onCmdList(BSLib::Utility::CProperties& a_properties, void* a_para)
{
	CChannelMgr::singleton().showAllChannelInfor();
	return 1;
}

int CMainCommand::_onCmdHelp(BSLib::Utility::CProperties& a_properties, void* a_para)
{
	return 0;
}

int CMainCommand::_onCmdUse(BSLib::Utility::CProperties& a_properties, void* a_para)
{
	std::string serverName;
	if (!a_properties.getValueString("1", serverName)) {
		printf("\n\r获取参数失败");
		return 1;
	}
	SChannelInfor* channelInfor = CChannelMgr::singleton().getChannelInfor(serverName);
	if (channelInfor == NULL) {
		printf("\n\r通道[%s]不存在", serverName);
		return 1;
	}

	m_cmdShow = channelInfor->m_serverName;

//	printf("\n%s>", m_cmdShow.c_str());

	m_localNumber = channelInfor->m_channelID.getLocalNumber();

	return 1;
}

bool CMainCommand::notifyCommandToServer(const std::string& a_command)
{
	if(m_localNumber < 0) {
		printf("\n\r当前通道无效");
		return false;
	}
	SChannelInfor* channelInfor = CChannelMgr::singleton().getChannelInfor(m_localNumber);
	if (channelInfor == NULL) {
		printf("\n\r通道[%d]不存在", m_localNumber);
		return false;
	}
	GFLib::SMsgSysChannelLC2LCNtfCommand ntfCommand;
	ntfCommand.setCommand(a_command);
	return CChannelMgr::singleton().sendMsg(channelInfor->m_channelID, &ntfCommand, sizeof(ntfCommand));
}
