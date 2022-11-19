#ifndef T_ARRAY_H
#define T_ARRAY_H

#include <iostream>
#include <iomanip>

using namespace std;

// 오름차순, 내림차순
enum SortingOrder { INCREASING = 0, DECREASING = 1 };

template <typename V>						// 클래스를 탬플릿으로 지정함
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

	// member functions
	void reserve(int new_capacity);			// 용량 재설정 함수
	void insert(int i, V element);			// 값 삽입 함수
	void insertBack(V element);				// 맨마지막에 
	void remove(int i);						// 값 제거 함수
	V& at(int i);							// 배열 변수 반환
	void set(int i, V& element);			// 배열 설정 
	V& Min(int begin, int end);				// 배열의 최소값
	V& Max(int begin, int end);				// 배열의 최대값 
	void fprint(ofstream& fout, int elements_per_line);	// 배열 출력
	bool isValidIndex(int index);			// 인덱스번호 유효성 검사
	int sequential_Search(V& search_key);	// 순차 탐색
	int binary_Search(V& search_key);		// 이진 탐색

	// Sorting
	void shuffle();							// 배열 뒤섞기
	void selection_sort(SortingOrder order = INCREASING);	// 선택정렬
	void quick_sort(SortingOrder order = INCREASING);		// 퀵정렬

	V& operator[](int index);				// 배열값 반환

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

/*				constructor ( 생성자 )
		1. default constructor ( 디폴트 생성자 )
		2. 용량, 이름을 받은 constructor				*/
template<typename V>
inline T_Array<V>::T_Array()
{
	// t_array는 NULL, 나머지는 0으로 초기화
	t_array = NULL;
	num_elements = 0;
	capacity = 0;
	name = "";
}
template<typename V>
inline T_Array<V>::T_Array(int capa, string n)
{
	capacity = capa;						// 용량 대입
	t_array = new V[capacity];				// 배열 동적할당
	if (t_array == NULL)
	{
		cout << "Error in allocate array !!" << endl;
		exit(-1);
	}
	num_elements = 0;
	name = n;
}

/*				destructor ( 소멸자 )				*/
template<typename V>
inline T_Array<V>::~T_Array()
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

