#ifndef __BSLIB_FRAMEWORK_MESSAGE_MSGEXEC_H__
#define __BSLIB_FRAMEWORK_MESSAGE_MSGEXEC_H__

#include <BSLib/utility/pointer.h>
#include <BSLib/utility/function.h>
#include <BSLib/framework/message/msgLabel.h>

namespace BSLib
{

namespace Framework
{

class BSLIB_FRAMEWORK_API CMsgExec
{
public:
	typedef void(*MessageExecFun)(SMsgLabel*, SMessage*);

public:
	CMsgExec(MessageExecFun execFun);
	CMsgExec(const BSLib::Utility::CFunction<void, SMsgLabel*, SMessage*>& execFun);
	
	template<class NAME>
	CMsgExec(void (NAME::*execFun)(SMsgLabel*, SMessage*), NAME* object) : m_execFun(NULL)
	{
		m_execFun = new BSLib::Utility::CFunctionObject<void, NAME, SMsgLabel*, SMessage*>(execFun, object);
	}

	virtual ~CMsgExec();
	virtual void executeMessage(SMsgLabel* msgLabel, SMessage* msg);

private:
	 BSLib::Utility::CFunction<void, SMsgLabel*, SMessage*>* m_execFun;
};
typedef Utility::CPointer<CMsgExec> CMsgExecPtr;

}//Framework

}//BSLib


#endif // __BSLIB_FRAMEWORK_MESSAGE_MSGEXEC_H__

