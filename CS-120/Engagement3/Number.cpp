#include <iostream>


#include "Complex.h"

int main() {
    // call constructors and output values
    Complex a;
    //cout << "a.real: " << a.getReal() << endl;
    //cout << "a.imag: " << a.getImaginary() << endl;

    Complex b(2.5, 3.8);
    //cout << "b.real: " << b.getReal() << endl;
    //cout << "b.imag: " << b.getImaginary() << endl;

    Complex c(5.7);
    //cout << "c.real: " << c.getReal() << endl;
    //cout << "c.imag: " << c.getImaginary() << endl;

    Complex d(b);
    //cout << "d.real: " << d.getReal() << endl;
    //cout << "d.imag: " << d.getImaginary() << endl;

    // change values and output
    //a.setReal(9.2);
    //a.setImaginary(2.4);
    //cout << "a.real: " << a.getReal() << endl;
    //cout << "a.imag: " << a.getImaginary() << endl;
}
