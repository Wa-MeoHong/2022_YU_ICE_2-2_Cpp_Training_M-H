#ifndef T_BST_H
#define T_BST_H

#include <iostream>
#include <iomanip>
#include <string>
#include "T_BSTN.h"
#include "T_Array.h"

using namespace std;

template<typename K, typename V>
class T_BST
{
public:
	// constructor
	T_BST(string nm) : _root(NULL), num_entry(0), name(nm) {}
		// 멤버 초기화 리스트를 통해 간단하게 작성
	
	// destructor
	void clear();											// Binary Search Tree를 삭제

	// getter
	string Name() const { return name; }					// 이름
	int Size() const { return num_entry; }					// 현재 들어있는 노드의 개수
	bool empty() const { return num_entry == 0; }			// 현재 트리가 비어있는가?
	T_BSTN<K, V>* Root() const { return _root; }			// root노드(최상위노드)의 값을 반환
	T_BSTN<K, V>** RootAddr() { return &_root; }		// root노드의 주소 반환
	T_Entry<K, V>* RootEntry() const { return _root->Entry(); }		// root노드의  Entry를 반환
	

	// member functions (interfaces)
	T_BSTN<K, V>* eraseBSTN(T_BSTN<K, V>** pp);				// 노드를 삭제
	void insertinOrder(const T_Entry<K, V> entry);			// 노드를 집어넣음
	void insertAndReBal(T_Entry<K, V> e);					// 노드를 집어넣고 리밸런싱함
	void travelsal_inOrder(T_BSTN<K, V>* p, T_Array<V>& array_value);		// 
	void travelsal_preOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value);
	void travelsal_postOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value);
	T_BSTN<K, V>* searchBSTN(K k);							// Binary Search Tree의 순차탐색
	T_Entry<K, V>& minEntry();								// 엔트리의 최소값
	T_Entry<K, V>& maxEntry();								// 엔트리의 최대값
	void print_with_Depth(ostream& ostr);					// BST의 출력 ( 깊이에 따른 )
	void print_inOrder(ostream& ostr);						// BST의 출력 ( 순서에 따른 )

protected:						// public에 있는 함수들이 실행하는 알고리즘이 담긴 소스들
	T_BSTN<K, V>* _maxBSTN(T_BSTN<K, V>* subRoot);			// maxBSTN
	T_BSTN<K, V>* _minBSTN(T_BSTN<K, V>* subRoot);			// minBSTN
	T_BSTN<K, V>* _insertInOrder(T_BSTN<K, V>** p, T_BSTN<K, V>* prPos, const T_Entry<K, V> e);	// insertInOrder
	T_BSTN<K, V>* _insertAndRebal(T_BSTN<K, V>** ppTN, T_BSTN<K, V>* pPr, T_Entry<K, V> e);		// insertAndRebal
	T_BSTN<K, V>* _rotate_LL(T_BSTN<K, V>* pCurSubRoot);				// 왼쪽-왼쪽 노드의 자리바꾸기 
	T_BSTN<K, V>* _rotate_RR(T_BSTN<K, V>* pCurSubRoot);				// 오른-오른 노드의 자리바꾸기
	T_BSTN<K, V>* _rotate_RL(T_BSTN<K, V>* pCurSubRoot);				// 오른-왼쪽 노드의 자리바꾸기
	T_BSTN<K, V>* _rotate_LR(T_BSTN<K, V>* pCurSubRoot);				// 왼쪽-오른 노드의 자리바꾸기
	int _Height(T_BSTN<K, V>* pTN);							// BST의 높이
	int _HeightDiff(T_BSTN<K, V>* pTN);						// BST의 높이(현재위치?)
	T_BSTN<K, V>* _reBalance(T_BSTN<K, V>** ppTN);			// 리밸런싱 함수
	T_BSTN<K, V>* _searchBSTN(T_BSTN<K, V>* pos, K k);				// BST의 순차탐색 함수
	void _print_with_Depth(T_BSTN<K, V>* pTN, ostream& ostr, int depth);		// 출력 함수
	void _print_inOrder(T_BSTN<K, V>* pTN, ostream& ostr);						// 출력 함수 2

private:
	T_BSTN<K, V>* _root;
	int num_entry;	// number of Nodes
	string name;
};

/*					destructor					*/	
template<typename K, typename V>
inline void T_BST<K, V>::clear()
{
	this->_root = NULL;
	this->num_entry = 0;
}

