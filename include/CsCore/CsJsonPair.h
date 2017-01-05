/****************************************************************************
**
** CNova: A quick, micro library of C++
**
** @file	CsJsonPair.h
** @brief	Json����/ֵ�����͵Ķ���
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2017-1-3
** @version	1.0
** @see		CsJsonPair
**
** Json���ݵ���д��ʽ�ǣ�����/ֵ�ԡ�
** ����/ֵ�԰����ֶ����ƣ���˫�����У�������дһ��ð�ţ�Ȼ����ֵ��
**	"firstName" : "John"
**
****************************************************************************/

#ifndef _CORE_JSON_PAIR_H_
#define _CORE_JSON_PAIR_H_

#include "CsString.h"
#include "CsJsonValue.h"

class CsJsonPair
{
private:
	CsString m_sKey;
	CsJsonValue *m_pValue;
};

#endif // _CORE_JSON_PAIR_H_