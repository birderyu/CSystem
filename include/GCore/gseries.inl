#ifndef _CORE_SERIES_INLINE_
#define _CORE_SERIES_INLINE_

#define G_SERIES_TYPE_LOCAL		0
#define G_SERIES_TYPE_GLOBAL	1
#define G_SERIES_TYPE_REFERENCE	2
#define G_SERIES_TEMPLATE		template<typename T, gsize LOCAL_SIZE, gbool HAS_END_FLAG, T END_FLAG>
#define G_SERIES_QUAL			GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG>

namespace gsystem { // gsystem
namespace detail { // gsystem.detail
namespace series { // gsystem.detail.series

template<gbool HAS_END_FLAG>
class GSeriesHelper
{
public:
	template<typename T> 
	GINLINE static T *CreateSeries(gsize size) noexcept(false)
	{
		return GArrays::CreateArray<T>(size);
	}

	/// ��������һ������
	template<typename T> 
	GINLINE static T *CreateSeries(const T *copy_arr, gsize copy_size) noexcept(false)
	{
		return GArrays::CreateArray<T>(copy_arr, 0, copy_size);
	}

	/// ����һ������Ϊsize�����飬����copy_arrȥ��ʼ���µ�����
	template<typename T> 
	GINLINE static T *CreateSeries(gsize size, const T *copy_arr, gsize copy_size) noexcept(false)
	{
		return GArrays::CreateArray<T>(size, 0, copy_arr, 0, copy_size);
	}

	template<typename T> 
	GINLINE static gvoid DestorySeries(T *arr, gsize size) noexcept(false)
	{
		GArrays::DestoryArray<T>(arr, size);
	}

	template<typename T> 
	GINLINE static gvoid ClearSeries(T *arr, gsize size) noexcept(false)
	{
		GArrays::ClearArray<T>(arr, size);
	}

	template<typename T> 
	GINLINE static T *ResizeSeries(T *old_arr, gsize old_size, gsize new_size) noexcept(false)
	{
		return GArrays::ResizeArray<T>(old_arr, old_size, new_size);
	}

	template<typename T>
	GINLINE static gvoid SetEndFlag(T *arr, gsize size, const T &end_flag)
	{

	}

	template<typename T> 
	GINLINE static gvoid SetEndFlag(T *arr, gsize size, T &&end_flag)
	{

	}

	/// arr��copy_arr��Ԫ�ظ���Ӧ���ڻ����size
	template<typename T>
	GINLINE static gvoid CopySeriesFrom(T *arr, gsize size, const T *copy_arr)
	{
		GArrays::CopyArrayFrom<T>(arr, size, copy_arr);
	}
};

template<>
template<typename T>
GINLINE T *GSeriesHelper<true>::CreateSeries(gsize size) noexcept(false)
{
	return GArrays::CreateArray<T>(size + 1);
}

template<>
template<typename T>
GINLINE T *GSeriesHelper<true>::CreateSeries(const T *copy_arr, gsize copy_size) noexcept(false)
{
	return GArrays::CreateArray<T>(copy_arr, 0, copy_size + 1);
}

template<>
template<typename T>
GINLINE T *GSeriesHelper<true>::CreateSeries(gsize size, const T *copy_arr, gsize copy_size) noexcept(false)
{
	return GArrays::CreateArray<T>(size + 1, 0, copy_arr, 0, copy_size + 1);
}

template<>
template<typename T>
GINLINE gvoid GSeriesHelper<true>::DestorySeries(T *arr, gsize size) noexcept(false)
{
	GArrays::DestoryArray<T>(arr, size + 1);
}

template<>
template<typename T>
GINLINE gvoid GSeriesHelper<true>::ClearSeries(T *arr, gsize size) noexcept(false)
{
	GArrays::ClearArray<T>(arr, size + 1);
}

template<>
template<typename T>
GINLINE T *GSeriesHelper<true>::ResizeSeries(T *old_arr, gsize old_size, gsize new_size) noexcept(false)
{
	return GArrays::ResizeArray<T>(old_arr, old_size + 1, new_size + 1);
}

template<>
template<typename T>
GINLINE gvoid GSeriesHelper<true>::CopySeriesFrom(T *arr, gsize size, const T *copy_arr)
{
	GArrays::CopyArrayFrom<T>(arr, size + 1, copy_arr);
}

template<>
template<typename T>
GINLINE gvoid GSeriesHelper<true>::SetEndFlag(T *arr, gsize size, const T &end_flag)
{
	arr[size] = end_flag;
}

template<>
template<typename T>
GINLINE gvoid GSeriesHelper<true>::SetEndFlag(T *arr, gsize size, T &&end_flag)
{
	arr[size] = GForward<T>(end_flag);
}

} // namespace gsystem.detail.series
} // namespace gsystem.detail
} // namespace gsystem

