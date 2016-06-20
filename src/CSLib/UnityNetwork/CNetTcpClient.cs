using System;
using System.Net;
using System.Net.Sockets;

namespace UnityNetwork
{
    class CNetTcpClient
    {
        // 连接服务器
        public bool ConnectAsync(string ipAddress, int remotePort)
        {
            if (m_socket != null && m_socket.Connected)
            {
                return false;
            }
            try
            {
                UnityUtility.CTrace.Singleton.debug("连接服务器[{0}:{1}]...", ipAddress, remotePort);

                //接受Buffer重置
                m_recvBuffer.Reset();

                IPAddress ip = IPAddress.Parse(ipAddress);
                //获得远程服务器的地址
                IPEndPoint ipend = new IPEndPoint(ip, remotePort);

                // 创建socket
                m_socket = new Socket(ipend.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

                // 开始连接
                m_socket.BeginConnect(ipend, new System.AsyncCallback(_ConnectionCallback), m_socket);
            }
            catch (System.Exception)
            {
                UnityUtility.CTrace.Singleton.error("连接服务器[{0}:{1}]失败", ipAddress, remotePort);
                // 连接失败
                return false;
            }
            UnityUtility.CTrace.Singleton.debug("连接服务器[{0}:{1}]成功", ipAddress, remotePort);
            return true;
        }

        // 关闭连接
        public void Disconnect(int timeout)
        {
            if (m_socket.Connected)
            {
                m_socket.Shutdown(SocketShutdown.Both);
                m_socket.Close(timeout);
            }
            else
            {
                m_socket.Close();
            }

        }

        // 发送消息
        public bool SendAsync(UnityUtility.CBuffer outBuffer)
        {
            if (m_socket == null || !m_socket.Connected)
            {
                return false;
            }

            uint dataSize = (uint)outBuffer.ReadSize;
            uint dataPos = 0;

            lock (m_sendBuffer)
            {
                while (dataSize > 0)
                {
                    uint cmdFlag = GNET_PACKET_FLAG;
                    uint cmdLen = 0;
                    if (dataSize > GNET_PACKET_LEN)
                    {
                        cmdFlag |= GNET_PACKET_NEXT;
                        cmdLen = GNET_PACKET_LEN;
                    }
                    else
                    {
                        cmdLen = dataSize;
                    }
                    cmdFlag = (cmdFlag & GNET_PACKET_SIGN) | cmdLen;

                    byte[] cmdFlagBytes = System.BitConverter.GetBytes(cmdFlag);
                    if (!m_sendBuffer.Write(cmdFlagBytes, 0, cmdFlagBytes.Length))
                    {
                        return false;
                    }
                    if (!m_sendBuffer.Write(outBuffer.BufferHead, (int)dataPos, (int)cmdLen))
                    {
                        return false;
                    }
                    dataSize -= cmdLen;
                    dataPos += cmdLen;
                }
            }
            if (_SendBufferToNet() >= 0)
            {
                return true;
            }

            UnityUtility.CTrace.Singleton.debug("发送消息失败, 断开连接");

            Disconnect(0);
            _PushPacket(CNetPacket.EType.CONNECTION_LOST, "");

            return false;
        }

        public bool IsConnected
        {
            get
            {
                if (m_socket == null || !m_socket.Connected)
                {
                    return false;
                }
                return true;
            }
        }

        // 异步接收消息
        public bool RecvAsync(out CNetPacket netPacket)
        {
            netPacket = null;
            if (m_packetQueue.Count <= 0)
            {
                return false;
            }
            lock (m_packetQueue)
            {
                netPacket = (CNetPacket)m_packetQueue.Dequeue(); ;
            }
            return true;
        }

        // 异步连接回调
        private void _ConnectionCallback(System.IAsyncResult ar)
        {
            try
            {
                // 与服务器取得连接
                m_socket.EndConnect(ar);

                // 设置timeout
                m_socket.SendTimeout = m_sendTimeout;
                m_socket.ReceiveTimeout = m_revTimeout;

                // 向Network Manager传递消息
                _PushPacket(CNetPacket.EType.CONNECTION_REQUEST_SUCCESS, "");

                // 接收从服务器返回的头信息
                m_socket.BeginReceive(m_netRecvBuffer, 0, m_netRecvBuffer.Length, SocketFlags.None, new System.AsyncCallback(_ReceiveCallback), m_netRecvBuffer);
            }
            catch (System.Exception e)
            {
                // 错误处理
                _PushPacket(CNetPacket.EType.CONNECTION_REQUEST_FAILED, e.Message);
                Disconnect(0);
            }
        }

        // 接收消息回调
        private void _ReceiveCallback(System.IAsyncResult ar)
        {
            try
            {
                int readSize = m_socket.EndReceive(ar);

                // 服务器断开连接
                if (readSize <= 0)
                {
                    Disconnect(0);
                    _PushPacket(CNetPacket.EType.CONNECTION_LOST, "");
                    return;
                }
                //收到数据，写入缓存
                m_recvBuffer.Write(m_netRecvBuffer, 0, readSize);

                do
                {
                    int buffReadSize = m_recvBuffer.ReadSize;
                    if (buffReadSize < 4)
                    {
                        m_socket.BeginReceive(m_netRecvBuffer, 0, m_netRecvBuffer.Length, SocketFlags.None, new System.AsyncCallback(_ReceiveCallback), m_netRecvBuffer);
                        return;
                    }
                    //合并数据包
                    UnityUtility.CBuffer outBuffer = null;
                    uint cmdFlag = 0;
                    int res = _MergerPacket(m_recvBuffer, out cmdFlag, out outBuffer);
                    if (res < 0)
                    {
                        Disconnect(0);
                        _PushPacket(CNetPacket.EType.CONNECTION_CLOSE, "");
                        return;
                    }
                    else if (res == 0)
                    {
                        m_socket.BeginReceive(m_netRecvBuffer, 0, m_netRecvBuffer.Length, SocketFlags.None, new System.AsyncCallback(_ReceiveCallback), m_netRecvBuffer);
                        return;
                    }

                    //uint cmdFlag = System.BitConverter.ToUInt32(outBuffer.BufferHead, 0);
                    uint flag = cmdFlag & GNET_PACKET_SIGN;
                    uint len = cmdFlag & GNET_PACKET_LEN;
                    //数据包标志
                    if ((flag & GNET_PACKET_FLAG) == 0)
                    {
                        Disconnect(0);
                        _PushPacket(CNetPacket.EType.CONNECTION_CLOSE, "");
                        return;
                    }
                    //数据包加密
                    if ((flag & GNET_PACKET_ENCRYPT) != 0)
                    {
                        Disconnect(0);
                        _PushPacket(CNetPacket.EType.CONNECTION_CLOSE_ENCRYPT, "");
                        return;
                    }
                    //数据压缩
                    if ((flag & GNET_PACKET_COMPRESS) != 0)
                    {
                        Disconnect(0);
                        _PushPacket(CNetPacket.EType.CONNECTION_CLOSE_COMPRESS, "");
                        return;
                    }
                    _PushPacket(outBuffer);
                }
                while (true);
            }
            catch (System.Exception e)
            {
                _PushPacket(CNetPacket.EType.CONNECTION_LOST, e.Message);
                Disconnect(0);
            }
        }

        private int _MergerPacket(UnityUtility.CBuffer inBuffer, out uint outBufferFlag, out UnityUtility.CBuffer outBuffer)
        {
            int readIndex = inBuffer.ReadIndex;
            uint cmdFlag = System.BitConverter.ToUInt32(inBuffer.BufferHead, readIndex);
            uint flag = cmdFlag & GNET_PACKET_SIGN;
            uint len = cmdFlag & GNET_PACKET_LEN;
            uint dataSize = len + sizeof(uint);

            outBuffer = null;
            outBufferFlag = 0;

            while ((flag & GNET_PACKET_NEXT) != 0)
            {
                if (dataSize + sizeof(uint) > inBuffer.ReadSize)
                {
                    return 0;
                }
                cmdFlag = System.BitConverter.ToUInt32(inBuffer.BufferHead, (int)dataSize + readIndex);
                len = cmdFlag & GNET_PACKET_LEN;
                flag = cmdFlag & GNET_PACKET_SIGN;
                dataSize += len + sizeof(uint);
            }
            if (dataSize > inBuffer.ReadSize)
            {
                return 0;
            }
            outBuffer = new UnityUtility.CBuffer();

            cmdFlag = System.BitConverter.ToUInt32(inBuffer.BufferHead, readIndex);
            flag = cmdFlag & GNET_PACKET_SIGN;
            len = cmdFlag & GNET_PACKET_LEN;
            dataSize = len + sizeof(uint);

            outBufferFlag = cmdFlag;
            uint readPos = sizeof(uint);

            while ((flag & GNET_PACKET_NEXT) != 0)
            {
                outBuffer.Write(inBuffer.BufferHead, (int)readPos, (int)len);
                readPos += len;

                cmdFlag = System.BitConverter.ToUInt32(inBuffer.BufferHead, (int)dataSize + readIndex);
                len = cmdFlag & GNET_PACKET_LEN;
                flag = cmdFlag & GNET_PACKET_SIGN;
                dataSize += len + sizeof(uint);
                readPos += sizeof(uint);
            }
            outBuffer.Write(inBuffer.BufferHead, (int)readPos + readIndex, (int)len);
            inBuffer.ReadFlip((int)dataSize);

            return outBuffer.ReadSize;
        }

        private int _SendBufferToNet()
        {
            lock (m_beginSendInfor)
            {
                if (m_beginSendInfor.m_sendSize > 0)
                {
                    return 0;
                }

                lock (m_sendBuffer)
                {
                    if (m_sendBuffer.ReadSize <= 0)
                    {
                        return 0;
                    }
                    m_beginSendInfor.m_sendSize = m_sendBuffer.Read(m_netSendBuffer, 0, m_netSendBuffer.Length);
                    m_beginSendInfor.m_index = 0;
                }
            }
            try
            {
                m_socket.BeginSend(m_netSendBuffer, m_beginSendInfor.m_index, m_beginSendInfor.m_sendSize, System.Net.Sockets.SocketFlags.None, new System.AsyncCallback(_SendCallback), m_beginSendInfor);
            }
            catch (System.Exception)
            {
                return -1;
            }
            return m_beginSendInfor.m_sendSize;
        }

        //发送回调
        private void _SendCallback(System.IAsyncResult ar)
        {
            int sendSize = 0;
            try
            {
                sendSize = m_socket.EndSend(ar);
            }
            catch (System.Exception)
            {
                _PushPacket(CNetPacket.EType.CONNECTION_LOST, "");
                Disconnect(0);
            }

            if (sendSize < m_beginSendInfor.m_sendSize)
            {
                m_beginSendInfor.m_sendSize -= sendSize;
                m_beginSendInfor.m_index += sendSize;

                try
                {
                    m_socket.BeginSend(m_netSendBuffer, m_beginSendInfor.m_index, m_beginSendInfor.m_sendSize, System.Net.Sockets.SocketFlags.None, new System.AsyncCallback(_SendCallback), m_beginSendInfor);
                }
                catch (System.Exception)
                {
                    Disconnect(0);
                    _PushPacket(CNetPacket.EType.CONNECTION_LOST, "");
                    return;
                }
            }

            m_beginSendInfor.m_sendSize = 0;
            m_beginSendInfor.m_index = 0;
            if (_SendBufferToNet() < 0)
            {
                Disconnect(0);
                _PushPacket(CNetPacket.EType.CONNECTION_LOST, "");
                return;
            }
        }

        private void _PushPacket(UnityUtility.CBuffer buffer)
        {
            CNetPacket packet = new CNetPacket();
            packet.m_packetType = CNetPacket.EType.CONNECTION_RECV_PACKET;
            packet.m_peer = m_socket;
            packet.m_buffer = buffer;

            lock (m_packetQueue)
            {
                m_packetQueue.Enqueue(packet);
            }
        }

        // 向Network Manager的队列传递内部消息
        private void _PushPacket(CNetPacket.EType packetType, string exception)
        {
            CNetPacket packet = new CNetPacket();
            packet.m_packetType = packetType;
            packet.m_peer = m_socket;
            packet.m_error = exception;

            lock (m_packetQueue)
            {
                m_packetQueue.Enqueue(packet);
            }
        }

        // 发送和接收的超时时间
        private int m_sendTimeout = 3;
        private int m_revTimeout = 3;

        private Socket m_socket = null;
        private System.Collections.Queue m_packetQueue = new System.Collections.Queue();

        private UnityUtility.CBuffer m_recvBuffer = new UnityUtility.CBuffer();
        private UnityUtility.CBuffer m_sendBuffer = new UnityUtility.CBuffer();

        private class CBeginSendInfor
        {
            public int m_index = 0;
            public int m_sendSize = 0;
        }
        private byte[] m_netRecvBuffer = new byte[GNET_BUFFER_MAX];
        private byte[] m_netSendBuffer = new byte[GNET_BUFFER_MAX];
        CBeginSendInfor m_beginSendInfor = new CBeginSendInfor();

        //数据包标志
        private const uint GNET_PACKET_FLAG = 0X80000000;
        //数据包压缩
        private const uint GNET_PACKET_COMPRESS = 0X40000000;
        //数据包加密
        private const uint GNET_PACKET_ENCRYPT = 0X20000000;
        //数据包连包
        private const uint GNET_PACKET_NEXT = 0X10000000;
        //数据控制标志
        private const uint GNET_PACKET_SIGN = 0XFF000000;
        //数据包长度
        private const uint GNET_PACKET_LEN = 0X00FFFFFF;
        //数据包长度
        private const uint GNET_BUFFER_MAX = 1024 * 64;
    }
}
