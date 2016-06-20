//////////////////////////////////////////////////////////////////////
//	created:	2012/08/06
//	filename:	src\BSLib\utility\file\dirInfo.cpp
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#if defined(WIN32)

	#include <direct.h>

#else

	#include <dirent.h>

#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <set>
#include <algorithm>
#include <BSLib/utility/file/dirInfo.h>
#include <BSLib/utility/file/fileInfo.h>


namespace BSLib
{

namespace Utility
{

CDirInfo::CDirInfo(const std::string& dir)
: m_dirName(dir)
{
}

CDirInfo::~CDirInfo()
{
}

void CDirInfo::standardization()
{
	standardization(m_dirName);
}

bool CDirInfo::isExist()
{
	return isExist(m_dirName);
}

int CDirInfo::makeDir()
{
	return makeDir(m_dirName);
}

int CDirInfo::getDirectories(std::vector<std::string>& ret)
{
	return getDirectories(m_dirName, ret);
}

int CDirInfo::getFiles(std::vector<std::string>& ret)
{
	return getFiles(m_dirName, ret);
}

void CDirInfo::standardization(std::string& dir)
{
	for(uint32 i=0; i<dir.size(); ++i){

#if defined(WIN32)

		if (dir[i] == '/'){
			dir[i] = '\\';
		}

#elif defined(_LINUX)

		if (dir[i] == '\\'){
			dir[i] = '/';
		}

#else

#error "Unknown platform !!"

#endif
	}
}

bool CDirInfo::isExist(const std::string& dir)
{
#if defined(WIN32)	

	DWORD attr = ::GetFileAttributes(dir.c_str());
	if (attr == INVALID_FILE_ATTRIBUTES){
		return false;
	}
	if ((attr  & FILE_ATTRIBUTE_DEVICE) || (attr  & FILE_ATTRIBUTE_DIRECTORY)){
		return true;
	}

#elif defined(_LINUX)
	
	struct stat fileInfo;
	if (::stat(dir.c_str(), &fileInfo) < 0) {
		return false;
	}
	if (S_ISDIR(fileInfo.st_mode)){
		return true;
	}

#else

#error "Unknown platform !!"

#endif

	return false;
}

int CDirInfo::makeDir(const std::string& dir)
{
	if (isExist(dir)){
		return 1;
	}

	size_t dirSize = dir.size();
	for (size_t i = 0; i < dirSize; i++){
		if (dir[i] == '\\' || dir[i] == '/') {
			if (i > 0 && dir[i-1] == ':'){
				continue;
			}
			std::string fatherdir = dir.substr(0, i);
			if (isExist(fatherdir)){
				continue;
			}
			if (fatherdir.empty()) {
				continue;
			}

#if defined(WIN32)

			if (::_mkdir(fatherdir.c_str()) < 0) {
				return -1;
			}

#elif defined(_LINUX)

			if (::mkdir(fatherdir.c_str(), 0777) < 0) {
				return -1;
			}

#else

#error "Unknown platform !!"

#endif

			continue;
		}
		if (i+1 == dirSize){
			if (isExist(dir)){
				continue;
			}

#if defined(WIN32)

			if (::_mkdir(dir.c_str()) < 0) {
				return -1;
			}

#elif defined(_LINUX)

			if (::mkdir(dir.c_str(), 0777) < 0) {
				return -1;
			}

#else

#error "Unknown platform !!"

#endif

		}
	}
	return 0;
}

int CDirInfo::getDirectories(const std::string& dir, std::vector<std::string>& ret)
{
#if defined(WIN32)	

	WIN32_FIND_DATA fd;

	std::string curdir = dir;
	curdir += "\\*.*";

	HANDLE hFile = FindFirstFile(curdir.c_str(), &fd);
	if (hFile != INVALID_HANDLE_VALUE){
		while(FindNextFile(hFile, &fd))
		{
			if (fd.cFileName[0] == '.') {
				continue;
			}
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
				ret.push_back(fd.cFileName);
			}
		}
		FindClose(hFile);
	}

#elif defined(_LINUX)

	dirent *dirText = NULL;    
	DIR *dirPtr = NULL;

	dirPtr = ::opendir(dir.c_str());
	while((dirText = ::readdir(dirPtr)) != NULL){
		if(dirText->d_name[0] == '.'){
			continue;
		}
		if (dirText->d_type & DT_DIR){
			ret.push_back(dirText->d_name);
		}
	}
	::closedir(dirPtr);

#else

#error "Unknown platform !!"

#endif

	return (int)ret.size();
}

int CDirInfo::getFiles(const std::string& dir, std::vector<std::string>& ret)
{
#if defined(WIN32)	

	WIN32_FIND_DATA fd;

	std::string curdir = dir;
	curdir += "\\*.*";

	HANDLE hFile = FindFirstFile(curdir.c_str(), &fd);
	if (hFile != INVALID_HANDLE_VALUE){
		while(FindNextFile(hFile, &fd))
		{
			if (fd.cFileName[0] == '.') {
				continue;
			}
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
				ret.push_back(fd.cFileName);
			}
		}
		FindClose(hFile);
	}

#elif defined(_LINUX)

	dirent *dirText = NULL;    
	DIR *dirPtr = NULL;

	dirPtr = ::opendir(dir.c_str());
	while((dirText = ::readdir(dirPtr)) != NULL){
		if(dirText->d_name[0] == '.'){
			continue;
		}
		if (dirText->d_type & DT_REG){
			ret.push_back(dirText->d_name);
		}
	}
	::closedir(dirPtr);

#else

#error "Unknown platform !!"

#endif

	return (int)ret.size();
}

bool CDirInfo::setCurDirectory(const std::string& dir)
{
#if defined(WIN32)

	return ::_chdir(dir.c_str()) ? false : true;

#elif defined(_LINUX)

	return ::chdir(dir.c_str()) ? false : true;

#else

	#error "Unknown platform !!"

#endif
}

std::string CDirInfo::getCurDirectory()
{
	char buf[1025] = {0};
	
#if defined(WIN32)

	::_getcwd(buf, 1024);

#elif defined(_LINUX)

	::getcwd(buf, 1024);

#else

#error "Unknown platform !!"

#endif

	std::string dir = buf;
	return dir;
}

std::string CDirInfo::getExeDirectory()
{
#if defined(WIN32)	

	char fileName[MAX_PATH + 1] = { 0 };
	::GetModuleFileName(NULL, fileName, MAX_PATH);
	return CFileInfo::getFullPath(fileName);

#elif defined(_LINUX)

	char fileName[1025] = { 0 };
	readlink("/proc/self/exe", fileName, 1025);
	return CFileInfo::getFullPath(fileName);

#else

#error "Unknown platform !!"

#endif
}

std::string CDirInfo::getExeFile()
{
#if defined(WIN32)	

	char fileName[MAX_PATH + 1] = { 0 };
	::GetModuleFileName(NULL, fileName, MAX_PATH);
	return CFileInfo::getFullName(fileName);

#elif defined(_LINUX)

	char fileName[1025] = { 0 };
	readlink("/proc/self/exe", fileName, 1025);
	return CFileInfo::getFullName(fileName);

#else

#error "Unknown platform !!"

#endif
}

}//Utility

}//BSLib
