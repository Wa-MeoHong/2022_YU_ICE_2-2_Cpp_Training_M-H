#ifndef T_ARRAY_H
#define T_ARRAY_H

#include <iostream>
#include <iomanip>

using namespace std;

// ��������, ��������
enum SortingOrder { INCREASING = 0, DECREASING = 1 };

template <typename V>						// Ŭ������ ���ø����� ������
class T_Array
{
public:
	// constructor
	T_Array();								// �⺻ ������
	T_Array(int capa, string n);			// ���ڸ� ���� ������

	// destructor
	~T_Array();

	// getter
	int size() { return num_elements; }		// num_elements ��ȯ
	string Name() { return name; }			// �̸�

	// member functions
	void reserve(int new_capacity);			// �뷮 �缳�� �Լ�
	void insert(int i, V element);			// �� ���� �Լ�
	void insertBack(V element);				// �Ǹ������� 
	void remove(int i);						// �� ���� �Լ�
	V& at(int i);							// �迭 ���� ��ȯ
	void set(int i, V& element);			// �迭 ���� 
	V& Min(int begin, int end);				// �迭�� �ּҰ�
	V& Max(int begin, int end);				// �迭�� �ִ밪 
	void fprint(ofstream& fout, int elements_per_line);	// �迭 ���
	bool isValidIndex(int index);			// �ε�����ȣ ��ȿ�� �˻�
	int sequential_Search(V& search_key);	// ���� Ž��
	int binary_Search(V& search_key);		// ���� Ž��

	// Sorting
	void shuffle();							// �迭 �ڼ���
	void selection_sort(SortingOrder order = INCREASING);	// ��������
	void quick_sort(SortingOrder order = INCREASING);		// ������

	V& operator[](int index);				// �迭�� ��ȯ

private:
	V* t_array;
	int num_elements;
	int capacity;
	string name;
};

template<typename V>
int _partition(V* array, int size, int left, int right, int PivotIndex, SortingOrder order);
template<typename V>
void _quicksort(V* array, int size, int left, int right, SortingOrder order);

/*				constructor ( ������ )
		1. default constructor ( ����Ʈ ������ )
		2. �뷮, �̸��� ���� constructor				*/
template<typename V>
inline T_Array<V>::T_Array()
{
	// t_array�� NULL, �������� 0���� �ʱ�ȭ
	t_array = NULL;
	num_elements = 0;
	capacity = 0;
	name = "";
}
template<typename V>
inline T_Array<V>::T_Array(int capa, string n)
{
	capacity = capa;						// �뷮 ����
	t_array = new V[capacity];				// �迭 �����Ҵ�
	if (t_array == NULL)
	{
		cout << "Error in allocate array !!" << endl;
		exit(-1);
	}
	num_elements = 0;
	name = n;
}

/*				destructor ( �Ҹ��� )				*/
template<typename V>
inline T_Array<V>::~T_Array()
{
	if (t_array != NULL)			// ���� �迭�� �����Ѵٸ� delete
		delete[] t_array;
}

/*					���� ���� �Լ�
		1. isValidIndex(index) : �ε�����ȣ ��ȿ�� �˻�
		2. reserve (new_capacity) : �뷮 ����
		3. insert (i, element) : ���ڸ� ����
		4. remove (i) : i��° ���ڸ� ����
		5. at(i) : �迭�� ���� ��ȯ��
		6. set(i, element) : �迭�� ���� ������
		7. Min(), Max() : �ּҰ�, �ִ밪
		8. fprint(fout, elemnets_per_line) : �迭 ���
		7. ����Ž��, ����Ž��							*/

