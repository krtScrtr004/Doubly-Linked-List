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

	myList.splice(myList.begin(), otherList);
	cout << otherList << endl;

	cout << myList << endl;

	return 0;
}

