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
	/// @brief 目录标准化，在window环境中将'/'转换成‘\\’在linu环境中将'\\'转换成'/'
	/// @return void
	/// @param fileName
	static void standardization(std::string& fileName);

	/// @brief 判断文件是否存在
	/// @return bool
	/// @param fileName
	static bool isExist(const std::string& fileName);

    /// @brief 获取文件完整的目录
    /// @return std::string
    /// @param fileName
    static std::string getFullPath(const std::string& fileName);

	/// @brief 获取文件所在的目录
	/// @return std::string
	/// @param fileName
	static std::string getPath(const std::string& fileName);

	/// @brief 获取完整文件名 文件名+扩展名
	/// @return std::string
	/// @param fileName
	static std::string getFullName(const std::string& fileName);

    /// @brief 获取文件名，不带扩展名
    /// @return std::string
    /// @param fileName
    static std::string getName(const std::string& fileName);

	/// @brief 获取文件扩展名
	/// @return std::string
	/// @param fileName
	static std::string getExtension(const std::string& fileName);

	/// @brief 获取文件长度
	/// @return unsigned int
	/// @param fileName
	static long getLength(const std::string& fileName);

	
	/// @brief 获取最后一次修改文件时间
	/// @return bool
	/// @param fileName
	/// @param datetime
	static bool getLastModifyTime(const std::string& fileName, CDateTime& dateTime);

	/// @brief 判断文件是否是只读类型
	/// @return bool
	/// @param fileName
	static bool isReadOnly(const std::string& fileName);

	/// @brief 拷贝文件
	/// @return bool
	/// @param dst
	/// @param src
	static bool copyFile(const std::string& dst, const std::string& src);

	/// @brief  renameFile 改文件名
	/// @return bool
	/// @param  dst
	/// @param  src
	static bool renameFile(const std::string& dst, const std::string& src);

	/// @brief 删除文件
	/// @return bool
	/// @param fileName
	static bool deleteFile(const std::string& fileName);

private:
	std::string m_fileName;
};

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_FILE_FILEINFO_H__

