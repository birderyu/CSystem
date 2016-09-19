/// �ڴ��

#ifndef _CORE_MEMORY_BLOCK_H_
#define _CORE_MEMORY_BLOCK_H_

#include "CsCoreGlobal.h"

class CsMemoryPool;

class CS_CORE_EXPORT CsMemoryBlock
{
	friend class CsMemoryPool;

public:
	CsMemoryBlock(cs_size_t nUnitSize, cs_size_t nUnitAmount);
	~CsMemoryBlock();

	/// �Ƿ���Է����ڴ�
	cs_bool CanAlloc() const;

	static void *operator new(cs_size_t, cs_int nUnitSize, cs_int nUnitAmount);
	static void operator delete (cs_pointer pBlock, cs_int nUnitSize, cs_int nUnitAmount);
	static void operator delete (cs_pointer pBlock);

private:
	cs_int m_nSize;              //���ڴ��Ĵ�С�����ֽ�Ϊ��λ
	cs_int m_nFree;              //���ڴ�黹�ж��ٿɷ���ĵ�Ԫ
	cs_int m_nFirst;             //��ǰ���õ�Ԫ����ţ���0��ʼ
	CsMemoryBlock *m_pNext;              //ָ����һ���ڴ��
	cs_char aData[1];           //���ڱ�Ƿ��䵥Ԫ��ʼ��λ�ã����䵥Ԫ��aData��λ�ÿ�ʼ
};

#endif // _CORE_MEMORY_BLOCK_H_