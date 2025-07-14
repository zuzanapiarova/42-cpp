#include "Fixed.hpp"

// static members must be declared outside a class, in namespace of that class of course, without static keyword
const int Fixed::fractional_bits = 8;

// Default Constructor
Fixed::Fixed() : value(0)
{
    std::cout<< "Default constructor called" << std::endl;
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
};

// Getter function
int Fixed::getRawBits( void ) const
{
    std::cout << "getRawBits member function called" << std::endl;
    return value;
};

// Setter function
void Fixed::setRawBits( int const raw )
{
    std::cout << "setRawBits member function called" << std::endl;
    value = raw;
};