#ifndef __BSLIB_UTILITY_UNIQUEID_H__
#define __BSLIB_UTILITY_UNIQUEID_H__

#include <set>
#include <BSLib/utility/thread/mutex.h>
#include <BSLib/utility/function.h>

namespace BSLib
{

namespace Utility
{

template<typename TYPE>
class CUniqueIDMgr
{
public:
	virtual ~CUniqueIDMgr(){}

	virtual bool checkUniqueID(TYPE id) = 0;
};

template<typename TYPE>
class CUniqueID
{
public:
	CUniqueID(CUniqueIDMgr<TYPE>* a_uniqueIDMgr = NULL)
		: m_uniqueIDMgr(a_uniqueIDMgr)
	{
		_init(1, (TYPE)-1, (TYPE)-1);
	}

	CUniqueID(TYPE a_startID, CUniqueIDMgr<TYPE>* a_uniqueIDMgr = NULL)
		: m_uniqueIDMgr(a_uniqueIDMgr)
	{
		_init(a_startID, (TYPE)-1, (TYPE)-1);
	}

	CUniqueID(TYPE a_startID, TYPE a_endID, CUniqueIDMgr<TYPE>* a_uniqueIDMgr = NULL)
		: m_uniqueIDMgr(a_uniqueIDMgr)
	{
		_init(a_startID, a_endID, a_endID);
	}

	CUniqueID(TYPE a_startID, TYPE a_endID, TYPE a_invalidID, CUniqueIDMgr<TYPE>* a_uniqueIDMgr = NULL)
		: m_uniqueIDMgr(a_uniqueIDMgr)
	{
		_init(a_startID, a_endID, a_invalidID);
	}

	virtual ~CUniqueID()
	{
		;
	}

	void setUniqueIDMgr(CUniqueIDMgr<TYPE>* uniqueIDMgr)
	{
		m_uniqueIDMgr = uniqueIDMgr;
	}

	TYPE invalidID()
	{
		return m_invalidID;
	}

	bool isValidID(TYPE id)
	{
		return id != m_invalidID;
	}

	TYPE allocateID()
	{
		if (m_uniqueIDMgr != NULL) {
			for (TYPE i=m_startID; i<m_endID; ++i) {
				if (m_currID >= m_endID)	{
					m_currID = m_startID;
				}
				if (m_currID == m_invalidID) {
					m_currID = m_startID;
					continue;
				}
				if (!m_uniqueIDMgr->checkUniqueID(m_currID)) {
					TYPE id = m_currID;	
					++m_currID;
					return id;
				}
				++m_currID;
			}
		}
		return m_invalidID;
	}

private:
	void _init(TYPE a_startID, TYPE a_endID, TYPE a_invalidID)
	{
		m_startID = a_startID;
		m_endID = a_endID;
		m_invalidID = a_invalidID;
		m_currID = m_startID;
	}

private:
	CUniqueIDMgr<TYPE>* m_uniqueIDMgr;
	TYPE m_startID;
	TYPE m_endID;
	TYPE m_invalidID;
	TYPE m_currID;
};

typedef CUniqueID<uint8> CUniqueID8;
typedef CUniqueID<uint16> CUniqueID16;
typedef CUniqueID<uint32> CUniqueID32;
typedef CUniqueID<uint64> CUniqueID64;

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_UNIQUEID_H__

