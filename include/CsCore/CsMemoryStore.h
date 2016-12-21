/// �Ƕ������ڴ��
/// ������Ƕ������ڴ�
/// �����ȥ���ڴ治����
/// �̲߳���ȫ

#ifndef _CORE_MEMORY_STORE_H_
#define _CORE_MEMORY_STORE_H_

#include "CsGlobal.h"
#include "CsBlock.h"

class CS_API CsMemoryStore
{
	// �ڴ�ص�Ԫ
	struct CsMemCell
	{
		//�ڴ��
		CsBlock<cs_byte> m_tBlock;

		//���
		cs_size_t m_nCursor;

		//ָ����һ���ڴ��
		CsMemCell *m_pNext;

		CsMemCell(cs_size_t nSize);
		~CsMemCell();
	};

public:
	CsMemoryStore(cs_size_t nInitSzie = 2048, cs_size_t nGrowSize = 1024);
	~CsMemoryStore();

	// �����ڴ棬����ʧ���򷵻�NULL
	cs_pointer Alloc(cs_size_t);

private:
	cs_size_t m_nInitSize;		// ��ʼ��С
	cs_size_t m_nGrowSize;		// ������С
	CsMemCell *m_pList;		// �ڴ������
};

#endif // _CORE_MEMORY_STORE_H_