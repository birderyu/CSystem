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

#include "gtype.h"

namespace gsystem { // gsystem
	class GSocketAddress;
	namespace detail { // gsystem.detail
		class GSocket_Ex;
	} // namespace gsystem.detail
} // namespace gsystem

namespace gsystem { // gsystem

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

	virtual gbool Open(gbool resue = false) = 0;
	virtual gbool Open(const GSocketAddress &addr, gbool resue = false) = 0;
	virtual gvoid Close() = 0;

	gbool SetRecvTimeout(gint msecs);
	gint GetRecvTimeout() const;

	gbool SetSendTimeout(gint msecs);
	gint GetSendTimeout() const;

	gbool SetReuseAddress(gbool resue);

	GSocketAddress GetPeerAddr() const;
	GSocketAddress GetLocalAddr() const;

protected:
	detail::GSocket_Ex *m_pSocket_Ex;
};

} // namespace gsystem

#endif // _CORE_SOCKET_H_
