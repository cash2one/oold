#include <GSLib/sceneSystem/GM/dropItemEntry.h>
#include <GSLib/sceneSystem/GM/dropItem.h>
#include <BSLib/utility/random.h>


namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

CDropTableEntry::CDropTableEntry()
:m_ID(0)
{
;
}

CDropTableEntry::~CDropTableEntry()
{
	for (BSLib::Utility::CHashMap<BSLib::uint32, CDropItem*>::iterator itr = m_mapDropItems.begin(); itr != m_mapDropItems.end(); ++itr) {
		if (itr->second != NULL) {
			delete itr->second, itr->second = NULL;
		}
	}

	m_mapDropItems.clear();
}

void CDropTableEntry::addDropItem(CDropItem *dropItem)
{
	if (dropItem != NULL) {
		if (m_mapDropItems.find(dropItem->m_itemTPID) == m_mapDropItems.end()) {
			m_mapDropItems.setValue(dropItem->m_itemTPID, dropItem);
		}
	}
}

const CDropItem* CDropTableEntry::getRandomItem() const
{
	BSLib::int32 start = 1;
	BSLib::int32 end = 101;
	BSLib::int32 randNum = BSLib::Utility::CRandom::randomBetween(start, end);		
	for (BSLib::Utility::CHashMap<BSLib::uint32, CDropItem*>::const_iterator itr = m_mapDropItems.begin(); itr != m_mapDropItems.end(); ++itr ) {
		if (randNum >= (BSLib::int32)itr->second->m_weight) {
			return itr->second;
		}
	}

	return NULL;
}

bool CDropTableEntry::IsValid() const
{
	BSLib::uint32 totalProbability = 0;
	for (BSLib::Utility::CHashMap<BSLib::uint32, CDropItem*>::const_iterator itr = m_mapDropItems.begin(); itr != m_mapDropItems.end(); ++itr) {
		totalProbability += itr->second->m_weight;	
	}
	
	return	totalProbability <= 100;
}


//bool IsValid()




}//GM

}//SceneSystem

}//GSLib






