using System;
using System.Runtime.InteropServices;

namespace UnityUtility
{
    public class CStream
    {
        public CStream()
        {
            m_buffer = new CBuffer();
        }

        public CStream(CBuffer buffer)
        {
            m_buffer = buffer;
        }

        public CBuffer Buffer
        {
            get
            {
                return m_buffer;
            }
            set
            {
                m_buffer = value;
            }
        }

        public bool ReadBoolean()
        {
            if (m_buffer.ReadSize < sizeof(bool))
            {
                throw new System.Exception("buffer null");
            }
            bool data = System.BitConverter.ToBoolean(m_buffer.BufferHead, m_buffer.ReadIndex);
            m_buffer.ReadFlip(sizeof(bool));
            return data;
        }

        public float ReadFloat()
        {
            if (m_buffer.ReadSize < sizeof(float))
            {
                throw new System.Exception("buffer null");
            }
            float data = System.BitConverter.ToSingle(m_buffer.BufferHead, m_buffer.ReadIndex);
            m_buffer.ReadFlip(sizeof(float));
            return data;
        }

        public double ReadDouble()
        {
            if (m_buffer.ReadSize < sizeof(double))
            {
                throw new System.Exception("buffer null");
            }
            double data = System.BitConverter.ToDouble(m_buffer.BufferHead, m_buffer.ReadIndex);
            m_buffer.ReadFlip(sizeof(double));
            return data;
        }

        public byte ReadByte()
        {
            if (m_buffer.ReadSize < sizeof(byte))
            {
                throw new System.Exception("buffer null");
            }
            byte data = 0;
            m_buffer.ReadByte(ref data);
            return data;
        }

        public short ReadShort()
        {
            if (m_buffer.ReadSize < sizeof(short))
            {
                throw new System.Exception("buffer null");
            }
            short data = System.BitConverter.ToInt16(m_buffer.BufferHead, m_buffer.ReadIndex);
            m_buffer.ReadFlip(sizeof(short));
            return data;
        }

        public int ReadInt()
        {
            if (m_buffer.ReadSize < sizeof(int))
            {
                throw new System.Exception("buffer null");
            }
            int data = System.BitConverter.ToInt32(m_buffer.BufferHead, m_buffer.ReadIndex);
            m_buffer.ReadFlip(sizeof(int));
            return data;
        }

        public long ReadLong()
        {
            if (m_buffer.ReadSize < sizeof(long))
            {
                throw new System.Exception("buffer empty");
            }
            long data = System.BitConverter.ToInt64(m_buffer.BufferHead, m_buffer.ReadIndex);
            m_buffer.ReadFlip(sizeof(long));
            return data;
        }

        public sbyte ReadSByte()
        {
            if (m_buffer.ReadSize < sizeof(sbyte))
            {
                throw new System.Exception("buffer null");
            }
            sbyte data = 0;
            m_buffer.ReadSByte(ref data);
            return data;
        }

        public ushort ReadUShort()
        {
            if (m_buffer.ReadSize < sizeof(ushort))
            {
                throw new System.Exception("buffer null");
            }
            ushort data = System.BitConverter.ToUInt16(m_buffer.BufferHead, m_buffer.ReadIndex);
            m_buffer.ReadFlip(sizeof(ushort));
            return data;
        }

        public uint ReadUInt()
        {
            if (m_buffer.ReadSize < sizeof(uint))
            {
                throw new System.Exception("buffer null");
            }
            uint data = System.BitConverter.ToUInt32(m_buffer.BufferHead, m_buffer.ReadIndex);
            m_buffer.ReadFlip(sizeof(uint));
            return data;
        }

        public ulong ReadULong()
        {
            if (m_buffer.ReadSize < sizeof(ulong))
            {
                throw new System.Exception("buffer empty");
            }
            ulong data = System.BitConverter.ToUInt64(m_buffer.BufferHead, m_buffer.ReadIndex);
            m_buffer.ReadFlip(sizeof(ulong));
            return data;
        }

        public string ReadString()
        {
            int strSize = ReadInt();
            if (strSize <= 0)
            {
                return "";
            }
            string data = System.Text.Encoding.UTF8.GetString(m_buffer.BufferHead, m_buffer.ReadIndex, strSize);
            m_buffer.ReadFlip(strSize);
            return data;
        }

