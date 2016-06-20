//////////////////////////////////////////////////////////////////////
//	created:	2014/07/20
//	filename:	BSLib\utility\memory\objectMgr.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UTILITY_MEMORY_OBJECTMGR_H__
#define __BSLIB_UTILITY_MEMORY_OBJECTMGR_H__

#include <BSLib/utility/memory/objectPool.h>
#include <BSLib/utility/uniqueID.h>
#include <BSLib/utility/hashMap.h>

#define BSLIB_UTILITY_OBJECTMGR_KEY1(T1, N1)\
	template< typename KEY1, typename TYPE >\
	class T1\
	{\
	public:\
		class CCallback\
		{\
		public:\
			virtual bool exec(TYPE* _value) = 0;\
		};\
	public:\
		virtual ~T1(){}\
		TYPE* getObjectBy ## N1(const KEY1& key1)\
		{\
			TYPE* obj = NULL;\
			if(!m_objectHashMapByKey1.getValue(key1, obj)){\
				return NULL;\
			}\
			return obj;\
		}\
		TYPE* allcateObject(const KEY1& key1)\
		{\
			TYPE* obj = m_objectPool.construct();\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			return obj;\
		}\
		template<class P1>\
		TYPE* allcateObject(const KEY1& key1, P1 p1)\
		{\
			TYPE* obj = m_objectPool.construct(p1);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			return obj;\
		}\
		template<class P1, class P2>\
		TYPE* allcateObject(const KEY1& key1, P1 p1, P2 p2)\
		{\
			TYPE* obj = m_objectPool.construct(p1, p2);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			return obj;\
		}\
		template<class P1, class P2, class P3>\
		TYPE* allcateObject(const KEY1& key1, P1 p1, P2 p2, P3 p3)\
		{\
			TYPE* obj = m_objectPool.construct(p1, p2, p3);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			return obj;\
		}\
		template<class P1, class P2, class P3, class P4>\
		TYPE* allcateObject(const KEY1& key1, P1 p1, P2 p2, P3 p3, P4 p4)\
		{\
			TYPE* obj = m_objectPool.construct(p1, p2, p3, p4);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			return obj;\
		}\
		template<class P1, class P2, class P3, class P4, class P5>\
		TYPE* allcateObject(const KEY1& key1, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)\
		{\
			TYPE* obj = m_objectPool.construct(p1, p2, p3, p4, p5);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			return obj;\
		}\
		template<class P1, class P2, class P3, class P4, class P5, class P6>\
		TYPE* allcateObject(const KEY1& key1, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)\
		{\
			TYPE* obj = m_objectPool.construct(p1, p2, p3, p4, p5, p6);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			return obj;\
		}\
		template<class P1, class P2, class P3, class P4, class P5, class P6, class P7>\
		TYPE* allcateObject(const KEY1& key1, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7)\
		{\
			TYPE* obj = m_objectPool.construct(p1, p2, p3, p4, p5, p6, p7);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			return obj;\
		}\
		template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>\
		TYPE* allcateObject(const KEY1& key1, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8)\
		{\
			TYPE* obj = m_objectPool.construct(p1, p2, p3, p4, p5, p6, p7, p8);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			return obj;\
		}\
		template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>\
		TYPE* allcateObject(const KEY1& key1, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9)\
		{\
			TYPE* obj = m_objectPool.construct(p1, p2, p3, p4, p5, p6, p7, p8, p9);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			return obj;\
		}\
		void destroyBy ## N1(const KEY1& key1)\
		{\
			TYPE* obj = NULL;\
			if(!m_objectHashMapByKey1.getValue(key1, obj)){\
				return;\
			}\
			if (obj != NULL) {\
				m_objectPool.destroy(obj);\
			}\
			m_objectHashMapByKey1.remove(key1);\
		}\
		void destroyAll()\
		{\
			typedef typename BSLib::Utility::CHashMap<KEY1, TYPE*>::iterator iterator;\
			for (iterator it = m_objectHashMapByKey1.begin(); it != m_objectHashMapByKey1.end(); ++it){\
				TYPE* obj = it->second;\
				if (obj != NULL) {\
					m_objectPool.destroy(obj);\
				}\
			}\
			m_objectHashMapByKey1.clear();\
		}\
		void traversal(CCallback& cb)\
		{\
			typedef typename BSLib::Utility::CHashMap<KEY1, TYPE*>::iterator iterator;\
			for (iterator it = m_objectHashMapByKey1.begin(); it != m_objectHashMapByKey1.end(); ++it){\
				if (!cb.exec(it->second)) {\
					break;\
				}\
			}\
		}\
	private:\
		BSLib::Utility::CHashMap<KEY1, TYPE*> m_objectHashMapByKey1;\
		BSLib::Utility::CObjectPool<TYPE> m_objectPool;\
	};



