#ifndef _CORE_ARCHIVE_H_
#define _CORE_ARCHIVE_H_

#include "gglobal.h"
#include "gnocopyable.h"

namespace gsystem { // gsystem

class GAPI GArchive
	: private GNocopyable
{
public:
	virtual ~GArchive() = 0;

public:
	virtual gbool Input() const = 0;
	virtual gbool Output() const = 0;

public:
	virtual gvoid PushCode(guint code) = 0;
	virtual guint PopCode() = 0;

public:
	virtual gvoid Start() = 0;
	virtual gvoid Stop(gbool saving = true) = 0;

public:
	virtual GArchive &Attach(gcbytes bytes, gsize size) = 0;
	virtual GArchive &Attach(gcstring str, gsize size) = 0;

	virtual GArchive &Detach(gbytes bytes, gsize size) = 0;

public:
	virtual GArchive &operator << (gbool) = 0;
	virtual GArchive &operator << (gchar) = 0;
	virtual GArchive &operator << (gschar) = 0;
	virtual GArchive &operator << (guchar) = 0;
	virtual GArchive &operator << (gchar16) = 0;
	virtual GArchive &operator << (gchar32) = 0;
	virtual GArchive &operator << (gwchar) = 0;
	virtual GArchive &operator << (gshort) = 0;
	virtual GArchive &operator << (gushort) = 0;
	virtual GArchive &operator << (gint) = 0;
	virtual GArchive &operator << (guint) = 0;
	virtual GArchive &operator << (glong) = 0;
	virtual GArchive &operator << (gulong) = 0;
	virtual GArchive &operator << (glonglong) = 0;
	virtual GArchive &operator << (gulonglong) = 0;
	virtual GArchive &operator << (gfloat) = 0;
	virtual GArchive &operator << (gdouble) = 0;
	virtual GArchive &operator << (glongdouble) = 0;

	virtual GArchive &operator >> (gbool &) = 0;
	virtual GArchive &operator >> (gchar &) = 0;
	virtual GArchive &operator >> (gschar &) = 0;
	virtual GArchive &operator >> (guchar &) = 0;
	virtual GArchive &operator >> (gchar16 &) = 0;
	virtual GArchive &operator >> (gchar32 &) = 0;
	virtual GArchive &operator >> (gwchar &) = 0;
	virtual GArchive &operator >> (gshort &) = 0;
	virtual GArchive &operator >> (gushort &) = 0;
	virtual GArchive &operator >> (gint &) = 0;
	virtual GArchive &operator >> (guint &) = 0;
	virtual GArchive &operator >> (glong &) = 0;
	virtual GArchive &operator >> (gulong &) = 0;
	virtual GArchive &operator >> (glonglong &) = 0;
	virtual GArchive &operator >> (gulonglong &) = 0;
	virtual GArchive &operator >> (gfloat &) = 0;
	virtual GArchive &operator >> (gdouble &) = 0;
	virtual GArchive &operator >> (glongdouble &) = 0;
};

} // namespace gsystem

#endif // _CORE_ARCHIVE_H_