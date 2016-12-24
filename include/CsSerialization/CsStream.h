// ��
#ifndef _CORE_STREAM_H_
#define _CORE_STREAM_H_

#include "CsGlobal.h"

class CS_API CsStream
{
public:
	virtual ~CsStream() = 0;
	virtual cs_bool Valid() const = 0;

	// �Ƿ��ǳ����
	virtual cs_bool IsAbstract() const = 0;
	// �Ƿ��Ƕ����ƣ�����Ϊ�ı�
	virtual cs_bool IsBinary() const = 0;
	// �Ƿ��л���
	virtual cs_bool HasBuffer() const = 0;
	// �Ƿ����ļ�
	virtual cs_bool HasFile() const = 0;
	// �Ƿ���������
	virtual cs_bool IsInput() const = 0;
	// �Ƿ��������
	virtual cs_bool IsOutput() const = 0;

	//virtual cs_bool Seek() = 0;
	//virtual cs_void Rewind() = 0;
};

#endif // _CORE_STREAM_H_
