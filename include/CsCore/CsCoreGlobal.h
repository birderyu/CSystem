#ifndef _CSCORE_CSCOREGLOBAL_H_
#define _CSCORE_CSCOREGLOBAL_H_

#include "CsGlobal.h"

enum CS_CORE_CLASSCODE
{
	CORE_CLASSCODE_OBJECT = 0,			// Object
	CORE_CLASSCODE_ARRAY,				// Array
	CORE_CLASSCODE_ARRAY_STACK,			// ArrayStack
	CORE_CLASSCODE_AUTO_LOCK,			// AutoLock
	CORE_CLASSCODE_BINARY_SORT_TREE,	// Binary Sort Tree
	CORE_CLASSCODE_BINARY_TREE,			// Binary Tree
	CORE_CLASSCODE_BOOLEAN,				// Boolean
	CORE_CLASSCODE_BYTE,				// Byte
	CORE_CLASSCODE_CHARACTER,			// Character

	
	CORE_CLASSCODE_INT8,			// Int8
	CORE_CLASSCODE_INT16,			// Int16
	CORE_CLASSCODE_INT32,			// Int32
	CORE_CLASSCODE_INT64,			// Int64
	CORE_CLASSCODE_FLOAT,			// Float
	CORE_CLASSCODE_DOUBLE,			// Double
	CORE_CLASSCODE_DECIMAL,			// Decimal
	CORE_CLASSCODE_STRING,			// String
	CORE_CLASSCODE_THREAD,			// Thread
	CORE_CLASSCODE_MUTEX,			// Mutex
	
	CORE_CLASSCODE_SEMAPHORE,		// Semaphore
	CORE_CLASSCODE_SOCKET_ADDRESS,		// SockAddress
	CORE_CLASSCODE_SOCKET,			// Socket
	CORE_CLASSCODE_TCPSOCKET,		// TcpSocket
	CORE_CLASSCODE_UDPSOCKET,		// UdpSocket
	CORE_CLASSCODE_VECTOR,			// Vector
	CORE_CLASSCODE_LIST,			// List
	CORE_CLASSCODE_MAP,				// Map
	CORE_CLASSCODE_TABLE,			// Table
	CORE_CLASSCODE_FILE,			// File

	CORE_CLASSCODE_DATE,			// Date

	CORE_CLASSCODE_RBTREE_NODE,		// RBTreeNode
};

#endif // _CSCORE_CSCOREGLOBAL_H_