#ifndef __BSLIB_UTILITY_FUNCTIONEVENT_H__
#define __BSLIB_UTILITY_FUNCTIONEVENT_H__

#include <BSLib/utility/function.h>

#define BSLIB_UTILITY_FUNCTION_EVENT(N)\
	template <BSLIB_UTILITY_FUNCTION_TEMPLATE_##N>\
	class CFunctionEvent\
	{\
	protected:\
		struct CFunctionEventItem\
		{\
			bool m_isValid;\
			BSLib::Utility::CFunction<BSLIB_UTILITY_FUNCTION_TEMPLATE_PARA_##N>* m_fun;\
			CFunctionEventItem() : m_isValid(NULL), m_fun(NULL) { }\
			~CFunctionEventItem()\
			{\
				if (m_fun != NULL) {\
					BSLIB_SAFE_DELETE(m_fun);\
				}\
			}\
		};\
		typedef typename std::list< CFunctionEventItem* >::iterator CFunctionEventItemListIter;\
	public:\
		CFunctionEvent(BSLib::Utility::CFunctionEventResult<R>* a_funRes = NULL, const R& a_default = 0) : m_funRes(a_funRes), m_default(a_default) {}\
		~CFunctionEvent() { _clear(); }\
		CFunctionEventHandle addFunctionEvent(R(*a_fun)(BSLIB_UTILITY_FUNCTION_TYPE_##N))\
		{\
			CFunctionEventItem* handle = new CFunctionEventItem();\
			if (handle == NULL) {\
				return NULL;\
			}\
			BSLib::Utility::CFunction<BSLIB_UTILITY_FUNCTION_TEMPLATE_PARA_##N>* fun = new BSLib::Utility::CFunction<BSLIB_UTILITY_FUNCTION_TEMPLATE_PARA_##N>(a_fun);\
			if (fun == NULL) {\
				BSLIB_SAFE_DELETE(handle);\
				return NULL;\
			}\
			handle->m_isValid = true;\
			handle->m_fun = fun;\
			m_functionAddList.push_back(handle);\
			return handle;\
		}\
		CFunctionEventHandle addFunctionEvent(BSLib::Utility::CFunction<BSLIB_UTILITY_FUNCTION_TEMPLATE_PARA_##N>& a_fun)\
		{\
			CFunctionEventItem* handle = new CFunctionEventItem();\
			if (handle == NULL) {\
				return NULL;\
			}\
			BSLib::Utility::CFunction<BSLIB_UTILITY_FUNCTION_TEMPLATE_PARA_##N>* fun = a_fun.clone();\
			if (fun == NULL) {\
				return NULL;\
			}\
			handle->m_isValid = true;\
			handle->m_fun = fun;\
			m_functionAddList.push_back(handle);\
			return handle;\
		}\
		template<class C>\
		CFunctionEventHandle addFunctionEvent(R(C::*a_fun)(BSLIB_UTILITY_FUNCTION_TYPE_##N), C* a_object)\
		{\
			CFunctionEventItem* handle = new CFunctionEventItem();\
			if (handle == NULL) {\
				return NULL;\
			}\
			BSLib::Utility::CFunctionObject<BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_PARA_##N>* fun = new BSLib::Utility::CFunctionObject<BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_PARA_##N>(a_fun, a_object);\
			if (fun == NULL) {\
				return NULL;\
			}\
			handle->m_isValid = true;\
			handle->m_fun = fun;\
			m_functionAddList.push_back(handle);\
			return handle;\
		}\
		void delFunctionEvent(CFunctionEventHandle& a_handle)\
		{\
			if (a_handle == NULL) {\
				return ;\
			}\
			CFunctionEventItem* item = (CFunctionEventItem*)a_handle;\
			if (item == NULL) {\
				return;\
			}\
			item->m_isValid = false;\
			a_handle = NULL;\
		}\
		bool empty()\
		{\
			return m_functionList.empty() && m_functionAddList.empty();\
		}\
		virtual R operator()(BSLIB_UTILITY_FUNCTION_TYPE_PARA_##N)\
		{\
			_updateFunctionEvent();\
			R res = m_default;\
			CFunctionEventItemListIter it = m_functionList.begin();\
			while (it != m_functionList.end()) {\
				CFunctionEventItem* item = *it;\
				if (item == NULL) {\
					it = m_functionList.erase(it);\
					continue;\
				}\
				if (item->m_isValid == false) {\
					it = m_functionList.erase(it);\
					BSLIB_SAFE_DELETE(item);\
					continue;\
				}\
				BSLib::Utility::CFunction<BSLIB_UTILITY_FUNCTION_TEMPLATE_PARA_##N>* fun = item->m_fun;\
				if (fun == NULL) {\
					++it;\
					continue;\
				}\
				res = (*fun)(BSLIB_UTILITY_FUNCTION_PARA_##N);\
				if (m_funRes == NULL) {\
					++it;\
					continue;\
				}\
				if (!(*m_funRes)(res)) {\
					break;\
				}\
				++it;\
			}\
			if (m_funRes != NULL) {\
				m_funRes->getFunctionResult(res);\
			}\
			return res;\
		}\
	protected:\
		void _clear()\
		{\
			CFunctionEventItemListIter it_addList = m_functionAddList.begin();\
			for (; it_addList != m_functionAddList.end(); ++it_addList) {\
				CFunctionEventItem* item = *it_addList;\
				if (item == NULL){\
					continue;\
				}\
				BSLIB_SAFE_DELETE(item);\
			}\
			m_functionAddList.clear();\
			CFunctionEventItemListIter it = m_functionList.begin();\
			for (; it != m_functionList.end(); ++it) {\
				CFunctionEventItem* item = *it;\
				if (item == NULL){\
					continue;\
				}\
				BSLIB_SAFE_DELETE(item);\
			}\
			m_functionList.clear();\
		}\
		void _updateFunctionEvent()\
		{\
			CFunctionEventItemListIter it_addList = m_functionAddList.begin();\
			for (; it_addList != m_functionAddList.end(); ++it_addList) {\
				CFunctionEventItem* item = *it_addList;\
				if (item == NULL){\
					continue;\
				}\
				m_functionList.push_back(item);\
			}\
			m_functionAddList.clear();\
		}\
	protected:\
		BSLib::Utility::CFunctionEventResult<R>* m_funRes;\
		std::list<CFunctionEventItem*> m_functionList;\
		std::list<CFunctionEventItem*> m_functionAddList;\
		R m_default;\
	};

#define BSLIB_UTILITY_FUNCTION_EVENT_SPECIAL(N)\
	template <BSLIB_UTILITY_FUNCTION_TEMPLATE_TYPE_##N>\
	class CFunctionEvent<BSLIB_UTILITY_FUNCTION_TEMPLATE_PARA_##N>\
	{\
	protected:\
		struct CFunctionEventItem\
		{\
		bool m_isValid;\
		BSLib::Utility::CFunction<BSLIB_UTILITY_FUNCTION_TEMPLATE_PARA_##N>* m_fun;\
		CFunctionEventItem() : m_isValid(NULL), m_fun(NULL) { }\
		~CFunctionEventItem()\
			{\
				if (m_fun != NULL) {\
					BSLIB_SAFE_DELETE(m_fun);\
				}\
			}\
		};\
		typedef typename std::list< CFunctionEventItem* >::iterator CFunctionEventItemListIter;\
	public:\
		CFunctionEvent(BSLib::Utility::CFunctionEventResult<R>* a_funRes = NULL, const R& a_default = 0) : m_funRes(a_funRes), m_default(a_default) {}\
		~CFunctionEvent() { _clear(); }\
		CFunctionEventHandle addFunctionEvent(R(*a_fun)(BSLIB_UTILITY_FUNCTION_TYPE_##N))\
		{\
			CFunctionEventItem* handle = new CFunctionEventItem();\
			if (handle == NULL) {\
				return NULL;\
			}\
			BSLib::Utility::CFunction<BSLIB_UTILITY_FUNCTION_TEMPLATE_PARA_##N>* fun = new BSLib::Utility::CFunction<BSLIB_UTILITY_FUNCTION_TEMPLATE_PARA_##N>(a_fun);\
			if (fun == NULL) {\
				BSLIB_SAFE_DELETE(handle);\
				return NULL;\
			}\
			handle->m_isValid = true;\
			handle->m_fun = fun;\
			m_functionAddList.push_back(handle);\
			return handle;\
		}\
		CFunctionEventHandle addFunctionEvent(BSLib::Utility::CFunction<BSLIB_UTILITY_FUNCTION_TEMPLATE_PARA_##N>& a_fun)\
		{\
			CFunctionEventItem* handle = new CFunctionEventItem();\
			if (handle == NULL) {\
				return NULL;\
			}\
			BSLib::Utility::CFunction<BSLIB_UTILITY_FUNCTION_TEMPLATE_PARA_##N>* fun = a_fun.clone();\
			if (fun == NULL) {\
				BSLIB_SAFE_DELETE(handle);\
				return NULL;\
			}\
			handle->m_isValid = true;\
			handle->m_fun = fun;\
			m_functionAddList.push_back(handle);\
			return handle;\
		}\
		template<class C>\
		CFunctionEventHandle addFunctionEvent(R(C::*a_fun)(BSLIB_UTILITY_FUNCTION_TYPE_##N), C* a_object)\
		{\
			CFunctionEventItem* handle = new CFunctionEventItem();\
			if (handle == NULL) {\
				return NULL;\
			}\
			BSLib::Utility::CFunctionObject<BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_PARA_##N>* fun = new BSLib::Utility::CFunctionObject<BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_PARA_##N>(a_fun, a_object);\
			if (fun == NULL) {\
				BSLIB_SAFE_DELETE(handle);\
				return NULL;\
			}\
			handle->m_isValid = true;\
			handle->m_fun = fun;\
			m_functionAddList.push_back(handle);\
			return handle;\
		}\
		void delFunctionEvent(CFunctionEventHandle& a_handle)\
		{\
			if (a_handle == NULL) {\
				return ;\
			}\
			CFunctionEventItem* item = (CFunctionEventItem*)a_handle;\
			if (item == NULL) {\
				return;\
			}\
			item->m_isValid = false;\
			a_handle = NULL;\
		}\
		bool empty()\
		{\
			return m_functionList.empty() && m_functionAddList.empty();\
		}\
		virtual R operator()(BSLIB_UTILITY_FUNCTION_TYPE_PARA_##N)\
		{\
			_updateFunctionEvent();\
			R res = m_default;\
			CFunctionEventItemListIter it = m_functionList.begin();\
			while (it != m_functionList.end()) {\
				CFunctionEventItem* item = *it;\
				if (item == NULL) {\
					it = m_functionList.erase(it);\
					continue;\
				}\
				if (item->m_isValid == false) {\
					it = m_functionList.erase(it);\
					BSLIB_SAFE_DELETE(item);\
					continue;\
				}\
				BSLib::Utility::CFunction<BSLIB_UTILITY_FUNCTION_TEMPLATE_PARA_##N>* fun = item->m_fun;\
				if (fun == NULL) {\
					++it;\
					continue;\
				}\
				res = (*fun)(BSLIB_UTILITY_FUNCTION_PARA_##N);\
				if (m_funRes == NULL) {\
					++it;\
					continue;\
				}\
				if (!(*m_funRes)(res)) {\
					break;\
				}\
				++it;\
			}\
			if (m_funRes != NULL) {\
				m_funRes->getFunctionResult(res);\
			}\
			return res;\
		}\
	protected:\
		void _clear()\
		{\
			CFunctionEventItemListIter it_addList = m_functionAddList.begin();\
			for (; it_addList != m_functionAddList.end(); ++it_addList) {\
				CFunctionEventItem* item = *it_addList;\
				if (item == NULL){\
					continue;\
				}\
				BSLIB_SAFE_DELETE(item);\
			}\
			m_functionAddList.clear();\
			CFunctionEventItemListIter it = m_functionList.begin();\
			for (; it != m_functionList.end(); ++it) {\
				CFunctionEventItem* item = *it;\
				if (item == NULL){\
					continue;\
				}\
				BSLIB_SAFE_DELETE(item);\
			}\
			m_functionList.clear();\
		}\
		void _updateFunctionEvent()\
		{\
			CFunctionEventItemListIter it_addList = m_functionAddList.begin();\
			for (; it_addList != m_functionAddList.end(); ++it_addList) {\
				CFunctionEventItem* item = *it_addList;\
				if (item == NULL){\
					continue;\
				}\
				m_functionList.push_back(item);\
			}\
			m_functionAddList.clear();\
		}\
	protected:\
		BSLib::Utility::CFunctionEventResult<R>* m_funRes;\
		std::list<CFunctionEventItem*> m_functionList;\
		std::list<CFunctionEventItem*> m_functionAddList;\
		R m_default;\
	};

#define BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_TYPE_0	
#define BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_TYPE_1	typename T1
#define BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_TYPE_2	BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_TYPE_1, typename T2
#define BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_TYPE_3	BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_TYPE_2, typename T3
#define BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_TYPE_4	BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_TYPE_3, typename T4
#define BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_TYPE_5	BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_TYPE_4, typename T5
#define BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_TYPE_6	BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_TYPE_5, typename T6
#define BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_TYPE_7	BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_TYPE_6, typename T7
#define BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_TYPE_8	BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_TYPE_7, typename T8
#define	BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_TYPE_9	BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_TYPE_8, typename T9

#define BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_0	void
#define BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_1	BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_0, T1
#define BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_2	BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_1, T2
#define BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_3	BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_2, T3
#define BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_4	BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_3, T4
#define BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_5	BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_4, T5
#define BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_6	BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_5, T6
#define BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_7	BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_6, T7
#define BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_8	BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_7, T8
#define BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_9	BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_8, T9

#define BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_VOID_PARA_0	void, C
#define BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_VOID_PARA_1	BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_VOID_PARA_0, T1
#define BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_VOID_PARA_2	BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_VOID_PARA_1, T2
#define BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_VOID_PARA_3	BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_VOID_PARA_2, T3
#define BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_VOID_PARA_4	BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_VOID_PARA_3, T4
#define BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_VOID_PARA_5	BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_VOID_PARA_4, T5
#define BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_VOID_PARA_6	BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_VOID_PARA_5, T6
#define BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_VOID_PARA_7	BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_VOID_PARA_6, T7
#define BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_VOID_PARA_8	BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_VOID_PARA_7, T8
#define BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_VOID_PARA_9	BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_VOID_PARA_8, T9

#define BSLIB_UTILITY_FUNCTION_EVENT_SPECIAL_VOID(N, TYPENAME)\
	template <BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_TYPE_##N>\
	class CFunctionEvent<BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_##N>\
	{\
	protected:\
		struct CFunctionEventItem\
		{\
			bool m_isValid;\
			BSLib::Utility::CFunction<BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_##N>* m_fun;\
			CFunctionEventItem() : m_isValid(NULL), m_fun(NULL) { }\
			~CFunctionEventItem()\
			{\
				if (m_fun != NULL) {\
					BSLIB_SAFE_DELETE(m_fun);\
				}\
			}\
		};\
		typedef TYPENAME std::list< CFunctionEventItem* >::iterator CFunctionEventItemListIter;\
	public:\
		CFunctionEvent() {}\
		~CFunctionEvent() { _clear(); }\
		CFunctionEventHandle addFunctionEvent(void(*a_fun)(BSLIB_UTILITY_FUNCTION_TYPE_##N))\
		{\
			CFunctionEventItem* handle = new CFunctionEventItem();\
			if (handle == NULL) {\
				return NULL;\
			}\
			BSLib::Utility::CFunction<BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_##N>* fun = new BSLib::Utility::CFunction<BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_##N>(a_fun);\
			if (fun == NULL) {\
				BSLIB_SAFE_DELETE(handle);\
				return NULL;\
			}\
			handle->m_isValid = true;\
			handle->m_fun = fun;\
			m_functionAddList.push_back(handle);\
			return handle;\
		}\
		CFunctionEventHandle addFunctionEvent(BSLib::Utility::CFunction<BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_##N>& a_fun)\
		{\
			CFunctionEventItem* handle = new CFunctionEventItem();\
			if (handle == NULL) {\
				return NULL;\
			}\
			BSLib::Utility::CFunction<BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_##N>* fun = a_fun.clone();\
			if (fun == NULL) {\
				BSLIB_SAFE_DELETE(handle);\
				return NULL;\
			}\
			handle->m_isValid = true;\
			handle->m_fun = fun;\
			m_functionAddList.push_back(handle);\
			return handle;\
		}\
		template<class C>\
		CFunctionEventHandle addFunctionEvent(void(C::*a_fun)(BSLIB_UTILITY_FUNCTION_TYPE_##N), C* a_object)\
		{\
			CFunctionEventItem* handle = new CFunctionEventItem();\
			if (handle == NULL) {\
				return NULL;\
			}\
			BSLib::Utility::CFunctionObject<BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_VOID_PARA_##N>* fun = new BSLib::Utility::CFunctionObject<BSLIB_UTILITY_FUNCTION_OBJECT_TEMPLATE_VOID_PARA_##N>(a_fun, a_object);\
			if (fun == NULL) {\
				BSLIB_SAFE_DELETE(handle);\
				return NULL;\
			}\
			handle->m_isValid = true;\
			handle->m_fun = fun;\
			m_functionAddList.push_back(handle);\
			return handle;\
		}\
		void delFunctionEvent(CFunctionEventHandle& a_handle)\
		{\
			if (a_handle == NULL) {\
				return ;\
			}\
			CFunctionEventItem* item = (CFunctionEventItem*)a_handle;\
			if (item == NULL) {\
				return;\
			}\
			item->m_isValid = false;\
			a_handle = NULL;\
		}\
		bool empty()\
		{\
			return m_functionList.empty() && m_functionAddList.empty();\
		}\
		void operator()(BSLIB_UTILITY_FUNCTION_TYPE_PARA_##N)\
		{\
			_updateFunctionEvent();\
			CFunctionEventItemListIter it = m_functionList.begin();\
			while (it != m_functionList.end()) {\
			CFunctionEventItem* item = *it;\
				if (item == NULL) {\
					it = m_functionList.erase(it);\
					continue;\
				}\
				if (item->m_isValid == false) {\
					it = m_functionList.erase(it);\
					BSLIB_SAFE_DELETE(item);\
					continue;\
				}\
				BSLib::Utility::CFunction<BSLIB_UTILITY_FUNCTION_TEMPLATE_VOID_PARA_##N>* fun = item->m_fun;\
				if (fun == NULL) {\
					++it;\
					continue;\
				}\
				(*fun)(BSLIB_UTILITY_FUNCTION_PARA_##N);\
				++it;\
			}\
		}\
	protected:\
		void _clear()\
		{\
			CFunctionEventItemListIter it_addList = m_functionAddList.begin();\
			for (; it_addList != m_functionAddList.end(); ++it_addList) {\
				CFunctionEventItem* item = *it_addList;\
				if (item == NULL){\
					continue;\
				}\
				BSLIB_SAFE_DELETE(item);\
			}\
			m_functionAddList.clear();\
			CFunctionEventItemListIter it = m_functionList.begin();\
			for (; it != m_functionList.end(); ++it) {\
				CFunctionEventItem* item = *it;\
				if (item == NULL){\
					continue;\
				}\
				BSLIB_SAFE_DELETE(item);\
			}\
			m_functionList.clear();\
		}\
		void _updateFunctionEvent()\
		{\
			CFunctionEventItemListIter it_addList = m_functionAddList.begin();\
			for (; it_addList != m_functionAddList.end(); ++it_addList) {\
				CFunctionEventItem* item = *it_addList;\
				if (item == NULL){\
					continue;\
				}\
				m_functionList.push_back(item);\
			}\
			m_functionAddList.clear();\
		}\
	protected:\
		std::list<CFunctionEventItem*> m_functionList;\
		std::list<CFunctionEventItem*> m_functionAddList;\
	};


namespace BSLib
{

namespace Utility
{

typedef void* CFunctionEventHandle;

template <class TYPE>
class CFunctionEventResult
{
public:

	/// @brief  operator()
	//			CFunctionEvent每次函数调用返回值处理
	/// @return bool CFunctionEvent是否继续执行
	/// @param  a_result 调用函数返回值
	virtual bool operator()(TYPE a_result) 
	{
		return true;
	}

	virtual void getFunctionResult(TYPE& a_result)
	{
		;
	}
};

BSLIB_UTILITY_FUNCTION_EVENT(9);

BSLIB_UTILITY_FUNCTION_EVENT_SPECIAL(0);
BSLIB_UTILITY_FUNCTION_EVENT_SPECIAL(1);
BSLIB_UTILITY_FUNCTION_EVENT_SPECIAL(2);
BSLIB_UTILITY_FUNCTION_EVENT_SPECIAL(3);
BSLIB_UTILITY_FUNCTION_EVENT_SPECIAL(4);
BSLIB_UTILITY_FUNCTION_EVENT_SPECIAL(5);
BSLIB_UTILITY_FUNCTION_EVENT_SPECIAL(6);
BSLIB_UTILITY_FUNCTION_EVENT_SPECIAL(7);
BSLIB_UTILITY_FUNCTION_EVENT_SPECIAL(8);

BSLIB_UTILITY_FUNCTION_EVENT_SPECIAL_VOID(0, );
BSLIB_UTILITY_FUNCTION_EVENT_SPECIAL_VOID(1, typename);
BSLIB_UTILITY_FUNCTION_EVENT_SPECIAL_VOID(2, typename);
BSLIB_UTILITY_FUNCTION_EVENT_SPECIAL_VOID(3, typename);
BSLIB_UTILITY_FUNCTION_EVENT_SPECIAL_VOID(4, typename);
BSLIB_UTILITY_FUNCTION_EVENT_SPECIAL_VOID(5, typename);
BSLIB_UTILITY_FUNCTION_EVENT_SPECIAL_VOID(6, typename);
BSLIB_UTILITY_FUNCTION_EVENT_SPECIAL_VOID(7, typename);
BSLIB_UTILITY_FUNCTION_EVENT_SPECIAL_VOID(8, typename);
BSLIB_UTILITY_FUNCTION_EVENT_SPECIAL_VOID(9, typename);

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> class CFunctionEvent;


}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_FUNCTIONEVENT_H__



