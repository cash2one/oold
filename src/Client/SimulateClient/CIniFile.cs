using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace SimulateClient
{
    public class CIniFile
    {
        public string path;				//INI文件名

        [DllImport("kernel32")]
        private static extern long WritePrivateProfileString(string section, string key,
                    string val, string filePath);

        [DllImport("kernel32")]
        private static extern int GetPrivateProfileString(string section, string key, string def,
                    StringBuilder retVal, int size, string filePath);

        //声明读写INI文件的API函数
        public CIniFile(string INIPath)
        {
            string file = System.Environment.CurrentDirectory;
            file += INIPath;
            path = file;
        }

        //类的构造函数，传递INI文件名
        public void IniWriteValue(string Section, string Key, string Value)
        {
            WritePrivateProfileString(Section, Key, Value, this.path);
        }

        //写INI文件
        public string IniReadValue(string Section, string Key)
        {
            StringBuilder temp = new StringBuilder(255);
            int i = GetPrivateProfileString(Section, Key, "", temp, 255, this.path);
            return temp.ToString();
        }

        //读取INI文件指定
    }
}
