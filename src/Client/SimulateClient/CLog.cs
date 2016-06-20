using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GC 
{
    class CLog
    {
        public static void write(string content)
        {
            UnityUtility.CTrace.Singleton.debug("{0}", content);
        }
    }
}
