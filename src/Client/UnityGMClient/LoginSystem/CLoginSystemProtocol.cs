using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace UnityGMClient
{
    class CNetSystem
    {
      public const uint EMSGNUMID_SERVERLINK_XS2XX_REQ_PING = 3;
      public const uint EMSGNUMID_SERVERLINK_XX2XS_RES_PING = 4;
      public delegate void CBPingGTNetStatu();


      public void Init()
      {
          CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(SMsgServerLinkXS2XXReqPing), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnSMsgServerLinkXS2XXReqPing));
      }

      private void OnSMsgServerLinkXS2XXReqPing(UnityFrame.CMsg msgData)
      {
          SMsgServerLinkXS2XXReqPing msg = new SMsgServerLinkXS2XXReqPing();
          CGameClient.Singleton.SendMsg(msg);
      }
    }

    //客户端与服务器之间的ping包
    class SMsgServerLinkXS2XXReqPing : UnityFrame.CMsg
    {
        public SMsgServerLinkXS2XXReqPing()
            : base(CServerType.ANY, CFuncType.LOCALNET, CNetSystem.EMSGNUMID_SERVERLINK_XS2XX_REQ_PING)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }

      class SMsgServerLinkXX2XSResPing : UnityFrame.CMsg
    {
        public SMsgServerLinkXX2XSResPing()
              : base(CServerType.ANY, CFuncType.LOCALNET, CNetSystem.EMSGNUMID_SERVERLINK_XX2XS_RES_PING)
        {
        }

        protected override bool _SerializeFrom(UnityUtility.CStream msgStream)
        {
            return true;
        }
    }
    partial class CLoginSystem
    {
        private UnityNetwork.CallbackNetState m_cbConnectServerSuccess = null;
        private UnityNetwork.CallbackNetState m_cbConnectServerFail = null;
        private UnityNetwork.CallbackNetState m_cbConnectServerClose = null;

        public void Init()
        {
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgLoginSystemLG2GCAckAccountLogin), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgLoginSystemLG2GCAckAccountLogin));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgLoginSystemGM2GCAckAccountLogin), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgLoginSystemGM2GCAckAccountLogin));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgLoginSystemLG2GCAckRegisterAccount), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgLoginSystemLG2GCAckRegisterAccount));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgLoginSystemLG2GCAckGetAccountToken), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgLoginSystemLG2GCAckGetAccountToken));

            m_cbConnectServerSuccess = new UnityNetwork.CallbackNetState(OnServerConnectSuccess);
            m_cbConnectServerFail = new UnityNetwork.CallbackNetState(OnServerConnectFail);
            m_cbConnectServerClose = new UnityNetwork.CallbackNetState(OnServerConnectClose);
            CGameClient.Singleton.RegisterEventCallBack(m_cbConnectServerSuccess, m_cbConnectServerFail, m_cbConnectServerClose);
        }

        public void Final()
        {
            CGameClient.Singleton.MsgExecMgr.DelParseMsgCb(typeof(CMsgLoginSystemLG2GCAckAccountLogin));
            CGameClient.Singleton.MsgExecMgr.DelParseMsgCb(typeof(CMsgLoginSystemGM2GCAckAccountLogin));
            CGameClient.Singleton.MsgExecMgr.DelParseMsgCb(typeof(CMsgLoginSystemLG2GCAckRegisterAccount));
            CGameClient.Singleton.MsgExecMgr.DelParseMsgCb(typeof(CMsgLoginSystemLG2GCAckGetAccountToken));
            CGameClient.Singleton.UnRegisterEventCallBack(m_cbConnectServerSuccess, m_cbConnectServerFail, m_cbConnectServerClose);
        }

        private bool CanLoginServer
        {
            get
            {
                switch (m_loginState)
                {
                    case LoginState.CONNECT_NULL:
                    case LoginState.CONNECT_LOGINSERVER_FAIL:
                    case LoginState.CONNECT_GAMESERVER_FAIL:
                        return true;
                    case LoginState.CONNECT_LOGINSERVER_WAIT_CONNECT:
                    case LoginState.CONNECT_GAMESERVER_WAIT_CONNECT:
                    case LoginState.CONNECT_GAMESERVER_SUCCESS:
                    default:
                        return false;
                }
            }
        }

        private void SetLoginState(LoginState state)
        {
            UnityUtility.CTrace.Singleton.debug("设置状态SetLoginState[{0}]", state.ToString());
            m_loginState = state;
        }

        private void SetLoginResult(EErrorPlayerLoginServer result)
        {
            if (ConnectCallBackType == EConnectCallBack.CONNECT_CB_RECONNECT_GT)
            {
                return;
            }
            CMsgLoginSystemGM2GCAckAccountLogin loginback = new CMsgLoginSystemGM2GCAckAccountLogin();
            loginback.m_state = (uint)result;
            CMsgLoginSystemGM2GCAckAccountLogin.CallBack(loginback);
        }

        private void NotifyNetState(ENetStatus netStatus)
        {
            if (CGameClient.NetStatusCallBack == null)
            {
                return;
            }
            CGameClient.NetStatusCallBack(netStatus);
        }

        private void OnMsgLoginSystemLG2GCAckAccountLogin(UnityFrame.CMsg msgData)
        {
            if (m_loginState != LoginState.CONNECT_LOGINSERVER_WAIT_LOGIN)
            {
                SetLoginState(LoginState.CONNECT_LOGINSERVER_FAIL);
                CGameClient.Singleton.Disconnect();
                return;
            }
            CMsgLoginSystemLG2GCAckAccountLogin accountLogin = (CMsgLoginSystemLG2GCAckAccountLogin)msgData;
            if ((EErrorPlayerLoginServer)accountLogin.m_state != EErrorPlayerLoginServer.ELOGINRESULT_SUCCESS)
            {
                SetLoginState(LoginState.CONNECT_LOGINSERVER_FAIL);
                CGameClient.Singleton.Disconnect();
                SetLoginResult((EErrorPlayerLoginServer)accountLogin.m_state);
                return;
            }
            m_gameServerIP = accountLogin.m_gameServerIP;
            m_gameServerPort = accountLogin.m_gameServerPort;
            m_loginKey = accountLogin.m_loginKey;
            m_loginSession = accountLogin.m_loginSession;
            m_accountKey = accountLogin.m_accountKey;

            SetLoginState(LoginState.CONNECT_LOGINSERVER_SUCCESS);
            CGameClient.Singleton.Disconnect();

            UnityUtility.CTrace.Singleton.debug("[LG][m_accountKey={0}][m_zoneID={1}]", m_accountKey.m_accountID.ToString(), m_accountKey.m_zoneID.ToString());
        }

        /// <summary>
        /// 连接网关回调
        /// </summary>
        /// <param name="msgData"></param>
        private void OnMsgLoginSystemGM2GCAckAccountLogin(UnityFrame.CMsg msgData)
        {
            if ((m_loginState != LoginState.CONNECT_GAMESERVER_WAIT_LOGIN) && (ConnectCallBackType != EConnectCallBack.CONNECT_CB_RECONNECT_GT))
            {
                SetLoginState(LoginState.CONNECT_GAMESERVER_FAIL);
                CGameClient.Singleton.Disconnect();
                return;
            }
            CMsgLoginSystemGM2GCAckAccountLogin accountLogin = (CMsgLoginSystemGM2GCAckAccountLogin)msgData;
            UnityUtility.CTrace.Singleton.debug("[GT][m_state={0}]]", ((EErrorPlayerLoginServer)accountLogin.m_state).ToString());
            if ((EErrorPlayerLoginServer)accountLogin.m_state != EErrorPlayerLoginServer.ELOGINRESULT_SUCCESS)
            {
                if ((EErrorPlayerLoginServer)accountLogin.m_state == EErrorPlayerLoginServer.ELOGINRESULT_SUCCESS_FIRST)
                {
                    if (ConnectCallBackType == EConnectCallBack.CONNECT_CB_RECONNECT_GT)
                    {
                        SendLostMsg();
                        return;
                    }
                    SetLoginState(LoginState.CONNECT_GAMESERVER_SUCCESS);
                    SetLoginResult(EErrorPlayerLoginServer.ELOGINRESULT_SUCCESS_FIRST);
                    return;
                }

                if (ConnectCallBackType == EConnectCallBack.CONNECT_CB_RECONNECT_GT)
                {
                    UnityUtility.CTrace.Singleton.debug("[GT][m_state={0}]][recoennect fail]", ((EErrorPlayerLoginServer)accountLogin.m_state).ToString());
                    NotifyNetState(ENetStatus.ENETSTATUS_RECONNECT_INVALID);
                    return;
                }
                
                SetLoginState(LoginState.CONNECT_GAMESERVER_FAIL);
                CGameClient.Singleton.Disconnect();
                SetLoginResult((EErrorPlayerLoginServer)accountLogin.m_state);
                return;
            }

            SetLoginState(LoginState.CONNECT_GAMESERVER_SUCCESS);
            if (ConnectCallBackType == EConnectCallBack.CONNECT_CB_RECONNECT_GT)
            {
                SendLostMsg();
                return;
            }
            CMsgLoginSystemGM2GCAckAccountLogin.CallBack(accountLogin);
        }

        private void OnMsgLoginSystemLG2GCAckRegisterAccount(UnityFrame.CMsg msgData)
        {
            CMsgLoginSystemLG2GCAckRegisterAccount msg = (CMsgLoginSystemLG2GCAckRegisterAccount)msgData;
            m_registerResult = (ERegisterResult)msg.m_state;
            CGameClient.Singleton.Disconnect();
        }

        private void OnMsgLoginSystemLG2GCAckGetAccountToken(UnityFrame.CMsg msgData)
        {
            CMsgLoginSystemLG2GCAckGetAccountToken msg = (CMsgLoginSystemLG2GCAckGetAccountToken)msgData;
            m_getTakenResult = (EGetAccountTokenResult)msg.m_state;
            m_token = msg.m_token;
            m_accountKey.m_accountID = msg.m_accountID;
            CGameClient.Singleton.Disconnect();
        }


        private void GetAccountTokenCallBack(EGetAccountTokenResult result)
        {
            if (result != EGetAccountTokenResult.EGETACCOUNTTAKEN_TOKEN_FAIL)
            {
                CGameClient.Singleton.Disconnect();
            }

            CMsgLoginSystemLG2GCAckGetAccountToken ack = new CMsgLoginSystemLG2GCAckGetAccountToken();
            ack.m_state = (uint)result;
            ack.m_accountID = AccountID;
            ack.m_token = m_token;
            CMsgLoginSystemLG2GCAckGetAccountToken.CallBack(ack);
        }

        public bool ReConnectGateServer()
        {
            UnityUtility.CTrace.Singleton.debug("[ReConnectGateServer][ConnectServer][ip{0}:{1}]", m_gameServerIP.ToString(), m_gameServerPort.ToString());
            return ConnectServer(m_gameServerIP, m_gameServerPort, EConnectServerType.CONNECT_SERVER_GT, EConnectCallBack.CONNECT_CB_RECONNECT_GT);
        }

        // 连接LG获取Token
        public bool GetAccountTokenAsync()
        {
            UnityUtility.CTrace.Singleton.debug("[GetAccountTokenAsync][ConnectAsync][ip{0}:{1}]", m_serverIP.ToString(), m_serverPort.ToString());
            bool bConnect = ConnectServer(m_serverIP, m_serverPort, EConnectServerType.CONNECT_SERVER_LG, EConnectCallBack.CONNECT_CB_GET_TOKEN);
            if (!bConnect)
            {
                GetAccountTokenCallBack(EGetAccountTokenResult.EGETACCOUNTTAKEN_TOKEN_FAIL);
                return false;
            }
            return true;
        }

        // 连接LG获取GT
        public bool EnterServerAsync()
        {
            if (!CanLoginServer)
            {
                return false;
            }
            SetLoginState(LoginState.CONNECT_LOGINSERVER_WAIT_CONNECT);
            UnityUtility.CTrace.Singleton.debug("[EnterServerAsync][ConnectAsync][ip{0}:{1}]", m_serverIP.ToString(), m_serverPort.ToString());
            bool bConnect = ConnectServer(m_serverIP, m_serverPort, EConnectServerType.CONNECT_SERVER_LG, EConnectCallBack.CONNECT_CB_GET_GT);
            if (!bConnect)
            {
                SetLoginState(LoginState.CONNECT_LOGINSERVER_FAIL);
                return false;
            }
            return true;
        }

        // 连接GT进入游戏
        private bool EnterGTAsync()
        {
            SetLoginState(LoginState.CONNECT_GAMESERVER_WAIT_CONNECT);
            UnityUtility.CTrace.Singleton.debug("[EnterGTAsync][ConnectAsync][ip{0}:{1}]", m_gameServerIP.ToString(), m_gameServerPort.ToString());
            bool bConnect = ConnectServer(m_gameServerIP, m_gameServerPort, EConnectServerType.CONNECT_SERVER_GT, EConnectCallBack.CONNECT_CB_CONNECT_GT);
            if (!bConnect)
            {
                SetLoginState(LoginState.CONNECT_GAMESERVER_FAIL);
                CGameClient.Singleton.Disconnect();
                return false;
            }
            return true;
        }

        /// <summary>
        /// 发送注册消息
        /// </summary>
        /// <returns></returns>
        private bool SendMsgToLGRegisterAccount()
        {
            CMsgLoginSystemGC2LGReqRegisterAccount accountRegister = new CMsgLoginSystemGC2LGReqRegisterAccount();
            accountRegister.m_account = m_account;
            accountRegister.m_password = m_password;
            accountRegister.m_channelID = m_channelID;
            accountRegister.m_platform = m_platform;
            accountRegister.m_uniqueID = m_uniqueID;
            accountRegister.m_uniqueKey = m_uniqueKey;
            accountRegister.m_regeisterType = (uint)m_registerType;
            accountRegister.m_activationCode = m_activationCode;
            return CGameClient.Singleton.SendMsg(accountRegister);
        }

        /// <summary>
        /// 发送获取Token消息
        /// </summary>
        /// <returns></returns>
        private bool SendMsgToLGGetToken()
        {
            CMsgLoginSystemGC2LGReqGetAccountToken accountTaken = new CMsgLoginSystemGC2LGReqGetAccountToken();
            accountTaken.m_account = m_account;
            accountTaken.m_password = m_password;
            accountTaken.m_channelID = m_channelID;
            accountTaken.m_platform = m_platform;
            accountTaken.m_uniqueID = m_uniqueID;
            accountTaken.m_uniqueKey = m_uniqueKey;
            accountTaken.m_getTakenType = (uint)m_loginType;
            return CGameClient.Singleton.SendMsg(accountTaken);
        }

        /// <summary>
        /// 获取网关
        /// </summary>
        /// <returns></returns>
        private bool SendMsgToLGGetGateWay()
        {
            CMsgLoginSystemGC2LGReqAccountLogin accountLogin = new CMsgLoginSystemGC2LGReqAccountLogin();
            accountLogin.m_account = m_account;
            accountLogin.m_password = m_password;
            accountLogin.m_zoneID = m_accountKey.m_zoneID;
            accountLogin.m_channelID = m_channelID;
            accountLogin.m_platform = m_platform;
            accountLogin.m_uniqueID = m_uniqueID;
            accountLogin.m_uniqueKey = m_uniqueKey;
            accountLogin.m_loginType = (uint)m_loginType;
            accountLogin.m_token = m_token;
            accountLogin.m_accountID = m_accountKey.m_accountID;
            UnityUtility.CTrace.Singleton.debug("[SendMsgToLGGetGateWay][m_loginState={0}][m_account={1}][m_password={2}]",
                ((LoginState)m_loginState).ToString(),
                m_account,
                m_password);
            return CGameClient.Singleton.SendMsg(accountLogin);
        }

        /// <summary>
        /// 登录网关
        /// </summary>
        /// <returns></returns>
        private bool SendMsgToGTAccountLogin()
        {
            CMsgLoginSystemGC2GMReqAccountLogin accountLogin = new CMsgLoginSystemGC2GMReqAccountLogin();
            accountLogin.m_loginKey = m_loginKey;
            accountLogin.m_loginSession = m_loginSession;
            accountLogin.m_channelID = m_channelID;
            accountLogin.m_accountKey = m_accountKey;
            return CGameClient.Singleton.SendMsg(accountLogin);
        }

        private void SendLostMsg()
        {
            if (CGameClient.LostMsgData == null)
            {
                return ;
            }
            if (!CGameClient.Singleton.SendMsg(CGameClient.LostMsgData))
            {
                NotifyNetState(ENetStatus.ENETSTATUS_RECONNECT_FAIL);
            }
            CGameClient.LostMsgData = null;
        }

