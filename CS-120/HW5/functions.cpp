#include <iostream>

#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using std::cout, std::endl, std::string;

#define ENMAX 10000000; // > 2*3*(255^2) largest possible energy value

void initializeImage(Pixel image[][MAX_HEIGHT])
{
  // iterate through columns
  for (unsigned int col = 0; col < MAX_WIDTH; col++)
  {
    // iterate through rows
    for (unsigned int row = 0; row < MAX_HEIGHT; row++)
    {
      // initialize pixel
      image[col][row] = {0, 0, 0};
    }
  }
}

void loadImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int &width, unsigned int &height)
{
  std::ifstream file(filename.c_str());
  if (!file.is_open())
  {
    throw std::runtime_error("Failed to open " + filename);
  }

  std::string ftype;
  file >> ftype;
  if (ftype != "P3" && ftype != "p3")
  {
    throw std::runtime_error("Invalid type " + ftype);
  }

  file >> width >> height;

  if (width <= 0 || height <= 0 || height >= MAX_HEIGHT || width >= MAX_WIDTH)
  {
    throw std::runtime_error("Invalid dimensions");
  }

  int color;
  file >> color;
  if (color != 255)
  {
    throw std::runtime_error("Invalid max color value");
  }

  for (unsigned int row = 0; row < height; row++)
  {
    for (unsigned int col = 0; col < width; col++)
    {
      Pixel pixel;
      int r, g, b;
      file >> r >> g >> b;
      if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        throw std::runtime_error("Invalid color value");
      }
      if (file.fail())
        throw std::runtime_error("Not enough values");
      pixel.r = r;
      pixel.g = g;
      pixel.b = b;
      image[col][row] = pixel;
    }
  }

  int _;
  file >> _;
  if (!file.fail())
    throw std::runtime_error("Too many values");
}

void outputImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height)
{

  std::ofstream file(filename.c_str());
  if (!file.is_open())
  {
    throw std::runtime_error("Failed to open " + filename);
  }
  file << "P3\n";
  file << width << " " << height << "\n";
  file << "255\n";

  for (unsigned int row = 0; row < height; row++)
  {
    for (unsigned int col = 0; col < width; col++)
    {
      Pixel pixel = image[col][row];
      file << pixel.r << " " << pixel.g << " " << pixel.b << " ";
    }
    file << "\n";
  }
}

#define ppix(p)                                                   \
  {                                                               \
    std::cout << "(" << p.r << " " << p.g << " " << p.b << ")\n"; \
  }

unsigned int solveAxisGradient(Pixel l, Pixel h)
{
  // ppix(l);
  // ppix(h);
  int d_r = h.r - l.r;
  int d_g = h.g - l.g;
  int d_b = h.b - l.b;
  return d_r * d_r + d_g * d_g + d_b * d_b;
}

unsigned int energy(Pixel image[][MAX_HEIGHT], unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{

  int l_x = x - 1;
  if (l_x < 0)
    l_x = width - 1;
  uint r_x = x + 1;
  if (r_x >= width)
    r_x = 0;

  int l_y = y - 1;
  if (l_y < 0)
    l_y = height - 1;
  uint r_y = y + 1;
  if (r_y >= height)
    r_y = 0;

  unsigned int g_x = solveAxisGradient(
      image[l_x][y], image[r_x][y]);
  // cout << g_x << " ";
  unsigned int g_y = solveAxisGradient(
      image[x][l_y], image[x][r_y]);
  // cout << g_y << " ";
  unsigned int en = g_x + g_y;
  // cout << en << endl;

  return en;
}

// uncomment functions as you implement them (part 2)

unsigned int loadVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_col, unsigned int width, unsigned int height, unsigned int seam[]) {

    seam[0] = start_col;
    long en_total = energy(image, start_col, 0, width, height);

    //unsigned int col = start_col;
    for (unsigned int row = 1, col = start_col; row < height; row++) {
        int en = energy(image, col, row, width, height);
        int en_l = col >= 1 ? energy(image, std::max((int)col - 1, 0), row, width, height) : ENMAX;
        int en_r = (col + 1) < width ? energy(image, std::min(col + 1, width-1), row, width, height) : ENMAX;
    
        int change_col = 0;
        if (en_r < en) {
            en = en_r;
            change_col = 1;
        }
        if (en_l < en) {
            en = en_l;
            change_col = -1;
        }
        col += change_col;
        seam[row] = col;

        en_total += en;
    }
    return en_total;
}

// unsigned int loadHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_row, unsigned int width, unsigned int height, unsigned int seam[]) {
//   // TODO: implement (part 2)
//   return 0;
// }

void findMinVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[]) {
    unsigned int best_seam = 0, lowest_en = ENMAX;
    for (unsigned int i = 0, en; i < width; i++) {
        if ((en = loadVerticalSeam(image, i, width, height, seam)) < lowest_en) {
            best_seam = i;
            lowest_en = en;
        }
    }
    loadVerticalSeam(image, best_seam, width, height, seam);
}

// void findMinHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[]) {
//   // TODO: implement (part 2)
// }

void removeVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int& width, unsigned int height, unsigned int verticalSeam[]) {
    width -= 1;
    for (unsigned int row = 0; row < height; row++) {
        for (unsigned int col = verticalSeam[row]; col < width; col++) {
            image[col][row] = image[col+1][row];
        }
    }
}

// void removeHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int& height, unsigned int horizontalSeam[]) {
//   // TODO: implement (part 2)
// }
