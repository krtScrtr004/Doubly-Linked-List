// TO ADD:
// MAX & MIN
// SORT FUNC
// MERGE
// REVERSE

#include <iostream>
#include "List.h"
using namespace List;

int main()
{
	list<int> myList;
	for (auto i = 0; i < 6; ++i)
		myList.push_front(i);
	cout << myList << endl;
	
	myList.reverse();
	cout << myList << endl;

	return 0;
}

