// TO ADD:
// 
// MERGE


#include <iostream>
#include "List.h"
using namespace List;

int main()
{
	list<int> myList;
	myList.push_back(1);
	myList.push_back(2);
	myList.push_back(3);
	myList.push_back(4);

	cout << myList << endl;
	cout << endl;

	list<int> otherList;
	for (auto i = 20; i > 10; i--)
		otherList.push_back(i);

	cout << otherList << endl;
	cout << endl;

	myList.merge(otherList);

	cout << myList << endl;
	cout << endl;

	cout << otherList << endl;
	cout << endl;


	return 0;
}

