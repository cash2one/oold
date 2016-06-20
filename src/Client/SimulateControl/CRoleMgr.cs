using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;

namespace SimulateControl
{
    public class CRoleMgr
    {
        private Hashtable m_hashtable = new Hashtable();

        public void update(CCamera a_camera, float a_delayTime, float a_serverTimer)
        {
            foreach (DictionaryEntry keyValuePair in m_hashtable)
            {
                IRole item = (IRole)keyValuePair.Value;
                item.update(a_camera, a_delayTime, a_serverTimer);
            }
        }

        public void addRole(IRole a_role)
        {
            m_hashtable.Add(a_role.GetHashCode(), a_role);
        }

        public void delRole(IRole a_role)
        {
            m_hashtable.Remove(a_role.GetHashCode());
        }
    }
}
