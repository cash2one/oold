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
	/// @brief  �����������
	/// @return void
	static void setRandomSeed(BSLib::uint32 randomSeed);

	/// @brief  ��[minNum, manNum]֮���ȡ�����
	/// @return int �����
	/// @param  minNum ��Сֵ
	/// @param  maxNum ���ֵ
	static int randomBetween(int minNum, int maxNum);

	/// @brief  ��ȡ����֮���ĸ���
	/// @return bool �Ƿ�ѡ��
	/// @param  upNum ����
	/// @param  downNum ��ĸ
	static bool selectByOdds(BSLib::uint32 upNum, BSLib::uint32 downNum);

	/// @brief  ��ȡ�ٷ�֮���ĸ���
	/// @return bool �Ƿ�ѡ��
	/// @param  rate �ٷ�֮���ĸ���
	static bool selectByPercent(BSLib::uint32 rate)
	{
		return selectByOdds(rate, 100);
	}

	/// @brief  ��ȡǧ��֮���ĸ���
	/// @return bool �Ƿ�ѡ��
	/// @param  rate ǧ��֮���ĸ���
	static bool selectByK(BSLib::uint32 rate)
	{
		return selectByOdds(rate, 1000);
	}

	/// @brief  ��ȡ���֮���ĸ���
	/// @return bool �Ƿ�ѡ��
	/// @param  rate ���֮���ĸ���
	static bool selectBy10K(BSLib::uint32 rate)
	{
		return selectByOdds(rate, 10000);
	}

	/// @brief  ��ȡʮ���֮���ĸ���
	/// @return bool �Ƿ�ѡ��
	/// @param  rate ʮ���֮���ĸ���
	static bool selectBy100K(BSLib::uint32 rate)
	{
		return selectByOdds(rate, 100000);
	}
	
	/// @brief  ��ȡ�����֮���ĸ���
	/// @return bool �Ƿ�ѡ��
	/// @param  rate �����֮���ĸ���
	static bool selectByM(BSLib::uint32 rate)
	{
		return selectByOdds(rate, 1000000);
	}
};

}//Utility

}//BSLib

#endif // __BSLIB_UTILITY_BUFFER_H__
