#include <BSLib/utility/atomic.h>

#ifdef _LINUX

#include <ext/atomicity.h>

#endif

namespace BSLib
{

namespace Utility
{

int32 CAtomic::increment()
{
	return increment(m_data);
}

int32 CAtomic::decrement()
{
	return decrement(m_data);
}

int32 CAtomic::increment(volatile int32& data)
{
#ifdef WIN32

	return (int32)InterlockedIncrement((long*)&data);

#else

	return (int32)__sync_add_and_fetch(&data, 1);

#endif
}

int32 CAtomic::decrement(volatile int32& data)
{
#ifdef WIN32

	return (int32)InterlockedDecrement((long*)&data);

#else
	return (int32)__sync_sub_and_fetch(&data, 1);

#endif
}

}//Utility

}//BSLib

