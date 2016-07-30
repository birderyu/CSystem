#ifndef _CSCORE_CSENDIAN_H_
#define _CSCORE_CSENDIAN_H_

#include "CsCoreGlobal.h"

class CsCore_Export CsEndian
{
public:
	/// ������ת��Ϊ����ֽ�����
	/// 
	/// @param[in]	nValue ��ת��������
	/// @parma[out]	nData ���ִ����ǰ���ֽ�����
	/// @return void��
	static void ToBigEndianBytes(cs_uint16 nValue, cs_byte nData[]);
	static void ToBigEndianBytes(cs_uint32 nValue, cs_byte nData[]);
	static void ToBigEndianBytes(cs_uint64 nValue, cs_byte nData[]);

	/// ������ֽ�����ת��Ϊ����
	/// 
	/// @param[in]	nData �����ǰ���ֽ�����
	/// @param[out]	nValue ת���������
	/// @return void��
	static void ToBigEndianNumber(cs_byte nData[], cs_uint16 &nValue);
	static void ToBigEndianNumber(cs_byte nData[], cs_uint32 &nValue);
	static void ToBigEndianNumber(cs_byte nData[], cs_uint64 &nValue);

	/// ������ת��ΪС���ֽ�����
	/// 
	/// @param[in]	nValue ��ת��������
	/// @param[out]	nData ����С����ǰ���ֽ�����
	/// @return void��
	static void ToLittleEndianBytes(cs_uint16 nValue, cs_byte nData[]);
	static void ToLittleEndianBytes(cs_uint32 nValue, cs_byte nData[]);
	static void ToLittleEndianBytes(cs_uint64 nValue, cs_byte nData[]);
	
	/// ��С���ֽ�����ת��Ϊ����
	/// 
	/// @param[in]	nData С����ǰ���ֽ�����
	/// @param[out]	nValue ת���������
	/// @return void��
	static void ToLittleEndianNumber(cs_byte nData[], cs_uint16 &nValue);
	static void ToLittleEndianNumber(cs_byte nData[], cs_uint32 &nValue);
	static void ToLittleEndianNumber(cs_byte nData[], cs_uint64 &nValue);

protected:
	CsEndian();
	~CsEndian();
};

#endif // _CSCORE_CSENDIAN_H_
