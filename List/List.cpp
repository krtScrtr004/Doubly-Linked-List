// TO ADD:
// ITR.pointed_

#include <iostream>
#include "List.h"
using namespace List;

int main()
{
	list<int> myList;
	iterator<int> itr = myList.begin();
	for (auto i = 5; i > 0; --i)
		myList.push_back(i);

	for (auto nd : myList)
		std::cout << nd << std::endl;

	//std::cout << *myList.end() << std::endl;

	/*list<int> otherList(myList);

	myList.push_back(3123);

	std::string i; 
	if (otherList < myList)
		i = "Yes";
	else
		i = "no";

	cout << myList << endl;
	cout << otherList << endl;
	cout << i << endl;*/

	return 0;
}

