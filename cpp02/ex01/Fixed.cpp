#include "Fixed.hpp"

// static members must be declared outside a class
const int Fixed::fractional_bits = 8;

const int Fixed::max_input = std::numeric_limits<int>::max() >> Fixed::fractional_bits; // 8388607
const int Fixed::min_input = std::numeric_limits<int>::min() >> Fixed::fractional_bits; // -8388608

const int Fixed::max_raw_value = Fixed::max_input << Fixed::fractional_bits; // 2,147,483,392
const int Fixed::min_raw_value = Fixed::min_input << Fixed::fractional_bits; // -2,147,483,648

// Default Constructor
Fixed::Fixed() : value(0)
{
    std::cout<< "Default constructor called" << std::endl;
};

// Overload constructor for Int fixed value
Fixed::Fixed(const int new_value)
{
    std::cout << "Int constructor called" << std::endl;
    if (new_value > max_input)
    {
        std::cerr << "Error: Input int is too large for fixed-point representation. Using maximum allowed value instead." << std::endl;
        value = max_raw_value;
    }
    else if (new_value < min_input)
    {
        std::cerr << "Error: Input int is too small for fixed-point representation. Using minimum allowed value instead." << std::endl;
        value = min_raw_value;
    }
    else
        value = new_value << fractional_bits;
};

// Overload Constructor for Float fixed value
Fixed::Fixed(const float new_value)
{
    std::cout << "Float constructor called" << std::endl;
    if (new_value > max_input)
    {
        std::cerr << "Error: Input float is too large for fixed-point representation. Using maximum allowed value instead." << std::endl;
        value = max_raw_value;
    }
    else if (new_value < min_input)
    {
        std::cerr << "Error: Input float is too small for fixed-point representation. Using minimum allowed value instead." << std::endl;
        value = min_raw_value;
    }
    else
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

// Overload Insertion Operator <<
std::ostream& operator <<(std::ostream& os, const Fixed& fixed)
{
    os << fixed.toFloat();
    return os;
}

// Destructor
Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
};

// Getter function
int Fixed::getRawBits( void ) const
{
    // std::cout << "getRawBits member function called" << std::endl;
    return value;
};

// Setter function
void Fixed::setRawBits( int const raw )
{
    // std::cout << "setRawBits member function called" << std::endl;
    value = raw;
};

// Convert Fixed to Float
float Fixed::toFloat( void ) const
{
    return static_cast<float>(value) / (1 << fractional_bits);
};

// Convert Fixed to Int
int Fixed::toInt( void ) const
{
    return value >> fractional_bits;
};

