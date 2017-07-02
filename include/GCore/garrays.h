#ifndef _CORE_ARRAYS_H_
#define _CORE_ARRAYS_H_

#include "gtype.h"

namespace gsystem { // gsystem

class GArrays
{
public:
	/****************************************************************************
	**
	** @name CreateArray
	** @brief ��̬����������һ������Ϊsize������
	** @param [in] size {gsize} ������������ĳ���
	** @return {DataT *} ���ش���������׵�ַ��������ʧ�ܣ��򷵻�GNULL
	**
	** ����һ������Ϊsize�����飬�����ÿһ��Ԫ�ص�Ĭ�Ϲ��캯����
	**
	****************************************************************************/
	template <typename DataT> static DataT *CreateArray(gsize size) GEXCEPT(false);

	/****************************************************************************
	**
	** @name CreateArray
	** @brief ��̬����������һ������Ϊsize�����飬�Ҷ�ÿһ��Ԫ�ظ���ʼֵ
	** @param [in] size {gsize} ������������ĳ���
	** @param [in] copyable {const DataT &} ��������Ԫ��ֵ
	** @return {DataT *} ���ش���������׵�ַ��������ʧ�ܣ��򷵻�GNULL
	**
	** ����һ������Ϊsize�����飬������ʹ��copyableȥ��ʼ�������е�ÿһ��Ԫ�أ��ڳ�ʼ���Ĺ�����
	**     �����ÿһ��Ԫ�صĿ������캯����
	**
	****************************************************************************/
	template <typename DataT> static DataT *CreateArray(gsize size, const DataT &copyable) GEXCEPT(false);

	/****************************************************************************
	**
	** @name CreateArray
	** @brief ��̬��������������һ�������һ����Ԫ�س�Ϊһ���µ�����
	** @param [in] copy_arr {const DataT *} ��������������׵�ַ
	** @param [in] copy_start_pos {gsize} �������������ʼδ֪
	** @param [in] copy_size {gsize} ϣ�������ĳ���
	** @return {DataT *} ���ش���������׵�ַ��������ʧ�ܣ��򷵻�GNULL
	**
	** ������copy_arr��copy_start_pos��Ԫ�أ���0��ʼ��������ʼ��copy_size��Ԫ�ؿ���������
	**     ����һ���µ����飬�ڳ�ʼ��������Ĺ����У������ÿһ��Ԫ�صĿ������캯����
	**
	****************************************************************************/
	template <typename DataT> static DataT *CreateArray(const DataT *copy_arr, gsize copy_start_pos, gsize copy_size) GEXCEPT(false);

	/// ��̬����������һ������Ϊsize�����飬����copy_arr�ĵ�copy_start���copy_sizeԪ��ȥ��ʼ���µ�����ĵ�start��ʼ��copy_size��Ԫ��
	/// �����Ԫ��ʹ��Ĭ�ϵĹ��캯������
	template <typename DataT>
	static DataT *CreateArray(gsize size, gsize start, const DataT *copy_arr, gsize copy_start, gsize copy_size) GEXCEPT(false);

	/// ��̬������������old_arr������Ԫ����Ŀ��old_size����Ϊnew_size
	/// �������鲻���ڣ�old_arr == GNULL && old_size == 0�����ᴴ��һ������Ϊnew_size���µ�����
	/// �ڵ�����С�Ĺ����У����µ�����Ԫ����Ŀ����ԭ����Ŀ���ᴴ���µ�Ԫ�أ���֮���в���Ԫ�ر�����
	/// �ڵ�����С�Ĺ����У������ȵ����ƶ�����
	template <typename DataT>
	static DataT *ResizeArray(DataT *old_arr, gsize old_size, gsize new_size) GEXCEPT(false);

	/// ��̬������������old_arr������Ԫ����Ŀ��old_size����Ϊnew_size
	/// �ڵ�����С�Ĺ����У����µ�����Ԫ����Ŀ����ԭ����Ŀ������copyableȥ��ʼ���µ�Ԫ�أ���֮���в���Ԫ�ر�����
	/// �ڵ�����С�Ĺ����У������ȵ����ƶ�����
	template <typename DataT>
	static DataT *ResizeArray(DataT *old_arr, gsize old_size, gsize new_size, const DataT &copyable) GEXCEPT(false);

	/// ��̬������������old_arr������Ԫ����Ŀ����Ϊnew_size
	/// �ڵ�����С�Ĺ����У�������ԭ������Ĵ�old_startλ��ʼ��old_size��Ԫ�أ����õ�������ĵ�new_startλ
	/// �ڵ�����С�Ĺ����У������ȵ����ƶ�����
	template <typename DataT>
	static DataT *ResizeArray(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start) GEXCEPT(false);

	/// ��̬������������old_arr������Ԫ����Ŀ����Ϊnew_size
	/// �ڵ�����С�Ĺ����У�������ԭ������Ĵ�old_startλ��ʼ��old_size��Ԫ�أ����õ�������ĵ�new_startλ
	/// �ڵ�����С�Ĺ����У��´���������Ԫ�أ���ʹ��copyable���г�ʼ��
	/// �ڵ�����С�Ĺ����У������ȵ����ƶ�����
	template <typename DataT>
	static DataT *ResizeArray(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const DataT &copyable) GEXCEPT(false);

	/// ��̬�������Ƴ������е�ĳһλԪ�أ�����Ƴ�����Ԫ�ص�����������
	template <typename DataT>
	static DataT *RemoveArrayElementAt(DataT *arr, gsize size, gsize pos) GEXCEPT(false);

	/// ��̬����������һ�����飬�����ε���ÿһ��Ԫ�ص���������
	template <typename DataT>
	static gvoid DestoryArray(DataT *arr, gsize size) GNOEXCEPT;

	/// ��̬���������ε���ÿһ��Ԫ�ص��������������ͷ��ڴ�
	template <typename DataT>
	static gvoid ClearArray(DataT *arr, gsize size) GNOEXCEPT;

	/// ��̬������������copy_arr�����ݿ�����arr��
	/// ���뱣֤copy_arr���ٰ�����size��Ԫ��
	template <typename DataT>
	static gvoid CopyArrayFrom(DataT *arr, gsize size, const DataT *copy_arr) GEXCEPT(false);

	/// ��̬������������copy_arr�����ݿ�����arr��
	/// �ڿ����Ĺ����У�arr�ĵ�ַ�ͳ��Ȼ�����copy_arr�Ĳ�ͬ���ı�
	/// ��size��copy_size��һ�£������·����ڴ�
	/// ���ؿ���֮������ݵĵ�ַ
	template <typename DataT>
	static DataT *CopyArrayFrom(DataT *arr, gsize size, const DataT *copy_arr, gsize copy_size) GEXCEPT(false);
};

}

#include "inline/garrays.inl"

#endif // _CORE_ARRAYS_H_
