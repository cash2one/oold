//////////////////////////////////////////////////////////////////////
//	created:	2015/7/2
//	filename: 	GSLib\chatSystem\GM\chatSystemData.cpp
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////

#include <GSLib/chatSystem/GM/chatSystemData.h>
#include <BSLib/utility/stream.h>

namespace GSLib
{

namespace ChatSystem
{

namespace GM
{

CChatEquipID::CChatEquipID()
:m_bagIndex(-1)
,m_equipID(-1)
{

}

CChatEquipID::~CChatEquipID()
{

}

void CChatEquipID::serializeFrom(BSLib::Utility::CStream& stream) const
{
	stream >> m_bagIndex;
	stream >> m_equipID;
}

}//GM

}//ChatSystem

}//GSLib




