#ifndef _CORE_STRINGS_H_
#define _CORE_STRINGS_H_

#include "gstring.h"

namespace gsystem {

class GStrings
{
public:
	/****************************************************************************
	**
	** @name ToString
	** @brief ��̬������ת�����ַ���
	** @template T ��������
	** @param [in] obj {const T &} ����
	** @return {GString} �ַ���
	**
	****************************************************************************/
	template <typename T>
	static GString ToString(const T &obj) GEXCEPT(false);

	static GString8 ToString8(const GString16 &str) GEXCEPT(false);
	static GString8 ToString8(const GString32 &str) GEXCEPT(false);
	static GString16 ToString16(const GString8 &str) GEXCEPT(false);
	static GString16 ToString16(const GString32 &str) GEXCEPT(false);
	static GString32 ToString32(const GString8 &str) GEXCEPT(false);
	static GString32 ToString32(const GString16 &str) GEXCEPT(false);

};

} // namespace gsystem

#endif // _CORE_STRING_H_
