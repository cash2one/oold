using System;

namespace UnityUtility
{
    public class CSingleton<TYPE>
    {
        public static TYPE Singleton
        {
            get
            {
                if (m_singletion == null)
                {
                    lock (m_lockObject)
                    {
                        if (m_singletion == null)
                        {
                            m_singletion = (TYPE)System.Activator.CreateInstance(typeof(TYPE), true);
                        }
                    }
                }
                return m_singletion;
            }
        }

        private static TYPE m_singletion = default(TYPE);
        private static object m_lockObject = new object();
    }

    public class CSingletonBase<TYPE>
    {
        public static TYPE Singleton
        {
            get
            {
                return m_singletion;
            }
            set
            {
                m_singletion = value;
            }
        }

        private static TYPE m_singletion = default(TYPE);
    }
}

