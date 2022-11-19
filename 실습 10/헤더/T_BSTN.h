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
	K getKey() const { return entry.Key(); }				// entry�� Ű�� ��ȯ
	V getVal() const { return entry.Val(); }				// entry�� ��� ��ȯ
	T_BSTN<K, V>* pPr() const { return pPR; }				// �θ���
	T_BSTN<K, V>* pLc() const { return pLC; }				// ���� �ڽĳ��
	T_BSTN<K, V>* pRc() const { return pRC; }				// ������ �ڽĳ��	
	T_BSTN<K, V>** ppLc() { return &pLC; }			// ���� �ڽĳ���� �ּ�
	T_BSTN<K, V>** ppRc() { return &pRC; }			// ������ �ڽĳ���� �ּ�
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