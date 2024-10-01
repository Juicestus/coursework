# include "functions.h"

using std::cout, std::cin;

// driver program
int main() {
    char selection = 0;

    while (selection != 'q') {
        cout << "(1) Deobfuscate\n(2) Word Filter\n(3) Password Converter\n(4) Word Calculator\n(5) Palindrome Counter\n(q) Quit Program\nSelect a function to run: ";
        cin >> selection;
        cin.clear();
        cin.ignore();

        cout << '\n';

        switch (selection) {
            case '1':
                deobfuscate();
                break;
            case '2':
                wordFilter();
                break;
            case '3':
                passwordConverter();
                break;
            case '4':
                wordCalculator();
                break;
            case '5':
                palindromeCounter();
                break;
            case 'q':
                cout << "Quitting\n";
                break;
            default:
                cout << "Invaid input\n";
        }

        cout << '\n';
    }

    return 0;
}