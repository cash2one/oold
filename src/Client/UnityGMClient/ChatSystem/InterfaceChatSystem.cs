using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public partial class CClientCore : UnityUtility.CSingletonBase<CClientCore>
    {
        public delegate void CBChatSystemGM2GCAckInitChatData(List<CChatContent> listWorldContent, List<CChatContent> listAnnounceContent);

        /// <summary>
        /// 注册角色上线推送的信息
        /// </summary>
        /// <param name="listChatContent"></param>
        public void RegisterInitChatInfoCallBack(CBChatSystemGM2GCAckInitChatData cb)
        {
            CMsgChatSystemGM2GCAckInitChatData.s_cb = cb;
        }

        /// <summary>
        /// 注册接收到的聊天消息
        /// </summary>
        /// <param name="cb"></param>
        public void RegisterInitRoleChatToAllCallBack(CBMsgChatSystemGM2GCAckChat2All cb)
        {
            CMsgChatSystemGM2GCAckChat2All.s_cb = cb;
        }

        /// <summary>
        /// 发送聊天信息反馈
        /// </summary>
        /// <param name="result"></param>
        public delegate void CBMsgChatSystemGM2GCAckChat(EChatResult result);

        /// <summary>
        /// 收到聊天消息
        /// </summary>
        /// <param name="senderID"></param>
        /// <param name="senderName"></param>
        /// <param name="channel"></param>
        /// <param name="content"></param>
        public delegate void CBMsgChatSystemGM2GCAckChat2All(CChatContent content);

        /// <summary>
        /// 发送聊天信息
        /// </summary>
        /// <param name="channel"></param>
        /// <param name="content"></param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgChatSystemGC2GMReqChat(SRoleKey roleKey, EChatChanel channel, string content, CChatEquipID equipID, CBMsgChatSystemGM2GCAckChat cb)
        {
            CMsgChatC2GMReqChat req = new CMsgChatC2GMReqChat(roleKey, channel, content, equipID);
            CMsgChatSystemGM2GCAckChat.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }


    }
}








