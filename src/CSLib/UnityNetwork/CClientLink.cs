using System;
using System.Collections.Generic;
using System.Text;

namespace UnityNetwork
{
    public delegate void CallbackNetState();
    public delegate void CallbackRecvAsync(UnityUtility.CBuffer buffer);
    
    public class CClientLink
    {
        public CallbackNetState ConnectSuccess
        {
            set
            {
                m_connectSuccess = value;
            }
        }
        public CallbackNetState ConnectFail
        {
            set
            {
                m_connectFail = value;
            }
        }

        public CallbackNetState NetLinkClose
        {
            set
            {
                m_netLinkClose = value;
            }
        }

        public CallbackRecvAsync RecvAsync
        {
            set
            {
                m_recvAsync = value;
            }
        }

        public bool IsConnected
        {
            get
            {
                if (m_netTcpClient == null)
                {
                    return false;
                }
                return m_netTcpClient.IsConnected;
            }
        }

        public bool ConnectAsync(string address, int remotePort)
        {
            if (m_netTcpClient == null)
            {
                m_netTcpClient = new CNetTcpClient();
            }
            if (m_netTcpClient.IsConnected)
            {
               return true;
            }
            m_isClose = false;
            if (!m_netTcpClient.ConnectAsync(address, remotePort))
            {
                m_isClose = true;
                return false;
            }
            return true;
        }

        public bool SendAsync(UnityUtility.CStream stream)
        {
            if (m_netTcpClient == null)
            {
                return false;
            }
            if (!m_netTcpClient.IsConnected)
            {
                return false;
            }
            return m_netTcpClient.SendAsync(stream.Buffer);
        }

        public void Disconnect()
        {
            if (m_netTcpClient == null)
            {
                return;
            }
            if (!m_netTcpClient.IsConnected)
            {
                return;
            }
            m_netTcpClient.Disconnect(0);
        }

        public void UpdateRecvAsync()
        {
            if (m_netTcpClient == null)
            {
                return;
            }

            CNetPacket netPacket = null;
            while (m_netTcpClient.RecvAsync(out netPacket))
            {
                switch (netPacket.m_packetType)
                {
                    case CNetPacket.EType.CONNECTION_REQUEST_SUCCESS:
                        if (m_connectSuccess != null)
                        {
                            UnityUtility.CTrace.Singleton.debug("连接成功[{0}]", netPacket.m_packetType);
                            m_connectSuccess();
                        }
                        break;
                    case CNetPacket.EType.CONNECTION_REQUEST_FAILED:
                        if (m_connectFail != null && !m_isClose)
                        {
                            m_isClose = true;
                            UnityUtility.CTrace.Singleton.debug("连接失败[{0}]", netPacket.m_packetType);
                            m_connectFail();
                        }
                        break;
                    case CNetPacket.EType.CONNECTION_LOST:
                    case CNetPacket.EType.CONNECTION_CLOSE:
                    case CNetPacket.EType.CONNECTION_CLOSE_ENCRYPT:
                    case CNetPacket.EType.CONNECTION_CLOSE_COMPRESS:
                        if (m_netLinkClose != null && !m_isClose)
                        {
                            m_isClose = true;
                            UnityUtility.CTrace.Singleton.debug("连接关闭[{0}]", netPacket.m_packetType);
                            m_netLinkClose();
                        }
                        break;
                    case CNetPacket.EType.CONNECTION_RECV_PACKET:
                        if (m_recvAsync != null)
                        {
                            m_recvAsync(netPacket.m_buffer);
                        }
                        break;
                    case CNetPacket.EType.NULL:
                    default:
                        {
                            ;
                        }
                        break;
                }
            }
        }
        private bool m_isClose = true;
        private CNetTcpClient m_netTcpClient = null;
        private CallbackNetState m_connectSuccess = null;
        private CallbackNetState m_connectFail = null;
        private CallbackNetState m_netLinkClose = null;
        private CallbackRecvAsync m_recvAsync = null;
    }
}
