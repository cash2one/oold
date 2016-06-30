#ifndef __GFLIB_COMMONSERVER_SERVICE_H__
#define __GFLIB_COMMONSERVER_SERVICE_H__

#include <BSLib/framework/message/msgExecMgr.h>
#include <BSLib/framework/message/msgQueue.h>
#include <GFLib/commonServer/serverTypeMgr.h>
#include <GFLib/commonServer/message/message.h>
#include <GFLib/commonServer/message/msgLabel.h>

namespace GFLib
{

namespace CommonServer
{

class GFLIB_COMMONSERVER_API IService
{
public:
	IService() {}
	virtual ~IService(){ m_msgExecMgr.clear(); }
	SServerID getServerID() { return m_serverID; }
	const std::string& getKey() { return m_key; }

	virtual bool IService_sendMsg(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize) = 0;
	virtual bool IService_sendMsg(GFLib::CMessage& a_msg) = 0;
	virtual void close() = 0;

protected:
	void _setKey(const std::string& a_key) { m_key = a_key; }
	void _setServerID(SServerID a_serverID) { m_serverID.setServerID(a_serverID); }
	BSLib::Framework::CMsgExecMgr* _getMsgExecMgr() { return &m_msgExecMgr; }

	bool _parseMsg(GFLib::SMessage* msg, BSLib::uint32 a_msgSize);

	virtual bool _transferMsg(GFLib::SMessage* msg, BSLib::uint32 a_msgSize);

	/// @brief  _canTransfer 
	///			判断能否转发消息
	///			如果不具有转发功能，消息只能在该对象内部处理
	/// @return bool
	virtual bool _canTransfer() { return false; }

protected:
	virtual GFLib::StubID _getStubID() = 0;

private:
	bool _executeMessage(GFLib::SNetMsgLabel* lable, GFLib::SMessage* msg);
	bool _executeTransfer(GFLib::SMessage* msg, BSLib::uint32 a_msgSize);

private:
	std::string m_key;
	SServerID m_serverID;
	BSLib::Framework::CMsgExecMgr m_msgExecMgr;
};

typedef BSLib::Utility::CPointer<IService> CServicePtr;

}//CommonServer

}//GFLib

#endif//__GFLIB_COMMONSERVER_SERVICE_H__




