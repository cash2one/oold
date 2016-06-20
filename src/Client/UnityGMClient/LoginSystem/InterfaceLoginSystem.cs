using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    /// <summary>
    /// 登陆返回码
    /// </summary>
    public enum EErrorPlayerLoginServer
    {
        ELOGINRESULT_SUCCESS = 0,               //登录成功
        ELOGINRESULT_SUCCESS_FIRST = 1,         //登录成功，首次登陆
        ELOGINRESULT_ACCOUNT_NOTEXIST = 2,      //账号不存在
        ELOGINRESULT_PASSWORD_ERROR = 3,        //密码错误
        ELOGINRESULT_ZONEID_NOTEXIST = 4,       //游戏区不存在
        ELOGINRESULT_ZONEID_STOP = 5,           //游戏区停服
        ELOGINRESULT_CONNECT_ERROR = 6,         //链接服务器失败
        ELOGINRESULT_VERSION_DIFFERENCE = 7,    //客户端与服务器版本不一致
        ELOGINRESULT_SERVER_ERROR = 8,          //服务器异常
        ELOGINRESULT_ACCOUNT_LOGIN = 9, 		//账号正在登陆
        ELOGINRESULT_ACCOUNT_ONLINE = 10,	    //账号已经在游戏区
        ELOGINRESULT_LOGIN_TIMEOUT = 11,		//登陆超时
        ELOGINRESULT_LOGIN_CHECK_ERROR = 12,	//登陆参数验证不合法
        ELOGINRESULT_ACCOUNT_EXIT = 13, 		//账号正在退出
    }

    public enum ELoginType
    {
        ELOGINTYPE_FAST_LOGIN,
        ELOGINTYPE_NORMAL_LOGIN,
        ELOGINTYPE_TOKEN_LOGIN,
    }

    public enum ERegisterType
    {
        EREGEITERTYPE_FAST_REGISTER,                 //快速注册
        EREGEITERTYPE_NORMAL_REGISTER,               //普通注册（绑定）
    }

    public enum ERegisterResult
    {
        EREGISTERRESULT_SUCCESS = 0,               //注册成功
        EREGISTERRESULT_ACCOUNT_EXIST = 1,         //账号或设备ID已经存在
        EREGISTERRESULT_ACCOUNT_INVALID = 2,       //账号或设备ID无效
        EREGISTERRESULT_ACTIVATION_CODE_INVALID = 3, // 激活码无效
        EREGISTERRESULT_FAIL = 10,                 //账号或设备ID无效
    }

    public enum EGetAccountTokenResult
    {
        EGETACCOUNTTAKEN_SUCCESS = 0,               //登录成功
        EGETACCOUNTTAKEN_SUCCESS_FIRST = 1,         //登录成功，首次登陆
        EGETACCOUNTTAKEN_ACCOUNT_NOTEXIST = 2,      //账号不存在
        EGETACCOUNTTAKEN_PASSWORD_ERROR = 3,        //密码错误
        EGETACCOUNTTAKEN_CONNECT_ERROR = 6,         //链接服务器失败
        EGETACCOUNTTAKEN_VERSION_DIFFERENCE = 7,    //客户端与服务器版本不一致
        EGETACCOUNTTAKEN_SERVER_ERROR = 8,          //服务器异常
        EGETACCOUNTTAKEN_ACCOUNT_LOGIN = 9, 		//账号正在登陆
        EGETACCOUNTTAKEN_ACCOUNT_ONLINE = 10,	    //账号已经在游戏区
        EGETACCOUNTTAKEN_LOGIN_TIMEOUT = 11,		//登陆超时
        EGETACCOUNTTAKEN_LOGIN_CHECK_ERROR = 12,	//登陆参数验证不合法
        EGETACCOUNTTAKEN_ACCOUNT_EXIT = 13, 		//账号正在退出
        EGETACCOUNTTAKEN_TOKEN_FAIL = 14,			//获取Taken失败
    };

    public enum ETakenLoginResult
    {
        ETAKENLOGIN_SUCCESS = 0,               //Taken登录成功
        ETAKENLOGIN_FAIL = 1,                  //Taken登录失败
        ETAKENLOGIN_ACCOUNT_NOTEXIST = 2,      //账号不存在
        ETAKENLOGIN_PASSWORD_ERROR = 3,        //密码错误
        ETAKENLOGIN_CONNECT_ERROR = 6,         //链接服务器失败
        ETAKENLOGIN_VERSION_DIFFERENCE = 7,    //客户端与服务器版本不一致
        ETAKENLOGIN_SERVER_ERROR = 8,          //服务器异常
        ETAKENLOGIN_ACCOUNT_LOGIN = 9, 		   //账号正在登陆
        ETAKENLOGIN_ACCOUNT_ONLINE = 10,	   //账号已经在游戏区
        ETAKENLOGIN_LOGIN_TIMEOUT = 11,		   //登陆超时
        ETAKENLOGIN_LOGIN_CHECK_ERROR = 12,	   //登陆参数验证不合法
        ETAKENLOGIN_ACCOUNT_EXIT = 13, 		   //账号正在退出
        ETAKENLOGIN_TOKEN_FAIL = 14,		   //获取Taken失败
    }

    public enum ENetStatus
    {
        ENETSTATUS_NULL = 0,
        ENETSTATUS_OFFLINE = 1,
        ENETSTATUS_RECONNECT_FAIL = 2,
        ENETSTATUS_RECONNECT_INVALID = 3,
    }

    public partial class CClientCore : UnityUtility.CSingletonBase<CClientCore>
    {
        /// <summary>
        /// 登录回调
        /// </summary>
        /// <param name="a_state">登录结果</param>
        public delegate void CBMsgLoginSystemGM2GCAckAccountLogin(EErrorPlayerLoginServer a_state);

        /// <summary>
        /// 选服登录
        /// </summary>
        /// <param name="serverIP"></param>
        /// <param name="serverPort"></param>
        /// <param name="zoneID"></param>
        /// <param name="accountID"></param>
        /// <param name="token"></param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgLoginSystemGC2LGReqSelectServer(string serverIP, ushort serverPort, ushort zoneID, UInt64 accountID, string token, CBMsgLoginSystemGM2GCAckAccountLogin cb)
        {
            CGameClient.Singleton.ResetClientLink();
            CGameClient.Singleton.ResetLoginSystem();
            
            CMsgLoginSystemGM2GCAckAccountLogin.cb = cb;
            CGameClient.Singleton.LoginSystem.ServerIP = serverIP;
            CGameClient.Singleton.LoginSystem.ServerPort = serverPort;
            CGameClient.Singleton.LoginSystem.Account = "";
            CGameClient.Singleton.LoginSystem.ZoneID = zoneID;
            CGameClient.Singleton.LoginSystem.Platform = "";
            CGameClient.Singleton.LoginSystem.ChannelID = 0;
            CGameClient.Singleton.LoginSystem.UniqueID = "";
            CGameClient.Singleton.LoginSystem.UniqueKey = "";
            CGameClient.Singleton.LoginSystem.AccountID = accountID;
            CGameClient.Singleton.LoginSystem.Token = token;
            CGameClient.Singleton.LoginSystem.LoginType = ELoginType.ELOGINTYPE_TOKEN_LOGIN;
            return CGameClient.Singleton.LoginSystem.EnterServerAsync();
        }

        public bool SendMsgLoginSystemGC2LGReqSelectServer(string serverIP, ushort serverPort, ushort zoneID, string account, string token, CBMsgLoginSystemGM2GCAckAccountLogin cb)
        {
            CGameClient.Singleton.ResetClientLink();
            CGameClient.Singleton.ResetLoginSystem();

            CMsgLoginSystemGM2GCAckAccountLogin.cb = cb;
            CGameClient.Singleton.LoginSystem.ServerIP = serverIP;
            CGameClient.Singleton.LoginSystem.ServerPort = serverPort;
            CGameClient.Singleton.LoginSystem.Account = account;
            CGameClient.Singleton.LoginSystem.ZoneID = zoneID;
            CGameClient.Singleton.LoginSystem.Platform = "";
            CGameClient.Singleton.LoginSystem.ChannelID = 0;
            CGameClient.Singleton.LoginSystem.UniqueID = "";
            CGameClient.Singleton.LoginSystem.UniqueKey = "";
            CGameClient.Singleton.LoginSystem.AccountID = 0;
            CGameClient.Singleton.LoginSystem.Token = token;
            CGameClient.Singleton.LoginSystem.LoginType = ELoginType.ELOGINTYPE_TOKEN_LOGIN;
            return CGameClient.Singleton.LoginSystem.EnterServerAsync();
        }

        public bool SendMsgReConnectServer()
        {
            return UnityGMClient.CGameClient.Singleton.SendMsgReConnectServer();
        }

        public bool SendMsgDisconnectGame()
        {
            return CGameClient.Singleton.LoginSystem.DiscounnectGame();
        }

        /// <summary>
        /// 注册回调
        /// </summary>
        /// <param name="a_state">注册结果</param>
        public delegate void CBMsgLoginSystemLG2GCAckRegisterAccount(ERegisterResult a_state);
        public bool SendMsgLoginSystemGC2LGReqFastRegister(string serverIP, ushort serverPort, string account, string password,  string platform, uint channelID, CBMsgLoginSystemLG2GCAckRegisterAccount cb)
        {
            CGameClient.Singleton.ResetClientLink();
            CGameClient.Singleton.ResetLoginSystem();
            
            CMsgLoginSystemLG2GCAckRegisterAccount.cb = cb;
            CGameClient.Singleton.LoginSystem.ServerIP = serverIP;
            CGameClient.Singleton.LoginSystem.ServerPort = serverPort;
            CGameClient.Singleton.LoginSystem.Account = account;
            CGameClient.Singleton.LoginSystem.Password = password;
            
            CGameClient.Singleton.LoginSystem.Platform = platform;
            CGameClient.Singleton.LoginSystem.ChannelID = channelID;
            CGameClient.Singleton.LoginSystem.UniqueID = "";
            CGameClient.Singleton.LoginSystem.UniqueKey = "";
            CGameClient.Singleton.LoginSystem.Token = "";
            CGameClient.Singleton.LoginSystem.RegisterType = ERegisterType.EREGEITERTYPE_FAST_REGISTER;
            return CGameClient.Singleton.LoginSystem.RegisterAccountAsync();
        }
        /// <summary>
        /// 普通注册
        /// </summary>
        /// <param name="serverIP">服务器ip</param>
        /// <param name="serverPort">服务器端口</param>
        /// <param name="account">账号名</param>
        /// <param name="password">密码</param>
        /// <param name="platform">平台(windows, android , ios等)</param>
        /// <param name="channelID">渠道</param>
        /// <param name="activationCode">激活码</param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgLoginSystemGC2LGReqNormalRegister(string serverIP, ushort serverPort, string account, string password, string platform,
            uint channelID, string activationCode, CBMsgLoginSystemLG2GCAckRegisterAccount cb)
        {
            CGameClient.Singleton.ResetClientLink();
            CGameClient.Singleton.ResetLoginSystem();
            
            CMsgLoginSystemLG2GCAckRegisterAccount.cb = cb;
            CGameClient.Singleton.LoginSystem.ServerIP = serverIP;
            CGameClient.Singleton.LoginSystem.ServerPort = serverPort;
            CGameClient.Singleton.LoginSystem.Account = account;
            CGameClient.Singleton.LoginSystem.Password = password;

            CGameClient.Singleton.LoginSystem.Platform = platform;
            CGameClient.Singleton.LoginSystem.ChannelID = channelID;
            CGameClient.Singleton.LoginSystem.UniqueID = "";
            CGameClient.Singleton.LoginSystem.UniqueKey = "";
            CGameClient.Singleton.LoginSystem.ActivationKey = activationCode;

            CGameClient.Singleton.LoginSystem.RegisterType = ERegisterType.EREGEITERTYPE_NORMAL_REGISTER;
            return CGameClient.Singleton.LoginSystem.RegisterAccountAsync();
        }

            
        /// <summary>
        /// 获取token回调
        /// </summary>
        /// <param name="a_state">获取token</param>
        public delegate void CBMsgLoginSystemLG2GCAckGetAccountToken(EGetAccountTokenResult a_state, UInt64 a_accountID, string a_taken);
        public bool SendMsgLoginSystemGC2LGReqNormalLogin(string serverIP, ushort serverPort, string account, string password, string platform, uint channelID, CBMsgLoginSystemLG2GCAckGetAccountToken cb)
        {
            CGameClient.Singleton.ResetClientLink();
            CGameClient.Singleton.ResetLoginSystem();
            
            CMsgLoginSystemLG2GCAckGetAccountToken.cb = cb;
            CGameClient.Singleton.LoginSystem.ServerIP = serverIP;
            CGameClient.Singleton.LoginSystem.ServerPort = serverPort;
            CGameClient.Singleton.LoginSystem.Account = account;
            CGameClient.Singleton.LoginSystem.Password = password;
            
            CGameClient.Singleton.LoginSystem.Platform = platform;
            CGameClient.Singleton.LoginSystem.ChannelID = channelID;
            CGameClient.Singleton.LoginSystem.UniqueID = "";
            CGameClient.Singleton.LoginSystem.UniqueKey = "";
            CGameClient.Singleton.LoginSystem.LoginType = ELoginType.ELOGINTYPE_NORMAL_LOGIN;

            return CGameClient.Singleton.LoginSystem.GetAccountTokenAsync();
        }

        /// <summary>
        /// 快速登陆请求
        /// </summary>
        /// <param name="serverIP"></param>
        /// <param name="serverPort"></param>
        /// <param name="account"></param>
        /// <param name="password"></param>
        /// <param name="zoneID">区号</param>
        /// <param name="cb">回调函数</param>
        /// <returns></returns>
        public bool SendMsgLoginSystemGC2LGReqFastLogin(string serverIP, ushort serverPort, string uniqueID, string uniqueKey, string platform, uint channelID, CBMsgLoginSystemLG2GCAckGetAccountToken cb)
        {
            CGameClient.Singleton.ResetClientLink();
            CGameClient.Singleton.ResetLoginSystem();
            
            CMsgLoginSystemLG2GCAckGetAccountToken.cb = cb;
            CGameClient.Singleton.LoginSystem.ServerIP = serverIP;
            CGameClient.Singleton.LoginSystem.ServerPort = serverPort;
            CGameClient.Singleton.LoginSystem.Account = "";
            CGameClient.Singleton.LoginSystem.Password = "";
            CGameClient.Singleton.LoginSystem.Platform = platform;
            CGameClient.Singleton.LoginSystem.ChannelID = channelID;
            CGameClient.Singleton.LoginSystem.UniqueID = uniqueID;
            CGameClient.Singleton.LoginSystem.UniqueKey = uniqueKey;
            CGameClient.Singleton.LoginSystem.Token = "";
            CGameClient.Singleton.LoginSystem.LoginType = ELoginType.ELOGINTYPE_FAST_LOGIN;
            return CGameClient.Singleton.LoginSystem.GetAccountTokenAsync();
        }

        /// <summary>
        /// 断线回调
        /// </summary>
        /// <param name="netStatus"></param>
        public delegate void CBNetStatusUpdate(ENetStatus netStatus);
        /// <summary>
        /// 注册断线回调
        /// </summary>
        /// <param name="cb"></param>
        public void RegisterNetStatusUpdate(CBNetStatusUpdate cb)
        {
            UnityGMClient.CGameClient.NetStatusCallBack = cb;
        }

        public void SendMsgReLogin()
        {
            UnityGMClient.CGameClient.Singleton.SendMsgReLogin();
        }

        public SAccountKey getAccountKey()
        {
            return CGameClient.Singleton.LoginSystem.AccountKey;
        }
    }
}
