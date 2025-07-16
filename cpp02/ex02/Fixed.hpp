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

        Fixed(); // default constructor
        Fixed(const int new_value); // overload constructor for int fixed value
        Fixed(const float new_value); // overload constructor for float fixed value
        Fixed(const Fixed& origin); // copy constructor
        Fixed& operator = (const Fixed& origin); // copy assignment operator

        ~Fixed(); // destructor

        int     getRawBits( void ) const;
        void    setRawBits( int const raw );
        float   toFloat( void ) const;
        int     toInt( void ) const;


        bool operator < (const Fixed& other) const;
        bool operator <= (const Fixed& other) const;
        bool operator > (const Fixed& other) const;
        bool operator >= (const Fixed& other) const;
        bool operator == (const Fixed& other) const;
        bool operator != (const Fixed& other) const;

        Fixed operator + (const Fixed& other) const;
        Fixed operator - (const Fixed& other) const;
        Fixed operator * (const Fixed& other) const;
        Fixed operator / (const Fixed& other) const;

        Fixed& operator ++ ( void ); // pre-increment
        Fixed& operator -- ( void ); // pre-dscrement
        Fixed operator ++ ( int );   // post-increment
        Fixed operator -- ( int );   // post-decrement

        static Fixed& min(Fixed& first, Fixed& second);
        static Fixed& max(Fixed& first, Fixed& second);

        static const Fixed& min(const Fixed& first, const Fixed& second);
        static const Fixed& max(const Fixed& first, const Fixed& second);

};

std::ostream& operator << (std::ostream& os, const Fixed& value);

#endif