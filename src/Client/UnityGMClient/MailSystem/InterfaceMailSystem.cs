using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{

    public partial class CClientCore : UnityUtility.CSingletonBase<CClientCore>
    {

        /// <summary>
        /// 推送邮件回调
        /// </summary>
        /// <param name="push_type">推送类型 1: 全体推送(上线时), 2:新邮件推送(在线时)</param>
        /// <param name="mail_box"></param>
        public delegate void CBMsgMailSystemGM2GCAckPushMail(UInt32 push_type, List<CMail> mail_box);

        /// <summary>
        /// 注册 推送邮件回调
        /// </summary>
        /// <param name="cb"></param>
        public void RegisterMailSystemGM2GCPushMail(CBMsgMailSystemGM2GCAckPushMail cb)
        {
            CMsgGM2GCAckPushMail.cb = cb;
        }


        
        public delegate void CBMsgMailSystemGM2GCAckOPMail(UInt32 op_type, List<UInt64> mail_ids);
        /// <summary>
        /// 请求操作
        /// </summary>
        /// <param name="op_type"> 1:设置已读取状态, 2:删除邮件</param>
        /// <param name="mail_ids">待操作的邮件列表(长度为0 代表一键操作)</param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgMailSystemGC2GMReqOPMail(UInt32 op_type, List<UInt64> mail_ids, CBMsgMailSystemGM2GCAckOPMail cb)
        {
            CMsgMailSystemGC2GMReqOPMail req = new CMsgMailSystemGC2GMReqOPMail(op_type, mail_ids);

            CMsgMailSystemGM2GCAckOPMail.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }


        /// <summary>
        /// 获取附件
        /// </summary>
        /// <param name="mail_ids">要获取附件的邮件id列表(列表长度为零代表一键获取)</param>
        /// <param name="bonus_ids">返回的奖励id列表</param>
        /// <param name="bonus_nums">返回的奖励数量列表</param>
        public delegate void CBMsgMailSystemGM2GCAckGetAttach(List<UInt64> mail_ids, List<UInt32> bonus_ids, List<UInt32> bonus_nums);
        public bool SendMsgMailSystemGC2GMReqGetAttach(List<UInt64> mail_ids, CBMsgMailSystemGM2GCAckGetAttach cb)
        {
            CMsgMailSystemGC2GMReqGetAttach req = new CMsgMailSystemGC2GMReqGetAttach(mail_ids);

            CMsgMailSystemGM2GCAckGetAttach.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

    }
}
