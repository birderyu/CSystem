#include "gstringpool.h"

GStringPool::GStringPool(gsize nInitSzie, gsize nMaxSize)
:m_tStore(nInitSzie, nInitSzie)
{

}

gpointer GStringPool::Alloc(gsize size)
{
	GMap<gsize, GVector<gaddress>>::ConstIterator citer = m_tRecycle.ConstFind(size);
	if (citer != m_tRecycle.ConstEnd())
	{
		// ���ڴ����վ�л�ȡһ���ڴ棨TODO��
	}
	return m_tStore.Alloc(size);
}

gvoid GStringPool::Free(gpointer)
{

}