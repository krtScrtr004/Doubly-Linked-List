#include <iostream>
#include "List.h"
using namespace List;

int main()
{
	LinkedList<int> list;
	list.PushFront(1);
	list.PushFront(2);
	list.PushFront(4);

	Iterator<int> itr = list.End();
	list.Insert(itr + 11, 15);
	cout << list;

	return 0;
}