/*			member functions interface			*/
template<typename K, typename V>
inline T_BSTN<K, V>* T_BST<K, V>::eraseBSTN(T_BSTN<K, V>** pp)		// remove node and rebalanced
{
	T_BSTN<K, V>* newSubRoot;
	T_BSTN<K, V>* tobeErased;

	tobeErased = *pp;
	if (tobeErased == NULL)
		return NULL;

	if ((tobeErased->pLc() == NULL) && (tobeErased->pRc() == NULL))			// 자식노드들이 없다면
		newSubRoot = NULL;

	else if ((tobeErased->pLc() != NULL) && (tobeErased->pRc() == NULL))	// 왼쪽 자식노드만 있다면
	{
		newSubRoot = tobeErased->pLc();										// 지울 노드의 왼쪽노드를 가져와서
		newSubRoot->SetpPr(tobeErased->pPr());								// 지워질 노드의 부모노드와 이어줌
	}
	else if ((tobeErased->pLc() == NULL) && (tobeErased->pRc() != NULL))	// 오른쪽 자식노드만 있다면
	{
		newSubRoot = tobeErased->pRc();										// 지울 노드의 오른쪽노드를 가져와서
		newSubRoot->SetpPr(tobeErased->pPr());								// 지워질 노드의 부모노드와 이어줌
	}
	else
	{
		int h_diff = _HeightDiff(tobeErased);			// 자식노드의 크기를 비교함.

		T_BSTN<K, V>* parDel = tobeErased->pPr();
		T_BSTN<K, V>* lChild = tobeErased->pLc();
		T_BSTN<K, V>* rChild = tobeErased->pRc();
		T_BSTN<K, V>* ioSs = NULL, * rcIoSs, * parIoSs;
		T_BSTN<K, V>* ioPd = NULL, * lcIoPd, * parIoPd;

		if (h_diff > 0)			// 왼쪽 노드 트리가 더 크다면, 지워진 노드를 대체할 노드를 ioPd로 집어넣음
		{
			ioPd = _maxBSTN(lChild);			// 지워진 노드의 왼쪽 자식노드 트리중 가장 큰 값
			lcIoPd = ioPd->pLc();
			parIoPd = ioPd->pPr();
			newSubRoot = ioPd;
			if (ioPd->pPr() != tobeErased)
			{
				newSubRoot->SetpLc(lChild);
				parIoPd->SetpRc(lcIoPd);
				if (lcIoPd != NULL)
					lcIoPd->SetpPr(parIoPd);
			}

			newSubRoot->SetpRc(rChild);
			newSubRoot->SetpPr(tobeErased->pPr());
		}
		else
		{
			ioSs = _minBSTN(rChild); // 지워지는 노드의 오른쪽 자식노드 트리 중 가장 작은 값
			rcIoSs = ioSs->pRc(); parIoSs = ioSs->pPr();
			newSubRoot = ioSs;
			if (ioSs->pPr() != tobeErased)			// 만약 그 노드의 부모노드가 지워야할 노드가 아니라면
			{
				newSubRoot->SetpRc(rChild);			// ioSs의 오른쪽 노드를 지워야할 노드의 오른쪽 자식노드로 설정
				parIoSs->SetpLc(rcIoSs);			// ioSs의 부모노드의 왼쪽자식노드의 값을 ioSs의 오른쪽 자식노드로 설정
				if (rcIoSs != NULL)
					rcIoSs->SetpPr(parIoSs);		// 만약 rcIoSs의 부모노드를 ioSs의 부모노드로 설정
			}
			newSubRoot->SetpLc(lChild);
			newSubRoot->SetpPr(tobeErased->pPr());
		}

		if (lChild != ioPd)
			lChild->SetpPr(newSubRoot);
		if (rChild != ioSs)
			rChild->SetpPr(newSubRoot);
	}
	if (tobeErased == _root)
		_root = newSubRoot;
	num_entry--;
	free(tobeErased);
	*pp = newSubRoot;
	return newSubRoot;
}

		// interface 
				// insert 함수 ( 이진탐색트리에 값을 집어넣음 )
		// 1. 순서에 따른 값 집어넣기
		// 2. 값을 집어넣고 리밸런싱을 함
