/****************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file	gsocket.h
** @brief	�׽������͵Ķ���
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0
** @see		GSocket
**
****************************************************************************/

#ifndef _CORE_SOCKET_H_
#define _CORE_SOCKET_H_

#include "gglobal.h"

namespace gnova { // gnova
	class GSockAddress;
	namespace detail { // gnova.detail
		class GSocket_Ex;
	} // namespace gnova.detail
} // namespace gnova

namespace gnova { // gnova

/****************************************************************************
**
** gsocket.h
**
** @class		GSocket
** @brief		�׽�������
** @module		GCore
**
** �ṩ�˿�ƽ̨���׽������ʵ�֣�������һ�������࣬�������������ʵ�֣�
** GTcpSocket {@see GTcpSocket} ��GUdpSocket {@see GUdpSocket}��
**
****************************************************************************/
class GAPI GSocket
{
public:
	/****************************************************************************
	**
	** GSocket
	**
	** @name		GSocket
	** @brief		���캯����constructor��
	** @param[in]	socket_ex {GSocket_Ex *} ˽��ʵ�����ָ�룬�����ഫ�롣
	**
	****************************************************************************/
	GSocket(detail::GSocket_Ex *socket_ex);
	virtual ~GSocket() = 0;

	virtual gbool Open(gbool nResue = false) = 0;
	virtual gbool Open(const GSockAddress &tSockAddr, gbool nResue = false) = 0;
	virtual gvoid Close() = 0;

	gbool SetRecvTimeout(gint nMsecs);
	gint GetRecvTimeout() const;

	gbool SetSendTimeout(gint nMsecs);
	gint GetSendTimeout() const;

	gbool SetReuseAddress(gbool nResue);

	gbool GetPeerAddr(GSockAddress &tSockAddr) const;
	gbool GetLocalAddr(GSockAddress &tSockAddr) const;

protected:
	detail::GSocket_Ex *m_pSocket_Ex;
};

} // namespace gnova

#endif // _CORE_SOCKET_H_
