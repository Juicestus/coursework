# ifndef ROVER_H
# define ROVER_H

# include "MyString.h"

class Rover {
	private:
		MyString savedSMILE; // MyString: default constructor

	public:
		// constructors
		Rover() : savedSMILE("") {} // MyString: parameterized constructor (const char* type)
		Rover(MyString newSMILE) : savedSMILE(newSMILE) {} // MyString: parametered constructor (MyString type), i.e., copy constructor

		// getters
		MyString getSMILE() { return savedSMILE; }

		// setters
		void setSMILE(MyString SMILE) { savedSMILE = SMILE; } // MyString: operator=(), copy assignment constructor

		// Rover chemical analysis functions
		// these are implemented in the Rover.cpp file
		void print();

		// other member functions
		void read(int n);
		void clear();
		void join(MyString input);
		MyString test(MyString input);
		bool find(MyString search);
};

# endif