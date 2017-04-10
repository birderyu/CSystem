// �ֽڻ���
// ���ֽ�����GByteBuffer��ͬ���ǣ�GByteBuffer�ᰴ����������������Ԥ�ȷ����ڴ�

#ifndef _CORE_BUFFER_H_
#define _CORE_BUFFER_H_

#include "gvector.h"

namespace gsystem { // gsystem
	class GBytes;
} // namespace gsystem

#define G_BYTES_DEFAULT_CAPACITY 1024

namespace gsystem { // gsystem

class GAPI GByteBuffer final
	: public GListT<GByteBuffer>
	, virtual public GObject
	, virtual public GSerializable
{
	friend class GBytes;

public:
	GByteBuffer(gsize capacity = G_BYTES_DEFAULT_CAPACITY);
	GByteBuffer(const GByteBuffer &tBytes);

	gvoid Reserve(gsize);
	gvoid Resize(gsize);
	gvoid Clear();
	gvoid Destroy();

	gbool IsEmpty() const;
	gsize Size() const;
	gsize Capacity() const;

	gbyte &GetAt(gsize);
	const gbyte &GetAt(gsize) const;
	
	const gbyte *Head() const;
	gbyte *Head();
	const gbyte *Tail() const;
	gbyte *Tail();

	gbyte &operator[](gsize);
	const gbyte &operator[](gsize) const;

	guint ClassCode() const GNOEXCEPT;
	gbool Serialize(GArchive &archive) const;
	gbool Deserialize(GArchive &archive);

private:
	GVector<gbyte> m_tBytes;
};

} // namespace gsystem

#undef G_BYTES_DEFAULT_CAPACITY

#endif // _CORE_BUFFER_H_