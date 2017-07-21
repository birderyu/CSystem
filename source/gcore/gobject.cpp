/****************************************************************************
**
** gsystem: A quick, micro library of C++
**
** @file	gobject.cpp
** @brief	�����������͵�Ĭ��ʵ��
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0
**
****************************************************************************/

#include "gobject.h"
#include "gstring.h"
#include "gbytes.h"
#include "gsharedptr.h"

namespace gsystem { // gsystem

GObjectPtr GObject::Clone() const
{
	// Ĭ������£�����һ����ָ��
	return GObjectPtr();
}

const GObject *GObject::Boxing() const
{
	return dynamic_cast<const GObject *>(this);
}

gbool GObject::Unboxing(const GObject *)
{
	// Ĭ������£����������
	return false;
}

GString GObject::ToString() const
{
	// Ĭ������£�����һ�����ַ���
	return GString();
}

GBytes GObject::ToBytes() const
{
	// Ĭ������£�����һ�����ֽڴ�
	return GBytes();
}

guint GObject::HashCode() const
{
	// Ĭ������£�����ָ����ָ��ַ������ֵ
	return (guint)this;
}

gbool GObject::Equals(const GObject &obj) const
{
	return Boxing() == obj.Boxing();
}

} // namespace gsystem
