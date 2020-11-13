#include <iostream>
#include <../memorylib/Stack.h>
#include <../memorylib/MultiStack.h>

using namespace std;
int main()
{
	TMultiStack<int> A(9, 3);
	A.push(3, 0);
	A.push(2, 1);
	A.push(-1, 0);
	A.push(5, 0);
	A.push(6, 1);
	A.push(-1, 0);
	A.push(5, 0);

	cout << A.stack_with_max_elem();

	return 0;
	
}
