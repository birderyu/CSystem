/// 字节串
#ifndef _CORE_BYTES_H_
#define _CORE_BYTES_H_

#include "gseries.h"

namespace gsystem { // gsystem

class GAPI GBytes final
	: public GArray<gbyte>
{
public:
	/// 将一个算数类型值转换成字节数组，返回该值所占的字节数
	/// 字节数组是大端的，可以直接用于网络字节序
	template<typename T> static gsize ArithmeticToBytes(const T *val, gbyte *bytes);

	/// 将一个字节数组转换成算数类型值，返回该值所占的字节数
	/// 字节数组是大端的
	template<typename T> static gsize BytesToArithmetic(const gbyte *bytes, T *val);

public:
	GBytes();
	GBytes(const gbyte *bytes, gsize size);
	GBytes(const GBytes &bytes);
	GBytes(GBytes &&bytes);

	gvoid Reserve(gsize capacity);
	gvoid Resize(gsize size);
	gvoid Clear();
	gvoid Destroy();

	gbool IsEmpty() const;
	gsize Size() const;
	gsize Capacity() const;

	gbyte &GetAt(gsize);
	const gbyte &GetAt(gsize) const;
	gbyte *CursorAt(gsize pos);
	const gbyte *CursorAt(gsize pos) const;

	const gbyte *Head() const;
	gbyte *Head();
	const gbyte *Tail() const;
	gbyte *Tail();

	GBytes &operator=(const GBytes &bytes);
	GBytes &operator=(GBytes &&bytes);
	gbyte &operator[](gsize pos);
	const gbyte &operator[](gsize pos) const;

private:
	GBytesData m_tBytes;
};

} // namespace gsystem

#include "inline/gbytes.inl"

#endif // _CORE_BYTES_H_