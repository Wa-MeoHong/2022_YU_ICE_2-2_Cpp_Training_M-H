#ifndef TRIENODE_H
#define TRIENODE_H

#include <iostream>
#include <iomanip>
#include <string>
#include <list>

#define VALUE_INITIAL_NODE NULL

using namespace std;

template <typename E>
class TrieNode
{
public:
	// constructor 
	TrieNode() {}				// default constructor 
	TrieNode(char k, E v)		// constructor 
		: _key(k), _value(v) 
	{	prev = next = parent = child = NULL;	}

	// setter 
	void SetKey(char k) { _key = k; }
	void SetVal(E v) { _value = v; }
	void SetNext(TrieNode<E>* nxt) { next = nxt; }
	void SetPrev(TrieNode<E>* pv) { prev = pv; }
	void SetParent(TrieNode<E>* pr) { parent = pr; }
	void SetChild(TrieNode<E>* chld) { child = chld; }

	// getter 
	char Key() { return _key; }
	E Val() { return _value; }
	TrieNode<E>* Prev() { return prev; }
	TrieNode<E>* Next() { return next; }
	TrieNode<E>* Parent() { return parent; }
	TrieNode<E>* Child() { return child; }

	// member function
	void _fprint(ostream& ostr, TrieNode<E>* pTN, int indent);
private:
	char _key;
	E _value;

	TrieNode<E>* prev;					// 이전 
	TrieNode<E>* next;					// 이후
	TrieNode<E>* parent;				// 부모
	TrieNode<E>* child;					// 자식

};
template<typename E>
inline void TrieNode<E>::_fprint(ostream& ostr, TrieNode<E>* pTN, int indent)
{
	if (pTN == NULL)		// 만약 노드가 없으면
	{
		ostr << endl;		// 끝내고 탈출
		return;
	}

	// 좌 우로 출력 하게 함(재귀함수 사용)
	else
	{
		ostr << pTN->Key();
		this->_fprint(ostr, pTN->Child(), indent + 1);		// 자식(다음에 올 단어 
		if (pTN->Next() == NULL)
			return;
		for (int i = 0; i < indent; i++)
			ostr << "\t";
		this->_fprint(ostr, pTN->Next(), indent);			// 다음 노드 출력
	}
}

#endif // !TRIENODE_H

