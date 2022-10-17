#ifndef T_ARRAY_H
#define T_ARRAY_H

#include "Student.h"
#include <iostream>
#include <iomanip>

using namespace std;

// 오름차순, 내림차순
enum SortingOrder { INCREASING = 0, DECREASING = 1 };

template <typename T, typename K>			// 클래스를 탬플릿으로 지정함
class T_Array
{
public:
	// constructor
	T_Array();								// 기본 생성자
	T_Array(int capa, string n);			// 인자를 받은 생성자

	// destructor
	~T_Array();

	// getter
	int size() { return num_elements; }		// num_elements 반환
	string Name() { return name; }			// 이름
	bool empty() { return num_elements == 0; } // 비어있는지 확인

	// member functions
	void reserve(int new_capacity);			// 용량 재설정 함수
	void insert(int i, T element);			// 값 삽입 함수
	void remove(int i);						// 값 제거 함수
	T& at(int i);							// 배열 변수 반환
	void set(int i, T& element);			// 배열 설정 
	T& Min(int begin, int end);				// 배열의 최소값
	T& Max(int begin, int end);				// 배열의 최대값 
	void print(int elements_per_line);	// 배열 출력
	bool isValidIndex(int index);			// 인덱스번호 유효성 검사
	int sequential_Search(string KeyName, K& search_key);	// 순차 탐색
	int binary_Search(string KeyName, K& search_key);		// 이진 탐색

	// Sorting
	void shuffle();							// 배열 뒤섞기
	void selection_sort(string KeyName, SortingOrder order = INCREASING);	// 선택정렬
	void merge_sort(string KeyName, SortingOrder order = INCREASING);		// 병합정렬
	void quick_sort(string KeyName, SortingOrder order = INCREASING);		// 퀵정렬

	T& operator[](int index);				// 배열값 반환

private:
	void _mergeSort(T* arr, T* tmp_array, int left, int right, string KeyName, SortingOrder order);
	T* t_array;
	int num_elements;
	int capacity;
	string name;
};

template<typename T, typename K>
int _partition(T* array, int size, int left, int right, int PivotIndex, string KeyName, SortingOrder order);
template<typename T, typename K>
void _quickSort(T* array, int size, int left, int right, string KeyName, SortingOrder order);

/*				constructor ( 생성자 )
		1. default constructor ( 디폴트 생성자 )
		2. 용량, 이름을 받은 constructor				*/
template<typename T, typename K>
inline T_Array<T, K>::T_Array()
{
	// t_array는 NULL, 나머지는 0으로 초기화
	t_array = NULL;
	num_elements = 0;
	capacity = 0;
	name = "";
}
template<typename T, typename K>
inline T_Array<T, K>::T_Array(int capa, string n)
{
	capacity = capa;						// 용량 대입
	t_array = new T[capacity];				// 배열 동적할당
	if (t_array == NULL)
	{
		cout << "Error in allocate array !!" << endl;
		exit(-1);
	}
	num_elements = 0;
	name = n;
}

/*				destructor ( 소멸자 )				*/
template<typename T, typename K>
inline T_Array<T, K>::~T_Array()
{
	if (t_array != NULL)			// 만약 배열이 존재한다면 delete
		delete[] t_array;
}

/*					인자 관련 함수
		1. isValidIndex(index) : 인덱스번호 유효성 검사
		2. reserve (new_capacity) : 용량 증가
		3. insert (i, element) : 인자를 삽입
		4. remove (i) : i번째 인자를 제거
		5. at(i) : 배열의 값을 반환함
		6. set(i, element) : 배열의 값을 변경함
		7. Min(), Max() : 최소값, 최대값
		8. fprint(fout, elemnets_per_line) : 배열 출력
		7. 순차탐색, 이진탐색							*/

