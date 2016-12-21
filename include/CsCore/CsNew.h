#ifndef _CORE_NEW_H_
#define _CORE_NEW_H_

#include <new>
#include "CsMemoryPool.h"
#include "CsLockGuard.h"

CS_API cs_pointer	CsMalloc(cs_size_t size);
CS_API cs_pointer	CsCalloc(cs_size_t n, cs_size_t size);
CS_API cs_pointer	CsRealloc(cs_pointer oldptr, cs_size_t newsize);
CS_API cs_void		CsFree(cs_pointer);
CS_API cs_pointer	CsMemoryCopy(cs_void *dst, const cs_void *src, cs_size_t size);

// NewHandler
class CsNewHander
{
public:
	explicit CsNewHander(std::new_handler nh)
		: handler(nh) {}
	~CsNewHander()
	{
		std::set_new_handler(handler);
	}

private:
	std::new_handler handler;
	CsNewHander(const CsNewHander&);
	CsNewHander &operator=(const CsNewHander&);
};

// �̲߳���ȫ
// �����䵽�ڴ��
// ������NewHandler
template<typename ClassT>
class CsNewT
{
public:
	static cs_pointer operator new(cs_size_t) throw(std::bad_alloc);
	static cs_void operator delete(cs_pointer);
};

// �̲߳���ȫ
// ���䵽�ڴ��
// ������NewHandler
template<typename ClassT>
class CsNewInPoolT
{
public:
	static cs_pointer operator new(cs_size_t) throw(std::bad_alloc);
	static cs_void operator delete(cs_pointer);

private:
	static CsMemoryPool pool;
};

// �̲߳���ȫ
// �����䵽�ڴ��
// ����NewHandler
template<typename ClassT>
class CsNewWithHandlerT
{
public:
	static std::new_handler set_new_handler(std::new_handler p) throw();
	static cs_pointer operator new(cs_size_t) throw(std::bad_alloc);
	static cs_void operator delete(cs_pointer);

private:
	static std::new_handler currentHandler;
};

// �̲߳���ȫ
// ���䵽�ڴ��
// ����NewHandler
template<typename ClassT>
class CsNewInPoolWithHandlerT
{
public:
	static std::new_handler set_new_handler(std::new_handler p) throw();
	static cs_pointer operator new(cs_size_t) throw(std::bad_alloc);
	static cs_void operator delete(cs_pointer);

private:
	static std::new_handler currentHandler;
	static CsMemoryPool pool;
};

// �̰߳�ȫ
// �����䵽�ڴ��
// ������NewHandler
template<typename ClassT, typename LockT>
class CsSafeNewT
{
public:
	static cs_pointer operator new(cs_size_t) throw(std::bad_alloc);
	static cs_void operator delete(cs_pointer);

private:
	static LockT lock;
};

// �̰߳�ȫ
// �����䵽�ڴ��
// ����NewHandler
template<typename ClassT, typename LockT>
class CsSafeNewWithHandlerT
{
public:
	static std::new_handler set_new_handler(std::new_handler p) throw();
	static cs_pointer operator new(cs_size_t) throw(std::bad_alloc);
	static cs_void operator delete(cs_pointer);

private:
	static std::new_handler currentHandler;
	static LockT lock;
};

// �̰߳�ȫ
// ���䵽�ڴ��
// ������NewHandler
template<typename ClassT, typename LockT>
class CsSafeNewInPoolT
{
public:
	static cs_pointer operator new(cs_size_t) throw(std::bad_alloc);
	static cs_void operator delete(cs_pointer);

private:
	static CsMemoryPool pool;
	static LockT lock;
};

// �̰߳�ȫ
// ���䵽�ڴ��
// ����NewHandler
template<typename ClassT, typename LockT>
class CsSafeNewInPoolWithHandlerT
{
public:
	static std::new_handler set_new_handler(std::new_handler p) throw();
	static cs_pointer operator new(cs_size_t) throw(std::bad_alloc);
	static cs_void operator delete(cs_pointer);

private:
	static std::new_handler currentHandler;
	static CsMemoryPool pool;
	static LockT lock;
};

#include "CsNew.inl"

#endif // _CORE_NEW_H_
