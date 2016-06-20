//////////////////////////////////////////////////////////////////////
//	created:	2014/11/12
//	filename: 	src\BSLib\utility\file\binFile.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <BSLib/utility/file/fileInfo.h>
#include <BSLib/utility/file/binFile.h>

namespace BSLib
{

namespace Utility
{

struct SFileHandle
{
	FILE* m_pFile;
	
	SFileHandle()
	{
		m_pFile = NULL;
	}
};

CBinFile::CBinFile()
: m_fileHandle(NULL)
{
	;
}

CBinFile::~CBinFile()
{
	close();
}

bool CBinFile::create(const std::string& a_file)
{
	if (m_fileHandle != NULL) {
		return false;
	}
	m_fileHandle = new SFileHandle();
	if (m_fileHandle == NULL) {
		return false;
	}

#ifdef _WIN32

	if (fopen_s(&m_fileHandle->m_pFile, a_file.c_str(), "wb+") != 0){
		BSLIB_SAFE_DELETE(m_fileHandle);
		return false;
	}

#else

	m_fileHandle->m_pFile = fopen(a_file.c_str(), "wb+");
	if (m_fileHandle->m_pFile == NULL) {
		BSLIB_SAFE_DELETE(m_fileHandle);
		return false;
	}

#endif

	m_fileName = a_file;
	return true;
}

bool CBinFile::open(const std::string& a_file)
{
	if (m_fileHandle != NULL) {
		return false;
	}
	m_fileHandle = new SFileHandle();
	if (m_fileHandle == NULL) {
		return false;
	}

#ifdef _WIN32

	if (fopen_s(&m_fileHandle->m_pFile, a_file.c_str(), "rb+") != 0){
		BSLIB_SAFE_DELETE(m_fileHandle);
		return false;
	}

#else

	m_fileHandle->m_pFile = fopen(a_file.c_str(), "rb+");
	if (m_fileHandle->m_pFile == NULL) {
		BSLIB_SAFE_DELETE(m_fileHandle);
		return false;
	}

#endif

	m_fileName = a_file;

	return true;
}

void CBinFile::flush()
{
	if (m_fileHandle == NULL){
		return;
	}
	if (m_fileHandle->m_pFile == NULL){
		BSLIB_SAFE_DELETE(m_fileHandle);
		return;
	}
	fflush(m_fileHandle->m_pFile);
}

void CBinFile::close()
{
	if (m_fileHandle == NULL){
		return;
	}
	if (m_fileHandle->m_pFile == NULL){
		BSLIB_SAFE_DELETE(m_fileHandle);
		return;
	}
	fclose(m_fileHandle->m_pFile);
	BSLIB_SAFE_DELETE(m_fileHandle);
}

BSLib::int32 CBinFile::tell()
{
	if (m_fileHandle == NULL || m_fileHandle->m_pFile == NULL){
		return -1;
	}

	return ftell(m_fileHandle->m_pFile);
}

BSLib::int32 CBinFile::size()
{
	if (m_fileHandle == NULL || m_fileHandle->m_pFile == NULL){
		return -1;
	}
	if (!m_fileName.empty()) {
		return -1;
	}
	return (BSLib::int32)CFileInfo::getLength(m_fileName);
}

BSLib::int32 CBinFile::read(void* a_buffer, BSLib::uint32 a_size)
{
	if (m_fileHandle == NULL || m_fileHandle->m_pFile == NULL){
		return -1;
	}
	if (a_buffer == 0 || a_size <= 0){
		return 0;
	}
	return (BSLib::int32)fread(a_buffer, 1, a_size, m_fileHandle->m_pFile);
}

BSLib::int32 CBinFile::write(const void *a_buffer, BSLib::uint32 a_size)
{
	if (m_fileHandle == NULL || m_fileHandle->m_pFile == NULL){
		return -1;
	}
	if (a_buffer == 0 || a_size <= 0){
		return 0;
	}
	return (BSLib::int32)fwrite(a_buffer, 1, a_size, m_fileHandle->m_pFile);
}

bool CBinFile::seek(BSLib::int32 a_offset, CBinFile::EFSeekOrigin a_origin)
{
	if (m_fileHandle == NULL || m_fileHandle->m_pFile == NULL){
		return false;
	}

	int org = SEEK_SET;
	switch (a_origin)
	{
	case FSEEK_BEGIN:
		org = SEEK_SET;
		break;
	case FSEEK_END:
		org = SEEK_END;
		break;
	case FSEEK_CURRENT:
		org = SEEK_CUR;
		break;   
	}

	return fseek(m_fileHandle->m_pFile, a_offset, org) == 0;
}

}//Utility

}//BSLib