# ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include <string>
# include "Image.h"

void printMenu();
std::string getFilename(std::string prompt);
unsigned int getColorValue(std::string prompt);
Pixel getPixel();
void processLoad(Image& image);
void processGreyscale(const Image& image);
void processSepia(const Image& image);
void processAdd(const Image& image);
  
# endif
