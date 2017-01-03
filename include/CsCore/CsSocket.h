/****************************************************************************
**
** CNova: A quick, micro library of C++
**
** @file	CsSocket.h
** @brief	�׽������͵Ķ���
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0
** @see		CsSocket
**
****************************************************************************/

#ifndef _CORE_SOCKET_H_
#define _CORE_SOCKET_H_

#include "CsGlobal.h"

class CsSocket_Ex;
class CsSockAddress;

/****************************************************************************
**
** CsSocket.h
**
** @class		CsSocket
** @brief		�׽�������
** @module		CsCore
**
** �ṩ�˿�ƽ̨���׽������ʵ�֣�������һ�������࣬�������������ʵ�֣�
** CsTcpSocket {@see CsTcpSocket} ��CsUdpSocket {@see CsUdpSocket}��
**
****************************************************************************/
class CS_API CsSocket 
{
public:
	/****************************************************************************
	**
	** CsObject
	**
	** @name		CsSocket
	** @brief		���캯����constructor��
	** @param[in]	socket_ex {CsSocket_Ex *} ˽��ʵ�����ָ�룬�����ഫ�롣
	**
	****************************************************************************/
	CsSocket(CsSocket_Ex *socket_ex);
	virtual ~CsSocket() = 0;

	virtual cs_bool Open(cs_bool nResue = false) = 0;
	virtual cs_bool Open(const CsSockAddress &tSockAddr, cs_bool nResue = false) = 0;
	virtual cs_void Close() = 0;

	cs_bool SetRecvTimeout(cs_int nMsecs);
	cs_int	GetRecvTimeout() const;

	cs_bool SetSendTimeout(cs_int nMsecs);
	cs_int	GetSendTimeout() const;

	cs_bool SetReuseAddress(cs_bool nResue);

	cs_bool GetPeerAddr(CsSockAddress &tSockAddr) const;
	cs_bool GetLocalAddr(CsSockAddress &tSockAddr) const;

protected:
	CsSocket_Ex *m_pSocket_Ex;
};

#endif // _CSCORE_CSSOCKET_H_
