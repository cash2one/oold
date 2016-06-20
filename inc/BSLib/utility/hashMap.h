//////////////////////////////////////////////////////////////////////
//	created:	2011/04/12
//	filename:	BSLib\utility\hashMap.h
//	author:		mazhejiang
//
///	@brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UTILITY_HASHMAP_H__
#define __BSLIB_UTILITY_HASHMAP_H__

#ifdef __GNUC__
#include <ext/hash_map>
#else
#include <hash_map>
#endif

#include <BSLib/utility/function.h>

#ifdef __GNUC__

namespace __gnu_cxx
{
	template< > struct hash< std::string >
	{
		size_t operator()(const std::string& x) const
		{
			//return hash<const char*>()(x.c_str());
			
			BSLib::uint32 v = 0;
			for (BSLib::uint32 i = 0; i < x.size();++i)
				v ^= (( v << 5) + (v >> 2) + x[i]);
			return size_t(v);
		}
	};

	template< > struct hash< BSLib::int64 >
	{
		size_t operator()(const BSLib::int64& x) const
		{
			if (sizeof(x) == sizeof(size_t))
				return x;
			else
				return (x >> 32) ^ (x & 0xFFFFFFFF);
		}
	};

	template< > struct hash< BSLib::uint64 >
	{
		size_t operator()(const BSLib::uint64& x) const
		{
			if (sizeof(x) == sizeof(size_t))
				return x;
			else
				return (x >> 32) ^ (x & 0xFFFFFFFF);
		}
	};
}

#endif

namespace BSLib
{

namespace Utility
{

//////////////////////////////////////////////////////////////////////////
/// @brief HashMap 对windows/linux统一接口
//////////////////////////////////////////////////////////////////////////
template< class KEY, class VALUE >
class CHashMap
{
public:
	class CCallback
	{
	public:
		virtual bool exec(const KEY& _key, VALUE& _value) = 0;
	};

private:

#ifdef __GNUC__
	typedef __gnu_cxx::hash_map< KEY, VALUE, __gnu_cxx::hash< KEY > > HashMapType;
#else
	typedef stdext::hash_map< KEY, VALUE, stdext::hash_compare< KEY > > HashMapType;
#endif

public:

	typedef typename HashMapType::iterator iterator;
	typedef typename HashMapType::const_iterator const_iterator;

private:
	HashMapType  m_hashMap;

public:
	iterator begin()
	{
		return m_hashMap.begin();
	}

	const_iterator begin() const
	{
		return m_hashMap.begin();
	}

	iterator end()
	{
		return m_hashMap.end();
	}

	const_iterator end() const
	{
		return m_hashMap.end();
	}

	iterator erase(iterator it)
	{
#ifdef __GNUC__
		iterator nextIt = it;
		++nextIt;
		m_hashMap.erase(it);
		return nextIt;
#else
		return m_hashMap.erase(it);
#endif
	}

	VALUE& getValue(const KEY& key) 
	{
		return m_hashMap[key];
	}

	bool getValue(const KEY& key, VALUE& value) const
	{
		const_iterator it = m_hashMap.find(key);	
		if (it == m_hashMap.end()){
			return false;
		}
		value = it->second;
		return true;
	}

	void setValue(const KEY& key, const VALUE& value)
	{
		m_hashMap[key] = value;
	}

	BSLib::uint32 remove(const KEY& key)
	{
		return (BSLib::uint32)m_hashMap.erase(key);
	}

	iterator find(const KEY& key)
	{
		return m_hashMap.find(key);	
	}

	const_iterator find(const KEY& key) const
	{
		return m_hashMap.find(key);	
	}

	void clear()
	{
		m_hashMap.clear();
	}

	bool empty() const
	{
		return m_hashMap.empty();
	}

	unsigned int size() const
	{
		return (unsigned int)m_hashMap.size();
	}

	void traversal(CCallback& cb)
	{
		for (iterator it = m_hashMap.begin(); it != m_hashMap.end(); ++it){
			if (!cb.exec(it->first, it->second)) {
				break;
			}
		}
	}

	void traversal(CFunction<bool, const KEY&, VALUE&>& fun)
	{
		for (iterator it = m_hashMap.begin(); it != m_hashMap.end(); ++it){
			if (!fun(it->first, it->second)) {
				break;
			}
		}
	}

	template<class P1>
	void traversal(CFunction<bool, const KEY&, VALUE&, P1>& fun, P1 p1)
	{
		for (iterator it = m_hashMap.begin(); it != m_hashMap.end(); ++it){
			if (!fun(it->first, it->second, p1)) {
				break;
			}
		}
	}
	template<class P1, class P2>
	void traversal(CFunction<bool, const KEY&, VALUE&, P1, P2>& fun, P1 p1, P2 p2)
	{
		for (iterator it = m_hashMap.begin(); it != m_hashMap.end(); ++it){
			if (!fun(it->first, it->second, p1, p2)) {
				break;
			}
		}
	}

	template<class P1, class P2, class P3>
	void traversal(CFunction<bool, const KEY&, VALUE&, P1, P2, P3>& fun, P1 p1, P2 p2, P3 p3)
	{
		for (iterator it = m_hashMap.begin(); it != m_hashMap.end(); ++it){
			if (!fun(it->first, it->second, p1, p2, p3)) {
				break;
			}
		}
	}

	template<class P1, class P2, class P3, class P4>
	void traversal(CFunction<bool, const KEY&, VALUE&, P1, P2, P3, P4>& fun, P1 p1, P2 p2, P3 p3, P4 p4)
	{
		for (iterator it = m_hashMap.begin(); it != m_hashMap.end(); ++it){
			if (!fun(it->first, it->second, p1, p2, p3, p4)) {
				break;
			}
		}
	}

