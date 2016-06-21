
#ifndef __BSLIB_UTILITY_MEMORY_OBJECTPOOL_H__
#define __BSLIB_UTILITY_MEMORY_OBJECTPOOL_H__

#include <BSLib/utility/noncopy.h>
#include <BSLib/utility/memory/allocator.h>

namespace BSLib
{

namespace Utility
{

class BSLIB_UTILITY_API CUnitPool : public CNoncopy
{
private:
	struct SUnitNode
	{
		BSLib::uint8* m_unit;
		SUnitNode* m_next;
	};

public:
	CUnitPool(uint32 unitSize);
	virtual ~CUnitPool();

	BSLib::uint8* allocUnit();
	void freeUnit(BSLib::uint8*& unit);

protected:
	bool _allocBuff();
	bool _allocUnit();
	void _freeBuff();

private:
	uint32 m_unitSize;

	std::vector<BSLib::uint8*> m_buffs;
	SUnitNode* m_units;
	SUnitNode* m_feerUnitNodes;
};

template<typename TYPE>
class CObjectPool
{
public:
	CObjectPool() : m_objectPool(sizeof(TYPE)) {}
	~CObjectPool() {}

	TYPE* construct()
	{
		TYPE* object = (TYPE*)m_objectPool.allocUnit();
		new (static_cast<void*>(object)) TYPE();
		return object;
	}

	template<class P1>
	TYPE* construct(P1 p1)
	{
		TYPE* object = (TYPE*)m_objectPool.allocUnit();
		new (static_cast<void*>(object)) TYPE(p1);
		return object;
	}

	template<class P1, class P2>
	TYPE* construct(P1 p1, P2 p2)
	{
		TYPE* object = (TYPE*)m_objectPool.allocUnit();
		new (static_cast<void*>(object)) TYPE(p1, p2);
		return object;
	}

	template<class P1, class P2, class P3>
	TYPE* construct(P1 p1, P2 p2, P3 p3)
	{
		TYPE* object = (TYPE*)m_objectPool.allocUnit();
		new (static_cast<void*>(object)) TYPE(p1, p2, p3);
		return object;
	}

	template<class P1, class P2, class P3, class P4>
	TYPE* construct(P1 p1, P2 p2, P3 p3, P4 p4)
	{
		TYPE* object = (TYPE*)m_objectPool.allocUnit();
		new (static_cast<void*>(object)) TYPE(p1, p2, p3, p4);
		return object;
	}

	template<class P1, class P2, class P3, class P4, class P5>
	TYPE* construct(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
	{
		TYPE* object = (TYPE*)m_objectPool.allocUnit();
		new (static_cast<void*>(object)) TYPE(p1, p2, p3, p4, p5);
		return object;
	}

	template<class P1, class P2, class P3, class P4, class P5, class P6>
	TYPE* construct(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)
	{
		TYPE* object = (TYPE*)m_objectPool.allocUnit();
		new (static_cast<void*>(object)) TYPE(p1, p2, p3, p4, p5, p6);
		return object;
	}

	template<class P1, class P2, class P3, class P4, class P5, class P6, class P7>
	TYPE* construct(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7)
	{
		TYPE* object = (TYPE*)m_objectPool.allocUnit();
		new (static_cast<void*>(object)) TYPE(p1, p2, p3, p4, p5, p6, p7);
		return object;
	}

	template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
	TYPE* construct(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8)
	{
		TYPE* object = (TYPE*)m_objectPool.allocUnit();
		new (static_cast<void*>(object)) TYPE(p1, p2, p3, p4, p5, p6, p7, p8);
		return object;
	}

	template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>
	TYPE* construct(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9)
	{
		TYPE* object = (TYPE*)m_objectPool.allocUnit();
		new (static_cast<void*>(object)) TYPE(p1, p2, p3, p4, p5, p6, p7, p8, p9);
		return object;
	}

	void destroy(TYPE*& object)
	{
		object->~TYPE();
		m_objectPool.freeUnit((BSLib::uint8*&)object);
		object = NULL;
	}

private:

	CUnitPool m_objectPool;
};

}//Utility

}//BSLib

#endif // __BSLIB_UTILITY_MEMORY_OBJECTPOOL_H__

