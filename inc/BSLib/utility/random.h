//////////////////////////////////////////////////////////////////////
//	created:	2012/10/22
//	filename:	BSLib\utility\random.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UTILITY_RANDOM_H__
#define __BSLIB_UTILITY_RANDOM_H__

#include <BSLib/utility/baseDef.h>

namespace BSLib
{

namespace Utility
{

class BSLIB_UTILITY_API CRandom
{
public:
	/// @brief  设置随机种子
	/// @return void
	static void setRandomSeed(BSLib::uint32 randomSeed);

	/// @brief  在[minNum, manNum]之间获取随机数
	/// @return int 随机数
	/// @param  minNum 最小值
	/// @param  maxNum 最大值
	static int randomBetween(int minNum, int maxNum);

	/// @brief  获取几分之几的概率
	/// @return bool 是否选中
	/// @param  upNum 分子
	/// @param  downNum 分母
	static bool selectByOdds(BSLib::uint32 upNum, BSLib::uint32 downNum);

	/// @brief  获取百分之几的概率
	/// @return bool 是否选中
	/// @param  rate 百分之几的概率
	static bool selectByPercent(BSLib::uint32 rate)
	{
		return selectByOdds(rate, 100);
	}

	/// @brief  获取千分之几的概率
	/// @return bool 是否选中
	/// @param  rate 千分之几的概率
	static bool selectByK(BSLib::uint32 rate)
	{
		return selectByOdds(rate, 1000);
	}

	/// @brief  获取万分之几的概率
	/// @return bool 是否选中
	/// @param  rate 万分之几的概率
	static bool selectBy10K(BSLib::uint32 rate)
	{
		return selectByOdds(rate, 10000);
	}

	/// @brief  获取十万分之几的概率
	/// @return bool 是否选中
	/// @param  rate 十万分之几的概率
	static bool selectBy100K(BSLib::uint32 rate)
	{
		return selectByOdds(rate, 100000);
	}
	
	/// @brief  获取百万分之几的概率
	/// @return bool 是否选中
	/// @param  rate 百万分之几的概率
	static bool selectByM(BSLib::uint32 rate)
	{
		return selectByOdds(rate, 1000000);
	}
};

}//Utility

}//BSLib

#endif // __BSLIB_UTILITY_BUFFER_H__
