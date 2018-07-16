
/********************************************************************************
**
** gsystem: A quick, micro library of C++
**
** @file gseries.h
** @brief ��������ṹ
** @author birderyu
** @contact https://github.com/birderyu
** @date 2016-12-03
** @version 1.0.0
**
** Ϊ��ʹ�ô��ṹ��String�����Ӹ�Ч�������˸�Ч����ջ�ռ�����ݽṹGSeries����ӵ�������ص㣺
** 1��Ϊ��֧�ִ������ڴ󲿷�ʹ�ó����У��䳤�ȶ��������ַ����У����ַ���Ƶ�����֣�����Ԫ����
** ����С���������ݴ洢�ڱ��ؿռ䣨ջ�ռ䣩�У�
** 2��Ϊ��֧�ִ��ڴ󲿷�ʱ����ʵ����ֻ���������龰��֧��COW��copy-on-write��дʱ��������
**
********************************************************************************/
#ifndef _CORE_SERIES_H_
#define _CORE_SERIES_H_

#include "garray.h"
#include "garrays.h"

namespace gsystem { // gsystem

/********************************************************************************
**
** @brief ��������
** @template T {type} ����Ԫ�ص�����
** @template LOCAL_SIZE {gsize} ���ؿռ��Ԫ�ظ���
** @template HAS_END_FLAG {gbool} �Ƿ����������־����C����ַ������ַ�0��Ϊ������־��
**     Ĭ��Ϊfalse
** @template END_FLAG {T} ������־����HAS_END_FLAGΪtrueʱ��Ч
**
********************************************************************************/
template<typename T, 
	gsize LOCAL_SIZE,
	gbool HAS_END_FLAG = false, 
	T END_FLAG = T()>
class GSeries
{
public:
	static const gsize MIN_CAPACITY = HAS_END_FLAG ? (LOCAL_SIZE - 1) : LOCAL_SIZE;
	static_assert(MIN_CAPACITY > 0, "MIN_CAPACITY must greater than zero.");

public:
	static GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> CopyOf(const T *copy_arr, gsize copy_size);
	static GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> ReferenceOf(const T *ref_arr, gsize ref_size);

public:
	/****************************************************************************
	**
	** @name GSeries
	** @brief ���캯����constructor��
	** @param [in] capacity {gsize} Ĭ��Ԫ�ص�����
	**
	****************************************************************************/
	GSeries(gsize capacity = 0);

	/****************************************************************************
	**
	** @name GSeries
	** @brief ���캯����constructor��
	** @param [in] arr {const T *} �������������׵�ַ
	** @param [in] size {gsize} �������������Ԫ�ظ���
	**
	****************************************************************************/
	GSeries(const T *arr, gsize size);

	/****************************************************************************
	**
	** @name GSeries
	** @brief ���캯����constructor��
	** @param [in] arr {const GArray<T> &} ����
	**
	****************************************************************************/
	GSeries(const GArray<T> &arr);

	/****************************************************************************
	**
	** @name GSeries
	** @brief ���캯����constructor��
	** @param [in] arr {GArray<T> &&} ����
	**
	****************************************************************************/
	GSeries(GArray<T> &&arr);

	/****************************************************************************
	**
	** @name GSeries
	** @brief �������캯����copy constructor��
	** @param [in] arr {const GSeries &} ����
	**
	****************************************************************************/
	GSeries(const GSeries &arr);

	/****************************************************************************
	**
	** @name GSeries
	** @brief �ƶ����캯����move constructor��
	** @param [in] arr {GSeries &&} ����
	**
	****************************************************************************/
	GSeries(GSeries &&arr);

	/****************************************************************************
	**
	** @name ~GSeries
	** @brief ����������destructor��
	**
	****************************************************************************/
	~GSeries();

	GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &operator=(const GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &arr);
	GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &operator=(GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &&arr);

	gsize Size() const;
	gsize Capacity() const;

	gbool IsEmpty() const;

	gvoid Resize(gsize size);
	gvoid Reserve(gsize capacity);

	const T &ConstGetAt(gsize pos) const;
	const T &GetAt(gsize pos) const;
	T &GetAt(gsize pos);

	const T *ConstCursorAt(gsize pos) const;
	const T *CursorAt(gsize pos) const;
	T *CursorAt(gsize pos);

	const T *ConstStart() const;
	const T *Start() const;
	T *Start();

	gvoid SetAt(gsize pos, const T &data);
	gvoid SetAt(gsize pos, T &&data);

	// ������飬���ͷ��ڴ�
	gvoid Clear();

	// �������鲢�������ÿ�
	gvoid Destroy();

	// ��һ��������ӵ�ĩβ
	gvoid Append(const GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &series);
	gvoid Append(GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &&series);

	const T &operator[](gsize pos) const;
	T &operator[](gsize pos);

private:
	// ע�⣬�����������ĵ�����Ҫ���أ�������Ϊ���������������˳�ʼ����δ��ԭ�����������ڴ����
	gvoid CopyConstruct(const T *copy_arr, gsize copy_size);
	gvoid MoveConstruct(T *&move_arr, gsize move_size);
	gvoid ReferenceConstruct(const T *ref_arr, gsize ref_size);

	gvoid Free(); // ��������

	gbool IsReference() const;

	// ����������ת����ֵ����
	gvoid ToValue(gsize capacity);

private:
	T *m_pStart;
	gsize m_nSize;
	gsize m_nCapacity;
	union
	{
		T  m_tArray[LOCAL_SIZE];
		T *m_pArray;
	};
	gbyte m_nType;
};

GAPI typedef GSeries<gbyte, 4, false, 0> GBytesData;
GAPI typedef GSeries<gchar8, 8, true, 0> GString8Data;
GAPI typedef GSeries<gchar16, 4, true, 0> GString16Data;
GAPI typedef GSeries<gchar32, 2, true, 0> GString32Data;
GAPI typedef GSeries<gwchar, 4, true, 0> GWStringData;

} // namespace gsystem

#include "inline/gseries.inl"

#endif // _CORE_SERIES_H_