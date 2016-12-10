#ifndef _CORE_DATA_INDEX_H_
#define _CORE_DATA_INDEX_H_

#include "CsObject.h"

class CsFilter;

// value��һ���޷�������ֵ����ʾ�к�
// value�������ظ�
class CsDataIndex
{
public:
	enum TYPE
	{
		INDEX_TYPE_NULL = -1,
		INDEX_TYPE_ORDER,		// �������������keyֵ�������򣬿���֧��>��>=��<��<=�Ȳ���
		INDEX_TYPE_UNORDER,		// �����������ٶȽϿ죬��֧��=����
		INDEX_TYPE_GEOMETRY,	// �ռ����������ܽ��пռ��ѯ
	};

public:
	virtual ~CsDataIndex();

	cs_bool Valid() const;

	// ����
	cs_bool Search(const CsFilter &sFilter) const;

	cs_bool Add();
	cs_bool Remove();

	// �ع�����
	cs_bool Rebulid();
};

#endif // _CORE_TABLE_INDEX_H_