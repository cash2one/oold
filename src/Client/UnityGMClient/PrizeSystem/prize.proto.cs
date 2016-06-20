using System;
using System.IO;
using System.Collections.Generic;

namespace UnityGMClient {
  public partial class CMsgPrizeSystemGC2GMReqState : UnityFrame.CMsg
  {
    public CMsgPrizeSystemGC2GMReqState()
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PRIZESYSTEM, 0){}
    public  bool deserialize(UnityUtility.CStream stream)
    {
      return true;
    }

    public bool serialize(UnityUtility.CStream stream)
    {
      return true;
    }

    protected override bool _SerializeFrom(UnityUtility.CStream stream)
    {
      return deserialize(stream);
    }

    protected override bool _SerializeTo(UnityUtility.CStream stream)
    {
      return serialize(stream);
    }

  }

  public partial class CMsgPrizeSystemGM2GCAckState : UnityFrame.CMsg
  {
    public Dictionary<UInt32,Int32> states = new Dictionary<UInt32,Int32>();
    public CMsgPrizeSystemGM2GCAckState()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PRIZESYSTEM, 1){}
    public  bool deserialize(UnityUtility.CStream stream)
    {
      {
        UInt32 len = 0; stream.Read(ref len);
        for (int i = 0 ; i < len ; ++i)
        {
          UInt32 first_element= 0; 
          Int32 second_element= 0; 
          stream.Read(ref first_element);
          stream.Read(ref second_element);
          states.Add(first_element,second_element);
        }
      }
      return true;
    }

    public bool serialize(UnityUtility.CStream stream)
    {
      {
        UInt32 len = (UInt32)states.Count;
        stream.Write(len);
        foreach (var i in states)
        {
          stream.Write(i.Key);
          stream.Write(i.Value);
        }
      }
      return true;
    }

    protected override bool _SerializeFrom(UnityUtility.CStream stream)
    {
      return deserialize(stream);
    }

    protected override bool _SerializeTo(UnityUtility.CStream stream)
    {
      return serialize(stream);
    }

  }

  public partial class CMsgPrizeSystemGC2GMReq : UnityFrame.CMsg
  {
    public UInt32 vip = 0;
    public CMsgPrizeSystemGC2GMReq()
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PRIZESYSTEM, 2){}
    public  bool deserialize(UnityUtility.CStream stream)
    {
      stream.Read(ref vip);
      return true;
    }

    public bool serialize(UnityUtility.CStream stream)
    {
      stream.Write(vip);
      return true;
    }

    protected override bool _SerializeFrom(UnityUtility.CStream stream)
    {
      return deserialize(stream);
    }

    protected override bool _SerializeTo(UnityUtility.CStream stream)
    {
      return serialize(stream);
    }

  }

  public partial class CMsgPrizeSystemGM2GCAck : UnityFrame.CMsg
  {
    public UInt32 vip = 0;
    public UInt32 result = 0;
    public CMsgPrizeSystemGM2GCAck()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PRIZESYSTEM, 3){}
    public  bool deserialize(UnityUtility.CStream stream)
    {
      stream.Read(ref vip);
      stream.Read(ref result);
      return true;
    }

    public bool serialize(UnityUtility.CStream stream)
    {
      stream.Write(vip);
      stream.Write(result);
      return true;
    }

    protected override bool _SerializeFrom(UnityUtility.CStream stream)
    {
      return deserialize(stream);
    }

    protected override bool _SerializeTo(UnityUtility.CStream stream)
    {
      return serialize(stream);
    }

  }

  public partial class CMsgPrizeSystemGM2GCNtfCharge : UnityFrame.CMsg
  {
    public UInt32 id = 0;
    public Int64 time = 0;
    public CMsgPrizeSystemGM2GCNtfCharge()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PRIZESYSTEM, 4){}
    public  bool deserialize(UnityUtility.CStream stream)
    {
      stream.Read(ref id);
      stream.Read(ref time);
      return true;
    }

    public bool serialize(UnityUtility.CStream stream)
    {
      stream.Write(id);
      stream.Write(time);
      return true;
    }

    protected override bool _SerializeFrom(UnityUtility.CStream stream)
    {
      return deserialize(stream);
    }

    protected override bool _SerializeTo(UnityUtility.CStream stream)
    {
      return serialize(stream);
    }

  }

  public partial class CMsgPrizeSystemGC2GMReqTime : UnityFrame.CMsg
  {
    public CMsgPrizeSystemGC2GMReqTime()
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PRIZESYSTEM, 5){}
    public  bool deserialize(UnityUtility.CStream stream)
    {
      return true;
    }

    public bool serialize(UnityUtility.CStream stream)
    {
      return true;
    }

    protected override bool _SerializeFrom(UnityUtility.CStream stream)
    {
      return deserialize(stream);
    }

    protected override bool _SerializeTo(UnityUtility.CStream stream)
    {
      return serialize(stream);
    }

  }

  public partial class CMsgPrizeSystemGM2GCAckTime : UnityFrame.CMsg
  {
    public Int64 time = 0;
    public CMsgPrizeSystemGM2GCAckTime()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PRIZESYSTEM, 6){}
    public  bool deserialize(UnityUtility.CStream stream)
    {
      stream.Read(ref time);
      return true;
    }

    public bool serialize(UnityUtility.CStream stream)
    {
      stream.Write(time);
      return true;
    }

    protected override bool _SerializeFrom(UnityUtility.CStream stream)
    {
      return deserialize(stream);
    }

    protected override bool _SerializeTo(UnityUtility.CStream stream)
    {
      return serialize(stream);
    }

  }

  public partial class CMsgPrizeSystemGC2GMReqChargeInfo : UnityFrame.CMsg
  {
    public UInt32 id = 0;
    public CMsgPrizeSystemGC2GMReqChargeInfo()
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PRIZESYSTEM, 7){}
    public  bool deserialize(UnityUtility.CStream stream)
    {
      stream.Read(ref id);
      return true;
    }

    public bool serialize(UnityUtility.CStream stream)
    {
      stream.Write(id);
      return true;
    }

    protected override bool _SerializeFrom(UnityUtility.CStream stream)
    {
      return deserialize(stream);
    }

    protected override bool _SerializeTo(UnityUtility.CStream stream)
    {
      return serialize(stream);
    }

  }

  public partial class PrizeSystemState : UnityFrame.CMsg
  {
    public Int32 type = 0;
    public Int32 key = 0;
    public Int32 value = 0;
    public PrizeSystemState()
        : base(CServerType.NULL, CFuncType.EFUNCTYPE_PRIZESYSTEM, 8){}
    public  bool deserialize(UnityUtility.CStream stream)
    {
      stream.Read(ref type);
      stream.Read(ref key);
      stream.Read(ref value);
      return true;
    }

    public bool serialize(UnityUtility.CStream stream)
    {
      stream.Write(type);
      stream.Write(key);
      stream.Write(value);
      return true;
    }

    protected override bool _SerializeFrom(UnityUtility.CStream stream)
    {
      return deserialize(stream);
    }

    protected override bool _SerializeTo(UnityUtility.CStream stream)
    {
      return serialize(stream);
    }

  }

  public partial class PrizeSystemChargeInfo : UnityFrame.CMsg
  {
    public UInt32 id = 0;
    public Int64 start_time = 0;
    public Int64 end_time = 0;
    public List<PrizeSystemState> states = new List<PrizeSystemState>();
    public PrizeSystemChargeInfo()
        : base(CServerType.NULL, CFuncType.EFUNCTYPE_PRIZESYSTEM, 9){}
    public  bool deserialize(UnityUtility.CStream stream)
    {
      stream.Read(ref id);
      stream.Read(ref start_time);
      stream.Read(ref end_time);
      {
        UInt32 len = 0; stream.Read(ref len);
        for (int i = 0 ; i < len ; ++i)
        {
          PrizeSystemState element= new PrizeSystemState(); 
          element.deserialize(stream);
          states.Add(element);
        }
      }
      return true;
    }

    public bool serialize(UnityUtility.CStream stream)
    {
      stream.Write(id);
      stream.Write(start_time);
      stream.Write(end_time);
      {
        UInt32 len = (UInt32)states.Count;
        stream.Write(len);
        foreach (PrizeSystemState i in states)
        {
          i.serialize(stream);
        }
      }
      return true;
    }

    protected override bool _SerializeFrom(UnityUtility.CStream stream)
    {
      return deserialize(stream);
    }

    protected override bool _SerializeTo(UnityUtility.CStream stream)
    {
      return serialize(stream);
    }

  }

  public partial class CMsgPrizeSystemGM2GCAckChargeInfo : UnityFrame.CMsg
  {
    public List<PrizeSystemChargeInfo> info = new List<PrizeSystemChargeInfo>();
    public CMsgPrizeSystemGM2GCAckChargeInfo()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_PRIZESYSTEM, 10){}
    public  bool deserialize(UnityUtility.CStream stream)
    {
      {
        UInt32 len = 0; stream.Read(ref len);
        for (int i = 0 ; i < len ; ++i)
        {
          PrizeSystemChargeInfo element= new PrizeSystemChargeInfo(); 
          element.deserialize(stream);
          info.Add(element);
        }
      }
      return true;
    }

    public bool serialize(UnityUtility.CStream stream)
    {
      {
        UInt32 len = (UInt32)info.Count;
        stream.Write(len);
        foreach (PrizeSystemChargeInfo i in info)
        {
          i.serialize(stream);
        }
      }
      return true;
    }

    protected override bool _SerializeFrom(UnityUtility.CStream stream)
    {
      return deserialize(stream);
    }

    protected override bool _SerializeTo(UnityUtility.CStream stream)
    {
      return serialize(stream);
    }

  }

  public partial class CMsgPrizeSystemGC2GMNtfAction : UnityFrame.CMsg
  {
    public UInt32 id = 0;
    public CMsgPrizeSystemGC2GMNtfAction()
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_PRIZESYSTEM, 11){}
    public  bool deserialize(UnityUtility.CStream stream)
    {
      stream.Read(ref id);
      return true;
    }

    public bool serialize(UnityUtility.CStream stream)
    {
      stream.Write(id);
      return true;
    }

    protected override bool _SerializeFrom(UnityUtility.CStream stream)
    {
      return deserialize(stream);
    }

    protected override bool _SerializeTo(UnityUtility.CStream stream)
    {
      return serialize(stream);
    }

  }

}

