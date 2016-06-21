#ifndef __BSLIB_UTILITY_FILE_DIRINFO_H__
#define __BSLIB_UTILITY_FILE_DIRINFO_H__

#include <BSLib/utility/baseDef.h>

namespace BSLib
{

namespace Utility
{

class BSLIB_UTILITY_API CDirInfo
{
public:
	CDirInfo(const std::string& dir = "");
	virtual ~CDirInfo();

	void standardization();
	bool isExist();
	int makeDir();
	int getDirectories(std::vector<std::string>& ret);
	int getFiles(std::vector<std::string>& ret);
	
public:
	/// @brief 目录标准化,在window环境中将'/'转换成‘\\’在linu环境中将'\\'转换成'/'
	/// @return void
	/// @param dir
	static void standardization(std::string& dir);
	
	/// @brief 判断目录是否存在
	/// @return bool
	/// @param dir
	static bool isExist(const std::string& dir);

	/// @brief 创建目录
	/// @return int
	/// @param dir
	static int makeDir(const std::string& dir);
	
	/// @brief 获取dir目录的所有子目录
	/// @return int
	/// @param dir
	/// @param ret
	static int getDirectories(const std::string& dir, std::vector<std::string>& ret);

	/// @brief 获取dir目录的所有文件
	/// @return int
	/// @param dir
	/// @param ret
	static int getFiles(const std::string& dir, std::vector<std::string>& ret);
	
	/// @brief 设置当前目录
	/// @return bool
	/// @param dir
	static bool setCurDirectory(const std::string& dir);

	/// @brief 获取当前目录
	/// @return std::string
	static std::string getCurDirectory();

	/// @brief 获取当前可执行程序的目录
	/// @return std::string
	static std::string getExeDirectory();

	/// @brief 获取当前可执行程序文件名
	/// @return std::string
	static std::string getExeFile();

private:
	std::string m_dirName;

};

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_FILE_DIRINFO_H__

