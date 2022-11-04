#ifndef TA_ENTRY_H
#define TA_ENTRY_H

#include <iostream>
#include <iomanip>
#include <string>
#include "T_Entry.h"

using namespace std;

// ���� ���� ( ��������, �������� )
enum SortDirection { INCREASING, DECREASING };

template<typename K, typename V>
class TA_Entry
{
public:
	// constructor
	TA_Entry(int n, string nm);

	// destructor
	~TA_Entry();

	// setter
	void reserve(int new_capacity);					// �� ū �迭�� ����
	void insert(int i, T_Entry<K, V>& element);		// ���� �����͸� �������
	void remove(int i);								// ������ ����
	void set(int i, T_Entry<K, V>& element);		// �ȿ��ٰ� ������ ����

	// getter
	string Name() { return name; }					// name ��ȯ
	int Size() { return num_elements; }				// ���� �� ����� ���� ��ȯ
	bool empty() { return num_elements == 0; }		// �� ��Ұ� ����ִ��� Ȯ��
	T_Entry<K, V>& at(int i);						// i��° �ִ� ������ ��ȯ (pointing)
	T_Entry<K, V> Min(int begin, int end);			// �迭�� Min�� ��ȯ
	T_Entry<K, V> Max(int begin, int end);			// �迭�� Max�� ��ȯ

	// member functions
	void shuffle();									// Shuffling 
	int sequential_search(T_Entry<K, V> search_key);	// ���� Ž��
	int binary_search(T_Entry<K, V> search_key);		// ���� Ž��
	void selection_sort(SortDirection sd);				// ��������
	void quick_sort(SortDirection sd);					// �� ����
	void fprint(ostream ostr, int elements_per_line);	// ����Լ� 1
	void fprintSample(ostream ostr, int elements_per_line, int num_sample_lines);	// ����Լ� 2
	bool isValidIndex(int i);
	// operator overloading ( �迭������ [] )
	T_Entry<K, V>& operator[] (int index) { return t_GA[index]; }			// �迭������ []
	

protected:
	T_Entry<K, V>* t_GA;		// T_Entry �迭
	int num_elements;			// �迭�� ����� ����
	int capacity;				// �迭�� �뷮
	string name;				// �迭�� �̸�

};

template<typename K, typename V>
inline void _quick_sort(T_Entry<K, V>* Array, int Size, int left, int right, SortDirection sd);
// ������ �� �Լ�
template<typename K, typename V>
inline void _partition(T_Entry<K, V>* Array, int Size, int left, int right, int PivotIndex, SortDirection sd);
// ��Ƽ�� ������ �Լ� 

/*				constructor ( ������ )
		1. n, nm�� �μ��� �޴� constructor		*/
template<typename K, typename V>
inline TA_Entry<K, V>::TA_Entry(int n, string nm)
	:  capacity(n), name(nm)
{
	num_elements = 0;
	t_GA = new T_Entry<K, V>[capacity];
}

/*			destructor ( �Ҹ��� )			*/
template<typename K, typename V>
inline TA_Entry<K, V>::~TA_Entry()
{
	if (t_GA != NULL)
		delete t_GA;					// �����Ҵ��� t_GA�� �Ҵ� ����
}		

/*				getter, setter ( ��� �Լ� ��, getter, setter )	
		1. reverse(new_capacity) ( ���ο� �뷮�� �迭�� ���Ҵ� ) 
		2. insert(i, element) ( ���ο� ���Ҹ� i��°�� ���� )
		3. remove(i)	( i��° ���Ҹ� ���� )
		4. set(i, element) ( i��° ���Ҹ� element������ ���� )
		5. at(i)		( i��° ���Ҹ� ��ȯ�� )			*/
