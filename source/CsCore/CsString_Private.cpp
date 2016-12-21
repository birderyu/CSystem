#include "CsString.h"

cs_void CsString::Free()
{
	CsStringStore::Free(m_tStringStore);
}

CsString &CsString::ToValue()
{
	if (IsReference())
	{
		// �������ͣ�����ת����ֵ
		// TODO
	}
	return *this;
}

cs_bool CsString::IsReference() const
{
	return m_tStringStore.m_nType == CsStringStore::STRING_STORE_TYPE_REFERENCE;
}

CsStringStore::TYPE CsString::GetTypeBySize(cs_size_t size) const
{
	if (size <= CsSmallStringStore::MAX_SIZE)
	{
		// С�ַ���
		return CsStringStore::STRING_STORE_TYPE_VALUE_SMALL;
	}

	if (size <= CsNormalStringStore::MAX_SIZE)
	{
		// ��ͨ�ַ���
		return CsStringStore::STRING_STORE_TYPE_VALUE_NORMAL;
	}

	// ���ַ���
	return CsStringStore::STRING_STORE_TYPE_VALUE_BIG;
}
