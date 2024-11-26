#include <iostream>
#include "linked_list.h"

using std::cout, std::endl;

int main() {
      MyList list;
   list.add("Juan", 95);
   list.add("Jill", 98);
   list.insert("Joon", 90, 1);
   cout << list << endl;
   return 0;


}
