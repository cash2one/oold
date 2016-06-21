#if defined(WIN32)

#include <direct.h>

#else

#include <dirent.h>

#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <set>
#include <algorithm>
#include <BSLib/utility/file/fileInfo.h>
#include <BSLib/utility/file/dirInfo.h>

namespace BSLib
{

namespace Utility
{

#if defined(WIN32)	

	#define PATH_SEPARATOR '\\'

#elif defined(_LINUX)

	#define PATH_SEPARATOR '/'

#else

	#error "Unknown platform !!"

#endif

CFileInfo::CFileInfo(const std::string& fileName)
: m_fileName(fileName)
{
}

CFileInfo::~CFileInfo(void)
{
}

void CFileInfo::standardization()
{
	standardization(m_fileName);
}

bool CFileInfo::isExist()
{
	return isExist(m_fileName);
}

std::string CFileInfo::getFullPath()
{
	return getFullPath(m_fileName);
}

std::string CFileInfo::getFullName()
{
	return getFullName(m_fileName);
}

std::string CFileInfo::getPath()
{
	return getPath(m_fileName);
}

std::string CFileInfo::getName()
{
	return getName(m_fileName);
}

std::string CFileInfo::getExtension()
{
	return getExtension(m_fileName);
}

long CFileInfo::getLength()
{
	return getLength(m_fileName);
}

bool CFileInfo::getLastModifyTime(CDateTime& dateTime)
{
	return getLastModifyTime(m_fileName, dateTime);
}

bool CFileInfo::isReadOnly()
{
	return isReadOnly(m_fileName);
}

bool CFileInfo::copyFile(const std::string& dst)
{
	return copyFile(dst, m_fileName);
}

bool CFileInfo::renameFile(const std::string& dst)
{
	return renameFile(dst, m_fileName);
}

bool CFileInfo::deleteFile()
{
	return deleteFile(m_fileName);
}

void CFileInfo::standardization(std::string& fileName)
{
	CDirInfo::standardization(fileName);
}

bool CFileInfo::isExist(const std::string& fileName)
{
	struct stat fileInfo;
	if (::stat(fileName.c_str(), &fileInfo) < 0) {
		return false;
	}

#if defined(WIN32)	

	if (!(fileInfo.st_mode & S_IFDIR)){
		return true;
	}

#elif defined(_LINUX)

	if (!(S_ISDIR(fileInfo.st_mode))){
		return true;
	}

#else

#error "Unknown platform !!"

#endif

	return false;
}

std::string CFileInfo::getFullPath(const std::string& fileName)
{
	size_t pos = fileName.find_last_of(PATH_SEPARATOR);
	if (pos > 0){
		return fileName.substr(0, pos);
	}
	return "";
}

std::string CFileInfo::getPath(const std::string& fileName)
{
	std::string fullPath = getFullPath(fileName);
	size_t pos = fullPath.find_last_of(PATH_SEPARATOR);
	if (pos > 0){
		return fullPath.substr(0, pos);
	}
	return "";
}

std::string CFileInfo::getFullName(const std::string& fileName)
{
	size_t pos = fileName.find_last_of(PATH_SEPARATOR);
	if (pos > 0){
		size_t count = fileName.size();
		count -= pos;
		return fileName.substr(pos+1, count-1);
	}
	return "";
}

std::string CFileInfo::getName(const std::string& fileName)
{
	std::string fullName = getFullName(fileName);
	size_t pos = fullName.find_last_of('.');
	if (pos > 0){
		return fullName.substr(0, pos);
	}
	return "";
}

std::string CFileInfo::getExtension(const std::string& fileName)
{
	std::string fullName = getFullName(fileName);
	size_t pos = fullName.find_last_of('.');
	if (pos > 0){
		size_t count = fullName.size();
		count -= pos;
		return fullName.substr(pos+1, count-1);
	}
	return "";
}

long CFileInfo::getLength(const std::string& fileName)
{
	if (!isExist(fileName)){
		return 0;
	}
	struct stat fileInfo;
	if (stat(fileName.c_str(), &fileInfo) < 0) {
		return 0;
	}
	return  fileInfo.st_size;
}

bool CFileInfo::getLastModifyTime(const std::string& fileName, CDateTime& dateTime)
{
	struct stat fileInfo;
	if (stat(fileName.c_str(), &fileInfo) < 0) {
		return false;
	}
	dateTime.setTime(fileInfo.st_mtime);
	return  true;
}

bool CFileInfo::isReadOnly(const std::string& fileName)
{
	struct stat fileInfo;
	if (::stat(fileName.c_str(), &fileInfo) < 0) {
		return false;
	}

#if defined(WIN32)	

	if ((fileInfo.st_mode & S_IREAD) && (!(fileInfo.st_mode & S_IWRITE))){
		return true;
	}

#elif defined(_LINUX)

	if ((fileInfo.st_mode & S_IRUSR) && (!(fileInfo.st_mode & S_IWUSR))){
		return true;
	}

#else

#error "Unknown platform !!"

#endif

	return false;
}

bool CFileInfo::copyFile(const std::string& dst, const std::string& src)
{
	if (!isExist(src)){
		return false;
	}
	std::string fullPath = getFullPath(dst);
	if (!CDirInfo::isExist(fullPath)){
		if (CDirInfo::makeDir(fullPath) < 0) {
			return false;
		}
	}

#if defined(WIN32)	

	return ::CopyFile(src.c_str(), dst.c_str(), FALSE) == TRUE;

#elif defined(_LINUX)

	std::string cmd = "cp -f ";
	cmd += src;
	cmd += " ";
	cmd += dst;
	system(cmd.c_str());
	return true;

#else

#error "Unknown platform !!"

#endif

}

bool CFileInfo::renameFile(const std::string& dst, const std::string& src)
{
	if (!isExist(src)) {
		return false;
	}
	std::string dstFullPath = getFullPath(dst);
	std::string srcFullPath = getFullPath(src);
	if (dstFullPath != srcFullPath) {
		return false;
	}
	return ::rename(src.c_str(), dst.c_str()) == 0;
}

bool CFileInfo::deleteFile(const std::string& fileName)
{
	
#if defined(WIN32)	

	return ::DeleteFile(fileName.c_str()) == TRUE;

#elif defined(_LINUX)

	std::string cmd = "rm -f ";
	cmd += fileName;
	system(cmd.c_str());
	return true;

#else

#error "Unknown platform !!"

#endif
}

}//Utility

}//BSLib

