#ifndef _CORE_STRING_LIST_H_
#define _CORE_STRING_LIST_H_

#include "CsStringPool.h"
#include "CsString.h"
#include <map>

enum CS_STRING_TYPE
{
	STRING_TYPE_VALUE,
	STRING_TYPE_REFERENCE,
};

class CS_API CsStringList
{
public:
	CsString GetAt(cs_size_t, CS_STRING_TYPE emStrType = STRING_TYPE_VALUE) const;

	cs_bool Add(const CsString &);
	cs_bool SetAt(cs_size_t, const CsString &);
	cs_bool RemoveAt(cs_size_t);

	cs_size_t Length() const;

	// ���շ������õ��ڴ�
	// �������ͬ����ռ��һ����ʱ��
	// ����֮�������͵�String��ʧЧ
	cs_bool Collect();

private:
	CsStringPool m_tPool;
	std::map<cs_size_t, cs_pointer> m_t; // <�±ָ꣬��>
};

#endif // _CORE_STRING_LIST_H_