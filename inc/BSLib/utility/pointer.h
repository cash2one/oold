/********************************************************************
	created:	2012/06/29
	filename:	BSLib\utility\pointer.h
	author:		mazhejiang
	
	purpose:	
*********************************************************************/
#ifndef __BSLIB_UTILITY_POINTER_H__
#define __BSLIB_UTILITY_POINTER_H__

#include <BSLib/utility/atomic.h>

namespace BSLib
{

namespace Utility
{

//////////////////////////////////////////////////////////////////////////
/// @brief ÷«ƒ‹÷∏’Î
//////////////////////////////////////////////////////////////////////////
template < class TYPE, class COUNT_TYPE = CAtomic>
class CPointer
{
public:
	CPointer(): m_object(NULL), m_count(NULL){}

	CPointer(TYPE* object): m_object(object), m_count(NULL)
	{
		_newCount();
	}

	CPointer(const CPointer<TYPE, COUNT_TYPE>& pointer) : m_object(NULL), m_count(NULL)
	{
		m_object = pointer.m_object;
		m_count = pointer.m_count;
		_setObject();
	}

	template <class OTHER_TYPE> CPointer(const CPointer<OTHER_TYPE, COUNT_TYPE>& pointer) : m_object(dynamic_cast<TYPE*>((OTHER_TYPE*)pointer)), m_count(pointer.getCount())
	{
		_setObject();
	}

	~CPointer()
	{
		_clear();
	}

	TYPE& operator *()
	{
		return *m_object;
	}

	const TYPE& operator *() const
	{
		return *m_object;
	}

	TYPE* operator ->()
	{
		return m_object;
	}

	const TYPE* operator ->() const
	{
		return m_object;
	}

	CPointer& operator =(TYPE* object)
	{
		_clear();
		m_object = object;
		_newCount();
		return *this;
	}

	CPointer& operator =(const CPointer<TYPE, COUNT_TYPE>& pointer)
	{
		if (&pointer == this) {
			return *this;
		}
		_clear();
		m_object = pointer.m_object;
		m_count = pointer.m_count;
		_setObject();
		return *this;
	}

	template <class OTHER> CPointer& operator =(CPointer<OTHER, COUNT_TYPE>& pointer)
	{
		_clear();
		m_object = dynamic_cast<TYPE*>((OTHER*)pointer);
		if (m_object != NULL) {
			m_count = pointer.getCount();
			_setObject();
		}
		return *this;
	}

	bool operator ==(TYPE* object) const
	{
		return m_object == object;
	}

	bool operator ==(const CPointer<TYPE>& pointer) const
	{
		return m_object == pointer.m_object;
	}

	template <class OTHER> bool operator ==(const CPointer<OTHER>& pointer) const
	{
		if (m_object == NULL && pointer.m_object == NULL) {
			return true;
		}
		return m_object != NULL && m_object == dynamic_cast<TYPE*>(pointer.m_object);
	}

	bool operator !=(TYPE* object) const
	{
		return m_object != object;
	}

	bool operator !=(const CPointer<TYPE>& pointer) const
	{
		return m_object != pointer.m_object;
	}

	template <class OTHER> bool operator !=(const CPointer<OTHER>& pointer) const
	{
		if (m_object == NULL && pointer.m_object == NULL) {
			return false;
		}
		return m_object != NULL && m_object != dynamic_cast<TYPE*>(pointer.m_object);
	}

	operator TYPE*() const
	{
		return m_object;
	}

	template <class OTHER> operator OTHER*() const
	{
		return dynamic_cast<OTHER*>(m_object);
	}

	COUNT_TYPE* getCount() const
	{ 
		return m_count; 
	}

private:
	inline void _clear()
	{
		if (m_object != NULL) {
			int32 count = m_count->decrement();
			if (count <= 0) {
				BSLIB_SAFE_DELETE(m_object);
				BSLIB_SAFE_DELETE(m_count);
				return ;
			}	
		}
		m_count = NULL;
		m_object = NULL;
	}

	inline void _newCount()
	{
		if (m_object != NULL) {
			m_count = new COUNT_TYPE();
			if (m_count == NULL) {
				m_object = NULL;
				return ;
			}
			m_count->increment();
		}
	}

	inline void _setObject()
	{
		if (m_object != NULL) {
			m_count->increment();
			return ;
		}
		m_count = NULL;
	}

private:
	TYPE* m_object;
	COUNT_TYPE* m_count;
};

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_POINTER_H__




