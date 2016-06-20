using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using System.Drawing;

namespace SimulateControl
{
    public class CSceneRole
    {
        public CSceneRole(float a_x, float a_y, float a_z)
        {
            m_sceneRoleID = ++m_currentSceneRoleID;
            setPosition(a_x, a_y, a_z);
            m_box.setBox(m_position, 5, 5, 5);
        }

        public void setPosition(float a_x, float a_y, float a_z)
        {
            m_position.X = a_x;
            m_position.Y = a_y;
            m_position.Z = a_z;

            m_box.setBox(m_position);
        }

        public Vector3 Position
        {
            get
            {
                return m_position;
            }
            set
            {
                m_position = value;
            }
        }

        public void setSpeed(float a_x, float a_y, float a_z)
        {
            m_speed.X = a_x;
            m_speed.Y = a_y;
            m_speed.Z = a_z;
        }

        public Vector3 Speed
        {
            get
            {
                return m_speed;
            }
            set
            {
                m_speed = value;
            }
        }

        public void update(float a_timer)
        {
            m_position += m_speed * a_timer;

            m_box.setBox(m_position);
        }

        public IRender getRender()
        {
            return m_box;
        }

        private Vector3 m_position = new Vector3(0, 0, 0);
        private Vector3 m_speed = new Vector3(0, 0, 0);

        private CBox m_box = new CBox();
        private uint m_sceneRoleID = 0;

        private static uint m_currentSceneRoleID = 0;
    }
}
