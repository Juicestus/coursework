#ifndef COMPLEX_H_
#define COMPLEX_H_


class Complex {
    double real;
    double imag;
public:
    Complex() : real(0.0), imag(0.0) {}
    Complex(double real, double imaginary) : real(real), imag(imaginary) {}
    Complex(double real) : real(real), imag(0.0) {}
    Complex(const Complex& c) : real(c.real), imag(c.imag) {} 
    double getReal() const { return real; }
    double getImaginary() const { return imag; }
    void setReal(double r) { real = r; }
    void setImaginary(double i) { imag = i; }
};

#endif 