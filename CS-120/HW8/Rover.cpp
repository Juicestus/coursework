# include <iostream>
# include "Rover.h"
# include "MyString.h"

using std::cout, std::endl;

void Rover::print() {
	cout << savedSMILE << endl; // MyString: operator<<()
}

void Rover::read(int n) {
	cout << savedSMILE.at(n) << endl; // MyString: at()
}

void Rover::clear() {
	if (!savedSMILE.empty()) { // MyString: empty()
		savedSMILE.clear(); // MyString: clear()
	}
}

void Rover::join(MyString input) {
	savedSMILE += input; // MyString: operator+=()
}

MyString Rover::test(MyString input) {
	MyString tester(savedSMILE); // MyString: copy constructor
	tester += input; // MyString: operator+=()
	return tester; // MyString: destructor
}

bool Rover::find(MyString search) {
	int index = savedSMILE.find(search);
	return index >= 0; // MyString: find()
}
