// �ڴ��ļ�
#ifndef _CORE_MEMORY_FILE_H_
#define _CORE_MEMORY_FILE_H_

#include "CsFile.h"

class CsMemoryFile
	: public CsFile
{
public:
	CsMemoryFile();

private:
	// �������ֽ���
	//CsBytes m_tBytes;
};

#endif // _CORE_MEMORY_FILE_H_