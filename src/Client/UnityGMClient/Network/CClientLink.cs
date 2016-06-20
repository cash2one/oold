using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;
using System.Reflection;

namespace UnityGMClient
{
    public class CClientLink
    {
        public CClientLink()
        {
            m_netTcpClient.ConnectSuccess = CallbackConnectSuccess;
            m_netTcpClient.ConnectFail = CallbackConnectFail;
            m_netTcpClient.NetLinkClose = CallbackNetLinkClose;
            m_netTcpClient.RecvAsync = CallbackRecvAsync;
        }

        public bool ConnectAsync(string address, int remotePort)
        {
            return m_netTcpClient.ConnectAsync(address, remotePort);
        }

        public bool IsConnected
        {
            get { return m_netTcpClient.IsConnected; }
        }

        public bool SendAsync(UnityFrame.CMsg msgData)
        {
            UnityUtility.CTrace.Singleton.debug("发送消息[{0}.{1}.{2}][{3}]", msgData.MsgID.ServerType.ServerType, msgData.MsgID.FuncType.FuncType, msgData.MsgID.MsgNumber, msgData.ToString());

            UnityUtility.CStream stream = new UnityUtility.CStream();
            stream.Write(msgData.MsgID.MsgID);
            if (!msgData.SerializeTo(stream))
            {
                return false;
            }
            if (!m_netTcpClient.SendAsync(stream))
            {
                //  UnityUtility.CTrace.Singleton.error("发送消息[{0}.{1}.{2}][{3}]", msgData.MsgID.ServerType.ServerType, msgData.MsgID.FuncType.FuncType, msgData.MsgID.MsgNumber, msgData.ToString());
                // return false;
                UnityUtility.CTrace.Singleton.error("发送消息[{0}.{1}.{2}][{3}]Fail", msgData.MsgID.ServerType.ServerType, msgData.MsgID.FuncType.FuncType, msgData.MsgID.MsgNumber, msgData.ToString());
                //CGameClient.LostMsgData = msgData;
                //CGameClient.Singleton.SendMsgReConnectServer();
                return false;
            }
            return true;
        }

        public bool IsCallbackReady()
        {
            if (ConnectRequestSuccess == null)
            {
                return false;
            }

            if (ConnectRequestFail == null)
            {
                return false;
            }

            if (NetLinkClose == null)
            {
                return false;
            }
            return true; 
        }

        public void Disconnect()
        {
            m_netTcpClient.Disconnect();
        }

        public void Update(float delayTimer)
        {
            if (m_netTcpClient == null)
            {
                return;
            }
            m_netTcpClient.UpdateRecvAsync();
        }
       
        private void CallbackConnectSuccess()
        {
            if (ConnectRequestSuccess == null)
            {
                return;
            }
            ConnectRequestSuccess();
        }

        private void CallbackConnectFail()
        {
            if (ConnectRequestFail == null)
            {
                return;
            }
            ConnectRequestFail();
        }

        private void CallbackNetLinkClose()
        {
            if (NetLinkClose == null)
            {
                return;
            }
            NetLinkClose();
        }

        private void CallbackRecvAsync(UnityUtility.CBuffer buffer)
        {
            m_stream.Buffer = buffer;
            uint id = 0;
            if (!m_stream.Read(ref id))
            {
                UnityUtility.CTrace.Singleton.debug("解析消息ID错误");
                m_netTcpClient.Disconnect();
                return;
            }
            UnityFrame.CMsgID msgID = new UnityFrame.CMsgID(id);
            UnityFrame.CMsg msgData = CGameClient.Singleton.MsgFactory.CreateMessageByMsgID(msgID);
            if (msgData != null)
            {
                UnityUtility.CTrace.Singleton.debug("解析消息[{0}.{1}.{2}][{3}]", msgID.ServerType.ServerType, msgID.FuncType.FuncType, msgID.MsgNumber, msgData.ToString());

                if (!msgData.SerializeFrom(m_stream))
                {
                    m_netTcpClient.Disconnect();
                    return;
                }
                if (m_stream.Buffer.CanRead)
                {
                    UnityUtility.CTrace.Singleton.error("解析消息ParseMessage[{0}.{1}.{2}]失败,消息还有多余数据", msgID.ServerType.ServerType, msgID.FuncType.FuncType, msgID.MsgNumber);
                    m_netTcpClient.Disconnect();
                    return;
                }
                if (!CGameClient.Singleton.MsgExecMgr.ParseMessage(msgData))
                {
                    UnityUtility.CTrace.Singleton.error("解析消息ParseMessage[{0}.{1}.{2}][{3}]失败", msgID.ServerType.ServerType, msgID.FuncType.FuncType, msgID.MsgNumber, msgData.ToString());
                    m_netTcpClient.Disconnect();
                    return;
                }
            }
            else
            {
                UnityUtility.CTrace.Singleton.error("解析消息ParseMessage[{0}.{1}.{2}]创建消息失败", msgID.ServerType.ServerType, msgID.FuncType.FuncType, msgID.MsgNumber);
                m_netTcpClient.Disconnect();
                return;
            }
        }

        public void RegisterEventCallBack(UnityNetwork.CallbackNetState a_cbSuccess, UnityNetwork.CallbackNetState a_cbFail, UnityNetwork.CallbackNetState a_cbClose)
        {
            UnityUtility.CTrace.Singleton.debug("RegisterEventCallBack");
            if (IsCallbackReady())
            {
                UnRegisterEventCallBack(a_cbSuccess, a_cbFail, a_cbClose);
            }

            ConnectRequestSuccess += a_cbSuccess;
            ConnectRequestFail += a_cbFail;
            NetLinkClose += a_cbClose;
        }

        public void UnRegisterEventCallBack(UnityNetwork.CallbackNetState a_cbSuccess, UnityNetwork.CallbackNetState a_cbFail, UnityNetwork.CallbackNetState a_cbClose)
        {
            UnityUtility.CTrace.Singleton.debug("UnRegisterEventCallBack");
            if (CGameClient.Singleton == null)
            {
                return;
            }
            ConnectRequestSuccess -= a_cbSuccess;
            ConnectRequestFail -= a_cbFail;
            NetLinkClose -= a_cbClose;
        }

        private event UnityNetwork.CallbackNetState ConnectRequestSuccess;
        private event UnityNetwork.CallbackNetState ConnectRequestFail;
        private event UnityNetwork.CallbackNetState NetLinkClose;

        private UnityUtility.CStream m_stream = new UnityUtility.CStream();
        private UnityNetwork.CClientLink m_netTcpClient = new UnityNetwork.CClientLink();
    }
}
