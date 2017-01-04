/****************************************************************************
**
** CNova: A quick, micro library of C++
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

// �����к�
enum CS_CORE_CLASS_CODE
{
	CLASS_CODE_OBJECT = 0,					// Object

	CLASS_CODE_PACKAGE,						// Package
	CLASS_CODE_NUMBER,						// Number
	CLASS_CODE_BYTE,						// Byte
	CLASS_CODE_BOOLEAN,						// Boolean
	CLASS_CODE_CHARACTER,					// Character
	CLASS_CODE_SIGNED_CHARACTER,			// SignedCharacter
	CLASS_CODE_UNSIGNED_CHARACTER,			// UnsignedCharacter
	CLASS_CODE_WIND_CHARACTER,				// WindCharacter
	CLASS_CODE_SMALL_INTEGER,				// SmallInteger
	CLASS_CODE_UNSIGNED_SMALL_INTEGER,		// UnsignedSmallInteger
	CLASS_CODE_SHORT_INTEGER,				// ShortInteger
	CLASS_CODE_UNSIGNED_SHORT_INTEGER,		// UnsignedShortInteger
	CLASS_CODE_INTEGER,						// Integer
	CLASS_CODE_UNSIGNED_INTEGER,			// UnsignedInteger
	CLASS_CODE_LONG_INTEGER,				// LongInteger
	CLASS_CODE_UNSIGNED_LONG_INTEGER,		// UnsignedLongInteger
	CLASS_CODE_LONG_LONG_INTEGER,			// LongLongInteger
	CLASS_CODE_UNSIGNED_LONG_LONG_INTEGER,	// UnsignedLongLongInteger
	CLASS_CODE_SINGLE_FLOAT,				// SingleFloat
	CLASS_CODE_DOUBLE_FLOAT,				// DoubleFloat
	CLASS_CODE_LONG_DOUBLE_FLOAT,			// LongDoubleFloat

	CLASS_CODE_ARRAY,						// Array
	CLASS_CODE_STATIC_ARRAY,				// StaticArray
	CLASS_CODE_DYNAMIC_ARRAY,				// DynamicArray
	CLASS_CODE_LINKED_LIST,					// LinkedList
	CLASS_CODE_SINGLE_LINKED_LIST,			// SingleLinkedList
	CLASS_CODE_CIRCULAR_LINKED_LIST,		// CircularLinkedList
	CLASS_CODE_DOUBLE_LINKED_LIST,			// DoubleLinkedList
	CLASS_CODE_STACK,						// Stack
	CLASS_CODE_ARRAY_STACK,					// ArrayStack
	CLASS_CODE_LIST_STACK,					// ListStack
	CLASS_CODE_BINARY_TREE,					// BinaryTree
	CLASS_CODE_BINARY_SORT_TREE,			// BinarySortTree

	CLASS_CODE_STRING,						// String
	CLASS_CODE_THREAD,						// Thread
	CLASS_CODE_MUTEX,						// Mutex
	CLASS_CODE_CRITICAL_SECTION,			// CriticalSection

	CLASS_CODE_SOCKET_ADDRESS,				// SockAddress
	CLASS_CODE_SOCKET,						// Socket
	CLASS_CODE_TCPSOCKET,					// TcpSocket
	CLASS_CODE_UDPSOCKET,					// UdpSocket
	CLASS_CODE_VECTOR,						// Vector
	CLASS_CODE_LIST,						// List
	CLASS_CODE_MAP,							// Map
	CLASS_CODE_TABLE,						// Table
	CLASS_CODE_FILE,						// File

	CLASS_CODE_DATE,						// Date
	CLASS_CODE_GEOMETRY,
};

class CsObject;
class CsString;
typedef CsSharedPointer<CsObject> CsObjectP;

/****************************************************************************
**
** CsObject.h
**
** @class		CsObject
** @brief		������������
** @module		CsCore
**
** ��������������������Դ����Ļ����ͣ����ڷ���Դ�Ͷ�����ں˶������Ƽ��̳и��ࡣ
**
****************************************************************************/
class CS_API CsObject
{
public:
	enum { CLASS_CODE = CLASS_CODE_OBJECT, };

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
	** @return	{CsObjectP} ��������ʵ������һ������ָ�루CsSharedPointer��
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
	** @return	{const CsObject *} �Ե�ǰ����ķ���
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
	** @param[in]	obj {const CsObject *} ���������ָ��
	** @return		{cs_bool} ��������Ƿ�ɹ�
	**
	** ��һ�����������ָ����䵽��ǰ�ࡣ
	**
	****************************************************************************/
	virtual cs_bool Unboxing(const CsObject *obj);

	/****************************************************************************
	**
	** CsObject
	**
	** @name	ToString
	** @brief	�����ڶ���ת��Ϊ�ַ���
	** @return	{CsString} ת���ɵ��ַ������ͣ�CsString��
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
	** @return	{cs_uint} �����к�
	**
	****************************************************************************/
	virtual cs_uint ClassCode() const;

	/****************************************************************************
	**
	** CsObject
	**
	** @name	ClassCode
	** @brief	��ȡ��ǰ����Ĺ�ϣ�루HashCode��
	** @return	{cs_uint} ��ϣ��ֵ
	**
	****************************************************************************/
	virtual cs_uint HashCode() const;

	/****************************************************************************
	**
	** CsObject
	**
	** @name		Equals
	** @brief		�ж϶����Ƿ�ֵ���
	** @param[in]	obj {const CsObject *} ���������ָ��
	** @return		{cs_bool} ����ȣ��򷵻�true�����򷵻�false
	**
	****************************************************************************/
	virtual cs_bool Equals(const CsObject *obj) const;

	/****************************************************************************
	**
	** CsObject
	**
	** @name	Serializable
	** @brief	��ǰ�����Ƿ�֧�����л�
	** @return	{cs_bool} ��֧�����л����򷵻�true�����򷵻�false
	**
	** ������֧�����л�����Ӧ�ṩ���л���Serialize���ͷ����л���Deserialize���ķ�����
	** ������������ģ�巽����template������Ҫ�������л��ĵ����ࣨArchiveT��������Ҫ
	** ģ��CsSerialization��֧�֡�
	**
	****************************************************************************/
	virtual cs_bool Serializable() const;

	/****************************************************************************
	**
	** CsObject
	**
	** @name		Serialize
	** @brief		���л�
	** @param[out]	archive {ArchiveT &} �鵵��
	** @return		{cs_bool} ���л��Ƿ�ɹ�
	** @see			CsArchive
	**
	** ����ǰ������������л��������У���Ҫ���л�ģ��CsSerialization��֧��
	**
	****************************************************************************/
	//template<typename ArchiveT> cs_bool Serialize(ArchiveT &archive) const;

	/****************************************************************************
	**
	** CsObject
	**
	** @name		Deserialize
	** @brief		�����л�
	** @param[in]	archive {ArchiveT &} �鵵��
	** @return		{cs_bool} �����л��Ƿ�ɹ�
	** @see			CsArchive
	**
	** �����������л�Ϊ��ǰ��������ݣ���Ҫ���л�ģ��CsSerialization��֧��
	**
	****************************************************************************/
	//template<typename ArchiveT> cs_bool Deserialize(ArchiveT &archive);
};

#endif // _CORE_OBJECT_H_
