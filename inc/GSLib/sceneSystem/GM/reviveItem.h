#ifndef		__GSLIB_SCENESYSTEM_GM_REVIVEITEM_H__
#define		__GSLIB_SCENESYSTEM_GM_REVIVEITEM_H__

#include <BSLib/utility/baseDef.h>


namespace GSLib
{
namespace SceneSystem
{

namespace GM
{
class CReviveItem
{
public:
	CReviveItem();
	~CReviveItem();
public:
	void setReviveTimes(BSLib::uint32 a_reviveTimes);
	BSLib::uint32 getReviveTimes() const;

	void setConstDiamond(BSLib::uint32 a_diamonds);
	BSLib::uint32 getConstDiamonds();

private:
	BSLib::uint32 m_reviveTimes;
	BSLib::uint32 m_costDiamonds;
};

}//GM

}//SceneSystem

}//GSLib








#endif





