#ifndef __BSLIB_UTILITY_UUID_H__
#define __BSLIB_UTILITY_UUID_H__

#if defined( WIN32 )

#include <Rpc.h>

#else

#include <uuid/uuid.h>

#endif

#include <BSLib/utility/baseDef.h>

namespace BSLib
{

namespace Utility
{

class BSLIB_UTILITY_API CUUID
{
public:
	CUUID();

	std::string unparse();

public:
	static bool generate(CUUID& a_uuid);

private:
	uuid_t m_uuid;
};

}//Utility

}//BSLib

#endif // __BSLIB_UTILITY_UUID_H__
