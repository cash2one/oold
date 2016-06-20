using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public partial class CClientCore : UnityUtility.CSingletonBase<CClientCore>
    {
        public void Init()
        {
            UnityGMClient.CGameClient.Singleton.Init();
        }

        public void Update(float delayTimer)
        {
            UnityGMClient.CGameClient.Singleton.Update(delayTimer);
        }

        public void Final()
        {
            UnityGMClient.CGameClient.Singleton.Final();
        }
    }
}
