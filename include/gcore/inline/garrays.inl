#ifndef _CORE_ARRAYS_INLINE_
#define _CORE_ARRAYS_INLINE_

#include "gallocator.h"
#include "gconstructor.h"

namespace gsystem { // gsystem
namespace detail { // gsystem.detail
namespace arrays { // gsystem.detail.arrays

/// T�������õĹ��캯�������蹹�죬�������ڴ�
template <typename T> GINLINE 
T *_GArrayCreate(gsize size, GTrueType) GEXCEPT(false)
{
	/// ������������Ҫ����
	return GAllocate<T>(size);
}

/// T���������õĹ��캯���������ڴ�֮�����ε���Ԫ�صĹ��캯��
template <typename T> GINLINE 
T *_GArrayCreate(gsize size, GFalseType) GEXCEPT(false)
{
	T *arr = GAllocate<T>(size);
	for (gsize i = 0; i < size; i++)
	{
		GDefaultConstruct<T>(arr + i);
	}
	return arr;
}

/// T���������ͣ�ֱ��ʹ���ڴ濽��������ɿ��������߼�
template <typename T> GINLINE 
T *_GArrayCreate(const T *copy_arr, gsize copy_start, gsize copy_size, GTrueType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(copy_size);
	GMemCopy(new_arr, copy_arr + copy_start, sizeof(T) * copy_size);
	return new_arr;
}

/// T�����������ͣ����ÿ����������캯������
template <typename T> GINLINE 
T *_GArrayCreate(const T *copy_arr, gsize copy_start, gsize copy_size, GFalseType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(copy_size);
	for (gsize i = 0; i < copy_size; i++)
	{
		GCopyConstruct<T>(new_arr + i, copy_arr[i + copy_start]);
	}
	return new_arr;
}

/// T���������ͣ�ֱ��ʹ���ڴ濽��������ɿ��������߼�������Ԫ�����蹹�죬�������ڴ�
template <typename T> GINLINE 
T *_GArrayCreate(gsize size, gsize start, const T *copy_arr, gsize copy_start, gsize copy_size, GTrueType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(size);
	gsize new_copy_size = size - start;
	gsize real_copy_size = copy_size < new_copy_size ? copy_size : new_copy_size;
	GMemCopy(new_arr + start, copy_arr + copy_start, sizeof(T) * real_copy_size);
	return new_arr;
}

/// T�����������ͣ����ÿ����������캯������
template <typename T> GINLINE 
T *_GArrayCreate(gsize size, gsize start, const T *copy_arr, gsize copy_start, gsize copy_size, GFalseType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(size);
	gsize new_copy_size = size - start;

	for (gsize i = 0; i < start; i++)
	{
		GDefaultConstruct<T>(new_arr + i);
	}

	if (copy_size < new_copy_size)
	{
		for (gsize i = start; i < start + copy_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, copy_arr[i + copy_start]);
		}
		for (gsize i = start + copy_size; i < size; i++)
		{
			GDefaultConstruct<T>(new_arr + i);
		}
	}
	else
	{
		for (gsize i = start; i < size; i++)
		{
			GCopyConstruct<T>(new_arr + i, copy_arr[i + copy_start]);
		}
	}

	return new_arr;
}

/// T�������õ��ƶ����캯�����ҵ�ǰ�������������ͣ�ֱ�ӵ����ڴ�����������Ԫ����Ŀ�ĵ���
template <typename T> GINLINE 
T *__GArrayResize(T *old_arr, gsize old_size, gsize new_size, GTrueType) GEXCEPT(false)
{
	return GReallocate<T>(old_arr, new_size);
}

/// T�������õ��ƶ����캯�����ҵ�ǰ�����ǲ��������ͣ�ʹ�ÿ������������ƶ�����
template <typename T> GINLINE 
T *__GArrayResize(T *old_arr, gsize old_size, gsize new_size, GFalseType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(new_size);
	if (old_size < new_size)
	{
		for (gsize i = 0; i < old_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, old_arr[i]);
		}
		for (gsize i = old_size; i < new_size; i++)
		{
			GDefaultConstruct<T>(new_arr + i);
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, old_arr[i]);
		}
	}

