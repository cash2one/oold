#include <GSLib/sceneSystem/GM/scenePrize.h>

namespace GSLib
{
namespace SceneSystem
{
namespace GM 
{

CScenePrize::CScenePrize(BSLib::int32 a_itemID)
:m_itemID(a_itemID)
{
}

CScenePrize::~CScenePrize()
{
}

void CScenePrize::setItemID(BSLib::int32 a_itemID)
{
	m_itemID = a_itemID;
}

BSLib::int32 CScenePrize::getItemID() const
{
	return m_itemID;
}



} // GM 

} // SceneSystem

} // GSLib







