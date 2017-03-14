#pragma once

#include "gallocator.h"
#include "gconstructor.h"
#include "gstring.h"

gnova::gvoid Constructor_Test()
{
	using namespace gnova;

	// Ϊ�����������ͷ���һ���ռ�
	gint *p_int = GAllocate<gint>();

	// ����Ĭ�ϵĹ��캯��
	GConstruct<gint>(p_int);

	// �ͷ�һ�������������͵Ŀռ�
	GDeallocate<gint>(p_int);

	// Ϊ�������Ͷ������һ���ռ�
	// ע�⣺���������˿ռ䣬��δ���ù��캯��������ᴦ�ڡ�δ���塱��״̬
	GString *p_str = GAllocate<GString>();

	// �ͷ�һ���������Ͷ���Ŀռ�
	// ע�⣺�����ͷ��˿ռ䣬��δ�����������������ܻ�����ڴ�й©
	GDeallocate<GString>(p_str);

	// �����������ռ�
	gint *p_int_arr = GAllocate<gint>(10);

	// ���·����������ռ�
	p_int_arr = GReallocate<gint>(p_int_arr, 20);

	// �ͷŶ�������ռ�
	GDeallocate<gint>(p_int_arr);

	// ����ռ�
	GString *p_str_original = GAllocate<GString>();
	GString *p_str_copy = GAllocate<GString>();
	GString *p_str_move = GAllocate<GString>();

	// ���ô������Ĺ��캯��
	GConstruct<GString>(p_str_original, "abcdef123456");
	// ���ÿ������캯��
	GCopyConstruct<GString>(p_str_copy, *p_str_original);
	// �����ƶ����캯��
	GMoveConstruct<GString>(p_str_move, GMove(*p_str_original));

	// ����
	GDestruct<GString>(p_str_original);
	GDestruct<GString>(p_str_copy);
	GDestruct<GString>(p_str_move);

	// �ͷſռ�
	GDeallocate<GString>(p_str_original);
	GDeallocate<GString>(p_str_copy);
	GDeallocate<GString>(p_str_move);
}
