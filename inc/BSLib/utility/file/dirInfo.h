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
	/// @brief Ŀ¼��׼��,��window�����н�'/'ת���ɡ�\\����linu�����н�'\\'ת����'/'
	/// @return void
	/// @param dir
	static void standardization(std::string& dir);
	
	/// @brief �ж�Ŀ¼�Ƿ����
	/// @return bool
	/// @param dir
	static bool isExist(const std::string& dir);

	/// @brief ����Ŀ¼
	/// @return int
	/// @param dir
	static int makeDir(const std::string& dir);
	
	/// @brief ��ȡdirĿ¼��������Ŀ¼
	/// @return int
	/// @param dir
	/// @param ret
	static int getDirectories(const std::string& dir, std::vector<std::string>& ret);

	/// @brief ��ȡdirĿ¼�������ļ�
	/// @return int
	/// @param dir
	/// @param ret
	static int getFiles(const std::string& dir, std::vector<std::string>& ret);
	
	/// @brief ���õ�ǰĿ¼
	/// @return bool
	/// @param dir
	static bool setCurDirectory(const std::string& dir);

	/// @brief ��ȡ��ǰĿ¼
	/// @return std::string
	static std::string getCurDirectory();

	/// @brief ��ȡ��ǰ��ִ�г����Ŀ¼
	/// @return std::string
	static std::string getExeDirectory();

	/// @brief ��ȡ��ǰ��ִ�г����ļ���
	/// @return std::string
	static std::string getExeFile();

private:
	std::string m_dirName;

};

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_FILE_DIRINFO_H__

