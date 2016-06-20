using System;

namespace UnityUtility
{
    public class CBuffer
    {
        public CBuffer()
        {
            Init(8);
        }

        public CBuffer(int size)
        {
            Init(size);
        }

        public virtual bool Init(int size)
        {
            if (m_buffer == null)
            {
                m_buffer = new byte[size];
                return true;
            }
            return false;
        }

        public bool Write(byte[] data, int index, int length)
        {
            if (!WriteReserve(length))
            {
                return false;
            }
            System.Array.Copy(data, index, m_buffer, m_writePos, length);
            m_writePos += length;
            return true;
        }

        public int Read(byte[] buffer, int offset, int writeLen)
        {
            int size = ReadSize;
            if (size <= 0)
            {
                return 0;
            }
            if (writeLen < size)
            {
                size = writeLen;
            }
            System.Array.Copy(m_buffer, m_readPos, buffer, offset, size);
            ReadFlip(size);
            return size;
        }

        public bool WriteByte(byte data)
        {
            if (!WriteReserve(1))
            {
                return false;
            }
            m_buffer[m_writePos] = data;
            m_writePos += 1;
            return true;
        }

        public bool WriteSByte(sbyte data)
        {
            if (!WriteReserve(1))
            {
                return false;
            }
            m_buffer[m_writePos] = (byte)data;
            m_writePos += 1;
            return true;
        }

        public bool ReadByte(ref byte data)
        {
            if (!CanRead)
            {
                return false;
            }
            data = m_buffer[m_readPos];
            m_readPos += 1;
            return true;
        }

        public bool ReadSByte(ref sbyte data)
        {
            if (!CanRead)
            {
                return false;
            }
            data = (sbyte)m_buffer[m_readPos];
            m_readPos += 1;
            return true;
        }

        public virtual bool WriteReserve(int size)
        {
            if (WriteSize < size)
            {
                int maxSize = (int)(m_buffer.Length + size) * 2;
                System.Array.Resize(ref m_buffer, maxSize);
            }
            return true;
        }

        public int WriteIndex
        {
            get
            {
                return m_writePos;
            }
        }

        public int ReadIndex
        {
            get
            {
                int tmpSize = m_writePos - m_readPos;
                if (tmpSize <= m_readPos)
                {
                    System.Array.Copy(m_buffer, m_readPos, m_buffer, 0, tmpSize);
                    m_readPos = 0;
                    m_writePos = tmpSize;
                }

                return m_readPos;
            }
        }

        public byte[] BufferHead
        {
            get
            {
                return m_buffer;
            }
        }

        public bool CanRead
        {
            get
            {
                return ReadSize > 0;
            }
        }

        public int ReadSize
        {
            get
            {
                if (m_writePos < m_readPos)
                {
                    return 0;
                }
                return m_writePos - m_readPos;
            }
        }

        public int WriteSize
        {
            get
            {
                if (m_buffer == null || m_buffer.Length < m_writePos)
                {
                    return 0;
                }
                return (int)m_buffer.Length - m_writePos;
            }
        }

        public void Reset()
        {
            m_writePos = 0;
            m_readPos = 0;
        }

        public void ReadFlip(int size)
        {
            m_readPos += size;
            if (m_readPos >= m_writePos)
            {
                m_readPos = 0;
                m_writePos = 0;
            }
        }

        public void WriteFlip(int size)
        {
            m_writePos += size;

            if (m_writePos > m_buffer.Length)
            {
                m_writePos = m_buffer.Length;
            }

            int tmpSize = m_writePos - m_readPos;
            if (tmpSize <= m_readPos)
            {
                System.Array.Copy(m_buffer, m_readPos, m_buffer, 0, tmpSize);
                m_readPos = 0;
                m_writePos = tmpSize;
            }
        }

        private int m_readPos;
        private int m_writePos;
        private byte[] m_buffer;
    }
}