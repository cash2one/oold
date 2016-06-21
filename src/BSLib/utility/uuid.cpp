#include <BSLib/utility/uuid.h>

namespace BSLib
{

namespace Utility
{

CUUID::CUUID()
{
	memset(&m_uuid, 0, sizeof(m_uuid));
}

std::string CUUID::unparse()
{
	

#if defined( WIN32 )

	std::string temp;
	RPC_CSTR strUUID = NULL;
	UuidToString(&m_uuid, &strUUID);
	temp = (char*)strUUID;
	RpcStringFree(&strUUID);
	return temp;

#else

	char strUUID[64] = "";
	uuid_unparse(m_uuid, strUUID);
	return strUUID;

#endif
	
}

bool CUUID::generate(CUUID& a_uuid)
{
#if defined( WIN32 )

	return UuidCreate(&a_uuid.m_uuid) == RPC_S_OK;

#else

	uuid_generate(a_uuid.m_uuid);
	return true;

#endif
}

}//Utility

}//BSLib
