#include "goutofmemoryexception.h"

namespace gsystem {

GOutOfMemoryException::GOutOfMemoryException() GNOEXCEPT
	: GSystemException()
{

}

GOutOfMemoryException::GOutOfMemoryException(
	const GString &methodName, gsize lineNumber, 
	const GString &fileName, const GStringList *whatArguments,
	const GString &whyMessageId, const GStringList *whyArguments) GNOEXCEPT
	: GSystemException(methodName, lineNumber, fileName, 
		whatArguments, whyMessageId, whyArguments)
{

}

GOutOfMemoryException::~GOutOfMemoryException() GNOEXCEPT
{

}

gvoid GOutOfMemoryException::Raise()
{
	throw this;
}

}