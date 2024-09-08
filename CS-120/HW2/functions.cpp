#include <iostream>
#include "functions.h"

using std::cout, std::endl;

bool is_valid_range(int a, int b) {
    if (a < 10) return false;
    if (b >= 10000) return false;
    return b >= a;
}

char classify_mv_range_type(int number) {
	// TODO(student): return 'M' if number has /\/\... pattern,
	// return 'V' if number has \/\/ pattern, and return 'N' otherwise
    
    std::string s = std::to_string(number);
    int ln = s.at(0) - '0';
    std::string x = "";
    for (unsigned long i = 1; i < s.length(); i++) {
        int n = s.at(i) - '0';
        if (ln < n) {
            if (x.at(x.size() - 1) == '/') return 'N';
            x += "/";
        } else {
            if (x.at(x.size() - 1) == '\\') return 'N';
            x += "\\";
        }
        ln = n;
    }
    return x.at(0) == '/' ? 'M' : 'V';        
}

void count_valid_mv_numbers(int a, int b) {
	// TODO(student): count the number of valid mountain ranges and valley
	// ranges in the range [a, b] and print out to console using the format
	// in Requirement 4 of the homework prompt
    //
    int nm = 0, nv = 0;
    for (int i = a; i <= b; i++) {
        char t = classify_mv_range_type(i); 
        cout << "bruh\n";
         if (t == 'M') nm++;
         else if (t == 'V') nv++;
    }
    cout << "There are " << nm << " mountain ranges and " << nv << " valley ranges between " << a << " and " << b << "\n";
}
