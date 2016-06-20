using System;
using System.Collections;
using System.Reflection;

namespace UnityGMClient
{
    class CMsgFactory : UnityFrame.CMsgFactory
    {
        public override UnityFrame.CMsg CreateMessageByTypeName(string typeName)
        {
            try
            {
                Assembly asm = Assembly.GetExecutingAssembly();
                Object obj = asm.CreateInstance(typeName, true);
                return (UnityFrame.CMsg)obj;
            }
            catch (System.Exception)
            {
                return null;
            }
        }

        public override UnityFrame.CMsgID CreateMsgIDByType(Type type)
        {
            try
            {
                Assembly asm = Assembly.GetExecutingAssembly();
                Object obj = asm.CreateInstance(type.FullName, true);
                if (obj != null)
                {
                    UnityFrame.CMsg msg = (UnityFrame.CMsg)obj;
                    if (msg != null)
                    {
                        return msg.MsgID;
                    }
                }
                return null;
            }
            catch (System.Exception)
            {
                return null;
            }
        }
    }
}
