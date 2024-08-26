#include <iostream>
#include <limits>
#include "boolean_functions.h"
using std::cin, std::cout, std::endl, std::string, std::boolalpha;

bool getBoolVal(string varName) {
    char boolChar = ' ';
    while (tolower(boolChar) != 't' && tolower(boolChar) != 'f') {
        cout << "Input T for true and F for false." << endl;
        cout << "Input value for " << varName << ": ";
        cin >> boolChar;
    }
    if (tolower(boolChar) == 't') {
        return true;
    }
    return false;
}

void processBooleanLogic1() {
    bool x = getBoolVal("x");
    bool y = getBoolVal("y");
    bool z = getBoolVal("z");
    cout << "x (" << boolalpha << x << ")" << endl;
    cout << "y (" << boolalpha << y << ")" << endl;
    cout << "z (" << boolalpha << z << ")" << endl;
    booleanLogic1(x, y, z);
}

void processBooleanLogic2() {
    bool x = getBoolVal("x");
    bool y = getBoolVal("y");
    bool z = getBoolVal("z");
    cout << "x (" << boolalpha << x << ")" << endl;
    cout << "y (" << boolalpha << y << ")" << endl;
    cout << "z (" << boolalpha << z << ")" << endl;
    booleanLogic2(x, y, z);
}

void processBooleanLogic3() {
    bool x = getBoolVal("x");
    bool y = getBoolVal("y");
    bool z = getBoolVal("z");
    cout << "x (" << boolalpha << x << ")" << endl;
    cout << "y (" << boolalpha << y << ")" << endl;
    cout << "z (" << boolalpha << z << ")" << endl;
    booleanLogic3(x, y, z);
}

void processCountLetters() {
    string str;
    cout << "Enter string: ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::getline(cin, str);
    unsigned int cnt = countLetters(str);
    cout << "String: " << str << endl;
    cout << "Num Letters: " << cnt << endl;
}

void processMystery() {
    bool x = getBoolVal("x");
    bool y = getBoolVal("y");
    bool z = getBoolVal("z");
    cout << "x (" << boolalpha << x << ")" << endl;
    cout << "y (" << boolalpha << y << ")" << endl;
    cout << "z (" << boolalpha << z << ")" << endl;
    f(x, y, z);
}

void processSetAssignments() {
    bool w = getBoolVal("w");
    bool x = getBoolVal("x");
    bool y = getBoolVal("y");
    bool z = getBoolVal("z");
    cout << "w (" << boolalpha << w << ")" << endl;
    cout << "x (" << boolalpha << x << ")" << endl;
    cout << "y (" << boolalpha << y << ")" << endl;
    cout << "z (" << boolalpha << z << ")" << endl;
    setAssignments(w, x, y, z);
}

void processSelection(int selection) {
    switch (selection) { // tolower lets X or x be valid
        case 1: printNOT(); break;
        case 2: printOR(); break;
        case 3: printAND(); break;
        case 4: printXOR(); break;
        case 5: processBooleanLogic1(); break;
        case 6: processBooleanLogic2(); break;
        case 7: processBooleanLogic3(); break;
        case 8: processCountLetters(); break;
        case 9: processMystery(); break;
        case 10: processSetAssignments(); break;
        case 0: break;
        default: cout << selection << " is not a valid option." << endl;
    }
}

int getChoice() {
    int selection = -1;
    cout << "Input number for the booleanLogic function to run (1 - 9)" << endl;
    cout << "Input 0 to exit" << endl;
    cout << "Choice: ";
    cin >> selection;
    return selection;
}

int main() {
    int selection = -1;
    while (tolower(selection) != 0) {
        selection = getChoice();
        processSelection(selection);
    }

}