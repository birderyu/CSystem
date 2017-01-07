#ifndef _CORE_SHARED_POINTER_H_
#define _CORE_SHARED_POINTER_H_

#include "greferencecounter.h"

template <typename ClassT, typename LockT = GMutex>
class GSharedPointer
{
public:
	// count: ��ʼ���ü�����Ĭ��Ϊ1
	GSharedPointer(ClassT *ptr = NULL, gsize count = 1);
	GSharedPointer(const GSharedPointer<ClassT, LockT> &);
	~GSharedPointer();

	// ����ָ��
	gvoid Reset(ClassT *);

	// ָ���Ƿ�ΪNULL
	gbool IsNull() const;

	// ָ���Ƿ񱻹���
	gbool IsShared() const;

	// ���ü���������
	gsize Add();
	gvoid Release();
	gsize Count() const;

	GSharedPointer<ClassT, LockT> &operator=(const GSharedPointer<ClassT, LockT> &);
	ClassT &operator*();
	const ClassT &operator*() const;
	ClassT *operator&();
	const ClassT *operator&() const;
	ClassT *operator->();
	const ClassT *operator->() const;
	
private:
	GReferenceCounter<ClassT, LockT> *m_pRefCounter;
};

#include "gsharedpointer.inl"

#endif // _CORE_SHARED_POINTER_H_