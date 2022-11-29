#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include "TrieNode.h"
#include "MyVoca.h"

#define MAX_STR_LEN 50

typedef list<MyVoca*> List_pVoca;
typedef list<MyVoca*>::iterator List_pVoca_Iter;

enum SearchMode { FULL_MATCH, PREFIX_MATCH };		// 완전일치, 부분일치

template <typename E>
class Trie
{
public:
	// constructor 
	Trie(string name)			// default constructor 
		: trie_name(name)
	{
		_root = new TrieNode<E>('\0', NULL);
		_root->SetKey('\0');
		_root->SetParent(NULL); _root->SetChild(NULL);
		_root->SetPrev(NULL); _root->SetNext(NULL);
		num_keys = 0;
	};

	// getter 
	int size() { return num_keys; }
	string name() { return trie_name; }

	// member functions
	void insert(string keystr, E value);
	void insertExternalTN(TrieNode<E>* pTN, string keystr, E value);
	TrieNode<E>* find(string keystr);
	void findPrefixMatch(string prefix, List_pVoca& predictVocas);
	void deleteKeyStr(string keystr);
	void eraseTrie();
	void fprintTrie(ostream& ostr);

protected:
	TrieNode<E>* _find(string keystr, SearchMode sm = FULL_MATCH);
	void _traverse(TrieNode<E>* pTN, List_pVoca& list_pVocas);
	void _fprint(ostream& ostr, TrieNode<E>* pTN, int indent);

private:
	TrieNode<E>* _root;
	int num_keys;
	string trie_name;
};

