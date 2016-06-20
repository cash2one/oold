using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using System.Drawing;


namespace SimulateControl
{
    class CSphere : IRender
    {
        private Vector3 m_center = new Vector3(0, 0, 0);
        private float m_radius = 1;
        private int m_splitCount = 10;

        private Vector3[] m_pointVectors = null;
        private Int32[] m_indexVectors = null;

        private Color m_color = Color.Blue;

        public CSphere()
        {
            Random random = new Random();
            m_color = RandomColor.nextColor();
            _setSplitCount();
        }

        public void setSphere(Vector3 a_center, float a_radius)
        {
            m_center = a_center;
            m_radius = a_radius;

            _setSphere();
        }

        public void setSphere(Vector3 a_center, float a_radius, int a_splitCount)
        {
            m_center = a_center;
            m_radius = a_radius;
            m_splitCount = a_splitCount;

            _setSplitCount();
            _setSphere();
        }

        private void _setSphere()
        {
            float theta = (float)Math.PI / m_splitCount;
            float alpha = 2 * (float)Math.PI / m_splitCount;

            for (int i = 0; i <= m_splitCount; ++i)
            {
                for (int j = 0; j <= m_splitCount; ++j)
                {
                    float x = m_radius * (float)Math.Sin(i * theta) * (float)Math.Cos(j * alpha);
                    float y = m_radius * (float)Math.Cos(i * theta);
                    float z = m_radius * (float)Math.Sin(i * theta) * (float)Math.Sin(j * alpha);

                    m_pointVectors[i * (m_splitCount + 1) + j] = new Vector3(m_center.X + x, m_center.Y + y, m_center.Z + z);
                }
            }

            int i_max = m_splitCount + 1;
            for (int i = 0; i < m_splitCount; ++i)
            {
                for (int j = 0; j < m_splitCount; ++j)
                {
//                     m_indexVectors[6 * (m_splitCount * i + j)] = j + i * i_max;
//                     m_indexVectors[6 * (m_splitCount * i + j) + 1] = j + 1 + i * i_max;
//                     m_indexVectors[6 * (m_splitCount * i + j) + 2] = j + (i + 1) * i_max;
//                     m_indexVectors[6 * (m_splitCount * i + j) + 3] = j + 1 + i * i_max;
//                     m_indexVectors[6 * (m_splitCount * i + j) + 4] = j + 1 + (i + 1) * i_max;
//                     m_indexVectors[6 * (m_splitCount * i + j) + 5] = j + (i + 1) * i_max;

                    m_indexVectors[6 * (m_splitCount * i + j)] = i_max * i + j;
                    m_indexVectors[6 * (m_splitCount * i + j) + 1] = i_max * i + (j + 1);
                    m_indexVectors[6 * (m_splitCount * i + j) + 2] = i_max * (i + 1) + j;

                    m_indexVectors[6 * (m_splitCount * i + j) + 3] = i_max * i + (j + 1);
                    m_indexVectors[6 * (m_splitCount * i + j) + 4] = i_max * (i + 1) + j + 1;
                    m_indexVectors[6 * (m_splitCount * i + j) + 5] = i_max * (i + 1) + j;
                }
            }
        }

        private void _setSplitCount()
        {
            m_pointVectors = new Vector3[(m_splitCount + 1) * (m_splitCount + 1)];
            m_indexVectors = new Int32[6 * m_splitCount * m_splitCount];
        }

        public Vector3[] getPositions()
        {
            return m_pointVectors;
        }

        public int[] getIndexs()
        {
            return m_indexVectors;
        }

        public Color getColor()
        {
            return m_color;
        }

        public Vector3 getCenter()
        {
            return m_center;
        }
    }
}
