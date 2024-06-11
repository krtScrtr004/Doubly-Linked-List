#include <iostream>
#include "List.h"
using namespace List;

int main()
{
	LinkedList<int> list;
	list.PushBack(1);
	list.PushBack(2);
	list.PushBack(4);

	/*Iterator<int> itr = list.End();
	list.Insert(itr, 15);*/
	cout << list;

	return 0;
}
