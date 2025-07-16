#include "Fixed.hpp"

// static members must be declared outside a class
const int Fixed::fractional_bits = 8;

const int Fixed::max_raw_input = std::numeric_limits<int>::max() >> fractional_bits;
const int Fixed::min_raw_input = std::numeric_limits<int>::min() >> fractional_bits;

const float Fixed::min_input = static_cast<float>(std::numeric_limits<int>::min()) / (1 << fractional_bits);
const float Fixed::max_input = static_cast<float>(std::numeric_limits<int>::max()) / (1 << fractional_bits);

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
    if (new_value > max_raw_input || new_value < min_raw_input)
    {
        std::cerr << "Error: Input int is too large for fixed-point representation." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    value = new_value << fractional_bits;
};

// Overload Constructor from Float
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

// in C++, when overloading operators as member functions, object left of operator is always the one the function is called on (== this)
// object right of operator is used as parameter
// eg. when doing a < b, it's internally treated like a.operator<(b);

bool Fixed::operator < (const Fixed& other) const
{
    return this->value < other.value;
};

bool Fixed::operator <= (const Fixed& other) const
{
    return this->value <= other.value;
};

bool Fixed::operator > (const Fixed& other) const
{
    return this->value > other.value;
};

bool Fixed::operator >= (const Fixed& other) const
{
    return this->value >= other.value;
};

bool Fixed::operator == (const Fixed& other) const
{
    return this->value == other.value;
};

bool Fixed::operator != (const Fixed& other) const
{
    return this->value != other.value;
};

// -------------------------------------------- Arithmetic Operators ---------------------------------------------

Fixed Fixed::operator + (const Fixed& other) const
{
    Fixed result;
    
    result.value = this->value + other.value;
    return result;
};

Fixed Fixed::operator - (const Fixed& other) const
{
    Fixed result;
    
    result.value = this->value - other.value;
    return result;
};

// when multiplying two fixed-point numbers, which is multiplying two scaled values, it results in an extra scaling
// (a << 8) * (b << 8) = ( a * b ) << 16
// the result must be shifted right by fractional_bits to correct it
Fixed Fixed::operator * (const Fixed& other) const
{
    Fixed result;
    
    result.value = (this->value * other.value) >> fractional_bits;
    return result;
};

// to maintain fixed-point precision, this->value must be shifted left before dividing to avoid losing the fractional part
Fixed Fixed::operator / (const Fixed& other) const
{
    Fixed result;

    if (other.value != 0)
        result.value = (this->value << fractional_bits)/ other.value;
    else
        result.value = 0;
    return result;
};

// --------------------------------------- Increment / Decrement Operators ---------------------------------------------

// pre-increment (++a) - this operator modifies the object (*this) in-place
// it returns a reference to the current object (*this) so you can chain operations or observe the updated value immediately

// Pre-increment
Fixed& Fixed::operator ++ ( void )
{
    value += (1 << fractional_bits);
    return *this;
};

// Pre-decrement
Fixed& Fixed::operator -- ( void )
{
    value -= (1 << fractional_bits);
    return *this;
};

// post-increment (a++) - this operator must return the original value before the increment, so it makes a copy of the current object, then increments the current one
// you cannot return a reference here because the result is a temporary copy — returning a reference to that would be unsafe and incorrect
// the int is just a dummy to differentiate it from pre-increment

// Post-increment
Fixed Fixed::operator ++ ( int )
{
    Fixed copy(*this);
    value += (1 << fractional_bits);
    return copy;
};

// Post-decrement
Fixed Fixed::operator -- ( int )
{
    Fixed copy(*this);
    value -= (1 << fractional_bits);
    return copy;
};

// -------------------------------------------- Min / Max Functions ---------------------------------------------

// If min and max don't depend on any internal state of a specific Fixed object (which they shouldn't), then they should be declared static.

Fixed& Fixed::min(Fixed& first, Fixed& second)
{
    return (first <= second) ? first : second;
};

Fixed& Fixed::max(Fixed& first, Fixed& second)
{
    return (first >= second) ? first : second;
};

const Fixed& Fixed::min(const Fixed& first, const Fixed& second)
{
    if (first < second)
        return first;
    return second;
};

const Fixed& Fixed::max(const Fixed& first, const Fixed& second)
{
    if (first > second)
        return first;
    return second;
};