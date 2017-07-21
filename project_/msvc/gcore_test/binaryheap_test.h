#pragma once
#include <gtest/gtest.h>
#include <windows.h>
#include "gbinheap.h"
#include "gdynamicarray.h"

/// ���������
gsystem::gint random(gsystem::gint start, gsystem::gint end)
{
	return start + (end - start)*rand() / 0x7fff;
}

gsystem::gvoid testBinaryHeap()
{
	using namespace gsystem;

	// ����һ�������������Χ������������
	gsize arr_size = random(10000, 30000);
	gint a = random(0, 30000);
	gint b = random(0, 30000);
	gint max_value = a > b ? a : b;
	gint min_value = a < b ? a : b;

	std::cout
		<< "����"
		<< arr_size
		<< "�������"
		<< "������СֵΪ��"
		<< min_value
		<< "����СֵΪ��"
		<< max_value
		<< std::endl;
	GDynamicArray<gint> arr(arr_size);

	std::cout << "���ڹ��������..." << std::endl;
	for (gsize i = 0; i < arr_size; i++)
	{
		arr[i] = random(min_value, max_value);
	}
	std::cout << "����������ɹ���" << std::endl;

	// ����һ����С�Ѻ�����
	GMinHeap<gint> minHeap;
	GMaxHeap<gint> maxHeap;
	minHeap.Append(arr);
	maxHeap.Append(arr);

	// ��������������е�Ԫ���Ƿ�һһ��Ӧ
	ASSERT_EQ(minHeap.Size(), arr_size) << "��С�ѵ�����Ӧ�ú�����Ԫ�ر���һ�¡�";
	ASSERT_EQ(maxHeap.Size(), arr_size) << "���ѵ�����Ӧ�ú�����Ԫ�ر���һ�¡�";

	// ������ѵ������Ƿ���������Ҫ��
	gint last_one = min_value - 1;
	gint this_one = min_value;
	for (gsize i = 0; i < arr_size; i++)
	{
		minHeap.Pop(&this_one);
		ASSERT_LE(last_one, this_one)
			<< "��С�����������"
			<< i - 1
			<< "��Ԫ��Ϊ"
			<< last_one
			<< "����"
			<< i
			<< "��Ԫ��Ϊ"
			<< this_one;
		last_one = this_one;
	}

	last_one = max_value + 1;
	this_one = max_value;
	for (gsize i = 0; i < 1000; i++)
	{
		maxHeap.Pop(&this_one);
		ASSERT_GE(last_one, this_one)
			<< "�������������"
			<< i - 1
			<< "��Ԫ��Ϊ"
			<< last_one
			<< "����"
			<< i
			<< "��Ԫ��Ϊ"
			<< this_one;
		last_one = this_one;
	}
}

TEST(BinaryHeapTest, HandleNoneZeroInput)
{
	using namespace gsystem;

	// ����10���������
	std::cout << "����10���������" << std::endl;
	for (gsize i = 0; i < 10; i++)
	{
		std::cout << "��" << i + 1 << "�β��ԣ�" << std::endl;
		testBinaryHeap();
		std::cout << "��" << i + 1 << "�β���ͨ����" << std::endl;
	}
}