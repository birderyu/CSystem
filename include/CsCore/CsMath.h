#ifndef _CSCORE_CSMATH_H_
#define _CSCORE_CSMATH_H_

#include "CsCoreGlobal.h"

class CsCore_Export CsMath
{
public:
	/// ����2
	static cs_real Cs_Sqrt2;

	/// Բ����
	static cs_real Cs_PI;

	/// Բ���ʳ���2
	static cs_real Cs_PI_2;

	/// Բ���ʳ���4
	static cs_real Cs_PI_4;

	/// Բ���ʵĵ���
	static cs_real Cs_1_PI;

	/// 2����Բ����
	static cs_real Cs_2_PI;

	/// ��Ȼ����
	static cs_real Cs_E;
	static cs_real Cs_Log2E;
	static cs_real Cs_Log10E;
	static cs_real Cs_Ln2;
	static cs_real Cs_Ln10;

	/// ȡ����ֵ
	static cs_uint		Abs(cs_int v);
	static cs_double	Abs(cs_double v);
	static cs_decimal	Abs(cs_decimal v);

	static cs_int Ceil(cs_real v);
	static cs_int Floor(cs_real v);
	static cs_real FastSin(cs_real x);

protected:
	CsMath();
	~CsMath();
};

#endif // _CSCORE_CSMATH_H_
