using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    class CScenelSystemMsgNumID
    {
        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_REVIVE = 1;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_REVIVE = 2;
    }

    class CMsgSceneSystemGC2GMReqRoleRevive : UnityFrame.CMsg
    {
        public CMsgSceneSystemGC2GMReqRoleRevive()
            : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SCENESYSTEM, CScenelSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GC2GM_REQ_REVIVE)
        {
        }

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

    class CMsgSceneSystemGM2GCAckRoleRevive : UnityFrame.CMsg
    {
        public byte m_result;
        static public CClientCore.CBMsgSceneSystemGM2GCAckRoleRevive s_cb = null;

        public CMsgSceneSystemGM2GCAckRoleRevive()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SCENESYSTEM, CScenelSystemMsgNumID.EMSGNUMID_SCENESYSTEM_GM2GC_ACK_REVIVE)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_result = msgStream.ReadByte();
            return true;
        }

        static public void CallBack(CMsgSceneSystemGM2GCAckRoleRevive msg)
        {
            if (msg != null)
            {
                if (s_cb != null)
                {
                    s_cb((UnityGMClient.ESceneRoleReviveError)msg.m_result);
                }
            }
        }
    }


}