template<typename T, typename K>
inline bool T_Array<T, K>::isValidIndex(int index)
{
	// 인덱스번호가 0 ~ capacity - 1사이에 있다면 true, 아니면 false
	if (index >= 0 && index < capacity)
		return true;
	else
		return false;
}
template<typename T, typename K>
inline void T_Array<T, K>::reserve(int new_capacity)
{

	if (capacity >= new_capacity)
		return;						// 용량이 충분하므로 필요없음

	T* old_array = this->t_array;						// 올드한 자료를 대입
	this->t_array = new T[new_capacity];				// 새로운 용량의 배열 생성
	if (t_array == NULL)								// 배열 생성 실패시 종료
	{
		cout << "Error in allocate array !!" << endl;
		exit(-1);
	}
	cout << this->Name() << " expands capacity to " << new_capacity << endl;

	// 기존의 값들을 모두 대입
	for (int i = 0; i < this->num_elements; i++)
		t_array[i] = old_array[i];

	delete[] old_array;			// 이전의 배열은 delete
	capacity = new_capacity;	// 새로운 용량으로 수정 
}
template<typename T, typename K>
inline void T_Array<T, K>::insert(int i, T element)
{
	// 만약 용량이 현재 든 값들 보다 적다면
	if (num_elements >= capacity)
	{
		int new_capa;
		new_capa = 2 * capacity;	// 새롭게 용량을 2배로 늘린 후, 다시 만듦
		reserve(new_capa);			// reserve 함수 호출
	}

	if (isValidIndex(i))			// 용량을 늘린후(선택) 인덱스 번호 검사
	{
		for (int j = this->num_elements - 1; j >= i; j--)	// i번째 이후의 값들은 전부 한칸씩 밀어줌
			t_array[j + 1] = t_array[j];
		t_array[i] = element;			// 비어있는 i번째에 값을 대입
		num_elements++;						// num_elements를 증가
	}
}
template<typename T, typename K>
inline void T_Array<T, K>::remove(int i)
{
	// 유효한 값인지 확인 후
	if (isValidIndex(i))
	{
		// i번째 까지 값을 모두 당겨서 i번째의 값을 없앰
		for (int j = i + 1; j < num_elements; j++)
			t_array[j - 1] = t_array[j];
		num_elements--;			// 값을 줄임
	}
	// 만약 배열의 개수가 2분의 1이하라면 용량을 줄임.
	if (num_elements < (capacity / 2))
	{
		int new_capa = capacity / 2;	// 2분의 1배의 용량
		T* t_newAR = (T*) new T[new_capa];		// 새롭게 배열 생성
		if (t_newAR == NULL)
		{
			cout << "Error in realloc new array!!" << endl;
			return;
		}

		// 배열의 값을 새로운 배열에 대입
		for (int i = 0; i < num_elements; i++)
			t_newAR[i] = t_array[i];

		// 기존의 배열을 없앰
		delete[] t_array;
		t_array = t_newAR;
		capacity = new_capa;
	}
}
template<typename T, typename K>
inline T& T_Array<T, K>::at(int i)
{
	if (isValidIndex(i))
		return t_array[i];			// 인덱스 번호가 유효하면 배열의 값을 반환
	else
		return 0;
}
template<typename T, typename K>
inline void T_Array<T, K>::set(int i, T& element)
{
	if (isValidIndex(i))
	{
		t_array[i] = element;		// 인덱스 번호가 유효하면 배열에 값을 변경함
	}
	else
		return 0;
}
template<typename T, typename K>
inline T& T_Array<T, K>::Min(int begin, int end)
{
	T min_value;					// 최소값 
	int index_min;					// 최소값 인덱스 번호

	// 초기값 설정
	min_value = t_array[begin];	index_min = begin;
	for (int i = begin + 1; i < end; i++)
	{
		// 만약 min_value보다 t_array[i]가 작으면
		if (t_array[i] < min_value)
		{
			min_value = t_array[i];		// 최소값을 새롭게 갱신
			index_min = i;				// 인덱스번호도 갱신
		}
	}

	return t_array[index_min];			// 최소값 반환
}
template<typename T, typename K>
inline T& T_Array<T, K>::Max(int begin, int end)
{
	T max_value;					// 최대값 
	int index_max;					// 최대값 인덱스 번호

	// 초기값 설정
	max_value = t_array[begin];	index_max = begin;
	for (int i = begin + 1; i < end; i++)
	{
		// 만약 max_value보다 t_array[i]가 크면
		if (t_array[i] > max_value)
		{
			max_value = t_array[i];		// 최대값을 새롭게 갱신
			index_max = i;				// 인덱스번호도 갱신
		}
	}

	return t_array[index_max];			// 최대값 반환
}
template<typename T, typename K>
inline void T_Array<T, K>::print(int elements_per_line)
{
	int count = 0;
	// 출력 
	while (count < num_elements)
	{
		for (int i = 0; i < elements_per_line; i++)
		{
			// 객체 출력, 한줄에 여러개를 출력하기 때문에 endl은 쓰지 않음
			cout << *t_array[count] << " ";
			count++;
			// 만약, 한줄의 출력이 다 끝났으면 endl;을 붙임
			if (count % elements_per_line == 0)
				cout << endl;
		}
	}
	cout << endl;
}
template<typename T, typename K>
inline int T_Array<T, K>::sequential_Search(string KeyName, K& search_key)		// 순차탐색
{
	string keytype;
	K key = NULL;

	// 하나하나 다 살펴봄
	for (int index = 0; index < num_elements; index++)
	{
		t_array[index]->getKey(KeyName, &key);
		if (key == search_key)		// 만약 똑같은것을 찾게 된다면 index를 반환
			return index;
	}
	return -1;			// 없으면 -1 반환
}
template<typename T, typename K>
inline int T_Array<T, K>::binary_Search(string KeyName, K& search_key)
{
	int low, mid, high;
	int loop = 1;

	// 초기값 설정 (low = 0, high = num_elements - 1)
	low = 0; high = num_elements - 1;
	K mid_key = NULL;

	while (low <= high)					// 로우와 하이가 만나기 전까지
	{
		// mid 값 설정 
		mid = (low + high) / 2;

		// 키 획득
		t_array[mid]->getKey(KeyName, &mid_key);
		// 만약 search_key가 mid보다 작다면, high를 갱신
		if (mid_key > search_key)
			high = mid - 1;
		// 만약 search_key가 mid보다 크다면, low를 갱신
		else if (mid_key < search_key)
			low = mid + 1;
		else
			return mid;			// 같다면 mid 반환
		loop++;
	}

	return -1;
}

