#ifndef _CORE_SERIALIZE_INLINE_
#define _CORE_SERIALIZE_INLINE_

#include "gtraits.h"
#include "garchive.h"
#include "gfunctor.h"

namespace gsystem { // gsystem
namespace detail {

// �ж�һ�����Ƿ���Serialize����
// gbool b = GHasSerializeFunction<ClassName>::value;
template<typename T>
struct GHasSerializeFunction {

	template<typename U, gbool(U::*)(GArchive &archive) const>
	struct Matcher;

	template<typename U>
	static gint8 Foo(Matcher<U, &U::Serialize> *);

	template<typename U>
	static gint32 Foo(...);

	enum { value = sizeof(Foo<T>(GNULL)) == sizeof(gint8) };
};

// �ж�һ�����Ƿ���Deserialize����
// gbool b = GHasDeserializeFunction<ClassName>::value;
template<typename T>
struct GHasDeserializeFunction {

	template<typename U, gbool(U::*)(GArchive &archive)>
	struct Matcher;

	template<typename U>
	static gint8 Foo(Matcher<U, &U::Deserialize> *);

	template<typename U>
	static gint32 Foo(...);

	enum { value = sizeof(Foo<T>(GNULL)) == sizeof(gint8) };
};

// T������Serialize����
template<typename T>
gbool ___GSerialize(GArchive &archive, const T &v, GTrueType)
{
	return v.Serialize(archive);
}

// Tδ����Serialize����
template<typename T>
gbool ___GSerialize(GArchive &archive, const T &v, GFalseType)
{
	// �޷����л����׳��쳣����TODO��
	return false;
}

// T��GSerializable������
template<typename T>
gbool __GSerialize(GArchive &archive, const T &v, GTrueType)
{
	return v.Serialize(archive);
}

// T����GSerializable������
template<typename T>
gbool __GSerialize(GArchive &archive, const T &v, GFalseType)
{
	// ���T�Ƿ������Serialize����
	return ___GSerialize<T>(archive, v,
		GCatBase<GHasSerializeFunction<T>::value>());
}

// T����������
template<typename T>
gbool _GSerialize(GArchive &archive, const T &v, GTrueType)
{
	archive << v;
	return true;
}

// T������������
template<typename T>
gbool _GSerialize(GArchive &archive, const T &v, GFalseType)
{
	// ���T�Ƿ���GSerializable������
	return __GSerialize<T>(archive, v,
		GIsBaseOf<GSerializable, T>());
}

// T������Deserialize����
template<typename T>
gbool ___GDeserialize(GArchive &archive, T &v, GTrueType)
{
	return v.Deserialize(archive);
}

// Tδ����Deserialize����
template<typename T>
gbool ___GDeserialize(GArchive &archive, T &v, GFalseType)
{
	// �޷����л����׳��쳣����TODO��
	return false;
}

// T��GSerializable������
template<typename T>
gbool __GDeserialize(GArchive &archive, T &v, GTrueType)
{
	return v.Deserialize(archive);
}

// T����GSerializable������
template<typename T>
gbool __GDeserialize(GArchive &archive, T &v, GFalseType)
{
	// ���T�Ƿ������Deserialize����
	return ___GDeserialize<T>(archive, v,
		GCatBase<GHasDeserializeFunction<T>::value>());
}

// T����������
template<typename T>
gbool _GDeserialize(GArchive &archive, T &v, GTrueType)
{
	archive >> v;
	return true;
}

// T������������
template<typename T>
gbool _GDeserialize(GArchive &archive, T &v, GFalseType)
{
	// ���T�Ƿ���GSerializable������
	return __GDeserialize<T>(archive, v,
		GIsBaseOf<GSerializable, T>());
}

} // namespace gsystem.detail

template<typename T> GINLINE
gbool GSerialize(GArchive &archive, const T &v)
{
	// ���T�Ƿ��ǻ�������
	return detail::_GSerialize<T>(archive, v,
		GIsArithmetic<T>());
}

template<typename T> GINLINE
gbool GDeserialize(GArchive &archive, T &v)
{
	// ���T�Ƿ��ǻ�������
	return detail::_GDeserialize<T>(archive, v,
		GIsArithmetic<T>());
}

} // namespace gsystem

#endif // _CORE_SERIALIZE_INLINE_
