#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>
#include <list>
#include <vector>
#include <exception>
#include "Entry.h"
#include "CyclicShiftHashCode.h"
#include "MyVoca.h"

#define DEFAULT_HASH_TABLE_SIZE 101

using namespace std;

template <typename K, typename V> 
class HashMap
{
public:
	typedef Entry<const K, V> Entry;				// Entry
	typedef list<Entry> Bucket;						// a bucket of entries
	typedef vector<Bucket> BktArray;				// bucket array
	typedef typename BktArray::iterator BItor;		// bucket iterator
	typedef typename Bucket::iterator EItor;		// entry iterator
	class Iterator;

public:
	// constructor
	HashMap(string name, int capacity = DEFAULT_HASH_TABLE_SIZE)
		: name(name), num_entry(0), B(capacity) {};

	// getter
	int size() const { return num_entry; }
	string Name() const { return name; }
	Iterator begin();								// Iterator�� ó�� ��ȯ
	Iterator end() { return Iterator(this->B, this->B.end()); };		// Iterator�� �� ��ȯ

	// member function (interfaces)
	bool Empty() const { return (num_entry == 0); }
	Iterator find(const K& k);						// Key�� ���� ��Ʈ�� ���� ã�´�
	Iterator insert(const K& k, const V& v);		// ��Ʈ���� Ű�� ���� �ִ´�
	void Erase(const K& k);							// K�� ���� �̿��� ��Ʈ�� ���� ( Iterator�� �Ͱ� �����ε� ��)
	void Erase(const Iterator& p);					// Iterator p�� �̿��� ��Ʈ�� ���� ( key�� �Ͱ� �����ε� ��)
	void fprintBucketSizes(ostream& ostr);			// printout bucket sizes
	void fprintBucket(ostream& ostr, BItor bkt);		// ��Ŷ ���
 
protected:
	Iterator _find(const K& k);								// find utility
	Iterator _insert(const Iterator& p, const Entry& e);		// insert utility
	void _erase(const Iterator& p);					//  remove utility
	static bool _endOfBkt(const Iterator& p) { return p.ent == p.bkt->end(); }	// end of bucket?

private:
	int num_entry;
	BktArray B;
	string name;

// ----------------------------------------------------------------------------------------------

public:
	//iterator class
	class Iterator
	{
	public:
		// constructor
		Iterator() {};
		Iterator(const BktArray& a, const BItor& b, const EItor& q = EItor())
			: ent(q), bkt(b), ba(&a) {};

		// getter
		V Value() { Entry& e = *ent; return e.Val(); }

		// operator overloading (�ݺ��ڷν� ����ϱ� ���� �ʼ� �����ε�)
		Entry& operator*() const { return *ent; }
		bool operator==(const Iterator& p) const;		// Iterator�� ������
		bool operator!=(const Iterator& p) const;		// Iterator�� ��ġ���� �ʴ���
		Iterator& operator++();				//	���� ��Ʈ���� �Ѿ������
		Iterator& advanceEltor() { ++ent; return *this; }
		friend class HashMap;			// give HashMap access

	protected:
		EItor ent;
		BItor bkt;
		const BktArray* ba;
	};
};

template<typename K, typename V>
inline typename HashMap<K, V>::Iterator HashMap<K, V>::begin()
{
	if (this->Empty())
		return end();						// if ��������� end ��ȯ
	BItor bkt = this->B.begin();			// �ƴϸ�, ��Ʈ���� ã�´�
	while (bkt->empty())					// ����ִٰ� ���ϱ� ������
		++bkt;								// ��Ŷ�� ù��°�� ã�´�.

	return Iterator(this->B, bkt, bkt->begin());
}

/*				interface function				*/

