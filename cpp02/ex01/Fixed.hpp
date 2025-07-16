#ifndef FIXED_H
# define FIXED_H

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

#include <iostream>
#include <string>
#include <cmath>
#include <limits>

class Fixed
{
    private:
        int value;
        static const int fractional_bits; // bits for storing numbers after the fixed point

    public:
        static const int max_input;
        static const int min_input;

        static const int max_raw_value;
        static const int min_raw_value;

        Fixed();                        // default constructor
        Fixed(const int new_value);     // overload constructor for int fixed value
        Fixed(const float new_value);   // overload constructor for float fixed value
        Fixed(const Fixed& origin);     // copy constructor
        Fixed& operator = (const Fixed& origin); // copy assignment operator

        ~Fixed();                       // destructor

        int     getRawBits( void ) const;
        void    setRawBits( int const raw );
        float   toFloat( void ) const;
        int     toInt( void ) const;

};

// insertion operator is std::ostream object, not object of the class, so its overloaded functionality is not inside the class
std::ostream& operator << (std::ostream& os, const Fixed& value);

#endif