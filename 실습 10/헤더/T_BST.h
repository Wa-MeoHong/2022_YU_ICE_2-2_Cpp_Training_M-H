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
		// ��� �ʱ�ȭ ����Ʈ�� ���� �����ϰ� �ۼ�
	
	// destructor
	void clear();											// Binary Search Tree�� ����

	// getter
	string Name() const { return name; }					// �̸�
	int Size() const { return num_entry; }					// ���� ����ִ� ����� ����
	bool empty() const { return num_entry == 0; }			// ���� Ʈ���� ����ִ°�?
	T_BSTN<K, V>* Root() const { return _root; }			// root���(�ֻ������)�� ���� ��ȯ
	T_BSTN<K, V>** RootAddr() { return &_root; }		// root����� �ּ� ��ȯ
	T_Entry<K, V>* RootEntry() const { return _root->Entry(); }		// root�����  Entry�� ��ȯ
	

	// member functions (interfaces)
	T_BSTN<K, V>* eraseBSTN(T_BSTN<K, V>** pp);				// ��带 ����
	void insertinOrder(const T_Entry<K, V> entry);			// ��带 �������
	void insertAndReBal(T_Entry<K, V> e);					// ��带 ����ְ� ���뷱����
	void travelsal_inOrder(T_BSTN<K, V>* p, T_Array<V>& array_value);		// 
	void travelsal_preOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value);
	void travelsal_postOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value);
	T_BSTN<K, V>* searchBSTN(K k);							// Binary Search Tree�� ����Ž��
	T_Entry<K, V>& minEntry();								// ��Ʈ���� �ּҰ�
	T_Entry<K, V>& maxEntry();								// ��Ʈ���� �ִ밪
	void print_with_Depth(ostream& ostr);					// BST�� ��� ( ���̿� ���� )
	void print_inOrder(ostream& ostr);						// BST�� ��� ( ������ ���� )

