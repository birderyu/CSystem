#include "gstring.h"

gvoid GString::Free()
{
	GStringStore::Free(m_tStringStore);
}

GString &GString::ToValue()
{
	if (IsReference())
	{
		// �������ͣ�����ת����ֵ
		// TODO
	}
	return *this;
}

gbool GString::IsReference() const
{
	return m_tStringStore.m_nType == GStringStore::STRING_STORE_TYPE_REFERENCE;
}

GStringStore::TYPE GString::GetTypeBySize(gsize size) const
{
	if (size <= GSmallStringStore::MAX_SIZE)
	{
		// С�ַ���
		return GStringStore::STRING_STORE_TYPE_VALUE_SMALL;
	}

	if (size <= GNormalStringStore::MAX_SIZE)
	{
		// ��ͨ�ַ���
		return GStringStore::STRING_STORE_TYPE_VALUE_NORMAL;
	}

	// ���ַ���
	return GStringStore::STRING_STORE_TYPE_VALUE_BIG;
}
