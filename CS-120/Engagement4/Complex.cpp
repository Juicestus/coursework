#include "Complex.h"
#include <sstream>
#include <string>

double Complex::getReal() { return real; }
double Complex::getImaginary() {return imag; }
void Complex::setReal(double real) { this->real = real; }
void Complex::setImaginary(double imaginary) { this->imag = imaginary; }
std::string Complex::to_string() {
  std::ostringstream oss;
  oss << real;
  if (imag < 0) { // negative imag
    oss << " - " << (-1*imag);
  }
  else {
    oss << " + " << imag;
  }
  oss << "i";
  return oss.str();
}

Complex Complex::operator+(Complex a) {
  return Complex(a.getReal() + this->getReal(), a.getImaginary() + this->getImaginary());
}

Complex Complex::operator-( Complex a) {
  return Complex(-a.getReal(), -a.getImaginary());
}

Complex Complex::operator=(Complex a) {
  return Complex(a);
}

bool Complex::operator==(Complex a) {
  return a.getReal() == this->getReal() && a.getImaginary() == this->getImaginary();
}





