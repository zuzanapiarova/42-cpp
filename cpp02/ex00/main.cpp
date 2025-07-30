#include "Fixed.hpp"

int main(void)
{
    Fixed a;        // default constructor
    Fixed b( a );   // copy constructor

    Fixed c;
    c = b;          // copy assignment operator

    std::cout << a.getRawBits() << std::endl;
    std::cout << b.getRawBits() << std::endl;
    std::cout << c.getRawBits() << std::endl;

    a.setRawBits(42);
    b.setRawBits(15);
    c.setRawBits(-50);

    std::cout << a.getRawBits() << std::endl;
    std::cout << b.getRawBits() << std::endl;
    std::cout << c.getRawBits() << std::endl;

    return 0;
}