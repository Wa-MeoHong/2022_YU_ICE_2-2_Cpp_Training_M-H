#ifndef TA_ENTRY_H
#define TA_ENTRY_H

#include <iostream>
#include <iomanip>
#include <string>
#include "T_Entry.h"

using namespace std;

// 정렬 방향 ( 오름차순, 내림차순 )
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
	void reserve(int new_capacity);					// 더 큰 배열을 생성
	void insert(int i, T_Entry<K, V>& element);		// 힙에 데이터를 집어넣음
	void remove(int i);								// 데이터 삭제
	void set(int i, T_Entry<K, V>& element);		// 안에다가 데이터 세팅

	// getter
	string Name() { return name; }					// name 반환
	int Size() { return num_elements; }				// 현재 든 요소의 개수 반환
	bool empty() { return num_elements == 0; }		// 든 요소가 비어있는지 확인
	T_Entry<K, V>& at(int i);						// i번째 있는 데이터 반환 (pointing)
	T_Entry<K, V> Min(int begin, int end);			// 배열의 Min값 반환
	T_Entry<K, V> Max(int begin, int end);			// 배열의 Max값 반환

	// member functions
	void shuffle();									// Shuffling 
	int sequential_search(T_Entry<K, V> search_key);	// 순차 탐색
	int binary_search(T_Entry<K, V> search_key);		// 이진 탐색
	void selection_sort(SortDirection sd);				// 선택정렬
	void quick_sort(SortDirection sd);					// 퀵 정렬
	void fprint(ostream ostr, int elements_per_line);	// 출력함수 1
	void fprintSample(ostream ostr, int elements_per_line, int num_sample_lines);	// 출력함수 2
	bool isValidIndex(int i);
	// operator overloading ( 배열연산자 [] )
	T_Entry<K, V>& operator[] (int index) { return t_GA[index]; }			// 배열연산자 []
	

protected:
	T_Entry<K, V>* t_GA;		// T_Entry 배열
	int num_elements;			// 배열안 요소의 개수
	int capacity;				// 배열의 용량
	string name;				// 배열의 이름

};

template<typename K, typename V>
inline void _quick_sort(T_Entry<K, V>* Array, int Size, int left, int right, SortDirection sd);
// 퀵정렬 본 함수
template<typename K, typename V>
inline void _partition(T_Entry<K, V>* Array, int Size, int left, int right, int PivotIndex, SortDirection sd);
// 파티션 나누기 함수 

/*				constructor ( 생성자 )
		1. n, nm만 인수를 받는 constructor		*/
template<typename K, typename V>
inline TA_Entry<K, V>::TA_Entry(int n, string nm)
	:  capacity(n), name(nm)
{
	num_elements = 0;
	t_GA = new T_Entry<K, V>[capacity];
}

/*			destructor ( 소멸자 )			*/
template<typename K, typename V>
inline TA_Entry<K, V>::~TA_Entry()
{
	if (t_GA != NULL)
		delete t_GA;					// 동적할당한 t_GA를 할당 해제
}		

/*				getter, setter ( 멤버 함수 중, getter, setter )	
		1. reverse(new_capacity) ( 새로운 용량의 배열로 재할당 ) 
		2. insert(i, element) ( 새로운 원소를 i번째에 삽입 )
		3. remove(i)	( i번째 원소를 삭제 )
		4. set(i, element) ( i번째 원소를 element값으로 변경 )
		5. at(i)		( i번째 원소를 반환함 )			*/
