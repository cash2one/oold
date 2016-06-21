#ifndef __BSLIB_UTILITY_STRING_H__
#define __BSLIB_UTILITY_STRING_H__

#include <algorithm>
#include <BSLib/utility/baseDef.h>

namespace BSLib
{

namespace Utility
{

class BSLIB_UTILITY_API CSpecialCharA
{
protected:
	static const std::string::value_type m_A;
	static const std::string::value_type m_Z;
	static const std::string::value_type m_a;
	static const std::string::value_type m_z;
	static const std::string::value_type m_percent;
};

class BSLIB_UTILITY_API CSpecialCharW
{
protected:
	static const std::wstring::value_type m_A;
	static const std::wstring::value_type m_Z;
	static const std::wstring::value_type m_a;
	static const std::wstring::value_type m_z;
	static const std::wstring::value_type m_percent;
};

template<class BaseStringType, class SpecialCharType>
class CBasicString : public BaseStringType, public SpecialCharType
{
public:
	typedef typename BaseStringType::value_type ValueType;
	typedef typename BaseStringType::size_type SizeType;

public:
	/// @brief 转换成小写
	/// @return void
	void toLower()
	{
		ValueType fixedValue = SpecialCharType::m_a - SpecialCharType::m_A;
		typename BaseStringType::iterator it = BaseStringType::begin();
		for(; it != BaseStringType::end(); ++it){
			if (*it >= SpecialCharType::m_A && *it <= SpecialCharType::m_Z){
				*it += fixedValue;
			}
		}
	}

	/// @brief 转换成大写
	/// @return void
	void toUpper()
	{
		ValueType fixedValue = SpecialCharType::m_a - SpecialCharType::m_A;
		typename BaseStringType::iterator it = BaseStringType::begin();
		for(; it != BaseStringType::end(); ++it){
			if (*it >= SpecialCharType::m_a && *it <= SpecialCharType::m_z){
				*it -= fixedValue;
			}
		}
	}

	/// @brief 不分大小写，比较
	/// @return bool true = 相等
	/// @param str
	bool compareNoCase(const BaseStringType& str)
	{
		SizeType strSize = BaseStringType::size();
		if (str.size() != strSize){
			return false;
		}
		int fixedValue1 = SpecialCharType::m_a - SpecialCharType::m_A;
		int fixedValue2 = -fixedValue1;

		for (uint32 i=0; i<strSize; ++i) {
			int tmp = str[i] - BaseStringType::operator[](i);
			if (tmp == 0 || tmp == fixedValue1 || tmp == fixedValue2) {
				continue;
			}
			return false;
		}
		return true;
	}

	/// @brief 替换所有strOld字符串
	/// @return unsigned int 替换的次数
	/// @param strOld
	/// @param strNew
	uint32 replace(const BaseStringType& strOld, const BaseStringType& strNew)
	{
		uint32 nCount = 0;
		typename BaseStringType::iterator itBegin = std::search(BaseStringType::begin(), BaseStringType::end(), strOld.begin(), strOld.end());
		while(itBegin != BaseStringType::end())	{
			typename BaseStringType::iterator itEnd = itBegin + strOld.size();
			BaseStringType::replace(itBegin, itEnd, strNew);
			itBegin = std::search(BaseStringType::begin() + strNew.size(), BaseStringType::end(), strOld.begin(), strOld.end());
			++nCount;
		}
		return nCount;
	}
	uint32 replace(const ValueType chOld, const ValueType chNew)
	{
		uint32 nCount = 0;
		typename BaseStringType::iterator it = BaseStringType::begin();
		for(; it != BaseStringType::end(); ++it){
			if (*it == chOld){
				*it = chNew;
				++nCount;
			}
		}
		return nCount;
	}

