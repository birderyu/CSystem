/****************************************************************************
**
** GSystem: A quick, micro library of C++
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

GObject::~GObject()
{
	// �����������붨��Ϊ����ģ����ṩһ��Ĭ�ϵ�ʵ�֣����������ڴ�й©
}

GObjectPtr GObject::Clone() const
{
	// Ĭ������£�����һ����ָ��
	return GObjectPtr();
}

const GObject *GObject::Boxing() const
{
	// Ĭ������£�����thisָ�룬���̳�����Ƚϸ���ʱ���÷���ʧЧ
	return this;
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

gbool GObject::Equals(const GObject *obj) const
{
	// Ĭ������£��Ƚ�ָ������ֵ
	return this == obj;
}

} // namespace gsystem