	// ���پɵ�����
	GArrays::DestoryArray<T>(old_arr, old_size);
	return new_arr;
}

/// T�������õ��ƶ����캯��������Ҫ����Ԫ�أ���ʱ�������������
template <typename T> GINLINE 
T *_GArrayResize(T *old_arr, gsize old_size, gsize new_size, GTrueType) GEXCEPT(false)
{
	/// ����T�Ƿ����������ͣ����ò�ͬ�Ĵ����߼�
	return __GArrayResize(old_arr, old_size, new_size,
		GTypeTraits<T>::Arithmetic());
}

/// T���������õ��ƶ����캯���������ƶ������������Ԫ�صĹ��죬�������Ԫ�ص���Ĭ�Ϲ��캯��
template <typename T> GINLINE 
T *_GArrayResize(T *old_arr, gsize old_size, gsize new_size, GFalseType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(new_size);
	if (old_size < new_size)
	{
		for (gsize i = 0; i < old_size; i++)
		{
			GMoveConstruct<T>(new_arr + i, GMove(old_arr[i]));
		}
		for (gsize i = old_size; i < new_size; i++)
		{
			GDefaultConstruct<T>(new_arr + i);
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_size; i++)
		{
			GMoveConstruct<T>(new_arr + i, GMove(old_arr[i]));
		}
	}

	// ���پɵ�����
	GArrays::DestoryArray<T>(old_arr, old_size);
	return new_arr;
}

/// T�������õ��ƶ����캯�����ҵ�ǰ�������������ͣ�����ʹ���ڴ����
template <typename T> GINLINE 
T *__GArrayResize(T *old_arr, gsize old_size, gsize new_size, const T &copyable, GTrueType) GEXCEPT(false)
{
	T *new_arr = GReallocate<T>(old_arr, new_size);
	if (old_size < new_size)
	{
		for (gsize i = old_size; i < new_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, copyable);
		}
	}
	return new_arr;
}

/// T�������õ��ƶ����캯�����ҵ�ǰ�����ǲ��������ͣ�ʹ�ÿ������������ƶ�����
template <typename T> GINLINE
T *__GArrayResize(T *old_arr, gsize old_size, gsize new_size, const T &copyable, GFalseType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(new_size);
	if (old_size < new_size)
	{
		for (gsize i = 0; i < old_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, old_arr[i]);
		}
		for (gsize i = old_size; i < new_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, copyable);
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, old_arr[i]);
		}
	}

	// ���پɵ�����
	GArrays::DestoryArray<T>(old_arr, old_size);
	return new_arr;
}

/// T�������õ��ƶ����캯������ʱ�������������
template <typename T> GINLINE 
T *_GArrayResize(T *old_arr, gsize old_size, gsize new_size, const T &copyable, GTrueType) GEXCEPT(false)
{
	/// ����T�Ƿ����������ͣ����ò�ͬ�Ĵ����߼�
	return __GArrayResize(old_arr, old_size, new_size, copyable,
		GTypeTraits<T>::Arithmetic());
}

/// T���������õ��ƶ����캯����ʹ���ƶ�����
template <typename T> GINLINE 
T *_GArrayResize(T *old_arr, gsize old_size, gsize new_size, const T &copyable, GFalseType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(new_size);
	if (old_size < new_size)
	{
		for (gsize i = 0; i < old_size; i++)
		{
			GMoveConstruct<T>(new_arr + i, GMove(old_arr[i]));
		}
		for (gsize i = old_size; i < new_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, copyable);
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_size; i++)
		{
			GMoveConstruct<T>(new_arr + i, GMove(old_arr[i]));
		}
	}

	// ���پɵ�����
	GArrays::DestoryArray<T>(old_arr, old_size);
	return new_arr;
}

/// T�������õ��ƶ����캯�����ҵ�ǰ�������������ͣ�����ʹ�õȺŲ���
template <typename T> GINLINE 
T *__GArrayResize(T *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, GTrueType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(new_size);
	gsize new_real_size = new_start + old_size;

	gsize j = old_start;
	if (new_real_size < new_size)
	{
		for (gsize i = new_start; i < new_real_size; i++)
		{
			new_arr[i] = old_arr[j++];
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = new_start; i < new_size; i++)
		{
			new_arr[i] = old_arr[j++];
		}
	}

	// ���پɵ�����
	GArrays::DestoryArray<T>(old_arr, old_start + old_size);
	return new_arr;
}

