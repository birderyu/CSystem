/****************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file	gserializable.h
** @brief	���ļ����������л��ӿڵĶ���
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2017-4-8
** @version	1.0.0
**
****************************************************************************/

#ifndef _CORE_SERIALIZABLE_H_
#define _CORE_SERIALIZABLE_H_

#include "gtype.h"

namespace gsystem { // gsystem
	class GString;
	class GArchive;
} // namespace gsystem

namespace gsystem { // gsystem

/****************************************************************************
**
** @brief	���л��ӿ�
**
** �̳иýӿڲ�ʵ���˸ýӿ��ж���ķ������࣬��һ�����Ա����л�����
**
****************************************************************************/
class GAPI GSerializable
{
public:
	/****************************************************************************
	**
	** @name	~GSerializable
	** @brief	����������destructor��
	**
	****************************************************************************/
	virtual ~GSerializable() = 0;

	/****************************************************************************
	**
	** @name	ClassCode
	** @brief	���ص�ǰ��������к�
	** @return	{guint} �����к�
	**
	** �����к������ж����Ƿ�һ��
	**
	****************************************************************************/
	virtual guint ClassCode() const GNOEXCEPT = 0;

	/****************************************************************************
	**
	** @name	ClassName
	** @brief	���ص�ǰ�������
	** @return	{GString} ����
	**
	****************************************************************************/
	//virtual GString ClassName() const GNOEXCEPT = 0;

	/****************************************************************************
	**
	** @name		Serialize
	** @brief		���л�����
	** @param[in]	archive {GArchive &} ������
	** @return		{gbool} ���л��Ƿ�ɹ�
	**
	****************************************************************************/
	virtual gbool Serialize(GArchive &archive) const = 0;

	/****************************************************************************
	**
	** @name		Deserialize
	** @brief		�����л�����
	** @param[in]	archive {GArchive &} ������
	** @return		{gbool} �����л��Ƿ�ɹ�
	**
	****************************************************************************/
	virtual gbool Deserialize(GArchive &archive) = 0;
};

} // namespace gsystem

#endif // _CORE_SERIALIZABLE_H_
