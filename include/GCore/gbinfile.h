#ifndef _CORE_BINARY_FILE_H_
#define _CORE_BINARY_FILE_H_

#include "gfile.h"

namespace gsystem { // gsystem
	class GBytes;
	namespace detail { // gsystem.detail
		class GBinFile_Ex;
	} // namespace gsystem.detail
} // namespace gsystem

namespace gsystem { // gsystem

/****************************************************************************
**
** @brief �������ļ���
**
** �������ļ������ڴ򿪡��������༭һ���������ļ��������ļ��ࣨGFile����һ��������
**
****************************************************************************/
class GAPI GBinFile final
	: public GFile
{
public:
	/****************************************************************************
	**
	** @name		GBinFile
	** @brief		���캯����constructor��
	** @param[in]	filename {const GString &} �ļ���
	**
	****************************************************************************/
	GBinFile(const GString &filename);

	/****************************************************************************
	**
	** @name		Read
	** @brief		��ȡ�������ļ������������һ���ֽ�����
	** @param[in]	size {gsize} ��ȡ�ĳߴ磬��λ�ֽ�
	** @param[out]	bytes {GBytes &} �ֽ�����
	** @return		{gbool} ����ȡʧ�ܣ��򷵻�false
	**
	****************************************************************************/
	gbool Read(gsize size, GBytes &bytes);

	/****************************************************************************
	**
	** @name		ReadAll
	** @brief		��ȡ�������ļ���ȫ�����ݣ����������һ���ֽ�����
	** @param[out]	bytes {GBytes &} �ֽ�����
	** @return		{gbool} ����ȡʧ�ܣ��򷵻�false
	**
	****************************************************************************/
	gbool ReadAll(GBytes &bytes);

	/****************************************************************************
	**
	** @name		Write
	** @brief		���ֽ������е�����д���ļ�
	** @param[out]	bytes {const GBytes &} �ֽ�����
	** @return		{gbool} ��д��ʧ�ܣ��򷵻�false
	** @see			GBytes
	**
	** д��ķ�ʽȡ���ڴ��ļ��ķ�ʽ��mode {OPEN_MODE}��
	**
	****************************************************************************/
	gbool Write(const GBytes &bytes);

protected:
	GBinFile(detail::GBinFile_Ex *);
};

} // namespace gsystem

#endif // _CORE_BINARY_FILE_H_