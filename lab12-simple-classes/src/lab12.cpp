#include "lab12.h"

double mesa::clock::time() {
	return t;
}

void mesa::clock::time(double val) {
	t = val;
}

complex::complex(double realVal, double imaginaryVal) : 
	realVal(realVal), imaginaryVal(imaginaryVal) {}

double complex::real() { return realVal; }
double complex::imaginary() { return imaginaryVal; }