template<typename K, typename V>
inline void TA_Entry<K, V>::reserve(int new_capacity)		// ���ο� �뷮�� �迭�� ���Ҵ� �ϴ� �Լ�
{
	if (this->Size() < this->capacity)
		return;					// ���� �뷮�� ����ϹǷ� �� �ʿ䰡 ����
	
	T_Entry* oldArray = this->t_GA;			// ���ο� �迭�� ����� ���� ������ �迭�� �ű�
	this->t_GA = new T_Entry<K, V>[new_capacity];		// ���ο� �迭 �����Ҵ�
	for (int i = 0; i < this->Size(); i++)				// ���ο� �迭�� ������ ���� �ű� 
	{
		this->t_GA[i] = oldArray[i];			// ����
	}
	capacity = new_capacity;			// ���ο� �뷮 ����
	delete oldArray;
}
template<typename K, typename V>
inline void TA_Entry<K, V>::insert(int i, T_Entry<K, V>& element) // i��°�� ���Ҹ� �������
{
	// ����, num_elements�� capacity�� �Ѿ�°�? 
	// �Ѿ�ٸ� 2���� �뷮���� ���Ӱ� �迭�� ���Ҵ��Ѵ�.
	if (this->Size() >= this->capacity)
	{
		int new_capa = 2 * capacity;		// 2���� �뷮
		this->reserve(new_capa);			// reserve�� ���Ӱ� �����
	}

	if (this->isValidIndex(i))				// i�� ��ȿ�� ������ Ȯ��
	{
		// i��°�� ���� ����ֱ� ����, ������ i��°���� ������������ 
		// ���� ��ĭ�� �ڷ� �о��, i��°�� �߰��Ѵ�.
		for (int j = this->Size() - 1; j >= i; i--)
		{
			t_GA[j + 1] = t_GA[j];			// ��ĭ�� �ڷ� �δ�.
		}
		t_GA[i] = element;					// i��°�� ���� �ְ�
		num_elements++;						// num_elements�� 1�� ���Ѵ�.
	}
}
template<typename K, typename V>
inline void TA_Entry<K, V>::remove(int i)		// i��°�� ���� ������
{
	// ���� ���� �����ش�. 
	if (this->isValidIndex(i))				// �ε��� ��ȣ ��ȿ���˻� ��
	{
		// i��°�� ���� ������ ������ ���� ��ܼ� i��° ���� ����
		for (int j = i + 1; i < this->Size(); i++)
		{
			t_GA[i - 1] = t_GA[i];
		}
		num_elements--;						// num_elements -1 ��
	}

	// ���� num_elements�� ���� ���� �뷮�� ���� ���϶��
	if (this->Size() < (capacity / 2))
	{
		int new_capa = capacity / 2;
		this->reserve(new_capa);			// ���Ӱ� �迭�� �����
	}
}
template<typename K, typename V>
inline void TA_Entry<K, V>::set(int i, T_Entry<K, V>& element) // i��°�� ���� element�� �ٲ�
{
	// ���� ��ȣ�� ��ȿ�� ��ȣ��� ���� ����
	if (this->isValidIndex(i))
	{
		t_GA[i] = element;
	}
	else
		return 0;					// �ƴϸ� 0�� ��ȯ
}
template<typename K, typename V>
inline T_Entry<K, V>& TA_Entry<K, V>::at(int i)	// �迭�� i��° ���� ��ȯ
{
	// ���� ��ȿ�� �˻縦 ����ߴٸ� t_GA[i]�� ��ȯ, �ƴϸ� NULL�� ��ȯ
	if (this->isValidIndex(i))
		return t_GA[i];
	else
		return NULL;
}

/*					member funtions ( ��� �Լ� )
		1. Min(begin, end) ( begin, end ���̿��� ���� ���� ���� ���� ��ȯ ) 
		2. Max(begin, end) ( begin, end ���̿��� ���� ���� ū ���� ��ȯ ) 
		3. shuffle() ( �迭�� ���� �������� ���� )
		4. sequential_search(search_key) ( Ű�� ����Ž���� )
		5. binary_search(search_key) ( Ű�� ����Ž���� )
		6. selection_sort(sd) ( ��������, ����/�������� ���� )
		7. quick_sort(sd) ( ������ ) 
		8. 9. _quick_sort(~), _partition(~) ( ������ ���Լ�, ��Ƽ�� �Լ� )
		10. 11. fprint(), fprintsample() ( �迭 ��� �Լ�, �迭 ��� ���� �Լ� )
		12. isValidIndex(i) ( �ε��� ��ȣ ��ȿ�� �˻� )			*/
