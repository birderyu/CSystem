/****************************************************************************
**
** Supernova
**
** @file	CsGeometry.h
** @brief	�����������͵Ķ���
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0
**
****************************************************************************/

#ifndef _CORE_GEOMETRY_H_
#define _CORE_GEOMETRY_H_

#include "CsObject.h"

class CsGeometry;
class CsEnvelope;
typedef CsSharedPointer<CsGeometry> CsGeometryP;

/****************************************************************************
**
** CsGeometry.h
**
** @class		CsGeometry
** @brief		������������
** @module		CsCore
**
** �����������������м��ζ���Ļ��࣬����Ҫ��ģ�͵�˼�������һ��ӿڷ�װ��
**
****************************************************************************/
class CS_API CsGeometry 
	: public CsObject
{
public:
	enum { CLASSCODE = CORE_CLASSCODE_GEOMETRY, };

public:
	virtual ~CsGeometry() = 0;

	virtual cs_bool Valid() const;
	virtual cs_real Distance(const CsGeometry &) const;
	virtual cs_real Length() const;
	virtual cs_real Area() const;
	virtual cs_real Volume() const;
	virtual CsEnvelope Envelope() const;
	virtual cs_int GeometryType() const;
};

#endif // _CORE_GEOMETRY_H_