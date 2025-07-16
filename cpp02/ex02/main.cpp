#include "Fixed.hpp"

int main(void)
{
    Fixed a(8388607);
    Fixed const b( 0 );

    // tests from subject
    std::cout << a << std::endl;
    std::cout << ++a << std::endl;
    std::cout << a << std::endl;
    std::cout << a++ << std::endl;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << Fixed::max( a, b ) << std::endl;
    
    // my tests
    std::cout << "Smaller: " << (a < b) << std::endl;
    std::cout << "Greater: " << (a > b) << std::endl;
    std::cout << "< or eq: " << (a <= b) << std::endl;
    std::cout << "> or eq: " << (a >= b) << std::endl;
    std::cout << "Equals : " << (a == b) << std::endl;
    std::cout << "Not eq : " << (a != b) << std::endl;
    
    std::cout << "Plus  : " << (a + b) << std::endl;
    std::cout << "Minus : " << (a - b) << std::endl;
    std::cout << "Multi : " << (a * b) << std::endl;
    std::cout << "Divide: " << (a / b) << std::endl;

    std::cout << "Increment: " << ++a << std::endl;
    std::cout << "Decrement: " << a++ << std::endl;

    std::cout << "Min : " << Fixed::min( a, b ) << std::endl;
    std::cout << "Max : " << Fixed::max( a, b ) << std::endl;

    Fixed const c( 3 );
    Fixed const d( Fixed( 5.05f ) * Fixed( 2 ) );

    std::cout << "Min const: " << Fixed::min( c, d ) << std::endl;
    std::cout << "Max const: " << Fixed::max( c, d ) << std::endl;

    return 0;
}