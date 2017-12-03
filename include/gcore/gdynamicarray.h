/********************************************************************************
**
** gsystem: A quick, micro library of C++
**
** @file gdynamicarray.h
** @brief 动态数组
** @author birderyu
** @contact https://github.com/birderyu
** @date 2017-1-24
** @version 1.0.0
**
********************************************************************************/

#ifndef _CORE_DYNAMIC_ARRAY_H_
#define _CORE_DYNAMIC_ARRAY_H_

#include "garray.h"
#include "gserializable.h"

namespace gsystem { // gsystem

/********************************************************************************
**
** @brief 动态数组
** @param <T> 数组元素的类型
**
** 动态数组可以动态地分配内存空间
**
********************************************************************************/
template <typename T>
class GDynamicArray final
	: public GArray<T>
	, public GSerializable
{
public:
	/****************************************************************************
	**
	** @name GDynamicArray
	** @brief 构造函数（constructor）
	**
	** 构造一个空数组
	**
	****************************************************************************/
	GDynamicArray();

	/****************************************************************************
	**
	** @name GDynamicArray
	** @brief 构造函数（constructor）
	** @param [in] size {gsize} 元素的数量
	**
	** 构造一个包含size个元素的数组，会依次调用每个元素的构造函数
	**
	****************************************************************************/
	explicit GDynamicArray(gsize size);

	/****************************************************************************
	**
	** @name GDynamicArray
	** @brief 构造函数（constructor）
	** @param [in] size {gsize} 元素的数量
	** @param [in] copyable {const T &} 初始值
	**
	** 构造一个包含size个元素的数组，对于每一个元素赋初始值copyable
	**
	****************************************************************************/
	GDynamicArray(gsize size, const T &copyable);

	/****************************************************************************
	**
	** @name GDynamicArray
	** @brief 拷贝构造函数（copy constructor）
	** @param [in] arr {const GDynamicArray<T> &} 数组
	**
	****************************************************************************/
	GDynamicArray(const GDynamicArray<T> &arr);

	/****************************************************************************
	**
	** @name GDynamicArray
	** @brief 移动构造函数（move constructor）
	** @param [in] arr {GDynamicArray<T> &&} 数组
	**
	****************************************************************************/
	GDynamicArray(GDynamicArray<T> &&arr);

	/****************************************************************************
	**
	** @name operator=
	** @brief 拷贝运算符
	** @param [in] arr {const GDynamicArray<T> &} 数组
	** @return {GDynamicArray<T> &} 数组的引用
	**
	****************************************************************************/
	GDynamicArray<T> &operator=(const GDynamicArray<T> &arr);

	/****************************************************************************
	**
	** @name operator=
	** @brief 移动运算符
	** @param [in] arr {GDynamicArray<T> &&} 数组
	** @return {GDynamicArray<T> &} 数组的引用
	**
	****************************************************************************/
	GDynamicArray<T> &operator=(GDynamicArray<T> &&arr);

	/****************************************************************************
	**
	** @name GDynamicArray
	** @brief 构造函数（constructor）
	** @param [in] copyable {const GArray<T> &} 数组
	** @param [in] start {gsize} 数组的起始数量
	** @param [in] size {gsize} 数组的长度
	**
	** 拷贝数组arr从start开始的size个元素，构造一个新的动态数组
	**
	****************************************************************************/
	GDynamicArray(const GArray<T> &arr, gsize start, gsize size);

	/****************************************************************************
	**
	** @name ~GDynamicArray
	** @brief 析构函数（destructor）
	**
	****************************************************************************/
	~GDynamicArray();

	/****************************************************************************
	**
	** @name Size
	** @brief 获取数组元素的数量
	** @return {gsize} 元素的数量
	** @see GArray
	**
	****************************************************************************/
	gsize Size() const GOVERRIDE;

	/****************************************************************************
	**
	** @name IsEmpty
	** @brief 判断数组是否为空
	** @return {gbool} 若元素的数量为0，则返回true，否则返回false
	** @see GArray
	**
	****************************************************************************/
	gbool IsEmpty() const GOVERRIDE;

	/****************************************************************************
	**
	** @name GetAt
	** @brief 获取指定位置的元素
	** @param [in] pos {gsize} 元素的下标，从0开始计数
	** @return {T &} 元素的引用
	** @see GArray
	**
	****************************************************************************/
	T &GetAt(gsize pos) GOVERRIDE;

	/****************************************************************************
	**
	** @name GetAt
	** @brief 获取指定位置的元素
	** @param [in] pos {gsize} 元素的下标，从0开始计数
	** @return {const T &} 元素的引用
	** @see GArray
	**
	****************************************************************************/
	const T &GetAt(gsize pos) const GOVERRIDE;

	/****************************************************************************
	**
	** @name CursorAt
	** @brief 获取指定位置的元素的光标
	** @param [in] pos {gsize} 元素的下标，从0开始计数
	** @return {T *} 元素的指针
	** @see GArray
	**
	****************************************************************************/
	T *CursorAt(gsize pos) GOVERRIDE;

	/****************************************************************************
	**
	** @name CursorAt
	** @brief 获取指定位置的元素的光标
	** @param [in] pos {gsize} 元素的下标，从0开始计数
	** @return {const T *} 元素的指针
	** @see GArray
	**
	****************************************************************************/
	const T *CursorAt(gsize pos) const GOVERRIDE;

	/****************************************************************************
	**
	** @name Resize
	** @brief 重置数组元素的个数
	** @param [in] new_size {gsize} 重置后的数组的元素个数
	**
	****************************************************************************/
	gvoid Resize(gsize new_size);

	/****************************************************************************
	**
	** @name Resize
	** @brief 重置数组元素的个数，并对新创建的元素赋初始值
	** @param [in] new_size {gsize} 重置后的数组的元素个数
	** @param [in] copyable {const T &} 初始值
	**
	****************************************************************************/
	gvoid Resize(gsize new_size, const T &copyable);

	/****************************************************************************
	**
	** @name Resize
	** @brief 重置数组元素的个数，并且仅保留原数组的部分元素
	** @param [in] new_size {gsize} 重置后的数组的元素个数
	** @param [in] start {gsize} 需要保留原数组的首位
	** @param [in] size {gsize} 需要保留原数组的元素个数
	** @param [in] new_start {gsize} 重置后的数组放置保留元素的位置
	**
	** 重置数组元素的个数，并保留原来从start开始的size个元素作为新数组的第new_start位
	**
	****************************************************************************/
	gvoid Resize(gsize new_size, gsize start, gsize size, gsize new_start = 0);

	/****************************************************************************
	**
	** @name Resize
	** @brief 重置数组元素的个数，并且仅保留原数组的部分元素，对新创建出来的元素赋初始值
	** @param [in] new_size {gsize} 重置后的数组的元素个数
	** @param [in] start {gsize} 需要保留原数组的首位
	** @param [in] size {gsize} 需要保留原数组的元素个数
	** @param [in] new_start {gsize} 重置后的数组放置保留元素的位置
	** @param [in] copyable {const T &} 初始值
	**
	** 重置数组元素的个数，并保留原来从start开始的size个元素作为新数组的第new_start位，在重置
	** 的过程中，若有新创建的元素，则用copyable赋初始值
	**
	****************************************************************************/
	gvoid Resize(gsize new_size, gsize start, gsize size, gsize new_start, const T &copyable);

	/****************************************************************************
	**
	** @name Destroy
	** @brief 销毁数组
	**
	** 依次调用每一个元素的析构函数，并释放内存
	**
	****************************************************************************/
	gvoid Destroy();

	/****************************************************************************
	**
	** @name Clear
	** @brief 清空数组
	**
	** 依次调用每一个元素的析构函数，但不释放内存
	**
	****************************************************************************/
	gvoid Clear();

	/****************************************************************************
	**
	** @name Remove
	** @brief 移除数组指定元素
	** @param [in] value {const T &} 待移除元素的值
	** @return {gsize} 获取移除掉的元素的个数
	**
	****************************************************************************/
	gsize Remove(const T &value);

	/****************************************************************************
	**
	** @name RemoveAt
	** @brief 移除数组指定位置的元素
	** @param [in] pos {gsize} 待移除元素的位置，从0开始计数
	**
	****************************************************************************/
	gvoid RemoveAt(gsize pos);

	/****************************************************************************
	**
	** @name operator==
	** @brief 判断数组是否相等
	** @param [in] arr {const GDynamicArray<T> &} 数组
	** @return {gbool} 若数组相等，则返回true，否则返回false
	**
	****************************************************************************/
	gbool operator==(const GDynamicArray<T> &arr);

	/****************************************************************************
	**
	** @name ClassCode
	** @brief 返回当前类的类序列号
	** @return {guint} 类序列号
	** @see GSerializable
	**
	****************************************************************************/
	guint ClassCode() const GNOEXCEPT;

	/****************************************************************************
	**
	** @name Serialize
	** @brief 序列化
	** @param [in] archive {GArchive &} 档案
	** @return {gbool} 序列化成功，则返回true，否则返回false
	** @see GSerializable
	**
	****************************************************************************/
	gbool Serialize(GArchive &archive) const;

	/****************************************************************************
	**
	** @name Deserialize
	** @brief 反序列化
	** @param [in] archive {GArchive &} 档案
	** @return {gbool} 反序列化成功，则返回true，否则返回false
	** @see GSerializable
	**
	****************************************************************************/
	gbool Deserialize(GArchive &archive);

private:
	/****************************************************************************
	**
	** 数组的首地址
	**
	****************************************************************************/
	T *m_pData;

	/****************************************************************************
	**
	** 数组元素的长度
	**
	****************************************************************************/
	gsize m_nSize;
};

/********************************************************************************
**
** @name GIntegerArray
** @brief 整形数组
**
********************************************************************************/
typedef GDynamicArray<gint> GIntegerArray;

/********************************************************************************
**
** @name GSizeArray
** @brief 尺寸类型数组
**
********************************************************************************/
typedef GDynamicArray<gsize> GSizeArray;

} // namespace gsystem

#include "inline/gdynamicarray.inl"

#endif // _CORE_DYNAMIC_ARRAY_H_