	/// @brief 返回一个从右边边起始nCount个字符的子字符串，[length() - nCount，nCount]，类似于std::substr(length() - nCount，nCount)
	/// @return BaseStringType
	/// @param nCount
	BaseStringType right(SizeType nCount)  const
	{
		if (nCount >= BaseStringType::size()){
			return *this;
		}
		return BaseStringType::substr(BaseStringType::size() - nCount, nCount);

	}
	/// @brief 返回一个从左边起始nCount个字符的子字符串，类似于std::substr(0，nCount)
	/// @return BaseStringType
	/// @param nCount 启始位置
	BaseStringType left(SizeType nCount)
	{
		if (nCount >= BaseStringType::size()){
			return *this;
		}
		return BaseStringType::substr(0, nCount);
	}
	
	/// @brief 类似于std::substr(iFirst，nCount)
	/// @return BaseStringType
	/// @param iFirst
	/// @param nCount
	BaseStringType mid(SizeType iFirst, SizeType nCount) const
	{
		if (iFirst > BaseStringType::size()){
			iFirst = BaseStringType::size();
		}
		if (nCount + iFirst > BaseStringType::size()){
			nCount = BaseStringType::size() - iFirst;
		}
		return BaseStringType::substr(iFirst, nCount);
	}

	
	/// @brief 按照strKeyword拆分字符串
	/// @return int
	/// @param subStringList
	/// @param strKeyword
	template<class SubStringType>
	int split(std::vector<SubStringType>& subStringList, const BaseStringType& strKeyword) const
	{
		SizeType npos = BaseStringType::find(strKeyword);
		SizeType nlastpos = 0;

		while(npos != BaseStringType::npos)
		{
			subStringList.push_back(mid(nlastpos, npos - nlastpos));
			nlastpos = npos + strKeyword.size();
			npos = BaseStringType::find(strKeyword, nlastpos);
		}

		if (nlastpos < BaseStringType::length())
		{
			subStringList.push_back(mid(nlastpos, BaseStringType::length() - nlastpos));
		}
		return subStringList.size();
	}

	/// @brief 按照separator拆分字符串
	/// @return int 拆分的个数
	/// @param subStringList 子字符串集合
	/// @param separator 拆分字符
	template<class SubStringType>
	int split(std::vector<SubStringType>& subStringList, ValueType separator) const
	{
		SubStringType tmpStr;

		subStringList.clear();
		
		typename BaseStringType::const_iterator it = BaseStringType::begin();
		for (; it != BaseStringType::end(); ++it){
			if (*it == separator){
				if (tmpStr.empty()){
					continue;
				}
				subStringList.push_back(tmpStr);
				tmpStr.clear();
				continue;
			}
			tmpStr.push_back(*it);
		}
		if (!(tmpStr.empty())){
			subStringList.push_back(tmpStr);
			tmpStr.clear();
		}
		return (int)subStringList.size();
	}

	/// @brief  split 按照separator集合拆分字符串,返回拆分的个数
	/// @return int 拆分的个数
	/// @param  subStringList 子字符串集合
	/// @param  separators 拆分字符集合
	/// @param  count 拆分字符个数
	template<class SubStringType>
	int split(std::vector<SubStringType>& subStringList, ValueType separators[], int count) const
	{
		SubStringType tmpStr;

		subStringList.clear();

		typename BaseStringType::const_iterator it = BaseStringType::begin();
		for (; it != BaseStringType::end(); ++it){
			bool isseparator = false;
			for (int i=0; i<count; ++i) {
				if (*it == separators[i]) {
					isseparator = true;
					break;
				}
			}
			if (isseparator){
				if (tmpStr.empty()){
					continue;
				}
				subStringList.push_back(tmpStr);
				tmpStr.clear();
				continue;
			}
			tmpStr.push_back(*it);
		}
		if (!(tmpStr.empty())){
			subStringList.push_back(tmpStr);
			tmpStr.clear();
		}
		return subStringList.size();
	}
	
	
	/// @brief 从左边和右边去掉连续的target，直到第一个字符不为 target
	///        如原字符串aaabbaa,target为a,则返回bb
	/// @return BSLib::Utility::CBasicString
	/// @param target
	void trim(ValueType target = ' ')
	{
		trimLeft(target);
		trimRight(target);
	}