#define BSLIB_UTILITY_OBJECTMGR_KEY2(T2, N1, N2) \
	template< typename KEY1, typename KEY2, typename TYPE >\
	class T2\
	{\
	public:\
		class CCallback\
		{\
		public:\
			virtual bool exec(TYPE* _value) = 0;\
		};\
	public:\
		virtual ~T2(){}\
		TYPE* getObjectBy ## N1(const KEY1& key1)\
		{\
			TYPE* obj = NULL;\
			if(!m_objectHashMapByKey1.getValue(key1, obj)){\
				return NULL;\
			}\
			return obj;\
		}\
		TYPE* getObjectBy ## N2(const KEY2& key2)\
		{\
			TYPE* obj = NULL;\
			if(!m_objectHashMapByKey2.getValue(key2, obj)){\
				return NULL;\
			}\
			return obj;\
		}\
		TYPE* allcateObject(const KEY1& key1, const KEY2& key2)\
		{\
			TYPE* obj = m_objectPool.construct();\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			m_objectHashMapByKey2.setValue(key2, obj);\
			return obj;\
		}\
		template<class P1>\
		TYPE* allcateObject(const KEY1& key1, const KEY2& key2, P1 p1)\
		{\
			TYPE* obj = m_objectPool.construct(p1);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			m_objectHashMapByKey2.setValue(key2, obj);\
			return obj;\
		}\
		template<class P1, class P2>\
		TYPE* allcateObject(const KEY1& key1, const KEY2& key2, P1 p1, P2 p2)\
		{\
			TYPE* obj = m_objectPool.construct(p1, p2);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			m_objectHashMapByKey2.setValue(key2, obj);\
			return obj;\
		}\
		template<class P1, class P2, class P3>\
		TYPE* allcateObject(const KEY1& key1, const KEY2& key2, P1 p1, P2 p2, P3 p3)\
		{\
			TYPE* obj = m_objectPool.construct(p1, p2, p3);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			m_objectHashMapByKey2.setValue(key2, obj);\
			return obj;\
		}\
		template<class P1, class P2, class P3, class P4>\
		TYPE* allcateObject(const KEY1& key1, const KEY2& key2, P1 p1, P2 p2, P3 p3, P4 p4)\
		{\
			TYPE* obj = m_objectPool.construct(p1, p2, p3, p4);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			m_objectHashMapByKey2.setValue(key2, obj);\
			return obj;\
		}\
		template<class P1, class P2, class P3, class P4, class P5>\
		TYPE* allcateObject(const KEY1& key1, const KEY2& key2, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)\
		{\
			TYPE* obj = m_objectPool.construct(p1, p2, p3, p4, p5);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			m_objectHashMapByKey2.setValue(key2, obj);\
			return obj;\
		}\
		template<class P1, class P2, class P3, class P4, class P5, class P6>\
		TYPE* allcateObject(const KEY1& key1, const KEY2& key2, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)\
		{\
			TYPE* obj = m_objectPool.construct(p1, p2, p3, p4, p5, p6);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			m_objectHashMapByKey2.setValue(key2, obj);\
			return obj;\
		}\
		template<class P1, class P2, class P3, class P4, class P5, class P6, class P7>\
		TYPE* allcateObject(const KEY1& key1, const KEY2& key2, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7)\
		{\
			TYPE* obj = m_objectPool.construct(p1, p2, p3, p4, p5, p6, p7);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			m_objectHashMapByKey2.setValue(key2, obj);\
			return obj;\
		}\
		template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>\
		TYPE* allcateObject(const KEY1& key1, const KEY2& key2, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8)\
		{\
			TYPE* obj = m_objectPool.construct(p1, p2, p3, p4, p5, p6, p7, p8);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			m_objectHashMapByKey2.setValue(key2, obj);\
			return obj;\
		}\
		template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>\
		TYPE* allcateObject(const KEY1& key1, const KEY2& key2, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9)\
		{\
			TYPE* obj = m_objectPool.construct(p1, p2, p3, p4, p5, p6, p7, p8, p9);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			m_objectHashMapByKey2.setValue(key2, obj);\
			return obj;\
		}\
		void destroyBy ## N1(const KEY1& key1)\
		{\
			TYPE* obj = NULL;\
			if(!m_objectHashMapByKey1.getValue(key1, obj)){\
				return;\
			}\
			if (obj == NULL) {\
				return;\
			}\
			KEY2 key2 = obj->get ## N2();\
			m_objectHashMapByKey1.remove(key1);\
			m_objectHashMapByKey2.remove(key2);\
			m_objectPool.destroy(obj);\
		}\
		void destroyBy ## N2(const KEY2& key2)\
		{\
			TYPE* obj = NULL;\
			if(!m_objectHashMapByKey2.getValue(key2, obj)){\
				return;\
			}\
			if (obj == NULL) {\
				return;\
			}\
			KEY1 key1 = obj->get ## N1();\
			m_objectHashMapByKey1.remove(key1);\
			m_objectHashMapByKey2.remove(key2);\
			m_objectPool.destroy(obj);\
		}\
		void destroyAll()\
		{\
			typedef typename BSLib::Utility::CHashMap<KEY1, TYPE*>::iterator iterator;\
			for (iterator it = m_objectHashMapByKey1.begin(); it != m_objectHashMapByKey1.end(); ++it){\
				TYPE* obj = it->second;\
				if (obj != NULL) {\
					m_objectPool.destroy(obj);\
				}\
			}\
			m_objectHashMapByKey1.clear();\
			m_objectHashMapByKey2.clear();\
		}\
		void traversal(CCallback& cb)\
		{\
			typedef typename BSLib::Utility::CHashMap<KEY1, TYPE*>::iterator iterator;\
			for (iterator it = m_objectHashMapByKey1.begin(); it != m_objectHashMapByKey1.end(); ++it){\
				if (!cb.exec(it->second)) {\
					break;\
				}\
			}\
		}\
	private:\
		BSLib::Utility::CHashMap< KEY1, TYPE* > m_objectHashMapByKey1;\
		BSLib::Utility::CHashMap< KEY2, TYPE* > m_objectHashMapByKey2;\
		BSLib::Utility::CObjectPool< TYPE > m_objectPool;\
	};




