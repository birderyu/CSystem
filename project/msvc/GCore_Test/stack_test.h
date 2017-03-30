#pragma once
#include <gtest/gtest.h>
#include "garraystack.h"
#include "gliststack.h"
#include "gstring.h"

TEST(ArrayStackTest, HandleNoneZeroInput)
{
	using namespace gsystem;

	GArrayStack<gint> stack;
	stack.Push(1);
	stack.Push(2);
	stack.Push(3);
	stack.Push(4);
	stack.Push(5);
	ASSERT_EQ(5, stack.Size()) << "ջ�е�Ԫ�ظ���Ӧ����5����������" << stack.Size();
	ASSERT_EQ(5, stack.Top()) << "ջ��Ԫ��Ӧ����5����������" << stack.Top();

	gint top_value = 0;
	stack.Pop(&top_value);
	ASSERT_EQ(5, top_value) << "ջ��Ԫ��Ӧ����5����������" << top_value;
	stack.Pop(&top_value);
	ASSERT_EQ(4, top_value) << "ջ��Ԫ��Ӧ����4����������" << top_value;

	stack.Push(10);
	ASSERT_EQ(4, stack.Size()) << "ջ�е�Ԫ�ظ���Ӧ����4����������" << stack.Size();
	stack.Pop(&top_value);
	ASSERT_EQ(10, top_value) << "ջ��Ԫ��Ӧ����10����������" << top_value;
	
	stack.Pop(&top_value);
	ASSERT_EQ(3, top_value) << "ջ��Ԫ��Ӧ����3����������" << top_value;
	
	stack.Clear();
	ASSERT_EQ(0, stack.Size()) << "ջ�е�Ԫ�ظ���Ӧ����0����������" << stack.Size();

	// ����һ�����Ԫ��
	for (gsize i = 0; i < 1000000; i++)
	{
		stack.Push(i);
	}
	ASSERT_EQ(1000000, stack.Size()) << "ջ�е�Ԫ�ظ���Ӧ����1000000����������" << stack.Size();
	for (gint i = 1000000 - 1; i >= 0; i--)
	{
		stack.Pop(&top_value);
		ASSERT_EQ(i, top_value) << "ջ��Ԫ��Ӧ����" << i << "����������" << top_value;
	}
	ASSERT_TRUE(stack.IsEmpty()) << "ջӦ�ñ��ÿգ������ﲻΪ��";

	stack.Push(100);
	stack.Push(200);
	stack.Push(300);
	stack.Push(400);
	stack.Pop();

	// ��֤��������
	GArrayStack<gint> _stack(stack);
	ASSERT_EQ(3, _stack.Size()) << "ջ�е�Ԫ�ظ���Ӧ����3����������" << _stack.Size();
	ASSERT_FALSE(stack.IsEmpty()) << "ջ�е�Ԫ�ز�Ӧ��Ϊ��";
	_stack.Pop(&top_value);
	ASSERT_EQ(300, top_value) << "ջ��Ԫ��Ӧ����300����������" << top_value;
	_stack.Pop(&top_value);
	ASSERT_EQ(200, top_value) << "ջ��Ԫ��Ӧ����200����������" << top_value;
	_stack.Pop(&top_value);
	ASSERT_EQ(100, top_value) << "ջ��Ԫ��Ӧ����100����������" << top_value;

	// ��֤�ƶ�����
	GArrayStack<gint> __stack(GMove(stack));
	ASSERT_TRUE(stack.IsEmpty());
	__stack.Pop(&top_value);
	ASSERT_EQ(300, top_value) << "ջ��Ԫ��Ӧ����300����������" << top_value;
	__stack.Pop(&top_value);
	ASSERT_EQ(200, top_value) << "ջ��Ԫ��Ӧ����200����������" << top_value;
	__stack.Pop(&top_value);
	ASSERT_EQ(100, top_value) << "ջ��Ԫ��Ӧ����100����������" << top_value;

	stack.Push(400);
	stack.Push(500);
	stack.Push(600);
	stack.Push(700);
	stack.Pop();

	// ��֤������ֵ
	GArrayStack<gint> _stack_;
	_stack_ = stack;
	ASSERT_EQ(3, _stack_.Size()) << "ջ�е�Ԫ�ظ���Ӧ����3����������" << _stack.Size();
	ASSERT_FALSE(stack.IsEmpty()) << "ջ�е�Ԫ�ز�Ӧ��Ϊ��";
	_stack_.Pop(&top_value);
	ASSERT_EQ(600, top_value) << "ջ��Ԫ��Ӧ����600����������" << top_value;
	_stack_.Pop(&top_value);
	ASSERT_EQ(500, top_value) << "ջ��Ԫ��Ӧ����500����������" << top_value;
	_stack_.Pop(&top_value);
	ASSERT_EQ(400, top_value) << "ջ��Ԫ��Ӧ����400����������" << top_value;

	// ��֤�ƶ���ֵ
	GArrayStack<gint> __stack__;
	__stack__ = GMove(stack);
	ASSERT_TRUE(stack.IsEmpty());
	__stack__.Pop(&top_value);
	ASSERT_EQ(600, top_value) << "ջ��Ԫ��Ӧ����600����������" << top_value;
	__stack__.Pop(&top_value);
	ASSERT_EQ(500, top_value) << "ջ��Ԫ��Ӧ����500����������" << top_value;
	__stack__.Pop(&top_value);
	ASSERT_EQ(400, top_value) << "ջ��Ԫ��Ӧ����400����������" << top_value;

	// һ�����String���͵�ջ
	GArrayStack<GString> stack_str;
	stack_str.Push("abc");
	stack_str.Push("this is stack test of gsystem test.");
	ASSERT_EQ(2, stack_str.Size()) << "ջ�е�Ԫ�ظ���Ӧ����2����������" << stack_str.Size();
	GString str;
	stack_str.Pop(&str);
	ASSERT_EQ("this is stack test of gsystem test.", str);
}

