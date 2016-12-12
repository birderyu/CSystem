/****************************************************************************
**
** Supernova: A quick, micro library of C++
**
** @file	CsObject.h
** @brief	�����������͵Ķ���
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0
** @see		CsObject
**
****************************************************************************/

#ifndef _CORE_OBJECT_H_
#define _CORE_OBJECT_H_

#include "CsGlobal.h"
#include "CsSharedPointer.h"

class CsObject;
class CsString;
class CsBytes;
typedef CsSharedPointer<CsObject> CsObjectP;

/****************************************************************************
**
** CsObject.h
**
** @class		CsObject
** @brief		������������
** @module		CsCore
** @property	CLASSCODE
** @method		Clone
** @method		Boxing
** @method		Unboxing
** @method		ToString
** @method		ClassCode
** @method		HashCode
** @method		Equals
** @method		Serialize
** @method		Deserialize
**
** ��������������������Դ����Ļ����ͣ����ڷ���Դ�Ͷ�����ں˶������Ƽ��̳и��ࡣ
**
****************************************************************************/
class CS_API CsObject
{
public:
	enum { CLASSCODE = CORE_CLASSCODE_OBJECT, };

public:
	/****************************************************************************
	**
	** CsObject
	**
	** @name	~CsObject
	** @brief	����������destructor��
	**
	** ����CsObject��Ҫ��Ϊ������Դ��Ļ��࣬�����������������������ģ�virtual����
	**
	****************************************************************************/
	virtual ~CsObject() = 0;

	/****************************************************************************
	**
	** CsObject
	**
	** @name	Clone
	** @brief	������һ���µ�ʵ��
	** @return	��������ʵ������һ������ָ�루CsSharedPointer��
	** @exception
	** @see		CsSharedPointer<T>
	** @see		CsObjectP
	**
	****************************************************************************/
	virtual CsObjectP Clone() const;

	/****************************************************************************
	**
	** CsObject
	**
	** @name	Boxing
	** @brief	����
	** @return	�Ե�ǰ����ķ���
	**
	** ��������ǽ���ǰ����ת��Ϊ�������͵ķ��������Ǵ������µ�ʵ����
	**
	****************************************************************************/
	virtual const CsObject *Boxing() const;

	/****************************************************************************
	**
	** CsObject
	**
	** @name		Unboxing
	** @brief		����
	** @param[in]	���������ָ��
	** @return		��������Ƿ�ɹ�
	**
	** ��һ�����������ָ����䵽��ǰ�ࡣ
	**
	****************************************************************************/
	virtual cs_bool Unboxing(const CsObject *);

	/****************************************************************************
	**
	** CsObject
	**
	** @name	ToString
	** @brief	�����ڶ���ת��Ϊ�ַ���
	** @return	ת���ɵ��ַ������ͣ�CsString��
	** @see		CsString
	**
	****************************************************************************/
	virtual CsString ToString() const;

	/****************************************************************************
	**
	** CsObject
	**
	** @name	ClassCode
	** @brief	��ȡ��ǰ����������кţ�ClassCode��
	** @return	�����к�
	**
	****************************************************************************/
	virtual cs_uint ClassCode() const;

	/****************************************************************************
	**
	** CsObject
	**
	** @name	ClassCode
	** @brief	��ȡ��ǰ����Ĺ�ϣ�루HashCode��
	** @return	��ϣ��ֵ
	**
	****************************************************************************/
	virtual cs_uint HashCode() const;

	/****************************************************************************
	**
	** CsObject
	**
	** @name		Equals
	** @brief		�ж϶����Ƿ�ֵ���
	** @param[in]	���������ָ��
	** @return		����ȣ��򷵻�true�����򷵻�false
	**
	****************************************************************************/
	virtual cs_bool Equals(const CsObject *) const;

	/****************************************************************************
	**
	** CsObject
	**
	** @name		Serialize
	** @brief		���л�
	** @param[out]	�ֽ���
	** @return		���л��Ƿ�ɹ�
	** @see			CsBytes
	**
	** ����ǰ������������л����ֽ�����
	**
	****************************************************************************/
	virtual cs_bool Serialize(CsBytes &) const;

	/****************************************************************************
	**
	** CsObject
	**
	** @name		Deserialize
	** @brief		�����л�
	** @param[in]	�ֽ���
	** @return		�����л��Ƿ�ɹ�
	** @see			CsBytes
	**
	** ���ֽ��������л�Ϊ��ǰ���������
	**
	****************************************************************************/
	virtual cs_bool Deserialize(CsBytes &);
};

#endif // _CORE_OBJECT_H_
