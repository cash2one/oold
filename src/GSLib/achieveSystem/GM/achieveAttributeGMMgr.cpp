/*
#include <GSLib/itemSystem/GM/itemAttributeGMMgr.h>
#include <GSLib/tracer.h>

namespace GSLib
{

namespace ItemSystem
{	

namespace GM
{

CItemAttributeGMMgr::CItemAttributeGMMgr()
{
    m_itemUInt32Attribute.resize(EITEM_INT32_MAX_INDEX,CItemUInt32Attribute(0));
}

CItemAttributeGMMgr::~CItemAttributeGMMgr()
{
	;
}

void CItemAttributeGMMgr::init()
{

}
void CItemAttributeGMMgr::final()
{

}

BSLib::uint32 CItemAttributeGMMgr::getAttribute(EItemUInt32Attribute m_attributeIndex)
{
   return m_itemUInt32Attribute[m_attributeIndex].getAttributeValue();
}

void CItemAttributeGMMgr::setAttribute(EItemUInt32Attribute m_attributeIndex,BSLib::uint32 value)
{
   m_itemUInt32Attribute[m_attributeIndex].setAttributeValue(value);
}



}//GM

}//PlayerSystem

}//GSLib
*/
