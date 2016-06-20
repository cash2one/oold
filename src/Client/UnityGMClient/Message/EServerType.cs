using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    class CServerType
    {
        public const uint NULL = 0;           //无效
        public const uint LOCAL = 1;          //简称'LC'
        public const uint ANY = 2;            //简称'XX'
        public const uint ANYSERVER = 3;      //简称'XS'

        public const uint SRVTYPE_GAMECLIENT = 8;       //简称'GC'
        public const uint SRVTYPE_GATESERVER = 9;       //简称'GT'
        public const uint SRVTYPE_GAMESERVER = 10;      //简称'GM'
        public const uint SRVTYPE_CENTERSERVER = 11;    //简称'CN'
        public const uint SRVTYPE_LOGINSERVER = 12;     //简称'LG'
        public const uint SRVTYPE_DATASERVER = 13;      //简称'DB'
    }
}

