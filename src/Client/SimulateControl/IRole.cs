using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SimulateControl
{
    public interface IRole
    {
        void update(CCamera a_camera, float a_delayTime, float a_serverTimer);
        IRender getRender();
    }
}
