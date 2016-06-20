using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    partial class CLoginSystem
    {
        public bool FastEnterServerAsync()
        {
            if (!CanLoginServer)
            {
                return false;
            }

            if (CGameClient.Singleton.IsConnected)
            {
                SetLoginState(LoginState.CONNECT_LOGINSERVER_WAIT_CONNECT);
                if (m_loginState != LoginState.CONNECT_LOGINSERVER_WAIT_CONNECT)
                {
                    SetLoginState(LoginState.CONNECT_LOGINSERVER_FAIL);
                    CGameClient.Singleton.Disconnect();
                    return false;
                }
                SetLoginState(LoginState.CONNECT_LOGINSERVER_WAIT_LOGIN);

                if (!SendMsgToLGGetGateWay())
                {
                    SetLoginState(LoginState.CONNECT_LOGINSERVER_FAIL);
                    SetLoginResult(EErrorPlayerLoginServer.ELOGINRESULT_CONNECT_ERROR);
                    CGameClient.Singleton.Disconnect();
                    return false;
                }
                return true;
            }

            EnterServerAsync();

            return true;
        }

        public bool RegisterAccountAsync()
        {
            bool bConnect = ConnectServer(m_serverIP, m_serverPort, EConnectServerType.CONNECT_SERVER_LG, EConnectCallBack.CONNECT_CB_REGEITER);
            if (!bConnect)
            {
                RegisterCallBack(ERegisterResult.EREGISTERRESULT_FAIL);
                return false;
            }
            return true;
        }

        public bool ReenterGameServerAsync()
        {
            if (!SendMsgToGTAccountLogin())
            {
                SetLoginState(LoginState.CONNECT_GAMESERVER_FAIL);
                CGameClient.Singleton.Disconnect();
                SetLoginResult(EErrorPlayerLoginServer.ELOGINRESULT_CONNECT_ERROR);
                return false;
            }
            return false;
        }

        public bool DiscounnectGame()
        {
            CGameClient.Singleton.Disconnect();
            return true;
        }

        private bool ConnectServer(string a_ip, ushort a_port, EConnectServerType a_serverType, EConnectCallBack a_msgType)
        {
            if (CGameClient.Singleton.IsConnected)
            {
                return false;
            }
            ConnectServerType = a_serverType;
            ConnectCallBackType = a_msgType;

            UnityUtility.CTrace.Singleton.debug("[EnterServerAsync][ConnectAsync][ip{0}:{1}]", a_ip.ToString(), a_port.ToString());
            if (!CGameClient.Singleton.ConnectAsync(a_ip, a_port))
            {
                return false;
            }
            return true;
        }

        /// <summary>
        /// 连接成功
        /// </summary>
        private void OnServerConnectSuccess()
        {
            switch (ConnectServerType)
            {
                case EConnectServerType.CONNECT_SERVER_LG:
                    {
                        switch (ConnectCallBackType)
                        {
                            case EConnectCallBack.CONNECT_CB_GET_GT: { OnConnectLoginServerRequestSuccess(); } break;
                            case EConnectCallBack.CONNECT_CB_GET_TOKEN: { OnConnectLoginServerRequestSuccessForGetLoginTaken(); } break;
                            case EConnectCallBack.CONNECT_CB_REGEITER: { OnConnectLoginServerRequestSuccessForRegister(); } break;
                            default: break;
                        }
                    }
                    break;
                case EConnectServerType.CONNECT_SERVER_GT:
                    {
                        switch (ConnectCallBackType)
                        {
                            case EConnectCallBack.CONNECT_CB_CONNECT_GT: { OnConnectGameServerRequestSuccess(); } break;
                            case EConnectCallBack.CONNECT_CB_RECONNECT_GT: { OnReConnectGameServerRequestSuccess(); } break;
                            default: break;
                        }
                    }
                    break;
            }
        }

        /// <summary>
        /// 连接失败
        /// </summary>
        private void OnServerConnectFail()
        {
            UnityUtility.CTrace.Singleton.debug("OnServerConnectFail");
            switch (ConnectServerType)
            {
                case EConnectServerType.CONNECT_SERVER_LG:
                    {
                        switch (ConnectCallBackType)
                        {
                            case EConnectCallBack.CONNECT_CB_GET_GT: { OnConnectLoginServerRequestFail(); } break;
                            case EConnectCallBack.CONNECT_CB_GET_TOKEN: { OnConnectLoginServerRequestFailForGetLoginTaken(); } break;
                            case EConnectCallBack.CONNECT_CB_REGEITER: { OnConnectLoginServerRequestFailForRegister(); } break;
                            default: break;
                        }
                    }
                    break;
                case EConnectServerType.CONNECT_SERVER_GT:
                    {
                        switch (ConnectCallBackType)
                        {
                            case EConnectCallBack.CONNECT_CB_CONNECT_GT: { OnConnectGameServerRequestFail(); } break;
                            case EConnectCallBack.CONNECT_CB_RECONNECT_GT: { OnReConnectGameServerRequestFail(); } break;
                            default: break;
                        }
                    }
                    break;
            }
        }

        /// <summary>
        /// 网络关闭
        /// 
        /// 
        /// </summary>
        private void OnServerConnectClose()
        {
            UnityUtility.CTrace.Singleton.debug("[OnServerConnectClose]");
            switch (ConnectServerType)
            {
                case EConnectServerType.CONNECT_SERVER_LG:
                    {
                        switch (ConnectCallBackType)
                        {
                            case EConnectCallBack.CONNECT_CB_GET_GT: { OnConnectLoginServerClose(); } break;
                            case EConnectCallBack.CONNECT_CB_GET_TOKEN: { OnConnectLoginServerCloseForGetLoginTaken(); } break;
                            case EConnectCallBack.CONNECT_CB_REGEITER: { OnConnectLoginServerCloseForRegister(); } break;
                            default: break;
                        }
                    }
                    break;
                case EConnectServerType.CONNECT_SERVER_GT:
                    {
                        switch (ConnectCallBackType)
                        {
                            case EConnectCallBack.CONNECT_CB_CONNECT_GT: { OnConnectGameServerClose(); } break;
                            case EConnectCallBack.CONNECT_CB_RECONNECT_GT: { OnReConnectGameServerClose(); } break;
                            default: break;
                        }
                    }
                    break;
            }
        }

        private void OnConnectLoginServerRequestSuccess()
        {
            UnityUtility.CTrace.Singleton.debug("[OnConnectLoginServerRequestSuccess][m_loginState={0}]\r\n", ((LoginState)m_loginState).ToString());
            if (m_loginState != LoginState.CONNECT_LOGINSERVER_WAIT_CONNECT)
            {
                SetLoginState(LoginState.CONNECT_LOGINSERVER_FAIL);
                CGameClient.Singleton.Disconnect();
                return;
            }
            SetLoginState(LoginState.CONNECT_LOGINSERVER_WAIT_LOGIN);
            if (!SendMsgToLGGetGateWay())
            {
                SetLoginState(LoginState.CONNECT_LOGINSERVER_FAIL);
                SetLoginResult(EErrorPlayerLoginServer.ELOGINRESULT_CONNECT_ERROR);
                CGameClient.Singleton.Disconnect();
                return;
            }
        }

        private void OnConnectLoginServerRequestFail()
        {
            UnityUtility.CTrace.Singleton.error("[OnConnectLoginServerRequestFail]\r\n");
            SetLoginState(LoginState.CONNECT_LOGINSERVER_FAIL);
            SetLoginResult(EErrorPlayerLoginServer.ELOGINRESULT_CONNECT_ERROR);
        }

        private void OnConnectLoginServerClose()
        {
            UnityUtility.CTrace.Singleton.debug("[OnConnectLoginServerClose][m_loginState={0}]\r\n", m_loginState.ToString());
            if (m_loginState == LoginState.CONNECT_LOGINSERVER_SUCCESS)
            {
                EnterGTAsync();
                return;
            }
            SetLoginState(LoginState.CONNECT_LOGINSERVER_FAIL);
            SetLoginResult(EErrorPlayerLoginServer.ELOGINRESULT_CONNECT_ERROR);
        }

        private void OnConnectGameServerRequestSuccess()
        {
            UnityUtility.CTrace.Singleton.debug("[OnConnectGameServerRequestSuccess][m_loginState={0}]\r\n", m_loginState.ToString());
            if (m_loginState != LoginState.CONNECT_GAMESERVER_WAIT_CONNECT)
            {
                SetLoginState(LoginState.CONNECT_GAMESERVER_FAIL);
                CGameClient.Singleton.Disconnect();
                return;
            }

            SetLoginState(LoginState.CONNECT_GAMESERVER_WAIT_LOGIN);
            if (!SendMsgToGTAccountLogin())
            {
                SetLoginState(LoginState.CONNECT_GAMESERVER_FAIL);
                CGameClient.Singleton.Disconnect();
                SetLoginResult(EErrorPlayerLoginServer.ELOGINRESULT_CONNECT_ERROR);
                return;
            }
        }

        private void OnConnectGameServerRequestFail()
        {
            UnityUtility.CTrace.Singleton.error("[OnConnectGameServerRequestFail][m_loginState={0}]\r\n", m_loginState.ToString());
            if (LoginState.CONNECT_NULL == m_loginState)
            {
                return;
            }
            SetLoginState(LoginState.CONNECT_GAMESERVER_FAIL);
            SetLoginResult(EErrorPlayerLoginServer.ELOGINRESULT_CONNECT_ERROR);
        }

        private void OnConnectGameServerClose()
        {
            UnityUtility.CTrace.Singleton.debug("[OnConnectGameServerClose][m_loginState={0}]\r\n", m_loginState.ToString());
            if (m_loginState == LoginState.CONNECT_GAMESERVER_SUCCESS)
            {
                SetLoginState(LoginState.CONNECT_NULL);
                //触发断线重连
                //CGameClient.Singleton.SendMsgReConnectServer();
                NotifyNetState(ENetStatus.ENETSTATUS_OFFLINE);
                return;
            }
            SetLoginState(LoginState.CONNECT_GAMESERVER_FAIL);
            SetLoginResult(EErrorPlayerLoginServer.ELOGINRESULT_CONNECT_ERROR);
        }


        private void OnReConnectGameServerRequestSuccess()
        {
            UnityUtility.CTrace.Singleton.error("[OnReConnectGameServerRequestSuccess][m_loginState={0}]\r\n", m_loginState.ToString());
            if (ConnectCallBackType == EConnectCallBack.CONNECT_CB_RECONNECT_GT)
            {
                ReenterGameServerAsync();
                return;
            }
        }

        private void OnReConnectGameServerRequestFail()
        {
            UnityUtility.CTrace.Singleton.error("[OnReConnectGameServerRequestFail][m_loginState={0}]\r\n", m_loginState.ToString());
            //SetLoginState(LoginState.CONNECT_GAMESERVER_FAIL);
            NotifyNetState(ENetStatus.ENETSTATUS_RECONNECT_FAIL);
        }

        private void OnReConnectGameServerClose()
        {
            UnityUtility.CTrace.Singleton.debug("[OnReConnectGameServerClose][m_loginState={0}]\r\n", m_loginState.ToString());
            if (m_loginState == LoginState.CONNECT_GAMESERVER_SUCCESS)
            {
                SetLoginState(LoginState.CONNECT_NULL);
                //触发断线重连
                //CGameClient.Singleton.SendMsgReConnectServer();
                NotifyNetState(ENetStatus.ENETSTATUS_OFFLINE);
                return;
            }
            SetLoginState(LoginState.CONNECT_GAMESERVER_FAIL);
        }


        private void OnConnectLoginServerRequestSuccessForRegister()
        {
            UnityUtility.CTrace.Singleton.debug("[OnConnectLoginServerRequestSuccessForRegister]\r\n");
            if (!SendMsgToLGRegisterAccount())
            {
                RegisterCallBack(ERegisterResult.EREGISTERRESULT_FAIL);
                return;
            }
        }

        private void OnConnectLoginServerRequestFailForRegister()
        {
            UnityUtility.CTrace.Singleton.error("[OnConnectLoginServerRequestFailForRegister]\r\n");
            RegisterCallBack(ERegisterResult.EREGISTERRESULT_FAIL);
        }

        private void OnConnectLoginServerCloseForRegister()
        {
            UnityUtility.CTrace.Singleton.debug("[OnConnectLoginServerRequestSuccessForRegister][m_registerResult={0}]\r\n", m_registerResult.ToString());
            RegisterCallBack(m_registerResult);
        }

        private void RegisterCallBack(ERegisterResult result)
        {
            if (result != ERegisterResult.EREGISTERRESULT_FAIL)
            {
                CGameClient.Singleton.Disconnect();
            }
            CMsgLoginSystemLG2GCAckRegisterAccount ack = new CMsgLoginSystemLG2GCAckRegisterAccount();
            ack.m_state = (uint)result;
            CMsgLoginSystemLG2GCAckRegisterAccount.CallBack(ack);
        }

        private void OnConnectLoginServerRequestSuccessForGetLoginTaken()
        {
            UnityUtility.CTrace.Singleton.error("[OnConnectLoginServerRequestSuccessForGetLoginTaken][m_getTakenResult={0}]\r\n", m_getTakenResult.ToString());
            if (!SendMsgToLGGetToken())
            {
                GetAccountTokenCallBack(EGetAccountTokenResult.EGETACCOUNTTAKEN_TOKEN_FAIL);
                return;
            }
        }

        private void OnConnectLoginServerRequestFailForGetLoginTaken()
        {
            UnityUtility.CTrace.Singleton.error("[OnConnectLoginServerRequestSuccessForRegister][m_getTakenResult={0}]\r\n", m_getTakenResult.ToString());
            GetAccountTokenCallBack(EGetAccountTokenResult.EGETACCOUNTTAKEN_TOKEN_FAIL);
        }

        private void OnConnectLoginServerCloseForGetLoginTaken()
        {
            UnityUtility.CTrace.Singleton.error("[OnConnectLoginServerCloseForGetLoginTaken][m_getTakenResult={0}]\r\n", m_getTakenResult.ToString());
            GetAccountTokenCallBack(m_getTakenResult);
        }

        private enum LoginState
        {
            CONNECT_NULL,
            CONNECT_LOGINSERVER_FAIL,
            CONNECT_LOGINSERVER_WAIT_CONNECT,
            CONNECT_LOGINSERVER_WAIT_LOGIN,
            CONNECT_LOGINSERVER_SUCCESS,
            CONNECT_GAMESERVER_FAIL,
            CONNECT_GAMESERVER_WAIT_CONNECT,
            CONNECT_GAMESERVER_WAIT_LOGIN,
            CONNECT_GAMESERVER_SUCCESS,
        }


        private enum GetTokenState
        {
            TOKENSTATE_NULL,
            TOKENSTATE_LOGINSERVER_FAIL,
            TOKENSTATE_LOGINSERVER_WAIT_CONNECT,
            TOKENSTATE_LOGINSERVER_WAIT_LOGIN,
            TOKENSTATE_LOGINSERVER_SUCCESS,
        }

        private enum OptionState
        {
            NULL,
            OPTION_LOGIN,
            OPTION_REGISTER,
        }

        private enum EGMNetStatus
        {
            GM_NETSTATUS_NULL,
            GM_NETSTATUS_RECONNECT,
        }

        public enum EConnectServerType
        {
            CONNECT_SERVER_NULL,
            CONNECT_SERVER_LG,
            CONNECT_SERVER_GT,
        }

        public enum EConnectCallBack
        {
            CONNECT_CB_NULL,
            CONNECT_CB_GET_TOKEN,
            CONNECT_CB_REGEITER,
            CONNECT_CB_GET_GT,
            CONNECT_CB_CONNECT_GT,
            CONNECT_CB_RECONNECT_GT,
        }

        public string ServerIP
        {
            get { return m_serverIP; }
            set { m_serverIP = value; }
        }

        public ushort ServerPort
        {
            get { return m_serverPort; }
            set { m_serverPort = value; }
        }

        //玩家账号
        public string Account
        {
            get { return m_account; }
            set { m_account = value; }
        }

        //玩家密码
        public string Password
        {
            get { return m_password; }
            set { m_password = value; }
        }

        //登录游戏区号
        public ushort ZoneID
        {
            get { return m_accountKey.m_zoneID; }
            set { m_accountKey.m_zoneID = value; }
        }

        public ulong AccountID
        {
            get { return m_accountKey.m_accountID; }
            set { m_accountKey.m_accountID = value; }
        }

        public SAccountKey AccountKey
        {
            get { return m_accountKey; }
            set { m_accountKey = value; }
        }

        //推广通道
        public uint ChannelID
        {
            get { return m_channelID; }
            set { m_channelID = value; }
        }

        public string UniqueID
        {
            get { return m_uniqueID; }
            set { m_uniqueID = value; }
        }

        public string UniqueKey
        {
            get { return m_uniqueKey; }
            set { m_uniqueKey = value; }
        }

        public string ActivationKey
        {
            get { return m_activationCode; }
            set { m_activationCode = value; }
        }

        public string Token
        {
            get { return m_token; }
            set { m_token = value; }
        }

        public string Platform
        {
            get { return m_platform; }
            set { m_platform = value; }
        }

        public ELoginType LoginType
        {
            get { return m_loginType; }
            set { m_loginType = value; }
        }

        public ERegisterType RegisterType
        {
            get { return m_registerType; }
            set { m_registerType = value; }
        }

        public EConnectCallBack ConnectCallBackType
        {
            get { return m_curConnectCallBackType; }
            set { m_curConnectCallBackType = value; }
        }

        public EConnectServerType ConnectServerType
        {
            get { return m_curConnectServerType; }
            set { m_curConnectServerType = value; }
        }

        private string m_serverIP = "";
        private ushort m_serverPort = 0;
        private string m_account = "";
        private string m_password = "";
        //private ushort m_zoneID = 0;
        private uint m_channelID = 0;
        //private ulong m_accountID = 0;
        private string m_uniqueID = "";
        private string m_uniqueKey = "";
        private string m_platform = "";
        private string m_activationCode = "";
        private ELoginType m_loginType = ELoginType.ELOGINTYPE_NORMAL_LOGIN;
        private ERegisterType m_registerType = ERegisterType.EREGEITERTYPE_NORMAL_REGISTER;
        private LoginState m_loginState = LoginState.CONNECT_NULL;
        //private GetTokenState m_getTokenState = GetTokenState.TOKENSTATE_NULL;

        private string m_gameServerIP = "";
        private ushort m_gameServerPort = 0;
        private uint m_loginKey = 0;
        private uint m_loginSession = 0;
        private string m_token = "";

        private ERegisterResult m_registerResult = ERegisterResult.EREGISTERRESULT_FAIL;
        private EGetAccountTokenResult m_getTakenResult = EGetAccountTokenResult.EGETACCOUNTTAKEN_TOKEN_FAIL;

        private SAccountKey m_accountKey = new SAccountKey();

        private EConnectServerType m_curConnectServerType = EConnectServerType.CONNECT_SERVER_NULL;
        private EConnectCallBack m_curConnectCallBackType = EConnectCallBack.CONNECT_CB_NULL;
    }
}
