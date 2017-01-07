#include "CsDateTime_Ex.h"
#include "gdatetime.h"
#include <time.h>
#ifdef WIN32
#include <windows.h>
#endif

gbool CsDateTime_Ex::GetNow(GDateTime &dt)
{
	return false;
}

gbool CsDateTime_Ex::GetNow(GDate &d)
{
	return false;
}

gbool CsDateTime_Ex::GetNow(GTime &t)
{
	return false;
}

gbool CsDateTime_Ex::GetNow(guint &y, guint &m, guint &d, guint &dofw,
	guint &h, guint &mm, guint &s, guint &ms)
{
	guint intertimep;
	gushort  msecp;
	struct tm breakuptime;
	time_t tmptime;

#ifdef WIN32
	intertimep = (guint)time(NULL);
	SYSTEMTIME cursystimep;
	GetSystemTime(&cursystimep);
	msecp = cursystimep.wMilliseconds;

	tmptime = (time_t)intertimep;
	errno_t errno;
	errno = localtime_s(&breakuptime, (time_t *)&tmptime);
	if (errno != 0) 
	{
		return false;
	}
#else
	struct timeval  tmptimeval;
	gettimeofday(&tmptimeval, NULL);
	intertimep = (guint)tmptimeval.tv_sec;
	msecp = (gshort)(tmptimeval.tv_usec / 1000);
	tmptime = (time_t)intertimep;
	struct tm  * ptm = localtime_r((time_t *)&tmptime, (tm *)&breakuptime);
	if (ptm == NULL)
	{
		return false
	};
#endif

	
	y = breakuptime.tm_year + 1900;
	m = breakuptime.tm_mon + 1;
	d = breakuptime.tm_mday;
	dofw = breakuptime.tm_mday;
	if (dofw == 0)
	{
		dofw = 7;
	}

	h = breakuptime.tm_hour;
	mm = breakuptime.tm_min;
	s = breakuptime.tm_sec;
	ms = msecp;
	return true;
}