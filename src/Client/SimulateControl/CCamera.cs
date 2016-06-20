using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace SimulateControl
{
    public class CCamera
    {
        private float m_width = 200;
        private float m_height = 100;
        private float m_nearPlane = 1;
        private float m_farPlane = 1000;

        private Vector3 m_cameraPostion = new Vector3(0, 0, -100);
        private Vector3 m_cameraTarget = new Vector3(0, 0, 0);
        private Vector3 m_cameraUp = new Vector3(0, 1, 0);

        private Matrix m_projectionMatrix;
        private Matrix m_viewMatrix;
        private Device m_device = null;

        public CCamera(Device a_device)
        {
            m_device = a_device;
            _updateProjection();
            _updateView();
            
        }

        private void _updateProjection()
        {
            m_projectionMatrix = Matrix.PerspectiveFovLH((float)Math.PI / 4, m_width / m_height, m_nearPlane, m_farPlane);
        }

        private void _updateView()
        {
            m_viewMatrix = Matrix.LookAtLH(m_cameraPostion, m_cameraTarget, m_cameraUp);
        }

        public void update()
        {
            if (m_device == null)
            {
                return ;
            }
            m_device.Transform.Projection = m_projectionMatrix;
            m_device.Transform.View = m_viewMatrix;
        }

        public Device getDevice()
        {
            return m_device;
        }

        public float Width
        {
            get
            {
                return m_width;
            }
            set
            {
                m_width = value;
                _updateProjection();
            }
        }

        public float Height
        {
            get
            {
                return m_height;
            }
            set
            {
                m_height = value;
                _updateProjection();
            }
        }

        public float NearPlane
        {
            get
            {
                return m_nearPlane;
            }
            set
            {
                m_nearPlane = value;
                _updateProjection();
            }
        }

        public float FarPlane
        {
            get
            {
                return m_farPlane;
            }
            set
            {
                m_farPlane = value;
                _updateProjection();
            }
        }

        public Vector3 CameraPostion
        {
            get
            {
                return m_cameraPostion;
            }
            set
            {
                m_cameraPostion = value;
                _updateView();
            }
        }

        public Vector3 CameraTarget
        {
            get
            {
                return m_cameraTarget;
            }
            set
            {
                m_cameraTarget = value;
                _updateView();
            }
        }

        public Vector3 Direction
        {
            get
            {
                Vector3 dir = m_cameraTarget - m_cameraPostion;
                dir.Normalize();
                return dir;
            }
        }

        public Vector3 CameraUp
        {
            get
            {
                return m_cameraUp;
            }
            set
            {
                m_cameraUp = value;
                _updateView();
            }
        }

        public void setPerspective(float a_width, float a_height, float a_nearPlane, float a_farPlane)
        {
            m_width = a_width;
            m_height = a_height;
            m_nearPlane = a_nearPlane;
            m_farPlane = a_farPlane;
            _updateProjection();
        }

        public void setCamera(Vector3 a_cameraPostion, Vector3 a_cameraTarget)
        {
            m_cameraPostion = a_cameraPostion;
            m_cameraTarget = a_cameraTarget;
            _updateView();
        }

        public void setCamera(Vector3 a_cameraPostion, Vector3 a_cameraTarget, Vector3 a_cameraUp)
        {
            m_cameraPostion = a_cameraPostion;
            m_cameraTarget = a_cameraTarget;
            m_cameraUp = a_cameraUp;
            _updateView();
        }

        public void setCameraPosition(Vector3 a_cameraPostion)
        {
            m_cameraPostion = a_cameraPostion;
            _updateView();
        }

        public void setCameraPosition(float a_x, float a_y, float a_z)
        {
            m_cameraPostion.X = a_x;
            m_cameraPostion.Y = a_y;
            m_cameraPostion.Z = a_z;
            _updateView();
        }

        public void setCameraTarget(Vector3 a_cameraTarget)
        {
            m_cameraTarget = a_cameraTarget;
            _updateView();
        }

        public void setCameraTarget(float a_x, float a_y, float a_z)
        {
            m_cameraTarget.X = a_x;
            m_cameraTarget.Y = a_y;
            m_cameraTarget.Z = a_z;
            _updateView();
        }

        public void forwardScale(float a_scale)
        {
            m_cameraPostion.Subtract(m_cameraTarget);
            m_cameraPostion.Scale(a_scale);
            m_cameraPostion.Add(m_cameraTarget);

            _updateView();
        }

        public void rotationY(float a_angle)
        {
            Matrix currentView = m_viewMatrix;

            m_cameraPostion.Subtract(m_cameraTarget);
            Vector4 tempV4 = Vector3.Transform(m_cameraPostion, Matrix.RotationQuaternion(Quaternion.RotationAxis(new Vector3(currentView.M12, currentView.M22, currentView.M32), a_angle)));
            m_cameraPostion.X = tempV4.X + m_cameraTarget.X;
            m_cameraPostion.Y = tempV4.Y + m_cameraTarget.Y;
            m_cameraPostion.Z = tempV4.Z + m_cameraTarget.Z;

            _updateView();
        }

        public void rotationX(float a_angle)
        {
            Matrix currentView = m_viewMatrix;
 
            float oldZ = m_cameraPostion.Z;

            m_cameraPostion.Subtract(m_cameraTarget);
            Vector4 tempV4 = Vector3.Transform(m_cameraPostion, Matrix.RotationQuaternion(Quaternion.RotationAxis(new Vector3(currentView.M11, currentView.M21, currentView.M31), a_angle)));

            m_cameraPostion.X = tempV4.X + m_cameraTarget.X;
            m_cameraPostion.Y = tempV4.Y + m_cameraTarget.Y;
            m_cameraPostion.Z = tempV4.Z + m_cameraTarget.Z;

            if ((oldZ >= 0 && m_cameraPostion.Z < 0) || oldZ < 0 && m_cameraPostion.Z >= 0)
            {
                m_cameraUp.X *= -1;
                m_cameraUp.Y *= -1;
                m_cameraUp.Z *= -1;
            }
          
            _updateView();
        }

    }
}