/*							정렬 관련 함수
		1. shuffle() : 배열 섞기 함수
		2. selection_sort(order) : 오름/내림차순에 따라 선택정렬
		3. merge_sort()	: 병합정렬
		4. _mergeSort() : 병합정렬 본함수
		3. quick_sort(order) : 오름/내림차순으로 퀵정렬
		4. _quicksort() : 퀵정렬 본함수
		5. _partition()	: 배열 중간값을 기준으로 조건에 맞게 분류			*/
template<typename T, typename K>
inline void T_Array<T, K>::shuffle()
{
	srand((unsigned int)time(NULL));		// 시드 생성
	int index1, index2;						// 인덱스 번호 1, 2
	T temp;									// 옮겨다닐 변수 temp

	for (int i = 0; i < num_elements; i++)
	{
		// 인덱스1 , 인덱스2 생성
		index1 = (((unsigned int)rand() << 15) | rand()) % num_elements;
		index2 = (((unsigned int)rand() << 15) | rand()) % num_elements;

		// swaping
		temp = t_array[index1];
		t_array[index1] = t_array[index2];
		t_array[index2] = temp;
	}
}
template<typename T, typename K>
inline void T_Array<T, K>::selection_sort(string KeyName, SortingOrder order)
{
	int In_Min, In_Max;
	T tempElement;
	K minKey, maxKey, Key;

	for (int i = 0; i < num_elements - 1; i++)
	{
		// 오름차순 정렬
		if (order == INCREASING)
		{
			// Min 부분 초기값 설정
			In_Min = i;
			t_array[i]->getKey(KeyName, &Key); // 인덱스 번호, 키값을 획득
			minKey = (K)Key;			// 최소의 키 값 얻기

			for (int j = i + 1; j < num_elements; j++)
			{
				this->t_array[j]->getKey(KeyName, &Key); // 인덱스 번호, 키값을 획득
				// 가장 작은 값 찾기
				if ((K)Key < minKey)			// 키를 비교하여, 새로운 값이 작으면 갱신
				{
					minKey = (K)Key;			// 키 갱신
					In_Min = j;
				}
			}
			// Swaping
			if (In_Min != i)
			{
				tempElement = t_array[In_Min];
				t_array[In_Min] = t_array[i];
				t_array[i] = tempElement;
			}
		}

		// 내림차순 정렬
		else
		{
			// Max 부분 초기값 설정
			In_Max = i;
			this->t_array[i]->getKey(KeyName, &Key); // 인덱스 번호, 키값을 획득
			maxKey = (K)Key;			// 최대의 키 값 얻기

			for (int j = i + 1; j < num_elements; j++)
			{
				this->t_array[j]->getKey(KeyName, &Key); // 인덱스 번호, 키값을 획득
				// 가장 큰 키 찾기
				if ((K)Key > maxKey)			// 키를 비교하여, 새로운 값이 크면 갱신
				{
					maxKey = (K)Key;			// 키 갱신
					In_Max = j;
				}
			}
			// Swaping
			if (In_Max != i)
			{
				tempElement = t_array[In_Max];
				t_array[In_Max] = t_array[i];
				t_array[i] = tempElement;
			}
		}
	}
}
template<typename T, typename K>
inline void T_Array<T, K>::merge_sort(string KeyName, SortingOrder order)
{
	T* tmp_array = new T[num_elements];
	if (tmp_array == NULL)
	{
		cout << "ERROR in creation tmp_array!!" << endl;
		exit(-1);
	}

	_mergeSort(t_array, tmp_array, 0, size() - 1, KeyName, order);
	delete[] tmp_array;
}
template<typename T, typename K>
inline void T_Array<T, K>::_mergeSort(T* arr, T* tmp_array, int left, int right, string KeyName, SortingOrder order)
{
	K key_i, key_j;

	if (left >= right)				// 만약 배열의 원소가 1개라면 서치 끝
		return;

	int mid = (left + right) / 2;
	_mergeSort(arr, tmp_array, left, mid, KeyName, order);		// 왼쪽 
	_mergeSort(arr, tmp_array, mid+1, right, KeyName, order);		// 오른쪽 값 


	for (int i = left; i <= mid; i++)						// 왼쪽은 순서대로 임시 배열에 넣어줌
		tmp_array[i] = arr[i];
	for (int j = 1; j <= right - mid; j++)					// 오른쪽은 역순(중요)으로 임시배열에 넣어줌
		tmp_array[right - j + 1] = arr[j + mid];

	// [1, 5, 2, 9, ----- ] → [1, 5, 9, 2, -----]

	for (int i = left, j = right, k = left; k <= right; k++)	// 중간 기준으로
	{
		tmp_array[i]->getKey(KeyName, &key_i);
		tmp_array[j]->getKey(KeyName, &key_j);
		// 키를 비교하여 작은 값은 왼쪽부터 넣어줌, 큰값은 오른쪽부터 넣어줌 (오름차순 기준)
		if (order == INCREASING)
		{
			if ((K)key_i < (K)key_j)
				arr[k] = tmp_array[i++];
			else
				arr[k] = tmp_array[j--];
		}
		else
		{
			if ((K)key_i > (K)key_j)
				arr[k] = tmp_array[i++];
			else
				arr[k] = tmp_array[j--];
		}
	}

}
template<typename T, typename K>
inline void T_Array<T, K>::quick_sort(string KeyName, SortingOrder order)
{
	_quickSort(t_array, size(), 0, size() - 1, KeyName, order);
}
template<typename T, typename K>
inline void _quickSort(T* array, int size, int left, int right, string KeyName, SortingOrder order)
{
	int P_I, newPI;

	if (left >= right)							// 만약 left가 right보다 크거나 같다면 newPI반환 중지, 거의 left가 1혹은 0일때이다..
		return;

	else if (left < right)
	{
		P_I = (left + right) / 2;				// 중간값, 만약 홀수인경우 내림값으로 나누기위치값 산출
	}

	newPI = _partition(array, size, left, right, P_I, KeyName, order);

	// 이렇게 왼쪽, 오른쪽 순서대로 작은덩이 → 큰덩이
	if (left < (newPI - 1))									// 이제 newPI기준으로 왼쪽부분
	{
		_quicksort(array, size, left, newPI - 1, KeyName, order);
		// 다시 newPI를 산출하면서 크기정렬을 쭉해준다.
	}
	if ((newPI + 1) < right)								// 다음, 왼쪽이 quickSort를 진행후, newPI기준 오른쪽 부분
	{
		_quicksort(array, size, newPI + 1, right, KeyName, order);
		// 오른쪽으로 newPI산출및 크기순으로 정렬해준다.
	}
}
template<typename T, typename K>
inline int _partition(T* array, int size, int left, int right, int PivotIndex, string KeyName, SortingOrder order)
{
	int newPI;
	T PivotValue, temp;							// PivotValue = 바꾸는 변수
	K key = NULL, key_val = NULL;

	PivotValue = array[PivotIndex];
	PivotValue.getKey(KeyName, &key_val);		// PivotValue 키 값을 구함

	array[PivotIndex] = array[right];
	array[right] = PivotValue;
	// 맨 처음 PivotIndex에 있던 값을 맨 오른쪽(혹은 P_I-1위치에 있는 값)과 바꾼다

	newPI = left;						// 이제 새로운 피벗위치를 설정해주는데 초기값은 맨 왼쪽(혹은 P_I + 1위치)으로 설정
	for (int i = left; i <= right - 1; i++)
		// 맨뒤로 가게된 PivotValue는 빼고 나머지 배열들을 범위로 잡는다.
	{
		array[i].getKey(KeyName, &key);

		if (order == INCREASING)
		{
			if ((K)key <= (K)key_val)								// 만약 key_val보다 key 값이 작다면
			{
				temp = array[i];
				array[i] = array[newPI];
				array[newPI] = temp;							// 현재(i)위치에 있는 값을 newPI에 있는 값과와 바꿔준다.
				newPI += 1;
			}
		}
		else
		{
			if ((K)key > (K)key_val)								// 만약 key_val보다 key 보다 작다면
			{
				temp = array[i];
				array[i] = array[newPI];
				array[newPI] = temp;							// 현재(i)위치에 있는 값을 newPI에 있는 값과와 바꿔준다.
				newPI += 1;
			}
		}
	}
	// 결론적으로 처음 PivotValue값을 기준으로 왼쪽은 PivotValue보다 작은 값들의 배열, 오른쪽은 PivotValue보다 큰 값들의 배열이 형성되었다.
	PivotValue = array[right];
	array[right] = array[newPI];
	array[newPI] = PivotValue;

	return newPI;											// newPI 반환
}

// operator overloading []
template<typename T, typename K>
inline T& T_Array<T, K>::operator[](int index)
{
	// 인덱스 번호가 유효하면 값 반환
	if (isValidIndex(index))
		return t_array[index];
	return 0;
}



#endif // !T_ARRAY_H