/// T�������õ��ƶ����캯�����ҵ�ǰ�����ǲ��������ͣ�ʹ�ÿ������������ƶ�����
template <typename T> GINLINE 
T *__GArrayResize(T *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, GFalseType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(new_size);
	gsize new_real_size = new_start + old_size;

	gsize j = old_start;
	if (new_real_size < new_size)
	{
		for (gsize i = 0; i < new_start; i++)
		{
			GDefaultConstruct<T>(new_arr + i);
		}
		for (gsize i = new_start; i < new_real_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, old_arr[j++]);
		}
		for (gsize i = new_real_size; i < new_size; i++)
		{
			GDefaultConstruct<T>(new_arr + i);
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_start; i++)
		{
			GDefaultConstruct<T>(new_arr + i);
		}
		for (gsize i = new_start; i < new_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, old_arr[j++]);
		}
	}

	// ���پɵ�����
	GArrays::DestoryArray<T>(old_arr, old_start + old_size);
	return new_arr;
}

/// T�������õ��ƶ����캯������ʱ�������������
template <typename T> GINLINE 
T *_GArrayResize(T *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, GTrueType) GEXCEPT(false)
{
	/// ����T�Ƿ����������ͣ����ò�ͬ�Ĵ����߼�
	return __GArrayResize(old_arr, old_start, old_size, new_size, new_start,
		GTypeTraits<T>::Arithmetic());
}

/// T���������õ��ƶ����캯����ʹ���ƶ�����
template <typename T> GINLINE 
T *_GArrayResize(T *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, GFalseType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(new_size);
	gsize new_real_size = new_start + old_size;
	gsize j = old_start;

	if (new_real_size < new_size)
	{
		for (gsize i = 0; i < new_start; i++)
		{
			GDefaultConstruct<T>(new_arr + i);
		}
		for (gsize i = new_start; i < new_real_size; i++)
		{
			GMoveConstruct<T>(new_arr + i, GMove(old_arr[j++]));
		}
		for (gsize i = new_real_size; i < new_size; i++)
		{
			GDefaultConstruct<T>(new_arr + i);
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_start; i++)
		{
			GDefaultConstruct<T>(new_arr + i);
		}
		for (gsize i = new_start; i < new_size; i++)
		{
			GMoveConstruct<T>(new_arr + i, GMove(old_arr[j++]));
		}
	}

	// ���پɵ�����
	GArrays::DestoryArray<T>(old_arr, old_start + old_size);
	return new_arr;
}

/// T�������õ��ƶ����캯�����ҵ�ǰ�������������ͣ�����ʹ�õȺŲ���
template <typename T> GINLINE 
T *__GArrayResize(T *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const T &copyable, GTrueType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(new_size);
	gsize new_real_size = new_start + old_size;

	gsize j = old_start;
	if (new_real_size < new_size)
	{
		for (gsize i = 0; i < new_start; i++)
		{
			new_arr[i] = copyable;
		}
		for (gsize i = new_start; i < new_real_size; i++)
		{
			new_arr[i] = old_arr[j++];
		}
		for (gsize i = new_real_size; i < new_size; i++)
		{
			new_arr[i] = copyable;
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_start; i++)
		{
			new_arr[i] = copyable;
		}
		for (gsize i = new_start; i < new_size; i++)
		{
			new_arr[i] = old_arr[j++];
		}
	}

	// ���پɵ�����
	GArrays::DestoryArray<T>(old_arr, old_start + old_size);
	return new_arr;
}

/// T�������õ��ƶ����캯�����ҵ�ǰ�����ǲ��������ͣ�ʹ�ÿ������������ƶ�����
template <typename T> GINLINE 
T *__GArrayResize(T *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const T &copyable, GFalseType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(new_size);
	gsize new_real_size = new_start + old_size;

	gsize j = old_start;
	if (new_real_size < new_size)
	{
		for (gsize i = 0; i < new_start; i++)
		{
			GCopyConstruct<T>(new_arr + i, copyable);
		}
		for (gsize i = new_start; i < new_real_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, old_arr[j++]);
		}
		for (gsize i = new_real_size; i < new_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, copyable);
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_start; i++)
		{
			GCopyConstruct<T>(new_arr + i, copyable);
		}
		for (gsize i = new_start; i < new_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, old_arr[j++]);
		}
	}

	// ���پɵ�����
	GArrays::DestoryArray<T>(old_arr, old_start + old_size);
	return new_arr;
}

