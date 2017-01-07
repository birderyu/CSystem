// ��
#ifndef _CORE_STREAM_H_
#define _CORE_STREAM_H_

#include "gglobal.h"

class GAPI CsStream
{
public:
	virtual ~CsStream() = 0;
	virtual gbool Valid() const = 0;

	// �Ƿ��ǳ����
	virtual gbool IsAbstract() const = 0;
	// �Ƿ��Ƕ����ƣ�����Ϊ�ı�
	virtual gbool IsBinary() const = 0;
	// �Ƿ��л���
	virtual gbool HasBuffer() const = 0;
	// �Ƿ����ļ�
	virtual gbool HasFile() const = 0;
	// �Ƿ���������
	virtual gbool IsInput() const = 0;
	// �Ƿ��������
	virtual gbool IsOutput() const = 0;

	//virtual cs_bool Seek() = 0;
	//virtual cs_void Rewind() = 0;
};

#endif // _CORE_STREAM_H_