	/// @brief 从左边去掉连续的target，直到第一个字符不为 target
	///        如原字符串aaabbaa,target为a,则返回bbaa
	/// @param target
	void trimLeft(ValueType target = ' ')
	{
		typename BaseStringType::iterator it = BaseStringType::begin();
		while (it != BaseStringType::end()){
			if (*it == target){
				++it;
				continue;
			}
			break;
		}
		BaseStringType::erase(BaseStringType::begin(), it);
	}

	/// @brief 从右边去掉连续的target，直到第一个字符不为 target
	///        如原字符串aaabbaa,target为a,则返回aaabb
	/// @return CStringA
	/// @param target
	void trimRight(ValueType target = ' ')
	{
		typename BaseStringType::iterator it = BaseStringType::end();
		if (BaseStringType::begin() == it) {
			return ;
		}
		--it;

		while (it != BaseStringType::begin()){
			if (*it == target){
				--it;
			}
			break;
		}
		if (it == BaseStringType::begin()) {
			if (*it == target){
				BaseStringType::erase(it, BaseStringType::end());
				return ;
			}
		}
		++it;
		if (it == BaseStringType::end()) {
			return ;
		}
		BaseStringType::erase(it, BaseStringType::end());
		
	}

protected:
	bool _formatSafeCheck(uint32 uParamCnt, const ValueType* pszFormat)
	{
		if (pszFormat == NULL) {
			return false;
		}
		uint32 nCnt = 0;
		int i=0;
		for (; pszFormat[i] != 0; ++i) {
			if (pszFormat[i] == SpecialCharType::m_percent) {
				if (pszFormat[i+1] == SpecialCharType::m_percent) {
					++i;
					continue;
				}
				++nCnt;
			}
		}
		if (i == 0) {
			return true;
		}
		if (pszFormat[i-1] == SpecialCharType::m_percent) {
			if (i-2 < 0) {
				return false;
			}
			if (pszFormat[i-2] != SpecialCharType::m_percent) {
				return false;
			}
		}
		return nCnt == uParamCnt;
	}
};

class CStringA;
class CStringW;

class BSLIB_UTILITY_API CStringA : public CBasicString<std::string, CSpecialCharA>
{
public:
	CStringA() {}

	template<class Type>
	CStringA(const Type& data)
	{
		operator =(data);
	}

	/// @brief 转换成宽字符
	/// @return CStringW
	CStringW toWideString() const;

	/// @brief 
	/// @return void
	/// @param uParamCnt
	/// @param pszFormat
	/// @param 
	void format(uint32 uParamCnt, const ValueType* pszFormat, ...);
	void format(const ValueType* pszFormat, ...);

public:
	CStringA& operator =(const char data[]);
	CStringA& operator =(const wchar_t data[]);
	CStringA& operator =(const CStringA& data);
	CStringA& operator =(const CStringW& data);
	CStringA& operator =(const std::string& data);
	CStringA& operator =(const std::wstring& data);
	CStringA& operator =(const int8& data);
	CStringA& operator =(const uint8& data);
	CStringA& operator =(const int16& data);
	CStringA& operator =(const uint16& data);
	CStringA& operator =(const int32& data);
	CStringA& operator =(const uint32& data);
	CStringA& operator =(const int64& data);
	CStringA& operator =(const uint64& data);	
	CStringA& operator =(const float& data);
	CStringA& operator =(const double& data);

	template<class Type>
	CStringA& operator =(const Type& data);

	CStringA& operator <<(const char data[]);
	CStringA& operator <<(const wchar_t data[]);
	CStringA& operator <<(const CStringA& data);
	CStringA& operator <<(const CStringW& data);
	CStringA& operator <<(const std::string& data);
	CStringA& operator <<(const std::wstring& data);
	CStringA& operator <<(const int8& data);
	CStringA& operator <<(const uint8& data);
	CStringA& operator <<(const int16& data);
	CStringA& operator <<(const uint16& data);
	CStringA& operator <<(const int32& data);
	CStringA& operator <<(const uint32& data);
	CStringA& operator <<(const int64& data);
	CStringA& operator <<(const uint64& data);	
	CStringA& operator <<(const float& data);
	CStringA& operator <<(const double& data);

