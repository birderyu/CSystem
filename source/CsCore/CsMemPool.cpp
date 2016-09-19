#include "CsMemPool.h"
#include "CsMemBlock.h"

#define  CS_MEMPOOL_ALIGNMENT 8            //���볤��

CsMemoryPool::CsMemoryPool(cs_size_t nUnitSize, cs_size_t nGrowSize, cs_size_t nInitSzie)
: m_nInitSize(nInitSzie), m_nGrowSize(nGrowSize), m_pBlock(NULL)
{
	if (nUnitSize > 4)
		m_nUnitSize = (nUnitSize + (CS_MEMPOOL_ALIGNMENT - 1)) & ~(CS_MEMPOOL_ALIGNMENT - 1);
	else if (nUnitSize < 2)
		m_nUnitSize = 2;
	else
		m_nUnitSize = 4;
}

CsMemoryPool::~CsMemoryPool()
{
	CsMemoryBlock* pBlock = static_cast<CsMemoryBlock*>(m_pBlock);
	while (pBlock)
	{
		pBlock = pBlock->m_pNext;
		delete(pBlock);
	}
}

cs_pointer CsMemoryPool::Alloc()
{
	if (!m_pBlock)
	{
		//�״�����MemoryBlock��new��������new��һ��MemoryBlock��
		m_pBlock = new(m_nUnitSize, m_nInitSize) CsMemoryBlock(m_nUnitSize, m_nInitSize);
		return (void*)m_pBlock->aData;
	}

	//�ҵ������������ڴ��
	CsMemoryBlock* pBlock = static_cast<CsMemoryBlock*>(m_pBlock);
	while (pBlock && 0 == pBlock->m_nFree)
	{
		pBlock = pBlock->m_pNext;
	}
		
	if (pBlock)
	{
		//�ҵ��ˣ����з���
		cs_pointer pFree = pBlock->aData + pBlock->m_nFirst * m_nUnitSize;
		pBlock->m_nFirst = *((cs_ushort*)pFree);
		pBlock->m_nFree--;
		return pFree;
	}
	else
	{
		//û���ҵ���˵��ԭ�����ڴ�鶼���ˣ�Ҫ�ٴη���
		if (0 == m_nGrowSize)
			return NULL;

		pBlock = (CsMemoryBlock*)new(m_nUnitSize, m_nGrowSize) CsMemoryBlock(m_nUnitSize, m_nGrowSize);

		if (NULL == pBlock)
			return NULL;

		//����һ�β������
		pBlock->m_pNext = m_pBlock;
		m_pBlock = pBlock;

		return (void*)pBlock->aData;
	}
}

cs_void CsMemoryPool::Free(cs_pointer pFree)
{
	//�ҵ�p���ڵ��ڴ��
	CsMemoryBlock* pBlock = m_pBlock;
	CsMemoryBlock* pPreBlock = NULL;
	while (pBlock != NULL && (m_pBlock->aData > pFree || pBlock->aData + pBlock->m_nSize < pFree))
	{
		pPreBlock = pBlock;
		pBlock = pBlock->m_pNext;
	}

	if (NULL != pBlock)      //���ڴ��ڱ��ڴ����pMyBlock��ָ����ڴ����
	{
		//Step1 �޸���������
		*((cs_ushort*)pFree) = pBlock->m_nFirst;
		pBlock->m_nFirst = (cs_ushort)((cs_ulong)pFree - (cs_ulong)pBlock->aData) / m_nUnitSize;
		pBlock->m_nFree++;

		//Step2 �ж��Ƿ���Ҫ��OS�ͷ��ڴ�
		if (pBlock->m_nSize == pBlock->m_nFree * m_nUnitSize)
		{
			if (!pPreBlock)
			{
				// ��ɾ������
				m_pBlock = pBlock;
			}
			else
			{
				//��������ɾ����block
				pPreBlock->m_pNext = pBlock->m_pNext;
				delete pBlock;
				pBlock = NULL;
			}
		}
		else
		{
			//����block���뵽����
			pPreBlock = pBlock->m_pNext;
			pBlock->m_pNext = m_pBlock;
			m_pBlock = pBlock;
		}
	}
}
