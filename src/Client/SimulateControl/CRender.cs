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
    enum ERenderType
    {
        ERENDERTYPE_POSTIONCOLORED = 1,
    }

    class RandomColor
    {
        public static Color nextColor()
        {
            return Color.FromArgb(m_random.Next(0, 255 * 255 * 255));
        }

        private static Random m_random = new Random((int)DateTime.Now.Ticks);
    }

    class CRender
    {
        private class CRenderItem
        {
            public IRender m_reader = null;
            public CustomVertex.PositionColored[] m_vectors = null;
        }

        private Device m_device = null;
        private CCamera m_camera = null;

        private Hashtable m_hashtable = new Hashtable();

        private ERenderType m_readerType = ERenderType.ERENDERTYPE_POSTIONCOLORED;

        public CRender(CCamera a_camera)
        {
            m_device = a_camera.getDevice();
            m_camera = a_camera;
        }

        public void addRender(IRender a_render)
        {
            CRenderItem item = new CRenderItem();
            item.m_reader = a_render;

            m_hashtable.Add(item.m_reader.GetHashCode(), item);
        }

        public void delRender(IRender a_render)
        {
            m_hashtable.Remove(a_render.GetHashCode());
        }

        public void update()
        {
            switch (m_readerType)
            {
                case ERenderType.ERENDERTYPE_POSTIONCOLORED:
                    {
                        _updatePostionColored();
                        break;
                    }
            }
        }

        public void _updatePostionColored()
        {
            m_device.VertexFormat = CustomVertex.PositionColored.Format;

            foreach (DictionaryEntry keyValuePair in m_hashtable)
            {
                CRenderItem item = (CRenderItem)keyValuePair.Value;

                IRender render = item.m_reader;
                if (render == null)
                {
                    continue;
                }
                Vector3[] positionList = render.getPositions();
                Int32[] postionIndex = render.getIndexs();

                int countPosition = positionList.Length;
                int countIndex = postionIndex.Length;

                if (item.m_vectors == null || item.m_vectors.Length < countPosition)
                {
                    item.m_vectors = new CustomVertex.PositionColored[countPosition];
                }

                for (int j = 0; j < positionList.Length; ++j)
                {
                    item.m_vectors[j].Position = positionList[j];
                    item.m_vectors[j].Color = render.getColor().ToArgb();
                }

                try
                {
                    m_device.DrawIndexedUserPrimitives(PrimitiveType.TriangleList, 0, countIndex, countIndex / 3, postionIndex, false, item.m_vectors);

                }
                catch (Exception e)
                {
                    UnityUtility.CTrace.Singleton.error("DrawIndexedUserPrimitives:{0}", e.Message);
                }

            }
        }
    }
}
