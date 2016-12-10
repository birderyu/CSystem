#ifdef _WIN32

#include "CsCriticalSection.h"
#include <windows.h>

/// Win32�ٽ���ʵ�����
struct CsCriticalSection_Handle
{
	CRITICAL_SECTION m_tCriticalSection;
};

CsCriticalSection::CsCriticalSection()
:m_pHandle(NULL)
{
	Initialize();
}

CsCriticalSection::~CsCriticalSection()
{
	Release();
}

cs_bool CsCriticalSection::Lock()
{
	CsCriticalSection_Handle *pHandle = static_cast<CsCriticalSection_Handle*>(m_pHandle);
	if (!pHandle) return false;

	
	return true;
}

cs_bool CsCriticalSection::Trylock()
{
	return false;
}

cs_void CsCriticalSection::Unlock()
{

}

cs_int CsCriticalSection::Initialize()
{
	if (!m_pHandle)
	{
		return 0;
	}
	CsCriticalSection_Handle *pHandle = new CsCriticalSection_Handle;
	if (!pHandle) return -1;
	m_pHandle = pHandle;

	InitializeCriticalSection(&pHandle->m_tCriticalSection);

	//ReleaseMutex(pHandle->m_hMutex);
	return 0;
}

cs_void CsCriticalSection::Release()
{
	if (m_pHandle)
	{
		CsCriticalSection_Handle *pHandle = static_cast<CsCriticalSection_Handle*>(m_pHandle);
		delete pHandle;
		m_pHandle = NULL;
	}
}

#endif // _WIN32