template<typename V>
inline bool T_Array<V>::isValidIndex(int index)
{
	// 인덱스번호가 0 ~ capacity - 1사이에 있다면 true, 아니면 false
	if (index >= 0 && index < capacity)
		return true;
	else
		return false;
}
template<typename V>
inline void T_Array<V>::reserve(int new_capacity)
{

	if (capacity >= new_capacity)
		return;						// 용량이 충분하므로 필요없음

	V* old_array = this->t_array;						// 올드한 자료를 대입
	this->t_array = new V[new_capacity];				// 새로운 용량의 배열 생성
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
template<typename V>
inline void T_Array<V>::insert(int i, V element)
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
template<typename V>
inline void T_Array<V>::insertBack(V element)
{
	// 만약 용량이 현재 든 값들 보다 적다면
	if (num_elements >= capacity)
	{
		int new_capa;
		new_capa = 2 * capacity;	// 새롭게 용량을 2배로 늘린 후, 다시 만듦
		reserve(new_capa);			// reserve 함수 호출
	}

	if (isValidIndex(this->num_elements))			// 용량을 늘린후(선택) 인덱스 번호 검사
	{
		t_array[num_elements] = element;			// 비어있는 i번째에 값을 대입
		num_elements++;						// num_elements를 증가
	}
}

template<typename V>
inline void T_Array<V>::remove(int i)
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
		V* t_newAR = (V*) new V[new_capa];		// 새롭게 배열 생성
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
template<typename V>
inline V& T_Array<V>::at(int i)
{
	if (isValidIndex(i))
		return t_array[i];			// 인덱스 번호가 유효하면 배열의 값을 반환
	else
		return 0;
}
template<typename V>
inline void T_Array<V>::set(int i, V& element)
{
	if (isValidIndex(i))
	{
		t_array[i] = element;		// 인덱스 번호가 유효하면 배열에 값을 변경함
	}
	else
		return 0;
}
template<typename V>
inline V& T_Array<V>::Min(int begin, int end)
{
	V min_value;					// 최소값 
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
template<typename V>
inline V& T_Array<V>::Max(int begin, int end)
{
	V max_value;					// 최대값 
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
template<typename V>
inline void T_Array<V>::fprint(ofstream& fout, int elements_per_line)
{
	int count = 0;
	// 출력 
	while (count < num_elements)
	{
		for (int i = 0; i < elements_per_line; i++)
		{
			// 객체 출력, 한줄에 여러개를 출력하기 때문에 endl은 쓰지 않음
			fout << t_array[count] << " ";
			count++;
			// 만약, 한줄의 출력이 다 끝났으면 endl;을 붙임
			if (count % elements_per_line == 0)
				fout << endl;
		}
	}
	fout << endl;
}
template<typename V>
inline int T_Array<V>::sequential_Search(V& search_key)		// 순차탐색
{
	int index;
	// 하나하나 다 살펴봄
	for (int index = 0; index < num_elements; index++)
	{
		if (t_array[index] == search_key)		// 만약 똑같은것을 찾게 된다면 index를 반환
			return index;
	}
	return -1;			// 없으면 -1 반환
}
template<typename V>
inline int T_Array<V>::binary_Search(V& search_key)
{
	int low, mid, high;
	int loop = 1;

	// 초기값 설정 (low = 0, high = num_elements - 1)
	low = 0; high = num_elements - 1;

	while (low <= high)
	{
		// mid 값 설정 
		mid = (low + high) / 2;
		// 만약 search_key가 mid보다 작다면, high를 갱신
		if (t_array[mid] > search_key)
			high = mid - 1;
		// 만약 search_key가 mid보다 크다면, low를 갱신
		else if (t_array[mid] < search_key)
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
		3. quick_sort(order) : 오름/내림차순으로 퀵정렬
		4. _quicksort(array, size, left, right, order) : 퀵정렬 본함수
		5. _partition(array, size, left, right, PivotIndex, order)
			: 배열 중간값을 기준으로 조건에 맞게 분류			*/
template<typename V>
inline void T_Array<V>::shuffle()
{
	srand((unsigned int)time(NULL));		// 시드 생성
	int index1, index2;						// 인덱스 번호 1, 2
	V temp;									// 옮겨다닐 변수 temp

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
template<typename V>
inline void T_Array<V>::selection_sort(SortingOrder order)
{
	int In_Min, In_Max;
	V minValue, maxValue;

	for (int i = 0; i < num_elements - 1; i++)
	{
		// 오름차순 정렬
		if (order == INCREASING)
		{
			// Min 부분 초기값 설정
			In_Min = i;	minValue = t_array[i];

			for (int j = i + 1; j < num_elements; j++)
			{
				// 가장 작은 값 찾기
				if (t_array[j] < minValue)	// 만약 t_array[i]가 minValue보다 작다면
				{
					minValue = t_array[j];	// 최소값 갱신
					In_Min = j;
				}
			}
			// Swaping
			t_array[In_Min] = t_array[i];
			t_array[i] = minValue;
		}

		// 내림차순 정렬
		else
		{
			// Min 부분 초기값 설정
			In_Max = i;	maxValue = t_array[i];

			for (int j = i + 1; j < num_elements; j++)
			{
				// 가장 큰 값 찾기
				if (t_array[j] > maxValue)
				{
					// 만약 t_array[i]가 maxValue보다 더 크다면 갱신
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
	//초기함수 부름
	_quicksort(t_array, size(), 0, size() - 1, order);
}
template<typename V>
void _quicksort(V* array, int size, int left, int right, SortingOrder order)
{
	int P_I, newPI;

	if (left >= right)							// 만약 left가 right보다 크거나 같다면 newPI반환 중지, 거의 left가 1혹은 0일때이다..
		return;

	else if (left < right)
	{
		P_I = (left + right) / 2;				// 중간값, 만약 홀수인경우 내림값으로 나누기위치값 산출
	}

	newPI = _partition(array, size, left, right, P_I, order);


	// 이렇게 왼쪽, 오른쪽 순서대로 작은덩이 → 큰덩이
	if (left < (newPI - 1))									// 이제 newPI기준으로 왼쪽부분
	{
		_quicksort(array, size, left, newPI - 1, order);
		// 다시 newPI를 산출하면서 크기정렬을 쭉해준다.
	}
	if ((newPI + 1) < right)								// 다음, 왼쪽이 quickSort를 진행후, newPI기준 오른쪽 부분
	{
		_quicksort(array, size, newPI + 1, right, order);
		// 오른쪽으로 newPI산출및 크기순으로 정렬해준다.
	}
}
template<typename V>
int _partition(V* array, int size, int left, int right, int PivotIndex, SortingOrder order)
{
	int newPI;
	V PivotValue, temp;							// PivotValue = 바꾸는 변수

	PivotValue = array[PivotIndex];
	array[PivotIndex] = array[right];
	array[right] = PivotValue;
	// 맨 처음 PivotIndex에 있던 값을 맨 오른쪽(혹은 P_I-1위치에 있는 값)과 바꾼다

	newPI = left;						// 이제 새로운 피벗위치를 설정해주는데 초기값은 맨 왼쪽(혹은 P_I + 1위치)으로 설정
	for (int i = left; i <= right - 1; i++)
		// 맨뒤로 가게된 PivotValue는 빼고 나머지 배열들을 범위로 잡는다.
	{
		// 오름차순
		if (order == INCREASING)
		{
			if (array[i] <= PivotValue)							//만약 맨뒤로 간 PivotValue보다 값이 작다면
			{
				temp = array[i];
				array[i] = array[newPI];
				array[newPI] = temp;							// 현재(i)위치에 있는 값을 newPI에 있는 값과와 바꿔준다.
				newPI += 1;
			}
		}
		// 내림차순
		else
		{
			if (array[i] > PivotValue)							//만약 맨뒤로 간 PivotValue보다 값이 작다면
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
template<typename V>
inline V& T_Array<V>::operator[](int index)
{
	// 인덱스 번호가 유효하면 값 반환
	if (isValidIndex(index))
		return t_array[index];
}

#endif // !T_ARRAY_H