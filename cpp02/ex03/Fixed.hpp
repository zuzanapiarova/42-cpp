#ifndef FIXED_HPP
# define FIXED_HPP

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

#include <iostream>
#include <cmath>
#include <limits>

class Fixed
{
    private:
        int value;
        static const int s_fractional_bits;

    public:
        static const int max_input;
        static const int min_input;
        static const int max_raw_value;
        static const int min_raw_value;

        Fixed();
        Fixed(const int new_value);
        Fixed(const float new_value);
        Fixed(const Fixed& origin);
        Fixed& operator = (const Fixed& origin);
        ~Fixed();

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

        Fixed& operator ++ ( void );
        Fixed& operator -- ( void );
        Fixed operator ++ ( int );
        Fixed operator -- ( int );

        static Fixed& min(Fixed& first, Fixed& second);
        static Fixed& max(Fixed& first, Fixed& second);
        static const Fixed& min(const Fixed& first, const Fixed& second);
        static const Fixed& max(const Fixed& first, const Fixed& second);

};

std::ostream& operator << (std::ostream& os, const Fixed& value);

#endif