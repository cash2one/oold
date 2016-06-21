#ifndef		__GSLIB_SCENESYSTEM_GM_SCENEDATA_H__
#define		__GSLIB_SCENESYSTEM_GM_SCENEDATA_H__

#include <BSLib/utility/baseDef.h>
#include <GSLib/baseDef.h>

namespace GSLib
{

namespace SceneSystem
{
namespace GM
{
class CSceneData
{
public:
	CSceneData();
	~CSceneData();
public:
	SceneTPID m_TPID;
	BSLib::uint16 m_starRank;	
	BSLib::uint16 m_dailyFinishedTimes;
	BSLib::uint32 m_reviveTimes;
};

}//GM
}//SceneSystem

}//GSLib






#endif











