/*
#include <GSLib/tracer.h>
#include <GSLib/itemSystem/msgItemSystem.h>
#include <GSLib/dbSystem/GM/dbSystemGM.h>
#include <GSLib/itemSystem/GM/itemStaticDataGM.h>

namespace GSLib
{

namespace ItemSystem
{	

namespace GM
{

CItemStaticDataGM::CItemStaticDataGM()
{
	m_attributeMgr = new CItemAttributeGMMgr();
}

	
CItemStaticDataGM::~CItemStaticDataGM()
{
	BSLIB_SAFE_DELETE(m_attributeMgr);
}

bool CItemStaticDataGM::isItemData(const BSLib::uint32 a_itemTPID,GSLib::ItemSystem::GM::EItemType a_itemType)
{
	if(m_attributeMgr->getAttribute(EITEM_BS_TPID) != a_itemTPID){
		return false;
	}
	else if(m_attributeMgr->getAttribute(EITEM_BS_TYPE) != (BSLib::uint32)a_itemType){
		return false;
	}

	return true;
}


bool CItemStaticDataGM::loadData(BSLib::Utility::CTableRow& a_tableRow)
{

	BSLib::uint32  tpid = 0;
	BSLib::uint32 type;
	BSLib::uint32 useLimit;
	BSLib::uint32 stackLimit;
	BSLib::uint32 isSell;
	BSLib::uint32 isUse;

	a_tableRow["f_id"] >> tpid;
	a_tableRow["f_type"] >> type;
	a_tableRow["f_use_limit"] >> useLimit;
	a_tableRow["f_stack_limit"] >> stackLimit;
	a_tableRow["f_issell"] >> isSell;
	a_tableRow["f_isuse"] >> isUse;

	m_attributeMgr->setAttribute(EITEM_BS_TPID,tpid);
	m_attributeMgr->setAttribute(EITEM_BS_TYPE,type);
	m_attributeMgr->setAttribute(EITEM_BS_USE_LIMIT,useLimit);
	m_attributeMgr->setAttribute(EITEM_BS_STACK_LIMIT,stackLimit);
	m_attributeMgr->setAttribute(EITEM_BS_ISSELL,isSell);
	m_attributeMgr->setAttribute(EITEM_BS_ISUSE,isUse);

	return true;
}

const BSLib::uint64 CItemStaticDataGM::getUniqueID()const
{
	BSLib::uint32  tpid = m_attributeMgr->getAttribute(EITEM_BS_TPID);
	BSLib::uint32  level = m_attributeMgr->getAttribute(EITEM_BS_TYPE);

	BSLib::uint64 left = (((BSLib::uint64)level) << (32)) & 0XFFFFFFFF00000000;
	BSLib::uint64 right = ((BSLib::uint64)tpid) & 0X00000000FFFFFFFF;
	BSLib::uint64 key = (left)|(right);
	return key;
}


}//GM

}//ItemSystem

}//GSLib
*/
