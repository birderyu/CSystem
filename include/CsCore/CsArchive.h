#ifndef _CORE_ARCHIVE_H_
#define _CORE_ARCHIVE_H_

#include "CsGlobal.h"

class CS_API CsArchive
{
public:
	CsArchive();
	cs_void SetClassCode(cs_uint);

private:
	cs_uint m_nClassCode;
	//CsBytes m_tBuffer; // ������
	//CsFile &m_rFile; // �ļ��鵵
};

#endif // _CORE_ARCHIVE_H_