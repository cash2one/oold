using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using System.Drawing;

namespace SimulateControl
{
    public interface IRender
    {
        Vector3[] getPositions();
        Int32[] getIndexs();
        Color getColor();

        Vector3 getCenter();

    }
}
