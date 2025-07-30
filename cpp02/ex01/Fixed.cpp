#include "Fixed.hpp"

// static members must be declared outside a class
const int Fixed::s_fractional_bits = 8;

// max value without the fractional part - 23 bits
const int Fixed::max_input = std::numeric_limits<int>::max() >> Fixed::s_fractional_bits; // 8388607
const int Fixed::min_input = std::numeric_limits<int>::min() >> Fixed::s_fractional_bits; // -8388608

// Default Constructor
Fixed::Fixed() : value()
{
    std::cout<< "Fixed default constructor called. " << std::endl;
};

// Overload constructor for Int fixed value
Fixed::Fixed(const int new_value)
{
    std::cout << "Fixed Int constructor called. " << std::endl;
    if (new_value > max_input)
    {
        std::cerr << "Error: Input int is too large for fixed-point representation. Using maximum allowed value instead." << std::endl;
        value = max_input << s_fractional_bits;
    }
    else if (new_value < min_input)
    {
        std::cerr << "Error: Input int is too small for fixed-point representation. Using minimum allowed value instead." << std::endl;
        value = min_input << s_fractional_bits;
    }
    else
        value = new_value << s_fractional_bits;
};

// Overload Constructor for Float fixed value
Fixed::Fixed(const float new_value)
{
    std::cout << "Fixed Float constructor called. " << std::endl;
    if (new_value > max_input)
    {
        std::cerr << "Error: Input float is too large for fixed-point representation. Using maximum allowed value instead." << std::endl;
        value = max_input << s_fractional_bits;
    }
    else if (new_value < min_input)
    {
        std::cerr << "Error: Input float is too small for fixed-point representation. Using minimum allowed value instead." << std::endl;
        value = min_input << s_fractional_bits;
    }
    else
        value = static_cast<int>(roundf(new_value * (1 << s_fractional_bits)));
};

// Copy Constructor
Fixed::Fixed(const Fixed& origin)
{
    std::cout << "Fixed copy constructor called. " << std::endl;
    this->value = origin.value;
};

// Copy Assignment Operator
Fixed& Fixed::operator = (const Fixed& origin)
{
    std::cout << "Fixed copy assignment operator called. " << std::endl;
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
    std::cout << "Fixed destructor called." << std::endl;
};

// Getter function
int Fixed::getRawBits( void ) const
{
    return value;
};

// Setter function
void Fixed::setRawBits( int const raw )
{
    value = raw;
};

// Convert Fixed to Float
float Fixed::toFloat( void ) const
{
    return static_cast<float>(value) / (1 << s_fractional_bits);
};

// Convert Fixed to Int
int Fixed::toInt( void ) const
{
    return value >> s_fractional_bits;
};

