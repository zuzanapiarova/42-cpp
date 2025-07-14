#include "Fixed.hpp"

// ! PROTECT AGAINS INT_MAX/INT_MIN

int main(void)
{
    Fixed a(3);
    Fixed b;
    b = Fixed(Fixed( 5.05f ) * Fixed( 2 ));
    
    std::cout << (a < b) << std::endl;
    std::cout << (a > b) << std::endl;
    std::cout << (a <= b) << std::endl;
    std::cout << (a >= b) << std::endl;
    std::cout << (a == b) << std::endl;
    std::cout << (a != b) << std::endl;
    
    std::cout << (a + b) << std::endl;
    std::cout << (a - b) << std::endl;
    std::cout << (a * b) << std::endl;
    std::cout << (a / b) << std::endl;

    std::cout << ++a << std::endl;
    std::cout << a++ << std::endl;

    std::cout << Fixed::min( a, b ) << std::endl;
    std::cout << Fixed::max( a, b ) << std::endl;

    Fixed const c( 3 );
    Fixed const d( Fixed( 5.05f ) * Fixed( 2 ) );

    std::cout << Fixed::min( c, d ) << std::endl;
    std::cout << Fixed::max( c, d ) << std::endl;

    return 0;
}