#ifndef _CSCORE_CSMATH_H_
#define _CSCORE_CSMATH_H_

#include "CsCoreGlobal.h"

class CsCore_Export CsMath
{
public:
	/// ����2
	static cs_double Cs_Sqrt2;

	/// Բ����
	static cs_double Cs_PI;

	/// Բ���ʳ���2
	static cs_double Cs_PI_2;

	/// Բ���ʳ���4
	static cs_double Cs_PI_4;

	/// Բ���ʵĵ���
	static cs_double Cs_1_PI;

	/// 2����Բ����
	static cs_double Cs_2_PI;

	/// ��Ȼ����
	static cs_double Cs_E;
	static cs_double Cs_Log2E;
	static cs_double Cs_Log10E;
	static cs_double Cs_Ln2;
	static cs_double Cs_Ln10;

	/// ���ֱȽ�
	static cs_bool Equals(cs_float v1, cs_float v2, cs_float precision);
	static cs_bool Equals(cs_double v1, cs_double v2, cs_double precision);

	/// ȡ����ֵ
	static cs_uint Abs(cs_int v);
	static cs_uint Abs(cs_float v);
	static cs_double Abs(cs_double v);
	static cs_decimal Abs(cs_decimal v);

	static cs_int Ceil(cs_float v);
	static cs_int Ceil(cs_double v);
	static cs_int Ceil(cs_decimal v);

	static cs_int Floor(cs_double v);

	/// ���Ǻ���
	static cs_double FastSin(cs_double x);

protected:
	CsMath();
	~CsMath();
};

#endif // _CSCORE_CSMATH_H_