/// T�������õ��ƶ����캯������ʱ�������������
template <typename T> GINLINE 
T *_GArrayResize(T *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const T &copyable, GTrueType) GEXCEPT(false)
{
	/// ����T�Ƿ����������ͣ����ò�ͬ�Ĵ����߼�
	return __GArrayResize(old_arr, old_start, old_size, new_size, new_start, copyable,
		GTypeTraits<T>::Arithmetic());
}

/// T���������õ��ƶ����캯����ʹ���ƶ�����
template <typename T> GINLINE 
T *_GArrayResize(T *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const T &copyable, GFalseType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(new_size);
	gsize new_real_size = new_start + old_size;
	gsize j = old_start;

	if (new_real_size < new_size)
	{
		for (gsize i = 0; i < new_start; i++)
		{
			GCopyConstruct<T>(new_arr + i, copyable);
		}
		for (gsize i = new_start; i < new_real_size; i++)
		{
			GMoveConstruct<T>(new_arr + i, GMove(old_arr[j++]));
		}
		for (gsize i = new_real_size; i < new_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, copyable);
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_start; i++)
		{
			GCopyConstruct<T>(new_arr + i, copyable);
		}
		for (gsize i = new_start; i < new_size; i++)
		{
			GMoveConstruct<T>(new_arr + i, GMove(old_arr[j++]));
		}
	}

	// ���پɵ�����
	GArrays::DestoryArray<T>(old_arr, old_start + old_size);
	return new_arr;
}

/// T�������õ��ƶ����캯�����ҵ�ǰ�������������ͣ�ʹ���ڴ濽��
template <typename T> GINLINE 
T *__GArrayRemoveAt(T *arr, gsize size, gsize pos, GTrueType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(size - 1);
	if (pos > 0)
	{
		GMemCopy(new_arr, arr, sizeof(T) * pos);
	}
	GMemCopy(new_arr + pos, arr + pos + 1, sizeof(T) * (size - pos - 1));

	// ���پɵ�����
	GArrays::DestoryArray<T>(arr, size);
	return new_arr;
}

/// T�������õ��ƶ����캯�����ҵ�ǰ�������������ͣ�ʹ�ÿ�������
template <typename T> GINLINE 
T *__GArrayRemoveAt(T *arr, gsize size, gsize pos, GFalseType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(size - 1);
	for (gsize i = 0; i < pos; i++)
	{
		GCopyConstruct<T>(new_arr + i, arr[i]);
	}
	for (gsize i = pos + 1; i < size; i++)
	{
		GCopyConstruct<T>(new_arr + i - 1, arr[i]);
	}

	// ���پɵ�����
	GArrays::DestoryArray<T>(arr, size);
	return new_arr;
}

/// T�������õ��ƶ����캯������ʱ�������������
template <typename T> GINLINE 
T *_GArrayRemoveAt(T *arr, gsize size, gsize pos, GTrueType) GEXCEPT(false)
{
	/// ����T�Ƿ����������ͣ����ò�ͬ�Ĵ����߼�
	return __GArrayRemoveAt(arr, size, pos,
		GTypeTraits<T>::Arithmetic());
}

/// T���������õ��ƶ����캯����ʹ���ƶ�����
template <typename T> GINLINE 
T *_GArrayRemoveAt(T *arr, gsize size, gsize pos, GFalseType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(size - 1);
	for (gsize i = 0; i < pos; i++)
	{
		GMoveConstruct<T>(new_arr + i, GMove(arr[i]));
	}
	for (gsize i = pos + 1; i < size; i++)
	{
		GMoveConstruct<T>(new_arr + i - 1, GMove(arr[i]));
	}

	// ���پɵ�����
	GArrays::DestoryArray<T>(arr, size);
	return new_arr;
}

