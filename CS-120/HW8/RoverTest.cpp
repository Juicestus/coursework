# include <iostream>
# include <fstream>
# include "Rover.h"
# include "MyString.h"
using std::cin, std::cout, std::endl, std::ifstream, std::istream;

// helper function "stoi" to converts MyString to int, works a lot like number slicing in reverse
int stoi(const MyString& str) { // just doing base 10 here
	int result = 0;
	for (unsigned int i = 0; i < str.size(); i++) { // MyString: size()
		if (str.at(i) >= '0' && str.at(i) <= '9') { // MyString: at()
			result *= 10; // increase digit (reverse of number slicing)
			result += str.at(i) - 48; // using ascii for conversion
		}
	}
	return result;
}

// helper function for insertion allows reading from input stream to MyString
istream& operator>>(istream& is, MyString& str) {
	str.clear();
	while (!is.eof()) {
		char c;
		is >> std::noskipws >> c; // use the noskipws manipulator
		if (isspace(c) || is.fail()) break; // if whitespace, can stop adding to string
		const char* newstr = new char[2] {c, '\0'};
		MyString newc = MyString(newstr); // MyString: copy constructor
		delete[] newstr;
		str += newc; // MyString: operator+=()
	}
	return is;
}


int main () {
	// open command file
	MyString filename; // MyString: default constructor
	cin >> filename; // operator>> is provided above

	ifstream commands(filename.data()); // MyString: data() return const char* type (otherwise, have to implement ifstream constructor for MyString type)

	if (!commands.is_open()) {
		cout << "Unable to open file" << endl;
		return 1;
	}

	// setup test rover
	Rover testRover;

	// read commands
	MyString comm;
	MyString data;
	while (!commands.eof()) {
		commands >> comm;

		if (comm.front() == 'P') { // MyString: front()
			testRover.print();
			continue;
		}

		if (comm.front() == 'C') {
			testRover.clear();
			continue;
		}

		commands >> data;

		switch (comm.front()) {
			case 'S':
				testRover.setSMILE(data);
				break;
			case 'R':
				testRover.read(stoi(data)); // stoi is provided above
				break;
			case 'J':
				testRover.join(data);
				break;
			case 'T':
				cout << testRover.test(data) << endl;
				break;
			case 'F':
				cout << data << " "; // MyString: operator<<()
				if (testRover.find(data)) {
					cout << "was found" << endl;
				} else {
					cout << "was not found" << endl;
				}
				break;
			default:
				continue;
		}
	}

	return 0;
}



// int main() {
// 	MyString str = MyString("obungus");
// 	cout << str << endl;
// 	str += MyString("blah blah blah");
// 	cout << str << endl;
// 	str += MyString("funk pants");
// 	cout << str << endl;

// 	MyString str2 = (str);
// 	cout << str2 << endl;

// 	cout << str2.find(MyString("")) << endl;

// 	cout << (str == str2 ? "yes!" : "no!") << endl;
// 	cout << str + str2 << endl;
// }