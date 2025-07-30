#ifndef POINT_HPP
# define POINT_HPP

#include "Fixed.hpp"

#include <iostream>
#include <cmath>
#include <limits>

class Point
{
    private:
        const Fixed x;
        const Fixed y;

    public:
        Point();
        Point(const float new_x, const float new_y);
        Point(const Point& origin);
        Point& operator = (const Point& origin);
        ~Point();

        const Fixed& getX( void ) const ;
        const Fixed& getY( void ) const ;

};

#endif