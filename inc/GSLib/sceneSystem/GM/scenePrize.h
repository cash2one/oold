#ifndef		__GSLIB_SCENESYSTEM_GM_SCENEPRIZE_H__
#define		__GSLIB_SCENESYSTEM_GM_SCENEPRIZE_H__

#include <BSLib/utility/baseDef.h>


namespace GSLib
{
namespace SceneSystem
{

namespace GM
{
class CScenePrize	
{
public:
	CScenePrize(BSLib::int32 a_itemID);
	~CScenePrize();
public:
	void setItemID(BSLib::int32 a_itemID);
	BSLib::int32 getItemID() const;
private:
	BSLib::uint32 m_itemID;
};

} // GM

} // SceneSystem

} // GSLib



#endif


