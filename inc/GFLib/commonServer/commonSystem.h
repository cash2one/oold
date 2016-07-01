#ifndef __GFLIB_COMMONSERVER_COMMONSYSTEM_H__
#define __GFLIB_COMMONSERVER_COMMONSYSTEM_H__

#include <BSLib/utility/cmdExecMgr.h>
#include <BSLib/utility/pointer.h>
#include <BSLib/utility/thread/thread.h>
#include <BSLib/utility/timerServer.h>
#include <BSLib/network/netClient.h>
#include <BSLib/framework/message/msgExecMgr.h>
#include <GFLib/commonServer/service.h>

namespace GFLib
{

namespace CommonServer
{

class GFLIB_COMMONSERVER_API CCommonSystem
{
public:
	CCommonSystem();
	virtual ~CCommonSystem();

public:
	virtual BSLib::uint16 getFuncType() = 0;

protected:
	///////////////////////////////////////////////////////////////////////////
	// Method:    _init
	// Qualifier: Server��ʼ����ɺ󣬿�ʼ��ʼ��CCommonSystem::_init
	// Returns:   bool ��ʼ��Systemʧ�ܣ�����false��Server����ֹ����
	///////////////////////////////////////////////////////////////////////////
	virtual bool _init();

	///////////////////////////////////////////////////////////////////////////
	// Method:    _final
	// Qualifier: Server�����˳�ʱ����
	///////////////////////////////////////////////////////////////////////////
	virtual void _final();

	///////////////////////////////////////////////////////////////////////////
	// Method:    ICommonServer_loadGameConfig
	// Qualifier: ����ϵͳ�����ļ�
	// Returns:   bool
	// Parameter: const std::string & a_configPath
	///////////////////////////////////////////////////////////////////////////
	virtual bool ICommonServer_loadGameConfig(const std::string& a_configPath);

	///////////////////////////////////////////////////////////////////////////
	// Method:    ICommonServer_initServerMsg
	// Qualifier: ��ʼ��ϵͳ��Ϣ
	// Returns:   bool
	// Parameter: BSLib::Framework::CMsgExecMgr * a_msgExecMgr
	///////////////////////////////////////////////////////////////////////////
	virtual bool ICommonServer_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	///////////////////////////////////////////////////////////////////////////
	// Method:    _initCommand
	// Qualifier: ��ʼ������
	// Returns:   bool
	// Parameter: BSLib::Framework::CMsgExecMgr * a_msgExecMgr
	///////////////////////////////////////////////////////////////////////////
	virtual bool _initCommand(BSLib::Utility::CCmdExecMgr* a_cmdExecMgr);
	
	///////////////////////////////////////////////////////////////////////////
	// Method:    _prepStartSystem
	// Qualifier: Ϊ����ϵͳ����׼��
	// Returns:   bool
	///////////////////////////////////////////////////////////////////////////
	virtual bool _prepStartSystem();

	///////////////////////////////////////////////////////////////////////////
	// Method:    _startSystem
	// Qualifier: ����ϵͳ����׼��
	// Returns:   bool
	///////////////////////////////////////////////////////////////////////////
	virtual bool _startSystem();

	///////////////////////////////////////////////////////////////////////////
	// Method:    _startSystem
	// Qualifier: ����ϵͳ����׼��
	// Returns:   bool
	///////////////////////////////////////////////////////////////////////////
	virtual bool _postStartSystem();

	///////////////////////////////////////////////////////////////////////////
	// Method:    ICommonServer_cbServerEnter
	// Qualifier:
	// Returns:   void
	// Parameter: SServerID & a_serverID
	// Parameter: const std::string & a_key
	///////////////////////////////////////////////////////////////////////////
	virtual void ICommonServer_cbServerEnter(const SServerID& a_serverID, const std::string& a_key);

	///////////////////////////////////////////////////////////////////////////
	// Method:    ICommonServer_cbServerLeave
	// Qualifier:
	// Returns:   void
	// Parameter: SServerID & a_serverID
	// Parameter: const std::string & a_key
	///////////////////////////////////////////////////////////////////////////
	virtual void ICommonServer_cbServerLeave(const SServerID& a_serverID, const std::string& a_key);
	
protected:
	///////////////////////////////////////////////////////////////////////////
	// Method:    _getTimerServer
	// Qualifier:
	// Returns:   BSLib::Utility::CTimerServer*
	///////////////////////////////////////////////////////////////////////////
	BSLib::Utility::CTimerServer* _getTimerServer() { return m_timerServer; }

private:
	void _setTimerServer(BSLib::Utility::CTimerServer* a_timerServer) { m_timerServer = a_timerServer; }

private:
	BSLib::Utility::CTimerServer* m_timerServer;

	friend class CCommonSystemMgr;
};
typedef BSLib::Utility::CPointer<CCommonSystem> CCommonSystemPtr;

}//CommonServer

}//GFLib

#endif//__GFLIB_COMMONSERVER_COMMONSYSTEM_H__
