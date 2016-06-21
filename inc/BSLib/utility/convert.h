#ifndef __BSLIB_UTILITY_CONVERT_H__
#define __BSLIB_UTILITY_CONVERT_H__

#include <BSLib/utility/baseDef.h>

namespace BSLib
{

namespace Utility
{

//////////////////////////////////////////////////////////////////////////
/// @brief �ַ���ת��
//////////////////////////////////////////////////////////////////////////
class BSLIB_UTILITY_API CConvert
{
public:
	/// @brief ��UTF-8����ת����UNICODE����
	/// @return int д�뻺�����Ŀ��ַ�����
	/// @param outBuff ���UNICODE���뻺����
	/// @param buffSize �����������С(��λ:sizeof(wchar_t))
	/// @param text ����UTF-8�����ı�
	/// @param textSize ��������ı���С
	static int utf8ToUnicode(wchar_t* outBuff, int buffSize, const char* text, int textSize);
	static int utf8ToUnicode(std::wstring& outBuff, const std::string& text);
	
	/// @brief ��UNICODE����ת����UTF-8����
	/// @return int д�뻺�������ֽ���
	/// @param outBuff ���UTF-8���뻺����
	/// @param buffSize �����������С
	/// @param text ����UNICODE�����ı�
	/// @param textSize ��������ı���С(��λ:sizeof(wchar_t))
	static int unicodeToUTF8(char* outBuff, int buffSize, const wchar_t* text, int textSize);
	static int unicodeToUTF8(std::string& outBuff, const std::wstring& text);

	/// @brief ��UNICODE����ת����GB2312����
	/// @return int д�뻺�������ֽ���
	/// @param outBuff ���GB2312���뻺����
	/// @param buffSize �����������С
	/// @param text ����UNICODE�����ı�
	/// @param textSize ��������ı���С(��λ:sizeof(wchar_t))
	static int unicodeToGB2312(char* outBuff, int buffSize, const wchar_t* text, int textSize);
	static int unicodeToGB2312(std::string& outBuff, const std::wstring& text);

	/// @brief ��GB2312����ת����UNICODE����
	/// @return int д�뻺�����Ŀ��ַ�����
	/// @param outBuff ���UNICODE���뻺����
	/// @param buffSize �����������С(��λ:sizeof(wchar_t))
	/// @param text ����GB2312�����ı�
	/// @param textSize ��������ı���С
	static int gb2312ToUnicode(wchar_t* outBuff, int buffSize, const char* text, int textSize);
	static int gb2312ToUnicode(std::wstring& outBuff, const std::string& text);

	/// @brief ��GB2312����ת����UTF-8����
	/// @return int д�뻺�������ֽ���
	/// @param outBuff ���UTF-8���뻺����
	/// @param buffSize �����������С
	/// @param text ����GB2312�����ı�
	/// @param textSize ��������ı���С
	static int gb2312ToUTF8(char* outBuff, int buffSize, const char* text, int textSize);
	static int gb2312ToUTF8(std::string& outBuff, const std::string& text);

	/// @brief ��UTF-8����ת����GB2312����
	/// @return int д�뻺�������ֽ���
	/// @param outBuff ���GB2312���뻺����
	/// @param buffSize �����������С(�ֽ�)
	/// @param text ����UTF-8�����ı�
	/// @param textSize ��������ı���С(�ֽ�)
	static int utf8ToGB2312(char* outBuff, int buffSize, const char* text, int textSize);
	static int utf8ToGB2312(std::string& outBuff, const std::string& text);

	static std::string toStringA(const int32 n);
	static std::string toStringA(const uint32 n);
	static std::string toStringA(const int64 n);
	static std::string toStringA(const uint64 n);
	static std::string toStringA(const float f);
	static std::string toStringA(const double d);

	static std::wstring toStringW(const int32 n);
	static std::wstring toStringW(const uint32 n);
	static std::wstring toStringW(const int64 n);
	static std::wstring toStringW(const uint64 n);
	static std::wstring toStringW(const float f);
	static std::wstring toStringW(const double d);

	static int32  toInt32(const std::string& str);
	static uint32 toUint32(const std::string& str);
	static int64  toInt64(const std::string& str);
	static uint64 toUint64(const std::string& str);
	static float  toFloat(const std::string& str);
	static double toDouble(const std::string& str);

	static int32  toInt32(const std::wstring& str);
	static uint32 toUint32(const std::wstring& str);
	static int64  toInt64(const std::wstring& str);
	static uint64 toUint64(const std::wstring& str);
	static float  toFloat(const std::wstring& str);
	static double toDouble(const std::wstring& str);
};

}//Utility

}//BSLib

#endif // __BSLIB_UTILITY_CONVERT_H__

