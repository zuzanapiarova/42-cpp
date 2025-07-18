#include "Fixed.hpp"

int main(void)
{
    Fixed a;
    Fixed const b( -8388609 );
    Fixed const c( -8388609.1f );
    Fixed const d( b );
    
    // a = Fixed( 8388607 ); // 2^23 - 1 - correct max int since 8 bits are used for fractional part and 1 for sign
    a = Fixed( 1234.4321f );

    // overload insertion operator
    std::cout << "a is " << a << std::endl;
    std::cout << "b is " << b << std::endl;
    std::cout << "c is " << c << std::endl;
    std::cout << "d is " << d << std::endl;

    // float representation
    std::cout << "a is " << a.toFloat() << " as float" << std::endl;
    std::cout << "b is " << b.toFloat() << " as float" << std::endl;
    std::cout << "c is " << c.toFloat() << " as float" << std::endl;
    std::cout << "d is " << d.toFloat() << " as float" << std::endl;

    // int represen
    std::cout << "a is " << a.toInt() << " as integer" << std::endl;
    std::cout << "b is " << b.toInt() << " as integer" << std::endl;
    std::cout << "c is " << c.toInt() << " as integer" << std::endl;
    std::cout << "d is " << d.toInt() << " as integer" << std::endl;

    return (EXIT_SUCCESS);
}