#include <iostream>
#include "functions.h"
using namespace std;

// simple helper function to print array
void printarr(int* arr, int size)
{
	cout << "[";
	for(int i=0; i < size; i++)
	{
		cout << arr[i];
		if(i != size-1)
			cout << ", ";
	}		
	cout << "]";
	
}

// testing code provided for convenience
int main() {	
	/* function_one() */ {
		int i = 2;
		int j = 2;

		cout << "---function_one()---\n\n";
		cout << "\tValues before execution:\n";
		cout << "\ti: " << i << '\n';
		cout << "\tj: " << j << '\n';

		function_one(i, j);
		cout << "\n\tfunction called\n\n";

		cout << "\tValues after execution:\n";
		cout << "\ti: " << i << '\n';
		cout << "\tj: " << j << '\n';
	}	 
		 
	/* function_two() */ {
		example foo;

		cout << "\n---function_two()---\n\n";
		cout << "\tValue before execution: " << foo.value << '\n';

		function_two(foo);
		cout << "\n\tfunction called\n\n";

		cout << "\tValue after execution: " << foo.value << '\n';
	}
	
	/* function_three() */ {
		int a = 4;
		int b = 4;
		
		cout << "\n---function_three()---\n\n";
		cout << "\tValues before execution:\n";
		cout << "\ta: " << a << '\n';
		cout << "\tb: " << b << '\n';

		function_three(&a, b);
		cout << "\n\tfunction called\n\n";

		cout << "\tValues after execution:\n";
		cout << "\ta: " << a << '\n';
		cout << "\tb: " << b << '\n';
	}
	
	/* function_four() */ {
		int * bar = new int[5]{3, 6, 4, -5, 5};
		int lowest = 0;
		int highest = 0;
		
		cout << "\n---function_four()---\n\n";
		cout << "\tValues before execution:\n";
		cout << "\tlowest: " << lowest << '\n';
		cout << "\thighest: " << highest << '\n';
		cout << "\tarray: "; printarr(bar, 5); cout << '\n';

		function_four(bar, 5, lowest, highest);
		cout << "\n\tfunction called\n\n";

		cout << "\tValues after execution:\n";
		cout << "\tlowest: " << lowest << '\n';
		cout << "\thighest: " << highest << '\n';
		cout << "\tarray: "; printarr(bar, 5); cout << '\n';
		
		delete [] bar;
	}
}