	template<class Type>
	CStringA& operator <<(const Type& data);

	const CStringA& operator >>(CStringA& data) const ;
	const CStringA& operator >>(CStringW& data) const ;
	const CStringA& operator >>(std::string& data) const ;
	const CStringA& operator >>(std::wstring& data) const ;
	const CStringA& operator >>(int8& data) const;
	const CStringA& operator >>(uint8& data) const;
	const CStringA& operator >>(int16& data) const;
	const CStringA& operator >>(uint16& data) const;
	const CStringA& operator >>(int32& data) const;
	const CStringA& operator >>(uint32& data) const;
	const CStringA& operator >>(int64& data) const;
	const CStringA& operator >>(uint64& data) const;
	const CStringA& operator >>(double& data) const;
	const CStringA& operator >>(float& data) const;

	template<class Type>
	const CStringA& operator >>(Type& data) const;
};

class BSLIB_UTILITY_API CStringW : public CBasicString<std::wstring, CSpecialCharW>
{
public:
	CStringW() {}

	template<class Type>
	CStringW(Type data)
	{
		operator =(data);
	}

	/// @brief  转换成窄字符
	/// @return CStringA&
	CStringA toNarrowString() const;

	/// @brief 
	/// @return void
	/// @param uParamCnt
	/// @param pszFormat
	/// @param 
	void format(uint32 uParamCnt, const ValueType* pszFormat, ...);
	void format(const ValueType* pszFormat, ...);

public:
	CStringW& operator =(const char data[]);
	CStringW& operator =(const wchar_t data[]);
	CStringW& operator =(const CStringA& data);
	CStringW& operator =(const CStringW& data);
	CStringW& operator =(const std::string& data);
	CStringW& operator =(const std::wstring& data);
	CStringW& operator =(const int8& data);
	CStringW& operator =(const uint8& data);
	CStringW& operator =(const int16& data);
	CStringW& operator =(const uint16& data);
	CStringW& operator =(const int32& data);
	CStringW& operator =(const uint32& data);
	CStringW& operator =(const int64& data);
	CStringW& operator =(const uint64& data);	
	CStringW& operator =(const float& data);
	CStringW& operator =(const double& data);

	template<class Type>
	CStringW& operator =(const Type& data);

	CStringW& operator <<(const char data[]);
	CStringW& operator <<(const wchar_t data[]);
	CStringW& operator <<(const CStringA& data);
	CStringW& operator <<(const CStringW& data);
	CStringW& operator <<(const std::string& data);
	CStringW& operator <<(const std::wstring& data);
	CStringW& operator <<(const int8& data);
	CStringW& operator <<(const uint8& data);
	CStringW& operator <<(const int16& data);
	CStringW& operator <<(const uint16& data);
	CStringW& operator <<(const int32& data);
	CStringW& operator <<(const uint32& data);
	CStringW& operator <<(const int64& data);
	CStringW& operator <<(const uint64& data);	
	CStringW& operator <<(const float& data);
	CStringW& operator <<(const double& data);

	template<class Type>
	CStringW& operator <<(const Type& data);

	const CStringW& operator >>(CStringA& data) const ;
	const CStringW& operator >>(CStringW& data) const ;
	const CStringW& operator >>(std::string& data) const ;
	const CStringW& operator >>(std::wstring& data) const ;
	const CStringW& operator >>(int8& data) const;
	const CStringW& operator >>(uint8& data) const;
	const CStringW& operator >>(int16& data) const;
	const CStringW& operator >>(uint16& data) const;
	const CStringW& operator >>(int32& data) const;
	const CStringW& operator >>(uint32& data) const;
	const CStringW& operator >>(int64& data) const;
	const CStringW& operator >>(uint64& data) const;
	const CStringW& operator >>(double& data) const;
	const CStringW& operator >>(float& data) const;

	template<class Type>
	const CStringW& operator >>(Type& data) const;
};

}//Utility

}//BSLib

#endif //__BSLIB_UTILITY_STRING_H__

