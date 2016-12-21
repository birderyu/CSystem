#ifndef _CORE_DATA_INDEX_H_
#define _CORE_DATA_INDEX_H_

#include "CsObject.h"

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

	cs_bool Valid() const;

	// ����
	cs_bool Search(const CsFilter &sFilter) const;

	cs_bool Add();
	cs_bool Remove();

	// �ع�����
	cs_bool Rebulid();
};

#endif // _CORE_TABLE_INDEX_H_