#include "Fixed.hpp"

// static members must be declared outside a class
const int Fixed::fractional_bits = 8;

const int Fixed::max_raw_input = std::numeric_limits<int>::max() >> fractional_bits;
const int Fixed::min_raw_input = std::numeric_limits<int>::min() >> fractional_bits;

const float Fixed::min_input = static_cast<float>(std::numeric_limits<int>::min()) / (1 << fractional_bits);
const float Fixed::max_input = static_cast<float>(std::numeric_limits<int>::max()) / (1 << fractional_bits);

// Default Constructor
Fixed::Fixed() : value(0)
{
    std::cout<< "Default constructor called" << std::endl;
};

// Overload constructor for Int fixed value
Fixed::Fixed(const int new_value)
{
    std::cout << "Int constructor called" << std::endl;
    if (new_value > max_raw_input || new_value < min_raw_input)
    {
        std::cerr << "Error: Input int is too large for fixed-point representation." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    value = new_value << fractional_bits;
};

// Overload Constructor for Float fixed value
Fixed::Fixed(const float new_value)
{
    std::cout << "Float constructor called" << std::endl;
    if (new_value > max_raw_input || new_value < min_raw_input)
    {
        std::cerr << "Error: Input float is too large for fixed-point representation." << std::endl;
        std::exit(EXIT_FAILURE);
    }
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

