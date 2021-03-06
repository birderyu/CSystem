#ifndef _CORE_INTEGER_H_
#define _CORE_INTEGER_H_

#include "gpackage.h"

namespace gsystem { // gsystem

class GAPI GInteger 
	: public GNumber<gint>
{
public:
	static const gsize MAX_VALUE = G_INT32_MAX;
	static const gsize MIN_VALUE = G_INT32_MIN;

	static gint MaxValue();
	static gint MinValue();
	static GInteger ValueOf(const GString &);

public:
	GInteger(gint val = 0);
	GInteger(const GInteger &);

	guint ClassCode() const GNOEXCEPT;
};

typedef GInteger GInt;
typedef GInteger GInteger32;
typedef GInteger GInt32;

} // namespace gsystem

#endif // _CORE_INTEGER_H_