/****************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file	grefcounter.h
** @brief	���ü�����
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0.0
**
****************************************************************************/

#ifndef _CORE_REFERENCE_COUNTER_H_
#define _CORE_REFERENCE_COUNTER_H_

#include "gnew.h"

namespace gsystem { // gsystem

/****************************************************************************
**
** @brief	���ü�����
**
****************************************************************************/
template <typename ClassT>
class GRefCounter 
	: public GNewT<GRefCounter<ClassT>>
{
public:
	/****************************************************************************
	**
	** @name GRefCounter
	** @brief ���캯����constructor��
	** @param[in] count {gsize} ��ʼ����һ������
	**
	** ����GObject��Ҫ��Ϊ������Դ��Ļ��࣬�����������������������ģ�virtual����
	**
	****************************************************************************/
	GRefCounter(gsize count = 1);
	GRefCounter(const GRefCounter &refCounter);
	GRefCounter(GRefCounter &&refCounter);
	~GRefCounter();

	gsize Add();
	gsize Release();
	gsize Count() const;

private:
	ClassT *m_pPointer;
};

} // namespace gsystem

#include "inline/grefcounter.inl"

#endif // _CORE_REFERENCE_COUNTER_H_