#ifndef _CSCORE_CSMEMORYPOOL_H_
#define _CSCORE_CSMEMORYPOOL_H_

#include "CsCoreGlobal.h"

class CsMemoryPool;
class CsCore_Export CsMemoryBlock
{
	friend class CsMemoryPool;
public:
	CsMemoryBlock(cs_int nUnitSize, cs_int nUnitAmount);
	~CsMemoryBlock();
	static void *operator new(cs_size_t, cs_int nUnitSize, cs_int nUnitAmount);
	static void operator delete (void *pBlock, cs_int nUnitSize, cs_int nUnitAmount);
	static void operator delete (void *pBlock);

private:
	cs_int m_nSize;              //���ڴ��Ĵ�С�����ֽ�Ϊ��λ
	cs_int m_nFree;              //���ڴ�黹�ж��ٿɷ���ĵ�Ԫ
	cs_int m_nFirst;             //��ǰ���õ�Ԫ����ţ���0��ʼ
	CsMemoryBlock *m_pNext;              //ָ����һ���ڴ��
	cs_char aData[1];           //���ڱ�Ƿ��䵥Ԫ��ʼ��λ�ã����䵥Ԫ��aData��λ�ÿ�ʼ
};

class CsCore_Export CsMemoryPool
{
public:
	CsMemoryPool(cs_int nUnitSize,
		cs_int nGrowSize = 1024,
		cs_int nInitSzie = 256);
	~CsMemoryPool();
	void *Alloc();
	void Free(void *pFree);

private:
	cs_int m_nInitSize;          //��ʼ��С
	cs_int m_nGrowSize;          //������С
	cs_int m_nUnitSize;          //���䵥Ԫ��С
	CsMemoryBlock *m_pBlock;     //�ڴ������
};

#endif // _CSCORE_CSMEMORYPOOL_H_
