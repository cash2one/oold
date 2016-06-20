using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SimulateClient
{
    class log
    {
        public static void write(string content)
        {
            UnityUtility.CTrace.Singleton.debug("{0}", content);
        }
    }
}
