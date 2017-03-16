#ifndef _CORE_BINARY_FILE_H_
#define _CORE_BINARY_FILE_H_

#include "gfile.h"

namespace gsystem { // gsystem
	class GBytes;
	namespace detail { // gsystem.detail
		class GBinaryFile_Ex;
	} // namespace gsystem.detail
} // namespace gsystem

namespace gsystem { // gsystem

/****************************************************************************
**
** gbinaryfile.h
**
** @class		GBinaryFile
** @brief		�������ļ�
**
** GBinaryFile���ڴ򿪡��������༭һ���������ļ��������ļ���GFile��һ��������
**
** @see GFile
**
****************************************************************************/
class GAPI GBinaryFile
	: public GFile
{
public:
	/****************************************************************************
	**
	** GBinaryFile
	**
	** @name		GBinaryFile
	** @brief		���캯����constructor��
	** @param[in]	filename {const GString &} �ļ���
	**
	****************************************************************************/
	GBinaryFile(const GString &filename);

	/****************************************************************************
	**
	** GBinaryFile
	**
	** @name		Read
	** @brief		��ȡ�������ļ������������һ���ֽ�����
	** @param[in]	size {gsize} ��ȡ�ĳߴ磬��λ�ֽ�
	** @param[out]	bytes {GBytes &} �ֽ�����
	** @return		{gbool} ����ȡʧ�ܣ��򷵻�false
	** @see			GBytes
	**
	****************************************************************************/
	gbool Read(gsize size, GBytes &bytes);

	/****************************************************************************
	**
	** GBinaryFile
	**
	** @name		ReadAll
	** @brief		��ȡ�������ļ���ȫ�����ݣ����������һ���ֽ�����
	** @param[out]	bytes {GBytes &} �ֽ�����
	** @return		{gbool} ����ȡʧ�ܣ��򷵻�false
	** @see			GBytes
	**
	****************************************************************************/
	gbool ReadAll(GBytes &bytes);

	/****************************************************************************
	**
	** GBinaryFile
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
	GBinaryFile(detail::GBinaryFile_Ex *);
};

} // namespace gsystem

#endif // _CORE_BINARY_FILE_H_