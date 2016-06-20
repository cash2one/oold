#include <GSLib/sceneSystem/GM/arenaPrize.h>

namespace GSLib
{
namespace SceneSystem
{
namespace GM 
{

CArenaPrize::CArenaPrize(BSLib::int64 a_gold, BSLib::uint32 a_diamond, BSLib::uint32 a_pvpCoin)
:m_gold(a_gold)
,m_diamond(a_diamond)
,m_pvpCoin(a_pvpCoin)
{
}

CArenaPrize::~CArenaPrize()
{
}

} // GM 

} // SceneSystem

} // GSLib







