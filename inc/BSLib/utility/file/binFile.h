//////////////////////////////////////////////////////////////////////
//	created:	2014/11/12
//	filename: 	BSLib\utility\file\binFile.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UTILITY_FILE_BINFILE_H__
#define __BSLIB_UTILITY_FILE_BINFILE_H__

#include <BSLib/utility/baseDef.h>

namespace BSLib
{

namespace Utility
{

struct SFileHandle;

class CBinFile
{
public:
	enum EFSeekOrigin
	{
		FSEEK_BEGIN,
		FSEEK_END,
		FSEEK_CURRENT,
	};

public:
	CBinFile();
	~CBinFile();

	bool create(const std::string& a_file);
	bool open(const std::string& a_file);
	void flush();
	void close();

	BSLib::int32 tell();
	BSLib::int32 size();

	BSLib::int32 read(void* a_buffer, BSLib::uint32 a_size);
	BSLib::int32 write(const void *a_buffer, BSLib::uint32 a_size);

	bool seek(BSLib::int32 a_offset, CBinFile::EFSeekOrigin a_origin);
	
	bool isValid() { return m_fileHandle != NULL; }

private:
	std::string m_fileName;
	SFileHandle* m_fileHandle;
};

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_FILE_BINFILE_H__