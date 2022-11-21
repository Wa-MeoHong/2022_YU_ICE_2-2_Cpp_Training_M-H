#ifndef HASH_DICTIONARY_H
#define HASH_DICTIONARY_H

#include "HashMap.h"

#define HASH_TABLE_SIZE 101

template<typename K, typename V>
class HashDict : public HashMap<K, V>
{
public:
	typedef typename HashMap<K, V>::Iterator Iterator;
	typedef typename HashMap<K, V>::Entry Entry;

	// iterator range
	class Range {
	private :
		Iterator _begin;
		Iterator _end;
	public:
		// constructor 
		Range() {};				// default constructor 
		Range(const Iterator& b, const Iterator& e) : _begin(b), _end(e) {};	// constructor

		// getter 
		Iterator& begin() { return _begin; }
		Iterator& end() { return _end; }
		// end of class Range
	};

public:
	// constructor
	HashDict(string name, int  capacity = HASH_TABLE_SIZE) : HashMap<K, V>(name, capacity) {};

	// member function
	Range findAll(const K& k);							// find All entry with K ( K�� Ű������ ������ ��Ʈ�� ���� )
	Iterator insert(const K& k, const V& v);			// insert Entry 
};


template<typename K, typename V>
inline typename HashDict<K, V>::Range HashDict<K, V>::findAll(const K& k)
{
	Iterator b = this->_find(k);			 // ��Ŷ�� ����
	Iterator p = b;	

	while (p != this->end() && (*p).Key() == k)		// ��Ŷ�� ���� �����ϰų�, k�� ������ ���������� 
		++p;		// p�� ���Ͽ� ã�´�. ( ��, K���� ������ ��Ʈ���� ������ ����)
	
	return Range(b, p);				//Range ��ȯ
}
template<typename K, typename V>
inline typename HashDict<K, V>::Iterator HashDict<K, V>::insert(const K& k, const V& v)
{
	Iterator p = this->_find(k);
	Iterator q = this->_insert(p, Entry(k, v));
	return q;
}



#endif // !HASH_DICTIONARY_H
