 #ifndef _CORE_AMAZING_H_
#define _CORE_AMAZING_H_

#include "CsGlobal.h"

class CS_API CsAmazing
{
	/// ������ƽ�����ĵ���
	cs_float FastInvSqrt(cs_float x)
	{
		cs_float xhalf = 0.5f * x;
		cs_int i = *(cs_int*)&x;
		i = 0x5f3759df - (i >> 1);
		x = *(cs_float*)&i;
		x = x*(1.5f - (xhalf*x*x));
		return x;
	}
};

#endif // _CORE_AMAZING_H_