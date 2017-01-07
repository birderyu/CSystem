#ifndef _CORE_STRING_POOL_EX_H_
#define _CORE_STRING_POOL_EX_H_

#include "CsGlobal_Ex.h"

class CsStringPool_Ex :public GNewT<CsStringPool_Ex>
{
public:
	struct CsAddress_Ex
	{
		gsize h;
		gsize l;
	};

	class CsFixedStringPool_Ex
	{
	public:
		CsFixedStringPool_Ex(gsize size);
		~CsFixedStringPool_Ex();

		CsAddress_Ex Add(const gchar *pInChar);
		void DeleteAt(const CsAddress_Ex &addr);

		/// �滻�ַ���
		/// ������������滻ΪpInChar�еģ�Լ��ͬAddObj
		void Modify(const CsAddress_Ex &addr, const gchar *pInChar);

		/// ��ȡ�ַ�������
		/// ���������ȱ�����ڵ����ַ����ĳ��ȣ�1	
		/// @param[out] pOutChar ���������
		void GetAt(const CsAddress_Ex &addr, gchar *pOutChar);

		/// ��ȡָ����ַ�ַ����Ĵ洢����ַ
		/// @return ָ���ַ����洢����ָ��
		gcstring GetAt(const CsAddress_Ex &addr);

	public:
		/// ���ô洢���������ȣ���λΪ�����ַ����ĳ����ټ���1
		void SetStep(gsize Step) { m_Step = Step; }

		/// ���ö��������������������󣬽����ȵ��ñ����������������
		/// @param[in] NewCapacity �����洢�������ɵ��ַ�������
		gbool SetSize(gsize NewCapacity);

		/// ��չ���������趨��������չ����
		gbool ExtendSize();

		/// �����洢(���貽��)
		void Pack();

	protected:
		inline gchar * GetCellAddress(gsize idx);

	protected:
		gsize m_Capacity; /// �洢�ռ�����ɵ�����ַ�������
		gsize m_Size; /// �洢�ռ��Ѵ��ڵ��ַ�������

		gsize m_WritePos; /// дָ��

		gsize m_StrLen; ///
		gsize m_Step;

		gchar * m_Region;
	};
};


#endif // _CORE_STRING_POOL_EX_H_