        public bool Read(ref bool data)
        {
            try
            {
                data = ReadBoolean();
                return true;
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool Read(ref float data)
        {
            try
            {
                data = ReadFloat();
                return true;
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool Read(ref double data)
        {
            try
            {
                data = ReadDouble();
                return true;
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool Read(ref byte data)
        {
            try
            {
                data = ReadByte();
                return true;
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool Read(ref short data)
        {
            try
            {
                data = ReadShort();
                return true;
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool Read(ref int data)
        {
            try
            {
                data = ReadInt();
                return true;
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool Read(ref long data)
        {
            try
            {
                data = ReadLong();
                return true;
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool Read(ref sbyte data)
        {
            try
            {
                data = ReadSByte();
                return true;
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool Read(ref ushort data)
        {
            try
            {
                data = ReadUShort();
                return true;
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool Read(ref uint data)
        {
            try
            {
                data = ReadUInt();
                return true;
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool Read(ref ulong data)
        {
            try
            {
                data = ReadULong();
                return true;
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool Read(ref string data)
        {
            try
            {
                data = ReadString();
                return true;
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool Write(bool data)
        {
            try
            {
                byte[] tmpBuf = System.BitConverter.GetBytes(data);
                return m_buffer.Write(tmpBuf, 0, tmpBuf.Length);
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool Write(char data)
        {
            try
            {
                byte[] tmpBuf = System.BitConverter.GetBytes(data);
                return m_buffer.Write(tmpBuf, 0, tmpBuf.Length);
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool Write(sbyte data)
        {
            try
            {
                return m_buffer.WriteSByte(data);
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool Write(short data)
        {
            try
            {
                byte[] tmpBuf = System.BitConverter.GetBytes(data);
                return m_buffer.Write(tmpBuf, 0, tmpBuf.Length);
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool Write(int data)
        {
            try
            {
                byte[] tmpBuf = System.BitConverter.GetBytes(data);
                return m_buffer.Write(tmpBuf, 0, tmpBuf.Length);
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool Write(long data)
        {
            try
            {
                byte[] tmpBuf = System.BitConverter.GetBytes(data);
                return m_buffer.Write(tmpBuf, 0, tmpBuf.Length);
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool Write(byte data)
        {
            try
            {
                return m_buffer.WriteByte(data);
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool Write(ushort data)
        {
            try
            {
                byte[] tmpBuf = System.BitConverter.GetBytes(data);
                return m_buffer.Write(tmpBuf, 0, tmpBuf.Length);
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool Write(uint data)
        {
            try
            {
                byte[] tmpBuf = System.BitConverter.GetBytes(data);
                return m_buffer.Write(tmpBuf, 0, tmpBuf.Length);
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool Write(ulong data)
        {
            try
            {
                byte[] tmpBuf = System.BitConverter.GetBytes(data);
                return m_buffer.Write(tmpBuf, 0, tmpBuf.Length);
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool Write(float data)
        {
            try
            {
                byte[] tmpBuf = System.BitConverter.GetBytes(data);
                return m_buffer.Write(tmpBuf, 0, tmpBuf.Length);
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool Write(double data)
        {
            try
            {
                byte[] tmpBuf = System.BitConverter.GetBytes(data);
                return m_buffer.Write(tmpBuf, 0, tmpBuf.Length);
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        public bool Write(string strVal)
        {
            try
            {
                int iCount = 0;

                if (strVal.Length == 0)
                {
                    return Write(iCount);
                }

                byte[] tmpBuf = System.Text.Encoding.UTF8.GetBytes(strVal);
                iCount = tmpBuf.Length;

                if (!Write(iCount))
                {
                    return false;
                }
                return Write(tmpBuf, 0, iCount);
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        /// <summary>
        /// 把 data 中的数据写入 Stream 中
        /// index  : 是指 data 中的位置偏移量
        /// length : 需要拷贝的数据总长度
        /// </summary>
        public bool Write(byte[] data, int index, int length)
        {
            try
            {
                return m_buffer.Write(data, index, length);
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        /// <summary>
        /// 把 Stream 中的数据读到 buffer 中
        /// index   : 是指 buffer 中的位置偏移量
        /// length : 需要拷贝的数据总长度
        /// </summary>
        public int Read(byte[] buffer, int index, int length)
        {
            int writeSize = 0;
            try
            {
                writeSize = m_buffer.Read(buffer, index, length);
            }
            catch (System.Exception)
            {
                return -1;
            }
            return writeSize;
        }

        public bool Write(object data)
        {
            int size = Marshal.SizeOf(data);
            byte[] bytes = new byte[size];
            IntPtr structPtr = Marshal.AllocHGlobal(size);
            Marshal.StructureToPtr(data, structPtr, false);
            Marshal.Copy(structPtr, bytes, 0, size);
            Marshal.FreeHGlobal(structPtr);
            return Write(bytes, 0, size);
        }

        public object ReadObject(Type type)
        {
            int size = Marshal.SizeOf(type);

            if (m_buffer.ReadSize < size)
            {
                throw new System.Exception("buffer null");
            }

            IntPtr structPtr = Marshal.AllocHGlobal(size);
            Marshal.Copy(m_buffer.BufferHead, m_buffer.ReadIndex, structPtr, size);
            object obj = Marshal.PtrToStructure(structPtr, type);
            Marshal.FreeHGlobal(structPtr);
            m_buffer.ReadFlip(size);

            return obj;

        }

        public bool Read(ref object data)
        {
            try
            {
                data = ReadObject(data.GetType());
                return true;
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        private CBuffer m_buffer = null;
    }
}