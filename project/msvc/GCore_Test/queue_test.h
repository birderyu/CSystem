#pragma once
#include <gtest/gtest.h>
#include "garrayqueue.h"
#include "glistqueue.h"
#include "gstring.h"

TEST(ArrayQueueTest, HandleNoneZeroInput)
{
	using namespace gsystem;

	GArrayQueue<gint> queue;
	queue.EnQueue(1);
	queue.EnQueue(2);
	queue.EnQueue(3);
	queue.EnQueue(4);
	queue.EnQueue(5);
	ASSERT_EQ(5, queue.Size()) << "�����е�Ԫ�ظ���Ӧ����5����������" << queue.Size();
	ASSERT_EQ(1, queue.Head()) << "��ͷԪ��Ӧ����1����������" << queue.Head();

	gint head_value = 0;
	queue.DeQueue(&head_value);
	ASSERT_EQ(1, head_value) << "��ͷԪ��Ӧ����1����������" << head_value;
	queue.DeQueue(&head_value);
	ASSERT_EQ(2, head_value) << "��ͷԪ��Ӧ����2����������" << head_value;

	queue.EnQueue(10);
	ASSERT_EQ(4, queue.Size()) << "�����е�Ԫ�ظ���Ӧ����4����������" << queue.Size();
	queue.DeQueue(&head_value);
	ASSERT_EQ(3, head_value) << "��ͷԪ��Ӧ����3����������" << head_value;

	queue.EnQueue(11);
	queue.EnQueue(12);
	queue.EnQueue(13);

	queue.DeQueue(&head_value);
	ASSERT_EQ(4, head_value) << "��ͷԪ��Ӧ����4����������" << head_value;

	queue.Clear();
	ASSERT_EQ(0, queue.Size()) << "�����е�Ԫ�ظ���Ӧ����0����������" << queue.Size();

	// ����һ�����Ԫ��
	for (gsize i = 0; i < 1000000; i++)
	{
		queue.EnQueue(i);
	}
	ASSERT_EQ(1000000, queue.Size()) << "�����е�Ԫ�ظ���Ӧ����1000000����������" << queue.Size();
	for (gint i = 0; i < 1000000; i++)
	{
		queue.DeQueue(&head_value);
		ASSERT_EQ(i, head_value) << "��ͷԪ��Ӧ����" << i << "����������" << head_value;
	}
	ASSERT_TRUE(queue.IsEmpty()) << "����Ӧ�ñ��ÿգ������ﲻΪ��";

	queue.EnQueue(100);
	queue.EnQueue(200);
	queue.EnQueue(300);
	queue.EnQueue(400);
	queue.DeQueue();

	// ��֤��������
	GArrayQueue<gint> _queue(queue);
	ASSERT_EQ(3, _queue.Size()) << "�����е�Ԫ�ظ���Ӧ����3����������" << _queue.Size();
	ASSERT_FALSE(queue.IsEmpty()) << "�����е�Ԫ�ز�Ӧ��Ϊ��";
	_queue.DeQueue(&head_value);
	ASSERT_EQ(200, head_value) << "��ͷԪ��Ӧ����200����������" << head_value;
	_queue.DeQueue(&head_value);
	ASSERT_EQ(300, head_value) << "��ͷԪ��Ӧ����300����������" << head_value;
	_queue.DeQueue(&head_value);
	ASSERT_EQ(400, head_value) << "��ͷԪ��Ӧ����400����������" << head_value;

	// ��֤�ƶ�����
	GArrayQueue<gint> __queue(GMove(queue));
	ASSERT_TRUE(queue.IsEmpty());
	__queue.DeQueue(&head_value);
	ASSERT_EQ(200, head_value) << "��ͷԪ��Ӧ����200����������" << head_value;
	__queue.DeQueue(&head_value);
	ASSERT_EQ(300, head_value) << "��ͷԪ��Ӧ����300����������" << head_value;
	__queue.DeQueue(&head_value);
	ASSERT_EQ(400, head_value) << "��ͷԪ��Ӧ����400����������" << head_value;

	queue.EnQueue(400);
	queue.EnQueue(500);
	queue.EnQueue(600);
	queue.EnQueue(700);
	queue.DeQueue();

	// ��֤������ֵ
	GArrayQueue<gint> _queue_;
	_queue_ = queue;
	ASSERT_EQ(3, _queue_.Size()) << "�����е�Ԫ�ظ���Ӧ����3����������" << _queue.Size();
	ASSERT_FALSE(queue.IsEmpty()) << "�����е�Ԫ�ز�Ӧ��Ϊ��";
	_queue_.DeQueue(&head_value);
	ASSERT_EQ(500, head_value) << "��ͷԪ��Ӧ����500����������" << head_value;
	_queue_.DeQueue(&head_value);
	ASSERT_EQ(600, head_value) << "��ͷԪ��Ӧ����600����������" << head_value;
	_queue_.DeQueue(&head_value);
	ASSERT_EQ(700, head_value) << "��ͷԪ��Ӧ����700����������" << head_value;

	// ��֤�ƶ���ֵ
	GArrayQueue<gint> __queue__;
	__queue__ = GMove(queue);
	ASSERT_TRUE(queue.IsEmpty());
	__queue__.DeQueue(&head_value);
	ASSERT_EQ(500, head_value) << "��ͷԪ��Ӧ����500����������" << head_value;
	__queue__.DeQueue(&head_value);
	ASSERT_EQ(600, head_value) << "��ͷԪ��Ӧ����600����������" << head_value;
	__queue__.DeQueue(&head_value);
	ASSERT_EQ(700, head_value) << "��ͷԪ��Ӧ����700����������" << head_value;

	// һ�����String���͵Ķ���
	GArrayQueue<GString> queue_str;
	queue_str.EnQueue("this is queue test of gsystem test.");
	queue_str.EnQueue("abc");
	ASSERT_EQ(2, queue_str.Size()) << "�����е�Ԫ�ظ���Ӧ����2����������" << queue_str.Size();
	GString str;
	queue_str.DeQueue(&str);
	ASSERT_EQ("this is queue test of gsystem test.", str);
}

