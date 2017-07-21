#ifndef _CORE_SERIALIZE_H_
#define _CORE_SERIALIZE_H_

#include "gserializable.h"

namespace gsystem { // gsystem

/****************************************************************************
**
** @name	GSerialize
** @brief	ȫ�ֵ����л�����
**
** ȫ�ֵ����л���������Ҫ����ģ������������л�
**
****************************************************************************/
template<typename DataT>
gbool GSerialize(GArchive &archive, const DataT &v);

/****************************************************************************
**
** @name	GDeserialize
** @brief	ȫ�ֵķ����л�����
**
** ȫ�ֵ����л���������Ҫ����ģ��������ķ����л�
**
****************************************************************************/
template<typename DataT>
gbool GDeserialize(GArchive &archive, DataT &v);

} // namespace gsystem

#include "inline/gserialize.inl"

#endif // _CORE_SERIALIZE_H_