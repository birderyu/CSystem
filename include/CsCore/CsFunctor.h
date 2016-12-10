#ifndef _CORE_FUNCTOR_H_
#define _CORE_FUNCTOR_H_

#include "CsType.h"

/// һԪ����
template<typename ArgType,
	typename ResultType>
struct CsUnaryF
{

};

/// ��Ԫ����
template<typename Arg1Type,
	typename Arg2Type,
	typename ResultType>
struct CsBinaryF
{

};

/// ��Ԫ������С��
template<typename ArgType = void>
struct CsLessF
	: public CsBinaryF<ArgType, ArgType, cs_bool>
{
	cs_bool operator()(const ArgType &left, const ArgType &right) const
	{
		return (left < right);
	}
};

/// ��Ԫ�������Ƚ�
template<typename ArgType = void>
struct CsCompareF
	: public CsBinaryF<ArgType, ArgType, cs_int>
{
	cs_int operator()(const ArgType &left, const ArgType &right) const
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