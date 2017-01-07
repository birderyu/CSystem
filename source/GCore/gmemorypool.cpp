#include "gmemorypool.h"
#include "gnew.h"

#define  G_MEMPOOL_ALIGNMENT 8            //���볤��

GMemoryPool::GMemoryCell::GMemoryCell(gsize nUnitSize, gsize nUnitAmount)
: m_nSize(nUnitAmount * nUnitSize)
, m_nFree(nUnitAmount - 1)  //�����ʱ�򣬾��ѽ���һ����Ԫ�����ȥ�ˣ����Լ�һ
, m_nFirst(1)                //ͬ��
, m_pNext(NULL)
{
	//��ʼ������������ÿ�����䵥Ԫ����һ�����䵥Ԫ�����д�ڵ�ǰ��Ԫ��ǰ�����ֽ���
	gchar* pData = aData;
	//���һ��λ�ò���д��
	for (gsize i = 1; i < nUnitAmount; i++)
	{
		(*(gushort*)pData) = i;
		pData += nUnitSize;
	}
}

GMemoryPool::GMemoryCell::~GMemoryCell()
{
	if (m_pNext)
	{
		delete m_pNext;
	}
}

void* GMemoryPool::GMemoryCell::operator new(gsize nSize, int nUnitSize, int nUnitAmount)
{
	//return ::operator new(nSize + nUnitSize * nUnitAmount);
	return GMalloc(nSize + nUnitSize * nUnitAmount);
}

void GMemoryPool::GMemoryCell::operator delete(void *pCell, gint nUnitSize, gint nUnitAmount)
{
	//::operator delete(pCell);
	GFree(pCell);
}

void GMemoryPool::GMemoryCell::operator delete(void* pCell)
{
	//::operator delete(pCell);
	GFree(pCell);
}

GMemoryPool::GMemoryPool(gsize nUnitSize, gsize nInitSzie, gsize nGrowSize)
: m_nInitSize(nInitSzie), m_nGrowSize(nGrowSize), m_pList(NULL)
{
	if (nUnitSize > 4)
		m_nUnitSize = (nUnitSize + (G_MEMPOOL_ALIGNMENT - 1)) & ~(G_MEMPOOL_ALIGNMENT - 1);
	else if (nUnitSize < 2)
		m_nUnitSize = 2;
	else
		m_nUnitSize = 4;
}

GMemoryPool::~GMemoryPool()
{
	if (m_pList)
	{
		delete m_pList;
	}
}

gpointer GMemoryPool::Alloc()
{
	if (!m_pList)
	{
		//�״�����MemoryBlock��new��������new��һ��MemoryBlock��
		m_pList = new(m_nUnitSize, m_nInitSize) GMemoryCell(m_nUnitSize, m_nInitSize);
		return (gpointer)m_pList->aData;
	}

	//�ҵ������������ڴ��
	GMemoryCell* pBlock = m_pList;
	while (pBlock && 0 == pBlock->m_nFree)
	{
		pBlock = pBlock->m_pNext;
	}
		
	if (pBlock)
	{
		//�ҵ��ˣ����з���
		gpointer pFree = pBlock->aData + pBlock->m_nFirst * m_nUnitSize;
		pBlock->m_nFirst = *((gushort*)pFree);
		pBlock->m_nFree--;
		return pFree;
	}
	else
	{
		//û���ҵ���˵��ԭ�����ڴ�鶼���ˣ�Ҫ�ٴη���
		if (0 == m_nGrowSize)
			return NULL;

		pBlock = (GMemoryCell*)new(m_nUnitSize, m_nGrowSize) GMemoryCell(m_nUnitSize, m_nGrowSize);

		if (NULL == pBlock)
			return NULL;

		//����һ�β������
		pBlock->m_pNext = m_pList;
		m_pList = pBlock;

		return (void*)pBlock->aData;
	}
}

gvoid GMemoryPool::Free(gpointer pFree)
{
	//�ҵ�p���ڵ��ڴ��
	GMemoryCell* pBlock = m_pList;
	GMemoryCell* pPreBlock = NULL;
	while (pBlock != NULL && (m_pList->aData > pFree || pBlock->aData + pBlock->m_nSize < pFree))
	{
		pPreBlock = pBlock;
		pBlock = pBlock->m_pNext;
	}

	if (NULL != pBlock)      //���ڴ��ڱ��ڴ����pMyBlock��ָ����ڴ����
	{
		//Step1 �޸���������
		*((gushort*)pFree) = pBlock->m_nFirst;
		pBlock->m_nFirst = (gushort)((gulong)pFree - (gulong)pBlock->aData) / m_nUnitSize;
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
