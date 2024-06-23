// TO ADD:
// ITR.pointed_

#include <iostream>
#include "List.h"
using namespace List;

int main()
{
	list<int> myList;
	iterator<int> itr = myList.begin();
	for (auto i = 100; i > 0; --i)
		myList.push_back(i);

	cout << myList << endl;

	return 0;
}