	template<class P1, class P2, class P3, class P4, class P5>
	void traversal(CFunction<bool, const KEY&, VALUE&, P1, P2, P3, P4, P5>& fun, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
	{
		for (iterator it = m_hashMap.begin(); it != m_hashMap.end(); ++it){
			if (!fun(it->first, it->second, p1, p2, p3, p4, p5)) {
				break;
			}
		}
	}
};

//////////////////////////////////////////////////////////////////////////
template< class KEY, class VALUE >
class CMultiHashMap
{
public:
	class CCallback
	{
	public:
		virtual bool exec(const KEY& _key, VALUE& _value) = 0;
	};

private:

#ifdef __GNUC__
	typedef __gnu_cxx::hash_multimap< KEY, VALUE, __gnu_cxx::hash< KEY > > MultiHashMapType;
#else
	typedef stdext::hash_multimap< KEY, VALUE, stdext::hash_compare< KEY > > MultiHashMapType;
#endif

public:

	typedef typename MultiHashMapType::iterator iterator;
	typedef typename MultiHashMapType::const_iterator const_iterator;

private:
	MultiHashMapType  m_hashMap;

public:
	iterator begin()
	{
		return m_hashMap.begin();
	}

	const_iterator begin() const
	{
		return m_hashMap.begin();
	}

	iterator end()
	{
		return m_hashMap.end();
	}

	const_iterator end() const
	{
		return m_hashMap.end();
	}

	iterator erase(iterator it)
	{
#ifdef __GNUC__
		iterator nextIt = it;
		++nextIt;
		m_hashMap.erase(it);
		return nextIt;
#else
		return m_hashMap.erase(it);
#endif
	}

	bool getValue(const KEY& key, VALUE& value) const
	{
		const_iterator it = m_hashMap.find(key);	
		if (it == m_hashMap.end()){
			return false;
		}
		value = it->second;
		return true;
	}

	bool addValue(const KEY& key, const VALUE& value)
	{
		return m_hashMap.insert(std::pair<KEY, VALUE>(key, value)) != m_hashMap.end();
	}

	void setValue(const KEY& key, const VALUE& value)
	{
		iterator it = m_hashMap.find(key);	
		if (it == m_hashMap.end()){
			m_hashMap.insert(std::pair<KEY, VALUE>(key, value));
		} else {
			it->second = value;
		}
	}

	BSLib::uint32 remove(const KEY& key)
	{
		return (BSLib::uint32)m_hashMap.erase(key);
	}

	BSLib::uint32 remove(const KEY& key, const VALUE& value)
	{
		int num = 0;
		iterator it = m_hashMap.find(key);
		while (it != m_hashMap.end()){
			if (it->first != key) {
				break;
			}
			if (it->second == value) {
				it = erase(it);
				++num;
				continue;
			}
			++it;
		}
		return num;
	}

	iterator find(const KEY& key)
	{
		return m_hashMap.find(key);	
	}

	const_iterator find(const KEY& key) const
	{
		return m_hashMap.find(key);	
	}

	void clear()
	{
		m_hashMap.clear();
	}

	bool empty() const
	{
		return m_hashMap.empty();
	}

	unsigned int size() const
	{
		return (unsigned int)m_hashMap.size();
	}

	unsigned int count(const KEY& key) const
	{
		return (unsigned int)m_hashMap.count(key);
	}

	void traversal(CCallback& cb)
	{
		for (iterator it = m_hashMap.begin(); it != m_hashMap.end(); ++it){
			if (!cb.exec(it->first, it->second)) {
				break;
			}
		}
	}

	void traversal(CFunction<bool, const KEY&, VALUE&>& fun)
	{
		for (iterator it = m_hashMap.begin(); it != m_hashMap.end(); ++it){
			if (!fun(it->first, it->second)) {
				break;
			}
		}
	}

	template<class P1>
	void traversal(CFunction<bool, const KEY&, VALUE&, P1>& fun, P1 p1)
	{
		for (iterator it = m_hashMap.begin(); it != m_hashMap.end(); ++it){
			if (!fun(it->first, it->second, p1)) {
				break;
			}
		}
	}
	template<class P1, class P2>
	void traversal(CFunction<bool, const KEY&, VALUE&, P1, P2>& fun, P1 p1, P2 p2)
	{
		for (iterator it = m_hashMap.begin(); it != m_hashMap.end(); ++it){
			if (!fun(it->first, it->second, p1, p2)) {
				break;
			}
		}
	}

	template<class P1, class P2, class P3>
	void traversal(CFunction<bool, const KEY&, VALUE&, P1, P2, P3>& fun, P1 p1, P2 p2, P3 p3)
	{
		for (iterator it = m_hashMap.begin(); it != m_hashMap.end(); ++it){
			if (!fun(it->first, it->second, p1, p2, p3)) {
				break;
			}
		}
	}

	template<class P1, class P2, class P3, class P4>
	void traversal(CFunction<bool, const KEY&, VALUE&, P1, P2, P3, P4>& fun, P1 p1, P2 p2, P3 p3, P4 p4)
	{
		for (iterator it = m_hashMap.begin(); it != m_hashMap.end(); ++it){
			if (!fun(it->first, it->second, p1, p2, p3, p4)) {
				break;
			}
		}
	}

	template<class P1, class P2, class P3, class P4, class P5>
	void traversal(CFunction<bool, const KEY&, VALUE&, P1, P2, P3, P4, P5>& fun, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
	{
		for (iterator it = m_hashMap.begin(); it != m_hashMap.end(); ++it){
			if (!fun(it->first, it->second, p1, p2, p3, p4, p5)) {
				break;
			}
		}
	}
};

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_HASHMAP_H__
