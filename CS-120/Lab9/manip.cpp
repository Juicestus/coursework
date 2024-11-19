# include <iostream>
# include "Image.h"
# include "functions.h"

using std::cout, std::endl, std::cin;

int main() {
    Image image;
    char menuChoice = ' ';

    do {
        printMenu();
        cin >> menuChoice;
        switch (toupper(menuChoice)) {
            case 'L':
                processLoad(image);
                break;
            case 'G':
                processGreyscale(image);
                break;
            case 'S':
                processSepia(image);
                break;
            case 'A':
                processAdd(image);
                break;
            case 'Q':
                break;
            default:
                cout << endl << "'" << menuChoice << "' is not a valid option'" << endl << endl;
        }
    } while (toupper(menuChoice) != 'Q'); 
}
