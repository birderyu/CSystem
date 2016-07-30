#ifndef _CSCORE_CSTHREAD_PRIVATE_H_
#define _CSCORE_CSTHREAD_PRIVATE_H_

#include "CsObject_Private.h"

class CsThread;

class CsThread_Private :public CsObject_Private
{
public:
	CsThread_Private(CsThread *pPublic);
	~CsThread_Private();

	/// �����̲߳�����
	virtual cs_int Start();
	virtual void Stop(cs_ulong nMsecs);

	/// �õ�ǰ�߳�˯�ߣ���λ����
	static void Sleep(cs_ulong nSecs);

	/// �õ�ǰ�߳�˯�ߣ���λ������
	static void MSleep(cs_ulong nMsecs);

	/// ����ָ�����߳�
	static void Join(CsThread_Private *pThread);

private:
	/// ��ǰ�߳���ľ�����ڲ�ͬ�Ĳ���ϵͳ��ʹ�ò�ͬ�Ľṹ
	void *m_pHandle;
};

#endif // _CSCORE_CSTHREAD_PRIVATE_H_