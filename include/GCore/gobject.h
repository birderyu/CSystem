/****************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file	gobject.h
** @brief	�����������͵Ķ���
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0
** @see		GObject
**
****************************************************************************/

#ifndef _CORE_OBJECT_H_
#define _CORE_OBJECT_H_

#include "gtype.h"
#include "gglobal.h"

namespace gsystem { // gsystem
	class GObject;
	class GString;
	class GBytes;
	template <typename ClassT> class GSharedPointer;
	typedef GSharedPointer<GObject> GObjectPtr;
} // namespace gsystem

namespace gsystem { // gsystem

/****************************************************************************
**
** gobject.h
**
** @class		GObject
** @brief		������������
** @module		GCore
**
** ��������������������Դ����Ļ����ͣ����ڷ���Դ�Ͷ�����ں˶������Ƽ��̳и��ࡣ
** ��Ϊ���������һ������������ԣ�
** 1���ɸ��ƣ����ƶ������и��ƹ��캯����������������ƶ����캯�����ƶ������
** 2������ת��Ϊ�ֽڴ����ַ���
**
****************************************************************************/
class GAPI GObject
{
public:
	enum { CLASS_CODE = CLASS_CODE_OBJECT, };

public:
	/****************************************************************************
	**
	** GObject
	**
	** @name	~GObject
	** @brief	����������destructor��
	**
	** ����GObject��Ҫ��Ϊ������Դ��Ļ��࣬�����������������������ģ�virtual����
	**
	****************************************************************************/
	virtual ~GObject() = 0;

	/****************************************************************************
	**
	** GObject
	**
	** @name	Clone
	** @brief	������һ���µ�ʵ��
	** @return	{GObjectPtr} ��������ʵ������һ������ָ�루GSharedPointer��
	** @exception
	** @see		GSharedPointer<T>
	** @see		GObjectP
	**
	****************************************************************************/
	virtual GObjectPtr Clone() const;

	/****************************************************************************
	**
	** GObject
	**
	** @name	Boxing
	** @brief	����
	** @return	{const GObject *} �Ե�ǰ����ķ���
	**
	** ��������ǽ���ǰ����ת��Ϊ�������͵ķ��������Ǵ������µ�ʵ����
	**
	****************************************************************************/
	virtual const GObject *Boxing() const;

	/****************************************************************************
	**
	** GObject
	**
	** @name		Unboxing
	** @brief		����
	** @param[in]	obj {const GObject *} ���������ָ��
	** @return		{gbool} ��������Ƿ�ɹ�
	**
	** ��һ�����������ָ����䵽��ǰ�ࡣ
	**
	****************************************************************************/
	virtual gbool Unboxing(const GObject *obj);

	/****************************************************************************
	**
	** GObject
	**
	** @name	ToString
	** @brief	�����ڶ���ת��Ϊ�ַ���
	** @return	{GString} ת���ɵ��ַ������ͣ�GString��
	** @see		GString
	**
	****************************************************************************/
	virtual GString ToString() const;

	/****************************************************************************
	**
	** GObject
	**
	** @name	ToBytes
	** @brief	�����ڶ���ת��Ϊ����������
	** @return	{GBytes} ת���ɵĶ������������ͣ�GBytes��
	** @see		GBytes
	**
	****************************************************************************/
	virtual GBytes ToBytes() const;

	/*
	virtual gbool FromString(const GString &str);
	virtual GBytes ToBytes() const;
	virtual gbool FromBytes(const GBytes &bytes);
	*/

	/****************************************************************************
	**
	** GObject
	**
	** @name	ClassCode
	** @brief	��ȡ��ǰ����������кţ�ClassCode��
	** @return	{guint} �����к�
	**
	****************************************************************************/
	virtual guint ClassCode() const;

	/****************************************************************************
	**
	** GObject
	**
	** @name	ClassCode
	** @brief	��ȡ��ǰ����Ĺ�ϣ�루HashCode��
	** @return	{guint} ��ϣ��ֵ
	**
	****************************************************************************/
	virtual guint HashCode() const;

	/****************************************************************************
	**
	** GObject
	**
	** @name		Equals
	** @brief		�ж϶����Ƿ�ֵ���
	** @param[in]	obj {const GObject *} ���������ָ��
	** @return		{gbool} ����ȣ��򷵻�true�����򷵻�false
	**
	****************************************************************************/
	virtual gbool Equals(const GObject *obj) const;

	/****************************************************************************
	**
	** GObject
	**
	** @name	Serializable
	** @brief	��ǰ�����Ƿ�֧�����л�
	** @return	{gbool} ��֧�����л����򷵻�true�����򷵻�false
	**
	** ������֧�����л�����Ӧ�ṩ���л���Serialize���ͷ����л���Deserialize���ķ�����
	** ������������ģ�巽����template������Ҫ�������л��ĵ����ࣨArchiveT��������Ҫ
	** ģ��GSerialization��֧�֡�
	**
	****************************************************************************/
	virtual gbool Serializable() const;

	/****************************************************************************
	**
	** GObject
	**
	** @name		Serialize
	** @brief		���л�
	** @param[out]	archive {ArchiveT &} �鵵��
	** @return		{gbool} ���л��Ƿ�ɹ�
	** @see			GArchive
	**
	** ����ǰ������������л��������У���Ҫ���л�ģ��GSerialization��֧��
	**
	****************************************************************************/
	//template<typename ArchiveT> gbool Serialize(ArchiveT &archive) const;

	/****************************************************************************
	**
	** GObject
	**
	** @name		Deserialize
	** @brief		�����л�
	** @param[in]	archive {ArchiveT &} �鵵��
	** @return		{gbool} �����л��Ƿ�ɹ�
	** @see			GArchive
	**
	** �����������л�Ϊ��ǰ��������ݣ���Ҫ���л�ģ��GSerialization��֧��
	**
	****************************************************************************/
	//template<typename ArchiveT> gbool Deserialize(ArchiveT &archive);
};

} // namespace gsystem

#endif // _CORE_OBJECT_H_