template<typename V>
inline bool T_Array<V>::isValidIndex(int index)
{
	// �ε�����ȣ�� 0 ~ capacity - 1���̿� �ִٸ� true, �ƴϸ� false
	if (index >= 0 && index < capacity)
		return true;
	else
		return false;
}
template<typename V>
inline void T_Array<V>::reserve(int new_capacity)
{

	if (capacity >= new_capacity)
		return;						// �뷮�� ����ϹǷ� �ʿ����

	V* old_array = this->t_array;						// �õ��� �ڷḦ ����
	this->t_array = new V[new_capacity];				// ���ο� �뷮�� �迭 ����
	if (t_array == NULL)								// �迭 ���� ���н� ����
	{
		cout << "Error in allocate array !!" << endl;
		exit(-1);
	}
	cout << this->Name() << " expands capacity to " << new_capacity << endl;

	// ������ ������ ��� ����
	for (int i = 0; i < this->num_elements; i++)
		t_array[i] = old_array[i];

	delete[] old_array;			// ������ �迭�� delete
	capacity = new_capacity;	// ���ο� �뷮���� ���� 
}
template<typename V>
inline void T_Array<V>::insert(int i, V element)
{
	// ���� �뷮�� ���� �� ���� ���� ���ٸ�
	if (num_elements >= capacity)
	{
		int new_capa;
		new_capa = 2 * capacity;	// ���Ӱ� �뷮�� 2��� �ø� ��, �ٽ� ����
		reserve(new_capa);			// reserve �Լ� ȣ��
	}

	if (isValidIndex(i))			// �뷮�� �ø���(����) �ε��� ��ȣ �˻�
	{
		for (int j = this->num_elements - 1; j >= i; j--)	// i��° ������ ������ ���� ��ĭ�� �о���
			t_array[j + 1] = t_array[j];
		t_array[i] = element;			// ����ִ� i��°�� ���� ����
		num_elements++;						// num_elements�� ����
	}
}
template<typename V>
inline void T_Array<V>::insertBack(V element)
{
	// ���� �뷮�� ���� �� ���� ���� ���ٸ�
	if (num_elements >= capacity)
	{
		int new_capa;
		new_capa = 2 * capacity;	// ���Ӱ� �뷮�� 2��� �ø� ��, �ٽ� ����
		reserve(new_capa);			// reserve �Լ� ȣ��
	}

	if (isValidIndex(this->num_elements))			// �뷮�� �ø���(����) �ε��� ��ȣ �˻�
	{
		t_array[num_elements] = element;			// ����ִ� i��°�� ���� ����
		num_elements++;						// num_elements�� ����
	}
}

