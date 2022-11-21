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
	Iterator begin();								// Iterator의 처음 반환
	Iterator end() { return Iterator(this->B, this->B.end()); };		// Iterator의 끝 반환

	// member function (interfaces)
	bool Empty() const { return (num_entry == 0); }
	Iterator find(const K& k);						// Key를 통해 엔트리 값을 찾는다
	Iterator insert(const K& k, const V& v);		// 엔트리에 키와 값을 넣는다
	void Erase(const K& k);							// K의 값을 이용해 엔트리 삭제 ( Iterator의 것과 오버로딩 중)
	void Erase(const Iterator& p);					// Iterator p를 이용해 엔트리 삭제 ( key의 것과 오버로딩 중)
	void fprintBucketSizes(ostream& ostr);			// printout bucket sizes
	void fprintBucket(ostream& ostr, BItor bkt);		// 버킷 출력
 
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

		// operator overloading (반복자로써 기능하기 위한 필수 오버로딩)
		Entry& operator*() const { return *ent; }
		bool operator==(const Iterator& p) const;		// Iterator가 같은지
		bool operator!=(const Iterator& p) const;		// Iterator가 일치하지 않는지
		Iterator& operator++();				//	다음 엔트리로 넘어가기위함
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
		return end();						// if 비어있으면 end 반환
	BItor bkt = this->B.begin();			// 아니면, 엔트리를 찾는다
	while (bkt->empty())					// 비어있다고 말하기 전까지
		++bkt;								// 버킷의 첫번째를 찾는다.

	return Iterator(this->B, bkt, bkt->begin());
}

/*				interface function				*/

template<typename K, typename V>
inline typename HashMap<K, V>::Iterator HashMap<K, V>::find(const K& k)
{
	Iterator p = _find(k);				// 키의 값을 찾아서 반환받음
	if (_endOfBkt(p))					// 만약 키의 값을 통해 찾지 못해서 end에 가있다면
		return end();					// end를 반환
	else
		return p;						// 아니면 반환받은 값 반환
}
template<typename K, typename V>
inline typename HashMap<K, V>::Iterator HashMap<K, V>::insert(const K& k, const V& v)
{
	Iterator p = _find(k);

	if (_endOfBkt(p))			// k의 값을 가진 키를 찾지 못했으면, 
	{
		return _insert(p, Entry(k, v));		// insert함수를 실행해 값을 집어넣는다. 
	}
	else
	{
		p.ent->setValue(v);				// 키를 찾았다면 Entry의 키 값을 이걸로 변경한 후, 반환
		return p;
	}
}
template<typename K, typename V>
inline void HashMap<K, V>::Erase(const K& k)
{
	Iterator p = _find(k);				// 키의 값을 찾음
	if (_endOfBkt(p))
		throw "Erase of nonexistent";	// Error 반환
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
	Iterator p(B, bkt, bkt->begin());			// 반복자 생성
	MyVoca* pVoca = NULL;						// Voca 포인터 
	while (p.ent != bkt->end())					// p.ent가 bkt의 끝에 도달할 때까지
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

	// 최대값, 최소값, 평균을 구함. 
	for (int bkt = 0; bkt < num_bkts; bkt++)
	{
		bkt_size = B[bkt].size();
		ostr << "Buktet[" << setw(3) << bkt << "] : " << bkt_size << "entries" << endl;
		if (bkt_size > max_ent)
		{
			max_ent = bkt_size;			// 최대 엔트리 사이즈 갱신
			max_bkt = bkt;
		}
		if (bkt_size < min_ent)			// 최소 엔트리 사이즈 갱신
		{
			min_ent = bkt_size;
		}
		total += bkt_size;

	}
	avg = (double)total / (double)num_bkts;

	// 출력
	ostr.precision(2);
	ostr << "\nMax_ent (" << setw(2) << max_ent << "), min_ent (" << setw(2) << min_ent 
		<< "), avg (" << setw(5) << avg << ")\n " << endl;
	
	ostr << "Bucket with maximum (" << max_ent << ") entries : " << endl;
	BItor bkt = B.begin() + max_bkt;		// 버킷이 가장 많은 해시의 버킷으로 향함
	fprintBucket(ostr, bkt);				// 버킷 출력


}


/*				protected function				*/
template<typename K, typename V>
inline typename HashMap<K, V>::Iterator HashMap<K, V>::_find(const K& k)
{
	CyclicShiftHashCode hash;
	int i = hash(k) % this->B.size();			// CyclicShiftHashCode를 사용해 hash의 Value를 계산함
	BItor bkt = this->B.begin() + i;			// 버킷의 시작에서부터 i번째에 있는 값

	Iterator p(this->B, bkt, bkt->begin());
	while (!_endOfBkt(p) && (*p).Key() != k)		// 버킷의 키가 끝에  도달하거나, k를 찾지 못할 때까지
		++p.ent;
	return p;									// p의 값 반환
}
template<typename K, typename V>
inline typename HashMap<K, V>::Iterator HashMap<K, V>::_insert(const Iterator& p, const Entry& e)
{
	EItor ins = p.bkt->insert(p.ent, e);			// list의 반복자의 insert를 사용함
	this->num_entry++;
	return  Iterator(this->B, p.bkt, ins);
}
template<typename K, typename V>
inline void HashMap<K, V>::_erase(const Iterator& p)
{
	p.bkt->erase(p.ent);			// list의 erase를 사용 중
	this->num_entry--;				// 엔트리 개수를 한개 줄임
}


/*				Iterator operator overloading				*/
template<typename K, typename V>
inline bool HashMap<K, V>::Iterator::operator==(const Iterator& p) const
{
	if (this->ba != p.ba || this->bkt != p.bkt)
		return false;					// 만약 둘중 하나라도 같지 않다면 false
	else if (this->bkt == this->ba->end())
		return true;					// 만약 둘다 끝에 가있다면
	else
		return (this->ent == p.ent);		// 둘다 아니라면 entry가 같은지 비교한 값을 반환
}
template<typename K, typename V>
inline bool HashMap<K, V>::Iterator::operator!=(const Iterator& p) const
{
	if (this->ba != p.ba || this->bkt != p.bkt)
		return true;					// 만약 둘중 하나라도 같지 않다면 true
	else if (this->bkt == this->ba->end())
		return false;					// 만약 둘다 끝에 가있다면
	else
		return (this->ent != p.ent);		// 둘다 아니라면 entry가 같은지 비교한 값을 반환
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


