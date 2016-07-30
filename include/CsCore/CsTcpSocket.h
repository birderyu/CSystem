#ifndef _CSCORE_CSTCPSOCKET_H_
#define _CSCORE_CSTCPSOCKET_H_

#include "CsSocket.h"

class CsCore_Export CsTcpSocket :public CsSocket
{
public:
	CsTcpSocket();
	virtual ~CsTcpSocket();

	cs_int Open(cs_bool nResue = false);
	cs_int Open(const CsSockAddress &tSockAddr, cs_bool nResue = false);
	void Close();

	// ������
	cs_int Listen(cs_int nBackLog = 16);
	cs_int Accept(const CsTcpSocket &pPeer);

	// �ͻ���
	cs_int Connect(const CsSockAddress &tSockAddr);

	// ���ͽ���
	cs_int Send(const void *pBufData, cs_int nDataLen);
	cs_int Recv(void *pBufData, cs_int nDataLen, cs_int nWaitAll = 0);

public:
	enum { CLASSCODE = CORE_CLASSCODE_TCPSOCKET, };
};

#endif // _CSCORE_CSTCPSOCKET_PRIVATE_H_