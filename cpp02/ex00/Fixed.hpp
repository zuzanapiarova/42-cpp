#ifndef FIXED_H
# define FIXED_H

#include <iostream>
#include <string>

class Fixed
{
    private:
        int value;
        static const int fractional_bits;

    public:
        Fixed(); // default constructor
        Fixed(const Fixed& origin); // copy constructor
        Fixed& operator = (const Fixed& origin); // copy assignment operator
        ~Fixed(); // destructor

        int     getRawBits( void ) const;
        void    setRawBits( int const raw );
};

#endif