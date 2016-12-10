#include "CsMemoryPool.h"
#include "CsNew.h"

#define  CS_MEMPOOL_ALIGNMENT 8            //���볤��

CsMemoryPool::CsMemoryCell::CsMemoryCell(cs_size_t nUnitSize, cs_size_t nUnitAmount)
: m_nSize(nUnitAmount * nUnitSize)
, m_nFree(nUnitAmount - 1)  //�����ʱ�򣬾��ѽ���һ����Ԫ�����ȥ�ˣ����Լ�һ
, m_nFirst(1)                //ͬ��
, m_pNext(NULL)
{
	//��ʼ������������ÿ�����䵥Ԫ����һ�����䵥Ԫ�����д�ڵ�ǰ��Ԫ��ǰ�����ֽ���
	cs_char* pData = aData;
	//���һ��λ�ò���д��
	for (cs_size_t i = 1; i < nUnitAmount; i++)
	{
		(*(cs_ushort*)pData) = i;
		pData += nUnitSize;
	}
}

CsMemoryPool::CsMemoryCell::~CsMemoryCell()
{
	if (m_pNext)
	{
		delete m_pNext;
	}
}

void* CsMemoryPool::CsMemoryCell::operator new(cs_size_t nSize, int nUnitSize, int nUnitAmount)
{
	//return ::operator new(nSize + nUnitSize * nUnitAmount);
	return CsMalloc(nSize + nUnitSize * nUnitAmount);
}

void CsMemoryPool::CsMemoryCell::operator delete(void *pCell, cs_int nUnitSize, cs_int nUnitAmount)
{
	//::operator delete(pCell);
	CsFree(pCell);
}

void CsMemoryPool::CsMemoryCell::operator delete(void* pCell)
{
	//::operator delete(pCell);
	CsFree(pCell);
}

CsMemoryPool::CsMemoryPool(cs_size_t nUnitSize, cs_size_t nInitSzie, cs_size_t nGrowSize)
: m_nInitSize(nInitSzie), m_nGrowSize(nGrowSize), m_pList(NULL)
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
	if (m_pList)
	{
		delete m_pList;
	}
}

cs_pointer CsMemoryPool::Alloc()
{
	if (!m_pList)
	{
		//�״�����MemoryBlock��new��������new��һ��MemoryBlock��
		m_pList = new(m_nUnitSize, m_nInitSize) CsMemoryCell(m_nUnitSize, m_nInitSize);
		return (cs_pointer)m_pList->aData;
	}

	//�ҵ������������ڴ��
	CsMemoryCell* pBlock = m_pList;
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

		pBlock = (CsMemoryCell*)new(m_nUnitSize, m_nGrowSize) CsMemoryCell(m_nUnitSize, m_nGrowSize);

		if (NULL == pBlock)
			return NULL;

		//����һ�β������
		pBlock->m_pNext = m_pList;
		m_pList = pBlock;

		return (void*)pBlock->aData;
	}
}

cs_void CsMemoryPool::Free(cs_pointer pFree)
{
	//�ҵ�p���ڵ��ڴ��
	CsMemoryCell* pBlock = m_pList;
	CsMemoryCell* pPreBlock = NULL;
	while (pBlock != NULL && (m_pList->aData > pFree || pBlock->aData + pBlock->m_nSize < pFree))
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
				m_pList = pBlock;
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
			pBlock->m_pNext = m_pList;
			m_pList = pBlock;
		}
	}
}
