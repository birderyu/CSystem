#include "CsMemPool.h"
#define  MEMPOOL_ALIGNMENT 8            //���볤��

CsMemoryBlock::CsMemoryBlock(cs_int nUnitSize, cs_int nUnitAmount)
	:m_nSize(nUnitAmount * nUnitSize),
	m_nFree(nUnitAmount - 1),  //�����ʱ�򣬾��ѽ���һ����Ԫ�����ȥ�ˣ����Լ�һ
	m_nFirst(1),                //ͬ��
	m_pNext(NULL)
{
	//��ʼ������������ÿ�����䵥Ԫ����һ�����䵥Ԫ�����д�ڵ�ǰ��Ԫ��ǰ�����ֽ���
	char* pData = aData;
	//���һ��λ�ò���д��
	for (int i = 1; i < m_nSize - 1; i++)
	{
		(*(cs_ushort*)pData) = i;
		pData += nUnitSize;
	}
}

CsMemoryBlock::~CsMemoryBlock()
{

}

void* CsMemoryBlock::operator new(size_t, int nUnitSize, int nUnitAmount)
{
	return ::operator new(sizeof(CsMemoryBlock)+nUnitSize * nUnitAmount);
}

void CsMemoryBlock::operator delete(void *pBlock, cs_int nUnitSize, cs_int nUnitAmount)
{
	::operator delete(pBlock);
}

void CsMemoryBlock::operator delete(void* pBlock)
{
	::operator delete(pBlock);
}

CsMemoryPool::CsMemoryPool(int nUnitSize, int nGrowSize, int nInitSzie)
{
	m_nInitSize = nInitSzie;
	m_nGrowSize = nGrowSize;
	m_pBlock = NULL;
	if (nUnitSize > 4)
		m_nUnitSize = (nUnitSize + (MEMPOOL_ALIGNMENT - 1)) & ~(MEMPOOL_ALIGNMENT - 1);
	else if (nUnitSize < 2)
		m_nUnitSize = 2;
	else
		m_nUnitSize = 4;
}

CsMemoryPool::~CsMemoryPool()
{
	CsMemoryBlock* pMyBlock = m_pBlock;
	while (pMyBlock != NULL)
	{
		pMyBlock = pMyBlock->m_pNext;
		delete(pMyBlock);
	}
}

void *CsMemoryPool::Alloc()
{
	if (NULL == m_pBlock)
	{
		//�״�����MemoryBlock,new��������new��һ��MemoryBlock��
		m_pBlock = (CsMemoryBlock*)new(m_nUnitSize, m_nInitSize) CsMemoryBlock(m_nUnitSize, m_nUnitSize);
		return (void*)m_pBlock->aData;
	}

	//�ҵ������������ڴ��
	CsMemoryBlock* pMyBlock = m_pBlock;
	while (pMyBlock != NULL && 0 == pMyBlock->m_nFree)
		pMyBlock = pMyBlock->m_pNext;

	if (pMyBlock != NULL)
	{
		//�ҵ��ˣ����з���
		char* pFree = pMyBlock->aData + pMyBlock->m_nFirst * m_nUnitSize;
		pMyBlock->m_nFirst = *((cs_ushort*)pFree);
		pMyBlock->m_nFree--;

		return (void*)pFree;
	}
	else
	{
		//û���ҵ���˵��ԭ�����ڴ�鶼���ˣ�Ҫ�ٴη���

		if (0 == m_nGrowSize)
			return NULL;

		pMyBlock = (CsMemoryBlock*)new(m_nUnitSize, m_nGrowSize) CsMemoryBlock(m_nUnitSize, m_nGrowSize);

		if (NULL == pMyBlock)
			return NULL;

		//����һ�β������
		pMyBlock->m_pNext = m_pBlock;
		m_pBlock = pMyBlock;

		return (void*)pMyBlock->aData;
	}
}

void CsMemoryPool::Free(void* pFree)
{
	//�ҵ�p���ڵ��ڴ��
	CsMemoryBlock* pMyBlock = m_pBlock;
	CsMemoryBlock* pPreBlock = NULL;
	while (pMyBlock != NULL && (m_pBlock->aData > pFree || pMyBlock->aData + pMyBlock->m_nSize))
	{
		pPreBlock = pMyBlock;
		pMyBlock = pMyBlock->m_pNext;
	}

	if (NULL != pMyBlock)      //���ڴ��ڱ��ڴ����pMyBlock��ָ����ڴ����
	{
		//Step1 �޸���������
		*((cs_ushort*)pFree) = pMyBlock->m_nFirst;
		pMyBlock->m_nFirst = (cs_ushort)((cs_ulong)pFree - (cs_ulong)pMyBlock->aData) / m_nUnitSize;
		pMyBlock->m_nFree++;

		//Step2 �ж��Ƿ���Ҫ��OS�ͷ��ڴ�
		if (pMyBlock->m_nSize == pMyBlock->m_nFree * m_nUnitSize)
		{
			//��������ɾ����block

			delete(pMyBlock);
		}
		else
		{
			//����block���뵽����
			pPreBlock = pMyBlock->m_pNext;
			pMyBlock->m_pNext = m_pBlock;
			m_pBlock = pMyBlock;
		}
	}
}
