#include "Fixed.hpp"

// static members must be declared outside a class
const int Fixed::fractional_bits = 8;

// -------------------------------------------- Orthodox Canonical Form ---------------------------------------------

// Default Constructor
Fixed::Fixed() : value(0)
{
    std::cout<< "Default constructor called" << std::endl;
};

// Overload Constructor from Int
Fixed::Fixed(const int new_value)
{
    std::cout << "Int constructor called" << std::endl;
    value = new_value << fractional_bits;
};

// Overload Constructor from Float
Fixed::Fixed(const float new_value)
{
    std::cout << "Float constructor called" << std::endl;
    value = static_cast<int>(roundf(new_value * (1 << fractional_bits)));
};

// Copy Constructor
Fixed::Fixed(const Fixed& origin)
{
    std::cout << "Copy constructor called" << std::endl;
    this->value = origin.value;
};

// Copy Assignment Operator
Fixed& Fixed::operator = (const Fixed& origin)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &origin)
        this->value = origin.value;
    return *this;
};

// Destructor
Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

// -------------------------------------------- Member Functions ---------------------------------------------

int Fixed::getRawBits( void ) const
{
    // std::cout << "getRawBits member function called" << std::endl;
    return value;
};

void Fixed::setRawBits( int const raw )
{
    // std::cout << "setRawBits member function called" << std::endl;
    value = raw;
};

// ! maybe add .0 if the number is a full int? so it is 10.0, not 10
float Fixed::toFloat( void ) const
{
    return static_cast<float>(value) / (1 << fractional_bits);

};

int Fixed::toInt( void ) const
{
    return value >> fractional_bits;
};

// --------------------------------------- External Operator Overloading ---------------------------------------------

// Overload Insertion Operator <<
std::ostream& operator <<(std::ostream& os, const Fixed& fixed)
{
    os << fixed.toFloat();
    return os;
}

// -------------------------------------------- Comparison Operators ---------------------------------------------

Fixed& Fixed::operator < (const Fixed& other) {};

Fixed& Fixed::operator <= (const Fixed& other) {};

Fixed& Fixed::operator > (const Fixed& other) {};

Fixed& Fixed::operator >= (const Fixed& other) {};

Fixed& Fixed::operator == (const Fixed& other) {};

Fixed& Fixed::operator != (const Fixed& other) {};

// -------------------------------------------- Arithmetic Operators ---------------------------------------------

Fixed& Fixed::operator + (const Fixed& other) {};

Fixed& Fixed::operator - (const Fixed& other) {};

Fixed& Fixed::operator * (const Fixed& other) {};

Fixed& Fixed::operator / (const Fixed& other) {};

// --------------------------------------- Increment / Decrement Operators ---------------------------------------------

// pre-increment (++a) - this operator modifies the object (*this) in-place
// it returns a reference to the current object (*this) so you can chain operations or observe the updated value immediately

// Pre-increment
Fixed& Fixed::operator ++ ( void ) {};

// Pre-decrement
Fixed& Fixed::operator -- ( void ) {};

// post-increment (a++) - this operator must return the original value before the increment, so it makes a copy of the current object, then increments the current one
// you cannot return a reference here because the result is a temporary copy — returning a reference to that would be unsafe and incorrect
// the int is just a dummy to differentiate it from pre-increment

// Post-increment
Fixed Fixed::operator ++ ( int ) {};

// Post-decrement
Fixed Fixed::operator -- ( int ) {}; 

// -------------------------------------------- Min / Max Functions ---------------------------------------------

// If min and max don't depend on any internal state of a specific Fixed object (which they shouldn't), then they should be declared static.

Fixed& Fixed::min(Fixed& first, Fixed& second) {};

Fixed& Fixed::max(Fixed& first, Fixed& second) {};

Fixed& Fixed::min(const Fixed& first, const Fixed& second) {};

Fixed& Fixed::max(const Fixed& first, const Fixed& second) {};