using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public class CMail
    {

        public UInt64 mail_id;
        public UInt32 mail_type;
        public UInt64 system_mail;
        public UInt32 is_read;
        public UInt32 is_get;
        public UInt64 time_stamp;

        public string title;
        public string content;
        public string sender;
        public List<UInt32> ids = new List<UInt32>();
        public List<UInt32> nums =  new List<UInt32>();
    }
}
