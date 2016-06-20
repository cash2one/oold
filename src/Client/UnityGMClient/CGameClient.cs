using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public enum EModuleType
    {
        EMODULECTYPE_NULL = 0,
        EMODULECTYPE_BAG,
        EMODULECTYPE_EQUIP,
        EMODULECTYPE_ITEM,
        EMODULECTYPE_SCENE,
        EMODULECTYPE_SKILL,
        EMODULECTYPE_PRIZE,
        EMODULECTYPE_TASK,
        EMODULECTYPE_CHAT,
        EMODULECTYPE_MAIL,
        EMODULECTYPE_PET,
        EMODULECTYPE_RANK,
        EMODULETYPE_SHOP,
        EMODULETYPE_FRIEND,
        EMODULECTYPE_MAX,
    };

    class CGameClient : UnityUtility.CSingleton<CGameClient>
    {
        public CGameClient()
        {
            m_msgExecMgr.MsgFactory = m_msgFactory;
        }

        public void Init()
        {
            m_netSystem.Init();
            m_loginSystem.Init();
            m_playerSystem.Init();
            m_equipSystem.Init();
            m_petSystem.Init();
            m_skillSystem.Init();
            m_chatSystem.Init();
            m_mailSystem.init();
            m_sceneSystem.Init();
            m_rankSystem.Init();
            m_taskSystem.Init();
            m_shopSystem.Init();
            m_friendSystem.Init();
            m_activitySystem.Init();
            m_achieveSystem.Init();
            m_prizeSystem.Init();
        }
        
        public void Update(float delayTimer)
        {
            if (Net != null)
            {
                Net.Update(delayTimer);
            }
        }

        public void Final()
        {
            if (Net != null)
            {
                Net.Disconnect();
                Net = null;
            }

            if (m_loginSystem != null)
            {
                m_loginSystem.Final();
                m_loginSystem = null;
            }
        }

        public bool SendMsg(UnityFrame.CMsg msgData)
        {
            if (Net != null)
            {
                if (!Net.SendAsync(msgData))
                {
                    CGameClient.LostMsgData = msgData;
                    if (LoginSystem.ConnectServerType == UnityGMClient.CLoginSystem.EConnectServerType.CONNECT_SERVER_GT)
                    {
                        return CGameClient.Singleton.SendMsgReConnectServer();
                    }
                    return false;
                }
                return true;
            }
            return false;
        }

        public bool SendMsgReConnectServer()
        {
            return m_loginSystem.ReConnectGateServer();
        }

        public bool SendMsgReLogin()
        {
            return m_loginSystem.EnterServerAsync();
        }

        public CMsgFactory MsgFactory
        {
            get { return m_msgFactory; }
        }

        public UnityFrame.CMsgExecMgr MsgExecMgr
        {
            get { return m_msgExecMgr; }
        }

        private CClientLink Net
        {
            get { return m_clientLink; }
            set { m_clientLink = value; }
        }

        public CLoginSystem LoginSystem
        {
            get { return m_loginSystem; }
        }

        public CPlayerSystem PlayerSystem
        {
            get { return m_playerSystem; }
        }

        public CEquipSystem EquipSystem
        {
            get { return m_equipSystem; }
        }

        public CPetSystem PetSystem
        {
            get { return m_petSystem; }
        }

        public CMailSystem MailSystem
        {
            get { return m_mailSystem; }
        }

        public CSceneSystem SceneSystem
        {
            get { return m_sceneSystem; }
        }

        public CRankSystem RankSystem
        {
            get { return m_rankSystem; }
        }

        public CTaskSystem TaskSystem
        {
            get { return m_taskSystem; }
        }

        public CAchieveSystem AchieveSystem
        {
            get { return m_achieveSystem; }
        }

        public static CClientCore.CBNetStatusUpdate NetStatusCallBack
        {
            get { return m_callBack; }
            set { m_callBack = value; }
        }

        public void ResetLoginSystem()
        {
            if (m_loginSystem == null)
            {
                m_loginSystem = new CLoginSystem();
                m_loginSystem.Init();
            }
        }

        public void ResetClientLink()
        {
            if (Net == null)
            {
                Net = new CClientLink();
            }
        }

        public static UnityFrame.CMsg LostMsgData 
        {
            get { return m_lostMsgData; }
            set { m_lostMsgData = value; }
        }

        public bool IsConnected
        {
            get {
                if (Net == null)
                {
                    return false;
                }
                return Net.IsConnected;
            }
        }


        public void Disconnect()
        {
            if (Net == null)
            {
                return;
            }
            Net.Disconnect();
        }

        public bool ConnectAsync(string address, int remotePort)
        {
            if (Net == null)
            {
                return false;
            }
            return Net.ConnectAsync(address, remotePort);
        }

        public void RegisterEventCallBack(UnityNetwork.CallbackNetState a_cbSuccess, UnityNetwork.CallbackNetState a_cbFail, UnityNetwork.CallbackNetState a_cbClose)
        {
            if (Net == null)
            {
                return;
            }
            Net.RegisterEventCallBack(a_cbSuccess, a_cbFail, a_cbClose); 
        }

        public void UnRegisterEventCallBack(UnityNetwork.CallbackNetState a_cbSuccess, UnityNetwork.CallbackNetState a_cbFail, UnityNetwork.CallbackNetState a_cbClose)
        {
            if (Net == null)
            {
                return;
            }
            Net.UnRegisterEventCallBack(a_cbSuccess, a_cbFail, a_cbClose); 
        }

        private CMsgFactory m_msgFactory = new CMsgFactory();
        private UnityFrame.CMsgExecMgr m_msgExecMgr = new UnityFrame.CMsgExecMgr();
        private CClientLink m_clientLink = new CClientLink();

        private CLoginSystem m_loginSystem = new CLoginSystem();
        private CPlayerSystem m_playerSystem = new CPlayerSystem();
        private CEquipSystem m_equipSystem = new CEquipSystem();
        private CPetSystem m_petSystem = new CPetSystem();
        private CSkillSystem m_skillSystem = new CSkillSystem();
        private CChatSystem m_chatSystem = new CChatSystem();
        private CMailSystem m_mailSystem = new CMailSystem();
        private CSceneSystem m_sceneSystem = new CSceneSystem();
        private CRankSystem m_rankSystem = new CRankSystem();
        private CTaskSystem m_taskSystem = new CTaskSystem();
        private CShopSystem m_shopSystem = new CShopSystem();
        private CFriendSystem m_friendSystem = new CFriendSystem();
        private CActivitySystem m_activitySystem = new CActivitySystem();
        private CAchieveSystem m_achieveSystem = new CAchieveSystem();
        private CNetSystem m_netSystem = new CNetSystem();
        private CPrizeSystem m_prizeSystem = new CPrizeSystem();

        private static CClientCore.CBNetStatusUpdate m_callBack = null;
        private static UnityFrame.CMsg m_lostMsgData = null;
    }

}