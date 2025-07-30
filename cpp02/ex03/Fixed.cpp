#include "Fixed.hpp"

// static members must be declared outside a class
const int Fixed::s_fractional_bits = 8;

const int Fixed::max_input = std::numeric_limits<int>::max() >> s_fractional_bits; // 8388607
const int Fixed::min_input = std::numeric_limits<int>::min() >> s_fractional_bits; // -8388608

const int Fixed::max_raw_value = std::numeric_limits<int>::max(); // 2,147,483,647
const int Fixed::min_raw_value = std::numeric_limits<int>::min(); // -2,147,483,648

// -------------------------------------------- Orthodox Canonical Form ---------------------------------------------

// Default Constructor
Fixed::Fixed() : value()
{
    std::cout<< "Fixed default constructor called" << std::endl;
};

// Overload Constructor from Int
Fixed::Fixed(const int new_value)
{
    std::cout << "Fixed Int constructor called" << std::endl;
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
        value = new_value << s_fractional_bits;
};

// Overload Constructor from Float
Fixed::Fixed(const float new_value)
{
    std::cout << "Fixed Float constructor called" << std::endl;
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
        value = static_cast<int>(roundf(new_value * (1 << s_fractional_bits)));
};

// Copy Constructor
Fixed::Fixed(const Fixed& origin)
{
    std::cout << "Fixed copy constructor called" << std::endl;
    this->value = origin.value;
};

// Copy Assignment Operator
Fixed& Fixed::operator = (const Fixed& origin)
{
    std::cout << "Fixed copy assignment operator called" << std::endl;
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
    return value;
};

void Fixed::setRawBits( int const raw )
{
    value = raw;
};

float Fixed::toFloat( void ) const
{
    return static_cast<float>(value) / (1 << s_fractional_bits);

};

int Fixed::toInt( void ) const
{
    return value >> s_fractional_bits;
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
    Fixed       result;
    long long   sum;

    sum = static_cast<long long>(this->value) + static_cast<long long>(other.value);
    if (sum > max_raw_value)
    {
        std::cerr << "Error: Sum larger than maximum value. Clamping to maximum allowed value." << std::endl;
        result.value = max_raw_value;
    }
    else if (sum < min_raw_value)
    {
        std::cerr << "Error: Sum smaller than minimum value. Clamping to minimum allowed value." << std::endl;
        result.value = min_raw_value;
    }
    else
        result.value = static_cast<int>(sum);
    return result;
};

Fixed Fixed::operator - (const Fixed& other) const
{
    Fixed   result;
    long long diff;
    
    diff = static_cast<long long>(this->value) - static_cast<long long>(other.value);
    if (diff > max_raw_value)
    {
        std::cerr << "Error: Difference larger than maximum value. Clamping to maximum allowed value." << std::endl;
        result.value = max_raw_value;
    }
    else if (diff < min_raw_value)
    {
        std::cerr << "Error: Difference smaller than minimum value. Clamping to minimum allowed value." << std::endl;
        result.value = min_raw_value;
    }
    else
        result.value = static_cast<int>(diff);
    return result;
};

// must be shifted right as multiplying results in an extra scaling, so it must be shifted back by fractional bits to be correct
Fixed Fixed::operator * (const Fixed& other) const
{
    Fixed       result;
    long long   product;
    
    product = (static_cast<long long>(this->value) * static_cast<long long>(other.value)) >> s_fractional_bits;
    if (product > max_raw_value)
    {
        std::cerr << "Error: Product larger than maximum value. Clamping to maximum allowed value." << std::endl;
        result.value = max_raw_value;
    }
    else if (product < min_raw_value)
    {
        std::cerr << "Error: Product smaller than minimum value. Clamping to minimum allowed value." << std::endl;
        result.value = min_raw_value;
    }
    else
        result.value = static_cast<int>(product);
    return result;
};

// to maintain fixed-point precision, this->value must be shifted left before dividing to avoid losing the fractional part
Fixed Fixed::operator / (const Fixed& other) const
{
    Fixed       result;
    long long   div;

    if (other.value == 0)
    {
        std::cerr << "Error: Division by 0. Doing nothing." << std::endl;
        result.value = this->value;
        return result;
    }
    div = (static_cast<long long>(this->value) << s_fractional_bits) / other.value;
    if (div > max_raw_value)
    {
        std::cerr << "Error: Result larger than maximum value. Clamping to maximum allowed value." << std::endl;
        result.value = max_raw_value;
    }
    else if (div < min_raw_value)
    {
        std::cerr << "Error: Result smaller than minimum value. Clamping to minimum allowed value." << std::endl;
        result.value = min_raw_value;
    }
    else
        result.value = static_cast<int>(div);

    return result;
};

// --------------------------------------- Increment / Decrement Operators ---------------------------------------------

// Pre-increment
Fixed& Fixed::operator ++ ( void )
{
    if (value >= max_raw_value)
        std::cerr << "Cannot increment. Value is already the highest allowed number." << std::endl;
    else
        value += 1;
    return *this;
};

// Pre-decrement
Fixed& Fixed::operator -- ( void )
{
    if (value <= min_raw_value)
        std::cerr << "Cannot decrement. Value is already the lowest allowed number." << std::endl;
    else
        value -= 1;
    return *this;
};

// Post-increment
Fixed Fixed::operator ++ ( int )
{
    Fixed copy(*this);

    if (value >= max_raw_value)
        std::cerr << "Cannot increment. Value is already the highest allowed number." << std::endl;
    else
        value += 1;
    return copy;
};

// Post-decrement
Fixed Fixed::operator -- ( int )
{
    Fixed copy(*this);

    if (value <= min_raw_value)
        std::cerr << "Cannot decrement. Value is already the lowest allowed number." << std::endl;
    else
        value -= 1;
    return copy;
};

// -------------------------------------------- Min / Max Functions ---------------------------------------------

Fixed& Fixed::min(Fixed& first, Fixed& second)
{
    return (first <= second) ? first : second;
};

Fixed& Fixed::max(Fixed& first, Fixed& second)
{
    return (first >= second) ? first : second;
};

// const overloads
const Fixed& Fixed::min(const Fixed& first, const Fixed& second)
{
    return (first <= second) ? first : second;
};

const Fixed& Fixed::max(const Fixed& first, const Fixed& second)
{
    return (first >= second) ? first : second;
};
