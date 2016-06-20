//////////////////////////////////////////////////////////////////////
//	created:	2014/07/29
//	filename: 	GSLib\equipSystem\GM\equipAttributeGM.h
//	author:		zhangping
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_EQUIPSYSTEM_GM_EQUIPATTRIBUTEGM_H__
#define __GSLIB_EQUIPSYSTEM_GM_EQUIPATTRIBUTEGM_H__

#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/equipSystem/baseDef.h>

namespace GSLib
{

namespace EquipSystem
{

namespace GM
{

enum EEquipType
{
    EQUIP_INVALID       =0,     //��Чװ��
    EQUIP_WEAPONS = 1,  //����
    EQUIP_CAP = 2,	    //�ؼ�
    EQUIP_ARMOR = 3,    //ͷ��
    EQUIP_CLOTHES = 4,	//�Ʒ�	
    EQUIP_UNDERPANTS = 5,//�ڿ�	
    EQUIP_SHOES = 6,	//��ѥ	
    EQUIP_NECKLACE = 7,	//����	
    EQUIP_RING = 8,		//����	
	EQUIP_FASHION = 9,
	EQUIP_NENGLIANGQIU	= 10,
    EQUIP_NUMBER   = 10,     //װ������
};

enum EEquipStatus
{
    EQUIP_STATUS_ON = 0,          // װ������
    EQUIP_STATUS_OFF =1,          // װ������
};


enum EGemsCombineType
{
    EGEMS_COMBINE_TYPE_SINGLE = 0,      // ��ʯ�ϳ�
    EGEMS_COMBINE_TYPE_ALL =1,          // һ���ϳ�
};

/// <summary>
/// ��ʯ״̬
/// </summary>
enum EGemStatus
{
    /// <summary>
    /// ��Ƕ
    /// </summary>
    GEM_STATUS_ON = 0,
    /// <summary>
    /// ȡ��
    /// </summary>
    GEM_STATUS_OFF = 1,
};

/// <summary>
/// ��ʯ��
/// </summary>
enum EGemSlot
{
    GEM_SLOT_FIRST = 0,
    GEM_SLOT_SECOND = 1,
    GEM_SLOT_THIRD = 2,
    GEM_SLOT_FORTH = 3,
    GEM_SLOT_MAX = 4,
    GEM_SLOT_INVALID = 5,
};

class CEquipData{
public:
	BSLib::uint32 m_equipTPID;
	BSLib::uint32 m_equipLevel;
	BSLib::uint32 m_gemTPID[EQUIP_GEM_MAXCOUNT];
	BSLib::uint32 m_gemLevel[EQUIP_GEM_MAXCOUNT];

	CEquipData()
	{
		m_equipTPID = 0;
		m_equipLevel= 0;
		for(int i=0;i<EQUIP_GEM_MAXCOUNT;++i){
			m_gemTPID[i] = 0;
			m_gemLevel[i] = 0;
		}
	}

	bool serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_equipTPID;
		stream << m_equipLevel;
		for(BSLib::uint32 i=0;i<EQUIP_GEM_MAXCOUNT;++i){
			stream << m_gemTPID[i];
		}
		for(BSLib::uint32 i=0;i<EQUIP_GEM_MAXCOUNT;++i){
			stream << m_gemLevel[i];
		}

		return true;
	}
};

}//GM

}//EquipSystem

}//GSLib
#endif// __GSLIB_EQUIPSYSTEM_GM_EQUIPATTRIBUTEGM_H__
