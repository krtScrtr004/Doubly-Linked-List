#include <iostream>
#include "List.h"
using namespace List;

int main()
{
	list<int> myList;
	for (auto i = 0; i < 6; ++i)
		myList.push_front(i);
	cout << myList << endl;
	cout << myList.size() << endl;

	cout << endl;

	list<int> otherList;
	for (auto i = 10; i < 21; ++i)
		otherList.push_front(i);

	cout << otherList << endl;
	cout << otherList.size() << endl;
	
	cout << endl;

	myList.splice(myList.end(), otherList);
	cout << myList << endl;
	cout << myList.size() << endl;

	cout << endl;

	cout << otherList << endl;
	cout << otherList.size() << endl;

	return 0;
}

