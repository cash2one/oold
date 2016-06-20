using System;
using System.IO;
using System.Collections.Generic;

namespace UnityGMClient {
  public partial class ShopSystemItemInfo : UnityFrame.CMsg
  {
    public UInt32 id = 0;
    public UInt32 type = 0;
    public UInt32 item_id = 0;
    public Int32 item_num = 0;
    public UInt32 pay_type = 0;
    public UInt32 pay_num = 0;
    public ShopSystemItemInfo()
        : base(CServerType.NULL, CFuncType.EFUNCTYPE_SHOPSYSTEM, 10){}
    public  bool deserialize(UnityUtility.CStream stream)
    {
      stream.Read(ref id);
      stream.Read(ref type);
      stream.Read(ref item_id);
      stream.Read(ref item_num);
      stream.Read(ref pay_type);
      stream.Read(ref pay_num);
      return true;
    }

    public bool serialize(UnityUtility.CStream stream)
    {
      stream.Write(id);
      stream.Write(type);
      stream.Write(item_id);
      stream.Write(item_num);
      stream.Write(pay_type);
      stream.Write(pay_num);
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

  public partial class ShopSystemAllItemsInfo : UnityFrame.CMsg
  {
    public List<ShopSystemItemInfo> info = new List<ShopSystemItemInfo>();
    public ShopSystemAllItemsInfo()
        : base(CServerType.NULL, CFuncType.EFUNCTYPE_SHOPSYSTEM, 11){}
    public  bool deserialize(UnityUtility.CStream stream)
    {
      {
        UInt32 len = 0; stream.Read(ref len);
        for (int i = 0 ; i < len ; ++i)
        {
          ShopSystemItemInfo element= new ShopSystemItemInfo(); 
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
        foreach (ShopSystemItemInfo i in info)
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

  public partial class CMsgShopSystemGC2GMReqOpenCard : UnityFrame.CMsg
  {
    public UInt32 fun_type = 0;
    public CMsgShopSystemGC2GMReqOpenCard()
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SHOPSYSTEM, 12){}
    public  bool deserialize(UnityUtility.CStream stream)
    {
      stream.Read(ref fun_type);
      return true;
    }

    public bool serialize(UnityUtility.CStream stream)
    {
      stream.Write(fun_type);
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

  public partial class CMsgShopSystemGM2GCAckOpenCard : UnityFrame.CMsg
  {
    public UInt32 fun_type = 0;
    public UInt32 glod1_free = 0;
    public UInt32 gold1_next_cost = 0;
    public UInt32 gold10_next_cost = 0;
    public UInt32 diamond1_free = 0;
    public UInt32 diamond1_next_cost = 0;
    public UInt32 diamond10_next_cost = 0;
    public UInt64 gold1_next_secs = 0;
    public UInt64 diamond1_next_secs = 0;
    public CMsgShopSystemGM2GCAckOpenCard()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SHOPSYSTEM, 13){}
    public  bool deserialize(UnityUtility.CStream stream)
    {
      stream.Read(ref fun_type);
      stream.Read(ref glod1_free);
      stream.Read(ref gold1_next_cost);
      stream.Read(ref gold1_next_secs);
      stream.Read(ref gold10_next_cost);
      stream.Read(ref diamond1_free);
      stream.Read(ref diamond1_next_cost);
      stream.Read(ref diamond1_next_secs);
      stream.Read(ref diamond10_next_cost);
      return true;
    }

    public bool serialize(UnityUtility.CStream stream)
    {
      stream.Write(fun_type);
      stream.Write(glod1_free);
      stream.Write(gold1_next_cost);
      stream.Write(gold1_next_secs);
      stream.Write(gold10_next_cost);
      stream.Write(diamond1_free);
      stream.Write(diamond1_next_cost);
      stream.Write(diamond1_next_secs);
      stream.Write(diamond10_next_cost);
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

  public partial class CMsgShopSystemGC2GMReqEventState : UnityFrame.CMsg
  {
    public CMsgShopSystemGC2GMReqEventState()
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SHOPSYSTEM, 14){}
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

  public partial class CMsgShopSystemGM2GCAckEventState : UnityFrame.CMsg
  {
    public UInt32 update_type = 0;
    public UInt32 triggered = 0;
    public UInt32 item_id = 0;
    public List<UInt32> event_names = new List<UInt32>();
    public CMsgShopSystemGM2GCAckEventState()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SHOPSYSTEM, 15){}
    public  bool deserialize(UnityUtility.CStream stream)
    {
      stream.Read(ref update_type);
      {
        UInt32 len = 0; stream.Read(ref len);
        for (int i = 0 ; i < len ; ++i)
        {
          UInt32 element= 0; 
          stream.Read(ref element);
          event_names.Add(element);
        }
      }
      stream.Read(ref triggered);
      stream.Read(ref item_id);
      return true;
    }

    public bool serialize(UnityUtility.CStream stream)
    {
      stream.Write(update_type);
      {
        UInt32 len = (UInt32)event_names.Count;
        stream.Write(len);
        foreach (UInt32 i in event_names)
        {
          stream.Write(i);
        }
      }
      stream.Write(triggered);
      stream.Write(item_id);
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

  public partial class CMsgShopSystemGC2GMReqClick : UnityFrame.CMsg
  {
    public UInt32 fun_type = 0;
    public UInt32 cost_type = 0;
    public CMsgShopSystemGC2GMReqClick()
        : base(CServerType.SRVTYPE_GAMESERVER, CFuncType.EFUNCTYPE_SHOPSYSTEM, 16){}
    public  bool deserialize(UnityUtility.CStream stream)
    {
      stream.Read(ref fun_type);
      stream.Read(ref cost_type);
      return true;
    }

    public bool serialize(UnityUtility.CStream stream)
    {
      stream.Write(fun_type);
      stream.Write(cost_type);
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

  public partial class CMsgShopSystemGM2GCAckClick : UnityFrame.CMsg
  {
    public UInt32 fun_type = 0;
    public UInt32 cost_type = 0;
    public UInt32 result = 0;
    public List<UInt32> item_ids = new List<UInt32>();
    public List<UInt32> item_nums = new List<UInt32>();
    public CMsgShopSystemGM2GCAckClick()
        : base(CServerType.SRVTYPE_GAMECLIENT, CFuncType.EFUNCTYPE_SHOPSYSTEM, 17){}
    public  bool deserialize(UnityUtility.CStream stream)
    {
      stream.Read(ref fun_type);
      stream.Read(ref cost_type);
      stream.Read(ref result);
      {
        UInt32 len = 0; stream.Read(ref len);
        for (int i = 0 ; i < len ; ++i)
        {
          UInt32 element= 0; 
          stream.Read(ref element);
          item_ids.Add(element);
        }
      }
      {
        UInt32 len = 0; stream.Read(ref len);
        for (int i = 0 ; i < len ; ++i)
        {
          UInt32 element= 0; 
          stream.Read(ref element);
          item_nums.Add(element);
        }
      }
      return true;
    }

    public bool serialize(UnityUtility.CStream stream)
    {
      stream.Write(fun_type);
      stream.Write(cost_type);
      stream.Write(result);
      {
        UInt32 len = (UInt32)item_ids.Count;
        stream.Write(len);
        foreach (UInt32 i in item_ids)
        {
          stream.Write(i);
        }
      }
      {
        UInt32 len = (UInt32)item_nums.Count;
        stream.Write(len);
        foreach (UInt32 i in item_nums)
        {
          stream.Write(i);
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

}