TEST(ListQueueTest, HandleNoneZeroInput)
{
	using namespace gsystem;

	GListQueue<gint> queue;
	queue.EnQueue(1);
	queue.EnQueue(2);
	queue.EnQueue(3);
	queue.EnQueue(4);
	queue.EnQueue(5);
	ASSERT_EQ(5, queue.Size()) << "�����е�Ԫ�ظ���Ӧ����5����������" << queue.Size();
	ASSERT_EQ(1, queue.Head()) << "��ͷԪ��Ӧ����1����������" << queue.Head();

	gint head_value = 0;
	queue.DeQueue(&head_value);
	ASSERT_EQ(1, head_value) << "��ͷԪ��Ӧ����1����������" << head_value;
	queue.DeQueue(&head_value);
	ASSERT_EQ(2, head_value) << "��ͷԪ��Ӧ����2����������" << head_value;

	queue.EnQueue(10);
	ASSERT_EQ(4, queue.Size()) << "�����е�Ԫ�ظ���Ӧ����4����������" << queue.Size();
	queue.DeQueue(&head_value);
	ASSERT_EQ(3, head_value) << "��ͷԪ��Ӧ����3����������" << head_value;

	queue.EnQueue(11);
	queue.EnQueue(12);
	queue.EnQueue(13);

	queue.DeQueue(&head_value);
	ASSERT_EQ(4, head_value) << "��ͷԪ��Ӧ����4����������" << head_value;

	queue.Clear();
	ASSERT_EQ(0, queue.Size()) << "�����е�Ԫ�ظ���Ӧ����0����������" << queue.Size();

	// ����һ�����Ԫ��
	for (gsize i = 0; i < 1000000; i++)
	{
		queue.EnQueue(i);
	}
	ASSERT_EQ(1000000, queue.Size()) << "�����е�Ԫ�ظ���Ӧ����1000000����������" << queue.Size();
	for (gint i = 0; i < 1000000; i++)
	{
		queue.DeQueue(&head_value);
		ASSERT_EQ(i, head_value) << "��ͷԪ��Ӧ����" << i << "����������" << head_value;
	}
	ASSERT_TRUE(queue.IsEmpty()) << "����Ӧ�ñ��ÿգ������ﲻΪ��";

	queue.EnQueue(100);
	queue.EnQueue(200);
	queue.EnQueue(300);
	queue.EnQueue(400);
	queue.DeQueue();

	// ��֤��������
	GListQueue<gint> _queue(queue);
	ASSERT_EQ(3, _queue.Size()) << "�����е�Ԫ�ظ���Ӧ����3����������" << _queue.Size();
	ASSERT_FALSE(queue.IsEmpty()) << "�����е�Ԫ�ز�Ӧ��Ϊ��";
	_queue.DeQueue(&head_value);
	ASSERT_EQ(200, head_value) << "��ͷԪ��Ӧ����200����������" << head_value;
	_queue.DeQueue(&head_value);
	ASSERT_EQ(300, head_value) << "��ͷԪ��Ӧ����300����������" << head_value;
	_queue.DeQueue(&head_value);
	ASSERT_EQ(400, head_value) << "��ͷԪ��Ӧ����400����������" << head_value;

	// ��֤�ƶ�����
	GListQueue<gint> __queue(GMove(queue));
	ASSERT_TRUE(queue.IsEmpty());
	__queue.DeQueue(&head_value);
	ASSERT_EQ(200, head_value) << "��ͷԪ��Ӧ����200����������" << head_value;
	__queue.DeQueue(&head_value);
	ASSERT_EQ(300, head_value) << "��ͷԪ��Ӧ����300����������" << head_value;
	__queue.DeQueue(&head_value);
	ASSERT_EQ(400, head_value) << "��ͷԪ��Ӧ����400����������" << head_value;

	queue.EnQueue(400);
	queue.EnQueue(500);
	queue.EnQueue(600);
	queue.EnQueue(700);
	queue.DeQueue();

	// ��֤������ֵ
	GListQueue<gint> _queue_;
	_queue_ = queue;
	ASSERT_EQ(3, _queue_.Size()) << "�����е�Ԫ�ظ���Ӧ����3����������" << _queue.Size();
	ASSERT_FALSE(queue.IsEmpty()) << "�����е�Ԫ�ز�Ӧ��Ϊ��";
	_queue_.DeQueue(&head_value);
	ASSERT_EQ(500, head_value) << "��ͷԪ��Ӧ����500����������" << head_value;
	_queue_.DeQueue(&head_value);
	ASSERT_EQ(600, head_value) << "��ͷԪ��Ӧ����600����������" << head_value;
	_queue_.DeQueue(&head_value);
	ASSERT_EQ(700, head_value) << "��ͷԪ��Ӧ����700����������" << head_value;

	// ��֤�ƶ���ֵ
	GListQueue<gint> __queue__;
	__queue__ = GMove(queue);
	ASSERT_TRUE(queue.IsEmpty());
	__queue__.DeQueue(&head_value);
	ASSERT_EQ(500, head_value) << "��ͷԪ��Ӧ����500����������" << head_value;
	__queue__.DeQueue(&head_value);
	ASSERT_EQ(600, head_value) << "��ͷԪ��Ӧ����600����������" << head_value;
	__queue__.DeQueue(&head_value);
	ASSERT_EQ(700, head_value) << "��ͷԪ��Ӧ����700����������" << head_value;

	// һ�����String���͵Ķ���
	GListQueue<GString> queue_str;
	queue_str.EnQueue("this is queue test of gsystem test.");
	queue_str.EnQueue("abc");
	ASSERT_EQ(2, queue_str.Size()) << "�����е�Ԫ�ظ���Ӧ����2����������" << queue_str.Size();
	GString str;
	queue_str.DeQueue(&str);
	ASSERT_EQ("this is queue test of gsystem test.", str);
}