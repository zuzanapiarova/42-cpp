#include "Fixed.hpp"

int main(void)
{
    std::cout << std::fixed << std::setprecision(8); // disables scientific notation

    // A. basic tests
    Fixed a(10);
    Fixed const b( 5.05f );
    Fixed const c( 3 );
    Fixed const d( b * Fixed( 2 ) );
    
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

    std::cout << "Min const: " << Fixed::min( c, d ) << std::endl;
    std::cout << "Max const: " << Fixed::max( c, d ) << std::endl;

    // B. edge-case tests - error/clamping
    // Fixed e(8388607);
    // Fixed f(-8388608);
    // Fixed g(0.00390625f);

    // std::cout << "Plus > int : " << (e + e) << std::endl;
    // std::cout << "Plus < int : " << (f + f) << std::endl;
    // std::cout << "Minus > int : " << (e - f) << std::endl;
    // std::cout << "Minus < int : " << (f - e) << std::endl;
    // std::cout << "Multi > int : " << (e * e) << std::endl;
    // std::cout << "Multi < int : " << (e * f) << std::endl;
    // std::cout << "Multi near 0: " << (g * g) << std::endl; 
    // std::cout << "Divide > int: " << (e / g) << std::endl;
    // std::cout << "Divide < int: " << (f / g) << std::endl;
    // std::cout << "Divide by 0 : " << (e / 0) << std::endl;

    return 0;
}