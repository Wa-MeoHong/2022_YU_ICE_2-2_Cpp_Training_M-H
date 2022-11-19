#ifndef T_BSTN_H
#define T_BSTN_H

#include "T_Entry.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

template <typename K, typename V>
class T_BSTN 
{
public:
	// constructor 
	T_BSTN()					// default constructor
		: entry(), pPR(NULL), pLC(NULL), pRC(NULL) {};
	T_BSTN(T_Entry<K, V> e) 	// constructor
		: entry(e), pPR(NULL), pLC(NULL), pRC(NULL) {} ;
	
	// setter
	void SetpPr(T_BSTN<K, V>* pTN) { pPR = pTN; }
	void SetpLc(T_BSTN<K, V>* pTN) { pLC = pTN; }
	void SetpRc(T_BSTN<K, V>* pTN) { pRC = pTN; }
	void SetEntry(T_Entry<K, V> e) { entry = e; }

	// getter
	K getKey() const { return entry.Key(); }				// entry의 키값 반환
	V getVal() const { return entry.Val(); }				// entry의 밸류 반환
	T_BSTN<K, V>* pPr() const { return pPR; }				// 부모노드
	T_BSTN<K, V>* pLc() const { return pLC; }				// 왼쪽 자식노드
	T_BSTN<K, V>* pRc() const { return pRC; }				// 오른쪽 자식노드	
	T_BSTN<K, V>** ppLc() { return &pLC; }			// 왼쪽 자식노드의 주소
	T_BSTN<K, V>** ppRc() { return &pRC; }			// 오른쪽 자식노드의 주소
	T_Entry<K, V>& Entry() { return entry; }

	// operator overloading
	T_Entry<K, V>& operator*() const { return entry; }

private:
	T_Entry<K, V>	entry;		// element value  
	T_BSTN<K, V>*	pPR;		// parent pointer
	T_BSTN<K, V>*	pLC;		// left child pointer
	T_BSTN<K, V>*	pRC;		// right child pointer
};
#endif // !T_BST_H