#define BSLIB_UTILITY_OBJECTMGR_KEY3(T3, N1, N2, N3)\
	template< typename KEY1, typename KEY2, typename KEY3, typename TYPE >\
	class T3\
	{\
	public:\
		class CCallback\
		{\
		public:\
			virtual bool exec(TYPE* _value) = 0;\
		};\
	public:\
		virtual ~T3(){}\
		TYPE* getObjectBy ## N1(const KEY1& key1)\
		{\
			TYPE* obj = NULL;\
			if(!m_objectHashMapByKey1.getValue(key1, obj)){\
				return NULL;\
			}\
			return obj;\
		}\
		TYPE* getObjectBy ## N2(const KEY2& key2)\
		{\
			TYPE* obj = NULL;\
			if(!m_objectHashMapByKey2.getValue(key2, obj)){\
				return NULL;\
			}\
			return obj;\
		}\
		TYPE* getObjectBy ## N3(const KEY3& key3)\
		{\
			TYPE* obj = NULL;\
			if(!m_objectHashMapByKey3.getValue(key3, obj)){\
				return NULL;\
			}\
			return obj;\
		}\
		TYPE* allcateObject(const KEY1& key1, const KEY2& key2, const KEY3& key3)\
		{\
			TYPE* obj = m_objectPool.construct();\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			m_objectHashMapByKey2.setValue(key2, obj);\
			m_objectHashMapByKey3.setValue(key3, obj);\
			return obj;\
		}\
		template<class P1>\
		TYPE* allcateObject(const KEY1& key1, const KEY2& key2, const KEY3& key3, P1 p1)\
		{\
			TYPE* obj = m_objectPool.construct(p1);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			m_objectHashMapByKey2.setValue(key2, obj);\
			m_objectHashMapByKey3.setValue(key3, obj);\
			return obj;\
		}\
		template<class P1, class P2>\
		TYPE* allcateObject(const KEY1& key1, const KEY2& key2, const KEY3& key3, P1 p1, P2 p2)\
		{\
			TYPE* obj = m_objectPool.construct(p1, p2);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			m_objectHashMapByKey2.setValue(key2, obj);\
			m_objectHashMapByKey3.setValue(key3, obj);\
			return obj;\
		}\
		template<class P1, class P2, class P3>\
		TYPE* allcateObject(const KEY1& key1, const KEY2& key2, const KEY3& key3, P1 p1, P2 p2, P3 p3)\
		{\
			TYPE* obj = m_objectPool.construct(p1, p2, p3);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			m_objectHashMapByKey2.setValue(key2, obj);\
			m_objectHashMapByKey3.setValue(key3, obj);\
			return obj;\
		}\
		template<class P1, class P2, class P3, class P4>\
		TYPE* allcateObject(const KEY1& key1, const KEY2& key2, const KEY3& key3, P1 p1, P2 p2, P3 p3, P4 p4)\
		{\
			TYPE* obj = m_objectPool.construct(p1, p2, p3, p4);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			m_objectHashMapByKey2.setValue(key2, obj);\
			m_objectHashMapByKey3.setValue(key3, obj);\
			return obj;\
		}\
		template<class P1, class P2, class P3, class P4, class P5>\
		TYPE* allcateObject(const KEY1& key1, const KEY2& key2, const KEY3& key3, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)\
		{\
			TYPE* obj = m_objectPool.construct(p1, p2, p3, p4, p5);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			m_objectHashMapByKey2.setValue(key2, obj);\
			m_objectHashMapByKey3.setValue(key3, obj);\
			return obj;\
		}\
		template<class P1, class P2, class P3, class P4, class P5, class P6>\
		TYPE* allcateObject(const KEY1& key1, const KEY2& key2, const KEY3& key3, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)\
		{\
			TYPE* obj = m_objectPool.construct(p1, p2, p3, p4, p5, p6);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			m_objectHashMapByKey2.setValue(key2, obj);\
			m_objectHashMapByKey3.setValue(key3, obj);\
			return obj;\
		}\
		template<class P1, class P2, class P3, class P4, class P5, class P6, class P7>\
		TYPE* allcateObject(const KEY1& key1, const KEY2& key2, const KEY3& key3, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7)\
		{\
			TYPE* obj = m_objectPool.construct(p1, p2, p3, p4, p5, p6, p7);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			m_objectHashMapByKey2.setValue(key2, obj);\
			m_objectHashMapByKey3.setValue(key3, obj);\
			return obj;\
		}\
		template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>\
		TYPE* allcateObject(const KEY1& key1, const KEY2& key2, const KEY3& key3, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8)\
		{\
			TYPE* obj = m_objectPool.construct(p1, p2, p3, p4, p5, p6, p7, p8);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			m_objectHashMapByKey2.setValue(key2, obj);\
			m_objectHashMapByKey3.setValue(key3, obj);\
			return obj;\
		}\
		template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>\
		TYPE* allcateObject(const KEY1& key1, const KEY2& key2, const KEY3& key3, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9)\
		{\
			TYPE* obj = m_objectPool.construct(p1, p2, p3, p4, p5, p6, p7, p8, p9);\
			if (obj == NULL) {\
				return NULL;\
			}\
			m_objectHashMapByKey1.setValue(key1, obj);\
			m_objectHashMapByKey2.setValue(key2, obj);\
			m_objectHashMapByKey3.setValue(key3, obj);\
			return obj;\
		}\
		void destroyBy ## N1(KEY1& key1)\
		{\
			TYPE* obj = NULL;\
			if(!m_objectHashMapByKey1.getValue(key1, obj)){\
				return;\
			}\
			if (obj == NULL) {\
				return;\
			}\
			KEY2 key2 = obj->get ## N2();\
			KEY3 key3 = obj->get ## N3();\
			m_objectHashMapByKey1.remove(key1);\
			m_objectHashMapByKey2.remove(key2);\
			m_objectHashMapByKey3.remove(key3);\
			m_objectPool.destroy(obj);\
		}\
		void destroyBy ## N2(KEY2& key2)\
		{\
			TYPE* obj = NULL;\
			if(!m_objectHashMapByKey2.getValue(key2, obj)){\
				return;\
			}\
			if (obj == NULL) {\
				return;\
			}\
			KEY1 key1 = obj->get ## N1();\
			KEY3 key3 = obj->get ## N3();\
			m_objectHashMapByKey1.remove(key1);\
			m_objectHashMapByKey2.remove(key2);\
			m_objectHashMapByKey3.remove(key3);\
			m_objectPool.destroy(obj);\
		}\
		void destroyBy ## N3(KEY3& key3)\
		{\
			TYPE* obj = NULL;\
			if(!m_objectHashMapByKey3.getValue(key3, obj)){\
				return;\
			}\
			if (obj == NULL) {\
				return;\
			}\
			KEY1 key1 = obj->get ## N1();\
			KEY2 key2 = obj->get ## N2();\
			m_objectHashMapByKey1.remove(key1);\
			m_objectHashMapByKey2.remove(key2);\
			m_objectHashMapByKey3.remove(key3);\
			m_objectPool.destroy(obj);\
		}\
		void destroyAll()\
		{\
			typedef typename BSLib::Utility::CHashMap<KEY1, TYPE*>::iterator iterator;\
			for (iterator it = m_objectHashMapByKey1.begin(); it != m_objectHashMapByKey1.end(); ++it){\
				TYPE* obj = it->second;\
				if (obj != NULL) {\
					m_objectPool.destroy(obj);\
				}\
			}\
			m_objectHashMapByKey1.clear();\
			m_objectHashMapByKey2.clear();\
			m_objectHashMapByKey3.clear();\
		}\
		void traversal(CCallback& cb)\
		{\
			typedef typename BSLib::Utility::CHashMap<KEY1, TYPE*>::iterator iterator;\
			for (iterator it = m_objectHashMapByKey1.begin(); it != m_objectHashMapByKey1.end(); ++it){\
				if (!cb.exec(it->second)) {\
					break;\
				}\
			}\
		}\
	private:\
		BSLib::Utility::CHashMap<KEY1, TYPE*> m_objectHashMapByKey1;\
		BSLib::Utility::CHashMap<KEY2, TYPE*> m_objectHashMapByKey2;\
		BSLib::Utility::CHashMap<KEY3, TYPE*> m_objectHashMapByKey3;\
		BSLib::Utility::CObjectPool<TYPE> m_objectPool;\
	};

#endif//__BSLIB_UTILITY_MEMORY_OBJECTMGR_H__
