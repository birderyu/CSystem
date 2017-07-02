#ifndef _CORE_EXCEPTION_H_
#define _CORE_EXCEPTION_H_

#include "gstring.h"
#include "gsharedptr.h"
#include "gserializable.h"

namespace gsystem {
	class GException;
	typedef GSharedPtr<GException> GExceptionPtr;
}

namespace gsystem {

class GAPI GException
	: virtual public GSerializable
{
public:
	virtual ~GException() GNOEXCEPT = 0;

public:
	virtual gvoid Raise() = 0;
	const GString &ExceptionMessage() const GNOEXCEPT;
	const GString &Details() const GNOEXCEPT;
	const GString &StackTrace() const GNOEXCEPT;
	gvoid AddStackTraceInfo(const GString &methodName,
		gsize lineNumber, const GString &fileName) GNOEXCEPT;
	gvoid AddStackTraceInfo(const GString &methodName, const GString &methodParams,
		gsize lineNumber, const GString &fileName) GNOEXCEPT;
	typedef GString(*LocaleCallbackFunc)();
	static gvoid RegisterLocaleCallback(LocaleCallbackFunc func);

public:
	guint ClassCode() const GNOEXCEPT;
	GString ClassName() const GNOEXCEPT;
	gbool Serialize(GArchive &archive) const;
	gbool Deserialize(GArchive &archive);

protected:
	GException() GNOEXCEPT;

	/****************************************************************************
	**
	** @brief �����쳣����
	** @param [in] methodName {const GString &} �쳣�׳�������
	** @param [in] lineNumber {gsize} �쳣�׳��к�
	** @param [in] fileName {const GString &} �쳣�׳��ļ�
	** @param [in] whatArguments {const GStringList *} ʲô�쳣
	** @param [in] whyMessageId {const GString &} �쳣Ϊʲô��������ϢID
	** @param [in] whyArguments {const GStringList *} �쳣Ϊʲô��������ز���
	**
	****************************************************************************/
	GException(const GString &methodName, gsize lineNumber,
		const GString &fileName, const GStringList *whatArguments,
		const GString &whyMessageId, const GStringList *whyArguments) GNOEXCEPT;

	virtual GString FormatWhatMessage(const GStringList &arguments) GNOEXCEPT = 0;
	virtual GString FormatWhyMessage(const GStringList &arguments) GNOEXCEPT = 0;
	virtual GString FormatDetails() GNOEXCEPT = 0;
	virtual GString FormatStackTrace() GNOEXCEPT = 0;

protected:
	/// �����쳣�ĺ���������
	GStringList m_tMethodNames;

	/// �����쳣�ĺ�������������
	GStringList m_tMethodParams;

	/// �����쳣����������
	GStringList m_tLineNumbers;

	/// �����쳣���ļ�������
	GStringList m_tFileNames;

	/// �����쳣��ʲô�Ĳ�������
	GStringList m_tWhatArguments;

	/// ����Ϊʲô�����쳣����ϢID��ʾ��
	GString m_sWhyMessageId;

	/// ����Ϊʲô�����쳣�Ĳ�������
	GStringList m_tWhyArguments;

	/// �ֲ���Ϣ
	GString m_sMessage;

	/// �ֲ�ϸ��
	GString m_sDetails;

	/// �ֲ���ջ��Ϣ
	GString m_sStackTrace;

private:
	static LocaleCallbackFunc smLocaleCallbackFunc;

	/// \brief ��ȡĬ�ϵı��ػ�����
	/// \return Ĭ�ϵı��ػ�����
	GString GetLocale() GNOEXCEPT;
};

} // namespace gsystem

#endif // _CORE_EXCEPTION_H_