template<typename K, typename V>
inline void TA_Entry<K, V>::reserve(int new_capacity)		// 새로운 용량의 배열을 재할당 하는 함수
{
	if (this->Size() < this->capacity)
		return;					// 아직 용량이 충분하므로 할 필요가 없다
	
	T_Entry* oldArray = this->t_GA;			// 새로운 배열을 만들기 위해 오래된 배열을 옮김
	this->t_GA = new T_Entry<K, V>[new_capacity];		// 새로운 배열 동적할당
	for (int i = 0; i < this->Size(); i++)				// 새로운 배열에 기존의 값을 옮김 
	{
		this->t_GA[i] = oldArray[i];			// 대입
	}
	capacity = new_capacity;			// 새로운 용량 대입
	delete oldArray;
}
template<typename K, typename V>
inline void TA_Entry<K, V>::insert(int i, T_Entry<K, V>& element) // i번째에 원소를 집어넣음
{
	// 먼저, num_elements가 capacity를 넘어섰는가? 
	// 넘어섰다면 2배의 용량으로 새롭게 배열을 재할당한다.
	if (this->Size() >= this->capacity)
	{
		int new_capa = 2 * capacity;		// 2배의 용량
		this->reserve(new_capa);			// reserve로 새롭게 재생산
	}

	if (this->isValidIndex(i))				// i가 유효한 값인지 확인
	{
		// i번째에 값을 집어넣기 위해, 기존의 i번째부터 마지막까지는 
		// 전부 한칸씩 뒤로 밀어내고, i번째에 추가한다.
		for (int j = this->Size() - 1; j >= i; i--)
		{
			t_GA[j + 1] = t_GA[j];			// 한칸씩 뒤로 민다.
		}
		t_GA[i] = element;					// i번째에 값을 넣고
		num_elements++;						// num_elements를 1개 더한다.
	}
}
template<typename K, typename V>
inline void TA_Entry<K, V>::remove(int i)		// i번째의 값을 삭제함
{
	// 먼저 값을 없애준다. 
	if (this->isValidIndex(i))				// 인덱스 번호 유효성검사 후
	{
		// i번째값 까지 이후의 값들을 전부 당겨서 i번째 값을 없앰
		for (int j = i + 1; i < this->Size(); i++)
		{
			t_GA[i - 1] = t_GA[i];
		}
		num_elements--;						// num_elements -1 함
	}

	// 만약 num_elements의 수가 기존 용량의 절반 이하라면
	if (this->Size() < (capacity / 2))
	{
		int new_capa = capacity / 2;
		this->reserve(new_capa);			// 새롭게 배열을 재생성
	}
}
template<typename K, typename V>
inline void TA_Entry<K, V>::set(int i, T_Entry<K, V>& element) // i번째의 값을 element로 바꿈
{
	// 만약 번호가 유효한 번호라면 값을 변경
	if (this->isValidIndex(i))
	{
		t_GA[i] = element;
	}
	else
		return 0;					// 아니면 0을 반환
}
template<typename K, typename V>
inline T_Entry<K, V>& TA_Entry<K, V>::at(int i)	// 배열의 i번째 값을 반환
{
	// 만약 유효성 검사를 통과했다면 t_GA[i]를 반환, 아니면 NULL값 반환
	if (this->isValidIndex(i))
		return t_GA[i];
	else
		return NULL;
}

/*					member funtions ( 멤버 함수 )
		1. Min(begin, end) ( begin, end 사이에서 값이 가장 작은 값을 반환 ) 
		2. Max(begin, end) ( begin, end 사이에서 값이 가장 큰 값을 반환 ) 
		3. shuffle() ( 배열의 값을 랜덤으로 섞음 )
		4. sequential_search(search_key) ( 키를 순차탐색함 )
		5. binary_search(search_key) ( 키를 이진탐색함 )
		6. selection_sort(sd) ( 선택정렬, 오름/내림차순 구분 )
		7. quick_sort(sd) ( 퀵정렬 ) 
		8. 9. _quick_sort(~), _partition(~) ( 퀵정렬 본함수, 파티션 함수 )
		10. 11. fprint(), fprintsample() ( 배열 출력 함수, 배열 출력 생략 함수 )
		12. isValidIndex(i) ( 인덱스 번호 유효성 검사 )			*/
