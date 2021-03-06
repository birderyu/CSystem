#include "glonglonginteger.h"

namespace gsystem { // gsystem

glonglong GLongLongInteger::MaxValue()
{
	return G_INT64_MAX;
}

glonglong GLongLongInteger::MinValue()
{
	return G_INT64_MIN;
}

GLongLongInteger GLongLongInteger::ValueOf(const GString &str)
{
	if (str.IsEmpty())
	{
		return GLongLongInteger();
	}
	return str.ToLongLong();
}

GLongLongInteger::GLongLongInteger(glonglong val)
: GNumber<glonglong>(val)
{

}

GLongLongInteger::GLongLongInteger(const GLongLongInteger &val)
: GNumber<glonglong>(val)
{

}

GLongLongInteger::~GLongLongInteger()
{

}

guint GLongLongInteger::ClassCode() const GNOEXCEPT
{
	return static_cast<guint>(GClassCode::LongLongInteger);
}

} // namespace gsystem