template<typename K, typename V>
inline void T_BST<K, V>::insertinOrder(const T_Entry<K, V> entry)
{
	_insertInOrder(&_root, NULL, entry);
}
template<typename K, typename V>
inline void T_BST<K, V>::insertAndReBal(T_Entry<K, V> e)
{
	_insertAndRebal(&_root, NULL, e);
}

				// travling BST ( 이진트리탐색을 순회함)
		// 1. 맨아래에서 ROOT노드로 올라가는 inOrder ( 왼쪽이 먼저 )
		// 2. 맨 위에서 LEAF노드로 내려가는 PreOrder ( 왼쪽이 먼저 )
		// 3. 높이에 맞게 찾아보는 PostOrder ( 왼쪽 선행 ) 
template<typename K, typename V>
inline void T_BST<K, V>::travelsal_inOrder(T_BSTN<K, V>* p, T_Array<V>& array_value)
{
	T_BSTN<K, V>* pLc, * pRc;
	T_Entry<K, V> entry;
	V val;
	if (p == NULL)
		return;

	pLc = p->pLc();		pRc = p->pRc();
	travelsal_inOrder(pLc, array_value);	// 재귀
	entry = p->Entry();
	val = entry.Val();			
	array_value.insertBack(val);			// 맨마지막에 노드 하나 삽입	
	travelsal_inOrder(pRc, array_value);	// 다시 재귀 
}
template<typename K, typename V>
inline void T_BST<K, V>::travelsal_preOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value)
{
	T_BSTN<K, V>* pLc, * pRc;
	T_Entry<K, V> entry;
	V val;
	if (pos == NULL)
		return;
	pLc = pos->pLc();		pRc = pos->pRc();

	entry = pos->Entry();
	val = entry.Val();
	array_value.insertBack(val);			// 맨마지막에 노드 하나 삽입

	travelsal_preOrder(pLc, array_value);		// 왼쪽노드에 대해 순회
	travelsal_preOrder(pRc, array_value);		// 오른쪽 노드에 대해 순회

}
template<typename K, typename V>
inline void T_BST<K, V>::travelsal_postOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value)
{
	T_BSTN<K, V>* pLc, * pRc;
	T_Entry<K, V> entry;
	V val;
	if (pos == NULL)
		return;
	pLc = pos->pLc();		pRc = pos->pRc();

	travelsal_postOrder(pLc, array_value);		// 왼쪽 노드에 대해 탐색 
	travelsal_postOrder(pRc, array_value);

	entry = pos->Entry();
	val = entry.Val();
	array_value.insertBack(val);			// 맨마지막에 노드 하나 삽입
}

				// search BSTN ( 이진탐색트리 노드 순차탐색 )
template<typename K, typename V>
inline T_BSTN<K, V>* T_BST<K, V>::searchBSTN( K k)
{
	T_BSTN<K, V>* pEntry;
	pEntry = _searchBSTN(this->_root, k);
	return pEntry;
}

					// 최대 노드, 최소 노드
template<typename K, typename V>
inline T_Entry<K, V>& T_BST<K, V>::minEntry()
{
	T_BSTN<K, V>* pMin;

	pMin = _minBSTN(this->_root);
	return pMin->Entry();
}
template<typename K, typename V>
inline T_Entry<K, V>& T_BST<K, V>::maxEntry()
{
	T_BSTN<K, V>* pMax;

	pMax = _maxBSTN(this->_root);
	return pMax->Entry();
}

				// 출력 함수 인터페이스
		// 1. 깊이에 따른 출력
		// 2. 순서에 따른 출력 
template<typename K, typename V>
inline void T_BST<K, V>::print_with_Depth(ostream& ostr)
{
	T_BSTN<K, V>* root = this->Root();
	if (this->num_entry == 0)
	{
		ostr << this->Name() << " is empty now !!" << endl;
		return;
	}
	_print_with_Depth(this->Root(), ostr, 0);

}
template<typename K, typename V>
inline void T_BST<K, V>::print_inOrder(ostream& ostr)
{
	T_BSTN<K, V>* root = this->Root();
	if (this->num_entry == 0)
	{
		ostr << this->Name() << " is empty now !!" << endl;
		return;
	}
	_print_inOrder(this->Root(), ostr);
}


/*			protected functions			*/

				//	insert function 
		// 1. insertInOrder
		// 2. insertAndRebalance 
