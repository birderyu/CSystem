#ifndef _SERIALIZATION_ARCHIVE_H_
#define _SERIALIZATION_ARCHIVE_H_

#include "GCore/gglobal.h"

namespace gsystem {
	namespace stream {
		class GStream;
	}
}

namespace gsystem {
namespace archive {

class GAPI GArchive
{
public:
	// ����������һ������
	GArchive(stream::GStream &);
	virtual ~GArchive();

	virtual gbool Input() const = 0;
	virtual gbool Output() const = 0;

	// ������ or �ı�
	virtual gbool IsBinary() const = 0;

	// ���������е��ļ�����
	virtual gvoid Flush() = 0;
	virtual gvoid Close() = 0;
	virtual gvoid Abort() = 0;

	virtual gvoid PushCode(guint) = 0;
	virtual guint PopCode() = 0;

	virtual GArchive &operator<<(gbool) = 0;
	virtual GArchive &operator<<(gchar) = 0;
	virtual GArchive &operator<<(gschar) = 0;
	virtual GArchive &operator<<(guchar) = 0;
	virtual GArchive &operator<<(gwchar) = 0;
	virtual GArchive &operator<<(gshort) = 0;
	virtual GArchive &operator<<(gushort) = 0;
	virtual GArchive &operator<<(gint) = 0;
	virtual GArchive &operator<<(guint) = 0;
	virtual GArchive &operator<<(glong) = 0;
	virtual GArchive &operator<<(gulong) = 0;
	virtual GArchive &operator<<(glonglong) = 0;
	virtual GArchive &operator<<(gulonglong) = 0;
	virtual GArchive &operator<<(gfloat) = 0;
	virtual GArchive &operator<<(gdouble) = 0;
	virtual GArchive &operator<<(gdecimal) = 0;

	virtual GArchive &operator>>(gbool &) = 0;
	virtual GArchive &operator>>(gchar &) = 0;
	virtual GArchive &operator>>(gschar &) = 0;
	virtual GArchive &operator>>(guchar &) = 0;
	virtual GArchive &operator>>(gwchar &) = 0;
	virtual GArchive &operator>>(gshort &) = 0;
	virtual GArchive &operator>>(gushort &) = 0;
	virtual GArchive &operator>>(gint &) = 0;
	virtual GArchive &operator>>(guint &) = 0;
	virtual GArchive &operator>>(glong &) = 0;
	virtual GArchive &operator>>(gulong &) = 0;
	virtual GArchive &operator>>(glonglong &) = 0;
	virtual GArchive &operator>>(gulonglong &) = 0;
	virtual GArchive &operator>>(gfloat &) = 0;
	virtual GArchive &operator>>(gdouble &) = 0;
	virtual GArchive &operator>>(gdecimal &) = 0;

private:
	GArchive(const GArchive &);
	GArchive &operator=(const GArchive &);

protected:
	stream::GStream &m_rStream;
};

GINLINE GArchive::GArchive(stream::GStream &stream)
: m_rStream(stream)
{

}

GINLINE GArchive::GArchive(const GArchive &archive)
: m_rStream(archive.m_rStream)
{

}

GINLINE GArchive::~GArchive()
{

}

GINLINE GArchive &GArchive::operator=(const GArchive &)
{
	return *this;
}

}
}

#endif // _SERIALIZATION_ARCHIVE_H_