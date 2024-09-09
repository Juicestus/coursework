#include <iostream>
#include "cstring.h"

using std::cin, std::cout, std::endl;

int main() {
  char test1[] = "Hello";
  char test2[] = "hello";
  char test3[] = "hello";
  char a = 'l';
  char b = 'z';
  cout << "length of " << test1 << ": " << length(test1) << endl;
  cout << "index of '" << a <<"': " << find(test1, a) << endl;
  cout << "index of '" << b <<"': " << find(test1, b) << endl;
  cout << test1 << " is ";
  if (!equalStr(test1, test2)) {
    cout << "not ";
  }
  cout << "equal to " << test2 << endl;
  cout << test2 << " is ";
  if (!equalStr(test2, test3)) {
    cout << "not ";
  }
  cout << "equal to " << test3 << endl;
  
  // unpredictible
  //  - Using test4 as a cstring is problematic since
  //    it does not have the terminating '\0'
  //char test4[] = {'H', 'E', 'L', 'L', 'O'}; // not a cstring
  //cout << "length of " << test4 << ": " << length(test4) << endl;
  
}

