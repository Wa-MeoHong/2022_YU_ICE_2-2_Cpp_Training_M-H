#ifndef T_ENTRY_H
#define T_ENTRY_H

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

template<typename K, typename V>
class T_Entry
{
	// operator Overloading (��� ������)
	friend ostream& operator<< (ostream& ostr, T_Entry<K, V>& entry)
	{
		// print format ( [key , Value] )
		/*ostr << "[" << setw(2) << entry.Key() << ", " << *entry.Val() << "]";*/
		// print format ( [Key:key]
		ostr << "[Key:" << setw(2) << entry.Key() << "]";
		return ostr;
	}

public:
	// constructor
	T_Entry() { _key = 999; }		// default constructor
	T_Entry(K key, V value) { _key = key; _value = value; }

	// setter
	void SetKey(const K& key) { _key = key; }
	void SetVal(const V& value) { _value = value; }

	// getter
	K Key() const { return _key; }				// return key
	V Val() const { return _value; }			// return value

	// operator Overloading ( �񱳿����� �����ε� )
	// >, >=, <, <=, ==, =
	bool operator> (const T_Entry& right) { return (this->Key() > right.Key()); }
	bool operator>= (const T_Entry& right) { return (this->Key() >= right.Key()); }
	bool operator< (const T_Entry& right) { return (this->Key() < right.Key()); }
	bool operator<= (const T_Entry& right) { return (this->Key() <= right.Key()); }
	bool operator== (const T_Entry& right) { return (this->Key() == right.Key()); }
	T_Entry& operator= (T_Entry& right);
	void Print(ostream& ostr);					// print Entry
private:
	K _key;			// Ű
	V _value;		// ��
};

template<typename K, typename V>			// ���Կ����� = 
inline T_Entry<K, V>& T_Entry<K, V>::operator=(T_Entry& right)
{
	this->SetKey(right.Key());				// Ű ����
	this->SetVal(right.Val());				// �� ���� (�̺�Ʈ ����)

	return *this;							// ���� ��ȯ
}

template<typename K, typename V>
inline void T_Entry<K, V>::Print(ostream& ostr)			// ���
{
	// print format : [Key : _key , Event(~)]
	ostr << "[Key: " << setw(2) << this->Key() << ", "
		<< *this->Val() << "]";
}


#endif // !T_ENTRY_H