template<typename K, typename V>
inline T_BSTN<K, V>* T_BST<K, V>::_insertInOrder(T_BSTN<K, V>** p, T_BSTN<K, V>* prPos, const T_Entry<K, V> e)
{
	T_BSTN<K, V>* newPos, ** pChildPos;
	T_BSTN<K, V>* pos;
	T_Entry<K, V> ent;

	if (p == NULL)
	{
		cout << "Error !! in creation of Binary Search Tree : \n"
			<< " address of the pointer to the Root Node is NULL !! \n";
		exit(-1);
	}

	pos = *p;

	// 만약 받은 노드가 없다면
	if (pos == NULL)
	{
		pos = new T_BSTN<K, V>(e);			// 노드를 동적할당
		if (prPos == NULL)
			this->_root = pos;					// pos가 root노드가 된다. 
		pos->SetpPr(prPos);						// 부모노드로 설정
		*p = pos;
		num_entry++;							// 엔트리의 개수 1개 증가
		return pos;								// 반환
	}

	ent = pos->Entry();
	
	// 받은 노드의 entry가 부모의 entry보다 더 작다면 왼쪽노드에 집어넣음 
	if (e < ent)					
	{
		pChildPos = pos->ppLc();					// 위치는 왼쪽노드 (주소)
		newPos = _insertInOrder(pChildPos, pos, e);	// 한번더 체크 ( 더 밑으로 이어지는지 )
		if (newPos != NULL)
			pos->SetpLc(newPos);					// 만약 더이상 밑으로 내려갈 노드가 없다면 그 노드를 왼쪽으로 세팅
		return NULL;								// 반환
	}
	
	// 받은 노드의 entry가 부모의 entry보다 더 크다면 왼쪽노드에 집어넣음 
	else if (e >= ent)
	{
		pChildPos = pos->ppRc();					// 위치는 오른쪽노드 (주소)
		newPos = _insertInOrder(pChildPos, pos, e);		// 체크 ( 더 밑으로 이어지는가 ) 
		if (newPos != NULL)
			pos->SetpRc(newPos);					// 더이상 밑으로 내려가지 않는다면 오른쪽 노드에 세팅함
		return NULL;								// 반환
	}
}
template<typename K, typename V>
inline T_BSTN<K, V>* T_BST<K, V>::_insertAndRebal(T_BSTN<K, V>** ppTN, T_BSTN<K, V>* pPr, T_Entry<K, V> e)
{
	T_BSTN<K, V>* pTN = NULL, ** ppLc = NULL, ** ppRc = NULL;
	T_Entry<K, V> bstn_entry;

	// 현재 외부 노드를 새 트리노드에 연결함
	if (*ppTN == NULL)
	{
		pTN = new T_BSTN<K, V>(e);
		*ppTN = pTN;
		if (pPr != NULL)
			pTN->SetpPr(pPr);				// 부모노드 설정
		(*ppTN)->SetpLc(NULL);				// 자식노드는 없으므로 NULL로 설정
		(*ppTN)->SetpRc(NULL);
		num_entry++;
		return *ppTN;						// 넣은 노드 반환
	}


	bstn_entry = (*ppTN)->Entry();				// 엔트리를 가져옴
	if (e < bstn_entry)
	{
		ppLc = (*ppTN)->ppLc();					// 만약 부모노드보다 엔트리값이 더 작다면 왼쪽 노드 주소를 가져오고 
		pTN = _insertAndRebal(ppLc, *ppTN, e);	// 더 밑으로 내려가면서 계속 넣을 곳을 찾는다
		if (ppTN != NULL)						// 만약 더 내려갈 곳이 없다면 
		{
			(*ppTN)->SetpLc(pTN);				// 노드를 넣음 
			*ppTN = _reBalance(ppTN);			// 위치 리밸런싱 한다.
		}
	}
	else
	{
		ppRc = (*ppTN)->ppRc();					// 부모노드 엔트리 값보다 크거나 같으면 오른쪽 노드 주소를 가져옴
		pTN = _insertAndRebal(ppRc, *ppTN, e);	// 계속 밑으로 내려간다.
		if (ppTN != NULL)						// 더 내려갈 곳이 없다면 
		{
			(*ppTN)->SetpRc(pTN);				// 오른쪽 노등에 세팅하고
			*ppTN = _reBalance(ppTN);			// 리밸런싱 함
		}
	}
	return *ppTN;
}


				// min, max
