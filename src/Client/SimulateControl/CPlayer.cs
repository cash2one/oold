using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using System.Drawing;
using System.Collections;

namespace SimulateControl
{

    public class CPlayer : IRole
    {
        private Vector3 m_direction = new Vector3(0, 0, 0);
        private Vector3 m_position = new Vector3(0, 2.5f, 0);
        private CBox m_box = new CBox();

        private bool m_isMoveFrontValid = false;
        private bool m_isMoveBackValid = false;
        private bool m_isMoveLeftValid = false;
        private bool m_isMoveRightValid = false;

        private float m_speed = 0.1f;

        public CPlayer()
        {
            m_box.setBox(m_position, 2, 5, 2);
        }

        public float Speed
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

        public Vector3 Direction
        {
            get
            {
                return m_direction;
            }

            set
            {
                m_direction = value;
            }
        }

        public void moveFront(bool a_isValid)
        {
            if (m_isMoveBackValid)
            {
                return ;
            }
            m_isMoveFrontValid = a_isValid;
        }

        public void moveBack(bool a_isValid)
        {
            if (m_isMoveFrontValid)
            {
                return;
            }
            m_isMoveBackValid = a_isValid;
        }

        public void moveLeft(bool a_isValid)
        {
            if (m_isMoveRightValid)
            {
                return;
            }
            m_isMoveLeftValid = a_isValid;
        }

        public void moveRight(bool a_isValid)
        {
            if (m_isMoveLeftValid)
            {
                return;
            }
            m_isMoveRightValid = a_isValid;
        }


        public void update(CCamera a_camera, float a_delayTime, float a_serverTimer)
        {
            Vector3 dirCamera = a_camera.Direction;
            Vector3 dirFront = new Vector3(dirCamera.X, 0, dirCamera.Z);
            Vector3 dirLeft = new Vector3(dirCamera.Z * -1, 0, dirCamera.X);

            Vector3 dirSpeedFront;
            Vector3 dirSpeedLeft;

            if (m_isMoveFrontValid)
            {
                dirSpeedFront = dirFront;
            }
            else if (m_isMoveBackValid)
            {
                dirSpeedFront = -1 * dirFront;
            }
            else
            {
                dirSpeedFront = new Vector3(0, 0, 0);
            }

            if (m_isMoveLeftValid)
            {
                dirSpeedLeft = dirLeft;
            }
            else if (m_isMoveRightValid)
            {
                dirSpeedLeft = -1 * dirLeft;
            }
            else
            {
                dirSpeedLeft = new Vector3(0, 0, 0);
            }

            m_direction = dirSpeedFront + dirSpeedLeft;
            m_direction.Normalize();

            Vector3 offset = m_direction * m_speed * a_delayTime;

            m_position.Add(offset);

            m_box.setBox(m_position);
        }

        public IRender getRender()
        {
            return m_box;
        }
    }
}
