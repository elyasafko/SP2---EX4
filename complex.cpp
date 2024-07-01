#include <cmath>
#include <stdexcept>
#include "complex.hpp"

// Default constructor - initializes the complex number to 0 + 0i
Complex::Complex() : real(0), imag(0) {}

// Parameterized constructor - initializes the complex number to real + imag*i
Complex::Complex(double r, double i) : real(r), imag(i) {}

// Copy constructor
Complex::Complex(const Complex &other) : real(other.real), imag(other.imag) {}

// Getter functions for the real and imaginary parts
double Complex::getReal() const { return real; }
double Complex::getImaginary() const { return imag; }

// Setter functions for the real and imaginary parts
void Complex::setReal(double r) { real = r; }
void Complex::setImaginary(double i) { imag = i; }

// Overloaded addition operator
Complex Complex::operator+(const Complex &other) const
{
    return Complex(real + other.real, imag + other.imag);
}

// Overloaded subtraction operator
Complex Complex::operator-(const Complex &other) const
{
    return Complex(real - other.real, imag - other.imag);
}

// Overloaded multiplication operator with a scalar
Complex Complex::operator*(double scalar) const
{
    return Complex(real * scalar, imag * scalar);
}

// Overloaded division operator with a scalar
Complex Complex::operator/(double scalar) const
{
    if (scalar == 0)
    {
        throw std::invalid_argument("Division by zero");
    }
    return Complex(real / scalar, imag / scalar);
}

// Overloaded multiplication operator with another complex number
Complex Complex::operator*(const Complex &other) const
{
    return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
}

// Overloaded division operator with another complex number
Complex Complex::operator/(const Complex &other) const
{
    double denominator = other.real * other.real + other.imag * other.imag;
    if (denominator == 0)
    {
        throw std::invalid_argument("Division by zero");
    }
    return Complex((real * other.real + imag * other.imag) / denominator,
                   (imag * other.real - real * other.imag) / denominator);
}

// Overloaded equality operator
bool Complex::operator==(const Complex &other) const
{
    return real == other.real && imag == other.imag;
}

// Overloaded inequality operator
bool Complex::operator!=(const Complex &other) const
{
    return !(*this == other);
}

// Calculate the magnitude using the formula: sqrt(real^2 + imag^2)
double Complex::magnitude() const
{
    return std::sqrt(real * real + imag * imag);
}

// Overloaded less-than operator based on the magnitude of the complex number
bool Complex::operator<(const Complex &other) const
{
    return this->magnitude() < other.magnitude();
}

bool Complex::operator>(const Complex &other) const
{
    return this->magnitude() > other.magnitude();
}

bool Complex::operator<=(const Complex &other) const
{
    return this->magnitude() <= other.magnitude();
}

bool Complex::operator>=(const Complex &other) const
{
    return this->magnitude() >= other.magnitude();
}

// Implementation of the friend function for the insertion operator <<
std::ostream &operator<<(std::ostream &os, const Complex &complex)
{
    os << complex.real;
    if (complex.imag >= 0)
    {
        os << "+" << complex.imag << "i";
    }
    else
    {
        os << complex.imag << "i";
    }
    return os;
}

// Method to convert Complex to string
std::string Complex::to_string()
{
    stringstream ss;
    ss << real << (imag >= 0 ? "+" : "") << imag << "i";
    return ss.str();
}
