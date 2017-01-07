#ifndef _CORE_DATA_INDEX_H_
#define _CORE_DATA_INDEX_H_

#include "gobject.h"

class CsFilter;

// value��һ���޷�������ֵ����ʾ�к�
// value�������ظ�
class CsTableDataIndex
{
public:
	enum DATA_INDEX_TYPE
	{
		INDEX_TYPE_ORDER,		// �������������keyֵ�������򣬿���֧��>��>=��<��<=�Ȳ���
		INDEX_TYPE_UNORDER,		// �����������ٶȽϿ죬��֧��=����
	};

public:
	virtual ~CsTableDataIndex();

	gbool Valid() const;

	// ����
	gbool Search(const CsFilter &sFilter) const;

	gbool Add();
	gbool Remove();

	// �ع�����
	gbool Rebulid();
};

#endif // _CORE_TABLE_INDEX_H_