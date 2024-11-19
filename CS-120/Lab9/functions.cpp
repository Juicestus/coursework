# include <iostream>
# include <fstream>
# include <cstring>
# include <cmath>
# include <limits>
# include "functions.h"

using std::cout, std::endl, std::cin, std::string, std::numeric_limits, std::streamsize;

void printMenu() {
    cout << "--------------------------" << endl;
    cout << " 'L': Load Image" << endl;
    cout << " 'G': Output Greyscale" << endl;
    cout << " 'S': Output Sepia" << endl;
    cout << " 'A': Output Add Color" << endl;
    cout << " 'Q': Quit" << endl;
    cout << "--------------------------" << endl;
    cout << endl << "Please enter your choice: ";
}

string getFilename(string prompt) {
    string filename;
    cout << prompt << ": ";
    cin >> filename;

    return filename;
}

unsigned int getColorValue(string prompt) {
    unsigned int val;

    do {
        cout << prompt;
        cin >> val;

        if (cin.fail()) {
            cout << " -- invalid color value" << endl;
            cin.clear(); // reset stream states
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer    
            val = 300;
        } else if (val > 255) {
            cout << " -- color value must be between 0 and 255" << endl;
        }
    } while (val > 255);

    return val;
}

Pixel getPixel() {
    int r, g, b;
    cout << "Enter Color Values:" << endl;
    r = getColorValue(" - Red: ");
    g = getColorValue(" - Green: ");
    b = getColorValue(" - Blue: ");

    return Pixel(r, g, b);
}

void processLoad(Image& image) {
    string filename = getFilename("Enter filename of image to load");
    image = Image(filename);

    if (image.getWidth() > 0 && image.getHeight() > 0) {
        cout << "Loaded image..." << endl;
    }
}

void processGreyscale(const Image& image) {
    Image greyscaleImage = image;
    greyscaleImage.makeGreyscale();
    string filename = getFilename("Enter filename to save greyscale image");
    greyscaleImage.output(filename);
}

void processSepia(const Image& image) {
    Image sepiaImage; 
    sepiaImage = image;
    sepiaImage.makeSepia();
    string filename = getFilename("Enter filename to save sepia image");
    sepiaImage = sepiaImage;
    sepiaImage.output(filename);
}

void processAdd(const Image& image) {
    Image addImage; 
    addImage = image;
    addImage.addColor(getPixel());
    string filename = getFilename("Enter filename to save color added image");
    addImage.output(filename);
}