template<typename V>
inline void T_Array<V>::remove(int i)
{
	// ��ȿ�� ������ Ȯ�� ��
	if (isValidIndex(i))
	{
		// i��° ���� ���� ��� ��ܼ� i��°�� ���� ����
		for (int j = i + 1; j < num_elements; j++)
			t_array[j - 1] = t_array[j];
		num_elements--;			// ���� ����
	}
	// ���� �迭�� ������ 2���� 1���϶�� �뷮�� ����.
	if (num_elements < (capacity / 2))
	{
		int new_capa = capacity / 2;	// 2���� 1���� �뷮
		V* t_newAR = (V*) new V[new_capa];		// ���Ӱ� �迭 ����
		if (t_newAR == NULL)
		{
			cout << "Error in realloc new array!!" << endl;
			return;
		}

		// �迭�� ���� ���ο� �迭�� ����
		for (int i = 0; i < num_elements; i++)
			t_newAR[i] = t_array[i];

		// ������ �迭�� ����
		delete[] t_array;
		t_array = t_newAR;
		capacity = new_capa;
	}
}
template<typename V>
inline V& T_Array<V>::at(int i)
{
	if (isValidIndex(i))
		return t_array[i];			// �ε��� ��ȣ�� ��ȿ�ϸ� �迭�� ���� ��ȯ
	else
		return 0;
}
template<typename V>
inline void T_Array<V>::set(int i, V& element)
{
	if (isValidIndex(i))
	{
		t_array[i] = element;		// �ε��� ��ȣ�� ��ȿ�ϸ� �迭�� ���� ������
	}
	else
		return 0;
}
template<typename V>
inline V& T_Array<V>::Min(int begin, int end)
{
	V min_value;					// �ּҰ� 
	int index_min;					// �ּҰ� �ε��� ��ȣ

	// �ʱⰪ ����
	min_value = t_array[begin];	index_min = begin;
	for (int i = begin + 1; i < end; i++)
	{
		// ���� min_value���� t_array[i]�� ������
		if (t_array[i] < min_value)
		{
			min_value = t_array[i];		// �ּҰ��� ���Ӱ� ����
			index_min = i;				// �ε�����ȣ�� ����
		}
	}

	return t_array[index_min];			// �ּҰ� ��ȯ
}
template<typename V>
inline V& T_Array<V>::Max(int begin, int end)
{
	V max_value;					// �ִ밪 
	int index_max;					// �ִ밪 �ε��� ��ȣ

	// �ʱⰪ ����
	max_value = t_array[begin];	index_max = begin;
	for (int i = begin + 1; i < end; i++)
	{
		// ���� max_value���� t_array[i]�� ũ��
		if (t_array[i] > max_value)
		{
			max_value = t_array[i];		// �ִ밪�� ���Ӱ� ����
			index_max = i;				// �ε�����ȣ�� ����
		}
	}

	return t_array[index_max];			// �ִ밪 ��ȯ
}
template<typename V>
inline void T_Array<V>::fprint(ofstream& fout, int elements_per_line)
{
	int count = 0;
	// ��� 
	while (count < num_elements)
	{
		for (int i = 0; i < elements_per_line; i++)
		{
			// ��ü ���, ���ٿ� �������� ����ϱ� ������ endl�� ���� ����
			fout << t_array[count] << " ";
			count++;
			// ����, ������ ����� �� �������� endl;�� ����
			if (count % elements_per_line == 0)
				fout << endl;
		}
	}
	fout << endl;
}
template<typename V>
inline int T_Array<V>::sequential_Search(V& search_key)		// ����Ž��
{
	int index;
	// �ϳ��ϳ� �� ���캽
	for (int index = 0; index < num_elements; index++)
	{
		if (t_array[index] == search_key)		// ���� �Ȱ������� ã�� �ȴٸ� index�� ��ȯ
			return index;
	}
	return -1;			// ������ -1 ��ȯ
}
template<typename V>
inline int T_Array<V>::binary_Search(V& search_key)
{
	int low, mid, high;
	int loop = 1;

	// �ʱⰪ ���� (low = 0, high = num_elements - 1)
	low = 0; high = num_elements - 1;

	while (low <= high)
	{
		// mid �� ���� 
		mid = (low + high) / 2;
		// ���� search_key�� mid���� �۴ٸ�, high�� ����
		if (t_array[mid] > search_key)
			high = mid - 1;
		// ���� search_key�� mid���� ũ�ٸ�, low�� ����
		else if (t_array[mid] < search_key)
			low = mid + 1;
		else
			return mid;			// ���ٸ� mid ��ȯ
		loop++;
	}

	return -1;
}

/*							���� ���� �Լ�
		1. shuffle() : �迭 ���� �Լ�
		2. selection_sort(order) : ����/���������� ���� ��������
		3. quick_sort(order) : ����/������������ ������
		4. _quicksort(array, size, left, right, order) : ������ ���Լ�
		5. _partition(array, size, left, right, PivotIndex, order)
			: �迭 �߰����� �������� ���ǿ� �°� �з�			*/
