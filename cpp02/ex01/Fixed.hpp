#ifndef FIXED_HPP
# define FIXED_HPP

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <limits>

class Fixed
{
    private:
        int                 value;
        static const int    s_fractional_bits;

    public:
        static const int    max_input;
        static const int    min_input;
        
        Fixed();                                // default constructor
        Fixed(const int new_value);             // overload constructor for int input
        Fixed(const float new_value);           // overload constructor for float input
        Fixed(const Fixed& origin);             // copy constructor
        Fixed& operator = (const Fixed& origin);// copy assignment operator
        ~Fixed();                               // destructor

        int     getRawBits( void ) const;
        void    setRawBits( int const raw );
        float   toFloat( void ) const;
        int     toInt( void ) const;

};

// insertion operator is in namespace of ostream, not object of the class, so its overloaded functionality is not inside the class
std::ostream& operator << (std::ostream& os, const Fixed& value);

#endif