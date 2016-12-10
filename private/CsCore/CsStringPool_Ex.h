#ifndef _CORE_STRING_POOL_EX_H_
#define _CORE_STRING_POOL_EX_H_

#include "CsGlobal_Ex.h"

class CsStringPool_Ex :public CsNewT<CsStringPool_Ex>
{
public:
	struct CsAddress_Ex
	{
		cs_size_t h;
		cs_size_t l;
	};

	class CsFixedStringPool_Ex
	{
	public:
		CsFixedStringPool_Ex(cs_size_t size);
		~CsFixedStringPool_Ex();

		CsAddress_Ex Add(const cs_char *pInChar);
		void DeleteAt(const CsAddress_Ex &addr);

		/// �滻�ַ���
		/// ������������滻ΪpInChar�еģ�Լ��ͬAddObj
		void Modify(const CsAddress_Ex &addr, const cs_char *pInChar);

		/// ��ȡ�ַ�������
		/// ���������ȱ�����ڵ����ַ����ĳ��ȣ�1	
		/// @param[out] pOutChar ���������
		void GetAt(const CsAddress_Ex &addr, cs_char *pOutChar);

		/// ��ȡָ����ַ�ַ����Ĵ洢����ַ
		/// @return ָ���ַ����洢����ָ��
		cs_cstring GetAt(const CsAddress_Ex &addr);

	public:
		/// ���ô洢���������ȣ���λΪ�����ַ����ĳ����ټ���1
		void SetStep(cs_size_t Step) { m_Step = Step; }

		/// ���ö��������������������󣬽����ȵ��ñ����������������
		/// @param[in] NewCapacity �����洢�������ɵ��ַ�������
		cs_bool SetSize(cs_size_t NewCapacity);

		/// ��չ���������趨��������չ����
		cs_bool ExtendSize();

		/// �����洢(���貽��)
		void Pack();

	protected:
		inline cs_char * GetCellAddress(cs_size_t idx);

	protected:
		cs_size_t m_Capacity; /// �洢�ռ�����ɵ�����ַ�������
		cs_size_t m_Size; /// �洢�ռ��Ѵ��ڵ��ַ�������

		cs_size_t m_WritePos; /// дָ��

		cs_size_t m_StrLen; ///
		cs_size_t m_Step;

		cs_char * m_Region;
	};
};


#endif // _CORE_STRING_POOL_EX_H_