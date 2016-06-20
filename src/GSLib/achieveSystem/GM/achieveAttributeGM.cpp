//////////////////////////////////////////////////////////////////////
//	created:	2014/07/29
//	filename: 	src\GSLib\achieveSystem\GM\itemAttributeGM.cpp
//	author:	    zhangping	
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include "GSLib/achieveSystem/GM/achieveAttributeGM.h"
#include <GSLib/tracer.h>

namespace GSLib
{

namespace AchieveSystem
{	

namespace GM
{
CAchieveItem::CAchieveItem(AchieveID a_achieveID, EAchieveType a_type, EAchieveStatus a_status, BSLib::uint32 a_count)
:m_achieveID(a_achieveID)
,m_achieveType(a_type)
,m_achieveStatus(a_status)
,m_achieveProgress(a_count)
{
}

CAchieveItem::~CAchieveItem()
{
}

void CAchieveItem::serializeTo(BSLib::Utility::CStream& stream) const
{
	stream << m_achieveID;
	stream << m_achieveType;
	stream << m_achieveStatus;
	stream << m_achieveProgress;
}

}//GM

}//PlayerSystem

}//GSLib
