#ifndef _CORE_INITIALIZER_LIST_H_
#define _CORE_INITIALIZER_LIST_H_

#include "gtype.h"

namespace gsystem { // gsystem

template<class ElemT>
class GInitializerList
{
public:
	typedef ElemT ValueType;
	typedef const ElemT& Reference;
	typedef const ElemT& ConstReference;
	typedef gsize SizeType;

	typedef const ElemT* iterator;
	typedef const ElemT* const_iterator;

	GInitializerList() GNOEXCEPT
		: m_pFirst(0), m_pLast(0)
	{
	}

	GInitializerList(const ElemT *first_arg,
		const ElemT *last_arg) GNOEXCEPT
		: m_pFirst(first_arg), m_pLast(last_arg)
	{
	}

	const ElemT *Begin() const GNOEXCEPT
	{
		return (m_pFirst);
	}

	const ElemT *End() const GNOEXCEPT
	{
		return (m_pLast);
	}

	gsize Size() const _NOEXCEPT
	{
		return ((gsize)(m_pLast - m_pFirst));
	}

private:
	const ElemT *m_pFirst;
	const ElemT *m_pLast;
};

} // namespace gsystem

#endif // _CORE_INITIALIZER_LIST_H_