// 
//            private void SendPingMsg()
//         {
//             if (CGameClient.LostMsgData == null)
//             {
//                 return ;
//             }
//             if (!CGameClient.Singleton.SendMsg(CGameClient.LostMsgData))
//             {
//                 NotifyNetState(ENetStatus.ENETSTATUS_RECONNECT_FAIL);
//             }
//             CGameClient.LostMsgData = null;
//         }
// 
// 
// 
//         public void BeginTheTimer()
//         {
//             //这里只是要一个object类型数据，用它做为下面Timer的参数之一，没有其它意思
//             object myobject = (object)7;
//             //暂时设定为1秒钟启动一次！
//             System.Threading.Timer t = new System.Threading.Timer(new System.Threading.TimerCallback(checkGameNetConnect), myobject, 1000, 1000);
//         }
// 
//             }
//         //启动监视"已登录用户通信情况"的线程
//         public void checkGameNetConnect(object myobject)  
//         {
//             //UserPassport up=new UserPassport();
//             Thread sendMyPulseThPro = new Thread(new ThreadStart(delegateSendMyPulse));
//             sendMyPulseThPro.Start();
//         }
// 
//         /// <summary>
//         /// 每隔1秒就是要来做这些事情的
//         /// </summary>
//         public void delegateSendMyPulse()
//         {
//             static int a =1;
//             //loginServer lser = new loginServer();
//             //3是确认联接正常的一个信号（让服务知道它与服务器的联接是正常的）
//             //启动一个新线程去发送数据          
//             Thread thSendDat2 = new Thread(new ParameterizedThreadStart(SendPingMsg));
//             thSendDat2.Start(l);
//             thSendDat2.IsBackground = true;
//             //标记我已经发送出去一次数据了
//             //longinserver.MyLostTime += 1;
//             //如果外发了3次请求暗号后仍不见服务器的回应，则认为客户端已经与服务器断开联系了
//            // if(longinserver.MyLostTime>=3)
//           //  {
//                 //停止Timer
//                 //告诉用户：“你已经与服务器失去联系了…………”
//                 //longinserver.Controls["txtShowMsg"].Text = "You have lost the connect!";
//             //}
//         }
    }  
}
