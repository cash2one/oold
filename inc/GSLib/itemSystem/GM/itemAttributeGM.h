#ifndef __GSLIB_ITEMSYSTEM_GM_ITEMATTRIBUTEGM_H__
#define __GSLIB_ITEMSYSTEM_GM_ITEMATTRIBUTEGM_H__

#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/itemSystem/baseDef.h>
namespace GSLib
{

namespace ItemSystem
{

namespace GM
{       
// ��Ʒ����
enum EItemType
{
    EITEM_TP_IVALID = 0,           // ��Ч��Ʒ

    EITEM_TP_EQUIP_BEGIN = 1, // װ����ʼ
    EITEM_TP_EQUIP_WEAPONS = 1,     //����
    EITEM_TP_EQUIP_JADE = 2,		//����
    EITEM_TP_EQUIP_CAP = 3,		//ͷ��
    EITEM_TP_EQUIP_ARMOR = 4,		//����	
    EITEM_TP_EQUIP_GLOVE = 5,		//����	
    EITEM_TP_EQUIP_SHOES = 6,		//սѥ	
    EITEM_TP_EQUIP_NECKLACE = 7,		//����	
    EITEM_TP_EQUIP_RING = 8,		//����	
	EITEM_TP_EQUIP_FASHION = 9,		//ʱװ
	EITEM_TP_EQUIP_NENGLIANGQIU = 10,	// ������
    EITEM_TP_EQUIP_END = 100, // װ������
    ///������
    EITEM_TP_MATERIAL_BEGIN = 101, //��ʼ
    EITEM_TP_EQUIP_UPGRADE_MATERIAL = 101, // װ��ǿ������
    EITEM_TP_EQUIP_QUALITY_MATERIAL = 102,    // װ����������
    EITEM_TP_EQUIP_RESET_MATERIAL = 103,   // װ��ϴ������
    EITEM_TP_GEMS = 104,                   // ��ʯ
    EITEM_TP_MATERIAL_END = 1000, //����

    ///��Ƭ��
    EITEM_TP_PIECE_BEGIN = 1001, //��ʼ
    EITEM_TP_VIR_PET_MATERIAL = 1001,  // �ż���Ƭ 
    EITEM_TP_GEMS_MATERIAL = 1002, // ��ʯ��Ƭ
    EITEM_TP_PIECE_END = 10000,

    ///������
    EITEM_TP_PRO_BEGIN = 10001, //��ʼ
    EITEM_TP_PROP_GIFT = 10001,               // ���	
    EITEM_TP_PROP_SPEAKER = 10002,            // ����	
    EITEM_TP_PROP_MEDICINE = 10003,           // ҩˮ 
    EITEM_TP_PROP_PET_FRIENDLY = 10004,       // �øжȵ���	
    EITEM_TP_PROP_PET_WATER = 10005,          // ��Ȫ��ҩ
    EITEM_TP_PROP_KEY = 10006,                // Կ�� 
    EITEM_TP_PROP_BOX = 10007,                // ����
    EITEM_TP_PROP_VITALITY = 10008,           // �������� 
	EITEM_TP_PROP_DRESS = 10009,			  // ʱװ
    EITEM_TP_PRO_END = 100000, //����

    ///������ ���ڱ�����ʾ(100001~)
    EITEM_TP_VIR_PET = 100001,           // ��� 
    EITEM_TP_VIR_PVPCOIN = 100002,       // PVP��
    EITEM_TP_VIR_VIPSCORE = 100003,     // VIP����
    EITEM_TP_VIR_ACTIVE_DEGREE = 100004, // ��Ծ��
    EITEM_TP_VIR_BAGEXPAND = 100005,     // ��������
    EITEM_TP_VIR_GOLD = 100006,          // ���
    EITEM_TP_VIR_DIAMOND = 100007,       // ��ʯ
    EITEM_TP_VIR_EXP = 100008,           // ����
    EITEM_TP_VIR_VIP_CARD = 100009,      // vip���鿨 
    EITEM_TP_VIR_VITALITY = 100010,      // ����
	EITEM_TP_VIR_LIGHT_POWER = 100011,	// ������
    EITEM_TP_MAX,
};

enum EMainType
{
	EMAIN_TP_IVALID=0,      // ��Ч����
    EMAIN_TP_ITEM=1,        // ��Ʒ
    EMAIN_TP_RESOURCE=2,    // ��Դ
	EMAIN_TP_PET=3,         // ��� 
	EMAIN_TP_EQUIP=4,       // װ��
};

// ������Ʒ
class CPrizeItem
{
public:
	CPrizeItem(ItemTPID a_TPID = 0, GSLib::ItemSystem::GM::EItemType a_itemType = GSLib::ItemSystem::GM::EITEM_TP_IVALID, BSLib::uint32 a_itemCount = 0);
	~CPrizeItem();
public:
    bool init(const std::string& a_strItem, const std::string& a_separator);
public:
	void serializeTo(BSLib::Utility::CStream& stream) const;
    void serializeFrom(BSLib::Utility::CStream& stream);
public:
	ItemTPID m_itemTPID;
	GSLib::ItemSystem::GM::EItemType m_itemType;
	BSLib::uint32 m_itemCount;
};

}//GM

}//ItemSystem

}//GSLib
#endif//__GSLIB_ITEMSYSTEM_GM_ITEMATTRIBUTEGM_H__

