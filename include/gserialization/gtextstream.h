// �ı���
#ifndef _CORE_TEXT_STREAM_H_
#define _CORE_TEXT_STREAM_H_

#include "gstream.h"
#include "GCore/gstring8.h"

class GAPI GTextStream
	: virtual public GStream
{
public:
	virtual ~GTextStream() = 0;
	gbool IsBinary() const;

	virtual GString ToString() const = 0;
};

#endif // _CORE_TEXT_STREAM_H_