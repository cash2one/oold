using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Management;

namespace GC 
{
    public class CHelper
    {
        public static void showMsg(string title, string msg)
        {
            System.Windows.Forms.MessageBox.Show(msg, title, System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Information);
        }

        public static void showMsg(string msg)
        {
            showMsg("",msg);
        }

        public static string getStringTime(long a_seconds)
        {
            DateTime startTime = new DateTime(1970, 1, 1,8,0,0);
            long lTime = long.Parse(a_seconds + "0000000");
            TimeSpan toNow = new TimeSpan(lTime);
            DateTime dtResult = startTime.Add(toNow);
            return dtResult.ToString("[yyyy-MM-dd HH:mm:ss]");
        }

        public static string getUniqueID()
        {
           return GetMoAddress();
        }

        ///<summary>
        ///   获取cpu序列号
        ///</summary>
        ///<returns> string </returns>
        public static string GetCpuInfo()
        {
            string cpuInfo = " ";
            using (ManagementClass cimobject = new ManagementClass("Win32_Processor"))
            {
                ManagementObjectCollection moc = cimobject.GetInstances();

                foreach (ManagementObject mo in moc)
                {
                    cpuInfo = mo.Properties["ProcessorId"].Value.ToString();
                    mo.Dispose();
                }
            }
            return cpuInfo.ToString();
        }

        ///<summary>
        ///   获取硬盘ID
        ///</summary>
        ///<returns> string </returns>
        public static string GetHDid()
        {
            string HDid = " ";
            using (ManagementClass cimobject1 = new ManagementClass("Win32_DiskDrive"))
            {
                ManagementObjectCollection moc1 = cimobject1.GetInstances();
                foreach (ManagementObject mo in moc1)
                {
                    HDid = (string)mo.Properties["Model"].Value;
                    mo.Dispose();
                }
            }
            return HDid.ToString();
        }

        ///<summary>
        ///   获取网卡硬件地址
        ///</summary>
        ///<returns> string </returns>
        public static string GetMoAddress()
        {
            string MoAddress = " ";
            using (ManagementClass mc = new ManagementClass("Win32_NetworkAdapterConfiguration"))
            {
                ManagementObjectCollection moc2 = mc.GetInstances();
                foreach (ManagementObject mo in moc2)
                {
                    if ((bool)mo["IPEnabled"] == true)
                        MoAddress = mo["MacAddress"].ToString();
                    mo.Dispose();
                }
            }
            return MoAddress.ToString();
        }


        public static string randString(int length)
        {
            string str = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";//~!@#$%^&*()_+";//75个字符
            Random r = new Random();
            string result = string.Empty;

            //生成一个8位长的随机字符，具体长度可以自己更改
            for (int i = 0; i < length; i++)
            {
                int m = r.Next(0, str.Length);
                string s = str.Substring(m, 1);
                result += s;
            }

            return result;
        }
    }
}
