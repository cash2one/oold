using System;
using System.Collections.Generic;
using System.Text;

namespace UnityFrame
{
    public class CSysConfig
    {
        private Dictionary<string, string> m_sysConfig = new Dictionary<string,string>();

        public void ParseMainArgs(string[] a_mainArgs)
        {
            string key;
            string val;
            int paraNum = 0;

            for (int i = 0; i < a_mainArgs.Length; ++i)
            {
                key = "";
                val = "";
                if (a_mainArgs[i][0] == '-')
                {
                    if (a_mainArgs[i].Length <= 1)
                    {
                        continue;
                    }
                    if (a_mainArgs[i][1] == '-')
                    {
                        if (a_mainArgs[i].Length <= 2)
                        {
                            continue;
                        }
                        key = a_mainArgs[i].Substring(2);
                        SetKeyStrValue(key, key);
                        continue;
                    }
                    key = a_mainArgs[i].Substring(1);
                    if (i + 1 < a_mainArgs.Length)
                    {
                        val = a_mainArgs[i + 1];
                        ++i;
                    }
                    SetKeyStrValue(key, val);
                    continue;
                }

                key = paraNum.ToString();
                val = a_mainArgs[i];
                SetKeyStrValue(key, val);
                ++paraNum;
            }
        }

        public string GetValueStr(string key)
        {
            string lowerKey = key.ToLower();

            string val;
            m_sysConfig.TryGetValue(lowerKey, out val);
            return val;
        }

        public int GetValueInt(string key)
        {
            string lowerKey = key.ToLower();

            string val;
            if (!m_sysConfig.TryGetValue(lowerKey, out val))
            {
                return 0;
            }
            try
            {
                return Int32.Parse(val);
            }
            catch (System.Exception)
            {
                return 0;
            }
        }

        public void ShowAll()
        {
            foreach (KeyValuePair<string, string> pair in m_sysConfig)
            {
                Console.WriteLine("{0}:{1}", pair.Key, pair.Value);
            }
        }

        public void SetKeyStrValue(string key, string val)
        {
            string lowerKey = key.ToLower();
            if (m_sysConfig.ContainsKey(lowerKey))
            {
                m_sysConfig.Remove(lowerKey);
            }
            m_sysConfig.Add(lowerKey, val);
        }

        public void SetKeyIntValue(string key, int val)
        {
            string lowerKey = key.ToLower();
            if (m_sysConfig.ContainsKey(lowerKey))
            {
                m_sysConfig.Remove(lowerKey);
            }
            m_sysConfig.Add(lowerKey, val.ToString());
        }
    }
}
