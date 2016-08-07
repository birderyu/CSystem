#include <iostream>
#include <windows.h>
#include "SortStack.h"

#ifndef RAND_MAX
#	define RAND_MAX 0x7fff
#endif

//#define PRINT_TEST_DATA				// �������õ����ݴ�ӡ����
#define TEST_DATA_COUNT 1000000			// ���ڲ��Ե��������������
#define TEST_FUN_COUNT 50000			// �������������Ƴ��������ݵ�����
#define PRE_ALLOC_MEM				// Ԥ����ռ�

using namespace std;

/// ���������
double random(double start, double end)
{
	return start + (end - start)*rand() / (RAND_MAX + 1.0);
}

int testUseSortStack(double *dArr, double *dFunArr)
{
	cout << endl << "ʹ��SortStack"; // print
	cout << endl << "���Կ�ʼ��"; // print
	cout << endl << "���ڲ��Ե������������" << TEST_DATA_COUNT; // print
	cout << endl << "����" << TEST_FUN_COUNT * 3 << "���������ڲ����������Ƴ��ȷ���"; // print
	cout << endl << "��ӡ�������ݣ�"; // print
#ifdef PRINT_TEST_DATA
	cout << "��"; // print
#else
	cout << "��"; // print
#endif
	cout << endl << "Ԥ����ռ䣺"; // print
#ifdef PRE_ALLOC_MEM
	cout << "��"; // print
#else
	cout << "��"; // print
#endif
	cout << endl;
	if (TEST_DATA_COUNT < TEST_FUN_COUNT * 3)
	{
		cout << endl << "���ڲ��Է�������������" << TEST_FUN_COUNT * 2 << "��"
			<< "����С�����������(" << TEST_DATA_COUNT << ")��"
			<< "����꣬���������ɳ���" << endl << endl; // print
		system("pause");
		return -1;
	}

	int _nTime = 0;
	int _nStartTime = 0;
	int _nEndTime = 0;

	// ������������
	cout << endl << "����" << TEST_DATA_COUNT << "�������..."; // print
	_nStartTime = GetTickCount(); // time
	for (size_t i = 0; i < TEST_DATA_COUNT; i++)
	{
		dArr[i] = random(0, 100);
#ifdef PRINT_TEST_DATA
		if (i % 10 == 0)			// print
		{							// print
			cout << endl;			// print
		}							// print
		cout << dArr[i] << ", ";	// print
#endif
	}
	_nEndTime = GetTickCount(); // time
	_nTime = (_nEndTime - _nStartTime); // time
	cout << endl << "����������ɹ�������ʱ��" << _nTime << "����" << endl;

	for (int i = 0; i < TEST_FUN_COUNT; i++)
	{
		dFunArr[i] = dArr[i];
	}

	// ����һ������
	CSortStack<double> tStack;

	// ͨ��Ԥ����ռ����Ӳ�����ٶȣ���ѡ��
#ifdef PRE_ALLOC_MEM
	cout << endl << "Ԥ����ռ�..."; // print
	_nStartTime = GetTickCount(); // time
	if (!tStack.reserve(TEST_DATA_COUNT))
	{
		return -1;
	}
	_nEndTime = GetTickCount(); // time
	_nTime = (_nEndTime - _nStartTime); // time
	cout << endl << "Ԥ����ռ�ɹ�������ʱ��" << _nTime << "����" << endl; // print
#else
	cout << endl << "û��ѡ��Ԥ����ռ�" << endl; // print
#endif

	// �������ݵķ���
	cout << endl << "��������..."; // print
	_nStartTime = GetTickCount(); // time
	for (int i = 0; i < TEST_DATA_COUNT; i++)
	{
		tStack.insert(dArr[i]);
	}
	_nEndTime = GetTickCount(); // time
	_nTime = (_nEndTime - _nStartTime); // time
	cout << endl << "�������ݳɹ�������ʱ��" << _nTime << "����" << endl; // print

	// �������ݵķ���һ��ʹ���±ֻ꣨����
	int nSize = tStack.size();
	cout << endl << "�������ݵķ���һ��ʹ���±ֻ꣨����..."; // print
	_nStartTime = GetTickCount(); // time
	for (int i = 0; i < nSize; i++)
	{
		// �±�ֱ�ӷ���
		double v = tStack[i];
#ifdef PRINT_TEST_DATA
		if (i % 10 == 0)			// print
		{							// print
			cout << endl;			// print
		}							// print
		cout << v << ", ";	// print
#endif
	}
	_nEndTime = GetTickCount(); // time
	_nTime = (_nEndTime - _nStartTime); // time
	cout << endl << "�������ݽ���������ʱ��" << _nTime << "����" << endl; // print

	// �������ݵķ�������ʹ�õ�����
	cout << endl << "�������ݵķ�������ʹ�õ�������ֻ����..."; // print
	_nStartTime = GetTickCount(); // time
	int nIndex = 0;
	for (CSortStack<double>::const_iterator citer = tStack.cbegin();
		citer != tStack.cend(); citer++)
	{
		double v = *citer;
#ifdef PRINT_TEST_DATA
		if (nIndex++ % 10 == 0)			// print
		{							// print
			cout << endl;			// print
		}							// print
		cout << v << ", ";	// print
#endif
	}
	_nEndTime = GetTickCount(); // time
	_nTime = (_nEndTime - _nStartTime); // time
	cout << endl << "�������ݽ���������ʱ��" << _nTime << "����" << endl; // print

	// �������ݵķ���
	cout << endl << "����" << TEST_FUN_COUNT << "������..."; // print
	_nStartTime = GetTickCount(); // time
	for (int i = 0; i < TEST_FUN_COUNT; i++)
	{
		int id = tStack.search(dFunArr[i]);
#ifdef PRINT_TEST_DATA
		cout << endl << "���֣�" << _dTestData[i] << "��λ�ã�" << id;	// print
#endif
	}
	_nEndTime = GetTickCount(); // time
	_nTime = (_nEndTime - _nStartTime); // time
	cout << endl << "�������ݽ���������ʱ��" << _nTime << "����" << endl; // print

	// ɾ����β���ݵķ���
	cout << endl << "�Ƴ�ǰ��" << TEST_FUN_COUNT << "������..."; // print
	_nStartTime = GetTickCount(); // time
	for (int i = 0; i < TEST_FUN_COUNT; i++)
	{
		CSortStack<double>::const_iterator cfront = tStack.pop_front();
		if (cfront != NULL)
		{
			double dfront = *cfront;
#ifdef PRINT_TEST_DATA
			if (nIndex++ % 10 == 0)			// print
			{							// print
				cout << endl;			// print
			}							// print
			cout << dfront << ", ";	// print
#endif
		}
	}
	_nEndTime = GetTickCount(); // time
	_nTime = (_nEndTime - _nStartTime); // time
	cout << endl << "�����Ƴ����ݽ���������ʱ��" << _nTime << "����" << endl; // print

	cout << endl << "�Ƴ���" << TEST_FUN_COUNT << "������..."; // print
	_nStartTime = GetTickCount(); // time
	for (int i = 0; i < TEST_FUN_COUNT; i++)
	{
		CSortStack<double>::const_iterator cback = tStack.pop_back();
		if (cback != NULL)
		{
			double dback = *cback;
#ifdef PRINT_TEST_DATA
			if (nIndex++ % 10 == 0)			// print
			{							// print
				cout << endl;			// print
			}							// print
			cout << dback << ", ";	// print
#endif
		}
	}
	_nEndTime = GetTickCount(); // time
	_nTime = (_nEndTime - _nStartTime); // time
	cout << endl << "��β�������ݽ���������ʱ��" << _nTime << "����" << endl; // print


	// ɾ������λ�����ݵķ���
	int _nSuc = 0;
	int _nFal = 0;
	cout << endl << "������λ���Ƴ�" << TEST_FUN_COUNT << "������..."; // print
	for (int i = 0; i < TEST_FUN_COUNT; i++)
	{
		bool bRet = tStack.remove(dFunArr[i]);
		if (bRet) _nSuc++;
		else _nFal++;
#ifdef PRINT_TEST_DATA
		cout << endl << "�Ƴ�����" << _dTestData[i];	// print
		if (bRet) cout << "�ɹ�";
		else cout << "ʧ�ܣ����ֲ�����";
#endif
	}
	_nEndTime = GetTickCount(); // time
	_nTime = (_nEndTime - _nStartTime); // time
	cout << endl << "�Ƴ����ݽ�������" << _nSuc << "�������Ƴ��ɹ���"
		<< _nFal << "�������Ƴ�ʧ�ܣ����ֲ����ڣ���"
		<< "����ʱ��" << _nTime << "����" << endl; // print

	nSize = tStack.size();
	cout << endl << "���ջ�ʣ" << nSize << "�����ݣ�"; // print
	_nStartTime = GetTickCount(); // time
	for (int i = 0; i < nSize; i++)
	{
		// �±�ֱ�ӷ���
		CSortStack<double>::const_iterator _citer = tStack.at(i);
		if (_citer != NULL)
		{
			double v = *_citer;
#ifdef PRINT_TEST_DATA
			if (i % 10 == 0)			// print
			{							// print
				cout << endl;			// print
			}							// print
			cout << v << ", ";	// print
#endif
		}
	}
	_nEndTime = GetTickCount(); // time
	_nTime = (_nEndTime - _nStartTime); // time
	cout << endl << "�������ݽ���������ʱ��" << _nTime << "����" << endl; // print

	cout << endl;
	system("pause");
	return 0;
}

int main(int argc, char *argv[])
{
	double *dArr = new double[TEST_DATA_COUNT];
	double *dFunArr = new double[TEST_FUN_COUNT];
	int nRet = testUseSortStack(dArr, dFunArr);
	delete[] dArr;
	delete[] dFunArr;
}