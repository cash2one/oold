//////////////////////////////////////////////////////////////////////
//	created:	2013/02/04
//	filename:	src\BSLib\utility\memory\objectPool.cpp
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/memory/objectPool.h>

namespace BSLib
{

namespace Utility
{

#define BSLIB_BUFFS_MAX 64

CUnitPool::CUnitPool(uint32 unitSize)
: m_unitSize(unitSize)
, m_units(NULL)
, m_feerUnitNodes(NULL)
{
	//_allocBuff();
}

CUnitPool::~CUnitPool()
{
	_freeBuff();
}

BSLib::uint8* CUnitPool::allocUnit()
{
	if (m_units == NULL) {
		if (!_allocBuff()) {
			return NULL;
		}
	}

	SUnitNode* unitNode = m_units;
	m_units = unitNode->m_next;

	unitNode->m_next = m_feerUnitNodes;
	m_feerUnitNodes = unitNode;

	return unitNode->m_unit;
}

void CUnitPool::freeUnit(BSLib::uint8*& unit)
{
	if (unit == NULL){
		return ;
	}
	if (m_feerUnitNodes == NULL) {
		if (!_allocUnit()) {
			return ;
		}
	}

	SUnitNode* unitNode = m_feerUnitNodes;
	m_feerUnitNodes = unitNode->m_next;

	unitNode->m_unit = unit;
	unitNode->m_next = m_units;
	m_units = unitNode;
}

bool CUnitPool::_allocBuff()
{
	if (m_unitSize <= 0) {
		return false;
	} 

	BSLib::uint8* buff = new BSLib::uint8[m_unitSize * BSLIB_BUFFS_MAX];
	if (buff == NULL) {
		return false;
	}
	m_buffs.push_back(buff);

	BSLib::uint8* tmpBuff = buff;
	SUnitNode* tmpUnit = NULL;

	for (int i=0; i<BSLIB_BUFFS_MAX; ++i) {
		if (m_feerUnitNodes == NULL) {
			if (!_allocUnit()) {
				return false;
			}
		}
		tmpUnit = m_feerUnitNodes;
		m_feerUnitNodes = tmpUnit->m_next;

		tmpUnit->m_unit = tmpBuff;
		tmpUnit->m_next = m_units;

		m_units = tmpUnit;

		tmpBuff += m_unitSize;
	}
	return true;
}

bool CUnitPool::_allocUnit()
{
	BSLib::uint8* node = new BSLib::uint8[sizeof(SUnitNode) * BSLIB_BUFFS_MAX];
	if (node == NULL) {
		return false;
	}
	m_buffs.push_back(node);

	BSLib::uint8* tmpNode = node;
	SUnitNode* tmpUnit = NULL;

	for (int i=0; i<BSLIB_BUFFS_MAX; ++i) {
		tmpUnit = (SUnitNode*)tmpNode;

		tmpUnit->m_unit = NULL;
		tmpUnit->m_next = m_feerUnitNodes;

		m_feerUnitNodes = tmpUnit;

		tmpNode += sizeof(SUnitNode);
	}
	return true;
}

void CUnitPool::_freeBuff()
{
	for (uint32 i=0; i<m_buffs.size(); ++i) {
		BSLib::uint8* buff = m_buffs[i];
		if (buff != NULL) {
			delete [] buff;
		}
	}
	m_buffs.clear();
	m_units = NULL;
	m_feerUnitNodes = NULL;
}

}//Utility

}//BSLib