template<typename V>
inline void T_Array<V>::shuffle()
{
	srand((unsigned int)time(NULL));		// �õ� ����
	int index1, index2;						// �ε��� ��ȣ 1, 2
	V temp;									// �Űܴٴ� ���� temp

	for (int i = 0; i < num_elements; i++)
	{
		// �ε���1 , �ε���2 ����
		index1 = (((unsigned int)rand() << 15) | rand()) % num_elements;
		index2 = (((unsigned int)rand() << 15) | rand()) % num_elements;

		// swaping
		temp = t_array[index1];
		t_array[index1] = t_array[index2];
		t_array[index2] = temp;
	}
}
template<typename V>
inline void T_Array<V>::selection_sort(SortingOrder order)
{
	int In_Min, In_Max;
	V minValue, maxValue;

	for (int i = 0; i < num_elements - 1; i++)
	{
		// �������� ����
		if (order == INCREASING)
		{
			// Min �κ� �ʱⰪ ����
			In_Min = i;	minValue = t_array[i];

			for (int j = i + 1; j < num_elements; j++)
			{
				// ���� ���� �� ã��
				if (t_array[j] < minValue)	// ���� t_array[i]�� minValue���� �۴ٸ�
				{
					minValue = t_array[j];	// �ּҰ� ����
					In_Min = j;
				}
			}
			// Swaping
			t_array[In_Min] = t_array[i];
			t_array[i] = minValue;
		}

		// �������� ����
		else
		{
			// Min �κ� �ʱⰪ ����
			In_Max = i;	maxValue = t_array[i];

			for (int j = i + 1; j < num_elements; j++)
			{
				// ���� ū �� ã��
				if (t_array[j] > maxValue)
				{
					// ���� t_array[i]�� maxValue���� �� ũ�ٸ� ����
					maxValue = t_array[j];
					In_Max = j;
				}
			}
			// Swaping
			t_array[In_Max] = t_array[i];
			t_array[i] = maxValue;
		}
	}

}
template<typename V>
inline void T_Array<V>::quick_sort(SortingOrder order)
{
	//�ʱ��Լ� �θ�
	_quicksort(t_array, size(), 0, size() - 1, order);
}
template<typename V>
void _quicksort(V* array, int size, int left, int right, SortingOrder order)
{
	int P_I, newPI;

	if (left >= right)							// ���� left�� right���� ũ�ų� ���ٸ� newPI��ȯ ����, ���� left�� 1Ȥ�� 0�϶��̴�..
		return;

	else if (left < right)
	{
		P_I = (left + right) / 2;				// �߰���, ���� Ȧ���ΰ�� ���������� ��������ġ�� ����
	}

	newPI = _partition(array, size, left, right, P_I, order);


	// �̷��� ����, ������ ������� �������� �� ū����
	if (left < (newPI - 1))									// ���� newPI�������� ���ʺκ�
	{
		_quicksort(array, size, left, newPI - 1, order);
		// �ٽ� newPI�� �����ϸ鼭 ũ�������� �����ش�.
	}
	if ((newPI + 1) < right)								// ����, ������ quickSort�� ������, newPI���� ������ �κ�
	{
		_quicksort(array, size, newPI + 1, right, order);
		// ���������� newPI����� ũ������� �������ش�.
	}
}
template<typename V>
int _partition(V* array, int size, int left, int right, int PivotIndex, SortingOrder order)
{
	int newPI;
	V PivotValue, temp;							// PivotValue = �ٲٴ� ����

	PivotValue = array[PivotIndex];
	array[PivotIndex] = array[right];
	array[right] = PivotValue;
	// �� ó�� PivotIndex�� �ִ� ���� �� ������(Ȥ�� P_I-1��ġ�� �ִ� ��)�� �ٲ۴�

	newPI = left;						// ���� ���ο� �ǹ���ġ�� �������ִµ� �ʱⰪ�� �� ����(Ȥ�� P_I + 1��ġ)���� ����
	for (int i = left; i <= right - 1; i++)
		// �ǵڷ� ���Ե� PivotValue�� ���� ������ �迭���� ������ ��´�.
	{
		// ��������
		if (order == INCREASING)
		{
			if (array[i] <= PivotValue)							//���� �ǵڷ� �� PivotValue���� ���� �۴ٸ�
			{
				temp = array[i];
				array[i] = array[newPI];
				array[newPI] = temp;							// ����(i)��ġ�� �ִ� ���� newPI�� �ִ� ������ �ٲ��ش�.
				newPI += 1;
			}
		}
		// ��������
		else
		{
			if (array[i] > PivotValue)							//���� �ǵڷ� �� PivotValue���� ���� �۴ٸ�
			{
				temp = array[i];
				array[i] = array[newPI];
				array[newPI] = temp;							// ����(i)��ġ�� �ִ� ���� newPI�� �ִ� ������ �ٲ��ش�.
				newPI += 1;
			}
		}

	}
	// ��������� ó�� PivotValue���� �������� ������ PivotValue���� ���� ������ �迭, �������� PivotValue���� ū ������ �迭�� �����Ǿ���.
	PivotValue = array[right];
	array[right] = array[newPI];
	array[newPI] = PivotValue;

	return newPI;											// newPI ��ȯ
}

// operator overloading []
template<typename V>
inline V& T_Array<V>::operator[](int index)
{
	// �ε��� ��ȣ�� ��ȿ�ϸ� �� ��ȯ
	if (isValidIndex(index))
		return t_array[index];
}

#endif // !T_ARRAY_H