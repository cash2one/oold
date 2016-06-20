#include <GSLib/sceneSystem/GM/reviveItem.h>

namespace GSLib
{
namespace SceneSystem
{
namespace GM
{

CReviveItem::CReviveItem()
:m_reviveTimes(0)
,m_costDiamonds(0)
{
;
}

CReviveItem::~CReviveItem()
{
;
}

void CReviveItem::setReviveTimes(BSLib::uint32 a_reviveTimes)
{
	m_reviveTimes = a_reviveTimes;
}

BSLib::uint32 CReviveItem::getReviveTimes() const
{
	return m_reviveTimes;
}

void CReviveItem::setConstDiamond(BSLib::uint32 a_diamonds)
{
	m_costDiamonds = a_diamonds;
}

BSLib::uint32 CReviveItem::getConstDiamonds()
{
	return m_costDiamonds;
}

}//GM

}//SceneSystem

}//GSLib