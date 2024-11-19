# include <ostream>
# include <cmath>
# include "Pixel.h"

using std::ostream;

Pixel::Pixel(int r, int g, int b) : r(getValidColor(r)), g(getValidColor(g)), b(getValidColor(b)) {}

Pixel::Pixel() : r(0), g(0), b(0) {}

int Pixel::getRed() const {
    return r;
}

int Pixel::getGreen() const {
    return g;
}

int Pixel::getBlue() const {
    return b;
}

void Pixel::setRed(int r) {
    this->r = getValidColor(r);
}

void Pixel::setGreen(int g) {
    this->g = getValidColor(g);
}

void Pixel::setBlue(int b) {
    this->b = getValidColor(b);
}

Pixel Pixel::operator+(const Pixel& p) {
    return Pixel((this->r + p.r) / 2, (this->g + p.g) / 2, (this->b + p.b) / 2);
}

int Pixel::getValidColor(int v) {
    if (v < 0) {
        v = 0;
    }
    if (v > 255) {
        v = 255;
    }
    return v;
}

std::ostream& operator<<(std::ostream& os, const Pixel& p) {
    os << "(" << p.getRed() << ", " << p.getGreen() << ", " << p.getBlue() << ")";
    return os;
}