TEST(ListStackTest, HandleNoneZeroInput)
{
	using namespace gsystem;

	GListStack<gint> stack;
	stack.Push(1);
	stack.Push(2);
	stack.Push(3);
	stack.Push(4);
	stack.Push(5);
	ASSERT_EQ(5, stack.Size()) << "ջ�е�Ԫ�ظ���Ӧ����5����������" << stack.Size();
	ASSERT_EQ(5, stack.Top()) << "ջ��Ԫ��Ӧ����5����������" << stack.Top();

	gint top_value = 0;
	stack.Pop(&top_value);
	ASSERT_EQ(5, top_value) << "ջ��Ԫ��Ӧ����5����������" << top_value;
	stack.Pop(&top_value);
	ASSERT_EQ(4, top_value) << "ջ��Ԫ��Ӧ����4����������" << top_value;

	stack.Push(10);
	ASSERT_EQ(4, stack.Size()) << "ջ�е�Ԫ�ظ���Ӧ����4����������" << stack.Size();
	stack.Pop(&top_value);
	ASSERT_EQ(10, top_value) << "ջ��Ԫ��Ӧ����10����������" << top_value;

	stack.Pop(&top_value);
	ASSERT_EQ(3, top_value) << "ջ��Ԫ��Ӧ����3����������" << top_value;

	stack.Clear();
	ASSERT_EQ(0, stack.Size()) << "ջ�е�Ԫ�ظ���Ӧ����0����������" << stack.Size();

	// ����һ�����Ԫ��
	for (gsize i = 0; i < 1000000; i++)
	{
		stack.Push(i);
	}
	ASSERT_EQ(1000000, stack.Size()) << "ջ�е�Ԫ�ظ���Ӧ����1000000����������" << stack.Size();
	for (gint i = 1000000 - 1; i >= 0; i--)
	{
		stack.Pop(&top_value);
		ASSERT_EQ(i, top_value) << "ջ��Ԫ��Ӧ����" << i << "����������" << top_value;
	}
	ASSERT_TRUE(stack.IsEmpty()) << "ջӦ�ñ��ÿգ������ﲻΪ��";

	stack.Push(100);
	stack.Push(200);
	stack.Push(300);
	stack.Push(400);
	stack.Pop();

	// ��֤��������
	GListStack<gint> _stack(stack);
	ASSERT_EQ(3, _stack.Size()) << "ջ�е�Ԫ�ظ���Ӧ����3����������" << _stack.Size();
	ASSERT_FALSE(stack.IsEmpty()) << "ջ�е�Ԫ�ز�Ӧ��Ϊ��";
	_stack.Pop(&top_value);
	ASSERT_EQ(300, top_value) << "ջ��Ԫ��Ӧ����300����������" << top_value;
	_stack.Pop(&top_value);
	ASSERT_EQ(200, top_value) << "ջ��Ԫ��Ӧ����200����������" << top_value;
	_stack.Pop(&top_value);
	ASSERT_EQ(100, top_value) << "ջ��Ԫ��Ӧ����100����������" << top_value;

	// ��֤�ƶ�����
	GListStack<gint> __stack(GMove(stack));
	ASSERT_TRUE(stack.IsEmpty());
	__stack.Pop(&top_value);
	ASSERT_EQ(300, top_value) << "ջ��Ԫ��Ӧ����300����������" << top_value;
	__stack.Pop(&top_value);
	ASSERT_EQ(200, top_value) << "ջ��Ԫ��Ӧ����200����������" << top_value;
	__stack.Pop(&top_value);
	ASSERT_EQ(100, top_value) << "ջ��Ԫ��Ӧ����100����������" << top_value;

	stack.Push(400);
	stack.Push(500);
	stack.Push(600);
	stack.Push(700);
	stack.Pop();

	// ��֤������ֵ
	GListStack<gint> _stack_;
	_stack_ = stack;
	ASSERT_EQ(3, _stack_.Size()) << "ջ�е�Ԫ�ظ���Ӧ����3����������" << _stack.Size();
	ASSERT_FALSE(stack.IsEmpty()) << "ջ�е�Ԫ�ز�Ӧ��Ϊ��";
	_stack_.Pop(&top_value);
	ASSERT_EQ(600, top_value) << "ջ��Ԫ��Ӧ����600����������" << top_value;
	_stack_.Pop(&top_value);
	ASSERT_EQ(500, top_value) << "ջ��Ԫ��Ӧ����500����������" << top_value;
	_stack_.Pop(&top_value);
	ASSERT_EQ(400, top_value) << "ջ��Ԫ��Ӧ����400����������" << top_value;

	// ��֤�ƶ���ֵ
	GListStack<gint> __stack__;
	__stack__ = GMove(stack);
	ASSERT_TRUE(stack.IsEmpty());
	__stack__.Pop(&top_value);
	ASSERT_EQ(600, top_value) << "ջ��Ԫ��Ӧ����600����������" << top_value;
	__stack__.Pop(&top_value);
	ASSERT_EQ(500, top_value) << "ջ��Ԫ��Ӧ����500����������" << top_value;
	__stack__.Pop(&top_value);
	ASSERT_EQ(400, top_value) << "ջ��Ԫ��Ӧ����400����������" << top_value;

	// һ�����String���͵�ջ
	GListStack<GString> stack_str;
	stack_str.Push("abc");
	stack_str.Push("this is stack test of gsystem test.");
	ASSERT_EQ(2, stack_str.Size()) << "ջ�е�Ԫ�ظ���Ӧ����2����������" << stack_str.Size();
	GString str;
	stack_str.Pop(&str);
	ASSERT_EQ("this is stack test of gsystem test.", str);
}