#ifndef __BSLIB_UTILITY_FILE_FILEINFO_H__
#define __BSLIB_UTILITY_FILE_FILEINFO_H__

#include <BSLib/utility/baseDef.h>
#include <BSLib/utility/dateTime.h>

namespace BSLib
{

namespace Utility
{

class BSLIB_UTILITY_API CFileInfo
{
public:
	CFileInfo(const std::string& fileName = "");
	virtual ~CFileInfo();

public:
	void standardization();
	bool isExist();
	std::string getFullPath();
	std::string getPath();
	std::string getFullName();
	std::string getName();
	std::string getExtension();
	long getLength();
	bool getLastModifyTime(CDateTime& dateTime);
	bool isReadOnly();
	bool copyFile(const std::string& dst);
	bool renameFile(const std::string& dst);
	bool deleteFile();

public:
	/// @brief Ŀ¼��׼������window�����н�'/'ת���ɡ�\\����linu�����н�'\\'ת����'/'
	/// @return void
	/// @param fileName
	static void standardization(std::string& fileName);

	/// @brief �ж��ļ��Ƿ����
	/// @return bool
	/// @param fileName
	static bool isExist(const std::string& fileName);

    /// @brief ��ȡ�ļ�������Ŀ¼
    /// @return std::string
    /// @param fileName
    static std::string getFullPath(const std::string& fileName);

	/// @brief ��ȡ�ļ����ڵ�Ŀ¼
	/// @return std::string
	/// @param fileName
	static std::string getPath(const std::string& fileName);

	/// @brief ��ȡ�����ļ��� �ļ���+��չ��
	/// @return std::string
	/// @param fileName
	static std::string getFullName(const std::string& fileName);

    /// @brief ��ȡ�ļ�����������չ��
    /// @return std::string
    /// @param fileName
    static std::string getName(const std::string& fileName);

	/// @brief ��ȡ�ļ���չ��
	/// @return std::string
	/// @param fileName
	static std::string getExtension(const std::string& fileName);

	/// @brief ��ȡ�ļ�����
	/// @return unsigned int
	/// @param fileName
	static long getLength(const std::string& fileName);

	
	/// @brief ��ȡ���һ���޸��ļ�ʱ��
	/// @return bool
	/// @param fileName
	/// @param datetime
	static bool getLastModifyTime(const std::string& fileName, CDateTime& dateTime);

	/// @brief �ж��ļ��Ƿ���ֻ������
	/// @return bool
	/// @param fileName
	static bool isReadOnly(const std::string& fileName);

	/// @brief �����ļ�
	/// @return bool
	/// @param dst
	/// @param src
	static bool copyFile(const std::string& dst, const std::string& src);

	/// @brief  renameFile ���ļ���
	/// @return bool
	/// @param  dst
	/// @param  src
	static bool renameFile(const std::string& dst, const std::string& src);

	/// @brief ɾ���ļ�
	/// @return bool
	/// @param fileName
	static bool deleteFile(const std::string& fileName);

private:
	std::string m_fileName;
};

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_FILE_FILEINFO_H__

