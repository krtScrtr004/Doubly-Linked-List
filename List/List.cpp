#include <iostream>
#include "List.h"
using namespace List;

int main()
{
	list<int> myList;
	for (auto i = 0; i < 10; ++i)
		myList.push_back(i);
	cout << myList << endl;

	myList.assign(myList.begin(), myList.end(), 99);
	cout << myList << endl;
	
	return 0;
}

