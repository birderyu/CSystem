#include "CsMemBlock.h"

CsMemoryBlock::CsMemoryBlock(cs_size_t nUnitSize, cs_size_t nUnitAmount)
: m_nSize(nUnitAmount * nUnitSize)
, m_nFree(nUnitAmount - 1)  //�����ʱ�򣬾��ѽ���һ����Ԫ�����ȥ�ˣ����Լ�һ
, m_nFirst(1)                //ͬ��
, m_pNext(NULL)
{
	//��ʼ������������ÿ�����䵥Ԫ����һ�����䵥Ԫ�����д�ڵ�ǰ��Ԫ��ǰ�����ֽ���
	char* pData = aData;
	//���һ��λ�ò���д��
	for (int i = 1; i < nUnitAmount; i++)
	{
		(*(cs_ushort*)pData) = i;
		pData += nUnitSize;
	}
}

CsMemoryBlock::~CsMemoryBlock()
{

}

cs_bool CsMemoryBlock::CanAlloc() const
{
	return m_nFree != 0;
}

void* CsMemoryBlock::operator new(size_t nSize, int nUnitSize, int nUnitAmount)
{
	return ::operator new(nSize + nUnitSize * nUnitAmount);
}

void CsMemoryBlock::operator delete(void *pBlock, cs_int nUnitSize, cs_int nUnitAmount)
{
	::operator delete(pBlock);
}

void CsMemoryBlock::operator delete(void* pBlock)
{
	::operator delete(pBlock);
}