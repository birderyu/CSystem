#include "SortStack.h"

int main(int argc, char *argv[])
{
	// ��������
	double dArr[7] = { 1.2, 3.9, 0.3, 7.2, 4.9, 5.5, 10.2 };

	// ����һ������
	CSortStack<double> tStack;

	// ͨ��Ԥ����ռ����Ӳ�����ٶȣ���ѡ��
	//tStack.reserve(10);

	// �������ݵķ���
	for (int i = 0; i < 7; i++)
	{
		tStack.insert(dArr[i]);
	}
	int nSize_1 = tStack.size();

	// �������ݵķ���һ��ʹ���±ֻ꣨����
	for (int i = 0; i < nSize_1; i++)
	{
		// �±�ֱ�ӷ���
		double v_1 = tStack[i];

		// �±��ȡ������
		CSortStack<double>::const_iterator _citer = tStack.at(i);
		if (_citer != NULL)
		{
			double v_2 = *_citer;
		}
	}

	// �������ݵķ���
	int id = tStack.search(1.2);
	CSortStack<double>::const_iterator cfind = tStack.cfind(1.2);

	// ɾ����β���ݵķ���
	CSortStack<double>::const_iterator cfront = tStack.pop_front();
	if (cfront != NULL)
	{
		double dfront = *cfront;
	}
	CSortStack<double>::const_iterator cback = tStack.pop_back();
	if (cback != NULL)
	{
		double dback = *cback;
	}
	
	// ɾ������λ�����ݵķ���
	tStack.remove(4.9);
	int nSize_2 = tStack.size();

	// �������ݵķ�������ʹ�õ�����
	for (CSortStack<double>::const_iterator citer = tStack.cbegin();
		citer != tStack.cend(); citer++)
	{
		double v = *citer;
	}
}