/*					member functions				*/
template<typename E>
inline void Trie<E>::insert(string keystr, E value)
{
	TrieNode<E>* pTN = NULL, * pTN_New = NULL;
	char* keyPtr = (char*)keystr.c_str();

	// 1. 받은 키가 없다면 바로 탈출
	if (keyPtr == NULL)
		return;

	// 2. 받은 키가 있지만, 완전일치하는 키를 찾지 못한 경우
	if (this->_find(keystr, FULL_MATCH) != NULL)
	{
		cout << "The given key string (" << keystr << ") is already existing; just return !!" << endl;
		return;
	}

	// 3. root를 반환받고 positioning 한다..
	pTN = this->_root;
	while ((pTN != NULL) && (*keyPtr != '\0'))
	{
		if ((pTN->Key() < *keyPtr) && (pTN->Next() == NULL) && (*keyPtr != '\0'))
			break;
		while ((pTN->Key() < *keyPtr) && (pTN->Next() != NULL))
			pTN = pTN->Next();
		while ((pTN != NULL) && (pTN->Key() == *keyPtr) && (*keyPtr != '\0'))
		{
			pTN = pTN->Child();
			keyPtr++;
		}

		if ((pTN->Key() > *keyPtr) && (*keyPtr != '\0'))
			break;
	}

	// insert를 진행함
	if ((pTN->Key() != '\0') && (*keyPtr == '\0'))
	{
		pTN_New = new TrieNode<E>('\0', value);
		pTN_New->SetParent(pTN->Parent());
		(pTN->Parent())->SetChild(pTN_New);
		pTN_New->SetNext(pTN);	pTN->SetPrev(pTN_New);
		this->num_keys++;
		return;
	}
	else if ((pTN->Key() < *keyPtr) && (pTN->Next() == NULL) && (*keyPtr != '\0'))
	{
		pTN_New = new TrieNode<E>(*keyPtr, VALUE_INITIAL_NODE);
		pTN_New->SetParent(pTN->Parent());
		pTN_New->SetPrev(pTN);
		pTN->SetNext(pTN_New);
		pTN = pTN_New;
		keyPtr++;

		while (*keyPtr != '\0')
		{
			pTN_New = new TrieNode<E>(*keyPtr, VALUE_INITIAL_NODE);
			pTN->SetChild(pTN_New);
			(pTN->Child())->SetParent(pTN);
			pTN = pTN->Child();
			keyPtr++;
		}
		if (*keyPtr == '\0')
		{
			this->insertExternalTN(pTN, keystr, value);
			this->num_keys++;
			return;
		}
	}
	else if ((pTN->Key() > *keyPtr) && (*keyPtr != '\0'))
	{
		pTN_New = new TrieNode<E>(*keyPtr, VALUE_INITIAL_NODE);
		pTN_New->SetNext(pTN);
		pTN_New->SetParent(pTN->Parent());

		if (pTN->Prev() == NULL)
		{
			if (pTN->Parent() != NULL)
				(pTN->Parent())->SetChild(pTN_New);
		}
		else
			(pTN->Prev())->SetNext(pTN_New);
		pTN_New->SetPrev(pTN->Prev());
		pTN->SetPrev(pTN_New);
		pTN = pTN_New;
		keyPtr++;

		while (*keyPtr != '\0')
		{
			pTN_New = new TrieNode<E>(*keyPtr, VALUE_INITIAL_NODE);
			pTN->SetChild(pTN_New);
			(pTN->Child())->SetParent(pTN);
			pTN = pTN->Child();
			keyPtr++;
		}
		if (*keyPtr == '\0')
		{
			this->insertExternalTN(pTN, keystr, value);
			this->num_keys++;
			return;
		}
	}
}
template<typename E>
inline void Trie<E>::insertExternalTN(TrieNode<E>* pTN, string keystr, E value)
{
	TrieNode<E> * pTN_New = NULL;

	pTN_New = new TrieNode<E>('\0', NULL);
	pTN->SetChild(pTN_New);
	(pTN->Child())->SetParent(pTN);
	pTN_New->SetVal(value);
}
template<typename E>
inline TrieNode<E>* Trie<E>::find(string keystr)
{
	TrieNode<E>* pTN = NULL;
	
	pTN = _find(keystr, FULL_MATCH);
	return pTN;
}
template<typename E>
inline void Trie<E>::findPrefixMatch(string prefix, List_pVoca& predictVocas)
{
	TrieNode<E>* pPtr = NULL, *pTN = NULL;
	string keyPtr;

	TrieNode<E>* found = NULL;
	keyPtr = prefix;

	if (prefix.empty())
		return;
	pTN = this->_root;
	pTN = _find(prefix, PREFIX_MATCH);
	this->_traverse(pTN, predictVocas);
}
template<typename E>
inline void Trie<E>::deleteKeyStr(string keystr)
{
	TrieNode<E>* pTN = NULL; *_root;
	TrieNode<E>* tmp = NULL;
	int trie_val = 0;

	_root = this->_root;
	if (NULL == _root || keystr.empty())
		return;
	pTN = _find(keystr, FULL_MATCH);		// 키가 정확히 일치하는 것을 찾음
	if (pTN == NULL)
	{
		cout << "Key [" << keystr << "] not found in trie !" << endl;
		return;
	}
	while (1)
	{
		// 만약 pTN이 NULL이 된다면 탈출
		if (pTN == NULL)
			break;
		if (pTN->Prev() && pTN->Next())
		{
			tmp = pTN;
			// 노드 재연결
			(pTN->Next())->SetPrev(pTN->Prev());
			(pTN->Prev())->SetNext(pTN->Next());
			free(tmp);	// 노드 삭제
			break;
		}
		else if (pTN->Prev() && !pTN->Next())
		{
			tmp = pTN;
			// 노드 재연결
			(pTN->Prev())->SetNext(NULL);	
			free(tmp);	// 노드 삭제
			break;
		}
		else if (!pTN->Prev() && pTN->Next())
		{
			tmp = pTN;
			// 노드 재연결
			(pTN->Prev())->SetNext(NULL);
			free(tmp);	// 노드 삭제
			break;
		}
		else
		{	// 만약 이전, 이후 노드 아무것도 없다면
			tmp = pTN;
			pTN = pTN->Parent();
			if (pTN != NULL)
				pTN->SetChild(NULL);
			if ((pTN == _root) && (pTN->Next() == NULL) && (pTN->Prev() == NULL))
			{
				cout << "the trie is empty !!" << endl;
				break;
			}
		}
	}
	this->num_keys--;
}
template<typename E>
inline void Trie<E>::eraseTrie()
{
	TrieNode<E>* pTN = NULL;
	TrieNode<E>* pTN_to_be_deleted = NULL;

	// 이미 루트노드가 없다면 바로 리턴
	if (this->_root == NULL)
		return;

	pTN = this->_root;
	while (pTN != NULL)
	{
		while ((pTN != NULL) && (pTN->Next()))
			pTN = pTN->Next();
		while (pTN->Child())
		{
			if (pTN->Next())
				break;
			pTN = pTN->Child();
		}
		if (pTN->Next())
			continue;

		if (pTN->Prev() && pTN->Next())
		{
			pTN_to_be_deleted = pTN;
			(pTN->Next())->SetPrev(pTN->Prev());
			(pTN->Prev())->SetNext(pTN->Next());
			pTN = pTN->Next();
			free(pTN_to_be_deleted); //free the memory
		}

		else if (!(pTN->Prev()) && pTN->Next())
		{
			pTN_to_be_deleted = pTN;
			(pTN->Parent())->SetChild(pTN->Next());
			(pTN->Next())->SetPrev(NULL);
			pTN = pTN->Next();
			free(pTN_to_be_deleted); //free the memory
		}
		else if (pTN->Prev() && !(pTN->Next()))
		{
			pTN_to_be_deleted = pTN;
			(pTN->Prev())->SetNext(NULL);
			pTN = pTN->Prev();
			free(pTN_to_be_deleted); //free the memory
		}
		else
		{
			pTN_to_be_deleted = pTN;
			if (pTN == this->_root)
			{
				this->num_keys = 0;
				return;
			}
			if (pTN->Parent() != NULL)
			{
				pTN = pTN->Parent();
				pTN->SetChild(NULL);
			}
			else
				pTN = pTN->Prev();
			free(pTN_to_be_deleted);	// free memory
		}
	}
}
template<typename E>
inline void Trie<E>::fprintTrie(ostream& ostr)
{
	TrieNode<E>* pTN;
	int line = 1, indent = 0;

	ostr << "trie ( " << this->name() << ") with "
		<< this->num_keys << " trie_nodes\n";
	// 만약 노드가 없다면 바로 리턴
	if (this->num_keys == 0) {
		ostr << "Empty trie !" << endl;
		return;
	}

	pTN = this->_root;
	pTN->_fprint(ostr, pTN, indent);
}

