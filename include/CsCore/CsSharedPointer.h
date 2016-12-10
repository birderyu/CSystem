#ifndef _CORE_SHARED_POINTER_H_
#define _CORE_SHARED_POINTER_H_

#include "CsReferenceCounter.h"

template <typename ClassT, typename LockT = CsMutex>
class CsSharedPointer
{
public:
	CsSharedPointer(ClassT *ptr = NULL);
	CsSharedPointer(const CsSharedPointer<ClassT, LockT> &);
	~CsSharedPointer();

	// ����ָ��
	cs_void Reset(ClassT *);

	// ָ���Ƿ�ΪNULL
	cs_bool IsNull() const;

	// ָ���Ƿ񱻹���
	cs_bool IsShared() const;

	CsSharedPointer<ClassT, LockT> &operator=(const CsSharedPointer<ClassT, LockT> &);
	ClassT &operator*();
	const ClassT &operator*() const;
	ClassT* operator->();
	const ClassT* operator->() const;
	
private:
	CsReferenceCounter<ClassT, LockT> *m_pRefCounter;
};

#include "CsSharedPointer.inl"

#endif // _CORE_SHARED_POINTER_H_