template<typename K, typename V>
inline T_Entry<K, V> TA_Entry<K, V>::Min(int begin, int end)		// �ּҰ�
{
	// �ּҰ� �ʱⰪ ����
	T_Entry<K, V>& minValue = this->t_GA[begin];

	// begin + 1���� end���� ���� �����ذ��� �ּҰ��� ã�� ( ���⼭�� �켱������ ���� )
	for (int i = begin + 1; i < end; i++)
	{
		if (minValue > this->t_GA[i])
			minValue = this->t_GA[i];
	}

	return minValue;		// �ּҰ� ��ȯ
}
template<typename K, typename V>
inline T_Entry<K, V> TA_Entry<K, V>::Max(int begin, int end)		// �ִ밪
{
	// �ִ밪 �ʱⰪ ����
	T_Entry<K, V>& maxValue = this->t_GA[begin];

	// begin + 1���� end���� ���� �����ذ��� �ִ밪�� ã�� ( ���⼭�� �켱������ ���� )
	for (int i = begin + 1; i < end; i++)
	{
		if (maxValue < this->t_GA[i])
			maxValue = this->t_GA[i];
	}

	return maxValue;		// �ִ밪 ��ȯ
}
template<typename K, typename V>
inline void TA_Entry<K, V>::shuffle()
{
	srand((unsigned int)time(NULL));				// �ð����� �õ� ����
	int index1 = 0, index2 = 0;
	int count = 0;
	T_Entry<K, V> temp;

	while (count != num_elements)
	{
		// ���� ���� ���� ��ȯ���� �����Ƿ� rand()������ ����� ��
		index1 = ((rand() << 15) | (rand())) % num_elements;
		index2 = ((rand() << 15) | (rand())) % num_elements;

		// swaping 
		temp = this->t_GA[index1];
		this->t_GA[index1] = this->t_GA[index2];
		this->t_GA[index2] = temp;

		count++;				// ī��Ʈ ��
	} 
}
template<typename K, typename V>
inline int TA_Entry<K, V>::sequential_search(T_Entry<K, V> search_key)
{
	// if t_GA[i] == search_key�� ���, i�� ��ȯ, �ƴϸ� -1�� ��ȯ
	for (int i = 0; i < this->Size(); i++)
	{
		if (search_key == this->t_GA[i])
			return i;
	}
	return -1;		// fail to searching
}
template<typename K, typename V>
inline int TA_Entry<K, V>::binary_search(T_Entry<K, V> search_key)		// ����Ž��
{
	int low = 0, high = this->Size()-1, mid = 0;
	int loop = 0;
	
	while (low >= high)
	{
		mid = (low + high) / 2;		// mid���� �߰��� ��� �ٲ�� ������ ��� ����
		if (this->t_GA[mid] == search_key)		// ���� �߾Ӱ��� search_key�� ���ٸ�, mid�� ��ȯ
			return mid;
		if (this->t_GA[mid] > search_key)		// �߾Ӱ����� ũ�ٸ� low�� mid + 1�� ���� ����
			low = mid + 1;
		else
			high = mid - 1;						// �߾Ӱ����� �۴ٸ� high�� mid - 1�� ����

		loop++;		// loop counting 
	}	

	return -1;		// fail to searching
	
}
template<typename K, typename V>
inline void TA_Entry<K, V>::selection_sort(SortDirection sd)
{
	T_Entry<K, V> compareValue;		// ���� ��
	int compareindex;				// ���� �� �ε���

	for (int i = 0; i < this->Size() - 1; i++)
	{
		if (sd == INCREASING)			// ��������
		{
			compareindex = i; compareValue = this->t_GA[i];	// ���� ��, �ε�����ȣ �ʱⰪ ����
			for (int j = i; j < this->Size(); j++)
			{
				if (compareValue > this->t_GA[j])			// ���� ���� ���� �� �۴ٸ�
				{
					compareValue = this->t_GA[j];			// �ּҰ� ����
					compareindex = j;						// �ּҰ� �ε��� ����
				}
			}
		}

		else							// ��������
		{
			compareindex = i; compareValue = this->t_GA[i];	// ���� ��, �ε��� ��ȣ �ʱ�ȭ
			for (int j = i; j < this->Size(); j++)
			{
				if (compareValue < this->t_GA[j])			// ���� ���� �� ũ�ٸ�
				{
					compareValue = this->t_GA[j];			// �ִ밪 ����
					compareindex = j;						// �ִ밪 �ε��� ����
				}
			}
		}

		// swaping, temp�� �ʿ���� ( compareValue�� temp���� �� )
		this->t_GA[compareindex] = this->t_GA[i];
		this->t_GA[i] = compareValue;
	}
}
template<typename K, typename V>
inline void TA_Entry<K, V>::quick_sort(SortDirection sd)
{
	_quick_sort(this->t_GA, this->Size(), 0, this->Size() - 1, sd);
}
template<typename K, typename V>
inline void _quick_sort(T_Entry<K, V>* Array, int Size, int left, int right, SortDirection sd)
{ 
	// ������ �� �Լ�
	int P_I = 0, newPI = 0;

	if (left >= right)				// ���� left�� right �̻��̶��, newPI��ȯ ������
		return;

	// �ƴ϶�� P_I�� ���� �� ��, newPI�� ���Ѵ�. ( P_I�� �������� ū��, ������ �з� ��, ���Ӱ� �߾Ӱ��� ����
	else if (left < right)
		P_I = (left + right) / 2;

	newPI = _partition(Array, Size, left, right, P_I, sd);

	if (left < (newPI - 1))
		// �з��� �� ��, ���ʹ迭�� ���� ����
		_quick_sort(Array, Size, left, newPI - 1, sd);
		// newPI�� �����ϸ鼭 �ٽ� ũ���� �з�
	if ((newPI + 1) < right)
		// �� ��, �����ʹ迭 ����
		_quick_sort(Array, Size, newPI + 1, right, sd);
}
template<typename K, typename V>
inline int _partition(T_Entry<K, V>* Array, int Size, int left, int right, int PivotIndex, SortDirection sd)
{
	int newPI = 0;
	T_Entry<K, V> PivotValue, temp;

	// ����, PivotValue�� �迭�� ���� ������ ���� �ٲ۴�.
	PivotValue = Array[PivotIndex];
	Array[PivotIndex] = Array[right];
	Array[right] = PivotValue;

	// newPI �ʱⰪ ���� = left
	newPI = left;
	for (int i = left; i < right; i++)
	{
		// ���������� ���, �������� ����, ū���� ������
		if (sd == INCREASING)
		{
			if (Array[i] <= PivotValue)		// ���� PivotValue���� �۰ų� ������
			{
				// newPI�� ���� �ڸ��� �ٲ۴�.
				temp = Array[i];
				Array[i] = Array[newPI];
				Array[newPI] = temp;
				newPI += 1;			// �׸��� newPI�� ���� ����
			}
		}
		else
		{
			if (Array[i] > PivotValue)		// ���� PivotValue���� ũ�ٸ�
			{
				// newPI�� ���� �ڸ��� �ٲ۴�.
				temp = Array[i];
				Array[i] = Array[newPI];
				Array[newPI] = temp;
				newPI += 1;			// �׸��� newPI�� ���� ����
			}
		}
	}

	// ���� ó�� PivotValue�� �������� ������ PivotValue���� ���� ����, �������� ū ������ �з��� 
	// �������� ����
	// ���� ���������� �� PivotValue�� ����ġ��Ŵ
	PivotValue = Array[right];
	Array[right] = Array[newPI];
	Array[newPI] = PivotValue;

	return newPI;
}
template<typename K, typename V>		// ���� ���
inline void TA_Entry<K, V>::fprint(ostream ostr, int elements_per_line)
{
	// num_lines = ���ٴ� ele~����ŭ �� ���� ����ϴ���?
	int num_lines = (this->Size() / elements_per_line) + 1;

	// 2�� �ݺ����� ���� ���
	for (int i = 0; i < num_lines; i++)
	{
		// �� �ٴ� ele~��, ����� ����, ���� �� ����ϰ� ���� �� �κ��� ���� ���·� ���
		for (int j = 0; j < elements_per_line; j++)
		{
			ostr << setw(10) << this->t_GA[10 * i + j] << " ";
		}
		ostr << endl;		// �������� endl��
	}
	ostr << endl;
	// print TA_Entry array 
}
template<typename K, typename V>		// ���� ��� (n�ٸ� ����� ������ ����)
inline void TA_Entry<K, V>::fprintSample(ostream ostr, int elements_per_line, int num_sample_lines)
{
	//int lastIndexs = 0;						// ���� ��, ���� �ε��� ��ȣ�� �� ù°

	//// ó���κ� ���
	//for (int i = 0; i < num_sample_lines; i++)
	//{
	//	for (int j = 0; j < elements_per_line; j++)
	//	{
	//		ostr << setw(10) << this->t_GA[elements_per_line * i + j] << " ";
	//	}
	//	ostr << endl;
	//}
	//// ����
	//ostr << " . . . . . . " << endl;
	//// lastIndex�� ����
	//lastIndexs = this->Size() - (elements_per_line * (num_sample_lines - 1) + (this->Size() % elements_per_line) + 1);

	//// ���� ��, ���� �κ� ���
	//for (int i = 0; i < num_sample_lines; i++)
	//{
	//	for (int j = 0; j < elements_per_line; j++)
	//	{
	//		ostr << setw[10] << this->t_GA[lastIndexs + (elements_per_line * i + j)] << " ";
	//	}
	//	ostr << endl;
	//}
	//ostr << endl;
	// print TA_Entry array, sample_lines
}
template<typename K, typename V>
inline bool TA_Entry<K, V>::isValidIndex(int i)
{
	// ���� �ε��� ��ȣ�� 0~capacity-1 ���� ���� ���� �ʴٸ� false, �ƴϸ� true
	if (i < 0 || i >= this->capacity)
		return false;
	return true;
}

#endif // !TA_ENTRY_H