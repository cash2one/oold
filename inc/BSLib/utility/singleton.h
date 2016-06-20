//////////////////////////////////////////////////////////////////////
//	created:	2011/04/12
//	filename:	BSLib\utility\singleton.h
//	author:		mazhejiang
//
///	@brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UTILITY_SINGLETON_H__
#define __BSLIB_UTILITY_SINGLETON_H__

//动态库中使用的单件
#define BSLIB_SINGLETON_DECLARE(classname) \
	public:\
	static classname& singleton();

#define BSLIB_SINGLETON_DEFINE(classname) \
	classname& classname::singleton()\
	{\
		static classname singleton;\
		return singleton;\
	}\

#endif//__BSLIB_UTILITY_SINGLETON_H__
