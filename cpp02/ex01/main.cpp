#include "Fixed.hpp"

int main(void)
{
    Fixed a;
    Fixed const b( 8388608 );
    Fixed const c( -8388608 );
    Fixed const d( b );
    
    a = Fixed( 1234.00390625f );
    std::cout << std::fixed << std::setprecision(8) << std::endl; // disables scientific notation

    // overload insertion operator
    std::cout << "a is " << a << std::endl;
    std::cout << "b is " << b << std::endl;
    std::cout << "c is " << c << std::endl;
    std::cout << "d is " << d << std::endl << std::endl;

    // float representation
    std::cout << "a is " << a.toFloat() << " as float" << std::endl;
    std::cout << "b is " << b.toFloat() << " as float" << std::endl;
    std::cout << "c is " << c.toFloat() << " as float" << std::endl;
    std::cout << "d is " << d.toFloat() << " as float" << std::endl << std::endl;

    // int represen
    std::cout << "a is " << a.toInt() << " as integer" << std::endl;
    std::cout << "b is " << b.toInt() << " as integer" << std::endl;
    std::cout << "c is " << c.toInt() << " as integer" << std::endl;
    std::cout << "d is " << d.toInt() << " as integer" << std::endl << std::endl;
    
    return 0;
}