template<typename K, typename V>
inline T_BSTN<K, V>* T_BST<K, V>::_minBSTN(T_BSTN<K, V>* subRoot)			// 최소값 반환
{
	T_BSTN<K, V>* pos;

	if ((subRoot == NULL) || (subRoot->pLc() == NULL))
		return subRoot;							// 만약 subRoot가 없거나 아니면 subRoot의 왼쪽노드 값이 없다면 subRoot를 반환
	pos = subRoot;
	while (pos->pLc() != NULL)
		pos = pos->pLc();						// 그렇지않다면 subRoot의 왼쪽노드가 NULL이 나올때까지, 계속 pos를 갱신하면서 최소값을 찾는다.
	
	return pos;						// pos 반환	
}
template<typename K, typename V>
inline T_BSTN<K, V>* T_BST<K, V>::_maxBSTN(T_BSTN<K, V>* subRoot)			// 최대값 반환
{
	T_BSTN<K, V>* pos;

	if ((subRoot == NULL) || (subRoot->pRc() == NULL))
		return subRoot;							// 만약 subRoot가 없거나 아니면 subRoot의 오른쪽 노드 값이 없다면 subRoot를 반환
	pos = subRoot;
	while (pos->pRc() != NULL)
		pos = pos->pRc();						// 그렇지않다면 subRoot의 오른쪽 노드가 NULL이 나올때까지, 계속 pos를 갱신하면서 최대값을 찾는다.

	return pos;						// pos 반환	
}

					// rebalance
template<typename K, typename V>
inline T_BSTN<K, V>* T_BST<K, V>::_reBalance(T_BSTN<K, V>** ppTN)
{
	int heightDiff = 0;

	heightDiff = _HeightDiff(*ppTN);				// 높이 차이를 계산
	if (heightDiff > 1)								// 만약 1보다 크다면 
	{
		if (_HeightDiff((*ppTN)->pLc()) > 0)		// 왼쪽노드도 계산해서 높이차이가 양수라면
			*ppTN = _rotate_LL(*ppTN);				// 왼-왼 로테이션
		else
			*ppTN = _rotate_LR(*ppTN);				// 아니면 왼-오 로테이션
	}
	else if (heightDiff < -1)						// -1보다 작다면 오른쪽이다.
	{
		if (_HeightDiff((*ppTN)->pRc()) < 0)		// 오른쪽 자식노드도 계산하여 차이가 음수라면
			*ppTN = _rotate_RR(*ppTN);				// 오-오 로테이션
		else
			*ppTN = _rotate_RL(*ppTN);				// 오-왼 로테이션
	}
	return *ppTN;									// 반환
}
template<typename K, typename V>
inline T_BSTN<K, V>* T_BST<K, V>::_rotate_LL(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pNewSubRoot, * pBR, * pCurParent;

	pCurParent = pCurSubRoot->pPr();
	pNewSubRoot = pCurSubRoot->pLc();
	pBR = pNewSubRoot->pRc();
	
	pCurSubRoot->SetpLc(pBR);
	if (pBR != NULL)
		pBR->SetpPr(pCurSubRoot);
	pNewSubRoot->SetpRc(pCurSubRoot);
	pNewSubRoot->SetpPr(pCurParent);
	pCurSubRoot->SetpPr(pNewSubRoot);

	return pNewSubRoot;
}
template<typename K, typename V>
inline T_BSTN<K, V>* T_BST<K, V>::_rotate_RR(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pNewSubRoot, * pBL, * pCurParent;

	pCurParent = pCurSubRoot->pPr();
	pNewSubRoot = pCurSubRoot->pRc();
	pBL = pNewSubRoot->pLc();

	pCurSubRoot->SetpRc(pBL);
	if (pBL != NULL)
		pBL->SetpPr(pCurSubRoot);
	pNewSubRoot->SetpLc(pCurSubRoot);
	pNewSubRoot->SetpPr(pCurParent);
	pCurSubRoot->SetpPr(pNewSubRoot);

	return pNewSubRoot;
}
template<typename K, typename V>
inline T_BSTN<K, V>* T_BST<K, V>::_rotate_RL(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pSubRoot, * pNewSubRoot, * pCurParent;
	T_BSTN<K, V>* pA, * pB, * pC, * pBL, * pBR;

	pA = pCurSubRoot;
	pCurParent = pCurSubRoot->pPr();
	pC = pA->pRc(); pB = pC->pLc();
	pBL = pB->pLc(); pBR = pB->pRc();

	pSubRoot = _rotate_LL(pC);
	pCurSubRoot->SetpRc(pSubRoot);
	pNewSubRoot = _rotate_RR(pA);

	pNewSubRoot->SetpPr(pCurParent);
	pA->SetpPr(pNewSubRoot); pC->SetpPr(pNewSubRoot);
	if (pBL != NULL)
		pBL->SetpPr(pA);
	if (pBR != NULL)
		pBR->SetpPr(pC);

	return pNewSubRoot;
}
template<typename K, typename V>
inline T_BSTN<K, V>* T_BST<K, V>::_rotate_LR(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pSubRoot, * pNewSubRoot, * pCurParent;
	T_BSTN<K, V>* pA, * pB, * pC, * pBL, * pBR;

	pC = pCurSubRoot;
	pCurParent = pCurSubRoot->pPr();
	pA = pC->pLc(); pB = pA->pRc();
	pBL = pB->pLc(); pBR = pB->pRc();

	pSubRoot = _rotate_RR(pA);
	pCurSubRoot->SetpLc(pSubRoot);
	pNewSubRoot = _rotate_LL(pC);

	pNewSubRoot->SetpPr(pCurParent);
	pA->SetpPr(pNewSubRoot); pC->SetpPr(pNewSubRoot);
	if (pBL != NULL)
		pBL->SetpPr(pA);
	if (pBR != NULL)
		pBR->SetpPr(pC);

	return pNewSubRoot;

}

