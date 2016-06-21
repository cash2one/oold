#include <BSLib/utility/baseDef.h>

#ifndef		__GSLIB_CHATSYSTEM_CHATSYSTEMDATA_H__
#define		__GSLIB_CHATSYSTEM_CHATSYSTEMDATA_H__

namespace BSLib
{
namespace Utility
{
	class CStream;
}

}

namespace GSLib
{

namespace ChatSystem
{

namespace GM
{

class CChatEquipID
{
public:
	enum {invalid_index = 0xffff,};
public:
	CChatEquipID();
	~CChatEquipID();
public:
	void serializeFrom(BSLib::Utility::CStream& stream) const;
public:
	BSLib::uint32 m_bagIndex;
	BSLib::uint32 m_equipID;
};

}//GM

}//ChatSystem

}//GSLib

#endif




