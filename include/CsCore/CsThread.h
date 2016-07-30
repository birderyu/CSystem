/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2015-2020, NARI Corporation. All rights reserved.
/// @brief �߳���Ķ���
/// 
///  ���ļ��а������߳���CsThread�Ķ���
/// 
/// @author  Birderyu
/// @version 1.0
/// @date    2016-02-05
/////////////////////////////////////////////////////////////////////////////////

#ifndef _CSCORE_CSTHREAD_H_
#define _CSCORE_CSTHREAD_H_

#include "CsCoreGlobal.h"
#include "CsObject.h"

/// �߳���
class CsCore_Export CsThread :public CsObject
{
public:
	CsThread();
	virtual ~CsThread();

	/// �����̲߳�����
	virtual cs_int Start();

	/// ��ֹһ���߳�
	virtual void Stop(cs_ulong nMsecs = 0);

	/// �õ�ǰ�߳�˯�ߣ���λ����
	static void Sleep(cs_ulong nSecs);

	/// �õ�ǰ�߳�˯�ߣ���λ������
	static void MSleep(cs_ulong nMsecs);

	/// ����ָ�����߳�
	static void Join(CsThread *pThread);

	/// �߳���������
	virtual int Run() = 0;

public:
	enum { CLASSCODE = CORE_CLASSCODE_THREAD, };
};

#endif // _CSCORE_CSTHREAD_H_
