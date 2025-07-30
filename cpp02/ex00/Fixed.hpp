#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include <string>

class Fixed
{
    private:
        int value;
        static const int s_fractional_bits;

    public:
        Fixed();                                  // default constructor
        Fixed(const Fixed& origin);               // copy constructor
        Fixed& operator = (const Fixed& origin);  // copy assignment operator
        ~Fixed();                                 // destructor

        int     getRawBits( void ) const;
        void    setRawBits( int const raw );
};

#endif