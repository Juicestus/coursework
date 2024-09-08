#include <iostream>
#include "functions.h"

using std::cout, std::cin, std::endl;

int main() {
    cout << "Enter numbers 10 <= a <= b < 10000: ";
	
    int a, b;
    cin >> a;
    cin >> b;
    
    if (is_valid_range(a, b)) {
        cout << "Invalid Input\n";
        return 0;
    }
    count_valid_mv_numbers(a, b);
	
	return 0;
}