namespace gsystem { // gsystem

G_SERIES_TEMPLATE GINLINE
G_SERIES_QUAL G_SERIES_QUAL::CopyOf(const T *copy_arr, gsize copy_size)
{
	G_SERIES_QUAL _series;
	_series.CopyConstruct(copy_arr, copy_size);
	return _series;
}

G_SERIES_TEMPLATE GINLINE
G_SERIES_QUAL G_SERIES_QUAL::ReferenceOf(const T *ref_arr, gsize ref_size)
{
	G_SERIES_QUAL _series;
	_series.ReferenceConstruct(ref_arr, ref_size);
	return _series;
}

G_SERIES_TEMPLATE GINLINE
G_SERIES_QUAL::GSeries(gsize capacity)
	: m_nSize(0), m_pStart(GNULL)
{
	if (capacity <= MIN_CAPACITY)
	{
		m_nType = G_SERIES_TYPE_LOCAL;
		m_nCapacity = MIN_CAPACITY;
		m_pStart = m_tArray;
	}
	else
	{
		m_nType = G_SERIES_TYPE_GLOBAL;
		m_nCapacity = capacity;
		m_pArray = detail::series::GSeriesHelper<HAS_END_FLAG>::CreateSeries<T>(capacity);
		m_pStart = m_pArray;
	}
	detail::series::GSeriesHelper<HAS_END_FLAG>::SetEndFlag<T>(m_pStart, m_nSize, END_FLAG);
}

G_SERIES_TEMPLATE
GINLINE G_SERIES_QUAL::GSeries(const T *copy_arr, gsize copy_size)
{
	CopyConstruct(copy_arr, copy_size);
}

G_SERIES_TEMPLATE
GINLINE G_SERIES_QUAL::GSeries(const GArray<T> &copy_arr)
{
	CopyConstruct(copy_arr.FirstCursor(), copy_arr.Size());
}

G_SERIES_TEMPLATE
GINLINE G_SERIES_QUAL::GSeries(GArray<T> &&move_arr)
{
	// TODO
}

G_SERIES_TEMPLATE
GINLINE G_SERIES_QUAL::GSeries(const G_SERIES_QUAL &arr)
	: m_nSize(arr.m_nSize)
	, m_nCapacity(arr.m_nSize)
	, m_nType(arr.m_nType)
	, m_pStart(GNULL)
{
	switch (arr.m_nType)
	{
	case G_SERIES_TYPE_LOCAL:
	{
		detail::series::GSeriesHelper<HAS_END_FLAG>::CopySeriesFrom<T>(m_tArray, arr.m_nSize, arr.m_pStart);
		m_pStart = m_tArray;
	}
		break;
	case G_SERIES_TYPE_GLOBAL:
	{
		m_pArray = detail::series::GSeriesHelper<HAS_END_FLAG>::CreateSeries(arr.m_pStart, arr.m_nSize);
		m_pStart = m_pArray;
	}
		break;
	case G_SERIES_TYPE_REFERENCE:
	{
		m_pStart = m_pArray;
	}
		break;
	default:
		throw "illegal type, type must be local or global or reference.";
		break;
	}
}

G_SERIES_TEMPLATE
GINLINE G_SERIES_QUAL::GSeries(G_SERIES_QUAL &&arr)
	: m_nSize(arr.m_nSize)
	, m_nCapacity(arr.m_nCapacity)
	, m_nType(arr.m_nType)
	, m_pStart(arr.m_pStart)
{
	switch (arr.m_nType)
	{
	case G_SERIES_TYPE_LOCAL:
	{
		m_pStart = m_tArray;
		detail::series::GSeriesHelper<HAS_END_FLAG>::CopySeriesFrom<T>(m_pStart, arr.m_nSize, arr.m_pStart);
	}
		break;
	case G_SERIES_TYPE_GLOBAL:
	{
		m_pArray = arr.m_pArray;
		m_pStart = m_pArray;

		// ֵ��arr���ݱ����ÿ�
		arr.m_nType = G_SERIES_TYPE_LOCAL;
		arr.m_pStart = arr.m_tArray;
		arr.m_nCapacity = arr.MIN_CAPACITY;
		arr.m_nSize = 0;
	}
		break;
	case G_SERIES_TYPE_REFERENCE:
	{
		// ���ã�arr���������ÿ�
		m_pArray = GNULL;
		m_nCapacity = 0;
	}
		break;
	default:
		throw "illegal type, type must be local or global or reference.";
		break;
	}
}

G_SERIES_TEMPLATE
GINLINE G_SERIES_QUAL::~GSeries()
{
	Free();
}

G_SERIES_TEMPLATE
GINLINE gsize G_SERIES_QUAL::Size() const
{
	return m_nSize;
}

G_SERIES_TEMPLATE
GINLINE gsize G_SERIES_QUAL::Capacity() const
{
	return m_nCapacity;
}

G_SERIES_TEMPLATE
GINLINE gbool G_SERIES_QUAL::IsEmpty() const
{
	return m_nSize == 0;
}

G_SERIES_TEMPLATE
GINLINE gvoid G_SERIES_QUAL::Resize(gsize size)
{
	if (IsReference())
	{
		// ��������
		ToValue(size);
		m_nSize = size;
		detail::series::GSeriesHelper<HAS_END_FLAG>::SetEndFlag<T>(m_pStart, m_nSize, END_FLAG);
	}
	else
	{
		// ֵ����
		if (m_nSize == size)
		{
			return;
		}

		if (size <= m_nCapacity)
		{
			m_nSize = size;
			detail::series::GSeriesHelper<HAS_END_FLAG>::SetEndFlag<T>(m_pStart, m_nSize, END_FLAG);
			return;
		}

		if (m_nType == G_SERIES_TYPE_LOCAL)
		{
			// ��Ҫ��local type��չ��global type
			T *arr = detail::series::GSeriesHelper<HAS_END_FLAG>::CreateSeries(size, m_tArray, m_nSize);
			m_nCapacity = size;
			m_pArray = arr;
			m_nType = G_SERIES_TYPE_GLOBAL;
			m_pStart = m_pArray;
		}
		else if (m_nType == G_SERIES_TYPE_GLOBAL)
		{
			// ��������
			m_pArray = detail::series::GSeriesHelper<HAS_END_FLAG>::ResizeSeries<T>(m_pArray, m_nCapacity, size);
		}
		m_nSize = size;
		detail::series::GSeriesHelper<HAS_END_FLAG>::SetEndFlag<T>(m_pStart, m_nSize, END_FLAG);
	}
}

G_SERIES_TEMPLATE
GINLINE gvoid G_SERIES_QUAL::Reserve(gsize capacity)
{
	if (IsReference())
	{
		// ��������
		ToValue(capacity > m_nSize ? capacity : m_nSize);
	}
	else
	{
		// ֵ����
		if (capacity < m_nCapacity)
		{
			// ��������
			return;
		}

		if (m_nType == G_SERIES_TYPE_LOCAL)
		{
			// ��Ҫ��local type��չ��global type
			T *arr = detail::series::GSeriesHelper<HAS_END_FLAG>::CreateSeries(capacity, m_tArray, m_nSize);
			m_pArray = arr;
			m_nType = G_SERIES_TYPE_GLOBAL;
			m_pStart = m_pArray;
		}
		else
		{
			// ��������
			m_pArray = detail::series::GSeriesHelper<HAS_END_FLAG>::ResizeSeries<T>(m_pArray, m_nCapacity, capacity);
		}
		m_nCapacity = capacity;
	}
}

G_SERIES_TEMPLATE
GINLINE const T &G_SERIES_QUAL::ConstGetAt(gsize pos) const
{
	GASSERT(pos < m_nSize);
	return m_pStart[pos];
}

G_SERIES_TEMPLATE
GINLINE const T &G_SERIES_QUAL::GetAt(gsize pos) const
{
	GASSERT(pos < m_nSize);
	return m_pStart[pos];
}

G_SERIES_TEMPLATE
GINLINE T &G_SERIES_QUAL::GetAt(gsize pos)
{
	ToValue(m_nSize);
	GASSERT(pos < m_nSize);
	return m_pStart[pos];
}

G_SERIES_TEMPLATE
GINLINE const T *G_SERIES_QUAL::ConstCursorAt(gsize pos) const
{
	return m_pStart + pos;
}

G_SERIES_TEMPLATE
GINLINE const T *G_SERIES_QUAL::CursorAt(gsize pos) const
{
	return m_pStart + pos;
}

G_SERIES_TEMPLATE
GINLINE T *G_SERIES_QUAL::CursorAt(gsize pos)
{
	ToValue(m_nSize);
	return m_pStart + pos;
}

G_SERIES_TEMPLATE
GINLINE const T *G_SERIES_QUAL::ConstStart() const
{
	return m_pStart;
}

G_SERIES_TEMPLATE
GINLINE const T *G_SERIES_QUAL::Start() const
{
	return m_pStart;
}

G_SERIES_TEMPLATE
GINLINE T *G_SERIES_QUAL::Start()
{
	ToValue(m_nSize);
	return m_pStart;
}

G_SERIES_TEMPLATE
GINLINE gvoid G_SERIES_QUAL::SetAt(gsize pos, const T &data)
{
	ToValue(m_nSize);
	GASSERT(pos < m_nSize);
	m_pStart[pos] = data;
}

G_SERIES_TEMPLATE
GINLINE gvoid G_SERIES_QUAL::SetAt(gsize pos, T &&data)
{
	ToValue(m_nSize);
	GASSERT(pos < m_nSize);
	m_pStart[pos] = GForward<T>(data);
}

G_SERIES_TEMPLATE
GINLINE gvoid G_SERIES_QUAL::Clear()
{
	switch (m_nType)
	{
	case G_SERIES_TYPE_LOCAL:
	case G_SERIES_TYPE_GLOBAL:
	{
		detail::series::GSeriesHelper<HAS_END_FLAG>::ClearSeries<T>(m_pArray, m_nCapacity);
	}
		break;
	case G_SERIES_TYPE_REFERENCE:
	{
		// ������ת��Ϊһ���յ�local type
		m_nType = G_SERIES_TYPE_LOCAL;
		m_nSize = 0;
		m_nCapacity = MIN_CAPACITY;
		m_pStart = m_tArray;
		detail::series::GSeriesHelper<HAS_END_FLAG>::SetEndFlag<T>(m_pStart, m_nSize, END_FLAG);
	}
		break;
	default:
		throw "illegal type, type must be local or global or reference.";
		break;
	}
	m_nSize = 0;
	detail::series::GSeriesHelper<HAS_END_FLAG>::SetEndFlag<T>(m_pStart, m_nSize, END_FLAG);
}

G_SERIES_TEMPLATE
GINLINE gvoid G_SERIES_QUAL::Destroy()
{
	// �ͷ��ڴ�
	Free();

	// ������ת��Ϊlocal type���ÿ�
	m_nType = G_SERIES_TYPE_LOCAL;
	m_nSize = 0;
	m_nCapacity = MIN_CAPACITY;
	m_pStart = m_tArray;
	detail::series::GSeriesHelper<HAS_END_FLAG>::SetEndFlag<T>(m_pStart, m_nSize, END_FLAG);
}

G_SERIES_TEMPLATE
GINLINE gvoid G_SERIES_QUAL::Append(const G_SERIES_QUAL &series)
{
	ToValue(m_nSize + series.m_nSize); // ת����ֵ����
	Reserve(m_nSize + series.m_nSize);
	detail::series::GSeriesHelper<HAS_END_FLAG>::CopySeriesFrom(m_pStart + m_nSize, series.m_nSize, series.m_pStart);
	m_nSize += series.m_nSize;
}

G_SERIES_TEMPLATE
GINLINE gvoid G_SERIES_QUAL::Append(G_SERIES_QUAL &&series)
{
	ToValue(m_nSize + series.m_nSize); // ת����ֵ����
	Reserve(m_nSize + series.m_nSize);
	detail::series::GSeriesHelper<HAS_END_FLAG>::CopySeriesFrom(m_pStart + m_nSize, series.m_nSize, series.m_pStart);
	m_nSize += series.m_nSize;
}

G_SERIES_TEMPLATE
GINLINE G_SERIES_QUAL &G_SERIES_QUAL::operator=(const G_SERIES_QUAL &arr)
{
	if (this == &arr)
	{
		return *this;
	}

	if (arr.IsReference())
	{
		// arr�������ͣ������õĴ���
		Free(); // �ͷſռ�
		m_nSize = arr.m_nSize;
		m_nType = arr.m_nType;
		m_nCapacity = arr.m_nCapacity;
		m_pStart = arr.m_pStart;
		return *this;
	}

	// arr����������
	if (m_nType == G_SERIES_TYPE_LOCAL)
	{
		// ����ԭ����local type
		if (arr.m_nSize > m_nCapacity)
		{
			// ��local type��չ��global type����������ڴ棬����Ҫ����Ԫ��
			m_nCapacity = arr.m_nSize;
			m_nType = G_SERIES_TYPE_GLOBAL;
			m_pArray = detail::series::GSeriesHelper<HAS_END_FLAG>::CreateSeries<T>(arr.m_nSize);
			m_pStart = m_pArray;
		}
	}
	else if (m_nType == G_SERIES_TYPE_GLOBAL)
	{
		// ����ԭ����global type
		// ��m_nCapacity >= arr.m_nSizeʱ��˵��ԭ����������Ѿ��ܹ��������µ����飬����������·����ڴ�
		// �������·����ڴ�
		if (m_nCapacity < arr.m_nSize)
		{
			// ԭ�е������Ѿ��޷��������µ����飬��Ҫ���ɵ���������
			detail::series::GSeriesHelper<HAS_END_FLAG>::DestorySeries<T>(m_pArray, m_nCapacity);
			if (arr.m_nSize <= MIN_CAPACITY)
			{
				// �µ����齫����local type����������ڴ�
				m_nCapacity = MIN_CAPACITY;
				m_nType = G_SERIES_TYPE_LOCAL;
				m_pStart = m_tArray;
			}
			else
			{
				// �µ����齫����global type����Ҫ�����ڴ�
				m_nCapacity = arr.m_nSize;
				m_nType = G_SERIES_TYPE_GLOBAL;
				m_pArray = detail::series::GSeriesHelper<HAS_END_FLAG>::CreateSeries<T>(arr.m_nSize);
				m_pStart = m_pArray;
			}
		}
	}
	else if (m_nType == G_SERIES_TYPE_REFERENCE)
	{
		// ����ԭ����reference�������ڴ沢����
		m_nSize = arr.m_nSize;
		m_nCapacity = arr.m_nSize;
		m_nType = arr.m_nType;
		m_pStart = GNULL;

		switch (arr.m_nType)
		{
		case G_SERIES_TYPE_LOCAL:
		{
			detail::series::GSeriesHelper<HAS_END_FLAG>::CopySeriesFrom<T>(m_tArray, arr.m_nSize, arr.m_pStart);
			m_pStart = m_tArray;
		}
		break;
		case G_SERIES_TYPE_GLOBAL:
		{
			m_pArray = detail::series::GSeriesHelper<HAS_END_FLAG>::CreateSeries(arr.m_pStart, arr.m_nSize);
			m_pStart = m_pArray;
		}
		break;
		default:
			throw "illegal type, type must be local or global or reference.";
			break;
		}
	}
	else
	{
		throw "illegal type, type must be local or global or reference.";
	}

	// ����Ԫ��
	m_nSize = arr.m_nSize;
	detail::series::GSeriesHelper<HAS_END_FLAG>::CopySeriesFrom(m_pStart, arr.m_nSize, arr.m_pStart);
}

G_SERIES_TEMPLATE
GINLINE G_SERIES_QUAL &G_SERIES_QUAL::operator=(G_SERIES_QUAL &&arr)
{
	if (this == &arr)
	{
		return *this;
	}

	// ���پɵ�����
	Free();

	if (arr.IsReference())
	{
		// arr��������
		m_nSize = arr.m_nSize;
		m_nType = arr.m_nType;
		m_nCapacity = arr.m_nCapacity;
		m_pStart = arr.m_pStart;
		return *this;
	}

	// �ƶ���ֵ�µ�����
	m_nSize = arr.m_nSize;
	m_nCapacity = arr.m_nCapacity;
	m_nType = arr.m_nType;

	switch (arr.m_nType)
	{
	case G_SERIES_TYPE_LOCAL:
	{
		detail::series::GSeriesHelper<HAS_END_FLAG>::CopySeriesFrom<T>(m_tArray, arr.m_nSize, arr.m_pStart);
		m_pStart = m_tArray;
	}
		break;
	case G_SERIES_TYPE_GLOBAL:
	{
		m_pArray = arr.m_pArray;
		m_pStart = m_pArray;
		// arr�����ÿ�
		arr.m_nType = G_SERIES_TYPE_LOCAL;
		arr.m_pStart = arr.m_tArray;
		arr.m_nCapacity = arr.MIN_CAPACITY;
		arr.m_nSize = 0;
	}
		break;
	case G_SERIES_TYPE_REFERENCE:
	{
		m_pArray = GNULL;
		m_pStart = arr.m_pStart;
	}
		break;
	default:
		throw "illegal type, type must be local or global or reference.";
		break;
	}
}

G_SERIES_TEMPLATE
GINLINE const T &G_SERIES_QUAL::operator[](gsize pos) const
{
	return ConstGetAt(pos);
}

G_SERIES_TEMPLATE
GINLINE T &G_SERIES_QUAL::operator[](gsize pos)
{
	return GetAt(pos);
}

G_SERIES_TEMPLATE GINLINE
gvoid G_SERIES_QUAL::CopyConstruct(const T *copy_arr, gsize copy_size)
{
	if (copy_size <= MIN_CAPACITY)
	{
		detail::series::GSeriesHelper<HAS_END_FLAG>::CopySeriesFrom<T>(m_tArray, copy_size, copy_arr);
		m_nType = G_SERIES_TYPE_LOCAL;
		m_nCapacity = MIN_CAPACITY;
		m_nSize = copy_size;
		m_pStart = m_tArray;
	}
	else
	{
		m_pArray = detail::series::GSeriesHelper<HAS_END_FLAG>::CreateSeries<T>(copy_arr, copy_size);
		m_nType = G_SERIES_TYPE_GLOBAL;
		m_nCapacity = copy_size;
		m_nSize = copy_size;
		m_pStart = m_pArray;
	}
	detail::series::GSeriesHelper<HAS_END_FLAG>::SetEndFlag<T>(m_pStart, m_nSize, END_FLAG);
}

G_SERIES_TEMPLATE GINLINE
gvoid G_SERIES_QUAL::MoveConstruct(T *&move_arr, gsize move_size)
{
	m_nType = G_SERIES_TYPE_GLOBAL;
	m_nCapacity = copy_size;
	m_nSize = copy_size;
	m_pArray = move_arr;
	m_pStart = m_pArray;
	move_arr = GNULL;
	detail::series::GSeriesHelper<HAS_END_FLAG>::SetEndFlag<T>(m_pStart, m_nSize, END_FLAG);
}

G_SERIES_TEMPLATE GINLINE
gvoid G_SERIES_QUAL::ReferenceConstruct(const T *ref_arr, gsize ref_size)
{
	m_nType = G_SERIES_TYPE_REFERENCE;
	m_nCapacity = 0;
	m_nSize = ref_size;
	m_pStart = const_cast<T *>(ref_arr);
	m_pArray = GNULL;
}

G_SERIES_TEMPLATE
GINLINE gvoid G_SERIES_QUAL::Free()
{
	switch (m_nType)
	{
	case G_SERIES_TYPE_LOCAL:
	{
		// ֻ����Ԫ�أ����ͷ��ڴ�
		detail::series::GSeriesHelper<HAS_END_FLAG>::ClearSeries<T>(m_pArray, m_nCapacity);
	}
	break;
	case G_SERIES_TYPE_GLOBAL:
	{
		// ����Ԫ�غ��ͷ��ڴ�
		detail::series::GSeriesHelper<HAS_END_FLAG>::DestorySeries<T>(m_pArray, m_nCapacity);
	}
	break;
	case G_SERIES_TYPE_REFERENCE:
	{
		// ���ã���������
	}
	break;
	default:
		throw "illegal type, type must be local or global or reference.";
		break;
	}
}

G_SERIES_TEMPLATE
GINLINE gbool G_SERIES_QUAL::IsReference() const
{
	return m_nType == G_SERIES_TYPE_REFERENCE;
}

G_SERIES_TEMPLATE
GINLINE gvoid G_SERIES_QUAL::ToValue(gsize capacity)
{
	if (!IsReference())
	{
		return;
	}

	// ʵ�ʵĴ�СΪm_nSize��capacity�еĽ�С�ߣ��������ڵ�capacity��Сʱ�����ԭ�����������ض�
	gsize real_size = m_nSize < capacity ? m_nSize : capacity;

	if (capacity <= MIN_CAPACITY)
	{
		m_nType = G_SERIES_TYPE_LOCAL;
		m_nCapacity = MIN_CAPACITY;
		detail::series::GSeriesHelper<HAS_END_FLAG>::CopySeriesFrom<T>(m_tArray, real_size, m_pStart);
		m_pStart = m_tArray;
	}
	else
	{
		m_nType = G_SERIES_TYPE_GLOBAL;
		m_nCapacity = capacity;
		m_pArray = detail::series::GSeriesHelper<HAS_END_FLAG>::CreateSeries<T>(capacity);
		detail::series::GSeriesHelper<HAS_END_FLAG>::CopySeriesFrom<T>(m_pArray, real_size, m_pStart);
		m_pStart = m_pArray;
	}

	m_nSize = real_size;
	detail::series::GSeriesHelper<HAS_END_FLAG>::SetEndFlag<T>(m_pStart, m_nSize, END_FLAG);
}

} // namespace gsystem

#undef G_SERIES_QUAL
#undef G_SERIES_TEMPLATE
#undef G_SERIES_TYPE_REFERENCE
#undef G_SERIES_TYPE_GLOBAL
#undef G_SERIES_TYPE_LOCAL

#endif // _CORE_SERIES_INLINE_
