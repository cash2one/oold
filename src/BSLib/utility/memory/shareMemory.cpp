#include <BSLib/utility/memory/shareMemory.h>
#include <BSLib/utility/string.h>


#if defined(WIN32)

#define BSLIB_UTILITY_HNDSHAREMEMORY_INVALID NULL

#elif defined(_LINUX)

#include <sys/ipc.h>
#include <sys/shm.h>
#define BSLIB_UTILITY_HNDSHAREMEMORY_INVALID -1

#endif


namespace BSLib
{

namespace Utility
{

CShareMemory::CShareMemory()
: m_hndShareMemory(BSLIB_UTILITY_HNDSHAREMEMORY_INVALID)
, m_headAddress(NULL)
{
	;
}

CShareMemory::~CShareMemory()
{
	close();
}

bool CShareMemory::create(BSLib::uint32 a_key, BSLib::uint32 size)
{
	if (m_hndShareMemory != BSLIB_UTILITY_HNDSHAREMEMORY_INVALID) {
		return false;
	}

#if defined(WIN32)

	BSLib::Utility::CStringA keyName;
	keyName.format("BSLib_Utility_ShareMemory_%x", a_key);

	m_hndShareMemory = ::CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, (DWORD)size, keyName.c_str());
	if (m_hndShareMemory == NULL) {
		return false;
	}
	if (::GetLastError() == ERROR_ALREADY_EXISTS) {
		CloseHandle(m_hndShareMemory);
		m_hndShareMemory = BSLIB_UTILITY_HNDSHAREMEMORY_INVALID;
		return false;
	}
	m_headAddress = ::MapViewOfFile(m_hndShareMemory, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (m_headAddress == NULL) {
		CloseHandle(m_hndShareMemory);
		m_hndShareMemory = BSLIB_UTILITY_HNDSHAREMEMORY_INVALID;
		return false;
	}
	
#elif defined(_LINUX)

	m_hndShareMemory = ::shmget((key_t)a_key, size, 0666 | IPC_CREAT | IPC_EXCL);
	if (m_hndShareMemory < 0) {
		return false;
	}
	m_headAddress = shmat(m_hndShareMemory, 0, 0);
	if (m_headAddress == (void*)-1){
		::shmctl(m_hndShareMemory, IPC_RMID, NULL);
		m_hndShareMemory = BSLIB_UTILITY_HNDSHAREMEMORY_INVALID;
		m_headAddress = NULL;
		return false;
	}

#endif
	
	return true;
}

bool CShareMemory::open(BSLib::uint32 a_key)
{
	if (m_hndShareMemory != BSLIB_UTILITY_HNDSHAREMEMORY_INVALID) {
		return false;
	}

#if defined(WIN32)

	BSLib::Utility::CStringA keyName;
	keyName.format("BSLib_Utility_ShareMemory_%x", a_key);

	m_hndShareMemory = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, keyName.c_str());
	if (m_hndShareMemory == NULL) {
		return false;
	}
	m_headAddress = ::MapViewOfFile(m_hndShareMemory, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (m_headAddress == NULL) {
		CloseHandle(m_hndShareMemory);
		m_hndShareMemory = BSLIB_UTILITY_HNDSHAREMEMORY_INVALID;
		return false;
	}

#elif defined(_LINUX)

	m_hndShareMemory = ::shmget((key_t)a_key, 0, 0666 | IPC_CREAT);
	if (m_hndShareMemory < 0) {
		return false;
	}
	m_headAddress = ::shmat(m_hndShareMemory, 0, 0);
	if (m_headAddress == (void*)-1){
		::shmctl(m_hndShareMemory, IPC_RMID, NULL);
		m_hndShareMemory = BSLIB_UTILITY_HNDSHAREMEMORY_INVALID;
		m_headAddress = NULL;
		return false;
	}

#endif

	return true;
}

void CShareMemory::close()
{
#if defined(WIN32)

	if (m_headAddress != NULL) {
		UnmapViewOfFile(m_headAddress);
		m_headAddress = NULL;
	}

	if (m_hndShareMemory != BSLIB_UTILITY_HNDSHAREMEMORY_INVALID) {
		CloseHandle(m_hndShareMemory);
		m_hndShareMemory = BSLIB_UTILITY_HNDSHAREMEMORY_INVALID;
	}

#elif defined(_LINUX)

	if (m_headAddress != NULL) {
		::shmdt(m_headAddress);
		m_headAddress = NULL;
	}

	if (m_hndShareMemory != BSLIB_UTILITY_HNDSHAREMEMORY_INVALID) {
		shmid_ds buf;
		if (::shmctl(m_hndShareMemory, IPC_STAT, &buf) == 0){
			if (buf.shm_nattch == 0) {
				::shmctl(m_hndShareMemory, IPC_RMID, NULL);
			}
		}
		m_hndShareMemory = BSLIB_UTILITY_HNDSHAREMEMORY_INVALID;
	}

#endif
}

}//Utility

}//BSLib

