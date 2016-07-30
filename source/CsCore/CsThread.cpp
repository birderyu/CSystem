/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2015-2020, NARI Corporation. All rights reserved.
/// @brief �߳�����Win32�µ�ʵ��
/// 
///  ���ļ��а������߳���CsThread��Win32�µľ���ʵ�ַ���
///  ����ײ�ʹ�ú���_beginthreadex����CreateThreadȥ����һ���߳�
/// 
/// @author  Birderyu
/// @version 1.0
/// @date    2016-02-05
/////////////////////////////////////////////////////////////////////////////////

#include "CsThread.h"
#include "CsThread_Private.h"

CsThread::CsThread()
:CsObject(new CsThread_Private(this))
{

}

CsThread::~CsThread()
{

}

int CsThread::Start()
{
	CS_PRIVATE(CsThread);
	return pPrivate->Start();
}

void CsThread::Stop(cs_ulong nMsecs)
{
	CS_PRIVATE(CsThread);
	pPrivate->Stop(nMsecs);
}

void CsThread::Sleep(cs_ulong nSecs)
{
	CsThread_Private::Sleep(nSecs);
}

void CsThread::MSleep(cs_ulong nMsecs)
{
	CsThread_Private::MSleep(nMsecs);
}

void CsThread::Join(CsThread *pThread)
{
	CsThread_Private::Join((CsThread_Private*)pThread->GetPrivate());
}

int CsThread::Run()
{
	return 0;
}