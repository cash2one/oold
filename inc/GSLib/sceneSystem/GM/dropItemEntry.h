#ifndef		__GSLIB_SCENESYSTEM_GM_DROPITEMENTRY_H__
#define		__GSLIB_SCENESYSTEM_GM_DROPITEMENTRY_H__

#include <BSLib/utility/baseDef.h>
#include <BSLib/utility/hashMap.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

	class CDropItem;

class CDropTableEntry
{
public:
	CDropTableEntry();
	~CDropTableEntry();
public:
	void addDropItem(CDropItem *dropItem);
	const CDropItem* getRandomItem() const;
	bool IsValid() const;
public:
	BSLib::uint32 m_ID;
	BSLib::Utility::CHashMap<BSLib::uint32, CDropItem*> m_mapDropItems;
};

}//GM

}//SceneSystem

}//GSLib


#endif








