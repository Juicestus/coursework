/*
This is an interface for invoking the functions, e.g. for testing.
You do not need to submit this file.
You may modify this file, e.g. to use unit tests.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <climits>
#include "functions.h"

using std::cout, std::cin, std::endl, std::string;

enum Function: int {
    sum_is_even = 1,
    largest,
    boxes_needed,
    smarter_section,
    good_dinner,
    sum_between,
    product,
    exit_the_program
};

int read_int() {
    int number = 0;
	cout << "Please enter an integer: ";
	cin >> number;
    if (cin.fail()) {
        throw std::invalid_argument("failed to get an integer");
    }
	return number;
}

long long read_longlong() {
    long long number = 0;
	cout << "Please enter a long long integer: ";
	cin >> number;
    if (cin.fail()) {
        throw std::invalid_argument("failed to get a long long integer");
    }
	return number;
}

string process_choice(int function_id) {
    std::ostringstream oss;
    int intResult;
    long long longResult;
    bool boolResult;
    int a, b, c, d;
    long long e, f;
    try {
        switch (function_id) {
        case sum_is_even:
            a = read_int();
            b = read_int();
            boolResult = SumIsEven(a, b);
            oss << "\nSumIsEven(" << a << ", " << b << ") = ";
            oss << std::boolalpha << boolResult << endl;
            break;
        case largest:
            a = read_int();
            b = read_int();
            c = read_int();
            intResult = Largest(a, b, c);
            oss << "\nLargest(" << a << ", " << b << ", " << c << ") = ";
            oss << intResult << endl;
            break;
        case boxes_needed:
            a = read_int();
            intResult = BoxesNeeded(a);
            oss << "\nBoxesNeeded(" << a << ") = ";
            oss << intResult << endl;
            break;
        case smarter_section:
            a = read_int();
            b = read_int();
            c = read_int();
            d = read_int();
            boolResult = SmarterSection(a, b, c, d);
            oss << "\nSmarterSection(" << a << ", " << b << ", " << c << ", " << d << ") = ";
            oss << std::boolalpha << boolResult << endl;
            break;
        case good_dinner:
            a = read_int();
            b = read_int();
            boolResult = GoodDinner(a, static_cast<bool>(b));
            oss << "\nGoodDinner(" << a << ", " << b << ") = ";
            oss << std::boolalpha << boolResult << endl;
            break;
        case sum_between:
            e = read_longlong();
            f = read_longlong();
            longResult = SumBetween(e, f);
            oss << "\nSumBetween(" << e << ", " << f << ") = ";
            oss << longResult << endl;
            break;
        case product:
            e = read_longlong();
            f = read_longlong();
            longResult = Product(e, f);
            oss << "\nProduct(" << e << ", " << f << ") = ";
            oss << longResult << endl;
            break;
        }
    } catch (const std::invalid_argument& err) {
        oss << "\nthrew an invalid_argument exception: " << err.what() << endl;
    } catch (const std::overflow_error& err) {
        oss << "\nthrew an overflow_error exception: " << err.what() << endl;
    } catch (const std::exception& err) {
        oss << "\nthrew an unanticipated exception: " << err.what() << endl;
    } catch (...) {
        oss << "\nthrew an unknown thing" << endl;
    }
    return oss.str();
}

void print_menu(const string function_names[], int num_functions) {
    cout << endl << "=== Menu ===" << endl;
    for (int id = 1; id < num_functions; id++) {
        cout << id << ") " << function_names[id] << endl;
    }
    cout << ">> ";
}

int get_choice() {
    int choice;
    cin >> choice;
    if (cin.fail()) {
        std::cerr << "Input failed" << endl;
        // exit
        choice = exit_the_program;
    }
    return choice;
}
	
int main() {
    const int NUM_FUNCTIONS = 9;
    const string function_names[NUM_FUNCTIONS]= {
        "",
        "SumIsEven",
        "Largest",
        "BoxesNeeded",
        "SmarterSection",
        "GoodDinner",
        "SumBetween",
        "Product",
        "Exit the program"
        };
    int function_id;
    
    cout << "Welcome to the Debugging Homework for CS 12x!" << endl;
    cout << "Please enter a number to run the function with the corresponding number: " << endl;
	do {
        print_menu(function_names, NUM_FUNCTIONS);
        
        function_id = get_choice();
        if (function_id < 1 || function_id >= NUM_FUNCTIONS || function_id == exit_the_program) {
            // exit
            break;
        }
        
        string results = process_choice(function_id);
		if (results.empty()) {
            cout << "Invalid input detected" << endl;
            // exit
            break;
        }
        cout << results << endl;
        
        //display_results(function_id, args, function_names, num_args);
	} while(function_id != 8 && !cin.fail());
	
	cout << "Exiting program." << endl;
    
    return 0;
}
