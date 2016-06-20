using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using System.Drawing;

namespace SimulateControl
{
    class CPlane
    {
        private Vector3 m_center = new Vector3(0, 0, 0);
        private float m_width = 100;
        private float m_height = 100;

        private Vector3[] m_pointVectors = new Vector3[4];
        private CustomVertex.PositionColored[] m_colorVectors = new CustomVertex.PositionColored[4];
        private Int32[] m_indexVectors = new Int32[6];

        public void setPlane(Vector3 a_center, float a_width, float a_height)
        {
            m_center = a_center;
            m_width = a_width;
            m_height = a_height;

            setPlane();
        }

        public void render(Device a_device)
        {
            a_device.VertexFormat = CustomVertex.PositionColored.Format;
            a_device.DrawIndexedUserPrimitives(PrimitiveType.TriangleList, 0, 6, 2, m_indexVectors, false, m_colorVectors);
        }

        private void setPlane()
        {
            m_pointVectors[0] = new Vector3(m_center.X + m_width / 2, m_center.Y, m_center.Z + m_height / 2);
            m_pointVectors[1] = new Vector3(m_center.X + m_width / 2, m_center.Y, m_center.Z - m_height / 2);
            m_pointVectors[2] = new Vector3(m_center.X - m_width / 2, m_center.Y, m_center.Z - m_height / 2);
            m_pointVectors[3] = new Vector3(m_center.X - m_width / 2, m_center.Y, m_center.Z + m_height / 2);

            m_colorVectors[0].Position = m_pointVectors[0];
            m_colorVectors[0].Color = Color.Gray.ToArgb();
            m_colorVectors[1].Position = m_pointVectors[1];
            m_colorVectors[1].Color = Color.Gray.ToArgb();
            m_colorVectors[2].Position = m_pointVectors[2];
            m_colorVectors[2].Color = Color.Gray.ToArgb();
            m_colorVectors[3].Position = m_pointVectors[3];
            m_colorVectors[3].Color = Color.Gray.ToArgb();

            m_indexVectors[0] = 0; m_indexVectors[1] = 1; m_indexVectors[2] = 3;
            m_indexVectors[3] = 1; m_indexVectors[4] = 2; m_indexVectors[5] = 3;


        }
    }
}
