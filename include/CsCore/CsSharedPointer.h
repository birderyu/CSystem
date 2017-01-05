#ifndef _CORE_SHARED_POINTER_H_
#define _CORE_SHARED_POINTER_H_

#include "CsReferenceCounter.h"

template <typename ClassT, typename LockT = CsMutex>
class CsSharedPointer
{
public:
	// count: ��ʼ���ü�����Ĭ��Ϊ1
	CsSharedPointer(ClassT *ptr = NULL, cs_size_t count = 1);
	CsSharedPointer(const CsSharedPointer<ClassT, LockT> &);
	~CsSharedPointer();

	// ����ָ��
	cs_void Reset(ClassT *);

	// ָ���Ƿ�ΪNULL
	cs_bool IsNull() const;

	// ָ���Ƿ񱻹���
	cs_bool IsShared() const;

	// ���ü���������
	cs_size_t Add();
	cs_void Release();
	cs_size_t Count() const;

	CsSharedPointer<ClassT, LockT> &operator=(const CsSharedPointer<ClassT, LockT> &);
	ClassT &operator*();
	const ClassT &operator*() const;
	ClassT *operator&();
	const ClassT *operator&() const;
	ClassT *operator->();
	const ClassT *operator->() const;
	
private:
	CsReferenceCounter<ClassT, LockT> *m_pRefCounter;
};

#include "CsSharedPointer.inl"

#endif // _CORE_SHARED_POINTER_H_