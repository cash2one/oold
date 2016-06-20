using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    class CLoginSystemMsgNumID
    {
         public const uint EMSGNUMID_LOGINSYSTEM_GC2LG_REQ_ACCOUNT_LOGIN = 1;
         public const uint EMSGNUMID_LOGINSYSTEM_LG2GC_ACK_ACCOUNT_LOGIN = 2;
         public const uint EMSGNUMID_LOGINSYSTEM_GC2GT_REQ_ACCOUNT_LOGIN = 3;
         public const uint EMSGNUMID_LOGINSYSTEM_GT2GC_ACK_ACCOUNT_LOGIN = 4;
         public const uint EMSGNUMID_LOGINSYSTEM_GC2LG_REQ_REGISTER_ACCOUNT = 52;
         public const uint EMSGNUMID_LOGINSYSTEM_LG2GC_ACK_REGISTER_ACCOUNT = 53;
         public const uint EMSGNUMID_LOGINSYSTEM_GC2LG_REQ_GET_ACCOUNT_TAKEN = 58;
         public const uint EMSGNUMID_LOGINSYSTEM_LG2GC_ACK_GET_ACCOUNT_TAKEN = 59;

         public const uint EMSGNUMID_LOGINSYSTEM_GC2LG_REQ_TAKEN_LOGIN = 60;
         public const uint EMSGNUMID_LOGINSYSTEM_LG2GC_ACK_TAKEN_LOGIN = 61;
    }

    class CMsgLoginSystemGC2LGReqAccountLogin : UnityFrame.CMsg
    {
        public CMsgLoginSystemGC2LGReqAccountLogin()
            : base(CServerType.SRVTYPE_LOGINSERVER, CFuncType.EFUNCTYPE_LOGINSYSTEM, CLoginSystemMsgNumID.EMSGNUMID_LOGINSYSTEM_GC2LG_REQ_ACCOUNT_LOGIN)
        {

        }
        public string m_account = "";
        public string m_password = "";
        public ushort m_zoneID = 0;
        public uint m_channelID = 0;

        public string m_uniqueID = "";
        public string m_uniqueKey = "";
        public string m_platform = "";
        public uint m_loginType = (uint)ELoginType.ELOGINTYPE_NORMAL_LOGIN;
        public string m_token;
        public UInt64 m_accountID = 0;
        

        //把数据序列化到msgBuffer中
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_account);
            msgStream.Write(m_password);
            msgStream.Write(m_zoneID);
            msgStream.Write(m_channelID);

            msgStream.Write(m_uniqueID);
            msgStream.Write(m_uniqueKey);
            msgStream.Write(m_platform);
            msgStream.Write(m_loginType);
            msgStream.Write(m_token);
            msgStream.Write(m_accountID);
            return true;
        }
    }

    class CMsgLoginSystemLG2GCAckAccountLogin : UnityFrame.CMsg
    {
        public CMsgLoginSystemLG2GCAckAccountLogin()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_LOGINSYSTEM, CLoginSystemMsgNumID.EMSGNUMID_LOGINSYSTEM_LG2GC_ACK_ACCOUNT_LOGIN)
        {

        }
        public uint m_state;
        public string m_gameServerIP = "";
        public ushort m_gameServerPort = 0;
        public uint m_loginKey = 0;
        public uint m_loginSession = 0;
        public SAccountKey m_accountKey = new SAccountKey();

        //从msgBuffer中序列化数据
        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_state = msgStream.ReadUInt();

            if (m_state != 0)
            {
                return true;
            }
            m_gameServerIP = msgStream.ReadString();
            m_gameServerPort = msgStream.ReadUShort();
            m_loginKey = msgStream.ReadUInt();
            m_loginSession = msgStream.ReadUInt();
            m_accountKey = (SAccountKey)msgStream.ReadObject(typeof(SAccountKey));
            
            return true;
        }
    }

    class CMsgLoginSystemGC2GMReqAccountLogin : UnityFrame.CMsg
    {
        public CMsgLoginSystemGC2GMReqAccountLogin()
        :base(CServerType.SRVTYPE_GATESERVER, CFuncType.EFUNCTYPE_LOGINSYSTEM, CLoginSystemMsgNumID.EMSGNUMID_LOGINSYSTEM_GC2GT_REQ_ACCOUNT_LOGIN)
        {

        }

        public uint m_loginKey = 0;
        public uint m_loginSession = 0;
        public uint m_channelID = 0;
        public SAccountKey m_accountKey =  new SAccountKey();

        //把数据序列化到msgBuffer中
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_loginSession);
            msgStream.Write(m_loginKey);
            msgStream.Write(m_channelID);
            msgStream.Write(m_accountKey);
            return true;
        }
    }

    class CMsgLoginSystemGM2GCAckAccountLogin : UnityFrame.CMsg
    {
        public CMsgLoginSystemGM2GCAckAccountLogin()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_LOGINSYSTEM, CLoginSystemMsgNumID.EMSGNUMID_LOGINSYSTEM_GT2GC_ACK_ACCOUNT_LOGIN)
        {

        }

        public uint m_state = 0;

        //从msgBuffer中序列化数据
        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_state = msgStream.ReadUInt();
            return true;
        }
        public static CClientCore.CBMsgLoginSystemGM2GCAckAccountLogin cb = null;
        public static void CallBack(CMsgLoginSystemGM2GCAckAccountLogin msg)
        {
            if (CMsgLoginSystemGM2GCAckAccountLogin.cb == null)
            {
                return;
            }

            CMsgLoginSystemGM2GCAckAccountLogin.cb((EErrorPlayerLoginServer)msg.m_state);
        }
    }


    /// <summary>
    /// 账号注册
    /// </summary>
    class CMsgLoginSystemGC2LGReqRegisterAccount : UnityFrame.CMsg
    {
        public CMsgLoginSystemGC2LGReqRegisterAccount()
            : base(CServerType.SRVTYPE_LOGINSERVER, CFuncType.EFUNCTYPE_LOGINSYSTEM, CLoginSystemMsgNumID.EMSGNUMID_LOGINSYSTEM_GC2LG_REQ_REGISTER_ACCOUNT)
        {

        }
        public string m_account = "";
        public string m_password = "";
        public uint m_channelID = 0;
        public string m_uniqueID = "";
        public string m_uniqueKey = "";
        public string m_platform = "";
        public uint m_regeisterType = (uint)ERegisterType.EREGEITERTYPE_FAST_REGISTER;
        public string m_activationCode = "";


        //把数据序列化到msgBuffer中
        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_account);
            msgStream.Write(m_password);
            msgStream.Write(m_channelID);

            msgStream.Write(m_uniqueID);
            msgStream.Write(m_uniqueKey);
            msgStream.Write(m_platform);
            msgStream.Write(m_regeisterType);
            msgStream.Write(m_activationCode);
            return true;
        }
    }

    class CMsgLoginSystemLG2GCAckRegisterAccount : UnityFrame.CMsg
    {
        public CMsgLoginSystemLG2GCAckRegisterAccount()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_LOGINSYSTEM, CLoginSystemMsgNumID.EMSGNUMID_LOGINSYSTEM_LG2GC_ACK_REGISTER_ACCOUNT)
        {

        }
        public uint m_state;

        //从msgBuffer中序列化数据
        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_state = msgStream.ReadUInt();
            return true;
        }

        public static CClientCore.CBMsgLoginSystemLG2GCAckRegisterAccount cb = null;
        public static void CallBack(CMsgLoginSystemLG2GCAckRegisterAccount msg)
        {
            if (CMsgLoginSystemLG2GCAckRegisterAccount.cb == null)
            {
                return;
            }

            CMsgLoginSystemLG2GCAckRegisterAccount.cb((ERegisterResult)msg.m_state);
        }
    }

    /// <summary>
    /// 获取Taken
    /// </summary>
    class CMsgLoginSystemGC2LGReqGetAccountToken : UnityFrame.CMsg
    {
        public CMsgLoginSystemGC2LGReqGetAccountToken()
            : base(CServerType.SRVTYPE_LOGINSERVER, CFuncType.EFUNCTYPE_LOGINSYSTEM, CLoginSystemMsgNumID.EMSGNUMID_LOGINSYSTEM_GC2LG_REQ_GET_ACCOUNT_TAKEN)
        {

        }
        public string m_account = "";
        public string m_password = "";
        public uint m_channelID = 0;
        public string m_uniqueID = "";
        public string m_uniqueKey = "";
        public string m_platform = "";
        public uint m_getTakenType = (uint)ELoginType.ELOGINTYPE_NORMAL_LOGIN;

        protected override bool _SerializeTo(UnityUtility.CStream msgStream)
        {
            msgStream.Write(m_account);
            msgStream.Write(m_password);
            msgStream.Write(m_channelID);

            msgStream.Write(m_uniqueID);
            msgStream.Write(m_uniqueKey);
            msgStream.Write(m_platform);
            msgStream.Write(m_getTakenType);
            return true;
        }
    }

    class CMsgLoginSystemLG2GCAckGetAccountToken : UnityFrame.CMsg
    {
        public CMsgLoginSystemLG2GCAckGetAccountToken()
            : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_LOGINSYSTEM, CLoginSystemMsgNumID.EMSGNUMID_LOGINSYSTEM_LG2GC_ACK_GET_ACCOUNT_TAKEN)
        {

        }
        public uint m_state = (uint)EGetAccountTokenResult.EGETACCOUNTTAKEN_TOKEN_FAIL;
        public string m_token="";
        public UInt64 m_accountID=0;

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            m_state = msgStream.ReadUInt();
            m_token = msgStream.ReadString();
            m_accountID = msgStream.ReadULong();
            return true;
        }

        public static CClientCore.CBMsgLoginSystemLG2GCAckGetAccountToken cb = null;
        public static void CallBack(CMsgLoginSystemLG2GCAckGetAccountToken msg)
        {
            if (CMsgLoginSystemLG2GCAckGetAccountToken.cb == null)
            {
                return;
            }

            CMsgLoginSystemLG2GCAckGetAccountToken.cb((EGetAccountTokenResult)msg.m_state, msg.m_accountID, msg.m_token);
        }
    }
}