/*				protected function				*/
template<typename E>
inline TrieNode<E>* Trie<E>::_find(string keystr, SearchMode sm )
{
	const char* keyPtr;
	TrieNode<E>* pTN = NULL, *found = NULL;

	if (keystr.empty())
		return NULL;

	keyPtr = (char*)keystr.c_str();
	pTN = this->_root;

	while ((pTN != NULL) && (*keyPtr != '\0'))
	{
		while ((pTN != NULL) && (pTN->Key() < *keyPtr))
		{
			if (pTN->Next() == NULL)
				return NULL;
			pTN = pTN->Next();
		}

		if ((pTN != NULL) && (pTN->Key() > *keyPtr))
			return NULL;

		else if ((pTN == NULL) && (*keyPtr != '\0'))
			return NULL;

		else if ((pTN->Key() == *keyPtr) && (*keyPtr != '\0'))
		{
			pTN = pTN->Child();
			keyPtr++;
			if (*keyPtr == '\0')
			{
				if (sm == FULL_MATCH)
				{
					if (pTN->Key() == '\0')
						return pTN;
					else
						// found the key string as a substring of a longer existing string
						return NULL;
				}
				else if (sm == PREFIX_MATCH)
					// found the key string as a full-match or as a substring of a longer existing string 
					return pTN;
			}
			else if ((pTN->Key() == '\0') && (*keyPtr != '\0'))
			{
				if (pTN->Next() != NULL)
				{
					pTN = pTN->Next();
					continue;
				}
				else
					return NULL;
			}
			else
				continue;
		}
	}
}
template<typename E>
inline void Trie<E>::_traverse(TrieNode<E>* pTN, List_pVoca& list_pVocas)
{
	if (pTN == NULL)
		return;
	if (pTN->Child() == NULL)
		list_pVocas.push_back(pTN->Val());
	else
		this->_traverse(pTN->Child(), list_pVocas);

	if (pTN->Next() == NULL)
		this->_traverse(pTN->Next(), list_pVocas);
}
template<typename E>
void Trie<E>::_fprint(ostream& fout, TrieNode<E>* pTN, int indent)
{
	if (pTN == NULL)  //end of downword
	{
		fout << endl;
		return;
	}
	else {
		fout << pTN->key;
		_fprint(fout, pTN->child, indent + 1); //recursive
		if (pTN->next == NULL) //end of same depth
			return;
		for (int i = 0; i < indent; i++)
			fout << " "; // indent
		_fprint(fout, pTN->next, indent); //recursive
	}
}

#endif // !TRIE_H


