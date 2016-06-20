#ifndef			__GSLIB_SCENESYSTEM_GM__DROPITEM_H__
#define			__GSLIB_SCENESYSTEM_GM__DROPITEM_H__

#include <BSLib/utility/baseDef.h>
#include <GSLib/itemSystem/GM/itemAttributeGM.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

class CDropItem
{
public:
	CDropItem();
	~CDropItem();
public:
	BSLib::uint32 m_itemTPID;	
	BSLib::uint32 m_itemCount;
	BSLib::uint32 m_weight;
	BSLib::uint32 m_totalWeight;
};

}//GM

}//SceneSystem

}//GSLib



#endif

