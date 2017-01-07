#ifndef _CORE_DATETIME_PRIVATE_H
#define _CORE_DATETIME_PRIVATE_H

#include "CsGlobal_Ex.h"

class GDateTime;
class GDate;
class GTime;

class CsDateTime_Ex
{
public:
	static gbool GetNow(GDateTime &dt);
	static gbool GetNow(GDate &d);
	static gbool GetNow(GTime &t);

private:
	static gbool GetNow(guint &y, guint &m, guint &d, guint &dofw,
		guint &h, guint &mm, guint &s, guint &ms);
};

#endif // _CORE_DATETIME_PRIVATE_H