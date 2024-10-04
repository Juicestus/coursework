#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

// struct for Pixel (short is a 2 byte signed integer)
struct Pixel {
  short r; // red
  short g; // green
  short b; // blue
};

// maximum image dimensions (do not change)
const unsigned int MAX_WIDTH = 1920;
const unsigned int MAX_HEIGHT = 1080;

// already implemented
void initializeImage(Pixel image[][MAX_HEIGHT]);

// TODO: implement (part 1)
void loadImage(std::string filename, Pixel image[][MAX_HEIGHT], unsigned int& width, unsigned int& height);
void outputImage(std::string filename, Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height);
unsigned int energy(Pixel image[][MAX_HEIGHT], unsigned int x, unsigned int y, unsigned int width, unsigned int height);

// TODO: uncomment and implement (part 2)
// unsigned int loadVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_col, unsigned int width, unsigned int height, unsigned int seam[]);
// unsigned int loadHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_row, unsigned int width, unsigned int height, unsigned int seam[]);
// void findMinVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[]);
// void findMinHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[]);
// void removeVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int& width, unsigned int height, unsigned int verticalSeam[]);
// void removeHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int& height, unsigned int horizontalSeam[]);

#endif