/// T���������õ�����������������
template <typename T> GINLINE 
gvoid _GArrayClear(T *arr, gsize size, GTrueType) GNOEXCEPT
{

}

/// T���������õ��������������ε�����������
template <typename T> GINLINE 
gvoid _GArrayClear(T *arr, gsize size, GFalseType) GNOEXCEPT
{
	if (!arr)
	{
		return;
	}
	for (gsize i = 0; i < size; i++)
	{
		arr[i].~T();
	}
}

/// T���������ͣ�������������ֱ��ʹ���ڴ濽��
template <typename T> GINLINE 
gvoid _GArrayCopyFrom(T *arr, gsize size, const T *copy_arr, GTrueType)
{
	GMemCopy(arr, copy_arr, sizeof(T) * size);
}

/// T�����������ͣ����������ڵ��ÿ�������
template <typename T> GINLINE 
gvoid _GArrayCopyFrom(T *arr, gsize size, const T *copy_arr, GFalseType) GEXCEPT(false)
{
	for (gsize i = 0; i < size; i++)
	{
		// ����ԭ��Ԫ��
		GDestruct<T>(arr + i);

		// ���������µ�Ԫ��
		GCopyConstruct<T>(arr + i, copy_arr[i]);
	}
}

/// T���������ͣ�������������ֱ��ʹ���ڴ濽��
template <typename T> GINLINE 
T *_GArrayCopyFrom(T *arr, gsize size, const T *copy_arr, gsize copy_size, GTrueType) GEXCEPT(false)
{
	if (size != copy_size)
	{
		GDeallocate<T>(arr);
		arr = GAllocate<T>(copy_size);
	}

	GMemCopy(arr, copy_arr, sizeof(T) * copy_size);
	return arr;
}

/// T�����������ͣ����������ٵ��ÿ�������
template <typename T> GINLINE 
T *_GArrayCopyFrom(T *arr, gsize size, const T *copy_arr, gsize copy_size, GFalseType) GEXCEPT(false)
{
	for (gsize i = 0; i < size; i++)
	{
		GDestruct<T>(arr + i);
	}
	if (size != copy_size)
	{
		GDeallocate<T>(arr);
		arr = GAllocate<T>(copy_size);
	}
	for (gsize i = 0; i < copy_size; i++)
	{
		GCopyConstruct<T>(arr + i, copy_arr[i]);
	}
	return arr;
}

} // namespace gsystem.detail.arrays
} // namespace gsystem.detail
} // namespace gsystem

