#ifndef _CORE_EXCEPTION_H_
#define _CORE_EXCEPTION_H_

#include "gserializable.h"

namespace gsystem {
	class GString;
}

namespace gsystem {

class GAPI GException
	: virtual public GSerializable
{
public:
	virtual ~GException() = 0;

public:
	GString ExceptionMessage() const;
	GString Details() const;
	GString StackTrace() const;

protected:
	/// \brief �����쳣����
	/// \param [in] methodName �쳣�׳�������
	/// \param [in] lineNumber �쳣�׳��к�
	/// \param [in] fileName �쳣�׳��ļ�
	/// \param [in] whatArguments ʲô�쳣
	/// \param [in] whyMessageId �쳣Ϊʲô��������ϢID
	/// \param [in] whyArguments �쳣Ϊʲô��������ز���
	GException(const GString &methodName, gsize lineNumber,
		const GString &fileName, WStringArray* whatArguments,
		CREFWSTRING whyMessageId, WStringArray* whyArguments) GNOEXCEPT;
};

} // namespace gsystem

#endif // _CORE_EXCEPTION_H_