template<typename K, typename V>
inline typename HashMap<K, V>::Iterator HashMap<K, V>::find(const K& k)
{
	Iterator p = _find(k);				// Ű�� ���� ã�Ƽ� ��ȯ����
	if (_endOfBkt(p))					// ���� Ű�� ���� ���� ã�� ���ؼ� end�� ���ִٸ�
		return end();					// end�� ��ȯ
	else
		return p;						// �ƴϸ� ��ȯ���� �� ��ȯ
}
template<typename K, typename V>
inline typename HashMap<K, V>::Iterator HashMap<K, V>::insert(const K& k, const V& v)
{
	Iterator p = _find(k);

	if (_endOfBkt(p))			// k�� ���� ���� Ű�� ã�� ��������, 
	{
		return _insert(p, Entry(k, v));		// insert�Լ��� ������ ���� ����ִ´�. 
	}
	else
	{
		p.ent->setValue(v);				// Ű�� ã�Ҵٸ� Entry�� Ű ���� �̰ɷ� ������ ��, ��ȯ
		return p;
	}
}
template<typename K, typename V>
inline void HashMap<K, V>::Erase(const K& k)
{
	Iterator p = _find(k);				// Ű�� ���� ã��
	if (_endOfBkt(p))
		throw "Erase of nonexistent";	// Error ��ȯ
	_erase(p);							// erase
}
template<typename K, typename V>
inline void HashMap<K, V>::Erase(const Iterator& p)
{
	_erase(p);							// erase
}
template<typename K, typename V>
inline void HashMap<K, V>::fprintBucket(ostream& ostr, BItor bkt)
{
	Iterator p(B, bkt, bkt->begin());			// �ݺ��� ����
	MyVoca* pVoca = NULL;						// Voca ������ 
	while (p.ent != bkt->end())					// p.ent�� bkt�� ���� ������ ������
	{
		pVoca = p.Value();
		ostr << *pVoca << endl;
		++p.ent;
	}
}
template<typename K, typename V>
inline void HashMap<K, V>::fprintBucketSizes(ostream& ostr)
{
	int bkt_size = 0;
	int max_ent, min_ent, total = 0;
	int num_bkts = 0, max_bkt = 0;
	double avg = 0.0;
	max_ent = min_ent = B[0].size();
	num_bkts = B.size();

	// �ִ밪, �ּҰ�, ����� ����. 
	for (int bkt = 0; bkt < num_bkts; bkt++)
	{
		bkt_size = B[bkt].size();
		ostr << "Buktet[" << setw(3) << bkt << "] : " << bkt_size << "entries" << endl;
		if (bkt_size > max_ent)
		{
			max_ent = bkt_size;			// �ִ� ��Ʈ�� ������ ����
			max_bkt = bkt;
		}
		if (bkt_size < min_ent)			// �ּ� ��Ʈ�� ������ ����
		{
			min_ent = bkt_size;
		}
		total += bkt_size;

	}
	avg = (double)total / (double)num_bkts;

	// ���
	ostr.precision(2);
	ostr << "\nMax_ent (" << setw(2) << max_ent << "), min_ent (" << setw(2) << min_ent 
		<< "), avg (" << setw(5) << avg << ")\n " << endl;
	
	ostr << "Bucket with maximum (" << max_ent << ") entries : " << endl;
	BItor bkt = B.begin() + max_bkt;		// ��Ŷ�� ���� ���� �ؽ��� ��Ŷ���� ����
	fprintBucket(ostr, bkt);				// ��Ŷ ���


}


/*				protected function				*/
template<typename K, typename V>
inline typename HashMap<K, V>::Iterator HashMap<K, V>::_find(const K& k)
{
	CyclicShiftHashCode hash;
	int i = hash(k) % this->B.size();			// CyclicShiftHashCode�� ����� hash�� Value�� �����
	BItor bkt = this->B.begin() + i;			// ��Ŷ�� ���ۿ������� i��°�� �ִ� ��

	Iterator p(this->B, bkt, bkt->begin());
	while (!_endOfBkt(p) && (*p).Key() != k)		// ��Ŷ�� Ű�� ����  �����ϰų�, k�� ã�� ���� ������
		++p.ent;
	return p;									// p�� �� ��ȯ
}
template<typename K, typename V>
inline typename HashMap<K, V>::Iterator HashMap<K, V>::_insert(const Iterator& p, const Entry& e)
{
	EItor ins = p.bkt->insert(p.ent, e);			// list�� �ݺ����� insert�� �����
	this->num_entry++;
	return  Iterator(this->B, p.bkt, ins);
}
template<typename K, typename V>
inline void HashMap<K, V>::_erase(const Iterator& p)
{
	p.bkt->erase(p.ent);			// list�� erase�� ��� ��
	this->num_entry--;				// ��Ʈ�� ������ �Ѱ� ����
}


/*				Iterator operator overloading				*/
template<typename K, typename V>
inline bool HashMap<K, V>::Iterator::operator==(const Iterator& p) const
{
	if (this->ba != p.ba || this->bkt != p.bkt)
		return false;					// ���� ���� �ϳ��� ���� �ʴٸ� false
	else if (this->bkt == this->ba->end())
		return true;					// ���� �Ѵ� ���� ���ִٸ�
	else
		return (this->ent == p.ent);		// �Ѵ� �ƴ϶�� entry�� ������ ���� ���� ��ȯ
}
template<typename K, typename V>
inline bool HashMap<K, V>::Iterator::operator!=(const Iterator& p) const
{
	if (this->ba != p.ba || this->bkt != p.bkt)
		return true;					// ���� ���� �ϳ��� ���� �ʴٸ� true
	else if (this->bkt == this->ba->end())
		return false;					// ���� �Ѵ� ���� ���ִٸ�
	else
		return (this->ent != p.ent);		// �Ѵ� �ƴ϶�� entry�� ������ ���� ���� ��ȯ
}
template<typename K, typename V>
inline typename HashMap<K, V>::Iterator& HashMap<K, V>::Iterator::operator++()
{
	++(this->ent);
	if (_endOfBkt(*this))
	{
		++bkt;
		while ((this->bkt != this->ba->end()) && (this->bkt->empty()))
			++bkt;
		if (this->bkt == this->ba->end())
			return *this;
		this->ent = this->bkt->begin();
	}
	return *this;

}


#endif // !HASHMAP_H


