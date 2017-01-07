#ifndef _CORE_NEW_H_
#define _CORE_NEW_H_

#include <new>
#include "gmemorypool.h"
#include "glockguard.h"

GAPI gpointer	GMalloc(gsize size);
GAPI gpointer	GCalloc(gsize n, gsize size);
GAPI gpointer	GRealloc(gpointer oldptr, gsize newsize);
GAPI gvoid		GFree(gpointer);
GAPI gpointer	GMemCopy(gvoid *dst, const gvoid *src, gsize size);
GAPI gpointer	GMemMove(gvoid *dst, const gvoid *src, gsize size);
GAPI gpointer	GMemSet(gvoid *dst, gbyte value, gsize size);

// NewHandler
class GNewHander
{
public:
	explicit GNewHander(std::new_handler nh)
		: handler(nh) {}
	~GNewHander()
	{
		std::set_new_handler(handler);
	}

private:
	std::new_handler handler;
	GNewHander(const GNewHander&);
	GNewHander &operator=(const GNewHander&);
};

// �̲߳���ȫ
// �����䵽�ڴ��
// ������NewHandler
template<typename ClassT>
class GNewT
{
public:
	static gpointer operator new(gsize) throw(std::bad_alloc);
	static gvoid operator delete(gpointer);
};

// �̲߳���ȫ
// ���䵽�ڴ��
// ������NewHandler
template<typename ClassT>
class GNewInPoolT
{
public:
	static gpointer operator new(gsize) throw(std::bad_alloc);
	static gvoid operator delete(gpointer);

private:
	static GMemoryPool pool;
};

// �̲߳���ȫ
// �����䵽�ڴ��
// ����NewHandler
template<typename ClassT>
class GNewWithHandlerT
{
public:
	static std::new_handler set_new_handler(std::new_handler p) throw();
	static gpointer operator new(gsize) throw(std::bad_alloc);
	static gvoid operator delete(gpointer);

private:
	static std::new_handler currentHandler;
};

// �̲߳���ȫ
// ���䵽�ڴ��
// ����NewHandler
template<typename ClassT>
class GNewInPoolWithHandlerT
{
public:
	static std::new_handler set_new_handler(std::new_handler p) throw();
	static gpointer operator new(gsize) throw(std::bad_alloc);
	static gvoid operator delete(gpointer);

private:
	static std::new_handler currentHandler;
	static GMemoryPool pool;
};

// �̰߳�ȫ
// �����䵽�ڴ��
// ������NewHandler
template<typename ClassT, typename LockT>
class GSafeNewT
{
public:
	static gpointer operator new(gsize) throw(std::bad_alloc);
	static gvoid operator delete(gpointer);

private:
	static LockT lock;
};

// �̰߳�ȫ
// �����䵽�ڴ��
// ����NewHandler
template<typename ClassT, typename LockT>
class GSafeNewWithHandlerT
{
public:
	static std::new_handler set_new_handler(std::new_handler p) throw();
	static gpointer operator new(gsize) throw(std::bad_alloc);
	static gvoid operator delete(gpointer);

private:
	static std::new_handler currentHandler;
	static LockT lock;
};

// �̰߳�ȫ
// ���䵽�ڴ��
// ������NewHandler
template<typename ClassT, typename LockT>
class GSafeNewInPoolT
{
public:
	static gpointer operator new(gsize) throw(std::bad_alloc);
	static gvoid operator delete(gpointer);

private:
	static GMemoryPool pool;
	static LockT lock;
};

// �̰߳�ȫ
// ���䵽�ڴ��
// ����NewHandler
template<typename ClassT, typename LockT>
class GSafeNewInPoolWithHandlerT
{
public:
	static std::new_handler set_new_handler(std::new_handler p) throw();
	static gpointer operator new(gsize) throw(std::bad_alloc);
	static gvoid operator delete(gpointer);

private:
	static std::new_handler currentHandler;
	static GMemoryPool pool;
	static LockT lock;
};

#include "gnew.inl"

#endif // _CORE_NEW_H_
