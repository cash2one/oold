using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace SimulateControl
{
    public partial class Control3DScene : UserControl
    {
        private Device m_device = null;
        private CCamera m_camera = null;
        private CPlane m_plane = null;
        private CRender m_render = null;

        private CRoleMgr m_roleMgr = null;


        public Control3DScene()
        {
            InitializeComponent();

            if (!initDirect3D())
            {
                return;
            }
        }

        public bool initDirect3D()
        {
            try
            {
                PresentParameters presentParameter = new PresentParameters();
                presentParameter.Windowed = true;
                presentParameter.SwapEffect = SwapEffect.Discard;
                presentParameter.AutoDepthStencilFormat = DepthFormat.D16;
                presentParameter.PresentationInterval = PresentInterval.Immediate;
                presentParameter.EnableAutoDepthStencil = true;
                m_device = new Device(0, DeviceType.Hardware, this, CreateFlags.SoftwareVertexProcessing, presentParameter);

                m_camera = new CCamera(m_device);
                m_camera.Width = this.Width;
                m_camera.Height = this.Height;

                m_render = new CRender(m_camera);

                m_plane = new CPlane();
                m_plane.setPlane(new Vector3(0, 0, 0), 200, 200);

                m_camera.CameraTarget = new Vector3(0, 0, 0);
                m_camera.CameraPostion = new Vector3(100, 100, 100);

                m_roleMgr = new CRoleMgr();
            }
            catch (Exception)
            {
                return false;
            }

            return true;
        }

        public void addPlayer(IRole a_role)
        {
            IRender render = a_role.getRender();
            if (render == null) 
            {
                return ;
            }
            m_render.addRender(render);
            m_roleMgr.addRole(a_role);
        }

        public void delPlayer(IRole a_role)
        {
            IRender render = a_role.getRender();
            if (render == null)
            {
                return;
            }
            m_render.delRender(render);
            m_roleMgr.delRole(a_role);
        }

        public void update(float a_delayTime, float a_serverTimer)
        {
            m_roleMgr.update(m_camera, a_delayTime, a_serverTimer);

            _render();
        }

        private void _render()
        {
            CustomVertex.PositionColored[] vectors = new CustomVertex.PositionColored[6]; 
            vectors[0].Position = new Vector3(0, -1, 0);
            vectors[0].Color = Color.Green.ToArgb();
            vectors[1].Position = new Vector3(0, 40, 0);
            vectors[1].Color = Color.Green.ToArgb();
            vectors[2].Position = new Vector3(-1, 0, 0);
            vectors[2].Color = Color.Red.ToArgb();
            vectors[3].Position = new Vector3(40, 0, 0);
            vectors[3].Color = Color.Red.ToArgb();
            vectors[4].Position = new Vector3(0, 0, -1);
            vectors[4].Color = Color.Blue.ToArgb();
            vectors[5].Position = new Vector3(0, 0, 40);
            vectors[5].Color = Color.Blue.ToArgb();

            if (m_device == null)
            {
                return;
            }
            if (m_camera != null)
            {
                m_camera.update();
            }

            m_device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.Black, 1000.0f, 0);
     
            m_device.RenderState.Lighting = false;

            m_device.BeginScene();
          
            m_plane.render(m_device);
 
            m_render.update();

            m_device.VertexFormat = CustomVertex.PositionColored.Format;
            m_device.DrawUserPrimitives(PrimitiveType.LineList, 3, vectors);

            m_device.EndScene();

            m_device.Present();
        }

        private void Control3DScene_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Control)
            {
                switch (e.KeyCode)
                {
                    case Keys.W:
                        {
                            m_camera.rotationX(0.01f);
                            break;
                        }
                    case Keys.S:
                        {
                            m_camera.rotationX(-0.01f);
                            break;
                        }
                    case Keys.A:
                        {
                            m_camera.rotationY(0.01f);
                            break;
                        }
                    case Keys.D:
                        {
                            m_camera.rotationY(-0.01f);
                            break;
                        }
                    case Keys.Q:
                        {
                            m_camera.forwardScale(0.95f);
                            break;
                        }
                    case Keys.E:
                        {
                            m_camera.forwardScale(1.05f);
                            break;
                        }
                }
            }
        }
    }

}
