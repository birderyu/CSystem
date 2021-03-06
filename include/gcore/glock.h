/********************************************************************************
**
** gsystem: A quick, micro library of C++
**
** @file glock.h
** @brief 锁接口
** @author birderyu
** @contact https://github.com/birderyu
** @date 2015-12-31
** @version 1.0.0
**
********************************************************************************/

#ifndef _CORE_LOCK_H_
#define _CORE_LOCK_H_

#include "gtype.h"

namespace gsystem { // gsystem

/********************************************************************************
**
** @brief 锁
**
** 当多个线程执行到同一个代码时，同一时间有且只会有一个线程是可以执行的，其他线程会根据调用
** 的方法不同等待或直接退出。
**
********************************************************************************/
class GAPI GLock
{
public:
	/****************************************************************************
	**
	** @name ~GLock
	** @brief 析构函数（destructor）
	**
	****************************************************************************/
	virtual ~GLock() = 0 {}

	/****************************************************************************
	**
	** @name Lock
	** @brief 加锁
	**
	****************************************************************************/
	virtual gvoid Lock() = 0;

	/****************************************************************************
	**
	** @name Unlock
	** @brief 解锁
	**
	****************************************************************************/
	virtual gvoid Unlock() = 0;
};

} // namespace gsystem

#endif // _CORE_MUTEX_H_