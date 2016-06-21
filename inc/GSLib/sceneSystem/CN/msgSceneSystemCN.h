#ifndef __GSLIB_SCENESYSTEM_CN_MSGSCENESYSTEMCN_H__
#define __GSLIB_SCENESYSTEM_CN_MSGSCENESYSTEMCN_H__

#include <GSLib/sceneSystem/msgNumIDSceneSystem.h>
#include <GSLib/sceneSystem/sceneSystemDefine.h>
#include <GSLib/sceneSystem/sceneSystemCommonData.h>

namespace GSLib
{

namespace SceneSystem
{
	const BSLib::uint32 MsgIDSceneSystemGM2CNReqArenaAction = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_CHATSYSTEM, EMSGNUMID_SCENESYSTEM_GM2CN_REQ_ARENA_ACTION);
	class CMsgSceneSystemGM2CNReqArenaAction: public GFLib::CMessage
	{
	public:
		CMsgSceneSystemGM2CNReqArenaAction() 
		:GFLib::CMessage(MsgIDSceneSystemGM2CNReqArenaAction)
		,m_actionID(EARENA_ACTION_NONE )
		,m_param1(0)
		,m_param2(0)
		,m_param3(0)
		{
		}
	protected:
		bool _serializeTo(BSLib::Utility::CStream& stream) const
		{
			stream << (BSLib::uint8)m_actionID;
			stream << m_param1;
			stream << m_param2;
			stream << m_param3;
			m_challengerRecord.serializeTo(stream);
			m_challengeeRecord.serializeTo(stream);
			return true;
		}

		bool _serializeFrom(BSLib::Utility::CStream& stream)
		{
			BSLib::uint8 actionID = 0;
			stream >> actionID;
			m_actionID = (EArenaAction)actionID;
			stream >> m_param1;
			stream >> m_param2;
			stream >> m_param3;
			m_challengerRecord.serializeFrom(stream);
			m_challengeeRecord.serializeFrom(stream);
			return true;
		}
	public:
		EArenaAction m_actionID;
		BSLib::uint32 m_param1;
		BSLib::uint32 m_param2;
		BSLib::uint32 m_param3;
		SceneSystem::CArenaChallengeRecord m_challengerRecord;
		SceneSystem::CArenaChallengeRecord m_challengeeRecord;
	};

	//------------------------------------------------------------------------------------------------------------

}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_CN_MSGSCENESYSTEMCN_H__

