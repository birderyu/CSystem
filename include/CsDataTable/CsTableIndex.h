#ifndef _CORE_INDEX_H_
#define _CORE_INDEX_H_

#include "CsObject.h"

class CsFilter;

template<typename TableT>
class CS_API CsTableIndex
	: public CsObject
{
public:
	enum TYPE
	{
		INDEX_TYPE_NULL = -1,
		INDEX_TYPE_DATA,		// ������������
		INDEX_TYPE_SPATIAL,		// �ռ���������
	};

	// �����
	class CsCursor
	{
		friend class CsTableIndex;
	public:
		CsCursor();
		cs_size_t Size() const;

	public:
		CsCursor &Next();

	private:
		TableT *m_tTable;
		cs_size_t m_nCursor;
		// �кŵļ���
	};

public:
	virtual cs_bool Valid() const = 0;
	virtual cs_void Rebulid() = 0;
	virtual cs_small IndexType() = 0;
	virtual cs_bool Search(const CsFilter &, CsCursor &) = 0;
	virtual cs_bool Sync();

private:
	TableT &m_tTable;
};

#endif // _CORE_INDEX_H_