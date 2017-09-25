#ifndef _CORE_SERIALIZE_H_
#define _CORE_SERIALIZE_H_

#include "gserializable.h"

namespace gsystem { // gsystem

/****************************************************************************
**
** @name GSerialize
** @brief ȫ�ֵ����л�����
** @param [in] archive {GArchive &} ����
** @throws GSerializationException
**
** ȫ�ֵ����л���������Ҫ����ģ������������л�
**
****************************************************************************/
template<typename T>
gbool GSerialize(GArchive &archive, const T &v);

/****************************************************************************
**
** @name GDeserialize
** @brief ȫ�ֵķ����л�����
** @throws GSerializationException
**
** ȫ�ֵ����л���������Ҫ����ģ��������ķ����л�
**
****************************************************************************/
template<typename T>
gbool GDeserialize(GArchive &archive, T &v);

} // namespace gsystem

#include "inline/gserialize.inl"

#endif // _CORE_SERIALIZE_H_