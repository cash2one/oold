using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace UnityGMClient
{
    [StructLayoutAttribute(LayoutKind.Sequential, Pack=1)]
    public struct SAccountKey
    {
        public UInt64 m_accountID;
        public UInt16 m_zoneID;
    }

    [StructLayoutAttribute(LayoutKind.Sequential, Pack = 1)]
    public struct SRoleKey
    {
        public UInt64 m_accountID;
        public UInt16 m_zoneID;
        public UInt32 m_roleIndex;

        public void serializeFrom(UnityUtility.CStream stream)
        {
            m_accountID = stream.ReadULong();
            m_zoneID = stream.ReadUShort();
            m_roleIndex = stream.ReadUInt();
        }

        public void serializeTo(UnityUtility.CStream stream)
        {
            stream.Write(m_accountID);
            stream.Write(m_zoneID);
            stream.Write(m_roleIndex);
        }

    }

    [StructLayoutAttribute(LayoutKind.Sequential, Pack = 1)]
    public struct SVector3
    {
        public SVector3(float a_x, float a_y, float a_z)
        {
            m_x = a_x;
            m_y = a_y;
            m_z = a_z;
        }

        public SVector3(SVector3 a_vector3)
        {
            m_x = a_vector3.m_x;
            m_y = a_vector3.m_y;
            m_z = a_vector3.m_z;
        }

        public float m_x;
        public float m_y;
        public float m_z;
    }

    public struct SRoleScene
    {
        public SRoleKey m_roleKey;
        public string m_roleName;
        public SVector3 m_position;
    }
}
