#ifndef VECTOR_HANDLER_H
#define VECTOR_HANDLER_H

#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
void printVector(vector<T>& v)
{
	string typeName = typeid(T).name();
	cout << "Vector size(" << v.size() << "), elements : \n";
	typename vector<T>::iterator p;

	for (p = v.begin(); p != v.end(); p++)
	{
		cout << *p << " ";
		if ((typeName == "class Date") || (typeName == "class Time"))
			continue;
		else
			cout << endl;
	}
	cout << endl;
}
#endif // !VECTOR_HANDLER_H