template<typename K, typename V>
inline int T_BST<K, V>::_Height(T_BSTN<K, V>* pTN)
{
	int height = 0, h_Lc = 0, h_Rc = 0;

	if (pTN != NULL)
	{
		h_Lc = _Height(pTN->pLc()); h_Rc = _Height(pTN->pRc());		// 재귀를 통해 자식노드들의 위치를 판별
		if (h_Lc > h_Rc)
			height = 1 + h_Lc;
		else
			height = 1 + h_Rc;
	}
	// 왼쪽, 오른쪽 중 가장 더 밑으로 내려간 노드를 기준으로 + 1한다.
	return height;
}
template<typename K, typename V>
inline int T_BST<K, V>::_HeightDiff(T_BSTN<K, V>* pTN)
{
	int h_diff = 0;
	if (pTN == NULL)
		return 0;
	h_diff = _Height(pTN->pLc()) - _Height(pTN->pRc());

	// 구한 왼쪽 노드의 높이와 오른쪽 노드의 높이를 구해 차를 계산
	return h_diff;
}

// searching function
template<typename K, typename V>
inline T_BSTN<K, V>* T_BST<K, V>::_searchBSTN(T_BSTN<K, V>* pos, K k)
{
	K ent_k;
	T_BSTN<K, V>* pos_result = NULL;

	if (pos == NULL)
		return NULL;

	ent_k = pos->getKey();							// ent_k 의 값은 노드의 entry의 Key값을 가져옴
	if (ent_k == k)
		pos_result = pos;							// 찾는 키값이 맞으면 바로 반환하게 값을 저장
	else if (ent_k > k)
		pos_result = _searchBSTN(pos->pLc(), k);	// 만약 key 값이 더 작으면 왼쪽 노드를 찾음
	else if (ent_k < k)
		pos_result = _searchBSTN(pos->pRc(), k);	// 만약 키값이 더 크면 오른쪽 노드를 찾음

	return pos_result;

}

// print function 
template<typename K, typename V>
inline void T_BST<K, V>::_print_with_Depth(T_BSTN<K, V>* pTN, ostream& ostr, int depth)
{
	T_BSTN<K, V>* pRc, * pLc;
	T_Entry<K, V> pEntry;

	if ((pRc = pTN->pRc()) != NULL)
		_print_with_Depth(pRc, ostr, depth + 1);				// 오른쪽 노드 출력
	for (int i = 0; i < depth; i++)
	{
		ostr << "\t\t";										// 탭 키로 간격 벌리기
	}
	ostr << pTN->Entry() << endl;
	if ((pLc = pTN->pLc() ) != NULL)							// 왼쪽 노드 출력
		_print_with_Depth(pLc, ostr, depth + 1);
}
template<typename K, typename V>
inline void T_BST<K, V>::_print_inOrder(T_BSTN<K, V>* pTN, ostream& ostr)
{
	T_BSTN<K, V>* pRc, * pLc;
	if ((pLc = pTN->pLc()) != NULL)
		_print_inOrder(pLc, ostr);						// 왼쪽 노드 출력
	ostr << pTN->Entry() << endl;						// 중간 노드 출력
	if ((pRc = pTN->pRc()) != NULL)
		_print_inOrder(pRc, ostr);						// 오른쪽 노드 출력
}


#endif // !T_BST_H


