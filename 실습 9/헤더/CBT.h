#ifndef CBT_H
#define CBT_H

#include "TA_Entry.h"
#include <iostream>
#include <iomanip>
#include "SimParam.h"

#define CBT_ROOT 1
using namespace std;

template<typename K, typename V>
class CompleteBinaryTree : public TA_Entry<K, V>
{
public:
	// constructor ( 생성자 )
	CompleteBinaryTree(int capa, string nm);				// CBT 초기 생성자

	int add_at_end(T_Entry<K, V>& elem);					// 노드 끝에 elem를 추가함

	// getter 
	T_Entry<K, V>& EndElement() { return this->t_GA[end]; }		// Leap노드 반환
	T_Entry<K, V>& RootElement() { return this->t_GA[CBT_ROOT]; }	// Root노드 반환
	int EndIndex() { return this->end; }					// Leap노드의 인덱스 반환

	// member functions ( 멤버 함수 ) 
	void removeCBTEnd();								// 완전 이진트리의 Leap노드 삭제
	void fprintCBT(ostream& ostr);						// 완전 이진트리 출력
	void fprintCBT_byLevel(ostream& ostr);				// 레벨에 따른 완전이진트리 출력

protected:
	void _printCBT_byLevel(ostream& ostr, int index, int level);		// 완전이진트리 본 출력함수
	int parentIndex(int index) const { return index / 2; }				// 부모노드의 인덱스
	int leftChildIndex(int index) const { return index * 2; }			// 왼쪽 자식노드 인덱스
	int rightChildIndex(int index) const { return index * 2 + 1; }		// 오른쪽 자식노드 인덱스
	bool hasLeftChild(int index) const { return ((index * 2) <= end); }	// 왼쪽자식노드가 있는지? 유효성검사
	bool hasRightChild(int index) const { return ((index * 2 + 1) <= end); } // 오른쪽자식노드가 있는지? 유효성검사
	int end;
};

#endif // !CBT_H

/*					constructor ( 생성자 )					*/
template<typename K, typename V>
inline CompleteBinaryTree<K, V>::CompleteBinaryTree(int capa, string nm)
	: TA_Entry<K, V>(capa, nm)
{
	end = 0;		// empty ( num_elements = 0 )
}

/*				member functions ( 멤버 함수 )
		1. add_at_end(elem) ( 끝에 element를 붙임 )
		2. removeCBTEnd() ( 가장 끝에 있는 노드를 삭제함 )
		3. fprintCBT(ostr) ( CBT를 단순히 배열의 상태로 출력 )
		4. fprintCBT_byLevel(ostr) ( CBT를 레벨형태로 출력 )
		5. _printCBT_byLevel(ostr) ( 본함수)					*/
template<typename K, typename V>
inline int CompleteBinaryTree<K, V>::add_at_end(T_Entry<K, V>& elem)
{
	// 만약 capacity까지 꽉 찼다면 바로 end를 반환.
	if (this->end >= this->capacity)
	{
		cout << this->name << "is Full now !!" << endl;
		return end;
	}
	// 꽉 차지 않았다면 end를 + 1 한 후, elem를 추가한 후 반환한다.
	this->end++;
	this->t_GA[this->end] = elem;

	return end;
}
template<typename K, typename V>
inline void CompleteBinaryTree<K, V>::removeCBTEnd()		// remove end point
{
	// 노드의 end와 num_elements를 줄인다. 
	this->end--;
	this->num_elements--;
}
template<typename K, typename V>
inline void CompleteBinaryTree<K, V>::fprintCBT(ostream& ostr)
{
	// 만약 출력할 CBT 노드가 없으면, 비어있다고 출력
	if (this->end <= 0)
	{
		ostr << this->Name() << "is empty now !!" << endl;
		return;
	}

	// 아니면 하나씩 출력 
	int count = 0;
	for (int i = 1; i <= end; i++)
	{
		if ((i-1) % EVENT_PER_LINE == 0)
			cout << endl;
		ostr << setw(3) << this->t_GA[i];
		count++;
	}
}
template<typename K, typename V>
inline void CompleteBinaryTree<K, V>::fprintCBT_byLevel(ostream& ostr)
{
	// 만약 노드가 없으면 출력하지 않고 탈출
	if (this->end <= 0)
	{
		ostr << "CBT is Empty now !! " << endl;
		return;
	}
	// 출력
	_printCBT_byLevel(ostr, CBT_ROOT, 0);
}
template<typename K, typename V>
inline void CompleteBinaryTree<K, V>::_printCBT_byLevel(ostream& ostr, int index, int level)
{
	int index_child;				// 자식 노드

	// 오른쪽 자식노드가 맨 먼저 나오기 때문에 재귀함수의 구조를 통해 level이 몇인지 계산
	if (this->hasRightChild(index))
	{
		index_child = rightChildIndex(index);
		this->_printCBT_byLevel(ostr, index_child, level + 1);
	}

	// 본 출력 코드
	for (int i = 0; i < level; i++)
	{
		ostr << "\t";
	}
	this->t_GA[index].Print(ostr);
	ostr << endl;

	// 왼쪽 자식 노드 출력 부분. 얘도 재귀를 통해 level을 계산함
	if (this->hasLeftChild(index))
	{
		index_child = leftChildIndex(index);
		this->_printCBT_byLevel(ostr, index_child, level + 1);
	}

}
