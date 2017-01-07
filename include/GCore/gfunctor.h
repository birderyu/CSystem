#ifndef _CORE_FUNCTOR_H_
#define _CORE_FUNCTOR_H_

#include "gtype.h"

/// һԪ����
template<typename ArgType,
	typename ResultType>
struct GUnaryF
{

};

/// ��Ԫ����
template<typename Arg1Type,
	typename Arg2Type,
	typename ResultType>
struct GBinaryF
{

};

/// ��Ԫ����������
/// ����Ӧ��������״̬�����ڡ�������
template<typename ArgType = void>
struct GEqualToF
	: public GBinaryF<ArgType, ArgType, gbool>
{
	gbool operator()(const ArgType &left, const ArgType &right) const
	{
		return (left == right);
	}
};

/// ��Ԫ������С��
/// С��Ӧ��������״̬��С�ڡ���С��
template<typename ArgType = void>
struct GLessThanF
	: public GBinaryF<ArgType, ArgType, gbool>
{
	gbool operator()(const ArgType &left, const ArgType &right) const
	{
		return (left < right);
	}
};

/// ��Ԫ����������
/// ����Ӧ��������״̬�����ڡ�������
template<typename ArgType = void>
struct GGreaterThanF
	: public GBinaryF<ArgType, ArgType, gbool>
{
	gbool operator()(const ArgType &left, const ArgType &right) const
	{
		return (left > right);
	}
};

/// ��Ԫ�������Ƚ�
/// �Ƚ�Ӧ�÷�������״̬�����ڡ����ڡ�С��
template<typename ArgType = void>
struct GCompareToF
	: public GBinaryF<ArgType, ArgType, gint>
{
	gint operator()(const ArgType &left, const ArgType &right) const
	{
		if (left < right)
		{
			return -1;
		}
		else if (left > right)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
};

#endif // _CORE_FUNCTOR_H_