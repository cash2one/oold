//////////////////////////////////////////////////////////////////////
//	created:	2014/09/13
//	filename: 	GSLib\moduleType.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_MODULETYPE_H__
#define __GSLIB_MODULETYPE_H__

#include <GFLib/commonServer/message/funcType.h>

namespace GSLib
{

enum EModuleType
{
	EMODULECTYPE_NULL = 0,
	EMODULECTYPE_EQUIP,
	EMODULECTYPE_BAG,
	EMODULECTYPE_ITEM,
	EMODULECTYPE_SCENE,
	EMODULECTYPE_SKILL,
	EMODULECTYPE_PRIZE,
	EMODULECTYPE_TASK,
	EMODULECTYPE_CHAT,
	EMODULECTYPE_MAIL,
    EMODULECTYPE_PET,
	EMODULECTYPE_RANK,
	EMODULETYPE_SHOP,
	EMODULETYPE_FRIEND,
	EMODULETYPE_ACTIVITY,
	EMODULECTYPE_ACHIEVE,
	EMODULECTYPE_MASTER,

	EMODULECTYPE_MAX,
};

}//GFLib

#ifdef __GNUC__

namespace __gnu_cxx
{
	template< > struct hash< GSLib::EModuleType >
	{
		size_t operator()(const GSLib::EModuleType& x) const
		{
			return (size_t)x;
		}
	};
}

#endif

#endif//__GSLIB_MODULETYPE_H__
