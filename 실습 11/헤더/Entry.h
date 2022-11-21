#ifndef ENTRY_H
#define ENTRY_H

#include <iostream>
#include <iomanip>
#include <string>


using namespace std;

template<typename K, typename V>
class Entry
{
	friend ostream& operator<< (ostream& ostr, Entry<K, V>& entry)
	{
		ostr << "[ Key : " << entry.Key() << ", "
			<< "Value : " << entry.Val() << " ]";
		return ostr;
	}
public:
	// constructor
	Entry() {};
	Entry(const K& k, const V& v) : _key(k), _value(v) {};

	// setter
	void SetKey(const K& key) { _key = key; }
	void SetVal(const V& value) { _value = value; }

	// getter
	K Key() const { return _key; }
	V Val() const { return _value; }

	// printing  function
	void fprint(ostream ostr)
	{
		ostr << "[ Key : " << this->Key() << ", "
			<< "Value : " << this->Val() << " ]";
		return ostr;
	}

	// operator overloading 
	bool operator>(const Entry<K, V>& right) const { return (this->Key() > right.Key()); }
	bool operator>=(const Entry<K, V>& right) const { return (this->Key() >= right.Key()); }
	bool operator<(const Entry<K, V>& right) const { return (this->Key() < right.Key()); }
	bool operator<=(const Entry<K, V>& right) const { return (this->Key() <= right.Key()); }
	bool operator==(const Entry<K, V>& right) const { return (this->Key() == right.Key()); }
	Entry<K, V>& operator= (const Entry<K, V>& right)
	{
		this->SetKey(right.Key());	this->SetVal(right.Val());
		return *this;
	}
	
private:
	K _key;
	V _value;

};
#endif // !ENTRY_H

