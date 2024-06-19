#include <iostream>
#include "List.h"
using namespace List;

int main()
{
	list<int> myList;
	for (auto i = 0; i < 6; ++i)
		myList.push_front(i);
	cout << myList << endl;

	list<int> otherList;
	for (auto i = 10; i < 21; ++i)
		otherList.push_front(i);

	cout << otherList << endl;

	myList.splice(myList.end(), otherList, otherList.begin() + 2);
	cout << myList << endl;
	myList.print();

	cout << otherList << endl;

	return 0;
}

