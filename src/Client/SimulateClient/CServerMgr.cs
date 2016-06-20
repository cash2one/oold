using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GC
{
    public class CServerIP
    {
        public const string IP_OUT_FOR_PUBLIC_TEST = "120.132.70.3";  // 外网测试服
        public const string IP_OUT     = "120.132.60.233";
        public const string IP_IN_2_13 = "192.168.2.13";
        public const string IP_IN_MZJ  = "192.168.1.47";
        public const string IP_IN_ZP   = "192.168.1.92";
        public const string IP_IN_ZM   = "10.0.1.102";
        public const string SERVER_BJ  = "10.0.1.101";
        public const string SERVER_BJ_LINUX = "192.168.2.37";
    }

    public class CServerPort
    {
        public const ushort PORT_OUT        = 9000;
        public const ushort PORT_2_13       = 9000;
        public const ushort PORT_2_13_ZM    = 9009;
        public const ushort PORT_MZJ        = 9000;
        public const ushort PORT_ZP         = 9000;
        public const ushort PORT_ZP_DEBUG   = 9010;
        public const ushort PORT_ZM         = 9000;
        public const ushort PORT_BJ         = 9000;
        public const ushort PORT_TESTSERVER = 7000;
        public const ushort PORT_BJ_LINUX =  9000;
    }

    public class CServerZone
    {
        public const ushort ZONE_OUT        = 30;
        public const ushort ZONE_2_13       = 1;
        public const ushort ZONE_2_13_ZM    = 11;
        public const ushort ZONE_MZJ        = 20;
        public const ushort ZONE_ZP         = 21;
        public const ushort ZONE_ZP_DEBUG   = 11;
        public const ushort ZONE_ZM         = 22;
        public const ushort ZONE_BJ         = 23;
        public const ushort ZONE_TESTSERVER = 2;
        public const ushort ZONE_BJ_LINUX = 1;
    }

    public class CServerName
    {
        public const string SERVER_OUT        = "外网正式服";
        public const string SERVER_2_13       = "公共测试服";
        public const string SERVER_2_13_ZM    = "公共测试服_zm";
        public const string SERVER_MZJ        = "dev_mzj";
        public const string SERVER_ZP         = "dev_zp";
        public const string SERVER_ZP_DEBUG   = "dev_zp_debug";
        public const string SERVER_ZM         = "dev_zm";
        public const string SERVER_BJ         = "dev_bj";
        public const string SERVER_TESTSERVER = "dev_test";
        public const string SERVER_BJ_LINUX = "dev_bj_linux";
    }

    public class CServerdata
    {
        public string m_serverIP = CServerIP.IP_IN_2_13;
        public ushort m_serverPort = CServerPort.PORT_2_13;
        public ushort m_zoneID = CServerZone.ZONE_2_13;
    }

    public class CServerMgr : UnityUtility.CSingleton<CServerMgr>
    {
        private CServerdata m_server = new CServerdata(); 
        public CServerdata getServer(string serverName)
        {
            switch (serverName)
            {
                case CServerName.SERVER_OUT:
                    {
                        m_server.m_serverPort = CServerPort.PORT_OUT;
                        m_server.m_zoneID = CServerZone.ZONE_OUT;
                        m_server.m_serverIP = CServerIP.IP_OUT;
                      
                    }
                    break;
                case CServerName.SERVER_2_13:
                    {
                        m_server.m_serverPort = CServerPort.PORT_2_13;
                        m_server.m_zoneID = CServerZone.ZONE_2_13;
                        m_server.m_serverIP = CServerIP.IP_IN_2_13;
                    }

                    break;
                case CServerName.SERVER_2_13_ZM:
                    {
                        m_server.m_serverPort = CServerPort.PORT_2_13_ZM;
                        m_server.m_zoneID = CServerZone.ZONE_2_13_ZM;
                        m_server.m_serverIP = CServerIP.IP_IN_2_13;
                    }
                    break;
                case CServerName.SERVER_MZJ:
                    {
                        m_server.m_serverPort = CServerPort.PORT_MZJ;
                        m_server.m_zoneID = CServerZone.ZONE_MZJ;
                        m_server.m_serverIP = CServerIP.IP_IN_MZJ;
                    }
                    break;
                case CServerName.SERVER_ZP:
                    {
                        m_server.m_serverPort = CServerPort.PORT_ZP;
                        m_server.m_zoneID = CServerZone.ZONE_ZP;
                        m_server.m_serverIP = CServerIP.IP_IN_ZP;
                    }
                    break;
                case CServerName.SERVER_ZP_DEBUG:
                    {
                        m_server.m_serverPort = CServerPort.PORT_ZP_DEBUG;
                        m_server.m_zoneID = CServerZone.ZONE_ZP_DEBUG;
                        m_server.m_serverIP = CServerIP.IP_IN_ZP;
                    }
                    break;
                case CServerName.SERVER_ZM:
                    {
                        m_server.m_serverPort = CServerPort.PORT_ZM;
                        m_server.m_zoneID = CServerZone.ZONE_ZM;
                        m_server.m_serverIP = CServerIP.IP_IN_ZM;
                    }
                    break;
                case CServerName.SERVER_BJ:
                    {
                        m_server.m_serverPort = CServerPort.PORT_BJ;
                        m_server.m_zoneID = CServerZone.ZONE_BJ;
                        m_server.m_serverIP = CServerIP.SERVER_BJ;
                    }
                    break;
                case CServerName.SERVER_TESTSERVER:
                    {
                        m_server.m_serverPort = CServerPort.PORT_TESTSERVER;
                        m_server.m_zoneID = CServerZone.ZONE_TESTSERVER;
                        m_server.m_serverIP = CServerIP.IP_IN_2_13;
                    }
                    break;
                case CServerName.SERVER_BJ_LINUX:
                    {
                        m_server.m_serverPort = CServerPort.PORT_BJ_LINUX;
                        m_server.m_zoneID = CServerZone.ZONE_BJ_LINUX;
                        m_server.m_serverIP = CServerIP.SERVER_BJ_LINUX;
                    }
                    break;
                default:

                    break;
//                     string lg = "zoneID =" + m_server.m_zoneID + " serverIP=" + m_server.m_serverIP;
//                     Log(lg);
            }
            return m_server;
        }
             
    }
} 