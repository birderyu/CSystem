/*���еĳ�����������*/
template <typename T>
class ArrayQueue
{
public:
	//���캯��
	ArrayQueue(int s) : maxsize(s), begin(0), end(0), array(NULL) {
		array = new T[maxsize];
	}
	//��������
	~ArrayQueue()
	{
		delete[]array;
	}


	T front();          //����Ԫ��
	bool pop();         //����
	bool push(T t);     //���
	bool isEmpty();     //�п�
	int size();         //���еĴ�С
private:
	int begin;      //����Ԫ��
	int end;        //��β
	T *array;       //����
	int maxsize;    //����
};

template <typename T>
T ArrayQueue<T>::front()
{
	if (begin != end)
		return array[begin];
};

template <typename T>
bool ArrayQueue<T>::pop()
{
	if (begin == end)
		return false;
	begin = (begin + 1) % maxsize;
	return true;
};

template <typename T>
bool ArrayQueue<T>::push(T t)
{
	if ((end + 1) % maxsize == begin)
		return false;
	array[end] = t;
	end = (end + 1) % maxsize;
	return true;
};

template <typename T>
bool ArrayQueue<T>::isEmpty()
{
	if (begin == end)
		return true;
	else
		return false;
};

template <typename T>
int ArrayQueue<T>::size()
{
	return (end - begin + maxsize) % maxsize;
};