protected:						// public�� �ִ� �Լ����� �����ϴ� �˰����� ��� �ҽ���
	T_BSTN<K, V>* _maxBSTN(T_BSTN<K, V>* subRoot);			// maxBSTN
	T_BSTN<K, V>* _minBSTN(T_BSTN<K, V>* subRoot);			// minBSTN
	T_BSTN<K, V>* _insertInOrder(T_BSTN<K, V>** p, T_BSTN<K, V>* prPos, const T_Entry<K, V> e);	// insertInOrder
	T_BSTN<K, V>* _insertAndRebal(T_BSTN<K, V>** ppTN, T_BSTN<K, V>* pPr, T_Entry<K, V> e);		// insertAndRebal
	T_BSTN<K, V>* _rotate_LL(T_BSTN<K, V>* pCurSubRoot);				// ����-���� ����� �ڸ��ٲٱ� 
	T_BSTN<K, V>* _rotate_RR(T_BSTN<K, V>* pCurSubRoot);				// ����-���� ����� �ڸ��ٲٱ�
	T_BSTN<K, V>* _rotate_RL(T_BSTN<K, V>* pCurSubRoot);				// ����-���� ����� �ڸ��ٲٱ�
	T_BSTN<K, V>* _rotate_LR(T_BSTN<K, V>* pCurSubRoot);				// ����-���� ����� �ڸ��ٲٱ�
	int _Height(T_BSTN<K, V>* pTN);							// BST�� ����
	int _HeightDiff(T_BSTN<K, V>* pTN);						// BST�� ����(������ġ?)
	T_BSTN<K, V>* _reBalance(T_BSTN<K, V>** ppTN);			// ���뷱�� �Լ�
	T_BSTN<K, V>* _searchBSTN(T_BSTN<K, V>* pos, K k);				// BST�� ����Ž�� �Լ�
	void _print_with_Depth(T_BSTN<K, V>* pTN, ostream& ostr, int depth);		// ��� �Լ�
	void _print_inOrder(T_BSTN<K, V>* pTN, ostream& ostr);						// ��� �Լ� 2

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

	if ((tobeErased->pLc() == NULL) && (tobeErased->pRc() == NULL))			// �ڽĳ����� ���ٸ�
		newSubRoot = NULL;

	else if ((tobeErased->pLc() != NULL) && (tobeErased->pRc() == NULL))	// ���� �ڽĳ�常 �ִٸ�
	{
		newSubRoot = tobeErased->pLc();										// ���� ����� ���ʳ�带 �����ͼ�
		newSubRoot->SetpPr(tobeErased->pPr());								// ������ ����� �θ���� �̾���
	}
	else if ((tobeErased->pLc() == NULL) && (tobeErased->pRc() != NULL))	// ������ �ڽĳ�常 �ִٸ�
	{
		newSubRoot = tobeErased->pRc();										// ���� ����� �����ʳ�带 �����ͼ�
		newSubRoot->SetpPr(tobeErased->pPr());								// ������ ����� �θ���� �̾���
	}
	else
	{
		int h_diff = _HeightDiff(tobeErased);			// �ڽĳ���� ũ�⸦ ����.

		T_BSTN<K, V>* parDel = tobeErased->pPr();
		T_BSTN<K, V>* lChild = tobeErased->pLc();
		T_BSTN<K, V>* rChild = tobeErased->pRc();
		T_BSTN<K, V>* ioSs = NULL, * rcIoSs, * parIoSs;
		T_BSTN<K, V>* ioPd = NULL, * lcIoPd, * parIoPd;

		if (h_diff > 0)			// ���� ��� Ʈ���� �� ũ�ٸ�, ������ ��带 ��ü�� ��带 ioPd�� �������
		{
			ioPd = _maxBSTN(lChild);			// ������ ����� ���� �ڽĳ�� Ʈ���� ���� ū ��
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
			ioSs = _minBSTN(rChild); // �������� ����� ������ �ڽĳ�� Ʈ�� �� ���� ���� ��
			rcIoSs = ioSs->pRc(); parIoSs = ioSs->pPr();
			newSubRoot = ioSs;
			if (ioSs->pPr() != tobeErased)			// ���� �� ����� �θ��尡 �������� ��尡 �ƴ϶��
			{
				newSubRoot->SetpRc(rChild);			// ioSs�� ������ ��带 �������� ����� ������ �ڽĳ��� ����
				parIoSs->SetpLc(rcIoSs);			// ioSs�� �θ����� �����ڽĳ���� ���� ioSs�� ������ �ڽĳ��� ����
				if (rcIoSs != NULL)
					rcIoSs->SetpPr(parIoSs);		// ���� rcIoSs�� �θ��带 ioSs�� �θ���� ����
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
				// insert �Լ� ( ����Ž��Ʈ���� ���� ������� )
		// 1. ������ ���� �� ����ֱ�
		// 2. ���� ����ְ� ���뷱���� ��
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

				// travling BST ( ����Ʈ��Ž���� ��ȸ��)
		// 1. �ǾƷ����� ROOT���� �ö󰡴� inOrder ( ������ ���� )
		// 2. �� ������ LEAF���� �������� PreOrder ( ������ ���� )
		// 3. ���̿� �°� ã�ƺ��� PostOrder ( ���� ���� ) 
template<typename K, typename V>
inline void T_BST<K, V>::travelsal_inOrder(T_BSTN<K, V>* p, T_Array<V>& array_value)
{
	T_BSTN<K, V>* pLc, * pRc;
	T_Entry<K, V> entry;
	V val;
	if (p == NULL)
		return;

	pLc = p->pLc();		pRc = p->pRc();
	travelsal_inOrder(pLc, array_value);	// ���
	entry = p->Entry();
	val = entry.Val();			
	array_value.insertBack(val);			// �Ǹ������� ��� �ϳ� ����	
	travelsal_inOrder(pRc, array_value);	// �ٽ� ��� 
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
	array_value.insertBack(val);			// �Ǹ������� ��� �ϳ� ����

	travelsal_preOrder(pLc, array_value);		// ���ʳ�忡 ���� ��ȸ
	travelsal_preOrder(pRc, array_value);		// ������ ��忡 ���� ��ȸ

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

	travelsal_postOrder(pLc, array_value);		// ���� ��忡 ���� Ž�� 
	travelsal_postOrder(pRc, array_value);

	entry = pos->Entry();
	val = entry.Val();
	array_value.insertBack(val);			// �Ǹ������� ��� �ϳ� ����
}

				// search BSTN ( ����Ž��Ʈ�� ��� ����Ž�� )
template<typename K, typename V>
inline T_BSTN<K, V>* T_BST<K, V>::searchBSTN( K k)
{
	T_BSTN<K, V>* pEntry;
	pEntry = _searchBSTN(this->_root, k);
	return pEntry;
}

					// �ִ� ���, �ּ� ���
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

				// ��� �Լ� �������̽�
		// 1. ���̿� ���� ���
		// 2. ������ ���� ��� 
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

	// ���� ���� ��尡 ���ٸ�
	if (pos == NULL)
	{
		pos = new T_BSTN<K, V>(e);			// ��带 �����Ҵ�
		if (prPos == NULL)
			this->_root = pos;					// pos�� root��尡 �ȴ�. 
		pos->SetpPr(prPos);						// �θ���� ����
		*p = pos;
		num_entry++;							// ��Ʈ���� ���� 1�� ����
		return pos;								// ��ȯ
	}

	ent = pos->Entry();
	
	// ���� ����� entry�� �θ��� entry���� �� �۴ٸ� ���ʳ�忡 ������� 
	if (e < ent)					
	{
		pChildPos = pos->ppLc();					// ��ġ�� ���ʳ�� (�ּ�)
		newPos = _insertInOrder(pChildPos, pos, e);	// �ѹ��� üũ ( �� ������ �̾������� )
		if (newPos != NULL)
			pos->SetpLc(newPos);					// ���� ���̻� ������ ������ ��尡 ���ٸ� �� ��带 �������� ����
		return NULL;								// ��ȯ
	}
	
	// ���� ����� entry�� �θ��� entry���� �� ũ�ٸ� ���ʳ�忡 ������� 
	else if (e >= ent)
	{
		pChildPos = pos->ppRc();					// ��ġ�� �����ʳ�� (�ּ�)
		newPos = _insertInOrder(pChildPos, pos, e);		// üũ ( �� ������ �̾����°� ) 
		if (newPos != NULL)
			pos->SetpRc(newPos);					// ���̻� ������ �������� �ʴ´ٸ� ������ ��忡 ������
		return NULL;								// ��ȯ
	}
}
template<typename K, typename V>
inline T_BSTN<K, V>* T_BST<K, V>::_insertAndRebal(T_BSTN<K, V>** ppTN, T_BSTN<K, V>* pPr, T_Entry<K, V> e)
{
	T_BSTN<K, V>* pTN = NULL, ** ppLc = NULL, ** ppRc = NULL;
	T_Entry<K, V> bstn_entry;

	// ���� �ܺ� ��带 �� Ʈ����忡 ������
	if (*ppTN == NULL)
	{
		pTN = new T_BSTN<K, V>(e);
		*ppTN = pTN;
		if (pPr != NULL)
			pTN->SetpPr(pPr);				// �θ��� ����
		(*ppTN)->SetpLc(NULL);				// �ڽĳ��� �����Ƿ� NULL�� ����
		(*ppTN)->SetpRc(NULL);
		num_entry++;
		return *ppTN;						// ���� ��� ��ȯ
	}


	bstn_entry = (*ppTN)->Entry();				// ��Ʈ���� ������
	if (e < bstn_entry)
	{
		ppLc = (*ppTN)->ppLc();					// ���� �θ��庸�� ��Ʈ������ �� �۴ٸ� ���� ��� �ּҸ� �������� 
		pTN = _insertAndRebal(ppLc, *ppTN, e);	// �� ������ �������鼭 ��� ���� ���� ã�´�
		if (ppTN != NULL)						// ���� �� ������ ���� ���ٸ� 
		{
			(*ppTN)->SetpLc(pTN);				// ��带 ���� 
			*ppTN = _reBalance(ppTN);			// ��ġ ���뷱�� �Ѵ�.
		}
	}
	else
	{
		ppRc = (*ppTN)->ppRc();					// �θ��� ��Ʈ�� ������ ũ�ų� ������ ������ ��� �ּҸ� ������
		pTN = _insertAndRebal(ppRc, *ppTN, e);	// ��� ������ ��������.
		if (ppTN != NULL)						// �� ������ ���� ���ٸ� 
		{
			(*ppTN)->SetpRc(pTN);				// ������ �� �����ϰ�
			*ppTN = _reBalance(ppTN);			// ���뷱�� ��
		}
	}
	return *ppTN;
}


				// min, max
template<typename K, typename V>
inline T_BSTN<K, V>* T_BST<K, V>::_minBSTN(T_BSTN<K, V>* subRoot)			// �ּҰ� ��ȯ
{
	T_BSTN<K, V>* pos;

	if ((subRoot == NULL) || (subRoot->pLc() == NULL))
		return subRoot;							// ���� subRoot�� ���ų� �ƴϸ� subRoot�� ���ʳ�� ���� ���ٸ� subRoot�� ��ȯ
	pos = subRoot;
	while (pos->pLc() != NULL)
		pos = pos->pLc();						// �׷����ʴٸ� subRoot�� ���ʳ�尡 NULL�� ���ö�����, ��� pos�� �����ϸ鼭 �ּҰ��� ã�´�.
	
	return pos;						// pos ��ȯ	
}
template<typename K, typename V>
inline T_BSTN<K, V>* T_BST<K, V>::_maxBSTN(T_BSTN<K, V>* subRoot)			// �ִ밪 ��ȯ
{
	T_BSTN<K, V>* pos;

	if ((subRoot == NULL) || (subRoot->pRc() == NULL))
		return subRoot;							// ���� subRoot�� ���ų� �ƴϸ� subRoot�� ������ ��� ���� ���ٸ� subRoot�� ��ȯ
	pos = subRoot;
	while (pos->pRc() != NULL)
		pos = pos->pRc();						// �׷����ʴٸ� subRoot�� ������ ��尡 NULL�� ���ö�����, ��� pos�� �����ϸ鼭 �ִ밪�� ã�´�.

	return pos;						// pos ��ȯ	
}

					// rebalance
template<typename K, typename V>
inline T_BSTN<K, V>* T_BST<K, V>::_reBalance(T_BSTN<K, V>** ppTN)
{
	int heightDiff = 0;

	heightDiff = _HeightDiff(*ppTN);				// ���� ���̸� ���
	if (heightDiff > 1)								// ���� 1���� ũ�ٸ� 
	{
		if (_HeightDiff((*ppTN)->pLc()) > 0)		// ���ʳ�嵵 ����ؼ� �������̰� ������
			*ppTN = _rotate_LL(*ppTN);				// ��-�� �����̼�
		else
			*ppTN = _rotate_LR(*ppTN);				// �ƴϸ� ��-�� �����̼�
	}
	else if (heightDiff < -1)						// -1���� �۴ٸ� �������̴�.
	{
		if (_HeightDiff((*ppTN)->pRc()) < 0)		// ������ �ڽĳ�嵵 ����Ͽ� ���̰� �������
			*ppTN = _rotate_RR(*ppTN);				// ��-�� �����̼�
		else
			*ppTN = _rotate_RL(*ppTN);				// ��-�� �����̼�
	}
	return *ppTN;									// ��ȯ
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
		h_Lc = _Height(pTN->pLc()); h_Rc = _Height(pTN->pRc());		// ��͸� ���� �ڽĳ����� ��ġ�� �Ǻ�
		if (h_Lc > h_Rc)
			height = 1 + h_Lc;
		else
			height = 1 + h_Rc;
	}
	// ����, ������ �� ���� �� ������ ������ ��带 �������� + 1�Ѵ�.
	return height;
}
template<typename K, typename V>
inline int T_BST<K, V>::_HeightDiff(T_BSTN<K, V>* pTN)
{
	int h_diff = 0;
	if (pTN == NULL)
		return 0;
	h_diff = _Height(pTN->pLc()) - _Height(pTN->pRc());

	// ���� ���� ����� ���̿� ������ ����� ���̸� ���� ���� ���
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

	ent_k = pos->getKey();							// ent_k �� ���� ����� entry�� Key���� ������
	if (ent_k == k)
		pos_result = pos;							// ã�� Ű���� ������ �ٷ� ��ȯ�ϰ� ���� ����
	else if (ent_k > k)
		pos_result = _searchBSTN(pos->pLc(), k);	// ���� key ���� �� ������ ���� ��带 ã��
	else if (ent_k < k)
		pos_result = _searchBSTN(pos->pRc(), k);	// ���� Ű���� �� ũ�� ������ ��带 ã��

	return pos_result;

}

// print function 
template<typename K, typename V>
inline void T_BST<K, V>::_print_with_Depth(T_BSTN<K, V>* pTN, ostream& ostr, int depth)
{
	T_BSTN<K, V>* pRc, * pLc;
	T_Entry<K, V> pEntry;

	if ((pRc = pTN->pRc()) != NULL)
		_print_with_Depth(pRc, ostr, depth + 1);				// ������ ��� ���
	for (int i = 0; i < depth; i++)
	{
		ostr << "\t\t";										// �� Ű�� ���� ������
	}
	ostr << pTN->Entry() << endl;
	if ((pLc = pTN->pLc() ) != NULL)							// ���� ��� ���
		_print_with_Depth(pLc, ostr, depth + 1);
}
template<typename K, typename V>
inline void T_BST<K, V>::_print_inOrder(T_BSTN<K, V>* pTN, ostream& ostr)
{
	T_BSTN<K, V>* pRc, * pLc;
	if ((pLc = pTN->pLc()) != NULL)
		_print_inOrder(pLc, ostr);						// ���� ��� ���
	ostr << pTN->Entry() << endl;						// �߰� ��� ���
	if ((pRc = pTN->pRc()) != NULL)
		_print_inOrder(pRc, ostr);						// ������ ��� ���
}


#endif // !T_BST_H


