#include <iostream>
#include "List.h"
using namespace List;

int main()
{
	LinkedList<int> list;
	list.PushBack(1);
	list.PushBack(2);
	list.PushBack(4);

	Iterator<int> itr = list.Begin();
	cout << list << endl;

	LinkedList<int> list2 = list;
	cout << list2;

	return 0;
}

