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

// DataT������Serialize����
template<typename DataT>
gbool ___GSerialize(GArchive &archive, const DataT &v, GTrueType)
{
	return v.Serialize(archive);
}

// DataTδ����Serialize����
template<typename DataT>
gbool ___GSerialize(GArchive &archive, const DataT &v, GFalseType)
{
	// �޷����л����׳��쳣����TODO��
	return false;
}

// DataT��GSerializable������
template<typename DataT>
gbool __GSerialize(GArchive &archive, const DataT &v, GTrueType)
{
	return v.Serialize(archive);
}

// DataT����GSerializable������
template<typename DataT>
gbool __GSerialize(GArchive &archive, const DataT &v, GFalseType)
{
	// ���DataT�Ƿ������Serialize����
	return ___GSerialize<DataT>(archive, v,
		GCatBase<GHasSerializeFunction<DataT>::value>());
}

// DataT����������
template<typename DataT>
gbool _GSerialize(GArchive &archive, const DataT &v, GTrueType)
{
	archive << v;
	return true;
}

// DataT������������
template<typename DataT>
gbool _GSerialize(GArchive &archive, const DataT &v, GFalseType)
{
	// ���DataT�Ƿ���GSerializable������
	return __GSerialize<DataT>(archive, v,
		GIsBaseOf<GSerializable, DataT>());
}

// DataT������Deserialize����
template<typename DataT>
gbool ___GDeserialize(GArchive &archive, DataT &v, GTrueType)
{
	return v.Deserialize(archive);
}

// DataTδ����Deserialize����
template<typename DataT>
gbool ___GDeserialize(GArchive &archive, DataT &v, GFalseType)
{
	// �޷����л����׳��쳣����TODO��
	return false;
}

// DataT��GSerializable������
template<typename DataT>
gbool __GDeserialize(GArchive &archive, DataT &v, GTrueType)
{
	return v.Deserialize(archive);
}

// DataT����GSerializable������
template<typename DataT>
gbool __GDeserialize(GArchive &archive, DataT &v, GFalseType)
{
	// ���DataT�Ƿ������Deserialize����
	return ___GDeserialize<DataT>(archive, v,
		GCatBase<GHasDeserializeFunction<DataT>::value>());
}

// DataT����������
template<typename DataT>
gbool _GDeserialize(GArchive &archive, DataT &v, GTrueType)
{
	archive >> v;
	return true;
}

// DataT������������
template<typename DataT>
gbool _GDeserialize(GArchive &archive, DataT &v, GFalseType)
{
	// ���DataT�Ƿ���GSerializable������
	return __GDeserialize<DataT>(archive, v,
		GIsBaseOf<GSerializable, DataT>());
}

} // namespace gsystem.detail

template<typename DataT> GINLINE
gbool GSerialize(GArchive &archive, const DataT &v)
{
	// ���DataT�Ƿ��ǻ�������
	return detail::_GSerialize<DataT>(archive, v,
		GIsArithmetic<DataT>());
}

template<typename DataT> GINLINE
gbool GDeserialize(GArchive &archive, DataT &v)
{
	// ���DataT�Ƿ��ǻ�������
	return detail::_GDeserialize<DataT>(archive, v,
		GIsArithmetic<DataT>());
}

} // namespace gsystem

#endif // _CORE_SERIALIZE_INLINE_