template<typename K, typename V>
inline T_Entry<K, V> TA_Entry<K, V>::Min(int begin, int end)		// 최소값
{
	// 최소값 초기값 설정
	T_Entry<K, V>& minValue = this->t_GA[begin];

	// begin + 1부터 end까지 값을 대조해가며 최소값을 찾음 ( 여기서는 우선순위로 따짐 )
	for (int i = begin + 1; i < end; i++)
	{
		if (minValue > this->t_GA[i])
			minValue = this->t_GA[i];
	}

	return minValue;		// 최소값 반환
}
template<typename K, typename V>
inline T_Entry<K, V> TA_Entry<K, V>::Max(int begin, int end)		// 최대값
{
	// 최대값 초기값 설정
	T_Entry<K, V>& maxValue = this->t_GA[begin];

	// begin + 1부터 end까지 값을 대조해가며 최대값을 찾음 ( 여기서는 우선순위로 따짐 )
	for (int i = begin + 1; i < end; i++)
	{
		if (maxValue < this->t_GA[i])
			maxValue = this->t_GA[i];
	}

	return maxValue;		// 최대값 반환
}
template<typename K, typename V>
inline void TA_Entry<K, V>::shuffle()
{
	srand((unsigned int)time(NULL));				// 시간으로 시드 생성
	int index1 = 0, index2 = 0;
	int count = 0;
	T_Entry<K, V> temp;

	while (count != num_elements)
	{
		// 현재 많은 값을 반환하진 않으므로 rand()만으로 충분할 것
		index1 = ((rand() << 15) | (rand())) % num_elements;
		index2 = ((rand() << 15) | (rand())) % num_elements;

		// swaping 
		temp = this->t_GA[index1];
		this->t_GA[index1] = this->t_GA[index2];
		this->t_GA[index2] = temp;

		count++;				// 카운트 업
	} 
}
template<typename K, typename V>
inline int TA_Entry<K, V>::sequential_search(T_Entry<K, V> search_key)
{
	// if t_GA[i] == search_key인 경우, i를 반환, 아니면 -1을 반환
	for (int i = 0; i < this->Size(); i++)
	{
		if (search_key == this->t_GA[i])
			return i;
	}
	return -1;		// fail to searching
}
template<typename K, typename V>
inline int TA_Entry<K, V>::binary_search(T_Entry<K, V> search_key)		// 이진탐색
{
	int low = 0, high = this->Size()-1, mid = 0;
	int loop = 0;
	
	while (low >= high)
	{
		mid = (low + high) / 2;		// mid값은 중간이 계속 바뀌기 때문에 계속 갱신
		if (this->t_GA[mid] == search_key)		// 만약 중앙값이 search_key와 같다면, mid를 반환
			return mid;
		if (this->t_GA[mid] > search_key)		// 중앙값보다 크다면 low를 mid + 1로 새로 갱신
			low = mid + 1;
		else
			high = mid - 1;						// 중앙값보다 작다면 high를 mid - 1로 갱신

		loop++;		// loop counting 
	}	

	return -1;		// fail to searching
	
}
template<typename K, typename V>
inline void TA_Entry<K, V>::selection_sort(SortDirection sd)
{
	T_Entry<K, V> compareValue;		// 비교할 값
	int compareindex;				// 비교할 값 인덱스

	for (int i = 0; i < this->Size() - 1; i++)
	{
		if (sd == INCREASING)			// 오름차순
		{
			compareindex = i; compareValue = this->t_GA[i];	// 비교할 값, 인덱스번호 초기값 설정
			for (int j = i; j < this->Size(); j++)
			{
				if (compareValue > this->t_GA[j])			// 만약 비교한 값이 더 작다면
				{
					compareValue = this->t_GA[j];			// 최소값 갱신
					compareindex = j;						// 최소값 인덱스 갱신
				}
			}
		}

		else							// 내림차순
		{
			compareindex = i; compareValue = this->t_GA[i];	// 비교할 값, 인덱스 번호 초기화
			for (int j = i; j < this->Size(); j++)
			{
				if (compareValue < this->t_GA[j])			// 비교한 값이 더 크다면
				{
					compareValue = this->t_GA[j];			// 최대값 갱신
					compareindex = j;						// 최대값 인덱스 갱신
				}
			}
		}

		// swaping, temp는 필요없음 ( compareValue가 temp역할 중 )
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
	// 퀵정렬 본 함수
	int P_I = 0, newPI = 0;

	if (left >= right)				// 만약 left가 right 이상이라면, newPI반환 중지함
		return;

	// 아니라면 P_I를 설정 한 후, newPI를 구한다. ( P_I를 기준으로 큰값, 작은값 분류 후, 새롭게 중앙값을 선정
	else if (left < right)
		P_I = (left + right) / 2;

	newPI = _partition(Array, Size, left, right, P_I, sd);

	if (left < (newPI - 1))
		// 분류된 값 중, 왼쪽배열을 먼저 정렬
		_quick_sort(Array, Size, left, newPI - 1, sd);
		// newPI를 산출하면서 다시 크기대로 분류
	if ((newPI + 1) < right)
		// 그 후, 오른쪽배열 정렬
		_quick_sort(Array, Size, newPI + 1, right, sd);
}
template<typename K, typename V>
inline int _partition(T_Entry<K, V>* Array, int Size, int left, int right, int PivotIndex, SortDirection sd)
{
	int newPI = 0;
	T_Entry<K, V> PivotValue, temp;

	// 먼저, PivotValue를 배열의 가장 우측의 값과 바꾼다.
	PivotValue = Array[PivotIndex];
	Array[PivotIndex] = Array[right];
	Array[right] = PivotValue;

	// newPI 초기값 설정 = left
	newPI = left;
	for (int i = left; i < right; i++)
	{
		// 오름차순일 경우, 작은것이 왼쪽, 큰것이 오른쪽
		if (sd == INCREASING)
		{
			if (Array[i] <= PivotValue)		// 만약 PivotValue보다 작거나 같으면
			{
				// newPI의 값과 자리를 바꾼다.
				temp = Array[i];
				Array[i] = Array[newPI];
				Array[newPI] = temp;
				newPI += 1;			// 그리고 newPI의 값을 갱신
			}
		}
		else
		{
			if (Array[i] > PivotValue)		// 만약 PivotValue보다 크다면
			{
				// newPI의 값과 자리를 바꾼다.
				temp = Array[i];
				Array[i] = Array[newPI];
				Array[newPI] = temp;
				newPI += 1;			// 그리고 newPI의 값을 갱신
			}
		}
	}

	// 이제 처음 PivotValue를 기준으로 왼쪽은 PivotValue보다 작은 값이, 오른쪽은 큰 값으로 분류됨 
	// 오름차순 기준
	// 가장 오른쪽으로 간 PivotValue를 원위치시킴
	PivotValue = Array[right];
	Array[right] = Array[newPI];
	Array[newPI] = PivotValue;

	return newPI;
}
template<typename K, typename V>		// 파일 출력
inline void TA_Entry<K, V>::fprint(ostream ostr, int elements_per_line)
{
	// num_lines = 한줄당 ele~개만큼 몇 줄을 출력하는지?
	int num_lines = (this->Size() / elements_per_line) + 1;

	// 2중 반복문을 통한 출력
	for (int i = 0; i < num_lines; i++)
	{
		// 한 줄당 ele~개, 띄어쓰기로 구분, 만약 다 출력하고 나면 빈 부분은 없는 상태로 출력
		for (int j = 0; j < elements_per_line; j++)
		{
			ostr << setw(10) << this->t_GA[10 * i + j] << " ";
		}
		ostr << endl;		// 마지막은 endl로
	}
	ostr << endl;
	// print TA_Entry array 
}
template<typename K, typename V>		// 파일 출력 (n줄만 출력후 나머지 생략)
inline void TA_Entry<K, V>::fprintSample(ostream ostr, int elements_per_line, int num_sample_lines)
{
	//int lastIndexs = 0;						// 생략 후, 남는 인덱스 번호들 중 첫째

	//// 처음부분 출력
	//for (int i = 0; i < num_sample_lines; i++)
	//{
	//	for (int j = 0; j < elements_per_line; j++)
	//	{
	//		ostr << setw(10) << this->t_GA[elements_per_line * i + j] << " ";
	//	}
	//	ostr << endl;
	//}
	//// 생략
	//ostr << " . . . . . . " << endl;
	//// lastIndex를 산출
	//lastIndexs = this->Size() - (elements_per_line * (num_sample_lines - 1) + (this->Size() % elements_per_line) + 1);

	//// 생략 후, 남는 부분 출력
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
	// 만약 인덱스 번호가 0~capacity-1 범위 내에 있지 않다면 false, 아니면 true
	if (i < 0 || i >= this->capacity)
		return false;
	return true;
}

#endif // !TA_ENTRY_H