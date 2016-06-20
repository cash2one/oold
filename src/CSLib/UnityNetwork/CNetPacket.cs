using System;
using System.Net.Sockets;

namespace UnityNetwork
{
    class CNetPacket
    {
        public enum EType
        {
            NULL = 0,

            // 客户端连接请求成功
            CONNECTION_REQUEST_SUCCESS,

            // 客户端连接请求失败
            CONNECTION_REQUEST_FAILED,

            // 客户端连接断开
            CONNECTION_LOST,

            // 客户端数据包异常，主动断开
            CONNECTION_CLOSE,

            // 客户端数据包解密或加密异常，主动断开
            CONNECTION_CLOSE_ENCRYPT,

            // 客户端数据包解压或压缩异常，主动断开
            CONNECTION_CLOSE_COMPRESS,

            // 客户端连接收到数据包
            CONNECTION_RECV_PACKET,
        }

        public EType m_packetType = EType.NULL;
        public Socket m_peer = null;
        public string m_error = "";
        public UnityUtility.CBuffer m_buffer = null;
    }
}

