using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GC
{
    public class CCmd
    {
        public const string TP_PLAYER = "玩家列表";
        public const string TP_ROLE = "角色信息";
        public const string TP_BAG = "背包数据";
        public const string TP_EQUIP = "装备信息";
        public const string TP_PET = "伙伴信息";

        public const string CMD_TRANSLATE_TIME = "转换时间";
        public const string CMD_CMD_MSG = "GM命令";
        public const string CMD_ERROR = "无效命令";
        public const string CMD_OK = "操作成功";
        
    }

    public class CCmdMgr : UnityUtility.CSingleton<CCmdMgr>
    {
        public string sendCmd(string a_cmd,string data,string p1,string p2)
        {
            string cmd = a_cmd;
            switch (cmd)
            {
                case GC.CCmd.TP_PLAYER: { return GC.CPlayer.Singleton.getPlayerDataToLogString(); }
                case GC.CCmd.TP_BAG:    { return GC.CPlayer.Singleton.getBagDataToLogString(); }
                case GC.CCmd.TP_ROLE:   { return GC.CPlayer.Singleton.getRoleDataToLogString(); }
                case GC.CCmd.TP_EQUIP:  { return GC.CPlayer.Singleton.getEquipDataToLogString(); }
                case GC.CCmd.TP_PET:    { return GC.CPlayer.Singleton.getPetDataToLogString(); }
                case GC.CCmd.CMD_TRANSLATE_TIME:
                    {
                        try
                        {
                            long seconds = long.Parse(data);
                            return CHelper.getStringTime(seconds);
                        }
                        catch (Exception exp)
                        {
                            return exp.ToString();
                        }
                    }
                case GC.CCmd.CMD_CMD_MSG:
                    {
                        UnityGMClient.CChatEquipID equipID = new UnityGMClient.CChatEquipID(UInt32.MaxValue, 0);
                        bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgChatSystemGC2GMReqChat(GC.CPlayer.Singleton.getCurRole().RoleKey, UnityGMClient.EChatChanel.CHAT_CHANNEL_PRIVATE, data, equipID, delegate(UnityGMClient.EChatResult result)
                        {
                            string lg = "result:" + result;
                            SimulateClient.FormRoleData.showLog(lg);
                        });

                        if (!bResult)
                        {
                            return "发送upgrade失败！ ";
                        }
                        return CCmd.CMD_OK;
                    }
                default:
                    {
                        return GC.CCmd.CMD_ERROR; 
                    }
            }
        }
    }
}