namespace gsystem { // gsystem

template <typename T> GINLINE
T *GArrays::CreateArray(gsize size) GEXCEPT(false)
{
	GASSERT(size > 0);

	/// ����T�Ƿ�������õ�Ĭ�Ϲ��캯����ȥ���ò�ͬ�Ĵ����߼�
	return detail::arrays::_GArrayCreate<T>(size,
		GTypeTraits<T>::TrivialDefaultConstructible());
}

template <typename T> GINLINE
T *GArrays::CreateArray(gsize size, const T &copyable) GEXCEPT(false)
{
	GASSERT(size > 0);

	T *arr = GAllocate<T>(size);
	for (gsize i = 0; i < size; i++)
	{
		// ��GConstruct�ĵ��ù����У��Ѿ�����������������͵Ĵ����߼�
		GCopyConstruct<T>(arr + i, copyable);
	}
	return arr;
}

template <typename T> GINLINE 
T *GArrays::CreateArray(const T *copy_arr, gsize copy_start, gsize copy_size) GEXCEPT(false)
{
	// ��copy_arr�����ڣ�����copy_start�����˷�Χ����ᱨ��
	GASSERT(copy_arr && copy_start < copy_size);

	// ����T�Ƿ����������ͣ�ȥ���ò�ͬ�Ĵ����߼�
	return detail::arrays::_GArrayCreate<T>(copy_arr, copy_start, copy_size,
		GTypeTraits<T>::Arithmetic());
}

template <typename T> GINLINE
T *GArrays::CreateArray(gsize size, gsize start, const T *copy_arr, gsize copy_start, gsize copy_size) GEXCEPT(false)
{
	GASSERT(start < size && copy_arr && copy_start < copy_size);

	// ����T�Ƿ����������ͣ�ȥ���ò�ͬ�Ĵ����߼�
	return detail::arrays::_GArrayCreate(size, start, copy_arr, copy_start, copy_size,
		GTypeTraits<T>::Arithmetic());
}

template <typename T> GINLINE
T *GArrays::ResizeArray(T *old_arr, gsize old_size, gsize new_size) GEXCEPT(false)
{
	// �ж�T�Ƿ�����ƶ����캯�������ж��Ƿ���Ҫ���ò�ͬ�ĺ���
	return detail::arrays::_GArrayResize<T>(old_arr, old_size, new_size,
		GTypeTraits<T>::TrivialMoveConstructible());
}

template <typename T> GINLINE
T *GArrays::ResizeArray(T *old_arr, gsize old_size, gsize new_size, const T &copyable) GEXCEPT(false)
{
	// �ж�T�Ƿ�����ƶ����캯�������ж��Ƿ���Ҫ���ò�ͬ�ĺ���
	return detail::arrays::_GArrayResize<T>(old_arr, old_size, new_size, copyable,
		GTypeTraits<T>::TrivialMoveConstructible());
}

template <typename T> GINLINE
T *GArrays::ResizeArray(T *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start) GEXCEPT(false)
{
	GASSERT(old_start < old_size);

	// �ж�T�Ƿ�����ƶ����캯�������ж��Ƿ���Ҫ���ò�ͬ�ĺ���
	return detail::arrays::_GArrayResize<T>(old_arr, old_start, old_size, new_size, new_start,
		GTypeTraits<T>::TrivialMoveConstructible());
}

template <typename T> GINLINE
T *GArrays::ResizeArray(T *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const T &copyable) GEXCEPT(false)
{
	// �ж�T�Ƿ�����ƶ����캯�������ж��Ƿ���Ҫ���ò�ͬ�ĺ���
	return detail::arrays::_GArrayResize<T>(old_arr, old_start, old_size, new_size, new_start, copyable,
		GTypeTraits<T>::TrivialMoveConstructible());
}

template <typename T> GINLINE
T *GArrays::RemoveArrayElementAt(T *arr, gsize size, gsize pos) GEXCEPT(false)
{
	GASSERT(size > 0 && pos < size);

	// �ж�T�Ƿ�����ƶ����캯�������ж��Ƿ���Ҫ���ò�ͬ�ĺ���
	return detail::arrays::_GArrayRemoveAt(arr, size, pos,
		GTypeTraits<T>::TrivialMoveConstructible());
}

template <typename T> GINLINE
gvoid GArrays::ClearArray(T *arr, gsize size) GNOEXCEPT
{
	detail::arrays::_GArrayClear(arr, size,
		GTypeTraits<T>::TrivialDestructible());
}

template <typename T> GINLINE
gvoid GArrays::DestoryArray(T *arr, gsize size) GNOEXCEPT
{
	// �ж�T�Ƿ�����������������ж��Ƿ���Ҫ���ò�ͬ�ĺ���
	detail::arrays::_GArrayClear(arr, size,
		GTypeTraits<T>::TrivialDestructible());

	// �ͷ��ڴ�
	GDeallocate<T>(arr);
}

template <typename T> GINLINE
gvoid GArrays::CopyArrayFrom(T *arr, gsize size, const T *copy_arr) GEXCEPT(false)
{
	GASSERT(arr && copy_arr);

	// �ж�T�Ƿ��ǻ������ͣ����ж��Ƿ���Ҫ���ò�ͬ�ĺ���
	detail::arrays::_GArrayCopyFrom<T>(arr, size, copy_arr,
		GTypeTraits<T>::Arithmetic());
}

template <typename T> GINLINE 
T *GArrays::CopyArrayFrom(T *arr, gsize size, const T *copy_arr, gsize copy_size) GEXCEPT(false)
{
	GASSERT(arr && copy_arr);

	// �ж�T�Ƿ��ǻ������ͣ����ж��Ƿ���Ҫ���ò�ͬ�ĺ���
	return detail::arrays::_GArrayCopyFrom<T>(arr, size, copy_arr, copy_size,
		GTypeTraits<T>::Arithmetic());
}

}  // namespace gsystem

#endif // _CORE_ARRAYS_INLINE_
