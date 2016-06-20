using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using System.Drawing;

namespace SimulateControl
{

    public class CBox : IRender
    {

        private Vector3 m_center = new Vector3(0, 0, 0);
        private float m_width = 1;
        private float m_height = 1;
        private float m_deep = 1;

        private Vector3[] m_pointVectors = new Vector3[8];
        private Int32[] m_indexVectors = new Int32[36];

        private Color m_color = Color.Red;

        public CBox()
        {
            m_color = RandomColor.nextColor();

            m_pointVectors[0] = new Vector3(0, 0, 0);
            m_pointVectors[1] = new Vector3(0, 0, 0);
            m_pointVectors[2] = new Vector3(0, 0, 0);
            m_pointVectors[3] = new Vector3(0, 0, 0);
            m_pointVectors[4] = new Vector3(0, 0, 0);
            m_pointVectors[5] = new Vector3(0, 0, 0);
            m_pointVectors[6] = new Vector3(0, 0, 0);
            m_pointVectors[7] = new Vector3(0, 0, 0);
        }

        public void setBox(Vector3 a_center)
        {
            m_center = a_center;
            _setBox();
        }

        public void setBox(Vector3 a_center, float a_width, float a_height, float a_deep)
        {
            m_center = a_center;
            m_width = a_width;
            m_height = a_height;
            m_deep = a_deep;

            _setBox();
        }

        private void _setBox()
        {
            m_pointVectors[0].X = m_center.X + m_width / 2; m_pointVectors[0].Y = m_center.Y + m_height / 2; m_pointVectors[0].Z = m_center.Z + m_deep / 2;
            m_pointVectors[1].X = m_center.X + m_width / 2; m_pointVectors[1].Y = m_center.Y + m_height / 2; m_pointVectors[1].Z = m_center.Z - m_deep / 2;
            m_pointVectors[2].X = m_center.X - m_width / 2; m_pointVectors[2].Y = m_center.Y + m_height / 2; m_pointVectors[2].Z = m_center.Z - m_deep / 2;
            m_pointVectors[3].X = m_center.X - m_width / 2; m_pointVectors[3].Y = m_center.Y + m_height / 2; m_pointVectors[3].Z = m_center.Z + m_deep / 2;
            m_pointVectors[4].X = m_center.X + m_width / 2; m_pointVectors[4].Y = m_center.Y - m_height / 2; m_pointVectors[4].Z = m_center.Z + m_deep / 2;
            m_pointVectors[5].X = m_center.X + m_width / 2; m_pointVectors[5].Y = m_center.Y - m_height / 2; m_pointVectors[5].Z = m_center.Z - m_deep / 2;
            m_pointVectors[6].X = m_center.X - m_width / 2; m_pointVectors[6].Y = m_center.Y - m_height / 2; m_pointVectors[6].Z = m_center.Z - m_deep / 2;
            m_pointVectors[7].X = m_center.X - m_width / 2; m_pointVectors[7].Y = m_center.Y - m_height / 2; m_pointVectors[7].Z = m_center.Z + m_deep / 2;

            m_indexVectors[0] = 0; m_indexVectors[1] = 1; m_indexVectors[2] = 3;
            m_indexVectors[3] = 1; m_indexVectors[4] = 2; m_indexVectors[5] = 3;

            m_indexVectors[6] = 7; m_indexVectors[7] = 5; m_indexVectors[8] = 4;
            m_indexVectors[9] = 7; m_indexVectors[10] = 6; m_indexVectors[11] = 5;

            m_indexVectors[12] = 0; m_indexVectors[13] = 4; m_indexVectors[14] = 1;
            m_indexVectors[15] = 1; m_indexVectors[16] = 4; m_indexVectors[17] = 5;

            m_indexVectors[18] = 1; m_indexVectors[19] = 5; m_indexVectors[20] = 2;
            m_indexVectors[21] = 2; m_indexVectors[22] = 5; m_indexVectors[23] = 6;

            m_indexVectors[24] = 2; m_indexVectors[25] = 6; m_indexVectors[26] = 3;
            m_indexVectors[27] = 3; m_indexVectors[28] = 6; m_indexVectors[29] = 7;

            m_indexVectors[30] = 0; m_indexVectors[31] = 3; m_indexVectors[32] = 7;
            m_indexVectors[33] = 0; m_indexVectors[34] = 7; m_indexVectors[35] = 4;
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
