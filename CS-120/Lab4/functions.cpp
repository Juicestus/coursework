# include "functions.h"
// add any includes

using std::cout, std::cin, std::endl, std::string;

void deobfuscate() {
    // TODO
}

void wordFilter() {
    // TODO
}

void passwordConverter() {
    cout << "Please enter your text input: ";
    std::string s;
    cin >> s;
    cout << "input: " << s << std::endl;
    std::string p1 = "";
    std::string p2 = "";
    for (int i = 0; i < (int)s.size(); i++) {
        char c = s[i];

        if (c == 'a') c = '@';
        else if (c == 'e') c = '3';
        else if (c == 'i') c = '!';
        else if (c == 'o') c = '0';
        else if (c == 'u') c = '^';

        p1 += c;
        p2 = c + p2;
    }
    cout << "output: " << (p1 + p2) << std::endl;
}

void wordCalculator() {
    // TODO
}

bool ispal(std::string s) {
    int l = s.size();
    for (int i = 0; i < l/2; i++) {
        if (s[i] != s[l-i-1]) {
            return false;
        }
    }
    return true;
}

void palindromeCounter() {
    int n = 0;
    cout << "Please enter a sentence (end with 'quit'): ";
    std::string s;
    while (s != "quit") {
        cin >> s;
        if (ispal(s)) n++;
    }
    printf("You have typed %d palindromes.\n", n);
}
